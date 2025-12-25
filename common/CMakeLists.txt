add_library(common
    rtos/Task.cpp
    can/SocketCanDriver.cpp
)

target_include_directories(common PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

