#include "core.hpp"

namespace bbb {
namespace gpio {

    core::core(unsigned index, stream_direction direct)
        : index_{ index }
    {
        if (index > index_max) {
            throw std::runtime_error("Invalid pin index: " + std::to_string(index));
        }

        config_ = std::move(config::make_config(gpio_class_path, index));
        exportation_.reset(new exportation(config_->get_export(), index));
        direction_.reset(new direction(config_->get_direction(), direct));
    }

    core::~core()
    {
        exportation_.reset();
        exportation_.reset(new exportation(config_->get_unexport(), index_));
    }
}
}
