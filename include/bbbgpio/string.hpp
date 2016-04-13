/**
 * \file
 * \brief  String operation for BBBGPIO format
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */

#ifndef BBB_GPIO_STRING_HPP_
#define BBB_GPIO_STRING_HPP_

#include <string>
#include "bbbgpio/pin_level.hpp"

namespace bbb {
namespace gpio {

    /**
 * \brief Convert logic pin level to readable string
 * \param level to be converted
 * \return string format
 */
    std::string to_string(pin_level level);

    /**
 * \brief Convert analog pin level to readable string
 * \param level to be converted
 * \return string format
 */
    std::string to_string(analog_level level);

} // namespace gpio
} // namespace bbb
#endif //BBB_GPIO_STRING_HPP_
