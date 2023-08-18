#include "GamepadInputProvider.h"

#include<Events/InputEvents.h>

// ALOE-TODO: Create a new event for Gamepad events

namespace Aloe::Input {

    GamepadInputProvider::GamepadInputProvider()
    {
    }

    GamepadInputProvider::~GamepadInputProvider()
    {
    }

    void GamepadInputProvider::ProcessButton(IEventListener* eventMessenger, const GLFWgamepadstate& previousState,
        const GLFWgamepadstate& currentState, u16 key)
    {

        u16 inputCurrent = currentState.buttons[key];
        u16 inputPrevious = previousState.buttons[key];

        switch (inputCurrent)
        {
            case GLFW_PRESS:
            {
                if (inputPrevious == GLFW_RELEASE)
                {
                    GamepadPressEvent event(TranslateGamepadButton(key), 0);
                    eventMessenger->OnEvent(event);
                }
                break;
            }

            case GLFW_RELEASE:
            {
                if (inputPrevious == GLFW_PRESS) 
                {
                    GamepadReleaseEvent event(TranslateGamepadButton(key));
                    eventMessenger->OnEvent(event);
                }
                break;
            }
        }
    }

    void GamepadInputProvider::ProcessThumbstickAxis(IEventListener* eventMessenger,
        const GLFWgamepadstate& currentState, u16 key)
    {
        float valueCurrent = currentState.axes[key];

        if (valueCurrent < -0.25f || valueCurrent > 0.25f) // Calculate deadzones here
        {
            GamepadAxisEvent event(TranslateGamepadAxis(key), valueCurrent);
            eventMessenger->OnEvent(event);
        }
    }

    void GamepadInputProvider::ProcessTriggerAxis(IEventListener* eventMessenger,
        const GLFWgamepadstate& currentState, u16 key)
    {
        float valueCurrent = currentState.axes[key];

        if (valueCurrent > -0.90f) // Calculate deadzones here
        {
            GamepadAxisEvent event(TranslateGamepadAxis(key), valueCurrent);
            eventMessenger->OnEvent(event);
        }
    }

    void GamepadInputProvider::PollInput(IEventListener* messenger)
    {
        static GLFWgamepadstate previousState;

        GLFWgamepadstate currentState;

        if (glfwGetGamepadState(GLFW_JOYSTICK_1, &currentState))
        {
            for (int i = 0; i <= GLFW_GAMEPAD_BUTTON_LAST; i++)
            {
                ProcessButton(messenger, previousState, currentState, i);
            }

            for (int i = 0; i <= GLFW_GAMEPAD_AXIS_RIGHT_Y; i++)
            {
                ProcessThumbstickAxis(messenger, currentState, i);
            }

            ProcessTriggerAxis(messenger, currentState, GLFW_GAMEPAD_AXIS_LEFT_TRIGGER);
            ProcessTriggerAxis(messenger, currentState, GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER);
        }

        previousState = currentState;
    }

}