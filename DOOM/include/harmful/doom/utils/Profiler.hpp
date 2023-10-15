#ifndef __DOOM__PROFILER__
#define __DOOM__PROFILER__

#include "harmful/doom/utils/Platform.hpp"
#include "harmful/doom/utils/Chrono.hpp"
#include <map>
#include <mutex>
#include <string>
#include <vector>

namespace Doom {
    /// <summary>
    /// Measure execution time of one or different parts of the code.
    /// </summary>
    /// <remarks>
    /// It is recommanded to use the macros instead of the direct used of the
    /// class. Indeed, they are more efficient for released softwares by
    /// disabling the profiler.
    /// </remarks>
    class Profiler final {
        private:
            /// <summary>
            /// The unique instance of the Profiler.
            /// </summary>
            static Profiler Instance ;

            /// <summary>
            /// Avoid concurrent accesses to the Profiler.
            /// </summary>
            std::mutex m_mutex ;

            /// <summary>
            /// Chronos used to compute the spent time of each wanted part of
            /// the code. A list of Chrono objects is used as a same portion of
            /// code can be splitted into different functions and parts.
            /// All the measured times are aggregated when the profiler is
            /// flushed.
            /// </summary>
            std::map<std::string, std::vector<Chrono>> m_chronos ;

            /// <summary>
            /// Computed elapsed times when the profiler is flushed.
            /// The data are available until the next call to the flush()
            /// method.
            /// </summary>
            std::map<std::string, std::intmax_t> m_elapsedTimes ;

            /// <summary>
            /// Instantiate the Profiler.
            /// </summary>
            explicit Profiler() ;

            /// <summary>
            /// Disable copy of Profiler.
            /// </summary>
            Profiler(const Profiler&) = delete ;

            /// <summary>
            /// Disable move of Profiler.
            /// </summary>
            Profiler(Profiler&&) = delete ;

            /// <summary>
            /// Destruction of the Profiler.
            /// </summary>
            virtual ~Profiler() noexcept ;

            /// <summary>
            /// Disable affectation.
            /// </summary>
            void operator= (const Profiler&) = delete ;

            /// <summary>
            /// Disable move.
            /// </summary>
            void operator= (Profiler&&) = delete ;

        public:
            /// <summary>
            /// Get the unique instance of the Profiler.
            /// </summary>
            /// <returns>The unique instance of the Profiler.</returns>
            exported static Profiler& GetInstance() ;

            /// <summary>
            /// Add a source of profiling. It can be named with an algorithm
            /// name to measure its execution time, or a group of functions
            /// under a generic name. For example, to measure the rendering
            /// time, a possible name would be "Render".
            /// </summary>
            /// <param name="name">The name of the new profiling source.</param>
            exported void addProfilingSource(const std::string& name) ;

            /// <summary>
            /// Start profiling for the provided source.
            /// </summary>
            /// <param name="name">Name of the source to profile.</param>
            /// <returns>ID of the profiling session for the given source.</returns>
            exported int startProfiling(const std::string& name) ;

            /// <summary>
            /// Stop profiling a source.
            /// </summary>
            /// <param name="name">Name of the source to stop profiling.</param>
            /// <param name="sessionID">ID of the session to stop profiling.</param>
            /// <remarks>
            /// If the sessionID value is invalid, all sessions are stopped.
            /// </remarks>
            /// <remarks>
            /// This function must be called in the same function than
            /// startProfiling() function.
            /// </remarks>
            exported void stopProfiling(const std::string& name, const int sessionID) ;

            /// <summary>
            /// Flush the profiler to store data until the next flush time.
            /// </summary>
            exported void flush() ;

            /// <summary>
            /// Get the spent time for the given source of profiling.
            /// </summary>
            /// <param name="name">Name of the source of profiling.</param>
            /// <returns>
            /// Cumulated time for the wanted source of profiling, zero if no
            /// such source has been registered.
            /// </returns>
            /// <remarks>
            /// This function is always available. Notice that it only returns
            /// value of previous main loop of the software, until flush() has
            /// been called.
            /// </remarks>
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
