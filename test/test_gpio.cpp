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

#include "stream.hpp"

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
#ifdef __arm__ /**> Run on BBB */
    constexpr unsigned pin = 66;

    bbb::gpio::ostream ogpio{ pin };

    ogpio << bbb::gpio::pin_level::high;

    std::this_thread::sleep_for(std::chrono::seconds(1));

    ogpio << bbb::gpio::pin_level::low;
#else /**> On x86, do nothing */
    BOOST_CHECK(true);
#endif // ifdef __arm__
}

/**
 * \brief Open GPIO 67 as input and toggle the state.
 */
BOOST_AUTO_TEST_CASE(ReadGPIO)
{
#ifdef __arm__ /**> Run on BBB */
    constexpr unsigned ipin = 67;
    constexpr unsigned opin = 68;

    bbb::gpio::ostream ogpio{ opin };

    ogpio << bbb::gpio::pin_level::low;

    bbb::gpio::istream igpio{ ipin };
    bbb::gpio::pin_level lvl;

    igpio >> lvl;

    BOOST_CHECK_EQUAL(test_gpio_config::export_path, gconfig.get_export());

    ogpio << bbb::gpio::pin_level::high;
    igpio >> lvl;

    BOOST_CHECK_EQUAL(bbb::gpio::pin_level::high, lvl);

    ogpio << bbb::gpio::pin_level::low;
    igpio >> lvl;

    BOOST_CHECK_EQUAL(bbb::gpio::pin_level::low, lvl);
#else /**> On x86, do nothing */
    BOOST_CHECK(true);
#endif // ifdef __arm__
}

BOOST_AUTO_TEST_SUITE_END() // BOOST_AUTO_TEST_SUITE(ActiveGPIO)
