/**
 * \file
 * \brief Open some file and write/read on start
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#ifndef BBB_GPIO_FILE_DESCRIPTOR_HPP_
#define BBB_GPIO_FILE_DESCRIPTOR_HPP_

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <boost/filesystem.hpp>

#include "stream_operation.hpp"

namespace bbb {
namespace gpio {

    /**
     * \brief Open some stream (out/in) and check
     */
    template <typename F>
    class file_descriptor {
    protected:
        F fs_; /**< Stream to be treated */

    public:
        /**
         * \brief Open file path and check if is valid
         * \param file_path file path to be opened
         */
        explicit file_descriptor(const boost::filesystem::path& file_path)
        {
            fs_.open(file_path.string());
            if (!fs_) {
                std::ostringstream oss;
                oss << "Could not open file path: " << file_path;
                throw std::runtime_error(file_path.string());
            }
        }
    };

    /**
     * \brief Open a file as stream output and write some data
     */
    template <typename T>
    class ofile_descriptor : public file_descriptor<std::ofstream> {
    public:
        /**
         * \brief Open file path, as ostream, and write T data
         * \param file_path regular file path to be write
         * \param t data to be write in ostream
         */
        ofile_descriptor(const boost::filesystem::path& file_path, T t)
            : file_descriptor(file_path)
        {
            push(t);
        }

    protected:
        /**
         * \brief Write some data in file and sync
         * \param t data to be write
         */
        void push(T t)
        {
            if (!fs_) {
                throw std::runtime_error("Could not write in file");
            }
            fs_ << t;
            fs_.flush();
        }
    };

    /**
     * \brief Open a stream file to input mode
     */
    template <typename T>
    class ifile_descriptor : public file_descriptor<std::ifstream> {
    public:
        /**
         * \brief Wrapper to ifstream
         * \param file_path Path to be read
         */
        explicit ifile_descriptor(const boost::filesystem::path& file_path)
            : file_descriptor(file_path)
        {
        }

    protected:
        /**
         * \brief Sync and read t from file stream
         * \param t variable to receive file stream
         */
        void pull(T& t)
        {
            fs_.seekg(0, fs_.beg);
            if (!fs_) {
                throw std::runtime_error("Could not read file");
            }

            fs_ >> t;
        }
    };
} // namespace gpio
} // namespace bbb

#endif // BBB_GPIO_FILE_DESCRIPTOR_HPP_
