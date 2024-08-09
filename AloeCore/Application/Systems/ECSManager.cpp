#include "ECSManager.h"

#include <ECS/Components/Components.h>

#include <Core/AloeEngine.h>

namespace Aloe {

    ECSManager::ECSManager()
    {
    }

    void ECSManager::Init()
    {
        m_scene = std::make_shared<Scene>();

        m_inputSystem = std::make_shared<InputSystem>();
        m_scriptSystem = std::make_shared<ScriptSystem>();
        m_renderMeshSystem = std::make_shared<RenderMeshSystem>();
        m_renderSpriteSystem = std::make_shared<RenderSpriteSystem>();
        m_renderCameraSystem = std::make_shared<RenderCameraSystem>();
        m_physics2DSystem = std::make_shared<Physics2DSystem>();

        m_inputSystem->Init();
        m_scriptSystem->Init();
        m_renderMeshSystem->Init();
        m_renderSpriteSystem->Init();
        m_renderCameraSystem->Init();
        m_physics2DSystem->Init();

        m_renderCameraSystem->m_meshRenderSystem = m_renderMeshSystem;
        m_renderCameraSystem->m_spriteRenderSystem = m_renderSpriteSystem;
    }

    void ECSManager::ExecutePreUpdateSystems()
    {
        m_inputSystem->Execute();

        m_scriptSystem->Execute();
    }

    void ECSManager::ExecutePostUpdateSystems()
    {
        m_physics2DSystem->Execute();

        m_renderCameraSystem->Execute();
    }
}