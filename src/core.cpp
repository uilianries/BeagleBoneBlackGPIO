/**
 * \file
 * \brief Load gpio pin core
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#include "bbbgpio/core.hpp"

#include <utility>
#include <string>

namespace bbb {
namespace gpio {

    core::core(unsigned index, stream_direction direct)
        : index_{ index }
        , config_{ index }
    {
        if (index > INDEX_MAX) {
            throw std::runtime_error("Invalid pin index: " + std::to_string(index));
        }

        exportation{ config_.get_export(), index };
        direction{ config_.get_direction(), direct };
    }

    core::~core()
    {
        exportation{ config_.get_unexport(), index_ };
    }
} // namespace gpio
} // namespace bbb
