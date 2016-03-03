#include "config.hpp"

#include <utility>
#include <fstream>
#include <stdexcept>

#include <boost/program_options.hpp>

namespace bbb {
namespace gpio {

    template <typename T>
    boost::program_options::typed_value<T>* make_value(T* store_to)
    {
        return boost::program_options::value<T>(store_to);
    }

    static std::string load_gpio_dir_path(const boost::filesystem::path& config_file_path)
    {
        using boost::program_options::options_description;
        using boost::program_options::variables_map;
        using boost::program_options::store;
        using boost::program_options::notify;
        using boost::program_options::parse_config_file;

        std::string gpio_dir_path;
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

    config::config(boost::filesystem::path gpio_dir_path)
        : gpio_dir_(std::move(gpio_dir_path))
    {
    }

    std::unique_ptr<config> config::make_config(boost::filesystem::path config_file_path, size_t gpio_pin)
    {
        if(!boost::filesystem::exists(config_file_path)) {
          std::ostringstream oss;
          oss << "Configuration file does not exists: " << config_file_path;
          throw std::runtime_error(oss.str());
        }

        if(!boost::filesystem::is_regular_file(config_file_path)) {
          std::ostringstream oss;
          oss << "Configuration file must be a valid regular file: " << config_file_path;
          throw std::runtime_error(oss.str());
        }

        std::string gpio_config_dir = load_gpio_dir_path(config_file_path);

        std::unique_ptr<config> gconfig(new config(std::move(gpio_config_dir)));
        const std::string gpio_pin_dir = "gpio" + std::to_string(gpio_pin);

        gconfig->export_path_ = gconfig->gpio_dir_ / "export";
        gconfig->unexport_path_ = gconfig->gpio_dir_ / "unexport";
        gconfig->direction_path_ = gconfig->gpio_dir_ / gpio_pin_dir / "direction";
        gconfig->value_path_ = gconfig->gpio_dir_ / gpio_pin_dir / "value";

        return gconfig;
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
}
}
