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
include mindspore/ccsrc/CMakeFiles/proto_input.dir/depend.make

# Include the progress variables for this target.
include mindspore/ccsrc/CMakeFiles/proto_input.dir/progress.make

# Include the compile flags for this target's objects.
include mindspore/ccsrc/CMakeFiles/proto_input.dir/flags.make

proto/onnx.pb.cc: .mslib/protobuf_4323d9fd41921ec1fa643ede4153ca87/bin/protoc
proto/onnx.pb.cc: proto/onnx.proto
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/geray/mindspore-master/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Running C++ protocol buffer compiler on /home/geray/mindspore-master/cmake-build-debug/proto/onnx.proto"
	cd /home/geray/mindspore-master && /usr/bin/cmake -E make_directory /home/geray/mindspore-master/cmake-build-debug/proto
	cd /home/geray/mindspore-master && /home/geray/mindspore-master/cmake-build-debug/.mslib/protobuf_4323d9fd41921ec1fa643ede4153ca87/bin/protoc -I/home/geray/mindspore-master/cmake-build-debug/proto --cpp_out=/home/geray/mindspore-master/cmake-build-debug/proto /home/geray/mindspore-master/cmake-build-debug/proto/onnx.proto

proto/onnx.pb.h: proto/onnx.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate proto/onnx.pb.h

proto/node_strategy.pb.cc: .mslib/protobuf_4323d9fd41921ec1fa643ede4153ca87/bin/protoc
proto/node_strategy.pb.cc: ../mindspore/ccsrc/utils/node_strategy.proto
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/geray/mindspore-master/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Running C++ protocol buffer compiler on utils/node_strategy.proto"
	cd /home/geray/mindspore-master && /usr/bin/cmake -E make_directory /home/geray/mindspore-master/cmake-build-debug/proto
	cd /home/geray/mindspore-master && /home/geray/mindspore-master/cmake-build-debug/.mslib/protobuf_4323d9fd41921ec1fa643ede4153ca87/bin/protoc -I/home/geray/mindspore-master/mindspore/ccsrc/utils --cpp_out=/home/geray/mindspore-master/cmake-build-debug/proto /home/geray/mindspore-master/mindspore/ccsrc/utils/node_strategy.proto

proto/node_strategy.pb.h: proto/node_strategy.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate proto/node_strategy.pb.h

proto/anf_ir.pb.cc: .mslib/protobuf_4323d9fd41921ec1fa643ede4153ca87/bin/protoc
proto/anf_ir.pb.cc: ../mindspore/ccsrc/utils/anf_ir.proto
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/geray/mindspore-master/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Running C++ protocol buffer compiler on utils/anf_ir.proto"
	cd /home/geray/mindspore-master && /usr/bin/cmake -E make_directory /home/geray/mindspore-master/cmake-build-debug/proto
	cd /home/geray/mindspore-master && /home/geray/mindspore-master/cmake-build-debug/.mslib/protobuf_4323d9fd41921ec1fa643ede4153ca87/bin/protoc -I/home/geray/mindspore-master/mindspore/ccsrc/utils --cpp_out=/home/geray/mindspore-master/cmake-build-debug/proto /home/geray/mindspore-master/mindspore/ccsrc/utils/anf_ir.proto
	cd /home/geray/mindspore-master && /home/geray/mindspore-master/cmake-build-debug/.mslib/protobuf_4323d9fd41921ec1fa643ede4153ca87/bin/protoc -I/home/geray/mindspore-master/mindspore/ccsrc/utils --python_out=/home/geray/mindspore-master/cmake-build-debug/proto /home/geray/mindspore-master/mindspore/ccsrc/utils/anf_ir.proto
	cd /home/geray/mindspore-master && /home/geray/mindspore-master/cmake-build-debug/.mslib/protobuf_4323d9fd41921ec1fa643ede4153ca87/bin/protoc -I/home/geray/mindspore-master/mindspore/ccsrc/utils --python_out=/home/geray/mindspore-master/cmake-build-debug/proto /home/geray/mindspore-master/mindspore/ccsrc/utils/anf_ir.proto
	cd /home/geray/mindspore-master && perl -pi -e "s/import (.+_pb2.*)/from . import \\1/" /home/geray/mindspore-master/cmake-build-debug/proto/anf_ir_pb2.py
	cd /home/geray/mindspore-master && cp /home/geray/mindspore-master/cmake-build-debug/proto/anf_ir_pb2.py /home/geray/mindspore-master/mindspore/train/

