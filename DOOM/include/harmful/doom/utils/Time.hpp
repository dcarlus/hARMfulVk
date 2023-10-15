#ifndef __DOOM_TIME__
#define __DOOM_TIME__

#include "harmful/doom/utils/Platform.hpp"
#include <string>

namespace Doom {
    /// <summary>
    /// Get the current date and time in a human-readable way.
    /// </summary>
    class exported Time final {
        public:
            /// <summary>
            /// Get a human-readable string of the current date and time.
            /// </summary>
            /// <returns>
            /// String representing the current date and time.
            /// </returns>
            static std::string GetDateTime() ;

            /// <summary>
            /// Get a human-readable string of the current date.
            /// </summary>
            /// <returns>String representing the current date.</returns>
            static std::string GetDate() ;

            /// <summary>
            /// Get a human-readable string of the current time.
            /// </summary>
            /// <returns>String representing the current time.</returns>
            static std::string GetTime() ;

        private:
            /// <summary>
            /// Disable copy of Time.
            /// </summary>
            Time(const Time&) = delete ;

            /// <summary>
            /// Disable move of Time.
            /// </summary>
            Time(Time&&) = delete ;

            /// <summary>
            /// Destruction of the Time.
            /// </summary>
            virtual ~Time() noexcept = default ;

            /// <summary>
            /// Disable affectation.
            /// </summary>
            void operator= (const Time&) = delete ;

            /// <summary>
            /// Disable move.
            /// </summary>
            void operator= (Time&&) = delete ;

            /// <summary>
            /// Get an information from the current time.
            /// </summary>
            /// <param name="format">
            /// Format of the output as the one taken by strftime.
            /// http://www.cplusplus.com/reference/ctime/strftime/
            /// </param>
            /// <param name="buffer">
            /// Buffer to get the information as a string.
            /// </param>
            /// <param name="bufferLength">
            /// Length of the buffer used to store the string.
            /// </param>
            static void GetTimeInfo(
                const std::string& format,
                char* buffer,
                const size_t bufferLength
            ) ;
    } ;
}

#endif
