#ifndef BBB_GPIO_CORE_HPP_
#define BBB_GPIO_CORE_HPP_

#include <memory>

#include "definition.hpp"
#include "direction.hpp"
#include "exportation.hpp"

namespace bbb {
namespace gpio {

    class core {
    private:
        std::unique_ptr<direction> direction_;
        std::unique_ptr<exportation> exportation_;
        size_t index_;

    protected:
        std::string get_value_path(size_t index);

    public:
        core(size_t index, stream_direction direct);
        ~core();
    };
}
}

#endif // BBB_GPIO_CORE_HPP_
