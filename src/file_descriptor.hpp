#ifndef BBB_GPIO_FILE_DESCRIPTOR_HPP_
#define BBB_GPIO_FILE_DESCRIPTOR_HPP_

#include <fstream>
#include <sstream>
#include <boost/filesystem.hpp>

#include "stream_operation.hpp"

namespace bbb {
namespace gpio {

    template <typename F>
    class file_descriptor {
    protected:
        F fs_;

    public:
        file_descriptor(const boost::filesystem::path& file_path)
        {
            fs_.open(file_path.string());
            if (!fs_) {
                std::ostringstream oss;
                oss << "Could not open file path: " << file_path;
                throw std::runtime_error(file_path.string());
            }
        }
    };

    template <typename T>
    class ofile_descriptor : public file_descriptor<std::ofstream> {
    public:
        ofile_descriptor(const boost::filesystem::path& file_path, T t)
            : file_descriptor(file_path)
        {
            push(t);
        }

    protected:
        void push(T t)
        {
            fs_ << t;
            fs_.flush();
        }
    };

    template <typename T>
    class ifile_descriptor : public file_descriptor<std::ifstream> {
    public:
        ifile_descriptor(const boost::filesystem::path& file_path)
            : file_descriptor(file_path)
        {
        }

    protected:
        void pull(T& t)
        {
            fs_.sync();
            fs_ >> t;
        }
    };
}
}

#endif // BBB_GPIO_FILE_DESCRIPTOR_HPP_
