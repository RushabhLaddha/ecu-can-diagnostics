#include "FaultIpcServer.hpp"
#include "tasks/CanTx.hpp"
#include "diagnostic/FaultType.hpp"

#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

static constexpr const char *SOCKET_PATH = "/tmp/ecu_fault.sock";

FaultIpcServer::FaultIpcServer(CanTx &tx) : m_canTx(tx) {

}

FaultIpcServer::~FaultIpcServer() {
    stop();
}

void FaultIpcServer::start() {
    m_running = true;
    m_thread = std::thread(&FaultIpcServer::serverLoop, this);
}

void FaultIpcServer::stop() {
    m_running = false;
    if(m_thread.joinable()) {
        m_thread.join();
    }
}

void FaultIpcServer::serverLoop() {
    unlink(SOCKET_PATH);

    m_serverFd = socket(AF_UNIX, SOCK_STREAM, 0); // Created Unix Domain Socket - Local IPC
    if(m_serverFd < 0) {
        perror("socket");
        return;
    }

    sockaddr_un addr {}; // Unix socket address
    addr.sun_family = AF_UNIX;
    std::strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1); // Unix socket are filesystem entries

    if(bind(m_serverFd, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) < 0) {
        perror("bind");
        return;
    }

    listen(m_serverFd, 1);

    while(m_running) {
        int clientFd = accept(m_serverFd, nullptr, nullptr);
        if(clientFd < 0) continue;

        FaultType fault;
        ssize_t n = read(clientFd, &fault, sizeof(fault));

        if(n == sizeof(fault)) {
            m_canTx.setFault(fault);
            std::cout << "IPC : Fault received = " << static_cast<int>(fault) << std::endl;
        }

        close(clientFd);
    }
    close(m_serverFd);
}