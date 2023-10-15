#ifndef __DOOM__PROFILER__
#define __DOOM__PROFILER__

#include "harmful/doom/utils/Platform.hpp"
#include "harmful/doom/utils/Chrono.hpp"
#include <map>
#include <mutex>
#include <string>
#include <vector>

namespace Doom {
    /**
     * Measure execution time of one or different parts of the code.
     * @warning It is recommanded to use the macros instead of the direct used
     *          of the class. Indeed, they are more efficient for released
     *          softwares by disabling the profiler.
     */
    class Profiler final {
        private:
            /**
             * The unique instance of the Profiler.
             */
            static Profiler Instance ;

            /**
             * Avoid concurrent accesses to the Profiler.
             */
            std::mutex m_mutex ;

            /**
             * Chronos used to compute the spent time of each wanted part of the
             * code. A list of Chrono objects is used as a same portion of code
             * can be splitted into different functions and parts.
             * All the measured times are aggregated when the profiler is
             * flushed.
             */
            std::map<std::string, std::vector<Chrono>> m_chronos ;

            /**
             * Computed elapsed times when the profiler is flushed.
             * The data are available until the next call to the flush() method.
             */
            std::map<std::string, std::intmax_t> m_elapsedTimes ;

            /**
             * Instantiate the Profiler.
             */
            Profiler() ;

            /**
             * Disable copy of Profiler.
             */
            Profiler(const Profiler&) = delete ;

            /**
             * Disable move of Profiler.
             */
            Profiler(Profiler&&) = delete ;

            /**
             * Destruction of the Profiler.
             */
            ~Profiler() noexcept ;

            /**
             * Disable affectation.
             */
            void operator= (const Profiler&) = delete ;

            /**
             * Disable move.
             */
            void operator= (Profiler&&) = delete ;

        public:
            /**
             * Get the unique instance of the Profiler.
             */
            exported static Profiler& GetInstance() ;

            /**
             * Add a source of profiling. It can be named with an algorithm name
             * to measure its execution time, or a group of functions under a
             * generic name. For example, to measure the rendering time, a
             * possible name would be "Render".
             * @param name The name of the new profiling source.
             */
            exported void addProfilingSource(const std::string& name) ;

            /**
             * Start profiling for the provided source.
             * @param  name Name of the source to profile.
             * @return      ID of the profiling session for the given source.
             */
            exported int startProfiling(const std::string& name) ;

            /**
             * Stop profiling a source.
             * @param name      Name of the source to stop profiling.
             * @param sessionID ID of the session to stop profiling.
             * @warning If the @a sessionID value is invalid, all sessions are
             *          stopped.
             * @warning This function must be called in the same function than
             *          startProfiling() function.
             */
            exported void stopProfiling(const std::string& name, const int sessionID) ;

            /**
             * Flush the profiler to store data until the next flush time.
             */
            exported void flush() ;

            /**
             * Get the spent time for the given source of profiling.
             * @param  name Name of the source of profiling.
             * @return      Cumulated time for the wanted source of profiling,
             *              zero if no such source has been registered.
             * @warning This function is always available. Notice that it only
             *          returns value of previous main loop of the software,
             *          until flush() has been called.
             */
            exported std::intmax_t getTime(const std::string& name) ;
    } ;
}

    #ifdef DEBUG
        #define Profiler_AddSource(name)    Doom::Profiler::GetInstance().addProfilingSource(name)
        #define Profiler_Start(name)        int Profiler_SessionID = Doom::Profiler::GetInstance().startProfiling(name)
        #define Profiler_Stop(name)         Doom::Profiler::GetInstance().stopProfiling(name, Profiler_SessionID)
        #define Profiler_Flush()            Doom::Profiler::GetInstance().flush()
        #define Profiler_GetTime(name)      Doom::Profiler::GetInstance().getTime(name)
    #else
        #define Profiler_AddSource(name)
        #define Profiler_Start(name)
        #define Profiler_Stop(name)
        #define Profiler_Flush()
        #define Profiler_GetTime(name)      -1
    #endif

#endif
