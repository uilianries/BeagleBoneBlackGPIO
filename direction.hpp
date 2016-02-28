#ifndef BBB_GPIO_DIRECTION_HPP_
#define BBB_GPIO_DIRECTION_HPP_

#include <fstream>
#include <string>

#include "definition.hpp"

namespace bbb {
namespace gpio {
    class direction {
    private:
        std::ofstream direction_fd_;
        stream_direction direction_;

        void init(const std::string& path);

    public:
        direction(const std::string& path, stream_direction direct);
        direction(std::string&& path, stream_direction direct);

        direction(const direction&) = delete;
        direction& operator=(const direction&) = delete;

        void update();
    };
}
}
#endif // BBB_GPIO_DIRECTION_HPP_
