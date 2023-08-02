#include <Game/GameApplicationBase.h>

#include <Core/AloeEngine.h>
#include <Core/Window.h>

// Defines the game possible behaviours
class GameModule {
public:

    virtual void Init() = 0;
    virtual void Start() = 0;
    virtual void Update() = 0;
    virtual void Pause() = 0; // System pause, not game pause, like Unity Editor´s pause
    virtual void End() = 0;

};

class MyGameModule : public GameModule {
public:

    void Init() override {}
    void Start() override {}
    void Update() override {}
    void Pause() override {}
    void End() override {}

};

class MyGameApplication : public Aloe::GameApplicationBase {
public:
    WindowHandler window;

    bool shouldApplicationClose = false;

    GameModule* gameModule = nullptr;

    MyGameApplication(GameModule* gm) {
        gameModule = gm;
    }

    virtual void Start() {

        window.Create(1280, 720, std::string("AloeEngine"), std::string("0.01"));

        if (gameModule != nullptr) gameModule->Start();

        Aloe::Engine::Get()->Init();

    }
    virtual void Update() {

        while (!shouldApplicationClose && !window.ShouldClose()) {

            // Process Input System here

            if (gameModule != nullptr) gameModule->Update();

            Aloe::Engine::Get()->ProcessSystems();

            window.UpdateFPSCount();
            window.Update();
        }
    }
    virtual void End() {
        if (gameModule != nullptr) gameModule->End();
    }

};

int main(){

    MyGameModule* gameModule = new MyGameModule();

    MyGameApplication gameApplication = MyGameApplication(gameModule);

    gameApplication.Start();
    gameApplication.Update();
    gameApplication.End();

  return 0;
}