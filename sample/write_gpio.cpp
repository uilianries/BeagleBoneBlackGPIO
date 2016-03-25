/**
 * \file
 * \brief Sample code for read a GPIO.
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#include <iostream>
#include <thread>

#include "bbbgpio/stream.hpp"
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

    bbb::gpio::ostream ogpio(ipin);

    ogpio << bbb::gpio::pin_level::high;
    std::cout << "GPIO " << ipin << " is high" << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));

    ogpio << bbb::gpio::pin_level::low;
    std::cout << "GPIO " << ipin << " is low" << std::endl;

    return EXIT_SUCCESS;
}
