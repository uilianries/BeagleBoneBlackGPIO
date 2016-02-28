#include "direction.hpp"

#include <unordered_map>
#include <string>
#include <utility>

#include "definition.hpp"
#include "exception.hpp"

namespace bbb {
namespace gpio {

    struct enum_hash {
        template <typename T>
        inline typename std::enable_if<std::is_enum<T>::value, std::size_t>::type
        operator()(T const value) const
        {
            return static_cast<std::size_t>(value);
        }
    };

    using direction_stringify = std::unordered_map<stream_direction, std::string, enum_hash>;

    static const direction_stringify direction_string = {
        { stream_direction::input, "in" },
        { stream_direction::output, "out" },
        { stream_direction::bidirectional, "not_supported" }
    };

    direction::direction(const std::string& path, stream_direction direct)
        : direction_fd_{ path }
        , direction_{ direct }
    {
        init(path);
    }

    direction::direction(std::string&& path, stream_direction direct)
        : direction_fd_{ std::move(path) }
        , direction_{ direct }
    {
        init(path);
    }

    void direction::init(const std::string& path)
    {
        if (!direction_fd_) {
            throw direction_error(path);
        }
        update();
    }

    void direction::update()
    {
        // direction_fd_ << direction_string.at(direction_);
    }
}
}
