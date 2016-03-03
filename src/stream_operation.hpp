#ifndef BBB_GPIO_STREAM_OPERATION_HPP_
#define BBB_GPIO_STREAM_OPERATION_HPP_

#include <iostream>
#include <type_traits>

namespace bbb {
namespace gpio {

    template <typename T>
    typename std::enable_if<std::is_enum<T>::value, std::ostream&>::type
    operator<<(std::ostream& os, T t)
    {
        os << static_cast<size_t>(t);
        return os;
    }

    template <typename T>
    typename std::enable_if<std::is_enum<T>::value, std::istream&>::type
    operator>>(std::istream& is, T& t)
    {
        size_t value;
        is >> value;
        t = static_cast<T>(value);
        return is;
    }
}
}

#endif // BBB_GPIO_STREAM_OPERATION_HPP_
