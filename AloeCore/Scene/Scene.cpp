#include "Scene.h"
#include "Scene.h"
#include "Scene.h"

#include "ECS/Components/Components.h"
#include <Scene/Entity.h>

namespace Aloe
{
    Scene::Scene()
    {
    }

    Entity Scene::CreateEntityByUUID(const UUID& uuid, const std::string& name)
    {
        entt::entity enttEntity = m_registry.create();
        Entity entity = { enttEntity, this };

        entity.AddComponent<IDComponent>(uuid);
        entity.AddComponent<TransformComponent>();
        auto& tag = entity.AddComponent<NameComponent>();
        tag.m_name = name.empty() ? "Entity" : name;

        m_entityMap[enttEntity] = entity;

        return entity;

    }

    Entity Scene::CreateEntity(const std::string& name)
    {
        return CreateEntityByUUID(UUID(), name);
    }
    void Scene::DestroyEntity(Entity entity)
    {
        m_entityMap.erase(entity.m_handler);
        m_registry.destroy(entity.m_handler);
    }

    std::vector<Entity> Aloe::Scene::GetAllEntities()
    {
        std::vector<Entity> result;
        result.reserve(m_entityMap.size());

        for (const auto& pair : m_entityMap)
        {
            result.push_back(pair.second);
        }

        return result;
    }

    Entity Scene::FindEntityByUUID(const UUID& uuid)
    {
        for (const auto& pair : m_entityMap)
        {
            Entity entity = pair.second;
            if (entity.GetComponent<IDComponent>().m_UUID == uuid) return entity;
        }

        return Entity();
    }
}