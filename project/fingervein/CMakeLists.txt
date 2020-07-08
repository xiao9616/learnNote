cmake_minimum_required(VERSION 3.14)
project(fingervein)

set(CMAKE_CXX_STANDARD 14)
#set(OpenCV_DIR /opt/intel/openvino/opencv/cmake)
find_package(OpenCV 4.2 REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable(fingervein main.cpp util/Common.h curvature/CurvatureCalculator.cpp curvature/CurvatureCalculator.h sift_lbp/DetectFeature.cpp sift_lbp/DetectFeature.h util/IO.cpp util/IO.h test/testAllImage.cpp test/testAllImage.h pre_treatment/fft.cpp pre_treatment/fft.h curvature/MaxCurvatures.cpp curvature/MaxCurvatures.h test/testInterface.h test/testMaxCurvature.cpp test/testMaxCurvature.h)
target_link_libraries(fingervein  ${OpenCV_LIBS})