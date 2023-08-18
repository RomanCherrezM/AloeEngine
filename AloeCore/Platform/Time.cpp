#include "Time.h"

#include <GLFW/glfw3.h>

namespace Aloe
{
    float Time::GetTime()
    {
        return glfwGetTime();
    }

}