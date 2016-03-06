/**
 * \file
 * \brief Give GPIO as stream
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#include "stream.hpp"

namespace bbb {
namespace gpio {

    ostream::ostream(unsigned index)
        : core{ index, stream_direction::output }
        , ofile_descriptor{ config_.get_value(), pin_level::low }
    {
    }

    ostream& ostream::operator<<(pin_level level)
    {
        push(level);
        return *this;
    }

    istream::istream(unsigned index)
        : core{ index, stream_direction::input }
        , ifile_descriptor{ config_.get_value() }
    {
    }

    istream& istream::operator>>(pin_level& level)
    {
        pull(level);
        return *this;
    }
} // namespace gpio
} // namespace bbb
