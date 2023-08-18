#include <Core/AloeEngine.h>

#include <Render/Renderer.h>
#include <Core/AssetLibrary.h>

#include <Application/Systems/ECSManager.h>

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
        m_appSystems = std::make_unique<ApplicationSystems>();
        
        m_appSystems->InitSystems();
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