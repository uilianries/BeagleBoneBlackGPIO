/**
 * \file
 * \brief Unit Test for GPIO pin class
 *        This test must be executed on BBB.
 *
 *        Hardware configuration:
 *        GPIO 66 -> LED -> GND
 *        GPIO 67 -> RES 1K -> GPIO 68
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#include <thread>
#include <chrono>

#include <catch.hpp>

#include "bbbgpio/stream.hpp"
#include "arch.hpp"

namespace bbb {
namespace test {

/**
 * \brief Test stream gpio class.
 */

/**
 * \brief Open GPIO 66 as output and toggle the state.
 *        May use a led, to watch the hardware.
 */
    TEST_CASE("Active and write on GPIO", "[gpio]")
    {

        REQUIRE(bbb::gpio::any(bbb::gpio::pin_level::high));
        REQUIRE_FALSE(bbb::gpio::any(bbb::gpio::pin_level::low));

        if (!IS_BBB_ARCH) {
            return;
        }

        constexpr unsigned pin = 66;

        bbb::gpio::logic_ostream ogpio{ pin };

        ogpio << bbb::gpio::pin_level::high;

        std::this_thread::sleep_for(std::chrono::seconds(1));

        ogpio << bbb::gpio::pin_level::low;
    }

/**
 * \brief Open GPIO 67 as input and toggle the state.
 */
    TEST_CASE("Active and read on GPIO", "[gpio]")
    {
        if (!IS_BBB_ARCH) {
            return;
        }

        constexpr unsigned ipin = 67;
        constexpr unsigned opin = 68;

        bbb::gpio::logic_ostream ogpio{ opin };

        ogpio << bbb::gpio::pin_level::low;

        bbb::gpio::logic_istream igpio{ ipin };
        bbb::gpio::pin_level lvl;

        igpio >> lvl;

        REQUIRE(bbb::gpio::pin_level::low == lvl);

        auto event_low_counter = 0;
        auto event_high_counter = 0;

        igpio.delegate_event(
            [&event_low_counter, &event_high_counter](bbb::gpio::pin_level gpio_lvl) {
            if (gpio_lvl == bbb::gpio::pin_level::high) {
                event_high_counter++;
            } else {
                event_low_counter++;
            }
            });

        ogpio << bbb::gpio::pin_level::high;
        igpio >> lvl;

        REQUIRE(bbb::gpio::pin_level::high == lvl);

        ogpio << bbb::gpio::pin_level::low;
        igpio >> lvl;

        REQUIRE(bbb::gpio::pin_level::low == lvl);

        REQUIRE(2 == event_low_counter);
        REQUIRE(1 == event_high_counter);
    }

} // namespace test
} // namespace bbb
