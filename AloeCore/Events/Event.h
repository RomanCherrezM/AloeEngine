#pragma once

#include <functional>

namespace Aloe
{
    enum EventType
    {
        None = 0,

        WindowClose,
        WindowResize,
        WindowFocus,
        WindowLostFocus,
        WindowMoved,

        KeyPress,
        KeyRelease,

        MouseButtonPress,
        MouseButtonRelease,
        MouseMove,
        MouseScroll,

        GamepadButtonPress,
        GamepadButtonRelease,
        GamepadAxis,
    };

#define ALOE_EVENT_CLASS(type) static EventType GetStaticType() { return EventType::type; }\

    class Event
    {
    public:
        virtual ~Event() = default;

        bool m_handled = false;

        virtual EventType GetType() const = 0;

    };
}