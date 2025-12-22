#pragma once

#include "CanFrame.hpp"

class ICanDriver {
public:
    virtual ~ICanDriver() = default;
    virtual bool init() = 0;
    virtual bool send(const CanFrame &frame) = 0;
    virtual bool receive(CanFrame &frame) = 0;
};