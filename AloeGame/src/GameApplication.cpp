#include "GameApplication.h"

GameApplication::GameApplication(Aloe::GameModuleBase* gm)
{
    m_gameModule = gm;
}

void GameApplication::Start() 
{
    Aloe::Engine::Get()->Init();

    m_window.Create(1280, 720, std::string("AloeEngine"), std::string("0.01"));

    if (m_gameModule != nullptr) m_gameModule->Start();
}

void GameApplication::Update() 
{
    while (!m_shouldApplicationClose && !m_window.ShouldClose()) {

        // Process Input System here

        if (m_gameModule != nullptr) m_gameModule->Update();

        Aloe::Engine::Get()->ProcessSystems();

        m_window.UpdateFPSCount();
        m_window.Update();
    }
}

void GameApplication::End() 
{
    if (m_gameModule != nullptr) m_gameModule->End();
}