#pragma once

#include <ECS/Systems/System.h>

#include <ECS/Components/Components.h>

#include <memory>

namespace Aloe {


    class RenderSpriteSystem : public System {
    public:

        RenderSpriteSystem();
        ~RenderSpriteSystem();

        void Init() override;
        void Execute() override;

        void OnRuntimeStart() override {}
        void OnRuntimeStop() override {}

        CameraComponent* m_renderCamera;
    };

    class RenderMeshSystem : public System {
    public:

        RenderMeshSystem();
        ~RenderMeshSystem();

        void OnRuntimeStart() override {}
        void OnRuntimeStop() override {}

        void Init() override;
        void Execute() override;

        CameraComponent* m_renderCamera;
    };

    class RenderCameraSystem : public System
    {
    public:
        RenderCameraSystem();
        ~RenderCameraSystem();

        void Init() override;
        void Execute() override;

        void OnRuntimeStart() override {}
        void OnRuntimeStop() override {}

        // TODO: Has to be a better way of doing this for sure
        std::shared_ptr<RenderSpriteSystem> m_spriteRenderSystem;
        std::shared_ptr<RenderMeshSystem> m_meshRenderSystem;
    };
}