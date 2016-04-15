cmake_minimum_required(VERSION 2.8)
project(bbbgpio CXX)

set(bbbgpio_VERSION_MAJOR 1)
set(bbbgpio_VERSION_MINOR 0)

option(TESTS "Generate tests" ON)
option(SAMPLES "Generate samples" ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wmissing-declarations -Wmissing-include-dirs -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused")

configure_file(
    "${PROJECT_SOURCE_DIR}/src/version.hpp.in"
    "${PROJECT_BINARY_DIR}/src/version.hpp")

include_directories("${PROJECT_BINARY_DIR}")
include_directories(include)

find_package(Boost
            COMPONENTS
            unit_test_framework
            program_options
            filesystem
            system
            regex
            signals
            REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

add_subdirectory(include)
add_subdirectory(src)

if (TESTS)
    add_subdirectory(test)
endif()

if (SAMPLES)
    add_subdirectory(sample)
endif()

install(FILES ${PROJECT_BINARY_DIR}/src/version.hpp
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${CMAKE_PROJECT_NAME})
