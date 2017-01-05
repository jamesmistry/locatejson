cmake_minimum_required(VERSION 2.6)

add_test(system_valid ${CMAKE_CURRENT_SOURCE_DIR}/run_test.sh "${EXECUTABLE_OUTPUT_PATH}/locatejson" "valid")
add_test(system_invalid ${CMAKE_CURRENT_SOURCE_DIR}/run_test.sh "${EXECUTABLE_OUTPUT_PATH}/locatejson" "invalid")
