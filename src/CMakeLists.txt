cmake_minimum_required(VERSION 2.8)

file(GLOB SOURCE_FILES *.cpp)

set(BUILD_FLAGS "-coverage -std=c++11 -pedantic -Wall -Wextra -Wdisabled-optimization -Wformat=2 -Winit-self -Wmissing-include-dirs -Wsign-promo -Werror -Wno-unused")

add_library(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${CMAKE_PROJECT_NAME} ${CONAN_LIBS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ")
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES COMPILE_FLAGS ${BUILD_FLAGS})

install(TARGETS ${CMAKE_PROJECT_NAME}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
