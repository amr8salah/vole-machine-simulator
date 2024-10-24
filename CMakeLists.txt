cmake_minimum_required(VERSION 3.27)
project(vole_machine_simulator)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/back-end)

add_executable(vole_machine_simulator
        src/back-end/app.cpp
        src/back-end/vole-machine.cpp
        src/back-end/vole-machine.h)
