cmake_minimum_required(VERSION 2.8)
project("mock_${CMAKE_PROJECT_NAME}" CXX)

find_library(POCO_FOUNDATION PocoFoundation)

file(GLOB SOURCE_FILES 
    *.cpp
    src/basic_stream.cpp
    src/config.cpp
    src/core.cpp
    src/string.cpp
    src/thermal_stream.cpp)

add_library(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${POCO_FOUNDATION} pthread)

install(TARGETS ${PROJECT_NAME}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
