/**
 * \file
 * \brief Control GPIO flow direction
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#ifndef BBB_GPIO_DIRECTION_HPP_
#define BBB_GPIO_DIRECTION_HPP_

#include <iostream>
#include <unordered_map>
#include <string>

#include "file_descriptor.hpp"
#include "stream_direction.hpp"

namespace bbb {
namespace gpio {

    /**
     * \brief Open direction GPIO and write the stream
     */
    using direction = ofile_descriptor<stream_direction>;

    /**
     * \brief Solve hash for enum  class
     */
    struct direction_hash {
        /**
         * \brief Extract hash value from enum class
         * \param t enum class variable to be check
         * \return hash value
         */
        template <typename T>
        std::size_t operator()(T t) const
        {
            return static_cast<std::size_t>(t);
        }
    };

    /**
     * \brief Overload stream output operator, to solve direction enum class
     * \param os output stream to receive the stream
     * \param stream GPIO direction
     * \return own os
     */
    std::ostream& operator<<(std::ostream& os, stream_direction stream)
    {
        using stream_direction_map = std::unordered_map<stream_direction, std::string, direction_hash>;

        static const stream_direction_map sd_map = {
            { stream_direction::input, "in" },
            { stream_direction::output, "out" }
        };

        os << sd_map.at(stream);
        return os;
    }
} // namespace gpio
} // namespace bbb
#endif // BBB_GPIO_DIRECTION_HPP_
