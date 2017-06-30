cmake_minimum_required(VERSION 2.8)
project(bbbgpio CXX)

set(bbbgpio_VERSION_MAJOR 0)
set(bbbgpio_VERSION_MINOR 2)
set(bbbgpio_VERSION_PATCH 0)

option(SAMPLES "Generate samples" OFF)

# Verbose mode ############################################################
set(CMAKE_VERBOSE_MAKEFILE ON)

# Conan packages ##########################################################
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()


configure_file(
    "${PROJECT_SOURCE_DIR}/src/version.hpp.in"
    "${PROJECT_BINARY_DIR}/src/version.hpp")

include_directories("${PROJECT_BINARY_DIR}")
include_directories(include)

add_subdirectory(include)
add_subdirectory(src)

if (SAMPLES)
    add_subdirectory(sample)
endif()

install(FILES ${PROJECT_BINARY_DIR}/src/version.hpp
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${CMAKE_PROJECT_NAME})
