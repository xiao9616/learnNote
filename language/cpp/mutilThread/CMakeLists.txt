cmake_minimum_required(VERSION 3.12)
project(mutilThread)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")

add_executable(mutilThread main.cpp)