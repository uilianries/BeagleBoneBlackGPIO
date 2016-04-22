/**
 * \file
 * \brief Give DS1820 configuration
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#include "bbbgpio/thermal_config.hpp"

#include <stdexcept>

#include <Poco/TemporaryFile.h>

namespace bbb {
namespace gpio {

    thermal_config::thermal_config()
    {
        Poco::TemporaryFile temporary_file;
        if (!temporary_file.createFile()) {
            throw std::runtime_error("ERROR: Could not create temporary file");
        }
        temporary_file.keep();

        thermal_config_path_ = temporary_file.path();
    }

    const Poco::Path& thermal_config::get_config_file() const noexcept
    {
        return thermal_config_path_;
    }

} // namespace gpio
} // namespace bbb