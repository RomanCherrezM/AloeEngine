#pragma once

#include <GLFW/glfw3.h>

#include <Core/PlatformTypes.h>

#include <Core/InputProviderBase.h>

namespace Aloe::Input {

    class GamepadInputProvider : public InputProvider
    {
    public:
        GamepadInputProvider();
        virtual ~GamepadInputProvider();

        void PollInput(IEventListener* eventMessenger) override;

    private:

        void ProcessButton(IEventListener* eventMessenger, const GLFWgamepadstate& previousState, 
            const GLFWgamepadstate& currentState, u16 key);
        void ProcessThumbstickAxis(IEventListener* eventMessenger, const GLFWgamepadstate& currentState, u16 key);
        void ProcessTriggerAxis(IEventListener* eventMessenger, const GLFWgamepadstate& currentState, u16 key);

    };

}