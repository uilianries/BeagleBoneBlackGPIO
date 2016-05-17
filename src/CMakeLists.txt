cmake_minimum_required(VERSION 2.8)

find_library(POCO_FOUNDATION PocoFoundation)

file(GLOB SOURCE_FILES 
    *.cpp)

add_library(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${CMAKE_PROJECT_NAME} ${Boost_LIBRARIES} ${POCO_FOUNDATION} pthread)

install(TARGETS ${CMAKE_PROJECT_NAME} 
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
