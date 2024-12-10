#pragma once

#include <Core/Core.h>

#include <Scene/Entity.h>

#include <vector>
#include <string>

namespace Aloe
{
    C_EXTERN ALOE_SCRIPT void Initialize();

    C_EXTERN ALOE_SCRIPT void GetScriptList(std::vector<std::string>* out);

    C_EXTERN ALOE_SCRIPT void InitImGuiContext(void* context);

    C_EXTERN ALOE_SCRIPT void DrawInterfaceFromString(std::string scriptName, Entity entity);

    C_EXTERN ALOE_SCRIPT class Script* AddComponentFromString(std::string scriptName, Entity entity);

    C_EXTERN ALOE_SCRIPT bool HasComponentFromString(std::string scriptName, Entity entity);

}