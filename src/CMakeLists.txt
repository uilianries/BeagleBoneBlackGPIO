cmake_minimum_required(VERSION 2.8)

find_library(POCO_FOUNDATION PocoFoundation)

file(GLOB SOURCE_FILES 
    *.cpp)

file(GLOB HEADER_FILES
    *.hpp)

add_library(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${CMAKE_PROJECT_NAME} ${Boost_LIBRARIES} ${POCO_FOUNDATION})

install(TARGETS ${CMAKE_PROJECT_NAME} 
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

install(FILES ${HEADER_FILES}
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${CMAKE_PROJECT_NAME})

