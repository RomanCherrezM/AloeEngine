#include "TestScript.h"

#include <string>

#include <Core/Input.h>
#include <ECS/Components/Components.h>
 
namespace Aloe
{
    TestScript::TestScript()
    {
        printf("\n TestScript Constructor");
        velocity = { 0.0f, 0.0f, 0.0f };
        input = { 0.0f, 0.0f, 0.0f }; 
    } 
     
    TestScript::~TestScript()
    {
        printf("\n TestScript Destructor");
    }
     
    void TestScript::Start()
    {
        printf("\n TestScript Start");

        if (HasComponent<InputComponent>())
        { 
            InputComponent& input = GetComponent<InputComponent>();

            input.AddActionBinding("W", Input::InputType::Pressed, CreateFunctionBinding(&TestScript::WInput, this));
            input.AddActionBinding("A", Input::InputType::Pressed, CreateFunctionBinding(&TestScript::AInput, this));
            input.AddActionBinding("S", Input::InputType::Pressed, CreateFunctionBinding(&TestScript::SInput, this));
            input.AddActionBinding("D", Input::InputType::Pressed, CreateFunctionBinding(&TestScript::DInput, this));

            input.AddActionBinding("W", Input::InputType::Released, CreateFunctionBinding(&TestScript::ResetW, this));
            input.AddActionBinding("A", Input::InputType::Released, CreateFunctionBinding(&TestScript::ResetA, this));
            input.AddActionBinding("S", Input::InputType::Released, CreateFunctionBinding(&TestScript::ResetS, this));
            input.AddActionBinding("D", Input::InputType::Released, CreateFunctionBinding(&TestScript::ResetD, this));
        }
    } 

    void TestScript::Update(float deltaTime) 
    {  
        velocity = input * deltaTime;
         
        if (HasComponent<TransformComponent>())
        {
            TransformComponent& tr = GetComponent<TransformComponent>();
            tr.m_position += velocity;
        }
    }

    void TestScript::WInput()
    {
        input.y = 1.0f;
    }
    void TestScript::AInput()
    {
        input.x = -1.0f;
    }
    void TestScript::SInput() 
    {
        input.y = -1.0f;
    }
    void TestScript::DInput()
    {
        input.x = 1.0f;
    }
    void TestScript::ResetW()
    {
        input.y = 0.0f;
    }
    void TestScript::ResetA()
    {
        input.x = 0.0f;
    }
    void TestScript::ResetS()
    {
        input.y = 0.0f;
    }
    void TestScript::ResetD()
    {
        input.x = 0.0f;
    }
}