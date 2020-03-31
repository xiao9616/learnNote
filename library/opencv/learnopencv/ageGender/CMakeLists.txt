cmake_minimum_required(VERSION 3.12)
project(ageGender)

find_package(OpenCV 4.0 REQUIRED)

set(CMAKE_CXX_STANDARD 14)

add_executable(ageGender main.cpp)

target_link_libraries(ageGender ${OpenCV_LIBS})