#pragma once
namespace Aloe {
    class ApplicationBase {
    public:

        virtual void Start() = 0;
        virtual void Update() = 0;
        virtual void End() = 0;
    };
}