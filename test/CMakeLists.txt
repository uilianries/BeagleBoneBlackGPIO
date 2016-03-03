cmake_minimum_required(VERSION 2.8)

set(GPIO_TEST_APP test_gpio)

find_package(Boost
            COMPONENTS
            unit_test_framework
            program_options
            filesystem
            system
            REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${Boost_INCLUDE_DIR})

add_executable(${GPIO_TEST_APP}
    test_config.cpp 
    main.cpp)

target_link_libraries(${GPIO_TEST_APP} ${CMAKE_PROJECT_NAME} ${Boost_LIBRARIES})

add_test(${GPIO_TEST_APP} ${GPIO_TEST_APP})

