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
 * \brief Get temperature events
 */
struct observer {
    /**
     * \brief Callback to read the temperature level
     * \param level current temperature
     */
    void operator()(const bbb::gpio::thermal_level_type& level) const
    {
        std::cout << "TEMPERATURE LEVEL: " << level << std::endl;
    }
};

/**
 * \brief Main
 */
int main()
{
    bbb::gpio::thermal_stream thermal_stream;
    observer local_observer;
    thermal_stream.delegate_event(local_observer);

    auto limit = std::chrono::seconds(10);
    std::this_thread::sleep_for(limit);

    return EXIT_SUCCESS;
}