/**
 * \file
 * \brief GPIO flow direction
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#ifndef BBB_GPIO_STREAM_DIRECTION_HPP_
#define BBB_GPIO_STREAM_DIRECTION_HPP_

#include "stream_operation.hpp"

namespace bbb {
namespace gpio {

    /**
     * \brief GPIO stream direction
     */
    enum class stream_direction { input,
                                  output };

    /**
     * \brief Overload GPIO direction by enum class
     * \return GPIO stream file
     */
    inline std::ostream& operator<<(std::ostream&, stream_direction);

    /**
     * \brief Overload GPIO stream direction capture
     * \return GPIO stream file
     */
    inline std::istream& operator>>(std::istream&, stream_direction&);
} // namespace gpio
} // namespace bbb

#endif // BBB_GPIO_STREAM_DIRECTION_HPP_
