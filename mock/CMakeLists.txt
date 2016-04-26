cmake_minimum_required(VERSION 2.8)
project("mock_${CMAKE_PROJECT_NAME}" CXX)

find_library(POCO_FOUNDATION PocoFoundation)

file(GLOB SOURCE_FILES 
    *.cpp)

set(BBBGPIO_SRC_DIR ${CMAKE_SOURCE_DIR}/src)
include_directories(${BBBGPIO_SRC_DIR})

add_library(${PROJECT_NAME}
        ${SOURCE_FILES}
        ${BBBGPIO_SRC_DIR}/basic_stream.cpp
        ${BBBGPIO_SRC_DIR}/string.cpp
        ${BBBGPIO_SRC_DIR}/thermal_stream.cpp
        ${BBBGPIO_SRC_DIR}/analog_config.cpp
        ${BBBGPIO_SRC_DIR}/logic_config.cpp
        ${BBBGPIO_SRC_DIR}/analog_core.cpp
        ${BBBGPIO_SRC_DIR}/logic_core.cpp)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${POCO_FOUNDATION} pthread)

install(TARGETS ${PROJECT_NAME}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
