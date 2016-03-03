/**
 * \file
 * \brief Load gpio library configuration
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#ifndef BBB_GPIO_CONFIG_HPP_
#define BBB_GPIO_CONFIG_HPP_

#include <memory>
#include <boost/filesystem.hpp>

namespace bbb {
namespace gpio {

    /** Default name for settings file */
    static const boost::filesystem::path SETTINGS_FILE_PATH = "bbbgpio.conf";

    /**
     * \brief Load settings from config file, parse data to internal
     *        path, as gpio-path-dir (aka /sys/class/gpio). After parse
     *        data, load each file address to a single path.
     */
    class config {
    private:
        boost::filesystem::path gpio_dir_; /**< gpio class directory */
        boost::filesystem::path export_path_; /**< gpio export file path */
        boost::filesystem::path unexport_path_; /**< gpio unexport file path */
        boost::filesystem::path direction_path_; /**< gpio direction flow file path */
        boost::filesystem::path value_path_; /**< gpio value level file path */

        /**
         * \brief Fill all members path, beased on gpio class dir and gpio index
         * \param gpio_class_dir gpio class directory path
         * \param gpio_index gpio index
         */
        void fill_gpio_path(const boost::filesystem::path gpio_class_dir, unsigned gpio_index) noexcept;

    public:
        /**
         * \brief Create config object and assign gpio path
         *        The pin index will be used by core, to give access with
         *        hardware pin. Config does not create gpio access, just
         *        give a pesudo path to gpio core.
         *        The settings file must exists, otherwise, a exception will
         *        be released.
         * \param config_file_path gpio settings file
         * \param gpio_index index to export for gpio
         */
        config(boost::filesystem::path config_file_path, unsigned gpio_index);

        /**
         * \brief Get gpio export file path
         * \return gpio export data member
         */
        boost::filesystem::path get_export() const noexcept;

        /**
         * \brief Get gpio unexport file path
         * \return gpio unexport data member
         */
        boost::filesystem::path get_unexport() const noexcept;

        /**
         * \brief Get gpio direction flow file path
         * \return gpio direction data member
         */
        boost::filesystem::path get_direction() const noexcept;

        /**
         * \brief Get gpio value file path
         * \return gpio value data member
         */
        boost::filesystem::path get_value() const noexcept;
    };
} // namespace gpio
} // namespace bbb

#endif // BBB_GPIO_CONFIG_HPP_
