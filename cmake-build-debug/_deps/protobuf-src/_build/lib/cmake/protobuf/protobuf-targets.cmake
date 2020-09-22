# Generated by CMake

if("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" LESS 2.5)
   message(FATAL_ERROR "CMake >= 2.6.0 required")
endif()
cmake_policy(PUSH)
cmake_policy(VERSION 2.6...3.17)
#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Protect against multiple inclusion, which would fail when already imported targets are added once more.
set(_targetsDefined)
set(_targetsNotDefined)
set(_expectedTargets)
foreach(_expectedTarget protobuf::libprotobuf-lite protobuf::libprotobuf protobuf::libprotoc protobuf::protoc)
  list(APPEND _expectedTargets ${_expectedTarget})
  if(NOT TARGET ${_expectedTarget})
    list(APPEND _targetsNotDefined ${_expectedTarget})
  endif()
  if(TARGET ${_expectedTarget})
    list(APPEND _targetsDefined ${_expectedTarget})
  endif()
endforeach()
if("${_targetsDefined}" STREQUAL "${_expectedTargets}")
  unset(_targetsDefined)
  unset(_targetsNotDefined)
  unset(_expectedTargets)
  set(CMAKE_IMPORT_FILE_VERSION)
  cmake_policy(POP)
  return()
endif()
if(NOT "${_targetsDefined}" STREQUAL "")
  message(FATAL_ERROR "Some (but not all) targets in this export set were already defined.\nTargets Defined: ${_targetsDefined}\nTargets not yet defined: ${_targetsNotDefined}\n")
endif()
unset(_targetsDefined)
unset(_targetsNotDefined)
unset(_expectedTargets)


# Create imported target protobuf::libprotobuf-lite
add_library(protobuf::libprotobuf-lite STATIC IMPORTED)

set_target_properties(protobuf::libprotobuf-lite PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "/home/geray/mindspore-master/cmake-build-debug/_deps/protobuf-src/src"
  INTERFACE_LINK_LIBRARIES "-lpthread"
)

# Create imported target protobuf::libprotobuf
add_library(protobuf::libprotobuf STATIC IMPORTED)

set_target_properties(protobuf::libprotobuf PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "/home/geray/mindspore-master/cmake-build-debug/_deps/protobuf-src/src"
  INTERFACE_LINK_LIBRARIES "-lpthread;ZLIB::ZLIB"
)

# Create imported target protobuf::libprotoc
add_library(protobuf::libprotoc STATIC IMPORTED)

set_target_properties(protobuf::libprotoc PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "/home/geray/mindspore-master/cmake-build-debug/_deps/protobuf-src/src"
  INTERFACE_LINK_LIBRARIES "protobuf::libprotobuf"
)

# Create imported target protobuf::protoc
add_executable(protobuf::protoc IMPORTED)

# Import target "protobuf::libprotobuf-lite" for configuration ""
set_property(TARGET protobuf::libprotobuf-lite APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(protobuf::libprotobuf-lite PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "/home/geray/mindspore-master/cmake-build-debug/_deps/protobuf-src/_build/libprotobuf-lite.a"
  )

# Import target "protobuf::libprotobuf" for configuration ""
set_property(TARGET protobuf::libprotobuf APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(protobuf::libprotobuf PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "/home/geray/mindspore-master/cmake-build-debug/_deps/protobuf-src/_build/libprotobuf.a"
  )

# Import target "protobuf::libprotoc" for configuration ""
set_property(TARGET protobuf::libprotoc APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(protobuf::libprotoc PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "/home/geray/mindspore-master/cmake-build-debug/_deps/protobuf-src/_build/libprotoc.a"
  )

# Import target "protobuf::protoc" for configuration ""
set_property(TARGET protobuf::protoc APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(protobuf::protoc PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "/home/geray/mindspore-master/cmake-build-debug/_deps/protobuf-src/_build/protoc-3.8.0.0"
  )

# This file does not depend on other imported targets which have
# been exported from the same project but in a separate export set.

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
cmake_policy(POP)
