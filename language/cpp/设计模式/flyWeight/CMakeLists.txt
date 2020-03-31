cmake_minimum_required(VERSION 3.12)
project(flyWeight)

set(CMAKE_CXX_STANDARD 14)

add_executable(flyWeight main.cpp Font.cpp Font.h FontFactory.cpp FontFactory.h)