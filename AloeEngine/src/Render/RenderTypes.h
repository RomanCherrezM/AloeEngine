#ifndef ALOE_RENDER_TYPES_H
#define ALOE_RENDER_TYPES_H 1

#include <glm/glm.hpp>
#include <Core/PlatformTypes.h>

namespace Aloe {

    struct Vertex {

        glm::vec3 pos;
        glm::vec3 nor;
        glm::vec2 uvs;

    };

    struct gl_Mesh {
        u32 gl_vertex_id;
        u32 gl_index_id;
    };

    struct gl_Shader {
        u32 gl_shader;
    };

}

#endif