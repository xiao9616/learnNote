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
CMAKE_SOURCE_DIR = /home/560204/gitee/LearnNote/cpp/设计模式/composite

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/560204/gitee/LearnNote/cpp/设计模式/composite/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/composite.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/composite.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/composite.dir/flags.make

CMakeFiles/composite.dir/main.cpp.o: CMakeFiles/composite.dir/flags.make
CMakeFiles/composite.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/560204/gitee/LearnNote/cpp/设计模式/composite/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/composite.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/composite.dir/main.cpp.o -c /home/560204/gitee/LearnNote/cpp/设计模式/composite/main.cpp

CMakeFiles/composite.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/composite.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/560204/gitee/LearnNote/cpp/设计模式/composite/main.cpp > CMakeFiles/composite.dir/main.cpp.i

CMakeFiles/composite.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/composite.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/560204/gitee/LearnNote/cpp/设计模式/composite/main.cpp -o CMakeFiles/composite.dir/main.cpp.s

# Object files for target composite
composite_OBJECTS = \
"CMakeFiles/composite.dir/main.cpp.o"

# External object files for target composite
composite_EXTERNAL_OBJECTS =

composite: CMakeFiles/composite.dir/main.cpp.o
composite: CMakeFiles/composite.dir/build.make
composite: CMakeFiles/composite.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/560204/gitee/LearnNote/cpp/设计模式/composite/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable composite"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/composite.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/composite.dir/build: composite

.PHONY : CMakeFiles/composite.dir/build

CMakeFiles/composite.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/composite.dir/cmake_clean.cmake
.PHONY : CMakeFiles/composite.dir/clean

CMakeFiles/composite.dir/depend:
	cd /home/560204/gitee/LearnNote/cpp/设计模式/composite/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/560204/gitee/LearnNote/cpp/设计模式/composite /home/560204/gitee/LearnNote/cpp/设计模式/composite /home/560204/gitee/LearnNote/cpp/设计模式/composite/cmake-build-debug /home/560204/gitee/LearnNote/cpp/设计模式/composite/cmake-build-debug /home/560204/gitee/LearnNote/cpp/设计模式/composite/cmake-build-debug/CMakeFiles/composite.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/composite.dir/depend

