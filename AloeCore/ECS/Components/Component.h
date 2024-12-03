#pragma once

#include <Scene/Entity.h>

namespace Aloe
{
    class Component
    {
    public:

        Entity GetOwner() { return m_owner; }

        void Initialize(Entity entity);

    private:

        Entity m_owner;
    };
}