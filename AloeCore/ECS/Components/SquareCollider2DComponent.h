#pragma once

#include "Component.h"

#include <glm/glm.hpp>

namespace Aloe
{
    class SquareCollider2DComponent : public Component
    {
    public:

        glm::vec2 m_offset = {0.0f, 0.0f};
        glm::vec2 m_size = {0.5f, 0.5f};

        // TODO: Physics Material
        float m_density = 1.0f;
        float m_friction = 0.5f;
        float m_restitution = 0.0f;
        float m_restitutionThreshold = 0.5f;

        void* m_runtimeFixture;

        SquareCollider2DComponent() = default;
        SquareCollider2DComponent(const SquareCollider2DComponent&) = default;
    };
}