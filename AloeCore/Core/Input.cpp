#include "Input.h"

#include <GLFW/glfw3.h>

#include <Platform/Input/GamepadInputProvider.h>

namespace Aloe::Input
{
    std::shared_ptr<InputProvider> CreateGamepadInputProvider()
    {
        return std::make_shared<GamepadInputProvider>();
    }

    Key TranslateKey(u16 key)
    {
        return (Key)key;
    }

    Key TranslateMouseButton(u16 key)
    {
        switch (key) 
        {
            case GLFW_MOUSE_BUTTON_LEFT: return MouseLeftClic;
            case GLFW_MOUSE_BUTTON_RIGHT: return MouseRightClic;
            case GLFW_MOUSE_BUTTON_MIDDLE: return MouseMiddleClic;
        }

        return Invalid;
    }

    Key TranslateGamepadButton(u16 key)
    {
        switch (key) 
        {
            case GLFW_GAMEPAD_BUTTON_A: return GamepadFaceDown;
            case GLFW_GAMEPAD_BUTTON_B: return GamepadFaceRight;
            case GLFW_GAMEPAD_BUTTON_X: return GamepadFaceLeft;
            case GLFW_GAMEPAD_BUTTON_Y: return GamepadFaceUp;
            case GLFW_GAMEPAD_BUTTON_LEFT_BUMPER: return GamepadLeftShoulder;
            case GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER: return GamepadRightShoulder;
            //case GLFW_GAMEPAD_BUTTON_BACK: return GamepadFaceDown;
            //case GLFW_GAMEPAD_BUTTON_START: return GamepadFaceDown;
            //case GLFW_GAMEPAD_BUTTON_GUIDE: return GamepadFaceDown;
            case GLFW_GAMEPAD_BUTTON_LEFT_THUMB: return GamepadLeftThumbstick;
            case GLFW_GAMEPAD_BUTTON_RIGHT_THUMB: return GamepadRightThumbstick;
            case GLFW_GAMEPAD_BUTTON_DPAD_UP: return GamepadDPadUp;
            case GLFW_GAMEPAD_BUTTON_DPAD_RIGHT: return GamepadDPadRight;
            case GLFW_GAMEPAD_BUTTON_DPAD_DOWN: return GamepadDPadDown;
            case GLFW_GAMEPAD_BUTTON_DPAD_LEFT: return GamepadDPadLeft;
        }

        return Invalid;
    }
    Key TranslateGamepadAxis(u16 key)
    {
        switch (key)
        {
            case GLFW_GAMEPAD_AXIS_LEFT_X: return GamepadLeftThumbstickX;
            case GLFW_GAMEPAD_AXIS_LEFT_Y: return GamepadLeftThumbstickY;
            case GLFW_GAMEPAD_AXIS_RIGHT_X: return GamepadRightThumbstickX;
            case GLFW_GAMEPAD_AXIS_RIGHT_Y: return GamepadRightThumbstickY;
            case GLFW_GAMEPAD_AXIS_LEFT_TRIGGER: return GamepadLeftTrigger;
            case GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER: return GamepadRightTrigger;
        }

        return Invalid;
    }

    // ALOE-TODO: This is for debugging only, change this to proper key namings.
    const char* GetKeyName(Key key)
    {
        if (key >= FirstKeyboardKey && key <= LastKeyboardKey)
        {
            std::string str;
            str += (char)key;
            return strdup(str.c_str());
        }

        switch (key)
        {
            case MouseLeftClic: return "MouseLeftClic";
            case MouseRightClic: return "MouseRightClic";
            case MouseMiddleClic: return "MouseMiddleClic";
            case MouseScroll: return "MouseScroll";
            case MouseX: return "MouseX";
            case MouseY: return "MouseY";
            case GamepadDPadLeft: return "GamepadDPadLeft";
            case GamepadDPadRight: return "GamepadDPadRight";
            case GamepadDPadUp: return "GamepadDPadUp";
            case GamepadDPadDown: return "GamepadDPadDown";
            case GamepadFaceLeft: return "GamepadFaceLeft";
            case GamepadFaceRight: return "GamepadFaceRight";
            case GamepadFaceUp: return "GamepadFaceUp";
            case GamepadFaceDown: return "GamepadFaceDown";
            case GamepadLeftThumbstickX: return "GamepadLeftThumbstickX";
            case GamepadLeftThumbstickY: return "GamepadLeftThumbstickY";
            case GamepadRightThumbstickX: return "GamepadRightThumbstickX";
            case GamepadRightThumbstickY: return "GamepadRightThumbstickY";
            case GamepadLeftThumbstick: return "GamepadLeftThumbstick";
            case GamepadRightThumbstick: return "GamepadRightThumbstick";
            case GamepadLeftShoulder: return "GamepadLeftShoulder";
            case GamepadLeftTrigger: return "GamepadLeftTrigger";
            case GamepadRightShoulder: return "GamepadRightShoulder";
            case GamepadRightTrigger: return "GamepadRightTrigger";

            default: return "INVALID";
        }
    }
}