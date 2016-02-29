#include "exportation.hpp"

#include <utility>
#include <string>
#include <sstream>

#include "exception.hpp"

namespace bbb {
namespace gpio {

    exportation::exportation(const std::string& path, size_t index)
        : index_(index)
        , path_(path)
    {
        init(export_file_name, index);
    }

    exportation::exportation(std::string&& path, size_t index)
        : index_(index)
        , path_(std::move(path))
    {
        init(export_file_name, index);
    }

    exportation::~exportation()
    {
        export_fd_.close();
        export_fd_.open(get_export_path(unexport_file_name));

        if (export_fd_) {
            push(index_);
        }
    }

    std::string exportation::get_export_path(const std::string& ss) const
    {
        std::ostringstream oss;
        oss << path_ << "/" << ss;
        return oss.str();
    }

    void exportation::init(const std::string& ss, size_t index)
    {
        export_fd_.open(get_export_path(ss));

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
