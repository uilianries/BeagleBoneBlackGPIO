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
/** Should not link with unit test lib */
#define BOOST_TEST_NO_LIB

#include <thread>
#include <chrono>

#include <boost/test/unit_test.hpp>

#include "bbbgpio/stream.hpp"
#include "arch.hpp"

namespace bbb {
namespace test {

    /**
 * \brief Test stream gpio class.
 */
    BOOST_AUTO_TEST_SUITE(ActiveGPIO)

    /**
 * \brief Open GPIO 66 as output and toggle the state.
 *        May use a led, to watch the hardware.
 */
    BOOST_AUTO_TEST_CASE(WriteGPIO)
    {

        BOOST_CHECK(bbb::gpio::any(bbb::gpio::pin_level::high));
        BOOST_CHECK(!bbb::gpio::any(bbb::gpio::pin_level::low));

        if (!IS_BBB_ARCH) {
            return;
        }

        constexpr unsigned pin = 66;

        bbb::gpio::ostream ogpio{ pin };

        ogpio << bbb::gpio::pin_level::high;

        std::this_thread::sleep_for(std::chrono::seconds(1));

        ogpio << bbb::gpio::pin_level::low;
    }

    /**
 * \brief Open GPIO 67 as input and toggle the state.
 */
    BOOST_AUTO_TEST_CASE(ReadGPIO)
    {
        if (!IS_BBB_ARCH) {
            return;
        }

        constexpr unsigned ipin = 67;
        constexpr unsigned opin = 68;

        bbb::gpio::ostream ogpio{ opin };

        ogpio << bbb::gpio::pin_level::low;

        bbb::gpio::istream igpio{ ipin };
        bbb::gpio::pin_level lvl;

        igpio >> lvl;

        BOOST_CHECK_EQUAL(bbb::gpio::pin_level::low, lvl);

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

        BOOST_CHECK_EQUAL(bbb::gpio::pin_level::high, lvl);

        ogpio << bbb::gpio::pin_level::low;
        igpio >> lvl;

        BOOST_CHECK_EQUAL(bbb::gpio::pin_level::low, lvl);

        BOOST_CHECK_EQUAL(2, event_low_counter);
        BOOST_CHECK_EQUAL(1, event_high_counter);
    }

    BOOST_AUTO_TEST_SUITE_END() // BOOST_AUTO_TEST_SUITE(ActiveGPIO)

} // namespace test
} // namespace bbb
