#include "Diagnostics.hpp"
#include <iostream>

Diagnostics::Diagnostics(MessageQueue<CanFrame>&rxQueue) : Task("TaskDiagnostics"), m_rxQueue(rxQueue) {

}

void Diagnostics::run() {
    while(isRunning()) {
        CanFrame frame {};
        if(m_rxQueue.pop_for(frame, std::chrono::milliseconds(100))) {
            processFrame(frame);
        }
        checkTimeouts();
    }
}

void Diagnostics::processFrame(const CanFrame& frame) {
    m_lastSeen[frame.id] = std::chrono::steady_clock::now();

    switch(frame.id) {
        case CanId::EngineSpeed: {
            if(frame.dlc != 2) {
                std::cout<<"[DIAG] : EngineSpeed DLC Error"<<std::endl;
                return;
            }
            uint16_t rpm = frame.data[0] | (frame.data[1] << 8);
            if(rpm < 500 || rpm > 4000) {
                std::cout<<"[DIAG] : EngineSpeed out of range "<<rpm<<std::endl;
            }
            break;
        }

        case CanId::Temperature: {
            if(frame.dlc != 1) {
                std::cout<<"[DIAG] : Temperature DLC Error"<<std::endl;
                return;
            }
            uint8_t temp = frame.data[0];
            if(temp > 150) {
                std::cout<<"[DIAG] : Temperature out of range "<<static_cast<int>(temp)<<std::endl;
            }
            break;
        }

        case CanId::Heartbeat: {
            if(frame.dlc != 1 || frame.data[0] != 0xAA) {
                std::cout<<"[DIAG] : Heartbeat invalid"<<std::endl;
                return;
            }
            break;
        }

        default:

            break;
    }
}

void Diagnostics::checkTimeouts() {
    auto currentTime = std::chrono::steady_clock::now();

    auto check = [&] (uint32_t id, std::chrono::milliseconds timeout, const char *name) {
        if(m_lastSeen.find(id) == m_lastSeen.end()) {
            return;
        }
        if(currentTime - m_lastSeen[id] > timeout) {
            std::cout<<"[DIAG] Timeout exceeded for "<<name<<std::endl;
            m_lastSeen.erase(id);
            return;
        }
    };

    check(CanId::EngineSpeed, engineTimeout, "EngineSpeed");
    check(CanId::Heartbeat, heartbeatTimeout, "Heartbeat");
    check(CanId::Temperature, TemperatureTimeout, "Temperature");
}