proto/anf_ir.pb.h: proto/anf_ir.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate proto/anf_ir.pb.h

proto/anf_ir_pb2.py: proto/anf_ir.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate proto/anf_ir_pb2.py

proto/checkpoint.pb.cc: .mslib/protobuf_4323d9fd41921ec1fa643ede4153ca87/bin/protoc
proto/checkpoint.pb.cc: ../mindspore/ccsrc/utils/checkpoint.proto
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/geray/mindspore-master/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Running C++ protocol buffer compiler on utils/checkpoint.proto"
	cd /home/geray/mindspore-master && /usr/bin/cmake -E make_directory /home/geray/mindspore-master/cmake-build-debug/proto
	cd /home/geray/mindspore-master && /home/geray/mindspore-master/cmake-build-debug/.mslib/protobuf_4323d9fd41921ec1fa643ede4153ca87/bin/protoc -I/home/geray/mindspore-master/mindspore/ccsrc/utils --cpp_out=/home/geray/mindspore-master/cmake-build-debug/proto /home/geray/mindspore-master/mindspore/ccsrc/utils/checkpoint.proto
	cd /home/geray/mindspore-master && /home/geray/mindspore-master/cmake-build-debug/.mslib/protobuf_4323d9fd41921ec1fa643ede4153ca87/bin/protoc -I/home/geray/mindspore-master/mindspore/ccsrc/utils --python_out=/home/geray/mindspore-master/cmake-build-debug/proto /home/geray/mindspore-master/mindspore/ccsrc/utils/checkpoint.proto
	cd /home/geray/mindspore-master && /home/geray/mindspore-master/cmake-build-debug/.mslib/protobuf_4323d9fd41921ec1fa643ede4153ca87/bin/protoc -I/home/geray/mindspore-master/mindspore/ccsrc/utils --python_out=/home/geray/mindspore-master/cmake-build-debug/proto /home/geray/mindspore-master/mindspore/ccsrc/utils/checkpoint.proto
	cd /home/geray/mindspore-master && perl -pi -e "s/import (.+_pb2.*)/from . import \\1/" /home/geray/mindspore-master/cmake-build-debug/proto/checkpoint_pb2.py
	cd /home/geray/mindspore-master && cp /home/geray/mindspore-master/cmake-build-debug/proto/checkpoint_pb2.py /home/geray/mindspore-master/mindspore/train/

proto/checkpoint.pb.h: proto/checkpoint.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate proto/checkpoint.pb.h

proto/checkpoint_pb2.py: proto/checkpoint.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate proto/checkpoint_pb2.py

proto/lineage.pb.cc: .mslib/protobuf_4323d9fd41921ec1fa643ede4153ca87/bin/protoc
proto/lineage.pb.cc: ../mindspore/ccsrc/utils/lineage.proto
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/geray/mindspore-master/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Running C++ protocol buffer compiler on utils/lineage.proto"
	cd /home/geray/mindspore-master && /usr/bin/cmake -E make_directory /home/geray/mindspore-master/cmake-build-debug/proto
	cd /home/geray/mindspore-master && /home/geray/mindspore-master/cmake-build-debug/.mslib/protobuf_4323d9fd41921ec1fa643ede4153ca87/bin/protoc -I/home/geray/mindspore-master/mindspore/ccsrc/utils --cpp_out=/home/geray/mindspore-master/cmake-build-debug/proto /home/geray/mindspore-master/mindspore/ccsrc/utils/lineage.proto
	cd /home/geray/mindspore-master && /home/geray/mindspore-master/cmake-build-debug/.mslib/protobuf_4323d9fd41921ec1fa643ede4153ca87/bin/protoc -I/home/geray/mindspore-master/mindspore/ccsrc/utils --python_out=/home/geray/mindspore-master/cmake-build-debug/proto /home/geray/mindspore-master/mindspore/ccsrc/utils/lineage.proto
	cd /home/geray/mindspore-master && /home/geray/mindspore-master/cmake-build-debug/.mslib/protobuf_4323d9fd41921ec1fa643ede4153ca87/bin/protoc -I/home/geray/mindspore-master/mindspore/ccsrc/utils --python_out=/home/geray/mindspore-master/cmake-build-debug/proto /home/geray/mindspore-master/mindspore/ccsrc/utils/lineage.proto
	cd /home/geray/mindspore-master && perl -pi -e "s/import (.+_pb2.*)/from . import \\1/" /home/geray/mindspore-master/cmake-build-debug/proto/lineage_pb2.py
	cd /home/geray/mindspore-master && cp /home/geray/mindspore-master/cmake-build-debug/proto/lineage_pb2.py /home/geray/mindspore-master/mindspore/train/

