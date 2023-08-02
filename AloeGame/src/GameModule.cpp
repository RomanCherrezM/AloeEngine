#include "GameModule.h"

#include <Render/Shader.h>

void GameModule::Init()
{
}

void GameModule::Start()
{
    std::string vertexPath("AloeGame/Assets/Shaders/main.vert");
    std::string fragmentPath("AloeGame/Assets/Shaders/main.frag");

    std::shared_ptr<Aloe::Shader> shaderTest = Aloe::Shader::Create(vertexPath, fragmentPath);
}

void GameModule::Update()
{
}

void GameModule::Pause()
{
}

void GameModule::End()
{
}
