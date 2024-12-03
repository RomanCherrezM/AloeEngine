#include "Component.h"

namespace Aloe
{
    void Component::Initialize(Entity entity)
    {
        m_owner = entity;
    }
}
