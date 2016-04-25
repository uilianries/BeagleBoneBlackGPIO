/**
 * \file
 * \brief Give GPIO as stream
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#include "bbbgpio/basic_stream.hpp"

#include <tuple>

#include <Poco/Delegate.h>

namespace bbb {
namespace gpio {

    template <class core_type, typename pin_level_type>
    ostream<core_type, pin_level_type>::ostream(unsigned index)
        : core_type{ index, stream_direction::output }
        , ofile_descriptor<pin_level_type>{ core_type::config_.get_value(), zero_level<pin_level_type>::value } /**< Output File Descriptor */
    {
    }

    template <class core_type, typename pin_level_type>
    ostream<core_type, pin_level_type>& ostream<core_type, pin_level_type>::operator<<(pin_level_type level)
    {
        ofile_descriptor<pin_level_type>::push(level);
        return *this;
    }

    template <class core_type, typename pin_level_type>
    istream<core_type, pin_level_type>::istream(unsigned index)
        : core_type{ index, stream_direction::input }
        , /** Treat file descriptor as stream */
        ifile_descriptor<pin_level_type>{ core_type::config_.get_value() }
        , /** Directory watcher */
        dir_watcher_(core_type::config_.get_value().parent_path().string())
    {
        dir_watcher_.itemModified += Poco::delegate(this, &istream::on_directory_change);
    }

    template <class core_type, typename pin_level_type>
    istream<core_type, pin_level_type>& istream<core_type, pin_level_type>::operator>>(pin_level_type& level)
    {
        ifile_descriptor<pin_level_type>::pull(level);
        return *this;
    }

    template <class core_type, typename pin_level_type>
    void istream<core_type, pin_level_type>::delegate_event(on_event event) noexcept
    {
        on_event_ = event;
        if (event && !dir_watcher_.eventsSuspended()) {
            dir_watcher_.resumeEvents();
        }
        else if (!event && dir_watcher_.eventsSuspended()) {
            dir_watcher_.suspendEvents();
        }
    }

    template <class core_type, typename pin_level_type>
    void istream<core_type, pin_level_type>::on_directory_change(const void* p_sender, const Poco::DirectoryWatcher::DirectoryEvent& event)
    {
        std::ignore = p_sender;
        if (on_event_) {
            if (event.item.path() == core_type::config_.get_value()) {
                pin_level_type level;
                ifile_descriptor<pin_level_type>::pull(level);
                on_event_(level);
            }
        }
    }

} // namespace gpio
} // namespace bbb

template class bbb::gpio::ostream<bbb::gpio::logic_core, bbb::gpio::pin_level>;
template class bbb::gpio::ostream<bbb::gpio::analog_core, bbb::gpio::analog_level>;

template class bbb::gpio::istream<bbb::gpio::logic_core, bbb::gpio::pin_level>;
template class bbb::gpio::istream<bbb::gpio::analog_core, bbb::gpio::analog_level>;
