# This tells, create executable named 'ecu_simulator' and compile main.cpp
add_executable(qt_diagnostics
    main.cpp
)

# Can use headers from common
target_link_libraries(qt_diagnostics
    common
)
