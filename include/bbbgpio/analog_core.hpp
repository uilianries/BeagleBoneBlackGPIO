/**
 * \file
 * \brief Load analog pin core
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#ifndef BBB_GPIO_ANALOG_CORE_HPP_
#define BBB_GPIO_ANALOG_CORE_HPP_

#include "bbbgpio/core.hpp"
#include "bbbgpio/analog_config.hpp"
#include "bbbgpio/stream_direction.hpp"

namespace bbb {
namespace gpio {

    /**
     * \brief Create pin access from settings.
     *        Allocate analog file descriptor, by slots
     *        some pin and release the state on exit
     */
    class analog_core : public core {
        /** Index limit for AIN, based on BBB */
        static constexpr auto INDEX_MAX = 6U;

    public:
        /**
         * \brief Load configuration and give acess to gpio by export
         * \param index gpio pin index
         * \param direct stream direction
         */
        analog_core(unsigned index, stream_direction direct);

        /**
         * \brief Virtual destructor
         */
        ~analog_core() override = default;

    protected:
        /** Pin configuration */
        analog_config config_; /**> gpio general settings from conf */
    };
} // namespace gpio
} // namespace bbb

#endif // BBB_GPIO_ANALOG_CORE_HPP_
