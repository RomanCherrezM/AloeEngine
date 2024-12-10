#pragma once

#include <ECS/Components/Component.h>
#include <Scene/Entity.h>

// Defines for Code Generation

#define ACLASS() /* Class marker for code generation */
#define APARAM() /* Param marker for code generation */

namespace Aloe
{
    class Script : public Component
    {
    public:

        virtual void Start() {};
        virtual void Update(float deltaTime) {};

        template<typename T>
        T& GetComponent() {
            return GetOwner().GetComponent<T>();
        }

        template<typename T>
        T& AddComponent() {
            GetOwner().AddComponent<T>(T());
        }

        template<typename T>
        bool HasComponent() {
            return GetOwner().HasComponent<T>();
        }

    protected:

        Script() {};
    };

}