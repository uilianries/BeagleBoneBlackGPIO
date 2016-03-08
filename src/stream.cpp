/**
 * \file
 * \brief Give GPIO as stream
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#include "stream.hpp"

#include <tuple>

#include <Poco/Delegate.h>

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
        , dir_watcher_(config_.get_value().parent_path().string())
    {
        dir_watcher_.itemModified += Poco::delegate(this, &istream::on_directory_change);
        dir_watcher_.suspendEvents();
    }

    istream& istream::operator>>(pin_level& level)
    {
        pull(level);
        return *this;
    }

    void istream::delegate_event(on_event event) noexcept
    {
        on_event_ = event;
        if (event && !dir_watcher_.eventsSuspended()) {
            dir_watcher_.resumeEvents();
        }
        else if (!event && dir_watcher_.eventsSuspended()) {
            dir_watcher_.suspendEvents();
        }
    }

    void istream::on_directory_change(const void* p_sender, const Poco::DirectoryWatcher::DirectoryEvent& event)
    {
        std::ignore = p_sender;
        if (on_event_) {
            if (event.item.path() == config_.get_value()) {
                pin_level level;
                pull(level);
                on_event_(level);
            }
        }
    }

} // namespace gpio
} // namespace bbb
