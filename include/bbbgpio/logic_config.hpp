/**
 * \file
 * \brief Load gpio library configuration
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#ifndef BBB_GPIO_LOGIC_CONFIG_HPP_
#define BBB_GPIO_LOGIC_CONFIG_HPP_

#include <memory>
#include <boost/filesystem.hpp>

#include "basic_config.hpp"
#include "pin_level.hpp"

namespace bbb {
namespace gpio {

    /** Default path for GPIO class dir */
    static const boost::filesystem::path GPIO_CLASS_DIR_PATH = "/sys/class/gpio";

    /**
     * Load each file address to a single path.
     */
    template <>
    class config<pin_level> {
    private:
        boost::filesystem::path gpio_dir_; /**< gpio class directory */
        boost::filesystem::path export_path_; /**< gpio export file path */
        boost::filesystem::path unexport_path_; /**< gpio unexport file path */
        boost::filesystem::path direction_path_; /**< gpio direction flow file path */
        boost::filesystem::path value_path_; /**< gpio value level file path */
        boost::filesystem::path gpio_pin_dir_; /**< gpio directory path */

        /**
         * \brief Fill all members path, beased on gpio class dir and gpio index
         * \param gpio_class_dir gpio class directory path
         * \param gpio_index gpio index
         */
        void fill_gpio_path(const boost::filesystem::path gpio_class_dir, unsigned gpio_index) noexcept
        {
            gpio_pin_dir_ = gpio_class_dir / std::string("gpio" + std::to_string(gpio_index));
            export_path_ = gpio_class_dir / "export";
            unexport_path_ = gpio_class_dir / "unexport";
            direction_path_ = gpio_pin_dir_ / "direction";
            value_path_ = gpio_pin_dir_ / "value";
        }

    public:
        /**
         * \brief Create config object and assign gpio path
         *        The pin index will be used by core, to give access with
         *        hardware pin. Config does not create gpio access, just
         *        give a pesudo path to gpio core.
         *        The settings file must exists, otherwise, a exception will
         *        be released.
         * \param gpio_index index to export for gpio
         */
        explicit config(unsigned gpio_index)
        {
            fill_gpio_path(GPIO_CLASS_DIR_PATH, gpio_index);
        }

        /**
         * \brief Get gpio export file path
         * \return gpio export data member
         */
        boost::filesystem::path get_export() const noexcept
        {
            return export_path_;
        }

        /**
         * \brief Get gpio unexport file path
         * \return gpio unexport data member
         */
        boost::filesystem::path get_unexport() const noexcept
        {
            return unexport_path_;
        }

        /**
         * \brief Get gpio direction flow file path
         * \return gpio direction data member
         */
        boost::filesystem::path get_direction() const noexcept
        {
            return direction_path_;
        }

        /**
         * \brief Get gpio value file path
         * \return gpio value data member
         */
        boost::filesystem::path get_value() const noexcept
        {
            return value_path_;
        }
    };
} // namespace gpio
} // namespace bbb

#endif // BBB_GPIO_LOGIC_CONFIG_HPP_
