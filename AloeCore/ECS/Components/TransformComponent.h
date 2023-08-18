#pragma once

#include <glm/glm.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace Aloe
{
    struct TransformComponent
    {
        glm::vec3 m_position = { 0.0f, 0.0f, 0.0f };
        glm::vec3 m_rotation = { 0.0f, 0.0f, 0.0f };
        glm::vec3 m_scale = { 1.0f, 1.0f, 1.0f };

        TransformComponent() = default;
        TransformComponent(const TransformComponent&) = default;
        TransformComponent(const glm::vec3& position)
            : m_position(position) {}

        glm::mat4 GetTransform() const
        {
            glm::mat4 rotation = glm::toMat4(glm::quat(m_rotation));

            return glm::translate(glm::mat4(1.0f), m_position)
                * rotation
                * glm::scale(glm::mat4(1.0f), m_scale);
        }
    };

}