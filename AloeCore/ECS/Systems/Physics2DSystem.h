#pragma once

#include <ECS/Systems/System.h>
#include <Scene/Entity.h>

class b2World;

namespace Aloe {

    class Physics2DSystem : public System {
    public:

        Physics2DSystem();
        ~Physics2DSystem();

        void Init() override;
        void Execute() override;

        void OnRuntimeStart() override;
        void OnRuntimeStop() override;

    private:

        b2World* m_physicsWorld = nullptr;
    };
}