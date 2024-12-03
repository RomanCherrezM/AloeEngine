#pragma once

#include "Component.h"

#include <Core/UUID.h>

namespace Aloe
{
    class IDComponent : public Component
    {
    public:

        UUID m_UUID;
    };
}