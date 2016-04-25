/**
 * \file
 * \brief Load gpio pin core
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#ifndef BBB_GPIO_LOGIC_CORE_HPP_
#define BBB_GPIO_LOGIC_CORE_HPP_

#include <memory>

#include "direction.hpp"
#include "exportation.hpp"
#include "logic_config.hpp"
#include "pin_level.hpp"
#include "basic_core.hpp"

namespace bbb {
namespace gpio {

    /**
     * \brief Create pin access from settings.
     *        Allocate gpio file descriptor, by export
     *        some pin and release the state on exit
     */
    template <>
    class core<pin_level> {
    private:
        unsigned index_; /**> gpio pin index */

    protected:
        config<pin_level> config_; /**> gpio general settings from conf */

    public:
        /**
         * \brief Load configuration and give acess to gpio by export
         * \param index gpio pin index
         * \param direct gpio flow direction
         */
        core(unsigned index, stream_direction direct)
            : index_{ index }
            , config_{ index }
        {
            if (index > INDEX_MAX) {
                throw std::runtime_error("Invalid pin index: " + std::to_string(index));
            }

            exportation{ config_.get_export(), index };
            direction{ config_.get_direction(), direct };
        }

        /**
         * \brief Unexport gpio
         */
        virtual ~core()
        {
            exportation{ config_.get_unexport(), index_ };
        }

        /** Index limit for GPIO, based on BBB */
        static constexpr unsigned INDEX_MAX = 115;
    };
} // namespace gpio
} // namespace bbb

#endif // BBB_GPIO_LOGIC_CORE_HPP_
