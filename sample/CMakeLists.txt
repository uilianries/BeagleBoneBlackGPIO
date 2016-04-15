cmake_minimum_required(VERSION 2.8)

set(SOURCE_LIST write_gpio read_gpio event_gpio read_analog write_analog)

include_directories(${CMAKE_SOURCE_DIR}/src)

foreach(SOURCE ${SOURCE_LIST})

    add_executable(${SOURCE} ${SOURCE}.cpp)

    target_link_libraries(${SOURCE} ${CMAKE_PROJECT_NAME} ${Boost_LIBRARIES})

    install(TARGETS ${SOURCE}
            DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/${CMAKE_PROJECT_NAME})

endforeach(SOURCE)