proto/lineage.pb.h: proto/lineage.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate proto/lineage.pb.h

proto/lineage_pb2.py: proto/lineage.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate proto/lineage_pb2.py

proto/print.pb.cc: .mslib/protobuf_4323d9fd41921ec1fa643ede4153ca87/bin/protoc
proto/print.pb.cc: ../mindspore/ccsrc/utils/print.proto
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/geray/mindspore-master/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Running C++ protocol buffer compiler on utils/print.proto"
	cd /home/geray/mindspore-master && /usr/bin/cmake -E make_directory /home/geray/mindspore-master/cmake-build-debug/proto
	cd /home/geray/mindspore-master && /home/geray/mindspore-master/cmake-build-debug/.mslib/protobuf_4323d9fd41921ec1fa643ede4153ca87/bin/protoc -I/home/geray/mindspore-master/mindspore/ccsrc/utils --cpp_out=/home/geray/mindspore-master/cmake-build-debug/proto /home/geray/mindspore-master/mindspore/ccsrc/utils/print.proto
	cd /home/geray/mindspore-master && /home/geray/mindspore-master/cmake-build-debug/.mslib/protobuf_4323d9fd41921ec1fa643ede4153ca87/bin/protoc -I/home/geray/mindspore-master/mindspore/ccsrc/utils --python_out=/home/geray/mindspore-master/cmake-build-debug/proto /home/geray/mindspore-master/mindspore/ccsrc/utils/print.proto
	cd /home/geray/mindspore-master && /home/geray/mindspore-master/cmake-build-debug/.mslib/protobuf_4323d9fd41921ec1fa643ede4153ca87/bin/protoc -I/home/geray/mindspore-master/mindspore/ccsrc/utils --python_out=/home/geray/mindspore-master/cmake-build-debug/proto /home/geray/mindspore-master/mindspore/ccsrc/utils/print.proto
	cd /home/geray/mindspore-master && perl -pi -e "s/import (.+_pb2.*)/from . import \\1/" /home/geray/mindspore-master/cmake-build-debug/proto/print_pb2.py
	cd /home/geray/mindspore-master && cp /home/geray/mindspore-master/cmake-build-debug/proto/print_pb2.py /home/geray/mindspore-master/mindspore/train/

proto/print.pb.h: proto/print.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate proto/print.pb.h

proto/print_pb2.py: proto/print.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate proto/print_pb2.py

