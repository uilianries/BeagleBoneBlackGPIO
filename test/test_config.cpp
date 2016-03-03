#define BOOST_TEST_NO_LIB

#include <string>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include <boost/test/unit_test.hpp>

#include "config.hpp"

BOOST_AUTO_TEST_SUITE(ConfigGPIO)

static const boost::filesystem::path fake_class_dir("fake_gpio_dir");
static constexpr auto gpio_pin = 66;
static const std::string pin = "gpio" + std::to_string(gpio_pin);
static const boost::filesystem::path fake_gpio_dir = fake_class_dir / pin;
static const boost::filesystem::path export_path = fake_class_dir / "export";
static const boost::filesystem::path unexport_path = fake_class_dir / "unexport";
static const boost::filesystem::path direction_path = fake_gpio_dir / "direction";
static const boost::filesystem::path value_path = fake_gpio_dir / "value";
static const boost::filesystem::path config_file = "settings.conf";

struct fake_environment {
    template<typename T>
    void create_file(T&& path) {
       using boost::filesystem::ofstream;

       ofstream ofs(std::forward<T>(path));
       BOOST_CHECK(ofs);
       ofs.close();
    }

    void create_config_file() {
      boost::filesystem::ofstream ofconfig(config_file);
      BOOST_CHECK(ofconfig);
      ofconfig << "gpio-dir-path=fake_gpio_dir";
    }

    fake_environment() {
       using boost::filesystem::path;
       using boost::filesystem::create_directories;

       create_directories(fake_gpio_dir);

       create_file(export_path);
       create_file(unexport_path);
       create_file(value_path);
       create_file(direction_path);

       create_config_file();
    }

    ~fake_environment() {
      BOOST_CHECK(boost::filesystem::remove_all(fake_gpio_dir));
      BOOST_CHECK(boost::filesystem::remove(config_file));
    }

};

BOOST_FIXTURE_TEST_CASE(FakeEnvironment, fake_environment)
{
   auto gconfig = bbb::gpio::config::make_config(config_file, gpio_pin);

   BOOST_CHECK_EQUAL(export_path, gconfig->get_export());
   BOOST_CHECK_EQUAL(unexport_path, gconfig->get_unexport());
   BOOST_CHECK_EQUAL(value_path, gconfig->get_value());
   BOOST_CHECK_EQUAL(direction_path, gconfig->get_direction());
}

BOOST_AUTO_TEST_SUITE_END()
