# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/user/下载/clion-2019.2/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/user/下载/clion-2019.2/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/user/learnNote/project/fingervein

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/user/learnNote/project/fingervein/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/fingervein.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/fingervein.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/fingervein.dir/flags.make

CMakeFiles/fingervein.dir/main.cpp.o: CMakeFiles/fingervein.dir/flags.make
CMakeFiles/fingervein.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/learnNote/project/fingervein/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/fingervein.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fingervein.dir/main.cpp.o -c /home/user/learnNote/project/fingervein/main.cpp

CMakeFiles/fingervein.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fingervein.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/learnNote/project/fingervein/main.cpp > CMakeFiles/fingervein.dir/main.cpp.i

CMakeFiles/fingervein.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fingervein.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/learnNote/project/fingervein/main.cpp -o CMakeFiles/fingervein.dir/main.cpp.s

CMakeFiles/fingervein.dir/curvature/CurvatureCalculator.cpp.o: CMakeFiles/fingervein.dir/flags.make
CMakeFiles/fingervein.dir/curvature/CurvatureCalculator.cpp.o: ../curvature/CurvatureCalculator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/learnNote/project/fingervein/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/fingervein.dir/curvature/CurvatureCalculator.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fingervein.dir/curvature/CurvatureCalculator.cpp.o -c /home/user/learnNote/project/fingervein/curvature/CurvatureCalculator.cpp

CMakeFiles/fingervein.dir/curvature/CurvatureCalculator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fingervein.dir/curvature/CurvatureCalculator.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/learnNote/project/fingervein/curvature/CurvatureCalculator.cpp > CMakeFiles/fingervein.dir/curvature/CurvatureCalculator.cpp.i

CMakeFiles/fingervein.dir/curvature/CurvatureCalculator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fingervein.dir/curvature/CurvatureCalculator.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/learnNote/project/fingervein/curvature/CurvatureCalculator.cpp -o CMakeFiles/fingervein.dir/curvature/CurvatureCalculator.cpp.s

CMakeFiles/fingervein.dir/sift_lbp/DetectFeature.cpp.o: CMakeFiles/fingervein.dir/flags.make
CMakeFiles/fingervein.dir/sift_lbp/DetectFeature.cpp.o: ../sift_lbp/DetectFeature.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/learnNote/project/fingervein/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/fingervein.dir/sift_lbp/DetectFeature.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fingervein.dir/sift_lbp/DetectFeature.cpp.o -c /home/user/learnNote/project/fingervein/sift_lbp/DetectFeature.cpp

CMakeFiles/fingervein.dir/sift_lbp/DetectFeature.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fingervein.dir/sift_lbp/DetectFeature.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/learnNote/project/fingervein/sift_lbp/DetectFeature.cpp > CMakeFiles/fingervein.dir/sift_lbp/DetectFeature.cpp.i

CMakeFiles/fingervein.dir/sift_lbp/DetectFeature.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fingervein.dir/sift_lbp/DetectFeature.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/learnNote/project/fingervein/sift_lbp/DetectFeature.cpp -o CMakeFiles/fingervein.dir/sift_lbp/DetectFeature.cpp.s

CMakeFiles/fingervein.dir/util/IO.cpp.o: CMakeFiles/fingervein.dir/flags.make
CMakeFiles/fingervein.dir/util/IO.cpp.o: ../util/IO.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/learnNote/project/fingervein/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/fingervein.dir/util/IO.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fingervein.dir/util/IO.cpp.o -c /home/user/learnNote/project/fingervein/util/IO.cpp

CMakeFiles/fingervein.dir/util/IO.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fingervein.dir/util/IO.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/learnNote/project/fingervein/util/IO.cpp > CMakeFiles/fingervein.dir/util/IO.cpp.i

CMakeFiles/fingervein.dir/util/IO.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fingervein.dir/util/IO.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/learnNote/project/fingervein/util/IO.cpp -o CMakeFiles/fingervein.dir/util/IO.cpp.s

CMakeFiles/fingervein.dir/test/testAllImage.cpp.o: CMakeFiles/fingervein.dir/flags.make
CMakeFiles/fingervein.dir/test/testAllImage.cpp.o: ../test/testAllImage.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/learnNote/project/fingervein/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/fingervein.dir/test/testAllImage.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fingervein.dir/test/testAllImage.cpp.o -c /home/user/learnNote/project/fingervein/test/testAllImage.cpp

CMakeFiles/fingervein.dir/test/testAllImage.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fingervein.dir/test/testAllImage.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/learnNote/project/fingervein/test/testAllImage.cpp > CMakeFiles/fingervein.dir/test/testAllImage.cpp.i

