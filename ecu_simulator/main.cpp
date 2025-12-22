#include "can/SocketCanDriver.hpp"
#include "can/CanIds.hpp"
#include<iostream>
#include"rtos/Task.hpp"
#include <chrono>

class DummyTask : public Task {
public:
    DummyTask() : Task("DummyTask") {}
protected:
    void run() override {
        while(isRunning()) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
};

int main()
{
    SocketCanDriver driver("vcan0");

    if(!driver.init()) {
        perror("init");
        return 1;
    }

    CanFrame frame {};
    frame.id = CanId::Heartbeat;
    frame.dlc = 1;
    frame.data[0] = 0x01;

    driver.send(frame);
    
    std::cout<<"Heartbeat sent"<<std::endl;

    DummyTask task;
    task.start();
    std::this_thread::sleep_for(std::chrono::seconds(3));
    task.stop();
    return 0;
}