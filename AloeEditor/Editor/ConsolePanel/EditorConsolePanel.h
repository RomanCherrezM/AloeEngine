#pragma once

#include <Editor/EditorPanelBase.h>

namespace Aloe {

    class EditorConsolePanel : public EditorPanelBase
    {
    public:
        EditorConsolePanel(EditorEventMessenger* eventRef);

        // EditorPanelBase
        virtual void Init() override;
        virtual EPanelType GetPanelType() override;
        virtual bool OnPanelUpdate(Entity entity) override;

        // IEditorEventListener
        virtual void OnEvent(Aloe::EditorEvent& event) override;
    private:
    };
}