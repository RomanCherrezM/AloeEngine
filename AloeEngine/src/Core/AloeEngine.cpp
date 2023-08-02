#include <Core/AloeEngine.h>

#include <Render/RenderResources.h>

#include <ECS/EcsManager.h>
#include <ECS/Components/SpriteComponent.h>

namespace Aloe {

    Engine::Engine()
    {

    }

    Engine::~Engine()
    {

    }

    Engine* Engine::Get()
    {
        static Engine* engine = new Engine();

        return engine;
    }

    void Engine::Init() {
        //Create ECS
        m_ecs = new ECSManager();
        m_ecs->Init();

        // Register Components
        m_ecs->RegisterComponent<SpriteComponent>();

        // Register Systems
        renderSystem = m_ecs->RegisterSystem<RenderSystem>();

        // Render signature
        {
            Signature signature;
            signature.set(m_ecs->GetComponentType<SpriteComponent>());
            m_ecs->SetSystemSignature<RenderSystem>(signature);
        }
        renderSystem->Init();


        //Render Resources
        m_renderResources = new RenderResources();
    }

    void Engine::ProcessSystems(){

        renderSystem->Execute();

    }

    ECSManager* Engine::GetECS(){
        return m_ecs;
    }
    RenderResources* Engine::GetRenderResources()
    {
        return m_renderResources;
    }
}