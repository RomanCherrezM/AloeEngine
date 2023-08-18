#include "EditorConsolePanel.h"

#include <imgui.h>

namespace Aloe
{
    EditorConsolePanel::EditorConsolePanel(EditorEventMessenger* eventRef)
    {
    }

    void EditorConsolePanel::Init()
    {
    }

    EPanelType EditorConsolePanel::GetPanelType()
    {
        return EPanelType::Console;
    }

    bool EditorConsolePanel::OnPanelUpdate(Entity entity)
    {
        bool open = true;
        if (ImGui::Begin("Console", &open))
        {

        }
        ImGui::End();

        return !open;
    }

    void EditorConsolePanel::OnEvent(Aloe::EditorEvent& event)
    {
    }
}