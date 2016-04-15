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
        Poco::Path wire_full_path(*files.begin());
        auto dir_to_watch = wire_full_path.parent().toString();
        directory_watcher_.reset(new Poco::DirectoryWatcher(dir_to_watch));
        directory_watcher_->itemModified += Poco::delegate(this, &thermal_stream::on_directory_change);
    }

    void thermal_stream::on_directory_change(const void* p_sender, const Poco::DirectoryWatcher::DirectoryEvent& event)
    {
        std::ignore = p_sender;
        auto modified_path = event.item.path();
        auto wire_path = wire_file_path_.toString();
        if (modified_path == wire_path) {
            subject_(get_temperature());
        }
    }

    void thermal_stream::delegate_event(on_event event) noexcept
    {
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

    thermal_stream& thermal_stream::operator>>(thermal_level_type& level)
    {
        level = get_temperature();
        return *this;
    }

} // namespace gpio
} // namespace bbb
