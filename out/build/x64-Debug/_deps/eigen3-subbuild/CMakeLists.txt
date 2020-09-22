# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.14.19050301-MSVC_2)

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(eigen3-populate NONE)

include(ExternalProject)
ExternalProject_Add(eigen3-populate
                     "UPDATE_DISCONNECTED" "False" "URL" "https://gitlab.com/libeigen/eigen/-/archive/3.3.7/eigen-3.3.7.tar.gz" "URL_HASH" "MD5=9e30f67e8531477de4117506fe44669b"
                    SOURCE_DIR          "D:/Mindspore/mindspore-master/out/build/x64-Debug/_deps/eigen3-src"
                    BINARY_DIR          "D:/Mindspore/mindspore-master/out/build/x64-Debug/_deps/eigen3-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
)
