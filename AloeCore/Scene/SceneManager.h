#pragma once

#include <Scene/Scene.h>

namespace Aloe
{
    class SceneManager
    {
    public:
        SceneManager(SceneManager const&) = delete;
        void operator=(SceneManager const&) = delete;

        static SceneManager& Get();
        bool TryLoadScene(const std::string& filepath);
        std::shared_ptr<Scene> GetCurrentScene();

        bool IsPlaying();

        void StartPlaying();

        void StopPlaying();

        void PausePlaying();

    private:
        SceneManager() {}

        // Current scene loaded from file
        std::shared_ptr<Scene> m_openScene;

        // The scene that needs to be modified
        std::shared_ptr<Scene> m_activeScene;

        bool m_isPlaying = false;
    };
}