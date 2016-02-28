#include "core.hpp"

#include <sstream>

#include "exception.hpp"

namespace bbb {
namespace gpio {

    core::core(size_t index, stream_direction direct)
        : index_{ index }
    {
        if (index > index_max) {
            throw index_error(index);
        }

        std::ostringstream oss;
        oss << gpio_class_path << "/" << export_file_name;
        exportation_.reset(new exportation(oss.str(), index));

        oss.str("");
        oss << gpio_class_path << "/" << gpio_dir_prefix << index << "/"
            << direction_file_name;
        direction_.reset(new direction(oss.str(), direct));
    }

    core::~core()
    {
        exportation_.reset();
        std::ostringstream oss;
        oss << gpio_class_path << "/" << unexport_file_name;
        exportation(oss.str(), index_);
    }

    std::string core::get_value_path(size_t index)
    {
        std::ostringstream oss;
        oss << gpio_class_path << "/"
            << gpio_dir_prefix << index << "/"
            << value_file_name;
        return oss.str();
    }
}
}
