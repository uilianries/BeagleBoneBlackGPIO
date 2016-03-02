cmake_minimum_required(VERSION 2.8)

find_package(Boost COMPONENTS filesystem system REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

set(SOURCE_FILES 
    config.cpp 
    core.cpp 
    stream.cpp)

add_library(${CMAKE_PROJECT_NAME} STATIC ${SOURCE_FILES})
target_link_libraries(${GPIO_TEST_APP} ${CMAKE_PROJECT_NAME} ${Boost_LIBRARIES})

