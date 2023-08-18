#include "Window.h"
#include <Core/Window.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Core/Input.h>
#include <Events/InputEvents.h>

#include <fstream>

namespace Aloe {

    WindowHandler::WindowHandler()
    {
        m_windowHandler = NULL;

        m_data.m_width = 0;
        m_data.m_height = 0;

        frameCount = 0;
    }

    WindowHandler::~WindowHandler()
    {

    }

    Error WindowHandler::Create(uint32_t w, uint32_t h, std::string name, std::string version)
    {
        if (!glfwInit())
        {
            return Error::Window_GLFW_Init;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        m_data.m_titleName = name;
        m_data.m_titleVersion = version;
        m_data.m_width = w;
        m_data.m_height = h;

        m_windowHandler = glfwCreateWindow(m_data.m_width, m_data.m_height, (m_data.m_titleName + " " + m_data.m_titleVersion).c_str(), NULL, NULL);
        if (!m_windowHandler)
        {
            glfwTerminate();
            return Error::Window_GLFW_CreateWindow;
        }

        glfwMakeContextCurrent(m_windowHandler);

        glfwSetWindowUserPointer(m_windowHandler, &m_data);

        // Setup GLFW callbacks

        m_gamepadInputProvider = Aloe::Input::CreateGamepadInputProvider();

        glfwSetKeyCallback(m_windowHandler, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    KeyPressEvent event((Key)key, 0);
                    data.m_eventMessenger->OnEvent(event);
                    break;
                }

                case GLFW_RELEASE:
                {
                    KeyReleaseEvent event((Key)key);
                    data.m_eventMessenger->OnEvent(event);
                    break;
                }
            }
        });

        glfwSetCursorPosCallback(m_windowHandler, [](GLFWwindow* window, double x, double y) 
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMoveEvent event((float)x, (float)y);
            data.m_eventMessenger->OnEvent(event);

        });

        glfwSetMouseButtonCallback(m_windowHandler, [](GLFWwindow* window, int button, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
            case GLFW_PRESS:
            {
                MouseButtonPressEvent event(TranslateMouseButton(button));
                data.m_eventMessenger->OnEvent(event);
                break;
            }
            case GLFW_RELEASE:
            {
                MouseButtonReleaseEvent event(TranslateMouseButton(button));
                data.m_eventMessenger->OnEvent(event);
                break;
            }
            }
        });

        glfwSetScrollCallback(m_windowHandler, [](GLFWwindow* window, double xOffset, double yOffset)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrollEvent event((float)xOffset, (float)yOffset);
            data.m_eventMessenger->OnEvent(event);
        });

        glfwSetCursorPosCallback(m_windowHandler, [](GLFWwindow* window, double xPos, double yPos)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMoveEvent event((float)xPos, (float)yPos);
            data.m_eventMessenger->OnEvent(event);
        });

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            return Error::Window_GLFW_Glad_load;
        }

        return Error::No_Error;
    }

    void WindowHandler::UpdateFPSCount()
    {
        // Measure speed
        static double lastTime = 0.0;
        double currentTime = glfwGetTime();
        double delta = currentTime - lastTime;
        frameCount++;
        if (delta >= 1.0) { // If last cout was more than 1 sec ago
            double fps = double(frameCount) / delta;

            char title[256];
            title[255] = '\0';

            snprintf(title, 255,
                "%s %s - [FPS: %3.2f]",
                m_data.m_titleName.c_str(), m_data.m_titleVersion.c_str(), fps);

            glfwSetWindowTitle(m_windowHandler, title);

            frameCount = 0;
            lastTime = currentTime;
        }
    }


    void WindowHandler::Clear()
    {
        // Does nothing, clear now its done in the renderer
    }

    void WindowHandler::PollEvents()
    {
        glfwPollEvents();

        m_gamepadInputProvider->PollInput(m_data.m_eventMessenger);
        //ALOE-TODO: Add Keybord and Mouse polling instead of callbacks
    }

    void WindowHandler::SwapBuffers()
    {
        glfwSwapBuffers(m_windowHandler);
    }

    void WindowHandler::SetEventMessenger(EventMessenger* eventMessenger)
    {
        m_data.m_eventMessenger = eventMessenger;
    }

    void WindowHandler::EnableVSync(bool enabled)
    {
        if (enabled)
        {
            glfwSwapInterval(1);
        }
        else
        {
            glfwSwapInterval(0);
        }
    }

    bool WindowHandler::ShouldClose() {
        return glfwWindowShouldClose(m_windowHandler);
    }

    GLFWwindow* WindowHandler::GetWindowInternal()
    {
        return m_windowHandler;
    }

}