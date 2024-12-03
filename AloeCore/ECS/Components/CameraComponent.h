#pragma once

#include "Component.h"

#include <glm/glm.hpp>

#include <Render/Framebuffer.h>

namespace Aloe
{
    enum CameraType
    {
        Perspective,
        Ortographic
    };

    struct CameraData
    {
        CameraType m_type = Perspective;

        // View Matrix
        glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 m_front = glm::vec3(0.0f, 0.0f, -1.0f);

        // Projection Matrix
        float m_width = 1920.0f;
        float m_height = 1080.0f;
        float m_fov = 90.0f;

        //Ortho Matrix
        float m_left = 0.0f;
        float m_right = 0.0f;
        float m_bottom = 0.0f;
        float m_top = 0.0f;

        float m_nearPlane = 0.1f;
        float m_farPlane = 1000.0f;
    };

    class CameraComponent : public Component
    {
    public:

        CameraComponent();
        CameraComponent(CameraData cameraData);
        ~CameraComponent();

        // Setters 
        void SetType(CameraType type);

        void SetPosition(glm::vec3 position);
        void SetUp(glm::vec3 up);
        void SetFront(glm::vec3 front);

        void SetWidth(float width);
        void SetHeight(float height);
        void SetFOV(float fov);

        void SetSides(float left, float right, float bottom, float top);

        void SetNearPlane(float nearPlane);
        void SetFarPlane(float farPlane);

        glm::mat4 GetViewMatrix() const;
        glm::mat4 GetProjectionMatrix() const;

        void CreateRenderTarget();

        std::shared_ptr<Framebuffer> m_renderTarget = nullptr;

        CameraData m_cameraData;
    };
}