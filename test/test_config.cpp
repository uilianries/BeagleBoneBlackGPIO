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
#include <boost/filesystem/fstream.hpp>

#include <boost/test/unit_test.hpp>

#include "config.hpp"

/**
 * \brief Test config gpio class.
 *        Create a fake environment for GPIO support on x86
 */
BOOST_AUTO_TEST_SUITE(ConfigGPIO)

namespace test_gpio_config {

static const boost::filesystem::path fake_class_dir("fake_gpio_dir");
static constexpr auto gpio_pin = 66;
static const std::string pin = "gpio" + std::to_string(gpio_pin);
static const boost::filesystem::path fake_gpio_dir = fake_class_dir / pin;
static const boost::filesystem::path export_path = fake_class_dir / "export";
static const boost::filesystem::path unexport_path = fake_class_dir / "unexport";
static const boost::filesystem::path direction_path = fake_gpio_dir / "direction";
static const boost::filesystem::path value_path = fake_gpio_dir / "value";

/**
 * \brief Create fake environment for test run on x86 arch
 */
struct fake_environment {

    /**
     * \brief Create some file and check.
     *        If could not create the file, then abort.
     * \param path file path to be created
     */
    template <typename T>
    void create_file(T&& path) noexcept(false)
    {
        using boost::filesystem::ofstream;

        ofstream ofs(std::forward<T>(path));
        BOOST_CHECK(ofs);
        ofs.close();
    }

    /**
     * \brief Create default config file with some data
     */
    static void create_config_file() noexcept(false)
    {
        boost::filesystem::ofstream ofconfig{ bbb::gpio::SETTINGS_FILE_PATH };
        BOOST_CHECK(ofconfig);
        ofconfig << "gpio-dir-path=fake_gpio_dir";
    }

    /**
     * \brief Produces a fake directory tree, as GPIO class structure on file system.
     *        Create the default gpio config file and hollow files for GPIO
     */
    fake_environment() noexcept(false)
    {
        using boost::filesystem::path;
        using boost::filesystem::create_directories;

        create_directories(fake_gpio_dir);

        create_file(export_path);
        create_file(unexport_path);
        create_file(value_path);
        create_file(direction_path);

        create_config_file();
    }

    /**
     * \brief Remove the fake environment from file system
     */
    ~fake_environment()
    {
        BOOST_CHECK(boost::filesystem::remove_all(fake_gpio_dir));
        BOOST_CHECK(boost::filesystem::remove(bbb::gpio::SETTINGS_FILE_PATH));
    }
};
} // namespace test_gpio_config

/**
 * \brief Produces a tree structure as GPIO class,
 *        and load gpio config. Verify each member, if the
 *        path is equal in fake environment.
 *
 */
BOOST_FIXTURE_TEST_CASE(FakeEnvironment, test_gpio_config::fake_environment)
{
    auto gconfig = bbb::gpio::config{ bbb::gpio::SETTINGS_FILE_PATH, test_gpio_config::gpio_pin };

    BOOST_CHECK_EQUAL(test_gpio_config::export_path, gconfig.get_export());
    BOOST_CHECK_EQUAL(test_gpio_config::unexport_path, gconfig.get_unexport());
    BOOST_CHECK_EQUAL(test_gpio_config::value_path, gconfig.get_value());
    BOOST_CHECK_EQUAL(test_gpio_config::direction_path, gconfig.get_direction());
}

BOOST_AUTO_TEST_SUITE_END() // BOOST_AUTO_TEST_SUITE(ConfigGPIO)
