#include "EditorViewportPanel.h"

#include <imgui.h>

#include <Core/AloeEngine.h>

#include <ECS/Components/CameraComponent.h>

constexpr float c_resolution16_9 = 16.0f / 9.0f;

namespace Aloe 
{
    EditorViewportPanel::EditorViewportPanel(EditorEventMessenger* eventRef) :
        m_toolBar(eventRef)
    {

    }

    void EditorViewportPanel::Init()
    {
        m_toolBar.Init();
    }

    EPanelType EditorViewportPanel::GetPanelType()
    {
        return EPanelType::Viewport;
    }

    bool EditorViewportPanel::OnPanelUpdate(Entity entity)
    {
        bool open = true;
        if (ImGui::Begin("Viewport", &open))
        {
            m_toolBar.OnPanelUpdate(entity);

            CameraComponent* cameraComponent = Engine::Get()->GetMainCamera();
            if (cameraComponent != nullptr && cameraComponent->m_renderTarget != nullptr) {

                uint32_t framebufferID = cameraComponent->m_renderTarget->GetColorAttachmentRendererID();

                ImVec2 availableRegion = ImGui::GetContentRegionAvail();
                float resolution = availableRegion.x / availableRegion.y;

                ImVec2 imageRegion = availableRegion;
                if (resolution >= (16.0f / 9.0f)) // The viewport's width is to high
                {
                    // Use Y coordinate to get X
                    imageRegion.x = imageRegion.y * (c_resolution16_9);

                }
                else // The viewport's height is to high
                {
                    // Use X coordinate to get the Y
                    imageRegion.y = imageRegion.x / (c_resolution16_9);
                }

                ImGui::SetCursorPos(ImGui::GetCursorPos() + (availableRegion - imageRegion) * 0.5f);
                ImGui::Image((void*)framebufferID, imageRegion, ImVec2(0, 1), ImVec2(1, 0));
            }
        }
        ImGui::End();

        return !open;
    }

    void EditorViewportPanel::OnEvent(Aloe::EditorEvent& event)
    {
    }
}