#include "SceneManager.h"
#include "SceneManager.h"
#include "SceneManager.h"
#include "SceneManager.h"
#include "SceneManager.h"

#include <Scene/SceneSerializer.h>

namespace Aloe
{
    SceneManager& SceneManager::Get()
    {
        static SceneManager instance;

        return instance;
    }

    bool SceneManager::TryLoadScene(const std::string& filepath)
    {
        std::shared_ptr<Scene> newScene = std::make_shared<Scene>();

        SceneSerializer sceneSerializer(newScene);
        if (sceneSerializer.Deserialize(filepath))
        {
            m_currentScene = newScene;
            return true;
        }

        return false;
    }

    std::shared_ptr<Scene> SceneManager::GetCurrentScene()
    {
        return m_currentScene;
    }

    bool Aloe::SceneManager::IsPlaying()
    {
        return m_isPlaying;
    }

    void Aloe::SceneManager::StartPlaying()
    {
        // Copy the current scene into the runtime scene and set playing to true
        m_isPlaying = true;

    }

    void Aloe::SceneManager::StopPlaying()
    {
        m_isPlaying = false;
    }

    void Aloe::SceneManager::PausePlaying()
    {
        // TODO    
    }
}
