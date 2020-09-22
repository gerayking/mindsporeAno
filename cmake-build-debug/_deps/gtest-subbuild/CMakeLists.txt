# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.18.2)

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(gtest-populate NONE)

include(ExternalProject)
ExternalProject_Add(gtest-populate
                     "UPDATE_DISCONNECTED" "False" "URL" "https://github.com/google/googletest/archive/release-1.8.0.tar.gz" "URL_HASH" "MD5=16877098823401d1bf2ed7891d7dce36"
                    SOURCE_DIR          "/home/geray/mindspore-master/cmake-build-debug/_deps/gtest-src"
                    BINARY_DIR          "/home/geray/mindspore-master/cmake-build-debug/_deps/gtest-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
)


