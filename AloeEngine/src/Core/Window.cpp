#include <Core/Window.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <fstream>

WindowHandler::WindowHandler()
{
    windowHandler = NULL;

    width = 0;
    height = 0;

    frameCount = 0;
}

WindowHandler::~WindowHandler()
{

}

Aloe::Error WindowHandler::Create(uint32_t w, uint32_t h, std::string name, std::string version)
{
    if (!glfwInit()) 
    {
        return Aloe::Error::Window_GLFW_Init;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    titleName = name;
    titleVersion = version;
    width = w;
    height = h;

    windowHandler = glfwCreateWindow(width, height, (titleName + " " + titleVersion).c_str(), NULL, NULL);
    if (!windowHandler)
    {
        glfwTerminate();
        return Aloe::Error::Window_GLFW_CreateWindow;
    }

    glfwMakeContextCurrent(windowHandler);
    glfwSwapInterval(0);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return Aloe::Error::Window_GLFW_Glad_load;
    }

    return Aloe::Error::No_Error;
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
        titleName.c_str(), titleVersion.c_str(), fps);

        glfwSetWindowTitle(windowHandler, title);

        frameCount = 0;
        lastTime = currentTime;
    }
}


void WindowHandler::Update()
{
    //Temporal
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwPollEvents();
    glfwSwapBuffers(windowHandler);
}

bool WindowHandler::ShouldClose(){
    return glfwWindowShouldClose(windowHandler);
}