proto/summary.pb.cc: .mslib/protobuf_4323d9fd41921ec1fa643ede4153ca87/bin/protoc
proto/summary.pb.cc: ../mindspore/ccsrc/utils/summary.proto
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/geray/mindspore-master/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Running C++ protocol buffer compiler on utils/summary.proto"
	cd /home/geray/mindspore-master && /usr/bin/cmake -E make_directory /home/geray/mindspore-master/cmake-build-debug/proto
	cd /home/geray/mindspore-master && /home/geray/mindspore-master/cmake-build-debug/.mslib/protobuf_4323d9fd41921ec1fa643ede4153ca87/bin/protoc -I/home/geray/mindspore-master/mindspore/ccsrc/utils --cpp_out=/home/geray/mindspore-master/cmake-build-debug/proto /home/geray/mindspore-master/mindspore/ccsrc/utils/summary.proto
	cd /home/geray/mindspore-master && /home/geray/mindspore-master/cmake-build-debug/.mslib/protobuf_4323d9fd41921ec1fa643ede4153ca87/bin/protoc -I/home/geray/mindspore-master/mindspore/ccsrc/utils --python_out=/home/geray/mindspore-master/cmake-build-debug/proto /home/geray/mindspore-master/mindspore/ccsrc/utils/summary.proto
	cd /home/geray/mindspore-master && /home/geray/mindspore-master/cmake-build-debug/.mslib/protobuf_4323d9fd41921ec1fa643ede4153ca87/bin/protoc -I/home/geray/mindspore-master/mindspore/ccsrc/utils --python_out=/home/geray/mindspore-master/cmake-build-debug/proto /home/geray/mindspore-master/mindspore/ccsrc/utils/summary.proto
	cd /home/geray/mindspore-master && perl -pi -e "s/import (.+_pb2.*)/from . import \\1/" /home/geray/mindspore-master/cmake-build-debug/proto/summary_pb2.py
	cd /home/geray/mindspore-master && cp /home/geray/mindspore-master/cmake-build-debug/proto/summary_pb2.py /home/geray/mindspore-master/mindspore/train/

proto/summary.pb.h: proto/summary.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate proto/summary.pb.h

proto/summary_pb2.py: proto/summary.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate proto/summary_pb2.py

mindspore/ccsrc/CMakeFiles/proto_input.dir/__/__/proto/onnx.pb.cc.o: mindspore/ccsrc/CMakeFiles/proto_input.dir/flags.make
mindspore/ccsrc/CMakeFiles/proto_input.dir/__/__/proto/onnx.pb.cc.o: proto/onnx.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/geray/mindspore-master/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object mindspore/ccsrc/CMakeFiles/proto_input.dir/__/__/proto/onnx.pb.cc.o"
	cd /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/proto_input.dir/__/__/proto/onnx.pb.cc.o -c /home/geray/mindspore-master/cmake-build-debug/proto/onnx.pb.cc

mindspore/ccsrc/CMakeFiles/proto_input.dir/__/__/proto/onnx.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/proto_input.dir/__/__/proto/onnx.pb.cc.i"
	cd /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/geray/mindspore-master/cmake-build-debug/proto/onnx.pb.cc > CMakeFiles/proto_input.dir/__/__/proto/onnx.pb.cc.i

mindspore/ccsrc/CMakeFiles/proto_input.dir/__/__/proto/onnx.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/proto_input.dir/__/__/proto/onnx.pb.cc.s"
	cd /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/geray/mindspore-master/cmake-build-debug/proto/onnx.pb.cc -o CMakeFiles/proto_input.dir/__/__/proto/onnx.pb.cc.s

mindspore/ccsrc/CMakeFiles/proto_input.dir/__/__/proto/node_strategy.pb.cc.o: mindspore/ccsrc/CMakeFiles/proto_input.dir/flags.make
mindspore/ccsrc/CMakeFiles/proto_input.dir/__/__/proto/node_strategy.pb.cc.o: proto/node_strategy.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/geray/mindspore-master/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object mindspore/ccsrc/CMakeFiles/proto_input.dir/__/__/proto/node_strategy.pb.cc.o"
	cd /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/proto_input.dir/__/__/proto/node_strategy.pb.cc.o -c /home/geray/mindspore-master/cmake-build-debug/proto/node_strategy.pb.cc

mindspore/ccsrc/CMakeFiles/proto_input.dir/__/__/proto/node_strategy.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/proto_input.dir/__/__/proto/node_strategy.pb.cc.i"
	cd /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/geray/mindspore-master/cmake-build-debug/proto/node_strategy.pb.cc > CMakeFiles/proto_input.dir/__/__/proto/node_strategy.pb.cc.i

mindspore/ccsrc/CMakeFiles/proto_input.dir/__/__/proto/node_strategy.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/proto_input.dir/__/__/proto/node_strategy.pb.cc.s"
	cd /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/geray/mindspore-master/cmake-build-debug/proto/node_strategy.pb.cc -o CMakeFiles/proto_input.dir/__/__/proto/node_strategy.pb.cc.s

