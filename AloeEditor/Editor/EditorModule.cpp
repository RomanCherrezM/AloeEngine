#include "EditorModule.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <ECS/Components/Components.h>
#include <Core/AloeEngine.h>
#include <Application/Systems/ApplicationSystems.h>
#include <Application/Systems/ECSManager.h>

#include <Scene/SceneManager.h>
#include <Scene/SceneSerializer.h>

#include <Editor/EditorStyles.h>
#include <Editor/EditorToolBar.h>
#include <Editor\HierarchyPanel\EditorHierarchyPanel.h>
#include <Editor\ViewportPanel\EditorViewportPanel.h>
#include <Editor\ConsolePanel\EditorConsolePanel.h>
#include <Editor\ContentBrowserPanel\EditorContentBrowserPanel.h>
#include <Editor\InspectorPanel\EditorInspectorPanel.h>

namespace Aloe {

    ImFont* font;

    EditorModule::EditorModule(Aloe::WindowHandler* window)
    {
        m_window = window;
    }

    void EditorModule::Start()
    {
        const char* glsl_version = "#version 330";

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();

        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(m_window->GetWindowInternal(), true);
        ImGui_ImplOpenGL3_Init(glsl_version);

        Engine::Get()->GetApplicationSystems()->GetECSManager()->GetScriptSystem()->InitImGuiContext(ImGui::GetCurrentContext());

        m_scene = SceneManager::Get().GetCurrentScene();

        SetDraculaStyle();

        font = io.Fonts->AddFontFromFileTTF("../../deps/imgui/misc/fonts/Roboto-Medium.ttf", 16.0f);

        // Open base panels
        OpenPanel(Hierachy);
        OpenPanel(Inspector);
        OpenPanel(Console);
        OpenPanel(ContentBrowser);
        OpenPanel(Viewport);
    }

    void EditorModule::Update(float deltaTime)
    {
        StartFrame();

        ImGui::PushFont(font);

        SetupDockspace();

        // Check for scene changes TODO: This should be an event maybe
        std::shared_ptr<Scene> scene = SceneManager::Get().GetCurrentScene();
        if (scene != m_scene)
        {
            m_scene = scene;
            SceneChangedEvent sceneChangedEvent(m_scene);
            OnEvent(sceneChangedEvent);
        }

        MainMenuBarUpdate();

        int deleteIndex = -1;

        for (int i = 0; i < m_panels.size(); ++i)
        {
            bool shouldClose = m_panels[i]->OnPanelUpdate(m_selectedEntity);

            if (shouldClose)
            {
                deleteIndex = i;
            }
        }

        if (deleteIndex != -1)
        {
            ClosePanel(m_panels[deleteIndex]->GetPanelType());
        }

        ImGui::PopFont();

        EndFrame();
    }

    void EditorModule::End()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
    }

    void EditorModule::StartFrame()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void EditorModule::EndFrame()
    {
        ImGui::EndFrame();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void EditorModule::SetupDockspace()
    {
        int windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking |
            ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(1920, 1080));

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f,0.0f));

        ImGui::Begin("Dockspace Demo", nullptr, windowFlags);
        ImGuiID dockspace_id = ImGui::GetID("Dockspace");

        ImGui::DockSpace(dockspace_id);

        ImGui::End();

        ImGui::PopStyleVar();
    }

    void EditorModule::MainMenuBarUpdate()
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Deserialize", "Ctrl+O"))
                {
                     SceneManager::Get().TryLoadScene("../../AloeProject/Assets/Scenes/TestScene.scene");
                }

                ImGui::Separator();

                if (ImGui::MenuItem("New Scene", "Ctrl+N")) {}
                if (ImGui::MenuItem("Save Scene", "Ctrl+S")) 
                {
                    SceneSerializer serializer(m_scene);
                    serializer.Serialize("../../AloeProject/Assets/Scenes/TestScene.scene");
                }
                if (ImGui::MenuItem("Save Scene As...", "Ctrl+Shift+S")) {}

                ImGui::Separator();

                if (ImGui::MenuItem("Exit")) {}

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Window"))
            {
                if (ImGui::BeginMenu("Open Panel"))
                {
                    if (ImGui::MenuItem("Inspector")) OpenPanel(EPanelType::Inspector);
                    if (ImGui::MenuItem("Hierarchy")) OpenPanel(EPanelType::Hierachy);
                    if (ImGui::MenuItem("Content Browser")) OpenPanel(EPanelType::ContentBrowser);
                    if (ImGui::MenuItem("Console")) OpenPanel(EPanelType::Console);
                    if (ImGui::MenuItem("Viewport")) OpenPanel(EPanelType::Viewport);

                    ImGui::EndMenu();
                }

                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }
    }

    void EditorModule::OpenPanel(EPanelType type)
    {
        if (PanelExists(type)) return;

        EditorPanelBase* panel = nullptr;

        switch (type)
        {
            case Viewport:
            {
                panel = new EditorViewportPanel(this);
            }
                break;
            case ContentBrowser:
            {
                panel = new EditorContentBrowserPanel(this);
            }
                break;
            case Hierachy:
            {
                panel = new EditorHierarchyPanel(this);
            }
                break;
            case Inspector:
            {
                panel = new EditorInspectorPanel(this);
            }
                break;
            case Console:
            {
                panel = new EditorConsolePanel(this);
            }
                break;
            default:
                break;
        }

        if (panel) 
        {
            m_panels.push_back(panel);
            AddListener(panel);

            panel->Init();
        }
    }

    void EditorModule::ClosePanel(EPanelType type)
    {
        int index = -1;
        if (PanelExists(type, &index))
        {
            RemoveListener(m_panels.at(index));
            delete m_panels.at(index);
            m_panels.erase(m_panels.begin() + index);
        }
    }

    bool EditorModule::PanelExists(EPanelType type, int* foundIndex)
    {
        for (int i = 0; i < m_panels.size(); ++i)
        {
            if (m_panels[i]->GetPanelType() == type)
            {
                if (foundIndex != nullptr)
                {
                    *foundIndex = i;
                }
                return true;
            }
        }
        return false;
    }

    void EditorModule::OnEvent(Aloe::EditorEvent& event)
    {

    }
}