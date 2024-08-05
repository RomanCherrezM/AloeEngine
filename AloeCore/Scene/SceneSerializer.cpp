#include "SceneSerializer.h"

#define YAML_CPP_STATIC_DEFINE

#include <yaml-cpp/yaml.h>

#include <ECS/Components/Components.h>
#include <Core/AloeEngine.h>

#include <fstream>

namespace YAML
{
    template<>
    struct convert<glm::vec3>
    {
        static Node encode(const glm::vec3& vec)
        {
            Node node;
            node.push_back(vec.x);
            node.push_back(vec.y);
            node.push_back(vec.z);
            return node;
        }

        static bool decode(const Node& node, glm::vec3& vec)
        {
            if (!node.IsSequence() || node.size() != 3)
                return false;

            vec.x = node[0].as<float>();
            vec.y = node[1].as<float>();
            vec.z = node[2].as<float>();

            return true;
        }
    };

    Emitter& operator<<(Emitter& out, const glm::vec3& vec)
    {
        out << Flow;
        out << BeginSeq << vec.x << vec.y << vec.z << EndSeq;
        return out;
    }

    Emitter& operator<<(YAML::Emitter& out, const glm::vec4& vec)
    {
        out << Flow;
        out << BeginSeq << vec.x << vec.y << vec.z << vec.w << EndSeq;
        return out;
    }
}

namespace Aloe {

    SceneSerializer::SceneSerializer(const std::shared_ptr<Scene>& scene)
        : m_scene(scene)
    {
    }

    void SerializeEntity(YAML::Emitter& out, Entity entity) 
    {
        out << YAML::BeginMap; // Entity
        out << YAML::Key << "Entity" << YAML::Value << entity.GetComponent<IDComponent>().m_UUID;

        if (entity.HasComponent<NameComponent>())
        {
            out << YAML::Key << "NameComponent";
            out << YAML::BeginMap; // Name Component

            NameComponent& component = entity.GetComponent<NameComponent>();
            out << YAML::Key << "Name" << YAML::Value << component.m_name;

            out << YAML::EndMap; // Name Component
        }

        if (entity.HasComponent<TransformComponent>())
        {
            out << YAML::Key << "TransformComponent";
            out << YAML::BeginMap; // Transform Component

            TransformComponent& component = entity.GetComponent<TransformComponent>();
            out << YAML::Key << "Position" << YAML::Value << component.m_position;
            out << YAML::Key << "Rotation" << YAML::Value << component.m_rotation;
            out << YAML::Key << "Scale" << YAML::Value << component.m_scale;

            out << YAML::EndMap; // Transform Component
        }

        if (entity.HasComponent<HierarchyComponent>())
        {
            out << YAML::Key << "HierarchyComponent";
            out << YAML::BeginMap; // HierarchyComponent

            HierarchyComponent& component = entity.GetComponent<HierarchyComponent>();
            
            if (component.GetParent())
            {
                const UUID uuid = component.GetParent()->m_entity.GetComponent<IDComponent>().m_UUID;
                out << YAML::Key << "Parent" << YAML::Value << uuid;
            }

            if (component.HasChildren())
            {
                out << YAML::Key << "Children" << YAML::Value << YAML::BeginSeq; // Children

                for each (auto child in component.m_childrenComponent)
                {
                    const UUID uuid = child->m_entity.GetComponent<IDComponent>().m_UUID;
                    out << YAML::Key << "Entity" << YAML::Value << uuid;
                }

                out << YAML::EndSeq; // Children
            }

            out << YAML::EndMap; // HierarchyComponent
        }

        if (entity.HasComponent<CameraComponent>())
        {
            out << YAML::Key << "CameraComponent";
            out << YAML::BeginMap; // CameraComponent

            CameraComponent& component = entity.GetComponent<CameraComponent>();
            CameraData& camera = component.m_cameraData;

            out << YAML::Key << "Main Camera" << YAML::Value << (Engine::Get()->GetMainCamera() == &component);

            out << YAML::Key << "Camera Type" << YAML::Value << camera.m_type;
            out << YAML::Key << "Position" << YAML::Value << camera.m_position;
            out << YAML::Key << "Up" << YAML::Value << camera.m_up;

            out << YAML::Key << "Front" << YAML::Value << camera.m_front;
            out << YAML::Key << "Width" << YAML::Value << camera.m_width;
            out << YAML::Key << "Height" << YAML::Value << camera.m_height;
            out << YAML::Key << "FOV" << YAML::Value << camera.m_fov;

            out << YAML::Key << "Left" << YAML::Value << camera.m_left;
            out << YAML::Key << "Right" << YAML::Value << camera.m_right;
            out << YAML::Key << "Bottom" << YAML::Value << camera.m_bottom;
            out << YAML::Key << "Top" << YAML::Value << camera.m_top;

            out << YAML::Key << "Near Plane" << YAML::Value << camera.m_nearPlane;
            out << YAML::Key << "Far Plane" << YAML::Value << camera.m_farPlane;

            out << YAML::EndMap; // CameraComponent
        }

        if (entity.HasComponent<SpriteComponent>())
        {
            out << YAML::Key << "SpriteComponent";
            out << YAML::BeginMap; // SpriteComponent

            auto component = entity.GetComponent<SpriteComponent>();

            out << YAML::Key << "Texture UUID" << YAML::Value << component.m_textureUUID;

            out << YAML::EndMap; // SpriteComponent
        }

        if (entity.HasComponent<InputComponent>())
        {
            out << YAML::Key << "InputComponent";
            out << YAML::BeginMap; // Component

            InputComponent& component = entity.GetComponent<InputComponent>();

            out << YAML::EndMap; // Component
        }

        //if (entity.HasComponent<Component>())
        //{
        //    out << YAML::Key << "Component";
        //    out << YAML::BeginMap; // Component

        //    Component& component = entity.GetComponent<Component>();

        //    out << YAML::EndMap; // Component
        //}

        out << YAML::EndMap; // Entity
    }

