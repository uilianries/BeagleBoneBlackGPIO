/**
 * \file
 * \brief Sample code for read a GPIO.
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#include <iostream>
#include <cstdlib>

#include "bbbgpio/stream.hpp"
#include "bbbgpio/pin_level.hpp"
#include "pinoption.hpp"

static void on_gpio_event(bbb::gpio::pin_level lvl)
{
    std::cout << "Current status for GPIO : "
              << (bbb::gpio::any(lvl) ? "high" : "low") << std::endl;
}

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
    igpio.delegate_event(&on_gpio_event);

    while (true)
        ;

    return EXIT_SUCCESS;
}