CMakeFiles/fingervein.dir/test/testAllImage.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fingervein.dir/test/testAllImage.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/learnNote/project/fingervein/test/testAllImage.cpp -o CMakeFiles/fingervein.dir/test/testAllImage.cpp.s

CMakeFiles/fingervein.dir/pre_treatment/FFT.cpp.o: CMakeFiles/fingervein.dir/flags.make
CMakeFiles/fingervein.dir/pre_treatment/FFT.cpp.o: ../pre_treatment/FFT.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/learnNote/project/fingervein/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/fingervein.dir/pre_treatment/FFT.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fingervein.dir/pre_treatment/FFT.cpp.o -c /home/user/learnNote/project/fingervein/pre_treatment/FFT.cpp

CMakeFiles/fingervein.dir/pre_treatment/FFT.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fingervein.dir/pre_treatment/FFT.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/learnNote/project/fingervein/pre_treatment/FFT.cpp > CMakeFiles/fingervein.dir/pre_treatment/FFT.cpp.i

CMakeFiles/fingervein.dir/pre_treatment/FFT.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fingervein.dir/pre_treatment/FFT.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/learnNote/project/fingervein/pre_treatment/FFT.cpp -o CMakeFiles/fingervein.dir/pre_treatment/FFT.cpp.s

CMakeFiles/fingervein.dir/curvature/MaxCurvatures.cpp.o: CMakeFiles/fingervein.dir/flags.make
CMakeFiles/fingervein.dir/curvature/MaxCurvatures.cpp.o: ../curvature/MaxCurvatures.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/learnNote/project/fingervein/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/fingervein.dir/curvature/MaxCurvatures.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fingervein.dir/curvature/MaxCurvatures.cpp.o -c /home/user/learnNote/project/fingervein/curvature/MaxCurvatures.cpp

CMakeFiles/fingervein.dir/curvature/MaxCurvatures.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fingervein.dir/curvature/MaxCurvatures.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/learnNote/project/fingervein/curvature/MaxCurvatures.cpp > CMakeFiles/fingervein.dir/curvature/MaxCurvatures.cpp.i

CMakeFiles/fingervein.dir/curvature/MaxCurvatures.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fingervein.dir/curvature/MaxCurvatures.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/learnNote/project/fingervein/curvature/MaxCurvatures.cpp -o CMakeFiles/fingervein.dir/curvature/MaxCurvatures.cpp.s

CMakeFiles/fingervein.dir/test/testMaxCurvature.cpp.o: CMakeFiles/fingervein.dir/flags.make
CMakeFiles/fingervein.dir/test/testMaxCurvature.cpp.o: ../test/testMaxCurvature.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/learnNote/project/fingervein/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/fingervein.dir/test/testMaxCurvature.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fingervein.dir/test/testMaxCurvature.cpp.o -c /home/user/learnNote/project/fingervein/test/testMaxCurvature.cpp

CMakeFiles/fingervein.dir/test/testMaxCurvature.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fingervein.dir/test/testMaxCurvature.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/learnNote/project/fingervein/test/testMaxCurvature.cpp > CMakeFiles/fingervein.dir/test/testMaxCurvature.cpp.i

CMakeFiles/fingervein.dir/test/testMaxCurvature.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fingervein.dir/test/testMaxCurvature.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/learnNote/project/fingervein/test/testMaxCurvature.cpp -o CMakeFiles/fingervein.dir/test/testMaxCurvature.cpp.s

CMakeFiles/fingervein.dir/test/SimpleTest.cpp.o: CMakeFiles/fingervein.dir/flags.make
CMakeFiles/fingervein.dir/test/SimpleTest.cpp.o: ../test/SimpleTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/learnNote/project/fingervein/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/fingervein.dir/test/SimpleTest.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fingervein.dir/test/SimpleTest.cpp.o -c /home/user/learnNote/project/fingervein/test/SimpleTest.cpp

CMakeFiles/fingervein.dir/test/SimpleTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fingervein.dir/test/SimpleTest.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/learnNote/project/fingervein/test/SimpleTest.cpp > CMakeFiles/fingervein.dir/test/SimpleTest.cpp.i

CMakeFiles/fingervein.dir/test/SimpleTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fingervein.dir/test/SimpleTest.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/learnNote/project/fingervein/test/SimpleTest.cpp -o CMakeFiles/fingervein.dir/test/SimpleTest.cpp.s

CMakeFiles/fingervein.dir/test/StringTest.cpp.o: CMakeFiles/fingervein.dir/flags.make
CMakeFiles/fingervein.dir/test/StringTest.cpp.o: ../test/StringTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/learnNote/project/fingervein/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/fingervein.dir/test/StringTest.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fingervein.dir/test/StringTest.cpp.o -c /home/user/learnNote/project/fingervein/test/StringTest.cpp

