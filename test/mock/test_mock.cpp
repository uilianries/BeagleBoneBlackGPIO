/**
 * \file
 * \brief Unit Test for Thermal Mock Config
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
/** Should not link with unit test lib */
#define BOOST_TEST_NO_LIB

#include <string>

#include <boost/filesystem.hpp>

#include <boost/test/unit_test.hpp>
#include <Poco/File.h>

#include "bbbgpio/thermal_config.hpp"

namespace bbb {
namespace test {

    /**
 * \brief Test mock config gpio class.
 *        Create a fake gpio fd
 */
    BOOST_AUTO_TEST_SUITE(MockGPIO)

    BOOST_AUTO_TEST_CASE(FileValidation)
    {
        bbb::gpio::thermal_config thermal_config;
        auto&& thermal_config_path = thermal_config.get_config_file().toString();

        BOOST_CHECK(boost::filesystem::exists(thermal_config_path));
        BOOST_CHECK(boost::filesystem::is_regular_file(thermal_config_path));

        Poco::File file(thermal_config_path);
        BOOST_CHECK(file.canRead());
        BOOST_CHECK(file.canWrite());
    }

    BOOST_AUTO_TEST_SUITE_END() // BOOST_AUTO_TEST_SUITE(MockGPIO)

} // namespace test
} // namespace bbb
