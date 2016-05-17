/**
 * \file
 * \brief Load analog library configuration
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */

#include "bbbgpio/analog_config.hpp"

#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

namespace bbb {
namespace gpio {

    analog_config::analog_config(unsigned index)
    {
        boost::filesystem::path bone_dir{ "/sys/devices" };
        boost::regex path_filter("bone_capemgr.\\d{1,2}");

        boost::filesystem::directory_iterator end;

        using slot_list = std::vector<boost::filesystem::path>;
        slot_list slots;

        for (boost::filesystem::directory_iterator it(bone_dir); it != end; ++it) {
            if (!boost::filesystem::is_directory(it->status())) {
                continue;
            }

            boost::smatch what;

            if (!boost::regex_match(it->path().string(), what, path_filter)) {
                continue;
            }

            boost::filesystem::path slot = it->path() / "slots";
            slots.push_back(slot);
        }

        for (const auto& slot : slots) {
            boost::filesystem::ofstream ofs(slot);
            if (!ofs) {
                throw std::runtime_error("Could not open cape bone slot file");
            }

            constexpr auto cape_bone = "cape-bone-iio";
            ofs << cape_bone;
        }

        auto analog_slot = "AIN" + std::to_string(index);

        boost::filesystem::recursive_directory_iterator recursive_end;
        auto analog_path = std::find_if(boost::filesystem::recursive_directory_iterator(bone_dir), recursive_end,
            [&analog_slot](const boost::filesystem::directory_entry& entry) {
                                        return entry.path().filename() == analog_slot;
            });

        if (analog_path == recursive_end) {
            throw std::runtime_error("Could not find AINx");
        }

        pin_path_ = analog_path->path();
    }

    boost::filesystem::path analog_config::get_value() const noexcept
    {
        return pin_path_;
    }

} // namespace gpio
} // namespace bbb
