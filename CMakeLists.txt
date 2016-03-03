cmake_minimum_required(VERSION 2.8)
project(bbbgpio)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused")

find_package(Boost
            COMPONENTS
            unit_test_framework
            program_options
            filesystem
            system
            REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

add_subdirectory(src)
add_subdirectory(test)
