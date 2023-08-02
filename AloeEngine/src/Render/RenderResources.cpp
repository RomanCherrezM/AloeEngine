#include "Render/RenderResources.h"

#include <glad/glad.h>

namespace Aloe {

    float triangleVertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    RenderResources::RenderResources()
    {

    }

    RenderResources::~RenderResources()
    {

    }

    // ResourceHandler -------------------------------

    u32 ResourceHandler::GetHandler()
    {
        return m_handler;
    }

    void ResourceHandler::SetHandler(u32 newHandler)
    {
        m_handler = newHandler;
    }

}