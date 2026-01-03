#pragma once // Include this header only once
#include<cstdint>
namespace CanId {
    // constexpr allows the compiler to compute the value at compile time itself
    constexpr uint32_t EngineSpeed = 0x101;
    constexpr uint32_t Temperature = 0x102;
    constexpr uint32_t Heartbeat = 0x700;
}

namespace DLC {
    constexpr uint32_t EngineSpeedDLC = 2;
    constexpr uint32_t TemperatureDLC = 1;
    constexpr uint32_t HeartbeatDLC = 1;
}

constexpr auto enginePeriod  = std::chrono::milliseconds(100);
constexpr auto temperaturePeriod = std::chrono::milliseconds(200);
constexpr auto heartbeatPeriod = std::chrono::seconds(1);

constexpr auto engineTimeout = enginePeriod * 3;
constexpr auto TemperatureTimeout = temperaturePeriod * 3;
constexpr auto heartbeatTimeout = heartbeatPeriod * 3;