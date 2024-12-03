#pragma once

#include "Component.h"

namespace Aloe
{
    class Rigidbody2DComponent : public Component
    {
    public:

        enum class BodyType { Static = 0, Kinematic, Dynamic};
        BodyType m_type = BodyType::Static;
        bool m_fixedRotation;

        void* m_runtimeBody;

        Rigidbody2DComponent() = default;
        Rigidbody2DComponent(const Rigidbody2DComponent&) = default;
    };
}