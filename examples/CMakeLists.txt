

include_directories (${CMAKE_SOURCE_DIR})
include (ExternalProject)

#
# Eigen
#
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wno-int-in-bool-context") ## REMOVE WITH EIGEN 3.3.5 ##
endif ()
ExternalProject_Add (eigenX
  PREFIX eigenX
  URL http://bitbucket.org/eigen/eigen/get/3.3.4.tar.bz2
  URL_HASH MD5=a7aab9f758249b86c93221ad417fbe18
  DOWNLOAD_DIR "$ENV{HOME}/Downloads"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  LOG_DOWNLOAD ON
  )
ExternalProject_Get_Property (eigenX source_dir)
set (EIGEN3_INCLUDE_DIRS "${source_dir}")
include_directories ("${EIGEN3_INCLUDE_DIRS}")


add_executable (differentiation differentiation.cpp)
add_executable (printing printing.cpp)
add_executable (complex complex.cpp)
add_executable (eigen eigen.cpp)

