/**
 * \file
 * \brief Sample code for read an analog pin.
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#include <iostream>
#include <cstdlib>

#include "bbbgpio/stream.hpp"
#include "bbbgpio/pin_level.hpp"
#include "bbbgpio/string.hpp"
#include "pinoption.hpp"

/**
 * \brief Start read analog sample
 * \param argc arguments list size
 * \param argv arguments list data
 * \return program result
 */
int main(int argc, char* argv[])
{
    auto ipin = bbb::sample::parse_gpio(argc, argv);

    bbb::gpio::analog_istream igpio(ipin);

    bbb::gpio::analog_level lvl;

    igpio >> lvl;

    std::cout << "Current status for AN " << ipin
              << ": " << bbb::gpio::to_string(lvl) << std::endl;

    return EXIT_SUCCESS;
}
