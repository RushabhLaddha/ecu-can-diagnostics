#pragma once 

#include "rtos/Task.hpp"
#include "can/ICanDriver.hpp"
#include "can/CanIds.hpp"
#include "diagnostic/FaultType.hpp"
#include <memory>
#include <chrono>

class CanTx : public Task {
public:
    explicit CanTx(std::shared_ptr<ICanDriver>driver);

    void setFault(FaultType fault);

protected:
    void run() override;

private:
    void sendEngineSpeed();
    void sendTemperature();
    void sendHeartbeat();

    std::shared_ptr<ICanDriver>m_driver;
    std::chrono::steady_clock::time_point m_lastEngineSpeed{};
    std::chrono::steady_clock::time_point m_lastTemperature{};
    std::chrono::steady_clock::time_point m_lastHeartbeat{};
    std::atomic<FaultType> m_fault {FaultType::None};
};