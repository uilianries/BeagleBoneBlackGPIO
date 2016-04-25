/**
 * \file
 * \brief Load analog library configuration
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */

#ifndef BBBGPIO_ANALOG_CONFIG_HPP
#define BBBGPIO_ANALOG_CONFIG_HPP

#include "config.hpp"

namespace bbb {
namespace gpio {
    /**
     * \brief Analog pinage configuration
     */
    class analog_config : public config {
        /** Analog pin path */
        boost::filesystem::path pin_path_;

    public:
        /**
         * \brief Create analog virtual path
         * \param index pin index to read
         */
        explicit analog_config(unsigned index);

        /**
         * \brief Obtain full pin path
         * \return Pin path
         */
        boost::filesystem::path get_value() const noexcept override;
    };

} // namespace gpio
} // namespace bbb

#endif //BBBGPIO_ANALOG_CONFIG_HPP
