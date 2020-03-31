cmake_minimum_required(VERSION 3.12)
project(strategy)

set(CMAKE_CXX_STANDARD 14)

add_executable(strategy main.cpp TaxStrategy.cpp TaxStrategy.h tax.h)