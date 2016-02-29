cmake_minimum_required(VERSION 2.8)

set(GPIO_TEST_APP test_gpio)

message("DIR IS " ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(${GPIO_TEST_APP} test_gpio.cpp main.cpp)
target_link_libraries(${GPIO_TEST_APP} ${CMAKE_PROJECT_NAME} gtest gtest_main pthread)
add_test(${GPIO_TEST_APP} ${GPIO_TEST_APP})

