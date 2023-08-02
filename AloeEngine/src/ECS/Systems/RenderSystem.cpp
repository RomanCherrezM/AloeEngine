#include <ECS/Systems/RenderSystem.h>

Aloe::RenderSystem::RenderSystem(){

}

Aloe::RenderSystem::~RenderSystem(){

}

void Aloe::RenderSystem::Init(){

}

void Aloe::RenderSystem::Execute(){

    for (int i = 0; i < 100000;++i) {
        float x = sqrt(float(i) / (i * 1.423489234f));
    }
}
