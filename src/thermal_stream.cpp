/**
 * \file
 * \brief Give DS1820 thermal sensor as stream
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */

#include "bbbgpio/thermal_stream.hpp"

#include <fstream>

#include <Poco/Delegate.h>
#include <Poco/Glob.h>

#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <iomanip>

namespace bbb {
namespace gpio {

    thermal_stream::thermal_stream()
        : monitor_sentinel_{ true }
    {
        const Poco::Path wire_dir("/sys/bus/w1/devices");

        Poco::File wire_dir_file(wire_dir.toString());
        if (!wire_dir_file.isDirectory()) {
            throw std::invalid_argument("Could not find wire directory");
        }

        auto path_pattern = wire_dir.toString() + "/*/w1_slave";
        std::set<std::string> files;

        Poco::Glob::glob(path_pattern, files);
        if (files.empty()) {
            throw std::invalid_argument("Could not find wire file");
        }

        wire_file_path_ = *(files.begin());
    }

    thermal_stream::thermal_stream(const Poco::Path& wire_file_path)
        : monitor_sentinel_{ true }
    {
        Poco::File file(wire_file_path.toString());
        if (!file.isFile()) {
            throw std::invalid_argument("Invalid wire path: The path is not  a file");
        }

        if (!file.canRead()) {
            throw std::runtime_error("ERROR: Could not read wire file: Permission denied");
        }

        wire_file_path_ = wire_file_path.toString();
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
        const auto polling_interval = std::chrono::seconds(1);
        std::string last_read;
        std::string current_read;

        while (monitor_sentinel_) {
            current_read = safe_get_temperature();
            if (last_read != current_read) {
                subject_(current_read);
                last_read = current_read;
            }
            std::this_thread::sleep_for(polling_interval);
        }
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
        std::ifstream wire_fs(wire_file_path_.toString());
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
        return get_temperature();
    }

    thermal_stream& thermal_stream::operator>>(thermal_level_type& level)
    {
        level = safe_get_temperature();
        return *this;
    }

} // namespace gpio
} // namespace bbb
