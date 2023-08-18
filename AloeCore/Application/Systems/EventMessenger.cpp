#include "EventMessenger.h"

#define MAX_EVENT_LISTENERS 32

namespace Aloe
{
    EventMessenger::EventMessenger()
    {
        m_listeners.reserve(32);
    }

    EventMessenger::~EventMessenger()
    {
        m_listeners.clear();
    }

    void EventMessenger::AddListener(IEventListener* listener)
    {
        //ALOE-TODO: Check nullptr with own assert

        m_listeners.push_back(listener);
    }

    void EventMessenger::OnEvent(Aloe::Event& event)
    {
        for each (IEventListener* listener in m_listeners)
        {
            listener->OnEvent(event);
        }
    }
}