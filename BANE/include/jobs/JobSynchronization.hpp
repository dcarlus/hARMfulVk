#ifndef __BANE_JOB_SYNCHRONIZATION__
#define __BANE_JOB_SYNCHRONIZATION__

#include <functional>
#include <condition_variable>
#include <latch>

namespace Bane {
    /**
     * Data required to synchronize threads in Jobs.
     */
    class JobSynchronization final {
        private:
            /**
             * Condition for synchronizing the different threads of a same Job
             * for making them start at the same time. Defined by the owning
             * Job of the ThreadJobs.
             */
            std::condition_variable m_condition;

            /**
             * Flag for the condition to continue waiting or not.
             */
            bool m_waitFlag;

            /**
             * Mutex used by the condition variable.
             */
            std::mutex m_mutex;

            /**
             * Latch for synchronizing the different threads of a same Job and
             * make wait after they have done their work. Defined by the owning
             * Job of the ThreadJobs.
             */
            std::latch m_latch;

        public:
            /**
             * Create a new JobSynchronization instance.
             */
            JobSynchronization(const uint8_t amountJobs)
                : m_waitFlag(true),
                  m_latch(std::latch(amountJobs)) {}

            /**
             * Get the condition variable.
             */
            std::condition_variable& condition() {
                return m_condition;
            }

            /**
             * Get the wait flag of the condition variable.
             */
            bool& waitFlag() {
                return m_waitFlag;
            }

            /**
             * Get the mutex.
             */
            std::mutex& mutex() {
                return m_mutex;
            }

            /**
             * Get the latch.
             */
            std::latch& latch() {
                return m_latch;
            }
    };

    /**
     * Data required to synchronize threads in Jobs (with reference wrappers).
     */
    class JobSynchronizationRW final {
        private:
            /**
             * Condition for synchronizing the different threads of a same Job
             * for making them start at the same time. Defined by the owning
             * Job of the ThreadJobs.
             */
            std::reference_wrapper<std::condition_variable> m_condition;

            /**
             * Flag for the condition to continue waiting or not.
             */
            std::reference_wrapper<bool> m_waitFlag;

            /**
             * Mutex used by the condition variable.
             */
            std::reference_wrapper<std::mutex> m_mutex;

            /**
             * Latch for synchronizing the different threads of a same Job and
             * make wait after they have done their work. Defined by the owning
             * Job of the ThreadJobs.
             */
            std::reference_wrapper<std::latch> m_latch;

        public:
            /**
             * Create a new JobSynchronization instance.
             */
            JobSynchronizationRW(JobSynchronization& sync)
                : m_condition(sync.condition()),
                m_waitFlag(sync.waitFlag()),
                m_mutex(sync.mutex()),
                m_latch(sync.latch()) {}

            /**
             * Get the condition variable.
             */
            std::condition_variable& condition() {
                return m_condition.get();
            }

            /**
             * Get the wait flag of the condition variable.
             */
            bool& waitFlag() {
                return m_waitFlag.get();
            }

            /**
             * Get the mutex.
             */
            std::mutex& mutex() {
                return m_mutex.get();
            }

            /**
             * Get the latch.
             */
            std::latch& latch() {
                return m_latch.get();
            }
    };
}

#endif