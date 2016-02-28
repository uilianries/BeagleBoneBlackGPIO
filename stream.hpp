#ifndef BBB_GPIO_STREAM_HPP_
#define BBB_GPIO_STREAM_HPP_

#include <fstream>
#include <utility>

#include "definition.hpp"
#include "core.hpp"

namespace bbb {
namespace gpio {

#if 0
    class stream : public core {
        protected:
            using std::pair<std::

            std::unique_ptr<std::ifstream> input_pin_;
            std::unique_ptr<std::ofstream> output_pin_;

        public:
            explicit stream(size_t index, stream_direction direction
                    = stream_direction::bidirectional);

            stream(const stream&) = delete;
            stream& operator=(const stream&) = delete;

            stream& operator>>(pin_level level);
            stream& operator<<(pin_level level);
    };
#endif

    class ostream : public core {
    private:
        std::ofstream pin_;

    public:
        explicit ostream(size_t index);

        ostream(const ostream&) = delete;
        ostream& operator=(const ostream&) = delete;

        ostream& operator<<(pin_level level);
    };

    class istream : public core {
    private:
        std::ifstream pin_;

    public:
        explicit istream(size_t index);

        istream(const istream&) = delete;
        istream& operator=(const istream&) = delete;

        istream& operator>>(pin_level& level);
    };
}
}
#endif // BBB_GPIO_STREAM_HPP_
