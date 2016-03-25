/**
 * \file
 * \brief Load gpio pin core
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#ifndef BBB_GPIO_CORE_HPP_
#define BBB_GPIO_CORE_HPP_

#include <memory>

#include "direction.hpp"
#include "exportation.hpp"
#include "config.hpp"

namespace bbb {
namespace gpio {

    /**
     * \brief Create pin access from settings.
     *        Allocate gpio file descriptor, by export
     *        some pin and release the state on exit
     */
    class core {
    private:
        unsigned index_; /**> gpio pin index */

    protected:
        config config_; /**> gpio general settings from conf */

    public:
        /**
         * \brief Load configuration and give acess to gpio by export
         * \param index gpio pin index
         * \param direct gpio flow direction
         */
        core(unsigned index, stream_direction direct);

        /**
         * \brief Unexport gpio
         */
        virtual ~core();

        /** Index limit for GPIO, based on BBB */
        static constexpr unsigned INDEX_MAX = 115;
    };
} // namespace gpio
} // namespace bbb

#endif // BBB_GPIO_CORE_HPP_
