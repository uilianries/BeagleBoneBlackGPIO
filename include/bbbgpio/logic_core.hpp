/**
 * \file
 * \brief Load gpio pin core
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#ifndef BBB_GPIO_LOGIC_CORE_HPP_
#define BBB_GPIO_LOGIC_CORE_HPP_

#include <memory>

#include "bbbgpio/direction.hpp"
#include "bbbgpio/exportation.hpp"
#include "bbbgpio/logic_config.hpp"
#include "bbbgpio/pin_level.hpp"
#include "bbbgpio/core.hpp"

namespace bbb {
namespace gpio {

    /**
     * \brief Create pin access from settings.
     *        Allocate gpio file descriptor, by export
     *        some pin and release the state on exit
     */
    class logic_core : core {
        unsigned index_; /**> gpio pin index */
        /** Index limit for GPIO, based on BBB */
        static constexpr auto INDEX_MAX = 115U;

    protected:
        /** gpio general settings from conf */
        logic_config config_;

    public:
        /**
         * \brief Load configuration and give acess to gpio by export
         * \param index gpio pin index
         * \param direct gpio flow direction
         */
        logic_core(unsigned index, stream_direction direct);

        /**
         * \brief Unexport gpio
         */
        virtual ~logic_core() override;
    };
} // namespace gpio
} // namespace bbb

#endif // BBB_GPIO_LOGIC_CORE_HPP_
