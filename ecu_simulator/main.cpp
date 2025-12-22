#include "can/SocketCanDriver.hpp"
#include "can/CanIds.hpp"
#include <iostream>
#include "rtos/Task.hpp"
#include <chrono>
#include <memory>
#include "tasks/CanTx.hpp"
#include "rtos/MessageQueue.hpp"
#include "tasks/CanRx.hpp"

int main()
{
    auto driver = std::make_shared<SocketCanDriver>("vcan0");
    if(!driver->init()) {
        perror("init");
        return 1;
    }

    MessageQueue<CanFrame>rxQueue;

    CanTx txTask(driver);
    CanRx rxTask(driver, rxQueue);
    txTask.start();
    rxTask.start();
    
    // Frames printing on console
    for(auto i = 0; i < 20; i++) {
        CanFrame frame = rxQueue.pop();
        std::cout<<"Rx: ID=0x"<<std::hex<<frame.id<<std::dec<<std::endl;
    }

    txTask.stop();
    rxTask.stop();
    
    return 0;
}