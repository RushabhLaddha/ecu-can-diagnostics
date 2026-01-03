#pragma once
#include "diagnostic/FaultType.hpp"
class FaultIpcClient {
public:
    static void sendFault(FaultType fault);
};