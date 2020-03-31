cmake_minimum_required(VERSION 3.12)
project(opencvTest)
find_package(OpenCV 4.0 REQUIRED)
set(CMAKE_CXX_STANDARD 14)

add_executable(opencvTest main.cpp)
TARGET_LINK_LIBRARIES(opencvTest ${OpenCV_LIBS})