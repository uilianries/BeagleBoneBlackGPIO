/**
 * \file
 * \brief Give DS1820 thermal sensor as stream
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */

#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#include "bbbgpio/stream.hpp"

/**
 * \brief Main
 */
int main()
{
    bbb::gpio::thermal_stream thermal_stream;

    auto limit = std::chrono::steady_clock::now() + std::chrono::seconds(10);

    while (std::chrono::steady_clock::now() <= limit) {
        bbb::gpio::thermal_level_type level;
        thermal_stream >> level;
        std::cout << "TEMPERATURE LEVEL: " << level << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return EXIT_SUCCESS;
}