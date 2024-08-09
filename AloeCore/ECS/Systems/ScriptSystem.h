#pragma once

#include <vector>
#include <string>

#include <ECS/Systems/System.h>
#include <Scene/Entity.h>

namespace Aloe {

    class Script;

    class ScriptSystem : public System {
    public:

        ScriptSystem();
        ~ScriptSystem();

        void Init() override;
        void Execute() override;
    
        void OnRuntimeStart() override {}
        void OnRuntimeStop() override {}

        void StartPlaying();
        void PausePlaying();
        void StopPlaying();

        void InitImGuiContext(void* context);

        void AddComponentFromString(std::string scriptName, Entity entity);
        bool HasComponentFromString(std::string scriptName, Entity entity);
        void DrawInterfaceFromString(std::string scriptName, Entity entity);

        std::vector<std::string> GetScriptList() { return m_scriptTypes; };

        bool IsPlaying() { return m_isPlatying; }

    private:

        bool m_isPlatying = false;

        std::vector<std::string> m_scriptTypes;
        std::vector<Script*> m_scripts;
    };
}