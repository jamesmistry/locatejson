cmake_minimum_required (VERSION 2.6)

configure_file (
  "${CMAKE_SOURCE_DIR}/src/appConfig.h.in"
  "${SRC_OUTPUT_PATH}/appConfig.h"
)

include_directories("${CMAKE_SOURCE_DIR}/src")
include_directories("${SRC_OUTPUT_PATH}")

file(GLOB_RECURSE src_files ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(locatejson ${src_files})
target_compile_options(locatejson PRIVATE ${PRODUCT_CXX_FLAGS})
set_target_properties(locatejson PROPERTIES LINK_FLAGS "-fPIE -pie -z now")
