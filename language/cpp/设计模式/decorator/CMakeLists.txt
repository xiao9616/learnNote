cmake_minimum_required(VERSION 3.12)
project(decorator)

set(CMAKE_CXX_STANDARD 14)

add_executable(decorator main.cpp stream.cpp stream.h FileStream.cpp FileStream.h NetStream.cpp NetStream.h CryptoStream.cpp CryptoStream.h BufferedStream.cpp BufferedStream.h)