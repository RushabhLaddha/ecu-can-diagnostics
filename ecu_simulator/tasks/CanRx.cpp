#include "CanRx.hpp"
#include <iostream>

CanRx::CanRx(std::shared_ptr<ICanDriver> driver, MessageQueue<CanFrame>&rxQueue) : Task("TaskCanRx"), m_driver(std::move(driver)), m_rxQueue(rxQueue) {

}

void CanRx::run() {
    while(isRunning()) {
        CanFrame frame {};

        if(m_driver->receive(frame)) {
            m_rxQueue.push(frame);
        }
    }
}