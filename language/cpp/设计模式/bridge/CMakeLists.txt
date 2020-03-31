cmake_minimum_required(VERSION 3.12)
project(bridge)

set(CMAKE_CXX_STANDARD 14)

add_executable(bridge main.cpp device.cpp device.h message.cpp message.h pcDevice.cpp pcDevice.h mobileDevice.cpp mobileDevice.h messageLite.cpp messageLite.h meaagePerfect.cpp meaagePerfect.h)