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
CMAKE_SOURCE_DIR = /home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-subbuild

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-subbuild

# Utility rule file for ms_onnx-populate.

# Include the progress variables for this target.
include CMakeFiles/ms_onnx-populate.dir/progress.make

CMakeFiles/ms_onnx-populate: CMakeFiles/ms_onnx-populate-complete


CMakeFiles/ms_onnx-populate-complete: ms_onnx-populate-prefix/src/ms_onnx-populate-stamp/ms_onnx-populate-install
CMakeFiles/ms_onnx-populate-complete: ms_onnx-populate-prefix/src/ms_onnx-populate-stamp/ms_onnx-populate-mkdir
CMakeFiles/ms_onnx-populate-complete: ms_onnx-populate-prefix/src/ms_onnx-populate-stamp/ms_onnx-populate-download
CMakeFiles/ms_onnx-populate-complete: ms_onnx-populate-prefix/src/ms_onnx-populate-stamp/ms_onnx-populate-update
CMakeFiles/ms_onnx-populate-complete: ms_onnx-populate-prefix/src/ms_onnx-populate-stamp/ms_onnx-populate-patch
CMakeFiles/ms_onnx-populate-complete: ms_onnx-populate-prefix/src/ms_onnx-populate-stamp/ms_onnx-populate-configure
CMakeFiles/ms_onnx-populate-complete: ms_onnx-populate-prefix/src/ms_onnx-populate-stamp/ms_onnx-populate-build
CMakeFiles/ms_onnx-populate-complete: ms_onnx-populate-prefix/src/ms_onnx-populate-stamp/ms_onnx-populate-install
CMakeFiles/ms_onnx-populate-complete: ms_onnx-populate-prefix/src/ms_onnx-populate-stamp/ms_onnx-populate-test
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Completed 'ms_onnx-populate'"
	/usr/bin/cmake -E make_directory /home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-subbuild/CMakeFiles
	/usr/bin/cmake -E touch /home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-subbuild/CMakeFiles/ms_onnx-populate-complete
	/usr/bin/cmake -E touch /home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-subbuild/ms_onnx-populate-prefix/src/ms_onnx-populate-stamp/ms_onnx-populate-done

ms_onnx-populate-prefix/src/ms_onnx-populate-stamp/ms_onnx-populate-install: ms_onnx-populate-prefix/src/ms_onnx-populate-stamp/ms_onnx-populate-build
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "No install step for 'ms_onnx-populate'"
	cd /home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-build && /usr/bin/cmake -E echo_append
	cd /home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-build && /usr/bin/cmake -E touch /home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-subbuild/ms_onnx-populate-prefix/src/ms_onnx-populate-stamp/ms_onnx-populate-install

ms_onnx-populate-prefix/src/ms_onnx-populate-stamp/ms_onnx-populate-mkdir:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Creating directories for 'ms_onnx-populate'"
	/usr/bin/cmake -E make_directory /home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-src
	/usr/bin/cmake -E make_directory /home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-build
	/usr/bin/cmake -E make_directory /home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-subbuild/ms_onnx-populate-prefix
	/usr/bin/cmake -E make_directory /home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-subbuild/ms_onnx-populate-prefix/tmp
	/usr/bin/cmake -E make_directory /home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-subbuild/ms_onnx-populate-prefix/src/ms_onnx-populate-stamp
	/usr/bin/cmake -E make_directory /home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-subbuild/ms_onnx-populate-prefix/src
	/usr/bin/cmake -E make_directory /home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-subbuild/ms_onnx-populate-prefix/src/ms_onnx-populate-stamp
	/usr/bin/cmake -E touch /home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-subbuild/ms_onnx-populate-prefix/src/ms_onnx-populate-stamp/ms_onnx-populate-mkdir

ms_onnx-populate-prefix/src/ms_onnx-populate-stamp/ms_onnx-populate-download: ms_onnx-populate-prefix/src/ms_onnx-populate-stamp/ms_onnx-populate-urlinfo.txt
ms_onnx-populate-prefix/src/ms_onnx-populate-stamp/ms_onnx-populate-download: ms_onnx-populate-prefix/src/ms_onnx-populate-stamp/ms_onnx-populate-mkdir
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Performing download step (download, verify and extract) for 'ms_onnx-populate'"
	cd /home/geray/mindspore-master/cmake-build-debug/_deps && /usr/bin/cmake -P /home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-subbuild/ms_onnx-populate-prefix/src/ms_onnx-populate-stamp/download-ms_onnx-populate.cmake
	cd /home/geray/mindspore-master/cmake-build-debug/_deps && /usr/bin/cmake -P /home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-subbuild/ms_onnx-populate-prefix/src/ms_onnx-populate-stamp/verify-ms_onnx-populate.cmake
	cd /home/geray/mindspore-master/cmake-build-debug/_deps && /usr/bin/cmake -P /home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-subbuild/ms_onnx-populate-prefix/src/ms_onnx-populate-stamp/extract-ms_onnx-populate.cmake
	cd /home/geray/mindspore-master/cmake-build-debug/_deps && /usr/bin/cmake -E touch /home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-subbuild/ms_onnx-populate-prefix/src/ms_onnx-populate-stamp/ms_onnx-populate-download

