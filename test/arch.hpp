/**
 * \file
 *
 * \brief Find current board
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#ifndef BBB_GPIO_TEST_ARCH_HPP_
#define BBB_GPIO_TEST_ARCH_HPP_

namespace bbb {
namespace test {

    /** Using BeagleBone Black Board */
    static constexpr auto IS_BBB_ARCH = false;

#ifdef __arm__
    IS_BBB_ARCH = true;
#endif // ifdef __arm__

} // namespace test
} // namespace bbb

#endif // BBB_GPIO_TEST_ARCH_HPP_
