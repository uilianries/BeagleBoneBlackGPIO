#ifndef BBB_GPIO_EXCEPTION_HPP_
#define BBB_GPIO_EXCEPTION_HPP_

#include <stdexcept>
#include <string>

namespace bbb {
namespace gpio {

    class export_error : public std::runtime_error {
    private:
        std::string path_;

    public:
        explicit export_error(const std::string& path);
        virtual const char* what() const throw();
        virtual ~export_error() throw() {}
    };

    class direction_error : public std::runtime_error {
    private:
        std::string path_;

    public:
        explicit direction_error(const std::string& path);
        const char* what() const throw();
        virtual ~direction_error() throw() {}
    };

    class index_error : public std::range_error {
    private:
        size_t index_;

    public:
        explicit index_error(size_t index);
        const char* what() const throw();
    };

    class ostream_error : public std::runtime_error {
    private:
        size_t index_;

    public:
        explicit ostream_error(size_t index);
        const char* what() const throw();
    };

    class istream_error : public std::runtime_error {
    private:
        size_t index_;

    public:
        explicit istream_error(size_t index);
        const char* what() const throw();
    };
}
}

#endif // BBB_GPIO_EXCEPTION_HPP_
