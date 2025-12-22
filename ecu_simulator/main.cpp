#include "can/SocketCanDriver.hpp"
#include "can/CanIds.hpp"
#include <iostream>
#include "rtos/Task.hpp"
#include <chrono>
#include <memory>
#include "tasks/CanTx.hpp"

int main()
{
    auto driver = std::make_shared<SocketCanDriver>("vcan0");
    if(!driver->init()) {
        perror("init");
        return 1;
    }

    CanTx txTask(driver);
    txTask.start();
    std::this_thread::sleep_for(std::chrono::seconds(10));
    txTask.stop();
    
    return 0;
}