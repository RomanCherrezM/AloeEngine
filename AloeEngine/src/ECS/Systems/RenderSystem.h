#ifndef ALOE_RENDER_SYSTEM_H
#define ALOE_RENDER_SYSTEM_H 1

#include <ECS/Systems/System.h>

namespace Aloe {

  class RenderSystem : public System {
  public:

    RenderSystem();
    ~RenderSystem();

    void Init() override;
    void Execute() override;
  };

}

#endif