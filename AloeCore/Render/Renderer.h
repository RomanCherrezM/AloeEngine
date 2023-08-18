#pragma once

#include <memory>

namespace Aloe {

    class Renderer {
    public:

        Renderer();
        ~Renderer();

        void Init();

        // Get a pointer to the instance
        static Renderer* Get();

        // Default Resources
        std::shared_ptr<class Shader> GetDefaultSpriteShader();
        std::shared_ptr<class Texture> GetDefaultSpriteTexture();
        std::shared_ptr<class VertexArray> GetDefaultSpriteVertexArray();

        void DrawFullScreenQuad(uint32_t textureId);

    private:
        struct Data* m_data;
    };
}