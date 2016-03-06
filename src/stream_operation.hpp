/**
 * \file
 * \brief  Overload input/output stream operators
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#ifndef BBB_GPIO_STREAM_OPERATION_HPP_
#define BBB_GPIO_STREAM_OPERATION_HPP_

#include <iostream>
#include <type_traits>

namespace bbb {
namespace gpio {

    /**
     * \brief Receive T data and write in stream
     * \param os stream output to receive data
     * \param t value to be wrote
     * \return GPIO file
     */
    template <typename T>
    typename std::enable_if<std::is_enum<T>::value, std::ostream&>::type
    operator<<(std::ostream& os, T t)
    {
        os << static_cast<size_t>(t);
        return os;
    }

    /**
     * \brief Read data from GPIO stream and save at t
     * \param is GPIO input stream
     * \param t receive data from GPIO
     * \return GPIO file
     */
    template <typename T>
    typename std::enable_if<std::is_enum<T>::value, std::istream&>::type
    operator>>(std::istream& is, T& t)
    {
        size_t value;
        is >> value;
        t = static_cast<T>(value);
        return is;
    }
} // namespace gpio
} // namespace bbb

#endif // BBB_GPIO_STREAM_OPERATION_HPP_
