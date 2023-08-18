#pragma once

#include <Application/Systems/EventMessenger.h>

namespace Aloe::Input {

    class InputProvider {
    public:

        virtual ~InputProvider() = default;

        virtual void PollInput(IEventListener* eventMessenger) = 0;

    };

}