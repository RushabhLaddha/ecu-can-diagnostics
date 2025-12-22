#pragma once

#include<cstdint>
#include<array>
#include<chrono>

// This CanFrame is going to be shared between ecu_simulator, qt_diagnotics and can_driver

struct CanFrame {
    // Can Id
    uint32_t id {0};
    // Data Length
    uint8_t dlc {0};
    // Data
    std::array<uint8_t, 8>data{};
    // Timestamp
    std::chrono::steady_clock::time_point timestamp{};
};