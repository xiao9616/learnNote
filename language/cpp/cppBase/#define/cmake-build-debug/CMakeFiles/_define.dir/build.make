# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /home/560204/soft/clion-2018.2.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/560204/soft/clion-2018.2.4/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/560204/LearnNote/C++高级/#define"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/560204/LearnNote/C++高级/#define/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/_define.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/_define.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/_define.dir/flags.make

CMakeFiles/_define.dir/main.cpp.o: CMakeFiles/_define.dir/flags.make
CMakeFiles/_define.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/560204/LearnNote/C++高级/#define/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/_define.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/_define.dir/main.cpp.o -c "/home/560204/LearnNote/C++高级/#define/main.cpp"

CMakeFiles/_define.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/_define.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/560204/LearnNote/C++高级/#define/main.cpp" > CMakeFiles/_define.dir/main.cpp.i

CMakeFiles/_define.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/_define.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/560204/LearnNote/C++高级/#define/main.cpp" -o CMakeFiles/_define.dir/main.cpp.s

# Object files for target _define
_define_OBJECTS = \
"CMakeFiles/_define.dir/main.cpp.o"

# External object files for target _define
_define_EXTERNAL_OBJECTS =

_define: CMakeFiles/_define.dir/main.cpp.o
_define: CMakeFiles/_define.dir/build.make
_define: CMakeFiles/_define.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/560204/LearnNote/C++高级/#define/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable _define"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/_define.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/_define.dir/build: _define

.PHONY : CMakeFiles/_define.dir/build

CMakeFiles/_define.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/_define.dir/cmake_clean.cmake
.PHONY : CMakeFiles/_define.dir/clean

CMakeFiles/_define.dir/depend:
	cd "/home/560204/LearnNote/C++高级/#define/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/560204/LearnNote/C++高级/#define" "/home/560204/LearnNote/C++高级/#define" "/home/560204/LearnNote/C++高级/#define/cmake-build-debug" "/home/560204/LearnNote/C++高级/#define/cmake-build-debug" "/home/560204/LearnNote/C++高级/#define/cmake-build-debug/CMakeFiles/_define.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/_define.dir/depend

