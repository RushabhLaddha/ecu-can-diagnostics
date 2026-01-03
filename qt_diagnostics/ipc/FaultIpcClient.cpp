#include "FaultIpcClient.hpp"

#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

static constexpr const char *SOCKET_PATH = "/tmp/ecu_fault.sock";

void FaultIpcClient::sendFault(FaultType fault) {
    int fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(fd < 0) return;

    sockaddr_un addr {};
    addr.sun_family = AF_UNIX;
    std::strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);

    if(connect(fd, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) == 0) {
        write(fd, &fault, sizeof(fault));
    }

    close(fd);
}