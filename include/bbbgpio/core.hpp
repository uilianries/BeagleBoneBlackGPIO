/**
 * \file
 * \brief Load basic pin core
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */

#ifndef BBBGPIO_CORE_HPP
#define BBBGPIO_CORE_HPP

namespace bbb {
namespace gpio {

    /**
* \brief Basic core declaration
*/
    class core {
    public:
        virtual ~core() = default;
    };

} // namespace gpio
} // namespace bbb

#endif //BBBGPIO_CORE_HPP
