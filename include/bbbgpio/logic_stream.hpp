/**
 * \file
 * \brief Give GPIO as stream in logic level
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#ifndef BBB_GPIO_LOGIC_STREAM_HPP_
#define BBB_GPIO_LOGIC_STREAM_HPP_

#include "bbbgpio/basic_stream.hpp"
#include "bbbgpio/pin_level.hpp"

namespace bbb {
namespace gpio {

    /** Logic output stream type */
    using logic_ostream = bbb::gpio::ostream<pin_level>;
    /** Logic input stream type */
    using logic_istream = bbb::gpio::istream<pin_level>;

} // namespace gpio
} // namespace bbb

#endif // BBB_GPIO_LOGIC_STREAM_HPP_
