#include "ScriptSystem.h"

#ifdef _WIN32
#include <windows.h>
#include <libloaderapi.h>
#endif

#include <filesystem>
#include <Core/Script.h>
#include <Core/AloeEngine.h>

namespace Aloe
{
    typedef void (*InitializeFn)();
    typedef void (*InitImGuiContextFn)(void* context);
    typedef Script* (*AddComponentFn)(std::string name, Entity entity);
    typedef bool (*HasComponentFn)(std::string name, Entity entity);
    typedef void (*DrawInterfaceFn)(std::string name, Entity entity);
    typedef void (*GetScriptListFn)(std::vector<std::string>*);

    static HMODULE s_module;

    static InitializeFn s_initFn;
    static InitImGuiContextFn s_initImGuiContextFn;
    static AddComponentFn s_addComponentFn;
    static HasComponentFn s_hasComponentFn;
    static GetScriptListFn s_getScriptListFn;
    static DrawInterfaceFn s_drawInterfaceFn;

    static FARPROC __stdcall TryLoadFunction(HMODULE module, const char* functionName)
    {
        auto func = GetProcAddress(module, functionName);
        if (func == NULL)
        {
            printf("\n Could not load dll function '%s'", functionName);
        }

        return func;
    }

    ScriptSystem::ScriptSystem()
    {

    }

    ScriptSystem::~ScriptSystem()
    {

    }

    void ScriptSystem::Init()
    {
        printf("\n Scripting Loading . . .");

        const std::filesystem::path dllPath = "AloeProject.dll";

        s_module = LoadLibraryA(dllPath.string().c_str());

        if (!s_module)
        {
            printf("\n Couldn't Load Scripting DLL Module");
            return;
        }

        s_initFn = (InitializeFn)TryLoadFunction(s_module, "Initialize");
        s_addComponentFn = (AddComponentFn)TryLoadFunction(s_module, "AddComponentFromString");
        s_getScriptListFn = (GetScriptListFn)TryLoadFunction(s_module, "GetScriptList");
        s_drawInterfaceFn = (DrawInterfaceFn)TryLoadFunction(s_module, "DrawInterfaceFromString");
        s_hasComponentFn = (HasComponentFn)TryLoadFunction(s_module, "HasComponentFromString");
        s_initImGuiContextFn = (InitImGuiContextFn)TryLoadFunction(s_module, "InitImGuiContext");

        // Initialize
        if (s_initFn)
        {
            s_initFn();
        }

        // Get script list
        s_getScriptListFn(&m_scriptTypes);
    }

    void ScriptSystem::Execute()
    {
        static Engine* engine = Engine::Get();
        if (m_isPlatying)
        {
            for each (auto script in m_scripts)
            {
                script->Update(engine->GetDeltaTime());
            }
        }
    }

    void ScriptSystem::StartPlaying()
    {
        if (!m_isPlatying)
        {
            m_isPlatying = true;

            for each (auto script in m_scripts)
            {
                script->Start();
            }
        }
    }

    void ScriptSystem::PausePlaying()
    {

    }

    void ScriptSystem::StopPlaying()
    {
        m_isPlatying = false;

        // TODO: Restore default values
    }

    void ScriptSystem::InitImGuiContext(void* context)
    {
        if (s_initImGuiContextFn)
        {
            s_initImGuiContextFn(context);
        }
    }

    void ScriptSystem::AddComponentFromString(std::string scriptName, Entity entity)
    {
        if (s_addComponentFn)
        {
            Script* script = nullptr;
            script = s_addComponentFn(scriptName, entity);

            if (script)
            {
                m_scripts.push_back(script);

                script->InternalInitialize(entity);
            }
        }
    }

    bool ScriptSystem::HasComponentFromString(std::string scriptName, Entity entity)
    {
        if (s_hasComponentFn)
        {
            return s_hasComponentFn(scriptName, entity);
        }

        return false;
    }

    void ScriptSystem::DrawInterfaceFromString(std::string scriptName, Entity entity)
    {
        if (s_drawInterfaceFn)
        {
            s_drawInterfaceFn(scriptName, entity);
        }
    }

}