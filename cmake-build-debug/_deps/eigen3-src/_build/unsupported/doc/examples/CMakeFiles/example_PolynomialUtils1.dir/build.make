# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

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
CMAKE_COMMAND = /home/geray/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7319.72/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/geray/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7319.72/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/_build

# Include any dependencies generated for this target.
include unsupported/doc/examples/CMakeFiles/example_PolynomialUtils1.dir/depend.make

# Include the progress variables for this target.
include unsupported/doc/examples/CMakeFiles/example_PolynomialUtils1.dir/progress.make

# Include the compile flags for this target's objects.
include unsupported/doc/examples/CMakeFiles/example_PolynomialUtils1.dir/flags.make

unsupported/doc/examples/CMakeFiles/example_PolynomialUtils1.dir/PolynomialUtils1.cpp.o: unsupported/doc/examples/CMakeFiles/example_PolynomialUtils1.dir/flags.make
unsupported/doc/examples/CMakeFiles/example_PolynomialUtils1.dir/PolynomialUtils1.cpp.o: ../unsupported/doc/examples/PolynomialUtils1.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object unsupported/doc/examples/CMakeFiles/example_PolynomialUtils1.dir/PolynomialUtils1.cpp.o"
	cd /home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/_build/unsupported/doc/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/example_PolynomialUtils1.dir/PolynomialUtils1.cpp.o -c /home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/unsupported/doc/examples/PolynomialUtils1.cpp

unsupported/doc/examples/CMakeFiles/example_PolynomialUtils1.dir/PolynomialUtils1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/example_PolynomialUtils1.dir/PolynomialUtils1.cpp.i"
	cd /home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/_build/unsupported/doc/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/unsupported/doc/examples/PolynomialUtils1.cpp > CMakeFiles/example_PolynomialUtils1.dir/PolynomialUtils1.cpp.i

unsupported/doc/examples/CMakeFiles/example_PolynomialUtils1.dir/PolynomialUtils1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/example_PolynomialUtils1.dir/PolynomialUtils1.cpp.s"
	cd /home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/_build/unsupported/doc/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/unsupported/doc/examples/PolynomialUtils1.cpp -o CMakeFiles/example_PolynomialUtils1.dir/PolynomialUtils1.cpp.s

# Object files for target example_PolynomialUtils1
example_PolynomialUtils1_OBJECTS = \
"CMakeFiles/example_PolynomialUtils1.dir/PolynomialUtils1.cpp.o"

# External object files for target example_PolynomialUtils1
example_PolynomialUtils1_EXTERNAL_OBJECTS =

unsupported/doc/examples/example_PolynomialUtils1: unsupported/doc/examples/CMakeFiles/example_PolynomialUtils1.dir/PolynomialUtils1.cpp.o
unsupported/doc/examples/example_PolynomialUtils1: unsupported/doc/examples/CMakeFiles/example_PolynomialUtils1.dir/build.make
unsupported/doc/examples/example_PolynomialUtils1: unsupported/doc/examples/CMakeFiles/example_PolynomialUtils1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable example_PolynomialUtils1"
	cd /home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/_build/unsupported/doc/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/example_PolynomialUtils1.dir/link.txt --verbose=$(VERBOSE)
	cd /home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/_build/unsupported/doc/examples && ./example_PolynomialUtils1 >/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/_build/unsupported/doc/examples/PolynomialUtils1.out

# Rule to build all files generated by this target.
unsupported/doc/examples/CMakeFiles/example_PolynomialUtils1.dir/build: unsupported/doc/examples/example_PolynomialUtils1

.PHONY : unsupported/doc/examples/CMakeFiles/example_PolynomialUtils1.dir/build

unsupported/doc/examples/CMakeFiles/example_PolynomialUtils1.dir/clean:
	cd /home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/_build/unsupported/doc/examples && $(CMAKE_COMMAND) -P CMakeFiles/example_PolynomialUtils1.dir/cmake_clean.cmake
.PHONY : unsupported/doc/examples/CMakeFiles/example_PolynomialUtils1.dir/clean

unsupported/doc/examples/CMakeFiles/example_PolynomialUtils1.dir/depend:
	cd /home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src /home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/unsupported/doc/examples /home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/_build /home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/_build/unsupported/doc/examples /home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/_build/unsupported/doc/examples/CMakeFiles/example_PolynomialUtils1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : unsupported/doc/examples/CMakeFiles/example_PolynomialUtils1.dir/depend

