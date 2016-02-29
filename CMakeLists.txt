cmake_minimum_required(VERSION 2.8)
project(bbbgpio)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -Wshadow -std=c++11")
set(GPIO_TEST_APP test_gpio)

set(SOURCE_FILES
    core.cpp
    direction.cpp
    exception.cpp
    exportation.cpp
    stream.cpp)

add_library(${CMAKE_PROJECT_NAME} STATIC ${SOURCE_FILES})


add_executable(${GPIO_TEST_APP} test_gpio.cpp main.cpp)
target_link_libraries(${GPIO_TEST_APP} ${CMAKE_PROJECT_NAME} gtest gtest_main pthread)
add_test(${GPIO_TEST_APP} ${GPIO_TEST_APP})

