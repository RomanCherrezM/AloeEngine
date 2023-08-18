#pragma once

#include <Scene/Scene.h>

#include <ECS/Systems/RenderSystem.h>
#include <ECS/Systems/InputSystem.h>
#include <ECS/Systems/ScriptSystem.h>

namespace Aloe {

    class ECSManager {

    public:
        ECSManager();
       
        void Init();

        void ExecutePreUpdateSystems();
        void ExecutePostUpdateSystems();

        // System Getters
        InputSystem* GetInputSystem() { return m_inputSystem.get(); }
        RenderMeshSystem* GetRenderMeshSystem() { return m_renderMeshSystem.get(); }
        RenderSpriteSystem* GetSpriteRenderSystem() { return m_renderSpriteSystem.get(); }
        ScriptSystem* GetScriptSystem() { return m_scriptSystem.get(); }

    private:
        // Current running ECS
        // Notes: To load a new Scene just call SceneManager Load which accpets some type of file
        // containing the scene data, reset the current ECS and load the new one. Also for future loading
        // this can be loaded into a different ECS and switch to the current one when ready.

        std::shared_ptr<Scene> m_scene;
        //std::shared_ptr<ECS> m_ecs;

        // ECS Systems
        std::shared_ptr<InputSystem> m_inputSystem;
        // TODO: This is not an ECS system as it doesn't have a signature, move this somewhere else
        std::shared_ptr<ScriptSystem> m_scriptSystem; 
        std::shared_ptr<RenderMeshSystem> m_renderMeshSystem;
        std::shared_ptr<RenderCameraSystem> m_renderCameraSystem;
        std::shared_ptr<RenderSpriteSystem> m_renderSpriteSystem;

    };

}