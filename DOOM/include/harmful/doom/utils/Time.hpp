#ifndef __DOOM_TIME__
#define __DOOM_TIME__

#include "harmful/doom/utils/Platform.hpp"
#include <string>

namespace Doom {
    /**
     * Get the current date and time in a human-readable way.
     */
    class exported Time final {
        public:
            /**
             * Get a human-readable string of the current date and time.
             * @return String representing the current date and time.
             */
            static std::string GetDateTime() ;

            /**
             * Get a human-readable string of the current date.
             * @return String representing the current date.
             */
            static std::string GetDate() ;

            /**
             * Get a human-readable string of the current time.
             * @return String representing the current time.
             */
            static std::string GetTime() ;


        private:
            /**
             * Disable copy of Time.
             */
            Time(const Time&) ;

            /**
             * Disable move of Time.
             */
            Time(Time&&) noexcept ;

            /**
             * Destruction of the Time.
             */
            virtual ~Time() noexcept ;

            /**
             * Disable affectation.
             */
            void operator= (const Time&) ;

            /**
             * Disable move.
             */
            void operator= (Time&&) noexcept ;

            /**
             * Get an information from the current time.
             * @param  format       Format of the output as the one taken by
             *                      strftime.
             *                      http://www.cplusplus.com/reference/ctime/strftime/
             * @param  buffer       Buffer to get the information as a string.
             * @param  bufferLength Length of the buffer used to store the
             *                      string.
             */
            static void GetTimeInfo(
                const std::string& format,
                char* buffer,
                const size_t bufferLength
            ) ;
    } ;
}

#endif
