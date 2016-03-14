/**
 * \file
 * \brief Load gpio library configuration
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#include "config.hpp"

namespace bbb {
namespace gpio {

    config::config(unsigned gpio_index)
    {
        fill_gpio_path(GPIO_CLASS_DIR_PATH, gpio_index);
    }

    void config::fill_gpio_path(const boost::filesystem::path gpio_class_dir, unsigned gpio_index) noexcept
    {
        const std::string gpio_pin_dir = "gpio" + std::to_string(gpio_index);

        export_path_ = gpio_class_dir / "export";
        unexport_path_ = gpio_class_dir / "unexport";
        direction_path_ = gpio_class_dir / gpio_pin_dir / "direction";
        value_path_ = gpio_class_dir / gpio_pin_dir / "value";
    }

    boost::filesystem::path config::get_export() const noexcept
    {
        return export_path_;
    }

    boost::filesystem::path config::get_unexport() const noexcept
    {
        return unexport_path_;
    }

    boost::filesystem::path config::get_direction() const noexcept
    {
        return direction_path_;
    }

    boost::filesystem::path config::get_value() const noexcept
    {
        return value_path_;
    }
} // namespace gpio
} // namespace bbb
