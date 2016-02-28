cmake_minimum_required(VERSION 2.8)
project(bbbgpio)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -Wshadow -std=c++0x")

set(SOURCE_FILES
    core.cpp
    direction.cpp
    exception.cpp
    exportation.cpp
    stream.cpp)

add_library(${CMAKE_PROJECT_NAME} STATIC ${SOURCE_FILES})


add_executable(test test_gpio.cpp)
target_link_libraries(test ${CMAKE_PROJECT_NAME})
