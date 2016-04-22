/**
 * \file
 * \brief Give DS1820 configuration
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#ifndef BBBGPIO_THERMAL_CONFIG_HPP
#define BBBGPIO_THERMAL_CONFIG_HPP

#include <Poco/Path.h>

namespace bbb {
namespace gpio {

    /**
 * \brief Translate config file path
 */
    class thermal_config {
    public:
        /**
     * \brief Load config path
     */
        thermal_config();

        /**
     * \brief Get config file path
     * \return Config file path
     */
        const Poco::Path& get_config_file() const noexcept;

    private:
        /** Config file path */
        Poco::Path thermal_config_path_;
    };

} // namespace gpio
} // namespace bbb

#endif // BBBGPIO_THERMAL_CONFIG_HPP
