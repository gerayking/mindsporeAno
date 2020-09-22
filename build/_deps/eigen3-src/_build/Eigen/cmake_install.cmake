# Install script for directory: D:/Mindspore/mindspore-master/build/_deps/eigen3-src/Eigen

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eigen3/Eigen" TYPE FILE FILES
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/Eigen/Cholesky"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/Eigen/CholmodSupport"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/Eigen/Core"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/Eigen/Dense"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/Eigen/Eigen"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/Eigen/Eigenvalues"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/Eigen/Geometry"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/Eigen/Householder"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/Eigen/IterativeLinearSolvers"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/Eigen/Jacobi"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/Eigen/LU"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/Eigen/MetisSupport"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/Eigen/OrderingMethods"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/Eigen/PaStiXSupport"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/Eigen/PardisoSupport"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/Eigen/QR"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/Eigen/QtAlignedMalloc"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/Eigen/SPQRSupport"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/Eigen/SVD"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/Eigen/Sparse"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/Eigen/SparseCholesky"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/Eigen/SparseCore"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/Eigen/SparseLU"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/Eigen/SparseQR"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/Eigen/StdDeque"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/Eigen/StdList"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/Eigen/StdVector"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/Eigen/SuperLUSupport"
    "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/Eigen/UmfPackSupport"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eigen3/Eigen" TYPE DIRECTORY FILES "D:/Mindspore/mindspore-master/build/_deps/eigen3-src/Eigen/src" FILES_MATCHING REGEX "/[^/]*\\.h$")
endif()

