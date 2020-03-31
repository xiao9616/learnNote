cmake_minimum_required(VERSION 3.12)
project(cudaTest)
find_package(CUDA)
set(CMAKE_CXX_STANDARD 14)

add_executable(cudaTest main.cpp foo.cuh foo.cu)
