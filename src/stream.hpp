/**
 * \file
 * \brief Give GPIO as stream
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#ifndef BBB_GPIO_STREAM_HPP_
#define BBB_GPIO_STREAM_HPP_

#include "file_descriptor.hpp"
#include "core.hpp"
#include "pin_level.hpp"

namespace bbb {
namespace gpio {

    /**
     * \brief Open GPIO pin as output stream
     */
    class ostream : public core, public ofile_descriptor<pin_level> {
    public:
        /**
         *  \brief Open GPIO as stream output
         *  \param index GPIO pin index to be opened
        */
        explicit ostream(unsigned index);

        /**
         * \brief Copy is not allowed
         */
        ostream(const ostream&) = delete;

        /**
         * \brief Copy is not allowed
         */
        ostream& operator=(const ostream&) = delete;

        /**
         * \brief overload push stream to GPIO
         * \param level logic level to set at GPIO index
         * \return GPIO file stream
         */
        ostream& operator<<(pin_level level);
    };

    /**
     * \brief Open GPIO pin as input stream
     */
    class istream : public core, public ifile_descriptor<pin_level> {
    public:
        /**
         * \brief Open GPIO index as stream input
         * \param index GPIO pin index to be opened
         */
        explicit istream(unsigned index);

        /**
         * \brief Copy is not allowed
         */
        istream(const istream&) = delete;

        /**
         * \brief Copy is not allowed
         */
        istream& operator=(const istream&) = delete;

        /**
         * \brief Read data from input stream and set to level
         * \param level receive GPIO current level
         * \return GPIO input stream
         */
        istream& operator>>(pin_level& level);
    };
} // namespace gpio
} // namespace bbb
#endif // BBB_GPIO_STREAM_HPP_
