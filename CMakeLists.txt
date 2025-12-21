cmake_minimum_required(VERSION 3.16)
project(ecu_can_diagnostics LANGUAGES CXX)

# forcing compiler to use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Go inside these folders and configure their cmakelist also
# Note : order matters, first the shared one, then backend and then frontend
add_subdirectory(common)
add_subdirectory(ecu_simulator)
add_subdirectory(qt_diagnostics)

