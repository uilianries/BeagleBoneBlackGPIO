cmake_minimum_required(VERSION 2.8)
project(bbbgpio)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -Wshadow -std=c++11")

add_subdirectory(src)
add_subdirectory(test)
