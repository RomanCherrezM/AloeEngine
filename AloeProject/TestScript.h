#pragma once

#include <Core/Script.h>

#include <glm/vec3.hpp>

namespace Aloe
{
    class TestScript : public Script
    {
    public:

        TestScript();
        ~TestScript();

        void Start() override;

        void Update(float deltaTime) override;

        float m_testFloat = 0.0f;

        int m_testInt = 0;

        void WInput();
        void AInput();
        void SInput();
        void DInput();

        void ResetW();
        void ResetA();
        void ResetS();
        void ResetD();

    private:
        // This would be in a physics component
        glm::vec3 velocity;
        glm::vec3 input;
    };
}