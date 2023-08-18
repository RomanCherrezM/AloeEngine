#include "Texture.h"

#include <Platform/OpenGL/OpenGLTexture.h>

namespace Aloe 
{
    std::shared_ptr<Texture> Texture::Create(const std::string& path)
    {
        return std::make_shared<OpenGLTexture>(path);
    }

    std::shared_ptr<Texture> Texture::Create(const TextureSpecification& spec)
    {
        return std::make_shared<OpenGLTexture>(spec);
    }

}