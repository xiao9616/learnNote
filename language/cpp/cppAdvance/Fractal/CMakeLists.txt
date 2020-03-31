cmake_minimum_required(VERSION 3.12)
project(Fractal)

set(CMAKE_CXX_STANDARD 14)

add_executable(Fractal main.cpp BITMAPFILEHEADER.h BitmapInfoHeader.h Bitmap.cpp Bitmap.h Mandelbrot.cpp Mandelbrot.h Zoom.h ZoomList.cpp ZoomList.h FractalCreator.cpp FractalCreator.h)