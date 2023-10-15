#ifndef __BANE_JOB_SYNCHRONIZATION__
#define __BANE_JOB_SYNCHRONIZATION__

#include <harmful/doom/utils/Platform.hpp>
#include <functional>
#include <condition_variable>
#include <barrier>

namespace Bane {
    /// <summary>
    /// Data required to synchronize threads in Jobs.
    /// </summary>
    class JobSynchronization final {
        private:
            /// <summary>
            /// Condition for synchronizing the different threads of a same Job
            /// for making them start at the same time. Defined by the owning
            /// Job of the ThreadJobs.
            /// </summary>
            std::condition_variable m_condition;

            /// <summary>
            /// Flag for the condition to continue waiting or not.
            /// </summary>
            bool m_waitFlag;

            /// <summary>
            /// Mutex used by the condition variable.
            /// </summary>
            std::mutex m_mutex;

            /// <summary>
            /// Barrier for synchronizing the different threads of a same Job
            /// and make wait after they have done their work. Defined by the
            /// owning Job of the ThreadJobs.
            /// </summary>
            std::barrier<> m_syncBarrier;

        public:
            /// <summary>
            /// Create a new JobSynchronization instance.
            /// </summary>
            /// <param name="amountThreads">Amount of threads.</param>
            exported JobSynchronization(const uint8_t amountThreads)
                : m_waitFlag(true),
                  m_syncBarrier(std::barrier(amountThreads + 1)) {}

            /// <summary>
            /// Get the condition variable.
            /// </summary>
            /// <returns>The condition variable.</returns>
            exported std::condition_variable& condition() {
                return m_condition;
            }

            /// <summary>
            /// Get the wait flag of the condition variable.
            /// </summary>
            /// <returns>The wait flag of the condition variable.</returns>
            exported bool& waitFlag() {
                return m_waitFlag;
            }

            /// <summary>
            /// Get the mutex.
            /// </summary>
            /// <returns>The mutex.</returns>
            exported std::mutex& mutex() {
                return m_mutex;
            }

            /// <summary>
            /// Get the barrier.
            /// </summary>
            /// <returns>The barrier.</returns>
            exported std::barrier<>& syncBarrier() {
                return m_syncBarrier;
            }
    };

    /// <summary>
    /// Data required to synchronize threads in Jobs (with reference wrappers).
    /// </summary>
    class JobSynchronizationRW final {
        private:
            /// <summary>
            /// Condition for synchronizing the different threads of a same Job
            /// for making them start at the same time. Defined by the owning
            /// Job of the ThreadJobs.
            /// </summary>
            std::reference_wrapper<std::condition_variable> m_condition;

            /// <summary>
            /// Flag for the condition to continue waiting or not.
            /// </summary>
            std::reference_wrapper<bool> m_waitFlag;

            /// <summary>
            /// Mutex used by the condition variable.
            /// </summary>
            std::reference_wrapper<std::mutex> m_mutex;

            /// <summary>
            /// Barrier for synchronizing the different threads of a same Job
            /// and make wait after they have done their work. Defined by the
            /// owning Job of the ThreadJobs.
            /// </summary>
            std::reference_wrapper<std::barrier<>> m_syncBarrier;

        public:
            /// <summary>
            /// Create a new JobSynchronization instance.
            /// </summary>
            /// <param name="sync">Aggregate of the synchronization data.</param>
            exported JobSynchronizationRW(JobSynchronization& sync)
                : m_condition(sync.condition()),
                m_waitFlag(sync.waitFlag()),
                m_mutex(sync.mutex()),
                m_syncBarrier(sync.syncBarrier()) {}

            /// <summary>
            /// Get the condition variable.
            /// </summary>
            /// <returns>The condition variable.</returns>
            exported std::condition_variable& condition() {
                return m_condition.get();
            }

            /// <summary>
            /// Get the wait flag of the condition variable.
            /// </summary>
            /// <returns>The wait flag of the condition variable.</returns>
            exported bool& waitFlag() {
                return m_waitFlag.get();
            }

            /// <summary>
            /// Get the mutex.
            /// </summary>
            /// <returns>The mutex.</returns>
            exported std::mutex& mutex() {
                return m_mutex.get();
            }

            /// <summary>
            /// Get the barrier.
            /// </summary>
            /// <returns>The barrier.</returns>
            exported std::barrier<>& syncBarrier() {
                return m_syncBarrier.get();
            }
    };
}

#endif