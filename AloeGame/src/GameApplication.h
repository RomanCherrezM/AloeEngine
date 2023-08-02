#ifndef ALOE_GAME_APPLICATION_H
#define ALOE_GAME_APPLICATION_H 1

#include <Game/GameApplicationBase.h>
#include <Game/GameModuleBase.h>
#include <Core/AloeEngine.h>
#include <Core/Window.h>

class GameApplication : public Aloe::GameApplicationBase {
public:

    GameApplication(Aloe::GameModuleBase* gm);

    virtual void Start();
    virtual void Update();
    virtual void End();

private:
    WindowHandler m_window;
    Aloe::GameModuleBase* m_gameModule = nullptr;

    bool m_shouldApplicationClose = false;

};


#endif