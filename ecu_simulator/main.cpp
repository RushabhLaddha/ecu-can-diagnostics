#include "can/SocketCanDriver.hpp"
#include "can/CanIds.hpp"
#include<iostream>

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
    return 0;
}