/**
 * \file
 * \brief Load gpio library configuration
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#include "config.hpp"

#include <utility>
#include <stdexcept>

#include <boost/program_options.hpp>
#include <boost/filesystem/fstream.hpp>

namespace bbb {
namespace gpio {

    /**
     * \brief Store settings options in a structure
     * \param store_to receives parsed options from buffer
     * \return object with settings, as gpio-dir-path
     */
    template <typename T>
    boost::program_options::typed_value<T>* make_value(T* store_to)
    {
        return boost::program_options::value<T>(store_to);
    }

    static boost::filesystem::path load_gpio_dir_path(const boost::filesystem::path& config_file_path)
    {
        using boost::program_options::options_description;
        using boost::program_options::variables_map;
        using boost::program_options::store;
        using boost::program_options::notify;
        using boost::program_options::parse_config_file;

        boost::filesystem::path gpio_dir_path;
        options_description desc("GPIO Options");
        desc.add_options()("gpio-dir-path", make_value(&gpio_dir_path), "System class directory for GPIO");

        variables_map vm;
        std::ifstream settings_file(config_file_path.string());
        if (!settings_file) {
            std::ostringstream oss;
            oss << "Could not open config file: " << config_file_path;
            throw std::runtime_error(oss.str());
        }
        store(parse_config_file(settings_file, desc), vm);
        settings_file.close();
        notify(vm);

        return gpio_dir_path;
    }

    config::config(boost::filesystem::path config_file_path, unsigned gpio_index)
    {
        if (!boost::filesystem::exists(config_file_path)) {
            std::ostringstream oss;
            oss << "Configuration file does not exists: " << config_file_path;
            throw std::runtime_error(oss.str());
        }

        if (!boost::filesystem::is_regular_file(config_file_path)) {
            std::ostringstream oss;
            oss << "Configuration file must be a valid regular file: " << config_file_path;
            throw std::runtime_error(oss.str());
        }

        gpio_dir_ = load_gpio_dir_path(config_file_path);
        fill_gpio_path(gpio_dir_, gpio_index);
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
