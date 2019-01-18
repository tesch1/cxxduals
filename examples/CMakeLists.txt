

include_directories (${CMAKE_SOURCE_DIR})


add_executable (differentiation differentiation.cpp)
add_executable (printing printing.cpp)
#add_executable (complex complex.cpp)
if (eigenX)
  add_executable (eigen eigen.cpp)
  add_dependencies (eigen eigenX)
endif (eigenX)

