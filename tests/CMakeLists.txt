# 3.9 adds support for "GoogleTest" which enumerates the tests inside
# of the code and adds them to ctest.
cmake_minimum_required (VERSION 3.9)

# Configure google-test as a downloadable library.
include (External_GTest.cmake)
include (GoogleTest)

# where to find cxxduals/dual
include_directories (${CMAKE_SOURCE_DIR}/)

# test binaries
add_executable (test1 test1.cpp)
target_link_libraries (test1 ${GTEST_LIBRARY})

add_executable (test2 test2.cpp)
target_link_libraries (test2 ${GTEST_LIBRARY})

# individual tests
gtest_add_tests (TARGET test1)
gtest_add_tests (TARGET test2)

# CUDA
if (CUDA_FOUND)
  cuda_add_executable (cudatest1 cudatest1.cu)
  target_link_libraries (cudatest1 ${GTEST_LIBRARY})
  gtest_add_test (TARGET cudatest1)
endif (CUDA_FOUND)