mindspore/ccsrc/CMakeFiles/proto_input.dir/__/__/proto/anf_ir.pb.cc.o: mindspore/ccsrc/CMakeFiles/proto_input.dir/flags.make
mindspore/ccsrc/CMakeFiles/proto_input.dir/__/__/proto/anf_ir.pb.cc.o: proto/anf_ir.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/geray/mindspore-master/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object mindspore/ccsrc/CMakeFiles/proto_input.dir/__/__/proto/anf_ir.pb.cc.o"
	cd /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/proto_input.dir/__/__/proto/anf_ir.pb.cc.o -c /home/geray/mindspore-master/cmake-build-debug/proto/anf_ir.pb.cc

mindspore/ccsrc/CMakeFiles/proto_input.dir/__/__/proto/anf_ir.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/proto_input.dir/__/__/proto/anf_ir.pb.cc.i"
	cd /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/geray/mindspore-master/cmake-build-debug/proto/anf_ir.pb.cc > CMakeFiles/proto_input.dir/__/__/proto/anf_ir.pb.cc.i

mindspore/ccsrc/CMakeFiles/proto_input.dir/__/__/proto/anf_ir.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/proto_input.dir/__/__/proto/anf_ir.pb.cc.s"
	cd /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/geray/mindspore-master/cmake-build-debug/proto/anf_ir.pb.cc -o CMakeFiles/proto_input.dir/__/__/proto/anf_ir.pb.cc.s

mindspore/ccsrc/CMakeFiles/proto_input.dir/__/__/proto/checkpoint.pb.cc.o: mindspore/ccsrc/CMakeFiles/proto_input.dir/flags.make
mindspore/ccsrc/CMakeFiles/proto_input.dir/__/__/proto/checkpoint.pb.cc.o: proto/checkpoint.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/geray/mindspore-master/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object mindspore/ccsrc/CMakeFiles/proto_input.dir/__/__/proto/checkpoint.pb.cc.o"
	cd /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/proto_input.dir/__/__/proto/checkpoint.pb.cc.o -c /home/geray/mindspore-master/cmake-build-debug/proto/checkpoint.pb.cc

mindspore/ccsrc/CMakeFiles/proto_input.dir/__/__/proto/checkpoint.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/proto_input.dir/__/__/proto/checkpoint.pb.cc.i"
	cd /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/geray/mindspore-master/cmake-build-debug/proto/checkpoint.pb.cc > CMakeFiles/proto_input.dir/__/__/proto/checkpoint.pb.cc.i

mindspore/ccsrc/CMakeFiles/proto_input.dir/__/__/proto/checkpoint.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/proto_input.dir/__/__/proto/checkpoint.pb.cc.s"
	cd /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/geray/mindspore-master/cmake-build-debug/proto/checkpoint.pb.cc -o CMakeFiles/proto_input.dir/__/__/proto/checkpoint.pb.cc.s

mindspore/ccsrc/CMakeFiles/proto_input.dir/__/__/proto/lineage.pb.cc.o: mindspore/ccsrc/CMakeFiles/proto_input.dir/flags.make
mindspore/ccsrc/CMakeFiles/proto_input.dir/__/__/proto/lineage.pb.cc.o: proto/lineage.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/geray/mindspore-master/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object mindspore/ccsrc/CMakeFiles/proto_input.dir/__/__/proto/lineage.pb.cc.o"
	cd /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/proto_input.dir/__/__/proto/lineage.pb.cc.o -c /home/geray/mindspore-master/cmake-build-debug/proto/lineage.pb.cc

mindspore/ccsrc/CMakeFiles/proto_input.dir/__/__/proto/lineage.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/proto_input.dir/__/__/proto/lineage.pb.cc.i"
	cd /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/geray/mindspore-master/cmake-build-debug/proto/lineage.pb.cc > CMakeFiles/proto_input.dir/__/__/proto/lineage.pb.cc.i

