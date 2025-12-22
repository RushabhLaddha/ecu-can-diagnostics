#include "CanTx.hpp"

#define enginePeriod std::chrono::milliseconds(100)
#define temperaturePeriod std::chrono::milliseconds(200)
#define heartbeatPeriod std::chrono::seconds(1)


CanTx::CanTx(std::shared_ptr<ICanDriver>driver) : Task("TaskCanTx") , m_driver(std::move(driver)){

}

void CanTx::run() {

    m_lastEngineSpeed = std::chrono::steady_clock::now();
    m_lastTemperature = std::chrono::steady_clock::now();
    m_lastHeartbeat = std::chrono::steady_clock::now();

    while(isRunning()) {
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

    CanFrame frame{};
    frame.id = CanId::EngineSpeed;
    frame.dlc = 2;
    frame.data[0] = rpm & 0xFF;
    frame.data[1] = (rpm >> 8) & 0xFF;

    m_driver->send(frame);
}

void CanTx::sendTemperature() {
    static uint8_t temp = 50;
    temp += 5;
    if(temp >= 150) temp = 50;

    CanFrame frame {};
    frame.id = CanId::Temperature;
    frame.dlc = 1;
    frame.data[0] = temp;

    m_driver->send(frame);
}

void CanTx::sendHeartbeat() {
    CanFrame frame {};
    frame.id = CanId::Heartbeat;
    frame.dlc = 1;
    frame.data[0] = 0xAA;

    m_driver->send(frame);
}