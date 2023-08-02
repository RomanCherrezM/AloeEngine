#ifndef ALOE_WINDOW_H
#define ALOE_WINDOW_H 1

#include <Core/ErrorHandling.h>

#include <string>

struct GLFWwindow;

class WindowHandler {
public:

    WindowHandler();
    ~WindowHandler();

    Aloe::Error Create(uint32_t w, uint32_t h, std::string name, std::string version);
    void Update();

    void UpdateFPSCount();
    bool ShouldClose();


private:
    GLFWwindow* windowHandler;
  
    std::string titleName;
    std::string titleVersion;

    uint32_t width;
    uint32_t height;

    uint32_t frameCount;
};

#endif