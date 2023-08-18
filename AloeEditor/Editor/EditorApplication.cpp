#include "EditorApplication.h"

#include <Editor/EditorModule.h>

#include <Platform/Time.h>

#include <Events/InputEvents.h>

#include <Application/Systems/EventMessenger.h>

#include <Scene/SceneManager.h>
#include <Scene/SceneSerializer.h>

#include <Core/AssetLibrary.h>

namespace Aloe {

    EditorApplication::EditorApplication()
    {
    }

    void EditorApplication::Start()
    {
        Engine::Get()->Init();

        m_window.Create(1920, 1080, std::string("AloeEngine - Editor Module"), std::string("0.02"));
        m_window.SetEventMessenger(Engine::Get()->GetApplicationSystems()->GetEventMessenger());
        m_window.EnableVSync(false);

        Renderer::Get()->Init();

        AssetLibrary::Get()->InitCacheLibrary("../../AloeProject/Assets");

        // TODO: Get the initial scene from some project settings
        SceneManager::Get().TryLoadScene("../../AloeProject/Assets/Scenes/TestScene.scene");

        m_editorModule = new EditorModule(&m_window);
        m_editorModule->Start();
    }

    void EditorApplication::Update()
    {
        while (!m_shouldApplicationClose && !m_window.ShouldClose()) {

            m_window.PollEvents();

            // Process Input System here

            // Calculate deltaTime
            float time = Time::GetTime();
            float deltaTime = time - m_LastFrameTime;
            m_LastFrameTime = time;

            Engine::Get()->GetApplicationSystems()->ExecutePreUpdateSystems();
            Engine::Get()->SetDeltaTime(deltaTime);

            m_window.Clear();

            Engine::Get()->GetApplicationSystems()->ExecutePostUpdateSystems();
            m_editorModule->Update(deltaTime);

            m_window.UpdateFPSCount();
            m_window.SwapBuffers();
        }
    }

    void EditorApplication::End()
    {
        if (m_editorModule != nullptr) m_editorModule->End();
    }
}