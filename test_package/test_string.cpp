/**
 * \file
 * \brief Unit Test for GPIO string
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#include <catch.hpp>

#include "bbbgpio/string.hpp"

namespace bbb {
namespace test {

    /**
     * \brief Convert pin_level and compare to string
    */
    TEST_CASE("ToString", "[String]")
    {
        REQUIRE("high" == bbb::gpio::to_string(bbb::gpio::pin_level::high));
        REQUIRE("low" == bbb::gpio::to_string(bbb::gpio::pin_level::low));
    }

} // namespace test
} // namespace bbb
