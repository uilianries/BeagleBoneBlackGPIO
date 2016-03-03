#ifndef BBB_GPIO_STREAM_HPP_
#define BBB_GPIO_STREAM_HPP_

#include "file_descriptor.hpp"
#include "definition.hpp"
#include "core.hpp"
#include "pin_level.hpp"

namespace bbb {
namespace gpio {

    class ostream : public core, public ofile_descriptor<pin_level> {
    public:
        explicit ostream(unsigned index);

        ostream(const ostream&) = delete;
        ostream& operator=(const ostream&) = delete;

        ostream& operator<<(pin_level level);
    };

    class istream : public core, public ifile_descriptor<pin_level> {
    public:
        explicit istream(unsigned index);

        istream(const istream&) = delete;
        istream& operator=(const istream&) = delete;

        istream& operator>>(pin_level& level);
    };
}
}
#endif // BBB_GPIO_STREAM_HPP_
