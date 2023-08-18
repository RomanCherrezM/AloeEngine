#include "CameraComponent.h"
#include "CameraComponent.h"

#include <glm/gtx/transform.hpp>

namespace Aloe
{
    CameraComponent::CameraComponent()
    {
    }

    CameraComponent::CameraComponent(CameraData cameraData)
    {
        m_cameraData = cameraData;

        CreateRenderTarget();
    }
    CameraComponent::~CameraComponent()
    {
    }
    void CameraComponent::SetType(CameraType type)
    {
        m_cameraData.m_type = type;
    }
    void CameraComponent::SetPosition(glm::vec3 position)
    {
        m_cameraData.m_position = position;
    }

    void CameraComponent::SetUp(glm::vec3 up)
    {
        m_cameraData.m_up = up;
    }

    void CameraComponent::SetFront(glm::vec3 front)
    {
        m_cameraData.m_front = front;
    }

    void CameraComponent::SetWidth(float width)
    {
        m_cameraData.m_width = width;
    }

    void CameraComponent::SetHeight(float height)
    {
        m_cameraData.m_height = height;
    }

    void CameraComponent::SetFOV(float fov)
    {
        m_cameraData.m_fov = fov;
    }

    void CameraComponent::SetSides(float left, float right, float bottom, float top)
    {
        m_cameraData.m_left = left;
    }

    void CameraComponent::SetNearPlane(float nearPlane)
    {
        m_cameraData.m_nearPlane = nearPlane;
    }

    void CameraComponent::SetFarPlane(float farPlane)
    {
        m_cameraData.m_farPlane = farPlane;
    }

    glm::mat4 CameraComponent::GetViewMatrix() const
    {
        auto view = glm::lookAt(m_cameraData.m_position, m_cameraData.m_position + m_cameraData.m_front, m_cameraData.m_up);

        return view;
    }

    glm::mat4 CameraComponent::GetProjectionMatrix() const
    {
        auto projection = glm::perspective(glm::radians(m_cameraData.m_fov), m_cameraData.m_width / m_cameraData.m_height, m_cameraData.m_nearPlane, m_cameraData.m_farPlane);

        return projection;
    }

    void CameraComponent::CreateRenderTarget()
    {
        FramebufferAttachmentSpecification attachSpec{ FramebufferTextureFormat::RGBA8 };

        FramebufferSpecification spec;

        spec.m_width = m_cameraData.m_width;
        spec.m_height = m_cameraData.m_height;
        spec.m_attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::DEPTH24STENCIL8 };

        m_renderTarget = Framebuffer::Create(spec);
    }
}