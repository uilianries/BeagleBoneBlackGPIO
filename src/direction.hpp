#ifndef BBB_GPIO_DIRECTION_HPP_
#define BBB_GPIO_DIRECTION_HPP_

#include <iostream>
#include <unordered_map>
#include <string>

#include "definition.hpp"
#include "file_descriptor.hpp"
#include "stream_direction.hpp"

namespace bbb {
namespace gpio {

    using direction = ofile_descriptor<stream_direction>;

    struct direction_hash {
        template <typename T>
        std::size_t operator()(T t) const
        {
            return static_cast<std::size_t>(t);
        }
    };

    std::ostream& operator<<(std::ostream& os, stream_direction stream)
    {
        using stream_direction_map = std::unordered_map<stream_direction, std::string, direction_hash>;

        static const stream_direction_map sd_map = {
            { stream_direction::input, "in" },
            { stream_direction::output, "out" },
            { stream_direction::bidirectional, "not_supported" }
        };

        os << sd_map.at(stream);
        return os;
    }
}
}
#endif // BBB_GPIO_DIRECTION_HPP_
