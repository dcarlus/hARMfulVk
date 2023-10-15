#ifndef __BANE_WORLD__
#define __BANE_WORLD__

#include <type_traits>
#include <memory>
#include <list>
#include <set>
#include <unordered_map>
#include <harmful/doom/utils/Platform.hpp>
#include "harmful/bane/entities/EntityFactory.hpp"
#include "harmful/bane/systems/System.hpp"
#include "harmful/bane/jobs/Job.hpp"

namespace Bane {
    /// <summary>
    /// Entry class for using the ECS instances. Handles interactions between
    /// these instances as automatic data suppression. For example, it removes
    /// all the Components attached to an Entity when this one is deleted.
    /// </summary>
    class World final {
        private:
            /// <summary>
            /// Factory for creating all the Entities in the application.
            /// </summary>
            EntityFactory m_entities;

            /// <summary>
            /// List of the Entities currently active in the application.
            /// </summary>
            std::set<Entity> m_entityList;

            /// <summary>
            /// List of the Systems in the application.
            /// </summary>
            std::unordered_map<std::string, std::unique_ptr<System>> m_systems;

            /// <summary>
            /// List of the Jobs in the application.
            /// </summary>
            std::unordered_map<std::string, std::unique_ptr<Job>> m_jobs;

        public:
            // No copy nor move constructors.
            exported World(const World& other) = delete;
            exported World(World&& other) = delete;

            /// <summary>
            /// Destruction of the World instance.
            /// </summary>
            exported virtual ~World() noexcept;

            /// <summary>
            /// Clear all data of the current World.
            /// </summary>
            exported void clear();

            /// <summary>
            /// Create an Entity instance.
            /// </summary>
            /// <returns>The created Entity instance.</returns>
            exported Entity createEntity();

            /// <summary>
            /// Get a System by its name. If it does not exist, it is created.
            /// </summary>
            /// <typeparam name="SystemClass">
            /// Class of the System to get. Must inherit the System class.
            /// </typeparam>
            /// <param name="name">Name of the System to get.</param>
            /// <returns>Pointer to the wanted system.</returns>
            template <class SystemClass>
            exported SystemClass* system(const std::string& name);

            /// <summary>
            /// Add a Job used to run Systems concurrently.
            /// </summary>
            /// <param name="name">Name of the Job.</param>
            /// <param name="systemNames">
            /// Name of the Systems the new Job works on.
            /// </param>
            /// <param name="threadCount">
            /// Amount of threads required to perform the new Job.
            /// </param>
            exported void addJob(
                const std::string& name,
                std::list<std::string>& systemNames,
                const uint8_t threadCount
            );

            /// <summary>
            /// Delete an Entity and all its attached Components.
            /// </summary>
            /// <param name="entity">ID of the Entity to delete.</param>
            /// <returns></returns>
            exported void destroy(const Entity& entity);
            
            /// <summary>
            /// Run all the registered Jobs/Systems in the World.
            /// </summary>
            exported void run();

            /// <summary>
            /// Stop all the Jobs.
            /// </summary>
            exported void stop();

            // No copy nor move assignment operator.
            World& operator=(const World& other) = delete;
            World& operator=(World&& other) = delete;

        private:
            /// <summary>
            /// Remove an Entity from the Systems using it.
            /// </summary>
            /// <param name="entity">ID of the Entity to delete.</param>
            void removeEntity(const Entity& entity);
    };

    template <class SystemClass>
    SystemClass* World::system(const std::string& name) {
        static_assert(
            std::is_base_of_v<System, SystemClass>,
            "Only derived class from System can be used here."
        );

        if (!m_systems.contains(name)) {
            m_systems[name] = std::make_unique<SystemClass>(name);
        }

        return static_cast<SystemClass*>(m_systems[name].get());
    }
}

#endif