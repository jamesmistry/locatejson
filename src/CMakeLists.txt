cmake_minimum_required (VERSION 2.6)

configure_file (
  "${CMAKE_SOURCE_DIR}/src/appConfig.h.in"
  "${CMAKE_BINARY_DIR}/appConfig.h"
  )

include_directories("${CMAKE_SOURCE_DIR}/src")
include_directories("${CMAKE_BINARY_DIR}")

file(GLOB_RECURSE src_files ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(locatejson ${src_files})

