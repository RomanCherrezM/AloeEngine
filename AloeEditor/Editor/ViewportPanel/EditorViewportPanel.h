#pragma once

#include <Editor/EditorPanelBase.h>

#include <Editor/EditorToolBar.h>

namespace Aloe 
{
    class EditorViewportPanel : public EditorPanelBase
    {
    public:
        EditorViewportPanel(EditorEventMessenger* eventRef);

        // EditorPanelBase
        virtual void Init() override;
        virtual EPanelType GetPanelType() override;
        virtual bool OnPanelUpdate(Entity entity) override;

        // IEditorEventListener
        virtual void OnEvent(Aloe::EditorEvent& event) override;

    private:

        EditorToolBar m_toolBar;
    };
}