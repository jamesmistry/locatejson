cmake_minimum_required(VERSION 2.6)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/src)

set (EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB test_src *.cpp)
file(GLOB_RECURSE subject_src ${PROJECT_SOURCE_DIR}/src/*.cpp)
list(REMOVE_ITEM subject_src "${PROJECT_SOURCE_DIR}/src/main.cpp")

add_executable(locatejson_unit_testexe ${subject_src} ${test_src})
target_compile_options(locatejson_unit_testexe PRIVATE ${TEST_CXX_FLAGS})

target_link_libraries(locatejson_unit_testexe gtest gtest_main pthread)

add_test(locatejson_unit_testexe ${CMAKE_CURRENT_SOURCE_DIR}/locatejson_unit_testexe)
