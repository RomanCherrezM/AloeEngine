#pragma once

#include <ECS/Systems/System.h>
#include <Application/Systems/EventMessenger.h>

#include <Core/Input.h>

#include <map>

namespace Aloe 
{

    struct ActionInputEvent 
    {
        Input::Key m_key;
        Input::InputType m_type;
    };

    struct AxisInputEvent
    {
        Input::Key m_key;
        
        float m_value;
    };

    // Settings is the structure used to store in file
    struct ActionInputSetting
    {
        Input::Key m_key;
    };

    struct AxisInputSetting
    {
        Input::Key m_key;
    };

    class InputSystem : public System, public IEventListener {

    public:
        InputSystem();
        ~InputSystem();

        void Init() override;
        void Execute() override;

        void OnEvent(Event& event) override;

    private:

        std::map<std::string, ActionInputSetting> m_actionSettingBingings;
        std::map<std::string, AxisInputSetting> m_axisSettingBingings;

        std::vector<ActionInputEvent> m_actionInputEvents;
        std::vector<AxisInputEvent> m_axisInputEvents;
    };

}