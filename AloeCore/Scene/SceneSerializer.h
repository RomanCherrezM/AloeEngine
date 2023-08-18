#pragma once

#include <Scene/Scene.h>

namespace Aloe {

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