#pragma once

#include <memory>

namespace Aloe {

    class ECSManager;
    class EventMessenger;

    class ApplicationSystems
    {
    public:
        
        ApplicationSystems();

        void InitSystems();
        void ExecutePreUpdateSystems();
        void ExecutePostUpdateSystems();

        // Getters
        EventMessenger* GetEventMessenger() { return m_eventMessenger.get(); }
        ECSManager* GetECSManager() { return m_ecsManager.get(); }

    private:

        std::shared_ptr<EventMessenger> m_eventMessenger;
        std::shared_ptr<ECSManager> m_ecsManager;
    };

}