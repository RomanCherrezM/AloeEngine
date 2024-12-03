#pragma once

#include "Component.h"

#include <Render/Texture.h>
#include <Render/Shader.h>

#include <Render/Renderer.h>
namespace Aloe
{
    class MeshRenderer : public Component
    {
    public:
        MeshRenderer()
        {
            Renderer* renderer = Renderer::Get();

            if (renderer != nullptr)
            {
                m_shader = Renderer::Get()->GetDefaultSpriteShader();
                m_texture = Renderer::Get()->GetDefaultSpriteTexture();
            }
        }

        MeshRenderer(std::shared_ptr<Shader>& shader, std::shared_ptr<Texture>& texture)
        {
            m_shader = shader;
            m_texture = texture;
        }

        ~MeshRenderer() 
        {

        }

        std::shared_ptr<Shader> m_shader;     // ALOE-TODO: Change to Material
        std::shared_ptr<Texture> m_texture;   // ALOE-TODO: Part of Material
    };
}
