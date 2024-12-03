#include "EditorInspectorPanel.h"

#include <imgui.h>

#include <misc/cpp/imgui_stdlib.h>

#include <Application/Systems/ApplicationSystems.h>
#include <Application/Systems/ECSManager.h>

#include <ECS/Components/Components.h>

#include <Core/AloeEngine.h>
#include <Core/AssetSerializer.h>
#include <Core/AssetLibrary.h>

#include <Editor/EditorHelpers.h>

namespace Aloe {

    typedef void (*DrawComponentFunction)(Entity entity);

    EditorInspectorPanel::EditorInspectorPanel(EditorEventMessenger* eventRef)
    {
        m_eventMessenger = eventRef;
    }

    void DrawIDComponent(Entity entity)
    {
        IDComponent& component = entity.GetComponent<IDComponent>();
        ImGui::Text("Unique ID: "); ImGui::SameLine();
        ImGui::Text(std::to_string(component.m_UUID).c_str());
    }

    void DrawNameComponent(Entity entity)
    {
        NameComponent& component = entity.GetComponent<NameComponent>();
        ImGui::Text("Entity Name: "); ImGui::SameLine();
        ImGui::InputText("##Entity", &component.m_name);
    }

    void DrawHierarchyComponent(Entity entity)
    {
        HierarchyComponent& component = entity.GetComponent<HierarchyComponent>();

        if (!component.IsRoot())
        {
            Entity parent = component.GetParent();
            ImGui::Text("Parent: "); ImGui::SameLine();
            ImGui::Text(parent.GetComponent<NameComponent>().m_name.c_str()); ImGui::SameLine();
            ImGui::Text(std::to_string(parent.GetComponent<IDComponent>().m_UUID).c_str());
        }

        ImGui::Text("Children:");
        ImGui::Indent();
        for (auto child : component.GetChildren())
        {
            ImGui::Text("Child: "); ImGui::SameLine();
            ImGui::Text(child.GetComponent<NameComponent>().m_name.c_str()); ImGui::SameLine();
            ImGui::Text(std::to_string(child.GetComponent<IDComponent>().m_UUID).c_str());
        }
        ImGui::Unindent();
    }

    void DrawTransformComponent(Entity entity)
    {
        TransformComponent& component = entity.GetComponent<TransformComponent>();

        Aloe::DrawVec3Editor("Position", component.m_position);
        Aloe::DrawVec3Editor("Rotation", component.m_rotation);
        Aloe::DrawVec3Editor("Scale", component.m_scale, 1.0f);
    }

    void DrawInputComponent(Entity entity)
    {
        InputComponent& component = entity.GetComponent<InputComponent>();
    }

    void DrawMeshComponent(Entity entity)
    {
        MeshComponent& component = entity.GetComponent<MeshComponent>();
    }

    void DrawMeshRenderer(Entity entity)
    {
        MeshRenderer& component = entity.GetComponent<MeshRenderer>();
    }

    void DrawSpriteComponent(Entity entity)
    {
        SpriteComponent& component = entity.GetComponent<SpriteComponent>();
        AssetLibrary* library = AssetLibrary::Get();

        std::shared_ptr<Asset> texture = library->GetAsset<Texture>(component.m_textureUUID);
        if (texture != nullptr && texture->m_assetSpec.m_path != "")
        {
            ImGui::Text(texture->m_assetSpec.m_path.c_str());
        }           
        else
        {
            ImGui::Text("No Texture");
        }

        if (ImGui::BeginDragDropTarget())
        {
            ImGuiDragDropFlags targetFlags = 0;

            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DragAsset", targetFlags)) {
                std::string assetPath = std::string((char*)payload->Data, payload->DataSize);

                AssetSerializer assetSerializer(assetPath);
                AssetSpec spec = assetSerializer.Deserialize();

                component.m_textureUUID = spec.m_uuid;
            }

            ImGui::EndDragDropTarget();
        }

