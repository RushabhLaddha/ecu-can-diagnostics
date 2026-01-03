#include "can/SocketCanDriver.hpp"
#include "can/CanIds.hpp"
#include <iostream>
#include "rtos/Task.hpp"
#include <chrono>
#include <memory>
#include "tasks/CanTx.hpp"
#include "rtos/MessageQueue.hpp"
#include "tasks/CanRx.hpp"
#include "tasks/Diagnostics.hpp"
#include "ipc/FaultIpcServer.hpp"

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
    Diagnostics diag(rxQueue);
    FaultIpcServer ipc(txTask);

    txTask.start();
    rxTask.start();
    diag.start();
    ipc.start();

    std::this_thread::sleep_for(std::chrono::seconds(100));

    ipc.stop();
    txTask.stop();
    rxTask.stop();
    diag.stop();
    
    return 0;
}