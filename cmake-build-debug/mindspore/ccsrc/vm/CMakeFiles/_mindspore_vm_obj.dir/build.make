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
include mindspore/ccsrc/vm/CMakeFiles/_mindspore_vm_obj.dir/depend.make

# Include the progress variables for this target.
include mindspore/ccsrc/vm/CMakeFiles/_mindspore_vm_obj.dir/progress.make

# Include the compile flags for this target's objects.
include mindspore/ccsrc/vm/CMakeFiles/_mindspore_vm_obj.dir/flags.make

mindspore/ccsrc/vm/CMakeFiles/_mindspore_vm_obj.dir/backend.cc.o: mindspore/ccsrc/vm/CMakeFiles/_mindspore_vm_obj.dir/flags.make
mindspore/ccsrc/vm/CMakeFiles/_mindspore_vm_obj.dir/backend.cc.o: ../mindspore/ccsrc/vm/backend.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/geray/mindspore-master/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object mindspore/ccsrc/vm/CMakeFiles/_mindspore_vm_obj.dir/backend.cc.o"
	cd /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc/vm && /usr/bin/c++ $(CXX_DEFINES) -DSUBMODULE_ID=mindspore::SubModuleId::SM_VM $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/_mindspore_vm_obj.dir/backend.cc.o -c /home/geray/mindspore-master/mindspore/ccsrc/vm/backend.cc

mindspore/ccsrc/vm/CMakeFiles/_mindspore_vm_obj.dir/backend.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/_mindspore_vm_obj.dir/backend.cc.i"
	cd /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc/vm && /usr/bin/c++ $(CXX_DEFINES) -DSUBMODULE_ID=mindspore::SubModuleId::SM_VM $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/geray/mindspore-master/mindspore/ccsrc/vm/backend.cc > CMakeFiles/_mindspore_vm_obj.dir/backend.cc.i

mindspore/ccsrc/vm/CMakeFiles/_mindspore_vm_obj.dir/backend.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/_mindspore_vm_obj.dir/backend.cc.s"
	cd /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc/vm && /usr/bin/c++ $(CXX_DEFINES) -DSUBMODULE_ID=mindspore::SubModuleId::SM_VM $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/geray/mindspore-master/mindspore/ccsrc/vm/backend.cc -o CMakeFiles/_mindspore_vm_obj.dir/backend.cc.s

mindspore/ccsrc/vm/CMakeFiles/_mindspore_vm_obj.dir/segment_runner.cc.o: mindspore/ccsrc/vm/CMakeFiles/_mindspore_vm_obj.dir/flags.make
mindspore/ccsrc/vm/CMakeFiles/_mindspore_vm_obj.dir/segment_runner.cc.o: ../mindspore/ccsrc/vm/segment_runner.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/geray/mindspore-master/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object mindspore/ccsrc/vm/CMakeFiles/_mindspore_vm_obj.dir/segment_runner.cc.o"
	cd /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc/vm && /usr/bin/c++ $(CXX_DEFINES) -DSUBMODULE_ID=mindspore::SubModuleId::SM_VM $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/_mindspore_vm_obj.dir/segment_runner.cc.o -c /home/geray/mindspore-master/mindspore/ccsrc/vm/segment_runner.cc

mindspore/ccsrc/vm/CMakeFiles/_mindspore_vm_obj.dir/segment_runner.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/_mindspore_vm_obj.dir/segment_runner.cc.i"
	cd /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc/vm && /usr/bin/c++ $(CXX_DEFINES) -DSUBMODULE_ID=mindspore::SubModuleId::SM_VM $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/geray/mindspore-master/mindspore/ccsrc/vm/segment_runner.cc > CMakeFiles/_mindspore_vm_obj.dir/segment_runner.cc.i

