# This tells, create executable named 'ecu_simulator' and compile main.cpp
add_executable(ecu_simulator
    main.cpp
)

# Can use headers from common
target_link_libraries(ecu_simulator
    common
)

