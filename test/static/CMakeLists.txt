cmake_minimum_required(VERSION 2.6)

add_test(static_analysis ${CMAKE_CURRENT_SOURCE_DIR}/static_analysis.sh "${PROJECT_SOURCE_DIR}/src" "${SRC_OUTPUT_PATH}")
