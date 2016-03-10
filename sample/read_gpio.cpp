/**
 * \file
 * \brief Sample code for read a GPIO.
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#include <iostream>
#include <cstdlib>

#include "stream.hpp"
#include "pin_level.hpp"
#include "pinoption.hpp"

/**
 * \brief Start read GPIO sample
 * \param argc arguments list size
 * \param argv arguments list data
 * \return program result
 */
int main(int argc, char* argv[])
{
    auto ipin = bbb::sample::parse_gpio(argc, argv);

    bbb::gpio::istream igpio(ipin);

    bbb::gpio::pin_level lvl;

    igpio >> lvl;

    std::cout << "Current status for GPIO " << ipin
              << ": " << (bbb::gpio::any(lvl) ? "high" : "low") << std::endl;

    return EXIT_SUCCESS;
}
