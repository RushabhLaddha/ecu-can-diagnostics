# This tells, create executable named 'ecu_simulator' and compile main.cpp
add_executable(ecu_simulator
    main.cpp
    can/SocketCanDriver.cpp
    tasks/CanTx.cpp
    tasks/CanRx.cpp
    tasks/Diagnostics.cpp
)

target_include_directories(ecu_simulator PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Can use headers from common
target_link_libraries(ecu_simulator
    common
)

if(UNIX)
    target_link_libraries(ecu_simulator pthread)
endif()
