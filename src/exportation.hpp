#ifndef BBB_GPIO_EXPORTATION_HPP_
#define BBB_GPIO_EXPORTATION_HPP_

#include <fstream>
#include <string>

#include "definition.hpp"

namespace bbb {
namespace gpio {
    class exportation {
    private:
        std::ofstream export_fd_;
        size_t index_;
        std::string path_;

        void push(size_t index);
        void init(const std::string& ss, size_t index);
        std::string get_export_path(const std::string& ss) const;

    public:
        exportation(const std::string& path, size_t index);
        exportation(std::string&& path, size_t index);
        ~exportation();

        exportation(const exportation&) = delete;
        exportation& operator=(const exportation&) = delete;
    };
}
}

#endif // BBB_GPIO_EXPORTATION_HPP_
