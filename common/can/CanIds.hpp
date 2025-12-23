#pragma once // Include this header only once
#include<cstdint>
namespace CanId {
    // constexpr allows the compiler to compute the value at compile time itself
    constexpr uint32_t EngineSpeed = 0x101;
    constexpr uint32_t Temperature = 0x102;
    constexpr uint32_t Heartbeat = 0x700;
}

#define enginePeriod std::chrono::milliseconds(100)
#define temperaturePeriod std::chrono::milliseconds(200)
#define heartbeatPeriod std::chrono::seconds(1)

#define engineTimeout enginePeriod * 3
#define TemperatureTimeout temperaturePeriod * 3
#define heartbeatTimeout heartbeatPeriod * 3