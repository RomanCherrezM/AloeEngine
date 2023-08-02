#ifndef ALOE_RENDER_RESOURCES_H
#define ALOE_RENDER_RESOURCES_H 1

#include "RenderTypes.h"

#include <vector>

namespace Aloe {

    class ResourceHandler {
    public:
        ResourceHandler() { m_handler = 0; }
        ~ResourceHandler() {}

        u32 GetHandler();
        void SetHandler(u32 newHandler);

    private:
        u32 m_handler;
    };

    class RenderResources {
    public:

        RenderResources();
        ~RenderResources();
    };
}


#endif
