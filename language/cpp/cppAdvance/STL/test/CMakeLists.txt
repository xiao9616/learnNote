cmake_minimum_required(VERSION 3.12)
project(test)

set(CMAKE_CXX_STANDARD 14)

add_executable(test main.cpp iterator_base.h varadicTemplate.h)