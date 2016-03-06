cmake_minimum_required(VERSION 2.8)

set(SOURCE_FILES 
    config.cpp 
    core.cpp 
    stream.cpp)

add_library(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${CMAKE_PROJECT_NAME} ${Boost_LIBRARIES})

