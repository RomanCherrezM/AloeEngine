#include "InputSystem.h"

#include <Events/Event.h>
#include <Events/InputEvents.h>

#include <ECS/Components/Components.h>

#include <Scene/Entity.h>
#include <Scene/SceneManager.h>

namespace Aloe {

    InputSystem::InputSystem()
    {
    }

    InputSystem::~InputSystem()
    {
    }

    void InputSystem::Init()
    {
        // ALOE-TODO: This should be read from a file
        m_actionSettingBingings.insert(std::make_pair(std::string("W"), ActionInputSetting{ Key::W }));
        m_actionSettingBingings.insert(std::make_pair(std::string("A"), ActionInputSetting{ Key::A }));
        m_actionSettingBingings.insert(std::make_pair(std::string("S"), ActionInputSetting{ Key::S }));
        m_actionSettingBingings.insert(std::make_pair(std::string("D"), ActionInputSetting{ Key::D }));
        m_actionSettingBingings.insert(std::make_pair(std::string("MouseLeftClic"), ActionInputSetting{ Key::MouseLeftClic }));
        m_actionSettingBingings.insert(std::make_pair(std::string("GamepadFaceBottom"), ActionInputSetting{ Key::GamepadFaceDown }));

        m_axisSettingBingings.insert(std::make_pair(std::string("GamepadLeftThumbstickX"), AxisInputSetting{ Key::GamepadLeftThumbstickX }));
        m_axisSettingBingings.insert(std::make_pair(std::string("GamepadLeftThumbstickY"), AxisInputSetting{ Key::GamepadLeftThumbstickY }));

        m_axisSettingBingings.insert(std::make_pair(std::string("LeftTrigger"), AxisInputSetting{ Key::GamepadLeftTrigger }));
        
        m_axisSettingBingings.insert(std::make_pair(std::string("MouseX"), AxisInputSetting{ Key::MouseX }));
        m_axisSettingBingings.insert(std::make_pair(std::string("MouseY"), AxisInputSetting{ Key::MouseY }));

        m_axisSettingBingings.insert(std::make_pair(std::string("MouseScroll"), AxisInputSetting{ Key::MouseScroll }));

    }

    void InputSystem::Execute()
    {
        std::shared_ptr<Scene> scene = SceneManager::Get().GetCurrentScene();

        for each (Entity entity in scene->GetEntities<InputComponent>())
        {
            InputComponent& input = entity.GetComponent<InputComponent>();

            for each (InputActionBinding binding in input.m_actionBindings)
            {
                Key bindingKey = m_actionSettingBingings[binding.m_name].m_key;

                for each (ActionInputEvent inputEvent in m_actionInputEvents)
                {
                    if (bindingKey == inputEvent.m_key) 
                    {
                        if (binding.m_inputType == inputEvent.m_type)
                        {
                            binding.m_binding();
                        }
                    }
                }
            }   

            for each (InputAxisBinding binding in input.m_axisBindings)
            {
                Key bindingKey = m_axisSettingBingings[binding.m_name].m_key;

                for each (AxisInputEvent inputEvent in m_axisInputEvents)
                {
                    if (bindingKey == inputEvent.m_key)
                    {
                        binding.m_binding(inputEvent.m_value);
                    }
                }
            }
        }

        m_actionInputEvents.clear();
        m_axisInputEvents.clear();
    }

    void InputSystem::OnEvent(Event& event)
    {
        switch (event.GetType())
        {
            // Actions
            case EventType::KeyPress:
            {
                KeyPressEvent* e = reinterpret_cast<KeyPressEvent*>(&event);
                m_actionInputEvents.push_back(ActionInputEvent{ e->GetKey(), InputType::Pressed });
                break;
            }
            case EventType::KeyRelease:
            {
                KeyReleaseEvent* e = reinterpret_cast<KeyReleaseEvent*>(&event);
                m_actionInputEvents.push_back(ActionInputEvent{ e->GetKey(), InputType::Released });
                break;
            }
            case EventType::MouseButtonPress:
            {
                MouseButtonPressEvent* e = reinterpret_cast<MouseButtonPressEvent*>(&event);
                m_actionInputEvents.push_back(ActionInputEvent{ e->GetKey(), InputType::Pressed });
                break;
            }
            case EventType::MouseButtonRelease:
            {
                MouseButtonReleaseEvent* e = reinterpret_cast<MouseButtonReleaseEvent*>(&event);
                m_actionInputEvents.push_back(ActionInputEvent{ e->GetKey(), InputType::Released });
                break;
            }
            case EventType::GamepadButtonPress:
            {
                GamepadPressEvent* e = reinterpret_cast<GamepadPressEvent*>(&event);
                m_actionInputEvents.push_back(ActionInputEvent{ e->GetKey(), InputType::Pressed });
                break;
            }
            case EventType::GamepadButtonRelease:
            {
                GamepadReleaseEvent* e = reinterpret_cast<GamepadReleaseEvent*>(&event);
                m_actionInputEvents.push_back(ActionInputEvent{ e->GetKey(), InputType::Released });
                break;
            }

            // Axis
            case EventType::MouseMove:
            {
                MouseMoveEvent* e = reinterpret_cast<MouseMoveEvent*>(&event);

                m_axisInputEvents.push_back(AxisInputEvent{ Input::MouseX, e->m_x });
                m_axisInputEvents.push_back(AxisInputEvent{ Input::MouseY, e->m_y });
                break;
            }
            case EventType::MouseScroll:
            {
                MouseScrollEvent* e = reinterpret_cast<MouseScrollEvent*>(&event);

                m_axisInputEvents.push_back(AxisInputEvent{ Input::MouseScroll, e->m_y });
                break;
            }
            case EventType::GamepadAxis:
            {
                GamepadAxisEvent* e = reinterpret_cast<GamepadAxisEvent*>(&event);

                m_axisInputEvents.push_back(AxisInputEvent{ e->GetKey(), e->m_value });
                break;
            }
        }
    }

}