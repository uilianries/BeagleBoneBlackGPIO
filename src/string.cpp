/**
 * \file
 * \brief  String operation for BBBGPIO format
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */

#include "bbbgpio/string.hpp"
#include <unordered_map>

namespace bbb {
namespace gpio {

    /**
     * \brief Generate hash for level
     */
    struct pin_level_hash {
        template <class T>
        /**
         * \brief generate hash for type T
         * \param t to be hashed
         * \return hash value
         */
        std::size_t operator()(T t) const
        {
            return static_cast<std::size_t>(t);
        }
    };

    std::string to_string(pin_level level)
    {
        using pin_level_string_mapped = std::unordered_map<pin_level, std::string, pin_level_hash>;
        static const pin_level_string_mapped mapped_level = {
            { pin_level::high, "high" },
            { pin_level::low, "low" }
        };

        return mapped_level.at(level);
    }

    std::string to_string(analog_level level)
    {
        return std::to_string(level);
    }

} // namespace gpio
} // namespace bbb
