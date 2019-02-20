
#
# CMake for cxxduals
#
cmake_minimum_required (VERSION 3.0)

# Default build mode
if (NOT CMAKE_BUILD_TYPE)
  set (CMAKE_BUILD_TYPE "RelWithDebInfo")
endif (NOT CMAKE_BUILD_TYPE)

#
# Project Name
#
project (cxxduals CXX)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wpedantic")
set (CMAKE_CXX_STANDARD 11)

find_package (CUDA)
if (CUDA_FOUND)
  set (CUDA_HOST_COMPILER ${CMAKE_CXX_COMPILER})
  set (CUDA_PROPAGATE_HOST_FLAGS OFF)
  set (CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} -std=c++11 --compiler-options -Wall -g")

  #LIST(APPEND CUDA_NVCC_FLAGS -gencode arch=compute_20,code=sm_20)
  LIST(APPEND CUDA_NVCC_FLAGS -gencode arch=compute_30,code=sm_30)
  #LIST(APPEND CUDA_NVCC_FLAGS -gencode arch=compute_35,code=sm_35)
  #LIST(APPEND CUDA_NVCC_FLAGS -gencode arch=compute_37,code=sm_37)
  #LIST(APPEND CUDA_NVCC_FLAGS -gencode arch=compute_50,code=sm_50)
  #LIST(APPEND CUDA_NVCC_FLAGS -gencode arch=compute_52,code=sm_52)
endif (CUDA_FOUND)

include (ExternalProject)

#
# Eigen
#
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wno-int-in-bool-context") ## REMOVE WITH EIGEN 3.3.5 ##
endif ()
ExternalProject_Add (eigenX
  PREFIX eigenX
  URL http://bitbucket.org/eigen/eigen/get/3.3.7.tar.bz2
  URL_HASH MD5=05b1f7511c93980c385ebe11bd3c93fa
  DOWNLOAD_DIR "$ENV{HOME}/Downloads"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  LOG_DOWNLOAD ON
  )
ExternalProject_Get_Property (eigenX source_dir)
set (EIGEN3_INCLUDE_DIRS "${source_dir}")
include_directories ("${EIGEN3_INCLUDE_DIRS}")


enable_testing ()
include (CTest)
add_subdirectory (tests)
add_subdirectory (examples)

configure_file (${CMAKE_SOURCE_DIR}/doc/Doxyfile.in ${CMAKE_BINARY_DIR}/doc/Doxyfile)
add_custom_target (docs
  COMMAND rm -f docs/*
  COMMAND cd doc && VERSION=1 doxygen Doxyfile
  )
