#include "Scene.h"

#include "ECS/Components/Components.h"
#include <Scene/Entity.h>

namespace Aloe
{
    Scene::Scene()
    {
    }

    template<typename Component>
    static void CopyComponent(Entity& src, Entity& dst)
    {
        if (src.HasComponent<Component>())
        {            
            dst.ReplaceComponent<Component>(src.GetComponent<Component>());
        }
    }

    std::shared_ptr<Scene> Scene::Copy(std::shared_ptr<Scene> other)
    {
        std::shared_ptr<Scene> newScene = std::make_shared<Scene>();

        auto entities = other->GetAllEntities();

        for each (auto otherEntity in entities)
        {
            UUID uuid = otherEntity.GetComponent<IDComponent>().m_UUID;
            std::string name = otherEntity.GetComponent<NameComponent>().m_name;
            Entity newEntity = newScene->CreateEntityByUUID(uuid, name);

            CopyComponent<TransformComponent>(otherEntity, newEntity);
            CopyComponent<InputComponent>(otherEntity, newEntity);
            CopyComponent<MeshComponent>(otherEntity, newEntity);
            CopyComponent<MeshRenderer>(otherEntity, newEntity);
            CopyComponent<SpriteComponent>(otherEntity, newEntity);
            CopyComponent<CameraComponent>(otherEntity, newEntity);
            CopyComponent<SquareCollider2DComponent>(otherEntity, newEntity);
            CopyComponent<Rigidbody2DComponent>(otherEntity, newEntity);

            // TODO: Copy Scripts
        }

        return newScene;
    }

    Entity Scene::CreateEntityByUUID(const UUID& uuid, const std::string& name)
    {
        entt::entity enttEntity = m_registry.create();
        Entity entity = { enttEntity, this };

        entity.AddComponent<IDComponent>().m_UUID = uuid;
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