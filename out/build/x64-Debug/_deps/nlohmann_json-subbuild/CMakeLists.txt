# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.14.19050301-MSVC_2)

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(nlohmann_json-populate NONE)

include(ExternalProject)
ExternalProject_Add(nlohmann_json-populate
                     "UPDATE_DISCONNECTED" "False" "URL" "https://github.com/nlohmann/json/releases/download/v3.6.1/include.zip" "URL_HASH" "MD5=0dc903888211db3a0f170304cd9f3a89"
                    SOURCE_DIR          "D:/Mindspore/mindspore-master/out/build/x64-Debug/_deps/nlohmann_json-src"
                    BINARY_DIR          "D:/Mindspore/mindspore-master/out/build/x64-Debug/_deps/nlohmann_json-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
)
