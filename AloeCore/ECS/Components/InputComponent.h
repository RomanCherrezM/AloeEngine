#pragma once

#include "Component.h"

#include <Core/Input.h>

namespace Aloe
{
    class InputComponent : public Component
    {
    public:

        std::vector<Input::InputActionBinding> m_actionBindings;
        std::vector<Input::InputAxisBinding> m_axisBindings;

        void AddActionBinding(const std::string& inputName, const Aloe::Input::InputType& type, const std::function<void()>& binding)
        {
            Input::InputActionBinding actionBinding;

            actionBinding.m_name = inputName;
            actionBinding.m_inputType = type;
            actionBinding.m_binding = binding;

            m_actionBindings.push_back(actionBinding);
        }

        void AddAxisBinding(const std::string& inputName, const std::function<void(const float&)>& binding)
        {
            Input::InputAxisBinding axisBinding;

            axisBinding.m_name = inputName;
            axisBinding.m_binding = binding;

            m_axisBindings.push_back(axisBinding);
        }
    };

    template<typename T>
    std::function<void()> CreateFunctionBinding(void (T::* function)(), T* object)
    {
        auto binding = std::bind(function, object);

        std::function<void()> bindedFunction(binding);

        return bindedFunction;
    }

    template<typename T>
    std::function<void(float)> CreateFunctionBinding(void (T::* function)(const float&), T* object)
    {
        auto binding = std::bind(function, object, std::placeholders::_1);

        std::function<void(const float&)> bindedFunction(binding);

        return bindedFunction;
    }
}