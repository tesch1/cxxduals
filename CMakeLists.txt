
#
# CMake for cxxduals
#
cmake_minimum_required (VERSION 2.6.8)

# Default build mode
if (NOT CMAKE_BUILD_TYPE)
  set (CMAKE_BUILD_TYPE "RelWithDebInfo")
endif (NOT CMAKE_BUILD_TYPE)

#
# Project Name
#
project (cxxduals CXX)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -Wall")

enable_testing ()

add_subdirectory (tests)
