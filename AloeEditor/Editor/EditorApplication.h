#pragma once

#include <Application/ApplicationBase.h>
#include <Application/ModuleBase.h>

#include <Core/AloeEngine.h>
#include <Core/Window.h>

namespace Aloe
{
    class EditorApplication : public ApplicationBase {
    public:

        EditorApplication();

        virtual void Start();
        virtual void Update();
        virtual void End();

    private:

        WindowHandler m_window;
        ModuleBase* m_editorModule = nullptr;

        bool m_shouldApplicationClose = false;
        float m_LastFrameTime = 0.0f;
    };
}