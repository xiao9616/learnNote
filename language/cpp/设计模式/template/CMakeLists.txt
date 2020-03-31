cmake_minimum_required(VERSION 3.12)
project(template)

set(CMAKE_CXX_STANDARD 14)

add_executable(template main.cpp lib.cpp lib.h app.cpp app.h)