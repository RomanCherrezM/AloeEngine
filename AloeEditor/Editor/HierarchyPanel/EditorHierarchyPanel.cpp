#include "EditorHierarchyPanel.h"

#include <vector>

#include <imgui.h>

#include <Editor/EditorHelpers.h>

#include <ECS/Components/Components.h>

#include <Scene/SceneManager.h>

namespace Aloe {

    // TODO: These function should be somewhere else
    void CreateEntity(std::shared_ptr<Scene> scene)
    {
        Entity entity = scene->CreateEntity("New Entity");

        entity.AddComponent<NameComponent>();
        entity.AddComponent<TransformComponent>();
    }

    void CreateSquareCollision(std::shared_ptr<Scene> scene)
    {
        Entity entity = scene->CreateEntity("Square Collision");

        entity.AddComponent<NameComponent>();
        entity.AddComponent<TransformComponent>().m_position = glm::vec3(rand()%30 - 15, 10.0f, 0.0f);
        entity.AddComponent<SpriteComponent>();
        entity.AddComponent<Rigidbody2DComponent>().m_type = Rigidbody2DComponent::BodyType::Dynamic;
        entity.AddComponent<SquareCollider2DComponent>().m_restitution = 1.0f;
    }

    EditorHierarchyPanel::EditorHierarchyPanel(EditorEventMessenger* eventRef)
    {
        m_eventMessenger = eventRef;
    }


    bool EditorHierarchyPanel::OnPanelUpdate(Entity entity)
    {
        bool open = true;
        if (ImGui::Begin("Hierarchy", &open))
        {
            UpdateToolsBar();
            UpdateHierarchy();
        }

        ImGui::End();

        return !open;
    }

    void EditorHierarchyPanel::UpdateToolsBar()
    {
        // Tools Panel
        if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(1))
        {
            ImGui::OpenPopup("CreateEntity");
        }

