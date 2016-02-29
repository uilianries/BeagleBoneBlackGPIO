#include <cassert>
#include <iostream>
#include <string>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#include "gtest/gtest.h"

#include "stream.hpp"
#include "definition.hpp"

constexpr size_t pin_led = 66;
const std::string gpio_dir_path = "/sys/class/gpio/gpio66";

TEST(GpioTest, Export)
{
    struct stat gpio_stat;

    {
        bbb::gpio::ostream ogpio(pin_led);

        EXPECT_EQ(0, stat(gpio_dir_path.c_str(), &gpio_stat));
        EXPECT_GT(S_ISDIR(gpio_stat.st_mode), 0);
    }

    EXPECT_EQ(-1, stat(gpio_dir_path.c_str(), &gpio_stat));
    EXPECT_EQ(ENOENT, errno);
}

TEST(GpioTest, BlinkLED)
{
    constexpr auto blink_interval = 1; // seconds:w
    const std::string led_path = gpio_dir_path + "/value";
    struct stat gpio_stat;

    {
        bbb::gpio::ostream ogpio(pin_led);

        EXPECT_EQ(0, stat(led_path.c_str(), &gpio_stat));
        EXPECT_GT(S_ISREG(gpio_stat.st_mode), 0);

        ogpio << bbb::gpio::pin_level::high;
        sleep(blink_interval);
        ogpio << bbb::gpio::pin_level::low;
    }

    EXPECT_EQ(-1, stat(led_path.c_str(), &gpio_stat));
    EXPECT_EQ(ENOENT, errno);
}

