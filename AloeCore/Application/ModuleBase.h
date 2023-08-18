#pragma once
// Defines the game possible behaviours

namespace Aloe {
    class ModuleBase {
    public:

        virtual void Start() = 0;
        virtual void Update(float deltaTime) = 0;
        virtual void End() = 0;

    };
}
