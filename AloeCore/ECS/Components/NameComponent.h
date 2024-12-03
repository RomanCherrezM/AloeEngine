#pragma once

#include "Component.h"

#include <string>

namespace Aloe
{
    class NameComponent : public Component
    {
    public:

        std::string m_name = "Unamed Entity";
    };
}