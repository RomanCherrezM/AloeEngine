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

        CameraComponent* m_renderCamera;
    };

    class RenderMeshSystem : public System {
    public:

        RenderMeshSystem();
        ~RenderMeshSystem();

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

        // TODO: Has to be a better way of doing this for sure
        std::shared_ptr<RenderSpriteSystem> m_spriteRenderSystem;
        std::shared_ptr<RenderMeshSystem> m_meshRenderSystem;
    };
}