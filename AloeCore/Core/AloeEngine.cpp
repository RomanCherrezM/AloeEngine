#include <Core/AloeEngine.h>

#include <Render/Renderer.h>
#include <Core/AssetLibrary.h>

#include <Application/Systems/ECSManager.h>

#include <Core/Log.h>

namespace Aloe {

    Engine::Engine()
    {
        m_appSystems = nullptr;
    }

    Engine::~Engine()
    {

    }

    Engine* Engine::Get()
    {
        static Engine* engine = new Engine();

        return engine;
    }

    void Engine::Init()
    {
        Log::Init();

        m_appSystems = std::make_unique<ApplicationSystems>();
        
        m_appSystems->InitSystems();

        ALOE_TRACE("Trace test");
        ALOE_INFO("Info test");
        ALOE_WARN("Warn test");
        ALOE_ERROR("Error test");
        ALOE_CRITICAL("Critical test");

        ALOE_ASSERT(true, "Assert Passed");
    }

    void Engine::SetMainCamera(CameraComponent* mainCamera)
    {
        // ALOE-TODO: Assert camera for nullptr
        m_mainCamera = mainCamera;
    }

    CameraComponent* Engine::GetMainCamera()
    {
        return m_mainCamera;
    }
}