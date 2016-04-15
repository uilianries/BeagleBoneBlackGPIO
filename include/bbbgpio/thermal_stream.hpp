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
        /** Watch directory changes */
        std::unique_ptr<Poco::DirectoryWatcher> directory_watcher_;
        /** Notify observers */
        boost::signals2::signal<void(thermal_level_type)> subject_;
        /** Wire file path */
        Poco::Path wire_file_path_;

        /**
     * \brief Treat event from Poco Dir Watcher
     * \param p_sender own object
     * \param event file changed
     */
        void on_directory_change(const void* p_sender, const Poco::DirectoryWatcher::DirectoryEvent& event);

        /**
     * \brief Read wire file and parse result
     */
        std::string get_temperature();
    };

} // namespace gpio
} // namespace bbb

#endif //BBBGPIO_THERMAL_STREAM_HPP
