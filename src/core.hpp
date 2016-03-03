#ifndef BBB_GPIO_CORE_HPP_
#define BBB_GPIO_CORE_HPP_

#include <memory>

#include "definition.hpp"
#include "direction.hpp"
#include "exportation.hpp"
#include "config.hpp"

namespace bbb {
namespace gpio {

    class core {
    private:
        unsigned index_;
        std::unique_ptr<direction> direction_;
        std::unique_ptr<exportation> exportation_;

    protected:
        std::unique_ptr<config> config_;

    public:
        core(unsigned index, stream_direction direct);
        virtual ~core();
    };
}
}

#endif // BBB_GPIO_CORE_HPP_
