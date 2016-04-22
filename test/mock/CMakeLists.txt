cmake_minimum_required(VERSION 2.8)
project(test_mock CXX)

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB SOURCE_FILES
        *.cpp
        ../main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} "mock_${CMAKE_PROJECT_NAME}" ${Boost_LIBRARIES})

add_test(${PROJECT_NAME} ${PROJECT_NAME})

