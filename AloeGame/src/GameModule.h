#ifndef ALOE_GAME_MODULE_H
#define ALOE_GAME_MODULE_H 1

#include <Game/GameModuleBase.h>

class GameModule : public Aloe::GameModuleBase {
public:

    void Init() override;
    void Start() override;
    void Update() override;
    void Pause() override;
    void End() override;

};


#endif