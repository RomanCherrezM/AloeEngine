#pragma once

#include <Core/ErrorHandling.h>

#include <Application/Systems/EventMessenger.h>
#include <Events/Event.h>

#include <Core/Input.h>

#include <string>

struct GLFWwindow;

namespace Aloe {

    class WindowHandler {
    public:

        WindowHandler();
        ~WindowHandler();

        Error Create(uint32_t w, uint32_t h, std::string name, std::string version);
        void Clear();
        void PollEvents();
        void SwapBuffers();

        void SetEventMessenger(EventMessenger* eventMessenger);

        void EnableVSync(bool enabled);

        void UpdateFPSCount();
        bool ShouldClose();

        GLFWwindow* GetWindowInternal();
    private:
        GLFWwindow* m_windowHandler;

        // ALOE-TODO: When the keyboard & mouse input change to be in a InputProvider
        //            this class wont be needed anymore

        struct WindowData
        {
            std::string m_titleName;
            std::string m_titleVersion;

            unsigned int m_width;
            unsigned int m_height;

            bool m_vsync;

            EventMessenger* m_eventMessenger;
        };

        WindowData m_data;

        std::shared_ptr<Input::InputProvider> m_gamepadInputProvider;

        uint32_t frameCount;
    };

}