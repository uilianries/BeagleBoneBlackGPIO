/**
 * \file
 * \brief Give DS1820 thermal sensor as stream
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */

#include "bbbgpio/thermal_stream.hpp"

#include <fstream>

#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <iomanip>

namespace bbb {
namespace gpio {

    thermal_stream::thermal_stream()
        : monitor_sentinel_{ true }
        , time_interval_{ 1 }
    {
    }

    thermal_stream::~thermal_stream()
    {
        if (monitor_thread_) {
            monitor_sentinel_ = false;
            monitor_thread_->join();
        }
    }

    void thermal_stream::monitor_temperature_change()
    {
        std::string last_read;
        std::string current_read;

        while (monitor_sentinel_) {
            current_read = safe_get_temperature();
            if (last_read != current_read) {
                subject_(current_read);
                last_read = current_read;
            }
            std::this_thread::sleep_for(time_interval_);
        }
    }

    void thermal_stream::set_polling_interval(std::chrono::seconds&& time_interval) noexcept
    {
        time_interval_ = std::move(time_interval);
    }

    void thermal_stream::delegate_event(on_event event) noexcept
    {
        if (subject_.empty()) {
            monitor_thread_.reset(new std::thread(std::bind(&thermal_stream::monitor_temperature_change, this)));
        }

        subject_.connect(event);
    }

    std::string thermal_stream::get_temperature()
    {
        std::ifstream wire_fs(thermal_config_.get_config_file().toString());
        if (!wire_fs) {
            throw std::runtime_error("Could not open wire file to read");
        }

        std::string result;
        boost::regex expression("t=\\d{3,6}");
        std::string line;
        boost::smatch what;

        while (std::getline(wire_fs, line)) {
            if (boost::regex_search(line, what, expression, boost::match_extra)) {
                result = what.str();
                boost::erase_all(result, "t=");
                std::ostringstream oss;
                oss << std::setfill('0') << std::setw(5) << result;
                result = oss.str();
                result.insert(2, ".");
                break;
            }
        }

        return result;
    }

    std::string thermal_stream::safe_get_temperature()
    {
        std::lock_guard<std::mutex> lock(monitor_mutex_);
        std::string result;
        while (result.empty()) {
            result = get_temperature();
        }
        return result;
    }

    thermal_stream& thermal_stream::operator>>(thermal_level_type& level)
    {
        level = safe_get_temperature();
        return *this;
    }

} // namespace gpio
} // namespace bbb
