#pragma once

#include "Core/PlatformTypes.h"

#ifdef _WIN32
    #define ALOE_SCRIPT __declspec(dllexport)
#else 
    #define ALOE_SCRIPT
#endif

#ifdef _WIN32
#define C_EXTERN extern "C"
#else 
#define C_EXTERN
#endif