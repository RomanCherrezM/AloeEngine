// TODO: This File should be generated at build time and not edited by hand

#include "init.h"

#include "generated/TestScript_generated.h"

#include <Core/AloeEngine.h>
#include <Core/Script.h>

#include <string>

namespace Aloe
{
    typedef Script* (*AddComponentFn)(Entity entity);
    typedef void (*DrawInterfaceFn)(Entity entity);
    typedef bool (*HasComponentFn)(Entity entity);

    std::unordered_map<std::string, AddComponentFn> s_addComponentFnMap =
    {
        { "TestScript", ReflectTestScript::AddComponent }
    };

    std::unordered_map<std::string, DrawInterfaceFn> s_drawInterfaceFnMap =
    {
        { "TestScript", ReflectTestScript::DrawInterface }
    };

    std::unordered_map<std::string, HasComponentFn> s_hasComponentFnMap =
    {
        { "TestScript", ReflectTestScript::HasComponent }
    };

    std::vector<std::string> s_scriptsList =
    {
        {"TestScript"},
    };

    void Initialize()
    {
        ReflectTestScript::Initialize();
    }

    void GetScriptList(std::vector<std::string>* out)
    {
        *out = s_scriptsList;
    }

    void InitImGuiContext(void* context)
    {
        ImGui::SetCurrentContext((ImGuiContext*)context);
    }

    void DrawInterfaceFromString(std::string scriptName, Entity entity)
    {
        if (s_drawInterfaceFnMap.find(scriptName) == s_drawInterfaceFnMap.end())
        {
            printf("\n Script Module Error (DrawInterface = %s): Component doesn't exist", scriptName.c_str());
        }
        return s_drawInterfaceFnMap[scriptName](entity);
    }

    Script* AddComponentFromString(std::string scriptName, Entity entity)
    {   
        if (s_addComponentFnMap.find(scriptName) == s_addComponentFnMap.end())
        {
            printf("\n Script Module Error (AddComponent = %s): Component doesn't exist", scriptName.c_str());
        }
        return s_addComponentFnMap[scriptName](entity);
    }

    bool HasComponentFromString(std::string scriptName, Entity entity)
    {
        if (s_hasComponentFnMap.find(scriptName) == s_hasComponentFnMap.end())
        {
            printf("\n Script Module Error (HasComponent = %s): Component doesn't exist", scriptName.c_str());
        }
        return s_hasComponentFnMap[scriptName](entity);
    }
}