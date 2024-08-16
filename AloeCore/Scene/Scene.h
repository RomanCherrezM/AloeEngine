#pragma once

#include "Core/UUID.h"

#include <entt.hpp>

#include <vector>

#include <Scene/Entity.h>

namespace Aloe
{
    class Entity;

    class Scene
    {
    public:
        Scene();
        static std::shared_ptr<Scene> Copy(std::shared_ptr<Scene> other);

        Entity CreateEntityByUUID(const UUID& uuid, const std::string& name = std::string());
        Entity CreateEntity(const std::string& name);
        void DestroyEntity(Entity entity);

        template<typename... Components>
        std::vector<Entity> GetEntities()
        {
            std::vector<Entity> result;

            auto view = m_registry.view<Components...>();

            for (auto entity : view) 
            {
                auto it = m_entityMap.find(entity);

                if (it != m_entityMap.end()) 
                {
                    result.push_back(it->second);
                }
            }

            return result;
        }

        std::vector<Entity> GetAllEntities();

        // TODO: Optimize this
        Entity FindEntityByUUID(const UUID& uuid);

    private:
        entt::registry m_registry;
        std::unordered_map<entt::entity, Entity> m_entityMap;

        friend class Entity;
    };
}