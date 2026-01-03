#include "SocketCanDriver.hpp"

#include <linux/can.h> // struct can_frame is present over here
#include <linux/can/raw.h> // CAN_RAW is defined over here. RAW means we're working with raw CAN frames and no high level protocol
#include <net/if.h> // struct ifreq is present over here
#include <sys/ioctl.h> // input output control. Gives interface index for vcan0
#include <sys/socket.h> // socket relatede system calls
#include <unistd.h> // POSIX system call - Portable Operating System Interface which helps in easy porting between different OS

#include<iostream>
#include<chrono>
#include<cstring>

SocketCanDriver::SocketCanDriver(const std::string& interfaceName) : m_interfaceName(interfaceName) {

}

SocketCanDriver::~SocketCanDriver() {
    if(m_socketFd >= 0) {
        close(m_socketFd);
    }
}

bool SocketCanDriver::init() {
    m_socketFd = socket(PF_CAN, SOCK_RAW, CAN_RAW); // Creates a Linux SocketCAN raw socket

    if(m_socketFd < 0) {
        perror("socket");
        return false;
    }

    struct ifreq ifr {}; // Use to convert interface name to interface index
    std::strncpy(ifr.ifr_name, m_interfaceName.c_str(), IFNAMSIZ - 1);

    if(ioctl(m_socketFd, SIOCGIFINDEX, &ifr) < 0) { // populates interface index in ifr struct
        perror("ioctl");
        return false;
    }

    struct sockaddr_can addr {}; // CAN-specific socket address
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex; // assigns interface index obtained from ioctl

    if(bind(m_socketFd, reinterpret_cast<struct sockaddr *>(&addr), sizeof(addr)) < 0) { // Bind m_socketFd to addr
        perror("bind");
        return false;
    }

    // CAN filters - Only the selected CAN frames will wake up the thread improving efficiency
    struct can_filter filters[3];
    filters[0].can_id   = 0x101;
    filters[0].can_mask = CAN_SFF_MASK;

    filters[1].can_id   = 0x102;
    filters[1].can_mask = CAN_SFF_MASK;

    filters[2].can_id   = 0x700;
    filters[2].can_mask = CAN_SFF_MASK;

    if (setsockopt(m_socketFd, SOL_CAN_RAW, CAN_RAW_FILTER, &filters, sizeof(filters)) < 0)
    {
        perror("setsockopt CAN_RAW_FILTER");
        return false;
    }


    // === Enable receive own messages ===
    int recvOwn = 1;
    if (setsockopt(m_socketFd, SOL_CAN_RAW, CAN_RAW_RECV_OWN_MSGS, &recvOwn, sizeof(recvOwn)) < 0) {
        perror("setsockopt CAN_RAW_RECV_OWN_MSGS");
    }

    // Allow receive() to wake up periodically prevents infinite blocking
    struct timeval timeout {};
    timeout.tv_sec  = 0;
    timeout.tv_usec = 200000; // 200 ms

    setsockopt(m_socketFd, SOL_SOCKET, SO_RCVTIMEO,
            &timeout, sizeof(timeout));

    return true;
}

bool SocketCanDriver::send(const CanFrame &frame) {
    struct can_frame canFrame;

    canFrame.can_id = frame.id;
    canFrame.can_dlc = frame.dlc;
    std::memcpy(canFrame.data, frame.data.data(), frame.dlc);

    ssize_t bytesSend = write(m_socketFd, &canFrame, sizeof(canFrame));
    return bytesSend == sizeof(canFrame);
}

bool SocketCanDriver::receive(CanFrame &frame) {
    struct can_frame canFrame;

    ssize_t bytesRead = read(m_socketFd, &canFrame, sizeof(canFrame));
    
    if(bytesRead < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) { // read() failed but due to timeout
            return false;
        }
        perror("read");
        return false;
    }

    frame.id = canFrame.can_id;
    frame.dlc = canFrame.can_dlc;
    std::memcpy(frame.data.data(), canFrame.data, canFrame.can_dlc);
    frame.timestamp = std::chrono::steady_clock::now();

    return true;
}