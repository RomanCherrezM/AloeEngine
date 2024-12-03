#pragma once

#include "Component.h"

#include <glm/glm.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace Aloe
{
    class TransformComponent : public Component
    {
    public:

        glm::vec3 m_position = { 0.0f, 0.0f, 0.0f };
        glm::vec3 m_rotation = { 0.0f, 0.0f, 0.0f };
        glm::vec3 m_scale = { 1.0f, 1.0f, 1.0f };

        TransformComponent() = default;
        TransformComponent(const TransformComponent&) = default;
        TransformComponent(const glm::vec3& position)
            : m_position(position) {}

        glm::mat4 m_matrix;
    };

}