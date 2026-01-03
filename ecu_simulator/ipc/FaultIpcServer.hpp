#pragma once

#include <thread>
#include <atomic>

class CanTx;

class FaultIpcServer {
public:
    explicit FaultIpcServer(CanTx &tx);
    ~FaultIpcServer();

    void start();
    void stop();
    
private:
    void serverLoop();
    std::thread m_thread;
    std::atomic<bool> m_running {false};
    int m_serverFd {-1};

    CanTx &m_canTx;
};