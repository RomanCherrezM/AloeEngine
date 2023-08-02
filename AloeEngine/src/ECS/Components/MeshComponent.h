#ifndef ALOE_MESH_COMPONENT_H
#define ALOE_MESH_COMPONENT_H 1

#include <vector>

namespace Aloe {

    class MeshComponent {
    public:

        MeshComponent();
        ~MeshComponent();

    private:

        std::vector<float> positions;
        std::vector<float> normals;
        std::vector<float> uvs;

    };
}

#endif