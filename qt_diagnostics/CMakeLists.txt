cmake_minimum_required(VERSION 3.16)

project(qt_diagnostics LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets)

# This tells, create executable named 'qt_diagnostics' and compile main.cpp
add_executable(qt_diagnostics
    main.cpp
    MainWindow.cpp
    ui/CanMonitorTab.cpp
    ui/DiagnosticsTab.cpp
    ui/FaultInjectionTab.cpp
    ui/model/CanTableModel.cpp
)

target_include_directories(qt_diagnostics PRIVATE
    $(CMAKE_CURRENT_SOURCE_DIR)
)

# Can use headers from common
target_link_libraries(qt_diagnostics
    common
    Qt5::Widgets
)
