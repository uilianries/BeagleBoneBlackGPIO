#include <string>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/test/unit_test_suite.hpp>
#include <boost/test/included/unit_test.hpp>

#include "config.hpp"

BOOST_AUTO_TEST_SUITE(ConfigGPIO)

static const boost::filesystem::path fake_class_dir("fake_gpio_dir");
static constexpr auto gpio_pin = 66;

struct fake_environment {
    fake_environment() {
       using boost::filesystem::path;
       using boost::filesystem::create_directories;
       using boost::filesystem::ofstream;

       const std::string pin = "gpio" + std::to_string(gpio_pin);
       const path fake_gpio_dir = fake_class_dir / pin;

       create_directories(fake_gpio_dir);

       const path export_path = fake_gpio_dir / "export";
       ofstream ofs(export_path);
       BOOST_CHECK(ofs);
       ofs.close();

       const path unexport_path = fake_gpio_dir / "unexport";
       ofs.open(export_path);
       BOOST_CHECK(ofs);
       ofs.close();

       const path direction_path = fake_gpio_dir / pin / "direction";
       ofs.open(direction_path);
       BOOST_CHECK(ofs);
       ofs.close();

       const path value_path = fake_gpio_dir / pin / "value";
       ofs.open(value_path);
       BOOST_CHECK(ofs);
       ofs.close();
    }
};

BOOST_FIXTURE_TEST_CASE(FakeEnvironment, fake_environment)
{
   auto gconfig = bbb::gpio::config::make_config(fake_class_dir, gpio_pin);
}

BOOST_AUTO_TEST_SUITE_END()
