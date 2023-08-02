#ifndef ALOE_ENGINE_H
#define ALOE_ENGINE_H 1

#include <memory>
#include <ECS/Systems/RenderSystem.h>

namespace Aloe {
    class Engine {
    public:
        Engine();
        ~Engine();

        // Get a pointer to the instance
        static Engine* Get();

        void Init();

        std::shared_ptr<RenderSystem> renderSystem;

        void ProcessSystems();

        class ECSManager* GetECS();
        class RenderResources* GetRenderResources();

    private:
        class ECSManager* m_ecs;
        class RenderResources* m_renderResources;
    };
}
#endif
