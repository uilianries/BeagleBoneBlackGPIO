#include "exportation.hpp"

#include <utility>

#include "exception.hpp"

namespace bbb {
namespace gpio {

    exportation::exportation(const std::string& path, size_t index)
        : export_fd_(path)
    {
        init(path, index);
    }

    exportation::exportation(std::string&& path, size_t index)
        : export_fd_(std::move(path))
    {
        init(path, index);
    }

    void exportation::init(const std::string& ss, size_t index)
    {
        if (!export_fd_) {
            throw export_error(ss);
        }
        push(index);
    }

    void exportation::push(size_t index)
    {
        export_fd_ << index;
        export_fd_.flush();
    }
}
}
