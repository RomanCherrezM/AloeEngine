#include "ApplicationSystems.h"

#include <Application/Systems/ECSManager.h>
#include <Application/Systems/EventMessenger.h>

namespace Aloe {

    ApplicationSystems::ApplicationSystems()
    {
    }

    void ApplicationSystems::InitSystems()
    {
        m_ecsManager = std::make_unique<ECSManager>();
        m_eventMessenger = std::make_shared<EventMessenger>();

        m_ecsManager->Init();

        m_eventMessenger->AddListener(m_ecsManager->GetInputSystem());
    }

    void ApplicationSystems::ExecutePreUpdateSystems()
    {
        m_ecsManager->ExecutePreUpdateSystems();
    }

    void ApplicationSystems::ExecutePostUpdateSystems()
    {
        m_ecsManager->ExecutePostUpdateSystems();
    }

}