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
CMAKE_SOURCE_DIR = /home/560204/gitee/LearnNote/cpp/设计模式/memento

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/560204/gitee/LearnNote/cpp/设计模式/memento/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/memento.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/memento.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/memento.dir/flags.make

CMakeFiles/memento.dir/main.cpp.o: CMakeFiles/memento.dir/flags.make
CMakeFiles/memento.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/560204/gitee/LearnNote/cpp/设计模式/memento/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/memento.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/memento.dir/main.cpp.o -c /home/560204/gitee/LearnNote/cpp/设计模式/memento/main.cpp

CMakeFiles/memento.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/memento.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/560204/gitee/LearnNote/cpp/设计模式/memento/main.cpp > CMakeFiles/memento.dir/main.cpp.i

CMakeFiles/memento.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/memento.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/560204/gitee/LearnNote/cpp/设计模式/memento/main.cpp -o CMakeFiles/memento.dir/main.cpp.s

CMakeFiles/memento.dir/memeto.cpp.o: CMakeFiles/memento.dir/flags.make
CMakeFiles/memento.dir/memeto.cpp.o: ../memeto.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/560204/gitee/LearnNote/cpp/设计模式/memento/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/memento.dir/memeto.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/memento.dir/memeto.cpp.o -c /home/560204/gitee/LearnNote/cpp/设计模式/memento/memeto.cpp

CMakeFiles/memento.dir/memeto.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/memento.dir/memeto.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/560204/gitee/LearnNote/cpp/设计模式/memento/memeto.cpp > CMakeFiles/memento.dir/memeto.cpp.i

CMakeFiles/memento.dir/memeto.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/memento.dir/memeto.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/560204/gitee/LearnNote/cpp/设计模式/memento/memeto.cpp -o CMakeFiles/memento.dir/memeto.cpp.s

CMakeFiles/memento.dir/originator.cpp.o: CMakeFiles/memento.dir/flags.make
CMakeFiles/memento.dir/originator.cpp.o: ../originator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/560204/gitee/LearnNote/cpp/设计模式/memento/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/memento.dir/originator.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/memento.dir/originator.cpp.o -c /home/560204/gitee/LearnNote/cpp/设计模式/memento/originator.cpp

CMakeFiles/memento.dir/originator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/memento.dir/originator.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/560204/gitee/LearnNote/cpp/设计模式/memento/originator.cpp > CMakeFiles/memento.dir/originator.cpp.i

CMakeFiles/memento.dir/originator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/memento.dir/originator.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/560204/gitee/LearnNote/cpp/设计模式/memento/originator.cpp -o CMakeFiles/memento.dir/originator.cpp.s

# Object files for target memento
memento_OBJECTS = \
"CMakeFiles/memento.dir/main.cpp.o" \
"CMakeFiles/memento.dir/memeto.cpp.o" \
"CMakeFiles/memento.dir/originator.cpp.o"

# External object files for target memento
memento_EXTERNAL_OBJECTS =

memento: CMakeFiles/memento.dir/main.cpp.o
memento: CMakeFiles/memento.dir/memeto.cpp.o
memento: CMakeFiles/memento.dir/originator.cpp.o
memento: CMakeFiles/memento.dir/build.make
memento: CMakeFiles/memento.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/560204/gitee/LearnNote/cpp/设计模式/memento/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable memento"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/memento.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/memento.dir/build: memento

.PHONY : CMakeFiles/memento.dir/build

CMakeFiles/memento.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/memento.dir/cmake_clean.cmake
.PHONY : CMakeFiles/memento.dir/clean

CMakeFiles/memento.dir/depend:
	cd /home/560204/gitee/LearnNote/cpp/设计模式/memento/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/560204/gitee/LearnNote/cpp/设计模式/memento /home/560204/gitee/LearnNote/cpp/设计模式/memento /home/560204/gitee/LearnNote/cpp/设计模式/memento/cmake-build-debug /home/560204/gitee/LearnNote/cpp/设计模式/memento/cmake-build-debug /home/560204/gitee/LearnNote/cpp/设计模式/memento/cmake-build-debug/CMakeFiles/memento.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/memento.dir/depend

