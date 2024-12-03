#include "Renderer.h"

#include <glad/glad.h>

#include <Render/Shader.h>
#include <Render/VertexArray.h>
#include <Render/Texture.h>

#include <Core/AssetLibrary.h>

namespace Aloe {

    struct Data
    {
        // Default Sprite Resources
        std::shared_ptr<Shader> m_spriteDefaultShader;
        std::shared_ptr<VertexArray> m_spriteDefaultVertexArray;
        std::shared_ptr<Texture> m_spriteDefaultTexture;


        // Full screen quad Resources
        std::shared_ptr<Shader> m_framebufferShader;
    };

    Renderer::Renderer() 
    {
        m_data = new Data();

    }

    Renderer::~Renderer() 
    {

    }

    void Renderer::Init()
    {
        // Default Resources

        { // Base Sprite Resources
            std::string spriteVertexPath("../AloeCore/Render/Shaders/sprite.vert");
            std::string spriteFragmentPath("../AloeCore/Render/Shaders/sprite.frag");

            m_data->m_spriteDefaultShader = Shader::Create(spriteVertexPath, spriteFragmentPath);

            float spriteVertices[] = {
                 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
                 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
                -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
            };

            std::shared_ptr<VertexBuffer> spriteVB = VertexBuffer::Create(spriteVertices, sizeof(spriteVertices));
            spriteVB->SetLayout({
                { ShaderDataType::Float3, "aPos" },
                { ShaderDataType::Float2, "aUV" }
                });

            m_data->m_spriteDefaultVertexArray = VertexArray::Create();
            m_data->m_spriteDefaultVertexArray->AddVertexBuffer(spriteVB);

            uint32_t spriteIndices[] = { 0, 1, 3, 1, 2, 3 };
            std::shared_ptr<IndexBuffer> spriteIB = IndexBuffer::Create(spriteIndices, sizeof(spriteIndices) / sizeof(uint32_t));
            m_data->m_spriteDefaultVertexArray->SetIndexBuffer(spriteIB);
        }

        // Frambuffer Resources

        {
            std::string framebufferVertexPath("../AloeCore/Render/Shaders/screenFramebuffer.vert");
            std::string framebufferFragmentPath("../AloeCore/Render/Shaders/screenFramebuffer.frag");

            m_data->m_framebufferShader = Shader::Create(framebufferVertexPath, framebufferFragmentPath);
        }

        // Default Texture
        {
            m_data->m_spriteDefaultTexture = Texture::Create("");
        }
    }

    Renderer* Aloe::Renderer::Get()
    {
        static Renderer* render = new Renderer();

        return render;
    }

    std::shared_ptr<Shader> Renderer::GetDefaultSpriteShader()
    {
        return m_data->m_spriteDefaultShader;
    }

    std::shared_ptr<Texture> Renderer::GetDefaultSpriteTexture()
    {
        return m_data->m_spriteDefaultTexture;
    }

    std::shared_ptr<VertexArray> Renderer::GetDefaultSpriteVertexArray()
    {
        return m_data->m_spriteDefaultVertexArray;
    }

    void Renderer::DrawFullScreenQuad(uint32_t textureId)
    {
        glDisable(GL_DEPTH_TEST);
        glBindTextureUnit(0, textureId);

        m_data->m_framebufferShader->Bind();
        m_data->m_spriteDefaultVertexArray->Bind();

        glDrawElements(GL_TRIANGLES, m_data->m_spriteDefaultVertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }
}