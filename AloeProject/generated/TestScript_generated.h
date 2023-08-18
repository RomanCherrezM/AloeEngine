// TODO: This File should be generated at build time and not edited by hand

#include "TestScript.h"

#include <Scene/Entity.h>
#include <Scene/Scene.h>

#include <imgui.h>

namespace Aloe
{
    namespace ReflectTestScript
    {
        bool s_initialized = false;

        void Initialize()
        {
            if (s_initialized)
            {
                return;
            }

            s_initialized = true;
        }

        Script* AddComponent(Entity entity)
        {
            TestScript& Script = entity.AddComponent<TestScript>();

            return &Script;
        }

        bool HasComponent(Entity entity)
        {
            return entity.HasComponent<TestScript>();
        }

        void DrawInterface(Entity entity)
        {
            TestScript& component = entity.GetComponent<TestScript>();

            ImGui::SliderFloat("Test Float", &component.m_testFloat, -1000, 1000);

            ImGui::SliderInt("Test Int", &component.m_testInt, -1000, 1000);

        }

    }
}