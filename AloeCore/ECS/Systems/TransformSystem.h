#pragma once

#include <ECS/Systems/System.h>
#include <Application/Systems/EventMessenger.h>

#include <ECS/Components/Components.h>

namespace Aloe 
{
    class TransformSystem : public System, public IEventListener {

    public:
        TransformSystem();
        ~TransformSystem();

        void Init() override;
        void Execute() override;

        void OnRuntimeStart() override {}
        void OnRuntimeStop() override {}

        void OnEvent(Event& event) override;

    private:

        void ApplyTransformation(
            TransformComponent& tr, 
            TransformComponent& trParent);
    };

}