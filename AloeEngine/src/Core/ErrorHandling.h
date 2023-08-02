#ifndef ALOE_ERROR_HANDLING_H
#define ALOE_ERROR_HANDLING_H 1

namespace Aloe {

  enum class Error {

    No_Error = 0,

    Window_GLFW_Init,
    Window_GLFW_CreateWindow,
    Window_GLFW_Glad_load,

  };

}

#endif