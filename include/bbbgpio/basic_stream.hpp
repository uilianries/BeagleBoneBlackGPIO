/**
 * \file
 * \brief Give GPIO as stream
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#ifndef BBB_GPIO_BASIC_STREAM_HPP_
#define BBB_GPIO_BASIC_STREAM_HPP_

#include <Poco/DirectoryWatcher.h>

#include "file_descriptor.hpp"
#include "pin_level.hpp"
#include "analog_core.hpp"
#include "logic_core.hpp"

namespace bbb {
namespace gpio {

    template <class core_type, typename pin_level_type>
    /**
       * \brief Open GPIO pin as output stream
       */
    class ostream : public core_type,
                    public ofile_descriptor<pin_level_type> {
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
        ostream& operator<<(pin_level_type level);
    };

    /** Pin level type */
    template <class core_type, typename pin_level_type>
    /**
       * \brief Open GPIO pin as input stream
       */
    class istream : public core_type, public ifile_descriptor<pin_level_type> {
    public:
        /**
           * \brief Value modification event
           */
        using on_event = std::function<void(pin_level_type)>;

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
        istream& operator>>(pin_level_type& level);

        /**
           * \brief Register callback for value modification on GPIO.
           *        Only a delegate can be used, with set twice,
           *        the first will be override.
           *        To cancel the event treatment, set event to nullptr.
           * \param event delegated function to treat event
           */
        void delegate_event(on_event event) noexcept;

    private:
        /**
           * \brief Receive event from Poco. The event means that one file was
           *        changed.
           * \param p_sender handler that sent the event
           * \param event object with file path and event id
           */
        void on_directory_change(const void* p_sender,
            const Poco::DirectoryWatcher::DirectoryEvent& event);

        on_event on_event_; /**> Value event callback */
        Poco::DirectoryWatcher dir_watcher_; /**> Observes GPIO directory */
    };
} // namespace gpio
} // namespace bbb
#endif // BBB_GPIO_BASIC_STREAM_HPP_
