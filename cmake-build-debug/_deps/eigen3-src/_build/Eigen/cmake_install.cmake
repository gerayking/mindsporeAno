# Install script for directory: /home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/Eigen

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eigen3/Eigen" TYPE FILE FILES
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/Eigen/Cholesky"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/Eigen/CholmodSupport"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/Eigen/Core"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/Eigen/Dense"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/Eigen/Eigen"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/Eigen/Eigenvalues"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/Eigen/Geometry"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/Eigen/Householder"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/Eigen/IterativeLinearSolvers"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/Eigen/Jacobi"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/Eigen/LU"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/Eigen/MetisSupport"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/Eigen/OrderingMethods"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/Eigen/PaStiXSupport"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/Eigen/PardisoSupport"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/Eigen/QR"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/Eigen/QtAlignedMalloc"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/Eigen/SPQRSupport"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/Eigen/SVD"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/Eigen/Sparse"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/Eigen/SparseCholesky"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/Eigen/SparseCore"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/Eigen/SparseLU"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/Eigen/SparseQR"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/Eigen/StdDeque"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/Eigen/StdList"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/Eigen/StdVector"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/Eigen/SuperLUSupport"
    "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/Eigen/UmfPackSupport"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eigen3/Eigen" TYPE DIRECTORY FILES "/home/geray/mindspore-master/cmake-build-debug/_deps/eigen3-src/Eigen/src" FILES_MATCHING REGEX "/[^/]*\\.h$")
endif()

