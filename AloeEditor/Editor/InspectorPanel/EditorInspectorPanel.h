#pragma once

#include <Editor/EditorPanelBase.h>

namespace Aloe {

    class EditorInspectorPanel : public EditorPanelBase
    {
    public:
        EditorInspectorPanel(EditorEventMessenger* eventRef);

        // EditorPanelBase
        virtual void Init() override;
        virtual EPanelType GetPanelType() override;
        virtual bool OnPanelUpdate(Entity entity) override;

        // IEditorEventListener
        virtual void OnEvent(Aloe::EditorEvent& event) override;

        void AddComponentPopUp();

    private:

        Entity m_selectedEntity;

        class ScriptSystem* m_scriptSystem;
    };
}