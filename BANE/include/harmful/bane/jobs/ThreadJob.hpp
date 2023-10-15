#ifndef __BANE_THREAD_JOB__
#define __BANE_THREAD_JOB__

#include <thread>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <harmful/doom/utils/Platform.hpp>
#include "harmful/bane/entities/Entity.hpp"
#include "harmful/bane/systems/System.hpp"
#include "harmful/bane/jobs/JobSynchronization.hpp"

namespace Bane {
    /// <summary>
    /// Encapsulates a thread and the related stuff for running Job processing
    /// Systems itself.
    /// </summary>
    class ThreadJob final {
        private:
            /// <summary>
            /// Structure for setting the indices of start and end for the
            /// ThreadJob to process some of the Components in the list of
            /// Components to process.
            /// </summary>
            struct FromToIndices {
                size_t fromIndex;
                size_t toIndex;
            };

            /// <summary>
            /// Used to stop the ThreadJob when set to false.
            /// true by default.
            /// </summary>
            bool m_continue{ true };

            /// <summary>
            /// The inner thread that will run the Job execution.
            /// </summary>
            std::thread m_innerThread;

            /// <summary>
            /// Set of data for synchronizing the current ThreadJob with others
            /// in the complete Job.
            /// </summary>
            JobSynchronizationRW m_syncData;

            /// <summary>
            /// Systems that are processed by the ThreadJob.
            /// </summary>
            std::unordered_set<System*> m_systems;

            /// <summary>
            /// Indices of start and end for the ThreadJob to process some of
            /// the Components in the list of Components to process by the
            /// related System.
            /// </summary>
            std::unordered_map<System*, FromToIndices> m_fromToComponents;

            /// <summary>
            /// List of Entity IDs to drop after the processing of the
            /// Components by the current ThreadJob.
            /// </summary>
            std::list<Entity> m_dropEntities;

        public:
             /// <summary>
             /// Create a new ThreadJob instance.
             /// </summary>
             /// <param name="sync">
             /// Data required to synchronize threads in Jobs.
             /// </param>
             exported ThreadJob(const JobSynchronizationRW& sync);

            /**
             * Add Systems to be processed by the ThreadJob.
             * @param systems List of the Systems that will be processed by the
             *                ThreadJob.
             */

             /// <summary>
             /// Add Systems to be processed by the ThreadJob.
             /// </summary>
             /// <param name="systems">
             /// List of the Systems that will be processed by the ThreadJob.
             /// </param>
             exported void setProcessedSystems(const std::vector<System*>& systems);

             /// <summary>
             /// Set the limits of Component execution of the thread for a
             /// System.
             /// </summary>
             /// <param name="system">
             /// System for which defining the limits.
             /// </param>
             /// <param name="fromIndex">
             /// Start index in the list of Components.
             /// </param>
             /// <param name="toIndex">
             /// End index in the list of Components.
             /// </param>
             exported void setFromToComponents(
                System* system,
                const size_t fromIndex,
                const size_t toIndex
            );

             /// <summary>
             /// Start the ThreadJob.
             /// </summary>
             exported void start();

             /// <summary>
             /// Stop the ThreadJob as soon as possible.
             /// </summary>
             exported void stop();

             /// <summary>
             /// Get the ID of Entities to be removed.
             /// </summary>
             /// <returns>The list of ID of Entities to be removed.</returns>
             exported std::list<Entity> dropEntities() const {
                return m_dropEntities;
            }

        private:
            /// <summary>
            /// Function executed by the ThreadJob.
            /// </summary>
            void run();

            /// <summary>
            /// Process the Systems in the Component index bounds.
            /// </summary>
            void processSystems();
    };
}

#endif