/**
 * \file
 * \brief Give DS1820 configuration
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#include "bbbgpio/thermal_config.hpp"

#include <stdexcept>
#include <set>

#include <Poco/File.h>
#include <Poco/Glob.h>

namespace bbb {
namespace gpio {

    thermal_config::thermal_config()
    {
        const Poco::Path wire_dir{ "/sys/bus/w1/devices" };
        Poco::File wire_dir_file(wire_dir.toString());
        if (!wire_dir_file.isDirectory()) {
            throw std::invalid_argument("Could not find wire directory");
        }

        auto path_pattern = wire_dir.toString() + "/*/w1_slave";
        std::set<std::string> files;

        Poco::Glob::glob(path_pattern, files);
        if (files.empty()) {
            throw std::invalid_argument("Could not find wire file");
        }

        thermal_config_path_ = *(files.begin());
    }

    const Poco::Path& thermal_config::get_config_file() const noexcept
    {
        return thermal_config_path_;
    }

} // namespace gpio
} // namespace bbb