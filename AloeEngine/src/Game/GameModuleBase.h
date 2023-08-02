#ifndef ALOE_GAME_MODULE_BASE_H
#define ALOE_GAME_MODULE_BASE_H 1

// Defines the game possible behaviours
namespace Aloe {
    class GameModuleBase {
    public:

        virtual void Init() = 0;
        virtual void Start() = 0;
        virtual void Update() = 0;
        virtual void Pause() = 0; // System pause, not game pause, like Unity Editor´s pause
        virtual void End() = 0;

    };
}

#endif
