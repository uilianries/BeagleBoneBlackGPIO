/**
 * \file
 * \brief Give GPIO as stream in analog level
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#ifndef BBB_GPIO_ANALOG_STREAM_HPP_
#define BBB_GPIO_ANALOG_STREAM_HPP_

#include "bbbgpio/basic_stream.hpp"
#include "bbbgpio/analog_core.hpp"
#include "bbbgpio/pin_level.hpp"

namespace bbb {
namespace gpio {

    /** Specialized analog output stream */
    using analog_ostream = bbb::gpio::ostream<analog_core, analog_level>;
    /** Specialized analog input stream */
    using analog_istream = bbb::gpio::istream<analog_core, analog_level>;

} // namespace gpio
} // namespace bbb

#endif // BBB_GPIO_ANALOG_STREAM_HPP_
