/**
 * \file
 * \brief GPIO pin level
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#ifndef BBB_GPIO_PIN_LEVEL_HPP_
#define BBB_GPIO_PIN_LEVEL_HPP_

#include "stream_operation.hpp"

namespace bbb {
namespace gpio {

    /**
     * \brief GPIO logic level
     */
    enum class pin_level { low,
                           high };
} // namespace gpio
} // namespace bbb

#endif // BBB_GPIO_PIN_LEVEL_HPP_
