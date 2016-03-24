cmake_minimum_required(VERSION 2.8)

file(GLOB HEADER_FILES
    bbbgpio/*.hpp)

install(FILES ${HEADER_FILES}
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${CMAKE_PROJECT_NAME})
