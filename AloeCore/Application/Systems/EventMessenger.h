#pragma once

#include <Events/Event.h>

namespace Aloe
{
    class IEventListener {
    public:

        virtual void OnEvent(Aloe::Event& event) = 0;

    };

    class EventMessenger : public IEventListener
    {
    public:
        EventMessenger();
        ~EventMessenger();

        void AddListener(IEventListener* listener);

        // ALOE-TODO: Think about storing the events to then execute them with ProcessEvents

        void OnEvent(Aloe::Event& event);

    private:

        std::vector<IEventListener*> m_listeners;

    };
}