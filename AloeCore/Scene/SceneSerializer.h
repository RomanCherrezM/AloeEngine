#pragma once

#include <Scene/Scene.h>

namespace Aloe {

    // IMPORTANT: In order to not lose scenes when making changes to serialization:
    // first implement the save function, open all the scenes and save, then implement the load function.

    class SceneSerializer
    {
    public:

        SceneSerializer(const std::shared_ptr<Scene>& scene);

        void Serialize(const std::string& filepath);
        
        bool Deserialize(const std::string& filepath);

    private:

        std::shared_ptr<Scene> m_scene;

    };
}