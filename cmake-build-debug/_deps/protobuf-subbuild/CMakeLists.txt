# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.18.2)

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(protobuf-populate NONE)

include(ExternalProject)
ExternalProject_Add(protobuf-populate
                     "UPDATE_DISCONNECTED" "False" "URL" "https://github.com/protocolbuffers/protobuf/archive/v3.8.0.tar.gz" "URL_HASH" "MD5=3d9e32700639618a4d2d342c99d4507a"
                    SOURCE_DIR          "/home/geray/mindspore-master/cmake-build-debug/_deps/protobuf-src"
                    BINARY_DIR          "/home/geray/mindspore-master/cmake-build-debug/_deps/protobuf-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
)