    void SceneSerializer::Serialize(const std::string& filepath)
    {
        YAML::Emitter out;
        out << YAML::BeginMap;
        out << YAML::Key << "Scene" << YAML::Value << "Untitled";
        out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;

        // Serialize all entities
        for each (auto entity in m_scene->GetAllEntities())
        {
            SerializeEntity(out, entity);
        }

        out << YAML::EndSeq; 
        out << YAML::EndMap;

        std::ofstream fout(filepath);
        fout << out.c_str();
    }

    bool SceneSerializer::Deserialize(const std::string& filepath)
    {
        std::ifstream stream(filepath);
        std::stringstream strStream;

        strStream << stream.rdbuf();

        YAML::Node data = YAML::Load(strStream.str());

        auto entitiesNode = data["Entities"];
        
        if (entitiesNode) 
        {
            for each (auto entityNode in entitiesNode)
            {
                uint64_t uuid = entityNode["Entity"].as<uint64_t>();

                // This adds the ID Component
                Entity entity = m_scene->CreateEntityByUUID(uuid);

                auto nameComponentNode = entityNode["NameComponent"];
                if (nameComponentNode)
                {
                    NameComponent& nameComponent = entity.AddComponent<NameComponent>();
                    nameComponent.m_name = nameComponentNode["Name"].as<std::string>();
                }

                auto transformComponentNode = entityNode["TransformComponent"];
                if (transformComponentNode)
                {
                    TransformComponent& transformComponent = entity.AddComponent<TransformComponent>();

                    transformComponent.m_position = transformComponentNode["Position"].as<glm::vec3>();
                    transformComponent.m_rotation = transformComponentNode["Rotation"].as<glm::vec3>();
                    transformComponent.m_scale = transformComponentNode["Scale"].as<glm::vec3>();

                }

                auto spriteComponentNode = entityNode["SpriteComponent"];
                if (spriteComponentNode)
                {
                    SpriteComponent& spriteComponent = entity.AddComponent<SpriteComponent>();

                    spriteComponent.m_textureUUID = spriteComponentNode["Texture UUID"].as<uint64_t>();
                }

                auto inputComponentNode = entityNode["InputComponent"];
                if (inputComponentNode)
                {
                    InputComponent& inputComponent = entity.AddComponent<InputComponent>();
                }

                auto cameraComponentNode = entityNode["CameraComponent"];
                if (cameraComponentNode)
                {
                    CameraComponent& c = entity.AddComponent<CameraComponent>();

                    c.m_cameraData.m_type = (CameraType)cameraComponentNode["Camera Type"].as<int32_t>();
                    c.m_cameraData.m_position = cameraComponentNode["Position"].as<glm::vec3>();
                    c.m_cameraData.m_up = cameraComponentNode["Up"].as<glm::vec3>();
                    c.m_cameraData.m_front = cameraComponentNode["Front"].as<glm::vec3>();
                    c.m_cameraData.m_width = cameraComponentNode["Width"].as<float>();
                    c.m_cameraData.m_height = cameraComponentNode["Height"].as<float>();
                    c.m_cameraData.m_fov = cameraComponentNode["FOV"].as<float>();
                    c.m_cameraData.m_left = cameraComponentNode["Left"].as<float>();
                    c.m_cameraData.m_right = cameraComponentNode["Right"].as<float>();
                    c.m_cameraData.m_bottom = cameraComponentNode["Bottom"].as<float>();
                    c.m_cameraData.m_top = cameraComponentNode["Top"].as<float>();
                    c.m_cameraData.m_nearPlane = cameraComponentNode["Near Plane"].as<float>();
                    c.m_cameraData.m_farPlane = cameraComponentNode["Far Plane"].as<float>();

                    c.CreateRenderTarget();

                    if (cameraComponentNode["Main Camera"].as<bool>())
                    {
                        Engine::Get()->SetMainCamera(&entity.GetComponent<CameraComponent>());
                    }
                }
            }
        }

        return true;
    }

}