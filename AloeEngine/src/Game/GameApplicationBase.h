#ifndef ALOE_GAME_APPLICATION_BASE_H
#define ALOE_GAME_APPLICATION_BASE_H 1

namespace Aloe {
    class GameApplicationBase {
    public:

        virtual void Start() = 0;
        virtual void Update() = 0;
        virtual void End() = 0;
    };
}

#endif