mindspore/ccsrc/vm/CMakeFiles/_mindspore_vm_obj.dir/segment_runner.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/_mindspore_vm_obj.dir/segment_runner.cc.s"
	cd /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc/vm && /usr/bin/c++ $(CXX_DEFINES) -DSUBMODULE_ID=mindspore::SubModuleId::SM_VM $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/geray/mindspore-master/mindspore/ccsrc/vm/segment_runner.cc -o CMakeFiles/_mindspore_vm_obj.dir/segment_runner.cc.s

mindspore/ccsrc/vm/CMakeFiles/_mindspore_vm_obj.dir/transform.cc.o: mindspore/ccsrc/vm/CMakeFiles/_mindspore_vm_obj.dir/flags.make
mindspore/ccsrc/vm/CMakeFiles/_mindspore_vm_obj.dir/transform.cc.o: ../mindspore/ccsrc/vm/transform.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/geray/mindspore-master/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object mindspore/ccsrc/vm/CMakeFiles/_mindspore_vm_obj.dir/transform.cc.o"
	cd /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc/vm && /usr/bin/c++ $(CXX_DEFINES) -DSUBMODULE_ID=mindspore::SubModuleId::SM_VM $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/_mindspore_vm_obj.dir/transform.cc.o -c /home/geray/mindspore-master/mindspore/ccsrc/vm/transform.cc

mindspore/ccsrc/vm/CMakeFiles/_mindspore_vm_obj.dir/transform.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/_mindspore_vm_obj.dir/transform.cc.i"
	cd /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc/vm && /usr/bin/c++ $(CXX_DEFINES) -DSUBMODULE_ID=mindspore::SubModuleId::SM_VM $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/geray/mindspore-master/mindspore/ccsrc/vm/transform.cc > CMakeFiles/_mindspore_vm_obj.dir/transform.cc.i

mindspore/ccsrc/vm/CMakeFiles/_mindspore_vm_obj.dir/transform.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/_mindspore_vm_obj.dir/transform.cc.s"
	cd /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc/vm && /usr/bin/c++ $(CXX_DEFINES) -DSUBMODULE_ID=mindspore::SubModuleId::SM_VM $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/geray/mindspore-master/mindspore/ccsrc/vm/transform.cc -o CMakeFiles/_mindspore_vm_obj.dir/transform.cc.s

mindspore/ccsrc/vm/CMakeFiles/_mindspore_vm_obj.dir/vm.cc.o: mindspore/ccsrc/vm/CMakeFiles/_mindspore_vm_obj.dir/flags.make
mindspore/ccsrc/vm/CMakeFiles/_mindspore_vm_obj.dir/vm.cc.o: ../mindspore/ccsrc/vm/vm.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/geray/mindspore-master/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object mindspore/ccsrc/vm/CMakeFiles/_mindspore_vm_obj.dir/vm.cc.o"
	cd /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc/vm && /usr/bin/c++ $(CXX_DEFINES) -DSUBMODULE_ID=mindspore::SubModuleId::SM_VM $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/_mindspore_vm_obj.dir/vm.cc.o -c /home/geray/mindspore-master/mindspore/ccsrc/vm/vm.cc

mindspore/ccsrc/vm/CMakeFiles/_mindspore_vm_obj.dir/vm.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/_mindspore_vm_obj.dir/vm.cc.i"
	cd /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc/vm && /usr/bin/c++ $(CXX_DEFINES) -DSUBMODULE_ID=mindspore::SubModuleId::SM_VM $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/geray/mindspore-master/mindspore/ccsrc/vm/vm.cc > CMakeFiles/_mindspore_vm_obj.dir/vm.cc.i

mindspore/ccsrc/vm/CMakeFiles/_mindspore_vm_obj.dir/vm.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/_mindspore_vm_obj.dir/vm.cc.s"
	cd /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc/vm && /usr/bin/c++ $(CXX_DEFINES) -DSUBMODULE_ID=mindspore::SubModuleId::SM_VM $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/geray/mindspore-master/mindspore/ccsrc/vm/vm.cc -o CMakeFiles/_mindspore_vm_obj.dir/vm.cc.s

