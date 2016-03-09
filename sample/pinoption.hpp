/**
 * \file
 * \brief Load pin option from command argument.
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#ifndef BBBGPIO_SAMPLE_PINOPTION_HPP_
#define BBBGPIO_SAMPLE_PINOPTION_HPP_

#include <sstream>
#include <stdexcept>
#include <exception>

#include <boost/program_options.hpp>

namespace bbb {
namespace sample {

    /**
 * \brief Parse GPIO index from input options
 * \param argc arguments amount
 * \param argv arguments list
 * \return gpio index
 */
    static unsigned parse_gpio(int argc, char* argv[]) noexcept(false)
    {
        namespace po = boost::program_options;
        const std::string pin_option("pin");
        unsigned gpio_pin = 0;

        po::options_description opt_description("BBBGPIO Read Pin Sample");
        opt_description.add_options()(pin_option.c_str(), po::value<decltype(gpio_pin)>(), "GPIO pin index to read");

        po::variables_map var_map;
        try {
            po::store(po::command_line_parser(argc, argv).options(opt_description).run(), var_map);

            if (!var_map.count(pin_option)) {
                throw std::runtime_error("Option --pin is needed");
            }

            gpio_pin = var_map[pin_option].as<decltype(gpio_pin)>();
            po::notify(var_map);
        }
        catch (const std::exception& e) {
            std::ostringstream oss;
            oss << "ERROR: Could not parse command line: " << e.what();
            throw std::runtime_error(oss.str());
        }

        return gpio_pin;
    }

} // namespace sample
} // namespace bbb

#endif // BBBGPIO_SAMPLE_PINOPTION_HPP_
