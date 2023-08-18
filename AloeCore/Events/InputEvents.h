#pragma once

#include "Event.h"

#include <Core/Input.h>

namespace Aloe
{

using namespace Input;

    class KeyEvent : public Event
    {
    public:

        Key GetKey() const { return m_key; }

    protected:
        KeyEvent(const Key key)
            : m_key(key) {}

        Key m_key;
    };

    class KeyPressEvent : public KeyEvent
    {
    public:

        ALOE_EVENT_CLASS(KeyPress);

        KeyPressEvent(const Input::Key key, bool isRepeat = false)
            : KeyEvent(key), m_isRepeat(isRepeat) {}

        EventType GetType() const override { return EventType::KeyPress;}

    private:

        bool m_isRepeat;

    };

    class KeyReleaseEvent : public KeyEvent
    {
    public:

        ALOE_EVENT_CLASS(KeyRelease);

        KeyReleaseEvent(const Input::Key key)
            : KeyEvent(key) {}

        EventType GetType() const override { return EventType::KeyRelease; }
    };

    class MouseButtonPressEvent : public KeyEvent
    {
    public:

        ALOE_EVENT_CLASS(MouseButtonPress);

        MouseButtonPressEvent(const Input::Key key, bool isRepeat = false)
            : KeyEvent(key), m_isRepeat(isRepeat) {}

        EventType GetType() const override { return EventType::MouseButtonPress; }

    private:

        bool m_isRepeat;
    };

    class MouseButtonReleaseEvent : public KeyEvent
    {
    public:

        ALOE_EVENT_CLASS(MouseButtonRelease);

        MouseButtonReleaseEvent(const Input::Key key)
            : KeyEvent(key) {}

        EventType GetType() const override { return EventType::MouseButtonRelease; }
    };

    class MouseMoveEvent : public Event
    {
    public:

        ALOE_EVENT_CLASS(MouseMove);

        MouseMoveEvent(float x, float y)
            : m_x(x), m_y(y) {}

        EventType GetType() const override { return EventType::MouseMove; }

        float m_x;
        float m_y;
    };

    class MouseScrollEvent : public Event
    {
    public:

        ALOE_EVENT_CLASS(MouseScroll);

        MouseScrollEvent(float x, float y)
            : m_x(x), m_y(y) {}

        EventType GetType() const override { return EventType::MouseScroll; }

        float m_x;
        float m_y;
    };

    class GamepadPressEvent : public KeyEvent
    {
    public:

        ALOE_EVENT_CLASS(GamepadButtonPress);

        GamepadPressEvent(const Input::Key key, bool isRepeat = false)
            : KeyEvent(key), m_isRepeat(isRepeat) {}

        EventType GetType() const override { return EventType::GamepadButtonPress; }

    private:

        bool m_isRepeat;

    };

    class GamepadReleaseEvent : public KeyEvent
    {
    public:

        ALOE_EVENT_CLASS(GamepadButtonRelease);

        GamepadReleaseEvent(const Input::Key key)
            : KeyEvent(key) {}

        EventType GetType() const override { return EventType::GamepadButtonRelease; }
    };

    class GamepadAxisEvent : public KeyEvent  // KeyEvent because we need to know what axis it is
    {
    public:

        ALOE_EVENT_CLASS(GamepadAxis);

        GamepadAxisEvent(const Input::Key key, float value)
            : KeyEvent(key), m_value(value){}

        EventType GetType() const override { return EventType::GamepadAxis; }

        float m_value;
    };

}
