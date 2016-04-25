/**
 * \file
 * \brief Load analog pin core
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#ifndef BBB_GPIO_ANALOG_CORE_HPP_
#define BBB_GPIO_ANALOG_CORE_HPP_

#include <memory>

#include "basic_core.hpp"
#include "analog_config.hpp"
#include "pin_level.hpp"
#include "stream_direction.hpp"

namespace bbb {
namespace gpio {

    /**
     * \brief Create pin access from settings.
     *        Allocate analog file descriptor, by slots
     *        some pin and release the state on exit
     */
    template <>
    class core<analog_level> {
    public:
        /**
         * \brief Load configuration and give acess to gpio by export
         * \param index gpio pin index
         * \param direct stream direction
         */
        core(unsigned index, stream_direction direct)
            : index_{ index }
            , config_{ index }
        {
            std::ignore = direct;

            if (index > INDEX_MAX) {
                throw std::runtime_error("Invalid pin index: " + std::to_string(index));
            }
        }

        /** Index limit for AIN, based on BBB */
        static constexpr unsigned INDEX_MAX = 6;

    private:
        unsigned index_; /**> gpio pin index */
    protected:
        /** Pin configuration */
        config<analog_level> config_; /**> gpio general settings from conf */
    };
} // namespace gpio
} // namespace bbb

#endif // BBB_GPIO_ANALOG_CORE_HPP_
