#include "Entity.h"
#include "Entity.h"

#include <Scene/Scene.h>

namespace Aloe
{
    Entity::~Entity()
    {
        m_handler = entt::null;
        m_scene = nullptr;
    }
    Entity::Entity(entt::entity handle, Scene* scene)
        : m_handler(handle), m_scene(scene)
    {
    }

}