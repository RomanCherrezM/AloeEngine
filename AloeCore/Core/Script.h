#pragma once

#include <Scene/Entity.h>

namespace Aloe
{
    class Script
    {
    public:

        virtual void Start() {};
        virtual void Update(float deltaTime) {};

        template<typename T>
        T& GetComponent() {
            return m_entity.GetComponent<T>();
        }

        template<typename T>
        T& AddComponent() {
            m_entity.AddComponent<T>(T());
        }

        template<typename T>
        bool HasComponent() {
            return m_entity.HasComponent<T>();
        }

        void InternalInitialize(Entity entity)
        {
            m_entity = entity;
        }

    protected:

        Script() {};

    private:

        Entity m_entity;
    };

}