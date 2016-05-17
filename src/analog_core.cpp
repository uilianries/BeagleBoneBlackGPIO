/**
 * \file
 * \brief Load analog pin core
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */

#include "bbbgpio/analog_core.hpp"

namespace bbb {
namespace gpio {

    analog_core::analog_core(unsigned index, stream_direction direct)
        : config_{ index }
    {
        std::ignore = direct;

        if (index > INDEX_MAX) {
            throw std::runtime_error("Invalid pin index: " + std::to_string(index));
        }
    }

} // namespace gpio
} // namespace bbb