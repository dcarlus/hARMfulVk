#ifndef __BANE_JOB__
#define __BANE_JOB__

#include <list>
#include <vector>
#include <unordered_map>
#include <harmful/doom/utils/Platform.hpp>
#include "harmful/bane/entities/Entity.hpp"
#include "harmful/bane/systems/System.hpp"
#include "harmful/bane/jobs/ThreadJob.hpp"
#include "harmful/bane/jobs/JobSynchronization.hpp"

namespace Bane {
    /// <summary>
    /// A Job groups systems that can run in parallel and threads to execute
    /// them.
    /// </summary>
    class Job final {
        private:
            /// <summary>
            /// Name of the Job.
            /// </summary>
            std::string m_name;

            /// <summary>
            /// Set of data for synchronizing the current Job with its
            /// different ThreadJobs.
            /// </summary>
            JobSynchronization m_syncData;

            /// <summary>
            /// Systems used by the Job.
            /// </summary>
            std::vector<System*> m_systems;

            /// <summary>
            /// Threads for running the Job in parallel.
            /// </summary>
            std::vector<ThreadJob> m_threads;

            /// <summary>
            /// List of entity IDs to be dropped.
            /// </summary>
            std::list<Entity> m_dropEntities;

        public:
            /// <summary>
            /// Create a new Job instance.
            /// </summary>
            /// <param name="name">Name of the Job.</param>
            /// <param name="systems">Systems used by the Job.</param>
            /// <param name="threadCount">Amount of threads in the Job.</param>
            exported Job(
                const std::string& name,
                const std::vector<System*> systems,
                const uint8_t threadCount
            );

            /// <summary>
            /// Execute the Job tasks.
            /// </summary>
            exported void execute();

            /// <summary>
            /// Stop the Job and all its threads.
            /// </summary>
            exported void stop();

            /// <summary>
            /// Get the name of the Job.
            /// </summary>
            /// <returns>Name of the Job.</returns>
            exported const std::string& name() const {
                return m_name;
            }

            /// <summary>
            /// Get the Entities that the World should delete.
            /// </summary>
            /// <returns>List of Entities to be deleted.</returns>
            exported std::list<Entity>& dropEntities() {
                return m_dropEntities;
            }

        private:
            /// <summary>
            /// Create the threads of the Job.
            /// </summary>
            /// <param name="threadCount">Amount of threads in the Job.</param>
            void createThreads(const uint8_t threadCount);

            /// <summary>
            /// Start the threads of the Job.
            /// </summary>
            void startThreads();

            /// <summary>
            /// Define the work load for each ThreadJob on each system.
            /// </summary>
            void defineThreadsCharge();

            /// <summary>
            /// Define the amount of Components processed by each threads (the
            /// thread #0 gets the extra amount of Components).
            /// </summary>
            /// <param name="threadCharge">
            /// Workload for each thread on each System.
            /// </param>
            void computeThreadCharge(std::unordered_map<System*, std::vector<uint32_t>>& threadCharge);

            /// <summary>
            /// Set the bounds of processing for each ThreadJob (start and end
            /// indices of Components to process).
            /// </summary>
            /// <param name="threadCharge">
            /// Workload for each thread on each System.
            /// </param>
            void computeThreadChargeBounds(std::unordered_map<System*, std::vector<uint32_t>>& threadCharge);
    };
}

#endif