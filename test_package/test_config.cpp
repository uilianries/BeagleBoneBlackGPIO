/**
 * \file
 * \brief Unit Test for GPIO config class
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#include <string>

#include <boost/filesystem.hpp>

#include <catch.hpp>

#include "bbbgpio/pin_level.hpp"
#include "bbbgpio/logic_config.hpp"

namespace bbb {
namespace test {

/**
 * \brief Test config gpio class.
 *        Create a fake environment for GPIO support on x86
 */
    TEST_CASE("ConfigGPIO", "[PathValidation]")
    {
        constexpr auto gpio_index = 66;
        const boost::filesystem::path gpio_class_dir = "/sys/class/gpio";

        const boost::filesystem::path gpio_dir = gpio_class_dir / std::string("gpio" + std::to_string(gpio_index));
        const boost::filesystem::path export_path = gpio_class_dir / "export";
        const boost::filesystem::path unexport_path = gpio_class_dir / "unexport";
        const boost::filesystem::path direction_path = gpio_dir / "direction";
        const boost::filesystem::path value_path = gpio_dir / "value";

        auto gconfig = bbb::gpio::logic_config{ gpio_index };

        REQUIRE(export_path == gconfig.get_export());
        REQUIRE(unexport_path == gconfig.get_unexport());
        REQUIRE(value_path == gconfig.get_value());
        REQUIRE(direction_path == gconfig.get_direction());
    }


} // namespace test
} // namespace bbb
