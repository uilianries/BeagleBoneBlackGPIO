#ifndef BBB_GPIO_CONFIG_HPP_
#define BBB_GPIO_CONFIG_HPP_

#include <fstream>
#include <string>
#include <memory>

#include <boost/filesystem.hpp>

namespace bbb {
namespace gpio {
    class config {
    private:
        boost::filesystem::path gpio_dir_;
        boost::filesystem::path export_path_;
        boost::filesystem::path unexport_path_;
        boost::filesystem::path direction_path_;
        boost::filesystem::path value_path_;

    public:
        config(boost::filesystem::path gpio_dir_path);

        boost::filesystem::path get_export() const noexcept;
        boost::filesystem::path get_unexport() const noexcept;
        boost::filesystem::path get_direction() const noexcept;
        boost::filesystem::path get_value() const noexcept;

        static std::unique_ptr<config> make_config(boost::filesystem::path gpio_dir_path, size_t gpio_pin);
    };
}
}

#endif // BBB_GPIO_CONFIG_HPP_