        if (ImGui::BeginPopup("CreateEntity"))
        {
            if (ImGui::Button("Create Entity"))
            {
                CreateEntity(SceneManager::Get().GetCurrentScene());
            }

            if (ImGui::Button("Create Square Collision"))
            {
                CreateSquareCollision(SceneManager::Get().GetCurrentScene());
            }

            ImGui::EndPopup();
        }
    }

    void EditorHierarchyPanel::UpdateHierarchy()
    {
        // Draw all entities
        std::vector<Entity> hierarchyEntities;

        // Filter root entities
        for (auto entity : SceneManager::Get().GetCurrentScene()->GetAllEntities())
        {
            if (entity.HasComponent<HierarchyComponent>())
            {
                HierarchyComponent& hc = entity.GetComponent<HierarchyComponent>();

                if (!hc.GetParent().IsValid())
                {
                    hierarchyEntities.push_back(entity);
                }
            }
            else
            {
                hierarchyEntities.push_back(entity);
            }
        }

        // Draw from root entities
        for each (auto entity in hierarchyEntities)
        {
            HandleEntityChildren(entity);
        }
    }

    void EditorHierarchyPanel::Init()
    {
    }

    EPanelType EditorHierarchyPanel::GetPanelType()
    {
        return EPanelType::Hierachy;
    }

    void EditorHierarchyPanel::OnEvent(Aloe::EditorEvent& event)
    {
        switch (event.GetType()) 
        {
        case HierarchyEntitySelected:
            m_selectedEntity = reinterpret_cast<HierarchyEntitySelectedEvent*>(&event)->GetEntity();
            break;
        }
    }

    void EditorHierarchyPanel::HandleEntityChildren(Entity entity)
    {
        // TODO: Fix Detachment line
        //HandleDetachmentLine(entity);

        NameComponent& nc = entity.GetComponent<NameComponent>();

        ImGuiTreeNodeFlags treeNodeFlags = 
            ImGuiTreeNodeFlags_OpenOnArrow | 
            ImGuiTreeNodeFlags_DefaultOpen | 
            ImGuiTreeNodeFlags_SpanFullWidth;

        if (m_selectedEntity == entity)
        {
            treeNodeFlags |= ImGuiTreeNodeFlags_Selected;
        }

        if (entity.HasComponent<HierarchyComponent>())
        {
            HierarchyComponent& hc = entity.GetComponent<HierarchyComponent>();
            if (!hc.HasChildren())
            {
                treeNodeFlags |= ImGuiTreeNodeFlags_Leaf;
            }
        }
        else
        {
            treeNodeFlags |= ImGuiTreeNodeFlags_Leaf;
        }

        bool open = ImGui::TreeNodeEx(nc.m_name.c_str(), treeNodeFlags);

        if (ImGui::IsItemClicked())
        {
            HierarchyEntitySelectedEvent editorEvent(entity);
            m_eventMessenger->SendEvent(editorEvent);
        }

        HandleOnEntityDragAndDrop(entity);

        if (open) {
            if (entity.HasComponent<HierarchyComponent>())
            {
                HierarchyComponent& hc = entity.GetComponent<HierarchyComponent>();
                for (auto child : hc.GetChildren()) {
                    HandleEntityChildren(child);
                }
            }

            ImGui::TreePop();
        }
    }

    //void EditorHierarchyPanel::HandleDetachmentLine(Entity entity)
    //{
    //    // Line Button
    //    ImGui::Dummy(ImVec2(ImGui::GetContentRegionAvail().x, 1));

    //    if (ImGui::GetDragDropPayload() != nullptr)
    //    {
    //        if (ImGui::BeginDragDropTarget())
    //        {
    //            ImGuiDragDropFlags targetFlags = 0;

    //            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DragChild", targetFlags)) {
    //                Entity childEntity = SceneManager::Get().GetCurrentScene()->FindEntityByUUID(*(const UUID*)payload->Data);

    //                if (childEntity.IsValid())
    //                {
    //                    HierarchyComponent& lineHC = entity.GetComponent<HierarchyComponent>();
    //                    HierarchyComponent& reattachHC = childEntity.GetComponent<HierarchyComponent>();


    //                    if (lineHC.GetOwner() != reattachHC.GetOwner()) {
    //                        if (entity.HasComponent<HierarchyComponent>())
    //                        {
    //                            HierarchyComponent& lineParentHC = entity.GetComponent<HierarchyComponent>();
    //                            lineParentHC.SetupAttachment(childEntity);
    //                        }
    //                        else {

    //                            if (childEntity.HasComponent<HierarchyComponent>())
    //                            {
    //                                HierarchyComponent& reattachParentHC = childEntity.GetComponent<HierarchyComponent>();
    //                                reattachParentHC.RemoveAttachment(childEntity);
    //                            }
    //                        }
    //                    }

    //                }
    //            }
    //            ImGui::EndDragDropTarget();
    //        }
    //    }
    //}

    void EditorHierarchyPanel::HandleOnEntityDragAndDrop(Entity entity)
    {
        ImGuiDragDropFlags srcFlags = 0;
        srcFlags |= ImGuiDragDropFlags_SourceNoDisableHover;
        srcFlags |= ImGuiDragDropFlags_SourceNoHoldToOpenOthers;
        if (ImGui::BeginDragDropSource(srcFlags)) 
        {
            if (!(srcFlags & ImGuiDragDropFlags_SourceNoPreviewTooltip))
            {
                if (entity.HasComponent<NameComponent>())
                {
                    auto name = entity.GetComponent<NameComponent>();
                    ImGui::Text(name.m_name.c_str());
                }
            }

            ImGui::SetDragDropPayload("DragChild", &entity.GetComponent<IDComponent>().m_UUID, sizeof(UUID));
            ImGui::EndDragDropSource();
        }

        if (ImGui::BeginDragDropTarget()) 
        {
            ImGuiDragDropFlags targetFlags = 0;

            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DragChild", targetFlags)) {
                Entity newChildEntity = SceneManager::Get().GetCurrentScene()->FindEntityByUUID(*(const UUID*)payload->Data);

                if (newChildEntity)
                {
                    HierarchyComponent& targetParentHierarchy = entity.AddComponent<HierarchyComponent>();

                    targetParentHierarchy.SetupAttachment(newChildEntity);
                }
            }

            ImGui::EndDragDropTarget();
        }
    }

}