/**
 * \file
 * \brief GPIO pin level
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#ifndef BBB_GPIO_PIN_LEVEL_HPP_
#define BBB_GPIO_PIN_LEVEL_HPP_

#include <type_traits>
#include <utility>

#include "stream_operation.hpp"

namespace bbb {
namespace gpio {

    /**
     * \brief GPIO logic level
     */
    enum class pin_level { low,
        high };

    /**
     * \brief Prototype enum class traits
     */
    template <typename enum_class_type>
    struct enum_class_traits {
    };

    /**
     * \brief Specify traits for pin_level rvalue-reference
     */
    template <>
    struct enum_class_traits<pin_level> {
        /** to be trait as boolean */
        static constexpr bool has_any = true;
    };

    /**
     * \brief Specify traits for pin_level lvalue-reference
     */
    template <>
    struct enum_class_traits<pin_level&> {
        /** to be trait as boolean */
        static constexpr bool has_any = true;
    };

    /**
     * \brief Traits pin_level as bool (SFINAE)
     * \param lvl pin level to be treated
     * \return true if pin_level::high; false, otherwise.
     */
    template <typename enum_class_type>
    typename std::enable_if<enum_class_traits<enum_class_type>::has_any, bool>::type
    any(enum_class_type lvl)
    {
        return lvl == enum_class_type::high;
    }
} // namespace gpio
} // namespace bbb

#endif // BBB_GPIO_PIN_LEVEL_HPP_
