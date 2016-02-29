cmake_minimum_required(VERSION 2.8)

set(SOURCE_FILES
    core.cpp
    direction.cpp
    exception.cpp
    exportation.cpp
    stream.cpp)

add_library(${CMAKE_PROJECT_NAME} STATIC ${SOURCE_FILES})
