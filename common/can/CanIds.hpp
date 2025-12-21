#pragma once // Include this header only once
#include<cstdint>
namespace CanId {
    // constexpr allows the compiler to compute the value at compile time itself
    constexpr uint32_t EngineSpeed = 0x101;
    constexpr uint32_t Temperature = 0x102;
    constexpr uint32_t Heartbeat = 0x700;
}