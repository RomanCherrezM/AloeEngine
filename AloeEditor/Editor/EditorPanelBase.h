#pragma once

#include <Editor/EditorEventMessenger.h>

#include <Scene/Entity.h>

namespace Aloe
{
    enum EPanelType
    {
        Viewport,
        Hierachy,
        Inspector,
        ContentBrowser,
        Console,
        ToolBar,

    };

    class EditorPanelBase : public IEditorEventListener
    {
    public:
        virtual void Init() = 0;
        virtual EPanelType GetPanelType() = 0;
        virtual bool OnPanelUpdate(Entity entity) = 0; // TODO: Change Entity to some payload   
    
        // Editor Main Messenger reference to send events to be propagated
        EditorEventMessenger* m_eventMessenger;
    };
}