# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/geray/mindspore-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/geray/mindspore-master/cmake-build-debug

# Include any dependencies generated for this target.
include mindspore/ccsrc/CMakeFiles/_c_expression.dir/depend.make

# Include the progress variables for this target.
include mindspore/ccsrc/CMakeFiles/_c_expression.dir/progress.make

# Include the compile flags for this target's objects.
include mindspore/ccsrc/CMakeFiles/_c_expression.dir/flags.make

mindspore/ccsrc/CMakeFiles/_c_expression.dir/pipeline/jit/init.cc.o: mindspore/ccsrc/CMakeFiles/_c_expression.dir/flags.make
mindspore/ccsrc/CMakeFiles/_c_expression.dir/pipeline/jit/init.cc.o: ../mindspore/ccsrc/pipeline/jit/init.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/geray/mindspore-master/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object mindspore/ccsrc/CMakeFiles/_c_expression.dir/pipeline/jit/init.cc.o"
	cd /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc && /usr/bin/c++ $(CXX_DEFINES) -DSUBMODULE_ID=mindspore::SubModuleId::SM_PIPELINE $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/_c_expression.dir/pipeline/jit/init.cc.o -c /home/geray/mindspore-master/mindspore/ccsrc/pipeline/jit/init.cc

mindspore/ccsrc/CMakeFiles/_c_expression.dir/pipeline/jit/init.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/_c_expression.dir/pipeline/jit/init.cc.i"
	cd /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc && /usr/bin/c++ $(CXX_DEFINES) -DSUBMODULE_ID=mindspore::SubModuleId::SM_PIPELINE $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/geray/mindspore-master/mindspore/ccsrc/pipeline/jit/init.cc > CMakeFiles/_c_expression.dir/pipeline/jit/init.cc.i

mindspore/ccsrc/CMakeFiles/_c_expression.dir/pipeline/jit/init.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/_c_expression.dir/pipeline/jit/init.cc.s"
	cd /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc && /usr/bin/c++ $(CXX_DEFINES) -DSUBMODULE_ID=mindspore::SubModuleId::SM_PIPELINE $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/geray/mindspore-master/mindspore/ccsrc/pipeline/jit/init.cc -o CMakeFiles/_c_expression.dir/pipeline/jit/init.cc.s

# Object files for target _c_expression
_c_expression_OBJECTS = \
"CMakeFiles/_c_expression.dir/pipeline/jit/init.cc.o"

# External object files for target _c_expression
_c_expression_EXTERNAL_OBJECTS =

mindspore/ccsrc/_c_expression.cpython-38-x86_64-linux-gnu.so: mindspore/ccsrc/CMakeFiles/_c_expression.dir/pipeline/jit/init.cc.o
mindspore/ccsrc/_c_expression.cpython-38-x86_64-linux-gnu.so: mindspore/ccsrc/CMakeFiles/_c_expression.dir/build.make
mindspore/ccsrc/_c_expression.cpython-38-x86_64-linux-gnu.so: mindspore/ccsrc/libmindspore.a
mindspore/ccsrc/_c_expression.cpython-38-x86_64-linux-gnu.so: .mslib/protobuf_4323d9fd41921ec1fa643ede4153ca87/lib/libprotobuf.a
mindspore/ccsrc/_c_expression.cpython-38-x86_64-linux-gnu.so: mindspore/core/libmindspore_core.a
mindspore/ccsrc/_c_expression.cpython-38-x86_64-linux-gnu.so: mindspore/core/gvar/libmindspore_gvar.so
mindspore/ccsrc/_c_expression.cpython-38-x86_64-linux-gnu.so: mindspore/ccsrc/libproto_input.a
mindspore/ccsrc/_c_expression.cpython-38-x86_64-linux-gnu.so: .mslib/protobuf_4323d9fd41921ec1fa643ede4153ca87/lib/libprotobuf.a
mindspore/ccsrc/_c_expression.cpython-38-x86_64-linux-gnu.so: securec/src/libsecurec.a
mindspore/ccsrc/_c_expression.cpython-38-x86_64-linux-gnu.so: .mslib/flatbuffers_45f1388bb81c31b4b939e662fce0be08/lib/libflatbuffers.a
mindspore/ccsrc/_c_expression.cpython-38-x86_64-linux-gnu.so: mindspore/ccsrc/CMakeFiles/_c_expression.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/geray/mindspore-master/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared module _c_expression.cpython-38-x86_64-linux-gnu.so"
	cd /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/_c_expression.dir/link.txt --verbose=$(VERBOSE)
	cd /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc && /usr/bin/strip /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc/_c_expression.cpython-38-x86_64-linux-gnu.so

# Rule to build all files generated by this target.
mindspore/ccsrc/CMakeFiles/_c_expression.dir/build: mindspore/ccsrc/_c_expression.cpython-38-x86_64-linux-gnu.so

.PHONY : mindspore/ccsrc/CMakeFiles/_c_expression.dir/build

mindspore/ccsrc/CMakeFiles/_c_expression.dir/clean:
	cd /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc && $(CMAKE_COMMAND) -P CMakeFiles/_c_expression.dir/cmake_clean.cmake
.PHONY : mindspore/ccsrc/CMakeFiles/_c_expression.dir/clean

mindspore/ccsrc/CMakeFiles/_c_expression.dir/depend:
	cd /home/geray/mindspore-master/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/geray/mindspore-master /home/geray/mindspore-master/mindspore/ccsrc /home/geray/mindspore-master/cmake-build-debug /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc/CMakeFiles/_c_expression.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : mindspore/ccsrc/CMakeFiles/_c_expression.dir/depend

