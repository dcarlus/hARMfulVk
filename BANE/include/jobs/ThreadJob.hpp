#ifndef __BANE_THREAD_JOB__
#define __BANE_THREAD_JOB__

#include <thread>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <utils/Platform.hpp>
#include "entities/Entity.hpp"
#include "systems/System.hpp"
#include "jobs/JobSynchronization.hpp"

namespace Bane {
    /**
     * Encapsulates a thread and the related stuff for running Job processing
     * Systems itself.
     */
    class ThreadJob final {
        private:
            /**
             * Structure for setting the indices of start and end for the
             * ThreadJob to process some of the Components in the list of
             * Components to process.
             */
            struct FromToIndices {
                size_t fromIndex;
                size_t toIndex;
            };

            /**
             * true by default.
             * Used to stop the ThreadJob when set to false.
             */
            bool m_continue{ true };

            /**
             * The inner thread that will run the Job execution.
             */
            std::thread m_innerThread;

            /**
             * Set of data for synchronizing the current ThreadJob with others
             * in the complete Job.
             */
            JobSynchronizationRW m_syncData;

            /**
             * Systems that are processed by the ThreadJob.
             */
            std::unordered_set<System*> m_systems;

            /**
             * Indices of start and end for the ThreadJob to process some of
             * the Components in the list of Components to process by the
             * related System.
             */
            std::unordered_map<System*, FromToIndices> m_fromToComponents;

            /**
             * List of Entity IDs to drop after the processing of the
             * Components by the current ThreadJob.
             */
            std::list<id_t> m_dropEntities;

        public:
            /**
             * Create a new ThreadJob instance.
             * @param sync Data required to synchronize threads in Jobs.
             */
             exported ThreadJob(const JobSynchronizationRW& sync);

            /**
             * Add Systems to be processed by the ThreadJob.
             * @param systems List of the Systems that will be processed by the
             *                ThreadJob.
             */
             exported void setProcessedSystems(const std::vector<System*>& systems);

            /**
             * Set the limits of Component execution of the thread for a
             * System.
             * @param system System for which defining the limits.
             * @param fromIndex Start index in the list of Components.
             * * @param toIndex End index in the list of Components.
             */
             exported void setFromToComponents(
                System* system,
                const size_t fromIndex,
                const size_t toIndex
            );

            /**
             * Start the ThreadJob.
             */
             exported void start();

            /**
             * Stop the ThreadJob as soon as possible.
             */
             exported void stop();

            /**
             * Get the ID of Entities to be removed.
             * @return The list of ID of Entities to be removed.
             */
             exported std::list<id_t> dropEntities() const {
                return m_dropEntities;
            }

        private:
            /**
             * Function executed by the ThreadJob.
             */
            void run();

            /**
             * Process the Systems in the Component index bounds.
             */
            void processSystems();
    };
}

#endif