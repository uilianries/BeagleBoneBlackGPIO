#include "stream.hpp"

#include <sstream>
#include <string>

#include "definition.hpp"
#include "exception.hpp"

namespace bbb {
namespace gpio {

#if 0
template <typename SS, typename Except>
    typename std::enable_if<std::is_object<SS>::type, bool>
void load_stream(SS& ss, size_t index)
{
    std::ostringstream oss;
    oss << bbb::gpio::gpio_class_path << "/"
        << bbb::gpio::gpio_dir_prefix << index
        << "/" << bbb::gpio::value_file_name;

    ss.open(oss.str());
    if (!ss.is_open()) {
        throw Except(index);
    }
}
#endif

    ostream::ostream(size_t index)
        : core{ index, stream_direction::output }
    {
        pin_.open(get_value_path(index));
        if (!pin_.is_open()) {
            throw ostream_error(index);
        }
    }

    ostream& ostream::operator<<(pin_level level)
    {
        pin_ << static_cast<int>(level);
        pin_.flush();
        return *this;
    }

    istream::istream(size_t index)
        : core{ index, stream_direction::input }
    {
        pin_.open(get_value_path(index));
        if (!pin_.is_open()) {
            throw ostream_error(index);
        }
    }

    istream& istream::operator>>(pin_level& level)
    {
        int value;
        pin_ >> value;

        level = static_cast<pin_level>(value);

        return *this;
    }
}
}