mindspore/ccsrc/CMakeFiles/proto_input.dir/__/__/proto/lineage.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/proto_input.dir/__/__/proto/lineage.pb.cc.s"
	cd /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/geray/mindspore-master/cmake-build-debug/proto/lineage.pb.cc -o CMakeFiles/proto_input.dir/__/__/proto/lineage.pb.cc.s

mindspore/ccsrc/CMakeFiles/proto_input.dir/__/__/proto/print.pb.cc.o: mindspore/ccsrc/CMakeFiles/proto_input.dir/flags.make
mindspore/ccsrc/CMakeFiles/proto_input.dir/__/__/proto/print.pb.cc.o: proto/print.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/geray/mindspore-master/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object mindspore/ccsrc/CMakeFiles/proto_input.dir/__/__/proto/print.pb.cc.o"
	cd /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/proto_input.dir/__/__/proto/print.pb.cc.o -c /home/geray/mindspore-master/cmake-build-debug/proto/print.pb.cc

mindspore/ccsrc/CMakeFiles/proto_input.dir/__/__/proto/print.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/proto_input.dir/__/__/proto/print.pb.cc.i"
	cd /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/geray/mindspore-master/cmake-build-debug/proto/print.pb.cc > CMakeFiles/proto_input.dir/__/__/proto/print.pb.cc.i

mindspore/ccsrc/CMakeFiles/proto_input.dir/__/__/proto/print.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/proto_input.dir/__/__/proto/print.pb.cc.s"
	cd /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/geray/mindspore-master/cmake-build-debug/proto/print.pb.cc -o CMakeFiles/proto_input.dir/__/__/proto/print.pb.cc.s

mindspore/ccsrc/CMakeFiles/proto_input.dir/__/__/proto/summary.pb.cc.o: mindspore/ccsrc/CMakeFiles/proto_input.dir/flags.make
mindspore/ccsrc/CMakeFiles/proto_input.dir/__/__/proto/summary.pb.cc.o: proto/summary.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/geray/mindspore-master/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object mindspore/ccsrc/CMakeFiles/proto_input.dir/__/__/proto/summary.pb.cc.o"
	cd /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/proto_input.dir/__/__/proto/summary.pb.cc.o -c /home/geray/mindspore-master/cmake-build-debug/proto/summary.pb.cc

mindspore/ccsrc/CMakeFiles/proto_input.dir/__/__/proto/summary.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/proto_input.dir/__/__/proto/summary.pb.cc.i"
	cd /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/geray/mindspore-master/cmake-build-debug/proto/summary.pb.cc > CMakeFiles/proto_input.dir/__/__/proto/summary.pb.cc.i

mindspore/ccsrc/CMakeFiles/proto_input.dir/__/__/proto/summary.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/proto_input.dir/__/__/proto/summary.pb.cc.s"
	cd /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/geray/mindspore-master/cmake-build-debug/proto/summary.pb.cc -o CMakeFiles/proto_input.dir/__/__/proto/summary.pb.cc.s

# Object files for target proto_input
proto_input_OBJECTS = \
"CMakeFiles/proto_input.dir/__/__/proto/onnx.pb.cc.o" \
"CMakeFiles/proto_input.dir/__/__/proto/node_strategy.pb.cc.o" \
"CMakeFiles/proto_input.dir/__/__/proto/anf_ir.pb.cc.o" \
"CMakeFiles/proto_input.dir/__/__/proto/checkpoint.pb.cc.o" \
"CMakeFiles/proto_input.dir/__/__/proto/lineage.pb.cc.o" \
"CMakeFiles/proto_input.dir/__/__/proto/print.pb.cc.o" \
"CMakeFiles/proto_input.dir/__/__/proto/summary.pb.cc.o"

# External object files for target proto_input
proto_input_EXTERNAL_OBJECTS =

