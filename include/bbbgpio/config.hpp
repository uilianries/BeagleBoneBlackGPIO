/**
 * \file
 * \brief Abstract Configuration
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */

#ifndef BBBGPIO_CONFIG_HPP
#define BBBGPIO_CONFIG_HPP

#include <boost/filesystem/path.hpp>

namespace bbb {
namespace gpio {

    /**
     * \brief Load pin configuration
     */
    class config {
    public:
        /**
       * \brief Virtual destructor
       */
        virtual ~config() = default;

        /**
       * \brief Retrieve pin file path
       */
        virtual boost::filesystem::path get_value() const noexcept = 0;
    };

} // namespace gpio
} // namespace bbb

#endif //BBBGPIO_CONFIG_HPP
