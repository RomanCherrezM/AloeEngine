#pragma once

#include <memory>

#include <Render/VertexArray.h>
#include <Render/Renderer.h>

namespace Aloe
{
    class MeshComponent
    {
    public:
        MeshComponent()
        {
            Renderer* renderer = Renderer::Get();

            if (renderer != nullptr)
            {
                m_vertexArray = Renderer::Get()->GetDefaultSpriteVertexArray();
            }
        }

        MeshComponent(std::shared_ptr<VertexArray>& vertex)
        {
            m_vertexArray = vertex;
        }

        ~MeshComponent() {}

        std::shared_ptr<VertexArray> m_vertexArray;
    };
}