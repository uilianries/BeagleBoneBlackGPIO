/**
 * \file
 * \brief Give DS1820 configuration
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#include "bbbgpio/thermal_config.hpp"

#include <stdexcept>

#include <Poco/File.h>

namespace bbb {
namespace gpio {

    thermal_config::thermal_config()
    {
        Poco::File fake_gpio_file("/var/tmp/fake_gpio");

        fake_gpio_file.setExecutable(false);
        fake_gpio_file.setWriteable(true);

        thermal_config_path_ = fake_gpio_file.path();
    }

    const Poco::Path& thermal_config::get_config_file() const noexcept
    {
        return thermal_config_path_;
    }

} // namespace gpio
} // namespace bbb