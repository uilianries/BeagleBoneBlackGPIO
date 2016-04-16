/**
 * \file
 * \brief Give DS1820 thermal sensor as stream
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#ifndef BBBGPIO_THERMAL_STREAM_HPP
#define BBBGPIO_THERMAL_STREAM_HPP

#include <string>
#include <memory>
#include <thread>
#include <mutex>
#include <atomic>
#include <Poco/DirectoryWatcher.h>
#include <Poco/Path.h>
#include <boost/signals2.hpp>

namespace bbb {
namespace gpio {

    /** Thermal type to be forward */
    using thermal_level_type = std::string;

    /**
 * \brief Read thermal level from DS1820 sensor
 */
    class thermal_stream {
    public:
        /**
     * \brief Open file descriptor
     */
        thermal_stream();

        /**
         * \brief Custom wire path
         * \param wire_file_path absolute path to device
         */
        explicit thermal_stream(const Poco::Path& wire_file_path);

        /**
         * \brief Stop the monitor thread
         */
        ~thermal_stream();

        /**
      * \brief Copy is not allowed
      */
        thermal_stream(const thermal_stream&) = delete;

        /**
      * \brief Copy is not allowed
      */
        thermal_stream& operator=(const thermal_stream&) = delete;

        /**
      * \brief Read data from input stream and set to level
      * \param level receive current thermal level
      * \return own object input stream
      */
        thermal_stream& operator>>(thermal_level_type& level);

        /** Callback to receive level change */
        using on_event = std::function<void(const thermal_level_type&)>;

        /**
     * \brief Add observer to receive event about the temperature
     * \param event callback to receive event
     */
        void delegate_event(on_event event) noexcept;

    private:
        /** Monitor temperature */
        std::unique_ptr<std::thread> monitor_thread_;
        /** Lock temperature read */
        std::mutex monitor_mutex_;
        /** sentinel to stop the thread */
        std::atomic<bool> monitor_sentinel_;
        /** Notify observers */
        boost::signals2::signal<void(thermal_level_type)> subject_;
        /** Wire file path */
        Poco::Path wire_file_path_;

        /**
     * \brief Monitor a file for changes
     */
        void monitor_temperature_change();

        /**
     * \brief Read wire file and parse result
     */
        std::string get_temperature();

        /**
         * \brief Lock before to read the temperature
         */
        std::string safe_get_temperature();
    };

} // namespace gpio
} // namespace bbb

#endif //BBBGPIO_THERMAL_STREAM_HPP
