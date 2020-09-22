# Install script for directory: D:/Mindspore/mindspore-master/build/_deps/eigen3-src/unsupported/Eigen

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "D:/Mindspore/mindspore-master/build/.mslib/eigen3_cf9dc027223958d2b63ccbc764d7f091")
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

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eigen3/unsupported/Eigen" TYPE FILE FILES
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/unsupported/Eigen/AdolcForward"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/unsupported/Eigen/AlignedVector3"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/unsupported/Eigen/ArpackSupport"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/unsupported/Eigen/AutoDiff"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/unsupported/Eigen/BVH"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/unsupported/Eigen/EulerAngles"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/unsupported/Eigen/FFT"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/unsupported/Eigen/IterativeSolvers"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/unsupported/Eigen/KroneckerProduct"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/unsupported/Eigen/LevenbergMarquardt"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/unsupported/Eigen/MatrixFunctions"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/unsupported/Eigen/MoreVectorization"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/unsupported/Eigen/MPRealSupport"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/unsupported/Eigen/NonLinearOptimization"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/unsupported/Eigen/NumericalDiff"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/unsupported/Eigen/OpenGLSupport"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/unsupported/Eigen/Polynomials"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/unsupported/Eigen/Skyline"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/unsupported/Eigen/SparseExtra"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/unsupported/Eigen/SpecialFunctions"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/unsupported/Eigen/Splines"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eigen3/unsupported/Eigen" TYPE DIRECTORY FILES "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/unsupported/Eigen/src" FILES_MATCHING REGEX "/[^/]*\\.h$")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("D:/Mindspore/mindspore-master/build/_deps/eigen3-src/_build/unsupported/Eigen/CXX11/cmake_install.cmake")

endif()