mindspore/ccsrc/vm/CMakeFiles/_mindspore_vm_obj.dir/vmimpl.cc.o: mindspore/ccsrc/vm/CMakeFiles/_mindspore_vm_obj.dir/flags.make
mindspore/ccsrc/vm/CMakeFiles/_mindspore_vm_obj.dir/vmimpl.cc.o: ../mindspore/ccsrc/vm/vmimpl.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/geray/mindspore-master/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object mindspore/ccsrc/vm/CMakeFiles/_mindspore_vm_obj.dir/vmimpl.cc.o"
	cd /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc/vm && /usr/bin/c++ $(CXX_DEFINES) -DSUBMODULE_ID=mindspore::SubModuleId::SM_VM $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/_mindspore_vm_obj.dir/vmimpl.cc.o -c /home/geray/mindspore-master/mindspore/ccsrc/vm/vmimpl.cc

mindspore/ccsrc/vm/CMakeFiles/_mindspore_vm_obj.dir/vmimpl.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/_mindspore_vm_obj.dir/vmimpl.cc.i"
	cd /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc/vm && /usr/bin/c++ $(CXX_DEFINES) -DSUBMODULE_ID=mindspore::SubModuleId::SM_VM $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/geray/mindspore-master/mindspore/ccsrc/vm/vmimpl.cc > CMakeFiles/_mindspore_vm_obj.dir/vmimpl.cc.i

mindspore/ccsrc/vm/CMakeFiles/_mindspore_vm_obj.dir/vmimpl.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/_mindspore_vm_obj.dir/vmimpl.cc.s"
	cd /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc/vm && /usr/bin/c++ $(CXX_DEFINES) -DSUBMODULE_ID=mindspore::SubModuleId::SM_VM $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/geray/mindspore-master/mindspore/ccsrc/vm/vmimpl.cc -o CMakeFiles/_mindspore_vm_obj.dir/vmimpl.cc.s

_mindspore_vm_obj: mindspore/ccsrc/vm/CMakeFiles/_mindspore_vm_obj.dir/backend.cc.o
_mindspore_vm_obj: mindspore/ccsrc/vm/CMakeFiles/_mindspore_vm_obj.dir/segment_runner.cc.o
_mindspore_vm_obj: mindspore/ccsrc/vm/CMakeFiles/_mindspore_vm_obj.dir/transform.cc.o
_mindspore_vm_obj: mindspore/ccsrc/vm/CMakeFiles/_mindspore_vm_obj.dir/vm.cc.o
_mindspore_vm_obj: mindspore/ccsrc/vm/CMakeFiles/_mindspore_vm_obj.dir/vmimpl.cc.o
_mindspore_vm_obj: mindspore/ccsrc/vm/CMakeFiles/_mindspore_vm_obj.dir/build.make

.PHONY : _mindspore_vm_obj

# Rule to build all files generated by this target.
mindspore/ccsrc/vm/CMakeFiles/_mindspore_vm_obj.dir/build: _mindspore_vm_obj

.PHONY : mindspore/ccsrc/vm/CMakeFiles/_mindspore_vm_obj.dir/build

mindspore/ccsrc/vm/CMakeFiles/_mindspore_vm_obj.dir/clean:
	cd /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc/vm && $(CMAKE_COMMAND) -P CMakeFiles/_mindspore_vm_obj.dir/cmake_clean.cmake
.PHONY : mindspore/ccsrc/vm/CMakeFiles/_mindspore_vm_obj.dir/clean

mindspore/ccsrc/vm/CMakeFiles/_mindspore_vm_obj.dir/depend:
	cd /home/geray/mindspore-master/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/geray/mindspore-master /home/geray/mindspore-master/mindspore/ccsrc/vm /home/geray/mindspore-master/cmake-build-debug /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc/vm /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc/vm/CMakeFiles/_mindspore_vm_obj.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : mindspore/ccsrc/vm/CMakeFiles/_mindspore_vm_obj.dir/depend

