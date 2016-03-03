/**
 * \file
 * \brief Unit Test Application main
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */

/** Only main should link with unit test lib */
#define BOOST_TEST_DYN_LINK
/** Unit Test Module Name */
#define BOOST_TEST_MODULE "C++ Unit Tests for BeagleBone Black GPIO"
#include <boost/test/included/unit_test.hpp>