        Aloe::DrawColorEditor("Color", component.m_color);

    }

    void DrawRigidbody2DComponent(Entity entity)
    {
        Rigidbody2DComponent& component = entity.GetComponent<Rigidbody2DComponent>();

        const char* bodyTypes[] = { "Static", "Kinematic", "Dynamic" };
        int currentItem = (int)component.m_type;

        if (ImGui::Combo("Object Type", &currentItem, bodyTypes, IM_ARRAYSIZE(bodyTypes)))
        {
            Rigidbody2DComponent::BodyType selectedType = static_cast<Rigidbody2DComponent::BodyType>(currentItem);

            component.m_type = selectedType;
        }

        ImGui::Checkbox("Fixed Rotatiton", &component.m_fixedRotation);

    }

    void DrawSquareCollider2DComponent(Entity entity)
    {
        SquareCollider2DComponent& component = entity.GetComponent<SquareCollider2DComponent>();

        DrawFloatEditor("Density", component.m_density);
        DrawFloatEditor("Friction", component.m_friction);
        DrawFloatEditor("Restitution", component.m_restitution);
        DrawFloatEditor("Restitution Threshold", component.m_restitutionThreshold);
    }

    void DrawCameraComponent(Entity entity)
    {
        CameraComponent& component = entity.GetComponent<CameraComponent>();

        auto engine = Aloe::Engine::Get();

        bool isMainCamera = engine->GetMainCamera() == &component;
        if (ImGui::Checkbox("Main Camera", &isMainCamera))
        {
            engine->SetMainCamera(&component);
        }

        DrawVec3Editor("Position", component.m_cameraData.m_position);
        DrawVec3Editor("Up", component.m_cameraData.m_up);
        DrawVec3Editor("Front", component.m_cameraData.m_front);

        DrawExtendedSliderEditor("Field of View", component.m_cameraData.m_fov, 0.0f, 180.0f);
        DrawFloatEditor("Near Plane", component.m_cameraData.m_nearPlane);
        DrawFloatEditor("Far Plane", component.m_cameraData.m_farPlane);

        if (component.m_renderTarget == nullptr)
        {
            if (ImGui::Button("Create Render Target"))
            {
                component.CreateRenderTarget();
            }
        }
        else
        {
            float space = ImGui::GetContentRegionAvail().x;
            ImGui::Image((ImTextureID)component.m_renderTarget->GetColorAttachmentRendererID(),
                ImVec2(space, space * (9.0f / 16.0f)),ImVec2(0, 1), ImVec2(1, 0));
        }
    }

    template<typename T>
    static void DrawComponent(Entity entity, const std::string& compName, DrawComponentFunction fn)
    {
        const ImGuiTreeNodeFlags treeNodeFlags =
            ImGuiTreeNodeFlags_DefaultOpen |
            ImGuiTreeNodeFlags_Bullet |
            ImGuiTreeNodeFlags_Framed |
            ImGuiTreeNodeFlags_Leaf |
            ImGuiTreeNodeFlags_SpanAvailWidth |
            ImGuiTreeNodeFlags_AllowItemOverlap |
            ImGuiTreeNodeFlags_FramePadding;

        if (entity.HasComponent<T>())
        {
            bool open = true;
            ImGui::CollapsingHeader(compName.c_str(), &open, treeNodeFlags);

            if (open)
            {
                fn(entity);
            }
            else 
            {
                entity.RemoveComponent<T>();
            }
        }
    }
    template<typename T>
    void AddComponentEntry(Entity entity, const std::string& compName)
    {
        if (!entity.HasComponent<T>())
        {
            if (ImGui::MenuItem(compName.c_str()))
            {
                entity.AddComponent<T>();
                ImGui::CloseCurrentPopup();
            }
        }
    }

    void AddComponentEntryFromString(ScriptSystem* scriptSystem, Entity entity, const std::string& scriptName)
    {
        if (!scriptSystem->HasComponentFromString(scriptName, entity))
        {
            if (ImGui::MenuItem(scriptName.c_str()))
            {
                scriptSystem->AddComponentFromString(scriptName, entity);
                ImGui::CloseCurrentPopup();
            }
        }
    }

    void EditorInspectorPanel::AddComponentPopUp()
    {
        const ImVec2 buttonSize = ImVec2(-FLT_MIN, 0.0f);

        if (ImGui::Button("Add Component", buttonSize))
            ImGui::OpenPopup("AddComponent");

        if (ImGui::BeginPopup("AddComponent"))
        {
            AddComponentEntry<IDComponent>(m_selectedEntity, "ID Component");
            AddComponentEntry<NameComponent>(m_selectedEntity, "Name Component");
            AddComponentEntry<TransformComponent>(m_selectedEntity, "Transform Component");
            AddComponentEntry<HierarchyComponent>(m_selectedEntity, "Hierarchy Component");
            AddComponentEntry<InputComponent>(m_selectedEntity, "Input Component");
            AddComponentEntry<MeshComponent>(m_selectedEntity, "Mesh Component");
            AddComponentEntry<MeshRenderer>(m_selectedEntity, "Mesh Renderer Component");
            AddComponentEntry<SpriteComponent>(m_selectedEntity, "Sprite Component");
            AddComponentEntry<CameraComponent>(m_selectedEntity, "Camera Component");
            AddComponentEntry<Rigidbody2DComponent>(m_selectedEntity, "Rigidbody2D Component");
            AddComponentEntry<SquareCollider2DComponent>(m_selectedEntity, "SquareCollider2D Component");

            for each (auto scriptName in m_scriptSystem->GetScriptList())
            {
                AddComponentEntryFromString(m_scriptSystem, m_selectedEntity, scriptName);
            }

            ImGui::EndPopup();
        }
    }

    void DrawComponentFromString(ScriptSystem* scriptSystem, Entity entity, const std::string& scriptName)
    {
        const ImGuiTreeNodeFlags treeNodeFlags =
            ImGuiTreeNodeFlags_DefaultOpen |
            ImGuiTreeNodeFlags_Framed |
            ImGuiTreeNodeFlags_SpanAvailWidth |
            ImGuiTreeNodeFlags_AllowItemOverlap |
            ImGuiTreeNodeFlags_FramePadding;

        if (scriptSystem->HasComponentFromString(scriptName, entity))
        {
            bool open = ImGui::TreeNodeEx(scriptName.c_str(), treeNodeFlags, scriptName.c_str());

            if (open)
            {
                scriptSystem->DrawInterfaceFromString(scriptName, entity);
                ImGui::TreePop();
            }
        }
    }

    bool EditorInspectorPanel::OnPanelUpdate(Entity entity)
    {
        bool open = true;
        if (ImGui::Begin("Component Settings", &open))
        {
            if (m_selectedEntity.IsValid())
            {
                DrawComponent<IDComponent>(m_selectedEntity, "ID Component", DrawIDComponent);
                DrawComponent<NameComponent>(m_selectedEntity, "Name Component", DrawNameComponent);
                DrawComponent<TransformComponent>(m_selectedEntity, "Transform Component", DrawTransformComponent);
                DrawComponent<HierarchyComponent>(m_selectedEntity, "Hierarchy Component", DrawHierarchyComponent);
                DrawComponent<InputComponent>(m_selectedEntity, "Input Component", DrawInputComponent);
                DrawComponent<MeshComponent>(m_selectedEntity, "Mesh Component", DrawMeshComponent);
                DrawComponent<MeshRenderer>(m_selectedEntity, "Mesh Renderer Component", DrawMeshRenderer);
                DrawComponent<SpriteComponent>(m_selectedEntity, "Sprite Component", DrawSpriteComponent);
                DrawComponent<CameraComponent>(m_selectedEntity, "Camera Component", DrawCameraComponent);
                DrawComponent<Rigidbody2DComponent>(m_selectedEntity, "Rigidbody2D Component", DrawRigidbody2DComponent);
                DrawComponent<SquareCollider2DComponent>(m_selectedEntity, "SquareCollider2D Component", DrawSquareCollider2DComponent);

                for each (auto scriptName in m_scriptSystem->GetScriptList())
                {
                    DrawComponentFromString(m_scriptSystem, m_selectedEntity, scriptName);
                }

                AddComponentPopUp();
            }
        }
        ImGui::End();

        return !open;
    }

    void EditorInspectorPanel::Init()
    {
        m_scriptSystem = Engine::Get()->GetApplicationSystems()->GetECSManager()->GetScriptSystem();
    }

    EPanelType EditorInspectorPanel::GetPanelType()
    {
        return EPanelType::Inspector;
    }

    void EditorInspectorPanel::OnEvent(Aloe::EditorEvent& event)
    {
        switch (event.GetType())
        {
        case HierarchyEntitySelected:
            m_selectedEntity = reinterpret_cast<HierarchyEntitySelectedEvent*>(&event)->GetEntity();
            break;
        case SceneChanged:
            m_selectedEntity = Entity();
            break;
        }
    }
}