mindspore/ccsrc/libproto_input.a: mindspore/ccsrc/CMakeFiles/proto_input.dir/__/__/proto/onnx.pb.cc.o
mindspore/ccsrc/libproto_input.a: mindspore/ccsrc/CMakeFiles/proto_input.dir/__/__/proto/node_strategy.pb.cc.o
mindspore/ccsrc/libproto_input.a: mindspore/ccsrc/CMakeFiles/proto_input.dir/__/__/proto/anf_ir.pb.cc.o
mindspore/ccsrc/libproto_input.a: mindspore/ccsrc/CMakeFiles/proto_input.dir/__/__/proto/checkpoint.pb.cc.o
mindspore/ccsrc/libproto_input.a: mindspore/ccsrc/CMakeFiles/proto_input.dir/__/__/proto/lineage.pb.cc.o
mindspore/ccsrc/libproto_input.a: mindspore/ccsrc/CMakeFiles/proto_input.dir/__/__/proto/print.pb.cc.o
mindspore/ccsrc/libproto_input.a: mindspore/ccsrc/CMakeFiles/proto_input.dir/__/__/proto/summary.pb.cc.o
mindspore/ccsrc/libproto_input.a: mindspore/ccsrc/CMakeFiles/proto_input.dir/build.make
mindspore/ccsrc/libproto_input.a: mindspore/ccsrc/CMakeFiles/proto_input.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/geray/mindspore-master/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Linking CXX static library libproto_input.a"
	cd /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc && $(CMAKE_COMMAND) -P CMakeFiles/proto_input.dir/cmake_clean_target.cmake
	cd /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/proto_input.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
mindspore/ccsrc/CMakeFiles/proto_input.dir/build: mindspore/ccsrc/libproto_input.a

.PHONY : mindspore/ccsrc/CMakeFiles/proto_input.dir/build

mindspore/ccsrc/CMakeFiles/proto_input.dir/clean:
	cd /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc && $(CMAKE_COMMAND) -P CMakeFiles/proto_input.dir/cmake_clean.cmake
.PHONY : mindspore/ccsrc/CMakeFiles/proto_input.dir/clean

mindspore/ccsrc/CMakeFiles/proto_input.dir/depend: proto/onnx.pb.cc
mindspore/ccsrc/CMakeFiles/proto_input.dir/depend: proto/onnx.pb.h
mindspore/ccsrc/CMakeFiles/proto_input.dir/depend: proto/node_strategy.pb.cc
mindspore/ccsrc/CMakeFiles/proto_input.dir/depend: proto/node_strategy.pb.h
mindspore/ccsrc/CMakeFiles/proto_input.dir/depend: proto/anf_ir.pb.cc
mindspore/ccsrc/CMakeFiles/proto_input.dir/depend: proto/anf_ir.pb.h
mindspore/ccsrc/CMakeFiles/proto_input.dir/depend: proto/anf_ir_pb2.py
mindspore/ccsrc/CMakeFiles/proto_input.dir/depend: proto/checkpoint.pb.cc
mindspore/ccsrc/CMakeFiles/proto_input.dir/depend: proto/checkpoint.pb.h
mindspore/ccsrc/CMakeFiles/proto_input.dir/depend: proto/checkpoint_pb2.py
mindspore/ccsrc/CMakeFiles/proto_input.dir/depend: proto/lineage.pb.cc
mindspore/ccsrc/CMakeFiles/proto_input.dir/depend: proto/lineage.pb.h
mindspore/ccsrc/CMakeFiles/proto_input.dir/depend: proto/lineage_pb2.py
mindspore/ccsrc/CMakeFiles/proto_input.dir/depend: proto/print.pb.cc
mindspore/ccsrc/CMakeFiles/proto_input.dir/depend: proto/print.pb.h
mindspore/ccsrc/CMakeFiles/proto_input.dir/depend: proto/print_pb2.py
mindspore/ccsrc/CMakeFiles/proto_input.dir/depend: proto/summary.pb.cc
mindspore/ccsrc/CMakeFiles/proto_input.dir/depend: proto/summary.pb.h
mindspore/ccsrc/CMakeFiles/proto_input.dir/depend: proto/summary_pb2.py
	cd /home/geray/mindspore-master/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/geray/mindspore-master /home/geray/mindspore-master/mindspore/ccsrc /home/geray/mindspore-master/cmake-build-debug /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc /home/geray/mindspore-master/cmake-build-debug/mindspore/ccsrc/CMakeFiles/proto_input.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : mindspore/ccsrc/CMakeFiles/proto_input.dir/depend

