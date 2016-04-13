/**
 * \file
 * \brief Sample code for write analog value in GPIO
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#include <iostream>
#include <thread>

#include "bbbgpio/stream.hpp"
#include "pinoption.hpp"

/**
 * \brief Start write analog GPIO sample
 * \param argc arguments list size
 * \param argv arguments list data
 * \return program result
 */
int main(int argc, char* argv[])
{
    auto ipin = bbb::sample::parse_gpio(argc, argv);

    bbb::gpio::analog_ostream ogpio(ipin);

    ogpio << 1.0;
    std::cout << "GPIO " << ipin << " is high" << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));

    ogpio << 0.0;
    std::cout << "GPIO " << ipin << " is low" << std::endl;

    return EXIT_SUCCESS;
}
