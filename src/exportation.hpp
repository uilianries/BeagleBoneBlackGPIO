#ifndef BBB_GPIO_EXPORTATION_HPP_
#define BBB_GPIO_EXPORTATION_HPP_

#include "file_descriptor.hpp"

namespace bbb {
namespace gpio {

    using exportation = ofile_descriptor<unsigned>;
}
}

#endif // BBB_GPIO_EXPORTATION_HPP_
