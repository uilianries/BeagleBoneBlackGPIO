/**
 * \file
 * \brief Give DS1820 configuration
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#include "bbbgpio/thermal_config.hpp"

#include <stdexcept>
#include <set>

#include <boost/filesystem/operations.hpp>
#include <Poco/Glob.h>

namespace bbb {
namespace gpio {

    thermal_config::thermal_config()
    {
        boost::filesystem::path wire_dir{ "/sys/bus/w1/devices" };
        if (!boost::filesystem::is_directory(wire_dir)) {
            throw std::invalid_argument("Could not find wire directory");
        }

        wire_dir += "/*/w1_slave";
        std::set<std::string> files;

        Poco::Glob::glob(wire_dir.string(), files);
        if (files.empty()) {
            throw std::invalid_argument("Could not find wire file");
        }

        thermal_config_path_ = *(files.begin());
    }

    boost::filesystem::path thermal_config::get_config_file() const noexcept
    {
        return thermal_config_path_;
    }

} // namespace gpio
} // namespace bbb