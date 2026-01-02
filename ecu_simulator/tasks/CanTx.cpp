#include "CanTx.hpp"

CanTx::CanTx(std::shared_ptr<ICanDriver>driver) : Task("TaskCanTx") , m_driver(std::move(driver)){

}

void CanTx::run() {

    m_lastEngineSpeed = std::chrono::steady_clock::now();
    m_lastTemperature = std::chrono::steady_clock::now();
    m_lastHeartbeat = std::chrono::steady_clock::now();

    while(isRunning()) {
        if(m_fault == FaultType::StopAll) {
            continue;
        }
        auto currentTime = std::chrono::steady_clock::now();

        if(currentTime - m_lastEngineSpeed >= enginePeriod) {
            sendEngineSpeed();
            m_lastEngineSpeed = currentTime;
        }

        if(currentTime - m_lastTemperature >= temperaturePeriod) {
            sendTemperature();
            m_lastTemperature = currentTime;
        }

        if(currentTime - m_lastHeartbeat >= heartbeatPeriod) {
            sendHeartbeat();
            m_lastHeartbeat = currentTime;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

void CanTx::sendEngineSpeed() {
    static uint16_t rpm = 1000;
    rpm += 50;
    if(rpm >= 4000) rpm = 1000;
    rpm = (m_fault == FaultType::WrongValues) ? 8000 : rpm;

    CanFrame frame{};
    frame.id = CanId::EngineSpeed;
    frame.dlc = (m_fault == FaultType::WrongDLC) ? 1 : 2;

    // little endian encoding LSB -> MSB
    frame.data[0] = rpm & 0xFF;
    frame.data[1] = (rpm >> 8) & 0xFF;

    m_driver->send(frame);
}

void CanTx::sendTemperature() {
    static uint8_t temp = 50;
    temp += 5;
    if(temp >= 150) temp = 50;
    temp = (m_fault == FaultType::WrongValues) ? 200 : temp;

    CanFrame frame {};
    frame.id = CanId::Temperature;
    frame.dlc = (m_fault == FaultType::WrongDLC) ? 2 : 1;
    frame.data[0] = temp;

    m_driver->send(frame);
}

void CanTx::sendHeartbeat() {
    CanFrame frame {};
    frame.id = CanId::Heartbeat;
    frame.dlc = (m_fault == FaultType::WrongDLC) ? 2 : 1;
    uint8_t beat = (m_fault == FaultType::WrongValues) ? 0xBB : 0xAA;
    frame.data[0] = beat;

    m_driver->send(frame);
}

void CanTx::setFault(FaultType fault) {
    m_fault = fault;
}