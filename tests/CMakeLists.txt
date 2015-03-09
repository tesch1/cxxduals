
# gtest install
add_custom_command (OUTPUT "gtest-1.7.0/src/gtest-all.cc"
  COMMAND rm -f gtest-1.7.0.zip
  COMMAND rm -fR gtest-1.7.0
  COMMAND wget -O gtest-1.7.0.zip https://googletest.googlecode.com/files/gtest-1.7.0.zip
  COMMAND unzip gtest-1.7.0.zip
  COMMAND rm -f gtest-1.7.0.zip
  )
include_directories (${CMAKE_CURRENT_BINARY_DIR}/gtest-1.7.0/include)
include_directories (${CMAKE_CURRENT_BINARY_DIR}/gtest-1.7.0)
add_library (gtest "gtest-1.7.0/src/gtest-all.cc")
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

