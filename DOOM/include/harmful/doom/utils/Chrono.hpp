#ifndef __DOOM_CHRONO__
#define __DOOM_CHRONO__

#include "harmful/doom/utils/Platform.hpp"
#include <chrono>
#include <cstdint>

namespace Doom {
    /**
     * Measure elapsed time.
     */
    class Chrono final {
        private:
            /**
             * TRUE if the chrono is started, FALSE if stopped.
             */
            bool m_isStarted = false ;

            /**
             * Time point at which the chrono has been started.
             */
            std::chrono::time_point<std::chrono::system_clock> m_start ;

            /**
             * Time point at which the chrono has been stopped.
             */
            std::chrono::time_point<std::chrono::system_clock> m_end ;

        public:
            /**
             * Start the chrono.
             */
            exported void start() ;

            /**
             * Stop the chrono.
             */
            exported void stop() ;

            /**
             * Get the elapsed time of the last chrono session.
             * @return  Amount of elapsed time during the last Chrono
             *          session. Zero is returned if the Chrono is not
             *          stopped.
             */
            template <class ToDuration>
            exported std::intmax_t elapsedTime() {
                if (isStarted()) {
                    return 0 ;
                }

                return std::chrono::duration_cast<ToDuration>(m_end - m_start).count() ;
            }

            /**
             * To know if the chrono is started.
             * @return TRUE if the chrono is started, FALSE if stopped.
             */
            exported bool isStarted() const ;
    } ;
}

#endif
