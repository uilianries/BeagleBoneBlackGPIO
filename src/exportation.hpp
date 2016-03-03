/**
 * \file
 * \brief Export/Unexport GPIO from /sys/class
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#ifndef BBB_GPIO_EXPORTATION_HPP_
#define BBB_GPIO_EXPORTATION_HPP_

#include "file_descriptor.hpp"

namespace bbb {
namespace gpio {

    /**
     * \brief Open export and write GPIO index to create gpioxx dir
     */
    using exportation = ofile_descriptor<unsigned>;

} // namespace gpio
} // namespace bbb

#endif // BBB_GPIO_EXPORTATION_HPP_
