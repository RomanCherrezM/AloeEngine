#pragma once

#include <Editor/EditorPanelBase.h>

namespace Aloe
{
    class Texture;

    class EditorToolBar : public EditorPanelBase
    {
    public:
        EditorToolBar(EditorEventMessenger* eventRef);

        // EditorPanelBase
        virtual void Init() override;
        virtual EPanelType GetPanelType() override;
        virtual bool OnPanelUpdate(Entity entity) override;

        // IEditorEventListener
        virtual void OnEvent(Aloe::EditorEvent& event) override;

    private:

        // Icon Textures
        std::shared_ptr<Texture> m_playIcon;
        std::shared_ptr<Texture> m_pauseIcon;
        std::shared_ptr<Texture> m_stopIcon;

        class ScriptSystem* m_scriptSystem = nullptr;
    };
}