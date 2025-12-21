#pragma once
#include "can/ICanDriver.hpp"
#include <string>

class SocketCanDriver : public ICanDriver {
public:

    // explicit so that it will tell compiler to disable implicit conversion and only creates an object when intended.
    explicit SocketCanDriver(const std::string& interfaceName);

    ~SocketCanDriver() override;

    bool init() override;

    bool send(const CanFrame &frame) override;

    bool receive(CanFrame &frame) override;

private:

    std::string m_interfaceName;
    int m_socketFd {-1};
};