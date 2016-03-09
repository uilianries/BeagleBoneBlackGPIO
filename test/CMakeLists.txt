cmake_minimum_required(VERSION 2.8)

set(GPIO_TEST_APP test_gpio)

include_directories(${CMAKE_INSTALL_PREFIX}/${CMAKE_PROJECT_NAME}/include)

add_executable(${GPIO_TEST_APP}
    test_config.cpp 
    test_gpio.cpp 
    main.cpp)

target_link_libraries(${GPIO_TEST_APP} ${CMAKE_PROJECT_NAME} ${Boost_LIBRARIES})

add_test(${GPIO_TEST_APP} ${GPIO_TEST_APP})

