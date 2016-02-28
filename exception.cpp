#include "exception.hpp"

#include <sstream>
#include <string>

namespace bbb {
namespace gpio {

    export_error::export_error(const std::string& path)
        : std::runtime_error(path)
        , path_{ path }
    {
    }

    const char* export_error::what() const throw()
    {
        std::ostringstream oss;
        oss << "Could open export file at " << path_;
        return oss.str().c_str();
    }

    direction_error::direction_error(const std::string& path)
        : std::runtime_error(path)
        , path_{ path }
    {
    }

    const char* direction_error::what() const throw()
    {
        std::ostringstream oss;
        oss << "Could open direction file at " << path_;
        return oss.str().c_str();
    }

    index_error::index_error(size_t index)
        : std::range_error(std::to_string(index))
        , index_(index)
    {
    }

    const char* index_error::what() const throw()
    {
        std::ostringstream oss;
        oss << "Invalid GPIO index: " << index_;
        return oss.str().c_str();
    }

    ostream_error::ostream_error(size_t index)
        : std::runtime_error(std::to_string(index))
        , index_(index)
    {
    }

    const char* ostream_error::what() const throw()
    {
        std::ostringstream oss;
        oss << "Could not open pin output at GPIO " << index_;
        return oss.str().c_str();
    }

    istream_error::istream_error(size_t index)
        : std::runtime_error(std::to_string(index))
        , index_(index)
    {
    }

    const char* istream_error::what() const throw()
    {
        std::ostringstream oss;
        oss << "Could not open pin input at GPIO " << index_;
        return oss.str().c_str();
    }
}
}
