/**
 * \file
 * \brief Unit Test for GPIO config class
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
/** Should not link with unit test lib */
#define BOOST_TEST_NO_LIB

#include <string>

#include <boost/filesystem.hpp>

#include <boost/test/unit_test.hpp>

#include "bbbgpio/config.hpp"

namespace bbb {
namespace test {

    /**
 * \brief Test config gpio class.
 *        Create a fake environment for GPIO support on x86
 */
    BOOST_AUTO_TEST_SUITE(ConfigGPIO)

    BOOST_AUTO_TEST_CASE(PathValidation)
    {
        constexpr auto gpio_index = 66;
        const boost::filesystem::path gpio_class_dir = "/sys/class/gpio";

        const boost::filesystem::path gpio_dir = gpio_class_dir / std::string("gpio" + std::to_string(gpio_index));
        const boost::filesystem::path export_path = gpio_class_dir / "export";
        const boost::filesystem::path unexport_path = gpio_class_dir / "unexport";
        const boost::filesystem::path direction_path = gpio_dir / "direction";
        const boost::filesystem::path value_path = gpio_dir / "value";

        auto gconfig = bbb::gpio::config{ gpio_index };

        BOOST_CHECK_EQUAL(export_path, gconfig.get_export());
        BOOST_CHECK_EQUAL(unexport_path, gconfig.get_unexport());
        BOOST_CHECK_EQUAL(value_path, gconfig.get_value());
        BOOST_CHECK_EQUAL(direction_path, gconfig.get_direction());
    }

    BOOST_AUTO_TEST_SUITE_END() // BOOST_AUTO_TEST_SUITE(ConfigGPIO)

} // namespace test
} // namespace bbb
