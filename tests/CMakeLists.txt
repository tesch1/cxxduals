
# https://gist.github.com/johnb003/65982fdc7a1274fdb023b0c68664ebe4

# 3.10 adds support for "GoogleTest" which enumerates the tests inside
# of the code and adds them to ctest.
#
cmake_minimum_required (VERSION 3.10)

# Configure google-test as a downloadable library.
include (External_GTest.cmake)

# where to find cxxduals/dual
include_directories (${CMAKE_SOURCE_DIR}/)

# test binaries
add_executable (test1 test1.cpp)
add_executable (test2 test2.cpp)
add_executable (test3 test3.cpp)

target_link_libraries (test1 ${GTEST_LIBRARY})
target_link_libraries (test2 ${GTEST_LIBRARY})
target_link_libraries (test3 ${GTEST_LIBRARY})

add_dependencies (test1 eigenX)
add_dependencies (test2 eigenX)
add_dependencies (test3 eigenX)

# individual tests
include (GoogleTest)
gtest_discover_tests (test1 TEST_LIST test1_targets)
gtest_discover_tests (test2 TEST_LIST test2_targets)
gtest_discover_tests (test3 TEST_LIST test3_targets)

# set each target to timeout if not finished within 10 sec
set_tests_properties (${test1_targets} PROPERTIES TIMEOUT 10)
set_tests_properties (${test2_targets} PROPERTIES TIMEOUT 10)
set_tests_properties (${test3_targets} PROPERTIES TIMEOUT 10)
#-ftest-coverage

# CUDA
if (CUDA_FOUND)
  cuda_add_executable (cudatest1 cudatest1.cu)
  target_link_libraries (cudatest1 ${GTEST_LIBRARY})
  gtest_add_test (TARGET cudatest1)
endif (CUDA_FOUND)

