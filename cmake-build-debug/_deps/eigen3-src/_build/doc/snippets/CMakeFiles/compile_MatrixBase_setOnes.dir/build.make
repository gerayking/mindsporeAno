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
include doc/snippets/CMakeFiles/compile_MatrixBase_setOnes.dir/depend.make

# Include the progress variables for this target.
include doc/snippets/CMakeFiles/compile_MatrixBase_setOnes.dir/progress.make

# Include the compile flags for this target's objects.
include doc/snippets/CMakeFiles/compile_MatrixBase_setOnes.dir/flags.make

doc/snippets/CMakeFiles/compile_MatrixBase_setOnes.dir/compile_MatrixBase_setOnes.cpp.o: doc/snippets/CMakeFiles/compile_MatrixBase_setOnes.dir/flags.make
doc/snippets/CMakeFiles/compile_MatrixBase_setOnes.dir/compile_MatrixBase_setOnes.cpp.o: doc/snippets/compile_MatrixBase_setOnes.cpp
doc/snippets/CMakeFiles/compile_MatrixBase_setOnes.dir/compile_MatrixBase_setOnes.cpp.o: ../doc/snippets/MatrixBase_setOnes.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object doc/snippets/CMakeFiles/compile_MatrixBase_setOnes.dir/compile_MatrixBase_setOnes.cpp.o"
	cd /home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/_build/doc/snippets && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/compile_MatrixBase_setOnes.dir/compile_MatrixBase_setOnes.cpp.o -c /home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/_build/doc/snippets/compile_MatrixBase_setOnes.cpp

doc/snippets/CMakeFiles/compile_MatrixBase_setOnes.dir/compile_MatrixBase_setOnes.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compile_MatrixBase_setOnes.dir/compile_MatrixBase_setOnes.cpp.i"
	cd /home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/_build/doc/snippets && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/_build/doc/snippets/compile_MatrixBase_setOnes.cpp > CMakeFiles/compile_MatrixBase_setOnes.dir/compile_MatrixBase_setOnes.cpp.i

doc/snippets/CMakeFiles/compile_MatrixBase_setOnes.dir/compile_MatrixBase_setOnes.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compile_MatrixBase_setOnes.dir/compile_MatrixBase_setOnes.cpp.s"
	cd /home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/_build/doc/snippets && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/_build/doc/snippets/compile_MatrixBase_setOnes.cpp -o CMakeFiles/compile_MatrixBase_setOnes.dir/compile_MatrixBase_setOnes.cpp.s

# Object files for target compile_MatrixBase_setOnes
compile_MatrixBase_setOnes_OBJECTS = \
"CMakeFiles/compile_MatrixBase_setOnes.dir/compile_MatrixBase_setOnes.cpp.o"

# External object files for target compile_MatrixBase_setOnes
compile_MatrixBase_setOnes_EXTERNAL_OBJECTS =

doc/snippets/compile_MatrixBase_setOnes: doc/snippets/CMakeFiles/compile_MatrixBase_setOnes.dir/compile_MatrixBase_setOnes.cpp.o
doc/snippets/compile_MatrixBase_setOnes: doc/snippets/CMakeFiles/compile_MatrixBase_setOnes.dir/build.make
doc/snippets/compile_MatrixBase_setOnes: doc/snippets/CMakeFiles/compile_MatrixBase_setOnes.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable compile_MatrixBase_setOnes"
	cd /home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/_build/doc/snippets && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/compile_MatrixBase_setOnes.dir/link.txt --verbose=$(VERBOSE)
	cd /home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/_build/doc/snippets && ./compile_MatrixBase_setOnes >/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/_build/doc/snippets/MatrixBase_setOnes.out

# Rule to build all files generated by this target.
doc/snippets/CMakeFiles/compile_MatrixBase_setOnes.dir/build: doc/snippets/compile_MatrixBase_setOnes

.PHONY : doc/snippets/CMakeFiles/compile_MatrixBase_setOnes.dir/build

doc/snippets/CMakeFiles/compile_MatrixBase_setOnes.dir/clean:
	cd /home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/_build/doc/snippets && $(CMAKE_COMMAND) -P CMakeFiles/compile_MatrixBase_setOnes.dir/cmake_clean.cmake
.PHONY : doc/snippets/CMakeFiles/compile_MatrixBase_setOnes.dir/clean

doc/snippets/CMakeFiles/compile_MatrixBase_setOnes.dir/depend:
	cd /home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src /home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/doc/snippets /home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/_build /home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/_build/doc/snippets /home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/_build/doc/snippets/CMakeFiles/compile_MatrixBase_setOnes.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : doc/snippets/CMakeFiles/compile_MatrixBase_setOnes.dir/depend

