#ifndef __BANE_JOB__
#define __BANE_JOB__

#include <list>
#include <vector>
#include <unordered_map>
#include <utils/Platform.hpp>
#include "entities/Entity.hpp"
#include "systems/System.hpp"
#include "jobs/ThreadJob.hpp"
#include "jobs/JobSynchronization.hpp"

namespace Bane {
    /**
     * A Job groups systems that can run in parallel and threads to execute
     * them.
     */
    class Job final {
        private:
            /**
             * Name of the Job.
             */
            std::string m_name;

            /**
             * Set of data for synchronizing the current Job with its different
             * ThreadJobs.
             */
            JobSynchronization m_syncData;

            /**
             * Systems used by the Job.
             */
            std::vector<System*> m_systems;

            /**
             * Threads for running the Job in parallel.
             */
            std::vector<ThreadJob> m_threads;

            /**
             * List of entity IDs to be dropped.
             */
            std::list<id_t> m_dropEntities;

        public:
            /**
             * Create a new Job instance.
             * @param name Name of the Job.
             * @param systems Systems used by the Job.
             * @param threadCount Amount of threads in the Job.
             */
            exported Job(
                const std::string& name,
                const std::vector<System*> systems,
                const uint8_t threadCount
            );

            /**
             * Execute the Job tasks.
             */
            exported void execute();

            /**
             * Stop the Job and all its threads.
             */
            exported void stop();

            /**
             * Get the name of the Job.
             */
            exported const std::string& name() const {
                return m_name;
            }

            /**
             * Get the Entities that the World should delete.
             */
            exported std::list<id_t>& dropEntities() {
                return m_dropEntities;
            }

        private:
            /**
             * Create the threads of the Job.
             * @param threadCount Amount of threads in the Job.
             */
            void createThreads(const uint8_t threadCount);

            /**
             * Start the threads of the Job.
             */
            void startThreads();

            /**
             * Define the work load for each ThreadJob on each system.
             */
            void defineThreadsCharge();

            /**
             * Define the amount of Components processed by each threads (the
             * thread #0 gets the extra amount of Components).
             */
            void computeThreadCharge(std::unordered_map<System*, std::vector<uint32_t>>& threadCharge);

            /**
             * Set the bounds of processing for each ThreadJob (start and end indices
             * of Components to process).
             */
            void computeThreadChargeBounds(std::unordered_map<System*, std::vector<uint32_t>>& threadCharge);
    };
}

#endif