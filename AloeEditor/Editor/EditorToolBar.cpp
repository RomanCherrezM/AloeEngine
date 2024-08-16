#include "EditorToolBar.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <filesystem>

#include <Core/AloeEngine.h>

#include <Scene/SceneManager.h>
#include <Application/Systems/ECSManager.h>

namespace Aloe
{
    EditorToolBar::EditorToolBar(EditorEventMessenger* eventRef)
    {
        std::filesystem::path path = "../../AloeEditor/Assets/Viewport";

        m_eventMessenger = eventRef;

        m_playIcon = Texture::Create((path / "play.png").string());
        m_pauseIcon = Texture::Create((path / "pause.png").string());
        m_stopIcon = Texture::Create((path / "stop.png").string());

        m_playIcon->Load();
        m_pauseIcon->Load();
        m_stopIcon->Load();
    }

    void EditorToolBar::Init()
    {
    }

    EPanelType EditorToolBar::GetPanelType()
    {
        return EPanelType::ToolBar;
    }

    bool EditorToolBar::OnPanelUpdate(Entity entity)
    {
        static SceneManager& sceneManager = SceneManager::Get();

        bool open = true;

        // Toolbar
        auto style = ImGui::GetStyle();

        float iconSize = 16;
        int toolbarItems = 2;

        ImVec2 toolbarPos = ImVec2{ ImGui::GetWindowPos().x + ImGui::GetCursorPos().x + (ImGui::GetWindowSize().x / 2.0f) - ((iconSize * toolbarItems) / 2.0f) ,
                                    ImGui::GetWindowPos().y + ImGui::GetCursorPos().y + 20.0f};

        ImGui::SetNextWindowPos(toolbarPos);
        ImGui::SetNextWindowBgAlpha(0.75f);

        ImGuiWindowFlags toolbarFlags = ImGuiWindowFlags_NoDecoration |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoScrollWithMouse |
            ImGuiWindowFlags_NoSavedSettings |
            ImGuiWindowFlags_NoBringToFrontOnFocus;

        if (ImGui::Begin("##ToolBar", &open, toolbarFlags))
        {
            ImGui::BringWindowToDisplayFront(ImGui::GetCurrentWindow());

            ImTextureID playIcon = (ImTextureID)(sceneManager.IsPlaying() ? m_stopIcon->GetRendererID() : m_playIcon->GetRendererID());

            if (ImGui::ImageButton(playIcon, ImVec2(iconSize, iconSize), ImVec2(0, 1), ImVec2(1, 0)))
            {
                if (sceneManager.IsPlaying())
                {
                    sceneManager.StopPlaying();
                    // TODO: Move this to somewhere else
                    Engine::Get()->GetApplicationSystems()->GetECSManager()->GetPhysics2DSystem()->OnRuntimeStop();
                    
                }
                else
                {
                    sceneManager.StartPlaying();
                    // TODO: Move this to somewhere else
                    Engine::Get()->GetApplicationSystems()->GetECSManager()->GetPhysics2DSystem()->OnRuntimeStart();
                }
            }

            ImGui::SameLine();

            if (ImGui::ImageButton((ImTextureID)m_pauseIcon->GetRendererID(), ImVec2(iconSize, iconSize), ImVec2(0, 1), ImVec2(1, 0)))
            {
                sceneManager.PausePlaying();
            }
        }
        ImGui::End();

        return false;
    }

    void EditorToolBar::OnEvent(Aloe::EditorEvent& event)
    {
    }

}