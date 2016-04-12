/**
 * \file
 * \brief Unit Test for GPIO string
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
/** Should not link with unit test lib */
#define BOOST_TEST_NO_LIB

#include <boost/test/unit_test.hpp>

#include "bbbgpio/string.hpp"

namespace bbb {
namespace test {

    /**
     * \brief Test stream gpio class.
     */
    BOOST_AUTO_TEST_SUITE(ToString)

    /**
            * \brief Convert pin_level and compare to string
            */
    BOOST_AUTO_TEST_CASE(String)
    {
        BOOST_CHECK_EQUAL("high", bbb::gpio::to_string(bbb::gpio::pin_level::high));
        BOOST_CHECK_EQUAL("low", bbb::gpio::to_string(bbb::gpio::pin_level::low));
    }

    BOOST_AUTO_TEST_SUITE_END() // BOOST_AUTO_TEST_SUITE(ToString)

} // namespace test
} // namespace bbb
