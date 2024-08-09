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

        // Current scene context
        std::shared_ptr<Scene> m_currentScene;

        bool m_isPlaying = false;
    };
}