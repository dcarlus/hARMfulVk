#include "harmful/doom/utils/Profiler.hpp"
#include "harmful/doom/utils/Translation.hpp"
#include "harmful/doom/DOOMStrings.hpp"
#include <iostream>
#include <limits>
#include <cassert>

namespace Doom {
    Profiler Profiler::Instance ;

    Profiler::Profiler() {}

    Profiler::~Profiler() {
        m_chronos.clear() ;
        m_elapsedTimes.clear() ;
    }

    Profiler& Profiler::GetInstance() {
        return Instance ;
    }

    void Profiler::addProfilingSource(const std::string& name) {
        m_mutex.lock() ;
        {
            m_chronos[name].reserve(4) ;
        }
        m_mutex.unlock() ;
    }

    int Profiler::startProfiling(const std::string& name) {
        int sessionID = -1 ;
        m_mutex.lock() ;
        {
            if (m_chronos.count(name) == 1) {
                if (m_chronos[name].size() < std::numeric_limits<unsigned int>::max()) {
					sessionID = static_cast<int>(m_chronos[name].size()) ;

					m_chronos[name].push_back(Chrono()) ;
					m_chronos[name].back().start() ;
				}
				else {
					throw std::overflow_error(
                        Translation::Get(Texts::Profiler_SessionIDTooHigh) +
                        name
                    ) ;
				}
            }
        }
        m_mutex.unlock() ;
        return sessionID ;
    }

    void Profiler::stopProfiling(const std::string& name, const int sessionID) {
        int amountSessions = 0 ;
        m_mutex.lock() ;
        {
            if (m_chronos.count(name) == 1) {
                assert(m_chronos[name].size() < std::numeric_limits<unsigned int>::max()) ;
                amountSessions = static_cast<int>(m_chronos[name].size()) ;
            }
        }
        m_mutex.unlock() ;

        // The amount of sessions does not match with the provided session ID:
        // - either no session at all for the wanted source;
        // - or the session ID is wrong.
        // In both case, their is nothing to do.
        bool hasSession = (amountSessions > 0) ;
        bool isSessionValid = (sessionID >= 0) && (sessionID < amountSessions) ;
        if (!hasSession || !isSessionValid) {
            return ;
        }

        m_mutex.lock() ;
        {
            if (m_chronos[name][sessionID].isStarted()) {
                m_chronos[name][sessionID].stop() ;
            }
        }
        m_mutex.unlock() ;
    }

    void Profiler::flush() {
        m_mutex.lock() ;
        {
            m_elapsedTimes.clear() ;

            // Cumulate the time for each session per source.
            for (auto source : m_chronos) {
                std::intmax_t cumulatedTime = 0 ;
                for (auto chrono : source.second) {
                    cumulatedTime += chrono.elapsedTime<std::chrono::milliseconds>() ;
                }
                m_elapsedTimes[source.first] = cumulatedTime ;
            }

            m_chronos.clear() ;
        }
        m_mutex.unlock() ;
    }

    std::intmax_t Profiler::getTime(const std::string& name) {
        std::intmax_t cumulatedTime = 0 ;
        m_mutex.lock() ;
        {
            if (m_elapsedTimes.count(name) == 1) {
                cumulatedTime = m_elapsedTimes[name] ;
            }
        }
        m_mutex.unlock() ;
        return cumulatedTime ;
    }
}