CMakeFiles/fingervein.dir/test/StringTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fingervein.dir/test/StringTest.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/learnNote/project/fingervein/test/StringTest.cpp > CMakeFiles/fingervein.dir/test/StringTest.cpp.i

CMakeFiles/fingervein.dir/test/StringTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fingervein.dir/test/StringTest.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/learnNote/project/fingervein/test/StringTest.cpp -o CMakeFiles/fingervein.dir/test/StringTest.cpp.s

CMakeFiles/fingervein.dir/GMS/GMS.cpp.o: CMakeFiles/fingervein.dir/flags.make
CMakeFiles/fingervein.dir/GMS/GMS.cpp.o: ../GMS/GMS.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/learnNote/project/fingervein/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/fingervein.dir/GMS/GMS.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fingervein.dir/GMS/GMS.cpp.o -c /home/user/learnNote/project/fingervein/GMS/GMS.cpp

CMakeFiles/fingervein.dir/GMS/GMS.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fingervein.dir/GMS/GMS.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/learnNote/project/fingervein/GMS/GMS.cpp > CMakeFiles/fingervein.dir/GMS/GMS.cpp.i

CMakeFiles/fingervein.dir/GMS/GMS.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fingervein.dir/GMS/GMS.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/learnNote/project/fingervein/GMS/GMS.cpp -o CMakeFiles/fingervein.dir/GMS/GMS.cpp.s

CMakeFiles/fingervein.dir/test/GmsTest.cpp.o: CMakeFiles/fingervein.dir/flags.make
CMakeFiles/fingervein.dir/test/GmsTest.cpp.o: ../test/GmsTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/learnNote/project/fingervein/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/fingervein.dir/test/GmsTest.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fingervein.dir/test/GmsTest.cpp.o -c /home/user/learnNote/project/fingervein/test/GmsTest.cpp

CMakeFiles/fingervein.dir/test/GmsTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fingervein.dir/test/GmsTest.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/learnNote/project/fingervein/test/GmsTest.cpp > CMakeFiles/fingervein.dir/test/GmsTest.cpp.i

CMakeFiles/fingervein.dir/test/GmsTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fingervein.dir/test/GmsTest.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/learnNote/project/fingervein/test/GmsTest.cpp -o CMakeFiles/fingervein.dir/test/GmsTest.cpp.s

# Object files for target fingervein
fingervein_OBJECTS = \
"CMakeFiles/fingervein.dir/main.cpp.o" \
"CMakeFiles/fingervein.dir/curvature/CurvatureCalculator.cpp.o" \
"CMakeFiles/fingervein.dir/sift_lbp/DetectFeature.cpp.o" \
"CMakeFiles/fingervein.dir/util/IO.cpp.o" \
"CMakeFiles/fingervein.dir/test/testAllImage.cpp.o" \
"CMakeFiles/fingervein.dir/pre_treatment/FFT.cpp.o" \
"CMakeFiles/fingervein.dir/curvature/MaxCurvatures.cpp.o" \
"CMakeFiles/fingervein.dir/test/testMaxCurvature.cpp.o" \
"CMakeFiles/fingervein.dir/test/SimpleTest.cpp.o" \
"CMakeFiles/fingervein.dir/test/StringTest.cpp.o" \
"CMakeFiles/fingervein.dir/GMS/GMS.cpp.o" \
"CMakeFiles/fingervein.dir/test/GmsTest.cpp.o"

# External object files for target fingervein
fingervein_EXTERNAL_OBJECTS =

