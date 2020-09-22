# Install script for directory: /home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/unsupported/Eigen

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/geray/mindspore-master/cmake-build-debug/.mslib/eigen3_65e827cb6fb06634b86270820ed99f7f")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eigen3/unsupported/Eigen" TYPE FILE FILES
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/unsupported/Eigen/AdolcForward"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/unsupported/Eigen/AlignedVector3"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/unsupported/Eigen/ArpackSupport"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/unsupported/Eigen/AutoDiff"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/unsupported/Eigen/BVH"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/unsupported/Eigen/EulerAngles"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/unsupported/Eigen/FFT"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/unsupported/Eigen/IterativeSolvers"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/unsupported/Eigen/KroneckerProduct"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/unsupported/Eigen/LevenbergMarquardt"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/unsupported/Eigen/MatrixFunctions"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/unsupported/Eigen/MoreVectorization"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/unsupported/Eigen/MPRealSupport"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/unsupported/Eigen/NonLinearOptimization"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/unsupported/Eigen/NumericalDiff"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/unsupported/Eigen/OpenGLSupport"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/unsupported/Eigen/Polynomials"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/unsupported/Eigen/Skyline"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/unsupported/Eigen/SparseExtra"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/unsupported/Eigen/SpecialFunctions"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/unsupported/Eigen/Splines"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eigen3/unsupported/Eigen" TYPE DIRECTORY FILES "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/unsupported/Eigen/src" FILES_MATCHING REGEX "/[^/]*\\.h$")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/_build/unsupported/Eigen/CXX11/cmake_install.cmake")

endif()

