#include "EditorEventMessenger.h"

#define MAX_EDITOR_EVENT_LISTENERS 32 // TODO: Change this to the maximum amount of Panels

namespace Aloe
{
    EditorEventMessenger::EditorEventMessenger()
    {
        m_listeners.reserve(32);
    }

    EditorEventMessenger::~EditorEventMessenger()
    {
        m_listeners.clear();
    }

    void EditorEventMessenger::AddListener(IEditorEventListener* listener)
    {
        //ALOE-TODO: Check nullptr with own assert

        m_listeners.push_back(listener);
    }

    void EditorEventMessenger::RemoveListener(IEditorEventListener* listener)
    {
        std::vector<IEditorEventListener*>::iterator position = std::find(m_listeners.begin(), m_listeners.end(), listener);
        if (position != m_listeners.end())
        {
            m_listeners.erase(position);
        }
    }

    void EditorEventMessenger::OnEvent(Aloe::EditorEvent& event)
    {
        for each (IEditorEventListener * listener in m_listeners)
        {
            listener->OnEvent(event);
        }
    }
}