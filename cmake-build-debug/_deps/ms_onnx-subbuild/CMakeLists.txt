# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.18.2)

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(ms_onnx-populate NONE)

include(ExternalProject)
ExternalProject_Add(ms_onnx-populate
                     "UPDATE_DISCONNECTED" "False" "URL" "https://github.com/onnx/onnx/releases/download/v1.6.0/onnx-1.6.0.tar.gz" "URL_HASH" "MD5=512f2779d6215d4a36f366b6b9acdf1e"
                    SOURCE_DIR          "/home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-src"
                    BINARY_DIR          "/home/geray/mindspore-master/cmake-build-debug/_deps/ms_onnx-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
)