ms_onnx-populate-prefix/src/ms_onnx-populate-stamp/ms_onnx-populate-update: ms_onnx-populate-prefix/src/ms_onnx-populate-stamp/ms_onnx-populate-download
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "No update step for 'ms_onnx-populate'"
	/usr/bin/cmake -E echo_append
	/usr/bin/cmake -E touch /home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-subbuild/ms_onnx-populate-prefix/src/ms_onnx-populate-stamp/ms_onnx-populate-update

ms_onnx-populate-prefix/src/ms_onnx-populate-stamp/ms_onnx-populate-patch: ms_onnx-populate-prefix/src/ms_onnx-populate-stamp/ms_onnx-populate-update
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "No patch step for 'ms_onnx-populate'"
	/usr/bin/cmake -E echo_append
	/usr/bin/cmake -E touch /home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-subbuild/ms_onnx-populate-prefix/src/ms_onnx-populate-stamp/ms_onnx-populate-patch

ms_onnx-populate-prefix/src/ms_onnx-populate-stamp/ms_onnx-populate-configure: ms_onnx-populate-prefix/tmp/ms_onnx-populate-cfgcmd.txt
ms_onnx-populate-prefix/src/ms_onnx-populate-stamp/ms_onnx-populate-configure: ms_onnx-populate-prefix/src/ms_onnx-populate-stamp/ms_onnx-populate-patch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "No configure step for 'ms_onnx-populate'"
	cd /home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-build && /usr/bin/cmake -E echo_append
	cd /home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-build && /usr/bin/cmake -E touch /home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-subbuild/ms_onnx-populate-prefix/src/ms_onnx-populate-stamp/ms_onnx-populate-configure

ms_onnx-populate-prefix/src/ms_onnx-populate-stamp/ms_onnx-populate-build: ms_onnx-populate-prefix/src/ms_onnx-populate-stamp/ms_onnx-populate-configure
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "No build step for 'ms_onnx-populate'"
	cd /home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-build && /usr/bin/cmake -E echo_append
	cd /home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-build && /usr/bin/cmake -E touch /home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-subbuild/ms_onnx-populate-prefix/src/ms_onnx-populate-stamp/ms_onnx-populate-build

ms_onnx-populate-prefix/src/ms_onnx-populate-stamp/ms_onnx-populate-test: ms_onnx-populate-prefix/src/ms_onnx-populate-stamp/ms_onnx-populate-install
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "No test step for 'ms_onnx-populate'"
	cd /home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-build && /usr/bin/cmake -E echo_append
	cd /home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-build && /usr/bin/cmake -E touch /home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-subbuild/ms_onnx-populate-prefix/src/ms_onnx-populate-stamp/ms_onnx-populate-test

ms_onnx-populate: CMakeFiles/ms_onnx-populate
ms_onnx-populate: CMakeFiles/ms_onnx-populate-complete
ms_onnx-populate: ms_onnx-populate-prefix/src/ms_onnx-populate-stamp/ms_onnx-populate-install
ms_onnx-populate: ms_onnx-populate-prefix/src/ms_onnx-populate-stamp/ms_onnx-populate-mkdir
ms_onnx-populate: ms_onnx-populate-prefix/src/ms_onnx-populate-stamp/ms_onnx-populate-download
ms_onnx-populate: ms_onnx-populate-prefix/src/ms_onnx-populate-stamp/ms_onnx-populate-update
ms_onnx-populate: ms_onnx-populate-prefix/src/ms_onnx-populate-stamp/ms_onnx-populate-patch
ms_onnx-populate: ms_onnx-populate-prefix/src/ms_onnx-populate-stamp/ms_onnx-populate-configure
ms_onnx-populate: ms_onnx-populate-prefix/src/ms_onnx-populate-stamp/ms_onnx-populate-build
ms_onnx-populate: ms_onnx-populate-prefix/src/ms_onnx-populate-stamp/ms_onnx-populate-test
ms_onnx-populate: CMakeFiles/ms_onnx-populate.dir/build.make

.PHONY : ms_onnx-populate

# Rule to build all files generated by this target.
CMakeFiles/ms_onnx-populate.dir/build: ms_onnx-populate

.PHONY : CMakeFiles/ms_onnx-populate.dir/build

CMakeFiles/ms_onnx-populate.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ms_onnx-populate.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ms_onnx-populate.dir/clean

CMakeFiles/ms_onnx-populate.dir/depend:
	cd /home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-subbuild && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-subbuild /home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-subbuild /home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-subbuild /home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-subbuild /home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-subbuild/CMakeFiles/ms_onnx-populate.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ms_onnx-populate.dir/depend
