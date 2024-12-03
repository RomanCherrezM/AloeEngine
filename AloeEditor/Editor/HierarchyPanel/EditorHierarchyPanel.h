#pragma once

#include <Editor/EditorPanelBase.h>

#include <Scene/Scene.h>

namespace Aloe {

    class EditorHierarchyPanel : public EditorPanelBase
    {
    public:
        EditorHierarchyPanel(EditorEventMessenger* eventRef);

        void UpdateToolsBar();
        void UpdateHierarchy();

        void HandleEntityChildren(Entity entity);

        void HandleOnEntityDragAndDrop(Entity entity);
        //void HandleDetachmentLine(Entity entity);

        // EditorPanelBase
        virtual void Init() override;
        virtual EPanelType GetPanelType() override;
        virtual bool OnPanelUpdate(Entity entity) override;

        // IEditorEventListener
        virtual void OnEvent(Aloe::EditorEvent& event) override;

    private:
        Entity m_selectedEntity;
    };
}