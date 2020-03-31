cmake_minimum_required(VERSION 3.12)
project(observer)

set(CMAKE_CXX_STANDARD 14)

add_executable(observer main.cpp oberverInterFace.cpp oberverInterFace.h oberver.cpp oberver.h objectInterface.cpp objectInterface.h object.cpp object.h)