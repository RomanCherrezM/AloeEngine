#ifndef ALOE_RENDERER_H
#define ALOE_RENDERER_H 1

#include <Render/RenderResources.h>

namespace Aloe {

    class Renderer {

        Renderer();
        ~Renderer();

    private:
        RenderResources* m_renderResources;
    };
}

#endif