#include <Core/AloeEngine.h>
#include <Core/Window.h>

#include <GameModule.h>
#include <GameApplication.h>

int main(){

    GameModule* gameModule = new GameModule();

    GameApplication gameApplication = GameApplication(gameModule);

    gameApplication.Start();
    gameApplication.Update();
    gameApplication.End();

  return 0;
}