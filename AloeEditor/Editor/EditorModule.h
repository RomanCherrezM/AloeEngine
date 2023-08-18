#pragma once

#include <Application/ModuleBase.h>

#include <ECS/Components/Components.h>
#include <Core/Window.h>

#include <Editor/EditorPanelBase.h>
#include <Editor/EditorEventMessenger.h>

namespace Aloe {

    class EditorModule : public ModuleBase , EditorEventMessenger {
    public:

        EditorModule(WindowHandler* window);

        void Start() override;
        void Update(float deltaTime) override;
        void End() override;

    private:

        void StartFrame();
        void EndFrame();

        void SetupDockspace();
        void MainMenuBarUpdate();

        void OpenPanel(EPanelType type);
        void ClosePanel(EPanelType type);
        bool PanelExists(EPanelType type, int* foundIndex = nullptr);

        std::vector<EditorPanelBase*> m_panels;

        WindowHandler* m_window;

        Entity m_selectedEntity;

        std::shared_ptr<Scene> m_scene;

        // TODO: How do we handle input on the editor?
    };

}