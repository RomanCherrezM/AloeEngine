#pragma once

#include <memory>
#include <Application/Systems/ApplicationSystems.h>
#include <Scene/Scene.h>

namespace Aloe {

    class CameraComponent;
    class ECS;

    class Engine {
    public:
        Engine();
        ~Engine();

        // Get a pointer to the instance
        static Engine* Get();

        void Init();

        void SetMainCamera(CameraComponent* mainCamera);
        CameraComponent* GetMainCamera();

        ApplicationSystems* GetApplicationSystems() { return m_appSystems.get(); }

        void SetDeltaTime(float deltaTime) { m_currentDeltaTime = deltaTime; }
        float GetDeltaTime() { return m_currentDeltaTime; }

    private:

        std::unique_ptr<ApplicationSystems> m_appSystems;

        CameraComponent* m_mainCamera = nullptr;

        float m_currentDeltaTime = 0.0f;
    };
}
