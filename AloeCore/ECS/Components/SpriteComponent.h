#pragma once

#include "Component.h"

#include <Render/Texture.h>
#include <Render/VertexArray.h>
#include <Render/Shader.h>
#include <Render/Renderer.h>

#include <Core/AssetLibrary.h>

namespace Aloe
{
    class SpriteComponent : public Component
    {
    public:
        SpriteComponent() 
        {
            // TODO : Change this to be default assets from the asset manager
            m_shader = Renderer::Get()->GetDefaultSpriteShader();
            m_mesh = Renderer::Get()->GetDefaultSpriteVertexArray();
        }

        SpriteComponent(std::shared_ptr<Texture>& texture)
        {
            m_shader = Renderer::Get()->GetDefaultSpriteShader();
            m_mesh = Renderer::Get()->GetDefaultSpriteVertexArray();
        }

        ~SpriteComponent()
        {

        }

        UUID m_textureUUID = 0;

        // DISCLAIMER: This is being redone, dont use these meshes directly
        // they should be loaded in the AssetLibrary and here should be
        // the asset UUID to access it, UUID of 0 is a default asset

        std::shared_ptr<VertexArray> m_mesh;  // ALOE-TODO: Mesh is always the same for sprites, move this
        std::shared_ptr<Shader> m_shader;     // ALOE-TODO: Change to Material

        glm::vec3 m_color = {1.0f, 1.0f, 1.0f};
    };
}