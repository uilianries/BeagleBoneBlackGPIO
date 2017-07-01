cmake_minimum_required(VERSION 2.8)
project(bbbgpio-test CXX)

# Verbose mode #################################################################
set(CMAKE_VERBOSE_MAKEFILE ON)

# Conan packages ###############################################################
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(BUILD_FLAGS "-std=c++11 -pedantic -Wall -Wextra -Wdisabled-optimization -Wformat=2 -Winit-self -Wmissing-include-dirs -Wsign-promo -Werror -Wno-unused")

file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${CMAKE_PROJECT_NAME} ${CONAN_LIBS})
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES COMPILE_FLAGS ${BUILD_FLAGS})


# Test application #############################################################
enable_testing()
add_test(NAME test-all
         WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
         COMMAND ${CMAKE_PROJECT_NAME})