fingervein: CMakeFiles/fingervein.dir/main.cpp.o
fingervein: CMakeFiles/fingervein.dir/curvature/CurvatureCalculator.cpp.o
fingervein: CMakeFiles/fingervein.dir/sift_lbp/DetectFeature.cpp.o
fingervein: CMakeFiles/fingervein.dir/util/IO.cpp.o
fingervein: CMakeFiles/fingervein.dir/test/testAllImage.cpp.o
fingervein: CMakeFiles/fingervein.dir/pre_treatment/FFT.cpp.o
fingervein: CMakeFiles/fingervein.dir/curvature/MaxCurvatures.cpp.o
fingervein: CMakeFiles/fingervein.dir/test/testMaxCurvature.cpp.o
fingervein: CMakeFiles/fingervein.dir/test/SimpleTest.cpp.o
fingervein: CMakeFiles/fingervein.dir/test/StringTest.cpp.o
fingervein: CMakeFiles/fingervein.dir/GMS/GMS.cpp.o
fingervein: CMakeFiles/fingervein.dir/test/GmsTest.cpp.o
fingervein: CMakeFiles/fingervein.dir/build.make
fingervein: /usr/local/lib/libopencv_stitching.so.4.4.0
fingervein: /usr/local/lib/libopencv_gapi.so.4.4.0
fingervein: /usr/local/lib/libopencv_intensity_transform.so.4.4.0
fingervein: /usr/local/lib/libopencv_xfeatures2d.so.4.4.0
fingervein: /usr/local/lib/libopencv_ccalib.so.4.4.0
fingervein: /usr/local/lib/libopencv_xphoto.so.4.4.0
fingervein: /usr/local/lib/libopencv_hfs.so.4.4.0
fingervein: /usr/local/lib/libopencv_dpm.so.4.4.0
fingervein: /usr/local/lib/libopencv_dnn_superres.so.4.4.0
fingervein: /usr/local/lib/libopencv_rgbd.so.4.4.0
fingervein: /usr/local/lib/libopencv_quality.so.4.4.0
fingervein: /usr/local/lib/libopencv_bioinspired.so.4.4.0
fingervein: /usr/local/lib/libopencv_bgsegm.so.4.4.0
fingervein: /usr/local/lib/libopencv_img_hash.so.4.4.0
fingervein: /usr/local/lib/libopencv_aruco.so.4.4.0
fingervein: /usr/local/lib/libopencv_saliency.so.4.4.0
fingervein: /usr/local/lib/libopencv_freetype.so.4.4.0
fingervein: /usr/local/lib/libopencv_reg.so.4.4.0
fingervein: /usr/local/lib/libopencv_hdf.so.4.4.0
fingervein: /usr/local/lib/libopencv_face.so.4.4.0
fingervein: /usr/local/lib/libopencv_stereo.so.4.4.0
fingervein: /usr/local/lib/libopencv_shape.so.4.4.0
fingervein: /usr/local/lib/libopencv_line_descriptor.so.4.4.0
fingervein: /usr/local/lib/libopencv_structured_light.so.4.4.0
fingervein: /usr/local/lib/libopencv_videostab.so.4.4.0
fingervein: /usr/local/lib/libopencv_fuzzy.so.4.4.0
fingervein: /usr/local/lib/libopencv_superres.so.4.4.0
fingervein: /usr/local/lib/libopencv_optflow.so.4.4.0
fingervein: /usr/local/lib/libopencv_surface_matching.so.4.4.0
fingervein: /usr/local/lib/libopencv_xobjdetect.so.4.4.0
fingervein: /usr/local/lib/libopencv_phase_unwrapping.so.4.4.0
fingervein: /usr/local/lib/libopencv_tracking.so.4.4.0
fingervein: /usr/local/lib/libopencv_dnn_objdetect.so.4.4.0
fingervein: /usr/local/lib/libopencv_rapid.so.4.4.0
fingervein: /usr/local/lib/libopencv_plot.so.4.4.0
fingervein: /usr/local/lib/libopencv_datasets.so.4.4.0
fingervein: /usr/local/lib/libopencv_text.so.4.4.0
fingervein: /usr/local/lib/libopencv_ml.so.4.4.0
fingervein: /usr/local/lib/libopencv_photo.so.4.4.0
fingervein: /usr/local/lib/libopencv_ximgproc.so.4.4.0
fingervein: /usr/local/lib/libopencv_video.so.4.4.0
fingervein: /usr/local/lib/libopencv_objdetect.so.4.4.0
fingervein: /usr/local/lib/libopencv_highgui.so.4.4.0
fingervein: /usr/local/lib/libopencv_videoio.so.4.4.0
fingervein: /usr/local/lib/libopencv_imgcodecs.so.4.4.0
fingervein: /usr/local/lib/libopencv_dnn.so.4.4.0
fingervein: /usr/local/lib/libopencv_calib3d.so.4.4.0
fingervein: /usr/local/lib/libopencv_features2d.so.4.4.0
fingervein: /usr/local/lib/libopencv_flann.so.4.4.0
fingervein: /usr/local/lib/libopencv_imgproc.so.4.4.0
fingervein: /usr/local/lib/libopencv_core.so.4.4.0
fingervein: CMakeFiles/fingervein.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/user/learnNote/project/fingervein/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Linking CXX executable fingervein"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/fingervein.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/fingervein.dir/build: fingervein

.PHONY : CMakeFiles/fingervein.dir/build

CMakeFiles/fingervein.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/fingervein.dir/cmake_clean.cmake
.PHONY : CMakeFiles/fingervein.dir/clean

CMakeFiles/fingervein.dir/depend:
	cd /home/user/learnNote/project/fingervein/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/user/learnNote/project/fingervein /home/user/learnNote/project/fingervein /home/user/learnNote/project/fingervein/cmake-build-debug /home/user/learnNote/project/fingervein/cmake-build-debug /home/user/learnNote/project/fingervein/cmake-build-debug/CMakeFiles/fingervein.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/fingervein.dir/depend

