#ifndef BBB_GPIO_STREAM_DIRECTION_HPP_
#define BBB_GPIO_STREAM_DIRECTION_HPP_

#include "stream_operation.hpp"

namespace bbb {
namespace gpio {
    enum class stream_direction { input,
                                  output,
                                  bidirectional };

    inline std::ostream& operator<<(std::ostream&, stream_direction);
    inline std::istream& operator>>(std::istream&, stream_direction&);
}
}

#endif // BBB_GPIO_STREAM_DIRECTION_HPP_
