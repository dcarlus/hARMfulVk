#ifndef __DOOM_CHRONO__
#define __DOOM_CHRONO__

#include "harmful/doom/utils/Platform.hpp"
#include <chrono>
#include <cstdint>

namespace Doom {
    /// <summary>
    /// Measure elapsed time.
    /// </summary>
    class Chrono final {
        private:
            /// <summary>
            /// true if the chrono is started, false if stopped.
            /// </summary>
            bool m_isStarted{ false };

            /// <summary>
            /// Time point at which the chrono has been started.
            /// </summary>
            std::chrono::time_point<std::chrono::system_clock> m_start ;

            /// <summary>
            /// Time point at which the chrono has been stopped.
            /// </summary>
            std::chrono::time_point<std::chrono::system_clock> m_end ;

        public:
            /// <summary>
            /// Start the chrono.
            /// </summary>
            exported void start() ;

            /// <summary>
            /// Stop the chrono.
            /// </summary>
            exported void stop() ;

            /// <summary>
            /// Get the elapsed time of the last chrono session.
            /// </summary>
            /// <typeparam name="ToDuration">
            /// Type of std::chrono::duration to convert the measured time.
            /// </typeparam>
            /// <returns>
            /// Amount of elapsed time during the last Chrono session.
            /// Zero is returned if the Chrono is not stopped.
            /// </returns>
            template <class ToDuration>
            exported std::intmax_t elapsedTime() {
                if (isStarted()) {
                    return 0 ;
                }

                return std::chrono::duration_cast<ToDuration>(m_end - m_start).count() ;
            }

            /// <summary>
            /// To know if the chrono is started.
            /// </summary>
            /// <returns>
            /// true if the chrono is started.
            /// false if stopped.
            /// </returns>
            exported bool isStarted() const ;
    } ;
}

#endif
