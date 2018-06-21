
# gtest install
set (GTESTVER 1.8.0)
add_custom_command (OUTPUT "googletest-release-${GTESTVER}/googletest/src/gtest-all.cc"
  COMMAND rm -f release-${GTESTVER}.tar.gz
  COMMAND rm -fR googletest-release-${GTESTVER}
  COMMAND wget https://github.com/google/googletest/archive/release-${GTESTVER}.tar.gz
  COMMAND tar xzvf release-${GTESTVER}.tar.gz
  )
include_directories (${CMAKE_CURRENT_BINARY_DIR}/googletest-release-${GTESTVER}/googletest/include)
include_directories (${CMAKE_CURRENT_BINARY_DIR}/googletest-release-${GTESTVER}/googletest)
add_library (gtest "googletest-release-${GTESTVER}/googletest/src/gtest-all.cc")
target_link_libraries (gtest pthread)

# where to find cxxduals/dual
include_directories (${CMAKE_SOURCE_DIR}/)

# test binaries
add_executable (test1 test1.cpp)
target_link_libraries (test1 gtest)

add_executable (test2 test2.cpp)
target_link_libraries (test2 gtest)

# individual tests
add_test (basic test1)
add_test (differentials test2)

# CUDA
if (CUDA_FOUND)
  cuda_add_executable (cudatest1 cudatest1.cu)
  target_link_libraries (cudatest1 gtest)
  add_test (basicCUDA cudatest1)
endif (CUDA_FOUND)

