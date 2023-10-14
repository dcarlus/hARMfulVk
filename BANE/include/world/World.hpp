#ifndef __BANE_WORLD__
#define __BANE_WORLD__

#include <type_traits>
#include <memory>
#include <list>
#include <set>
#include <unordered_map>
#include <utils/Platform.hpp>
#include "entities/EntityFactory.hpp"
#include "systems/System.hpp"
#include "jobs/Job.hpp"

namespace Bane {
    /**
     * Entry class for using the ECS instances. Handles interactions between
     * these instances as automatic data suppression. For example, it removes
     * all the Components attached to an Entity when this one is deleted.
     */
    class World final {
        private:
            /**
             * Factory for creating all the Entities in the application.
             */
            EntityFactory m_entities;

            /**
             * List of the Entities currently active in the application.
             */
            std::set<Entity> m_entityList;

            /**
             * List of the Systems in the application.
             */
            std::unordered_map<std::string, std::unique_ptr<System>> m_systems;

            /**
             * List of the Jobs in the application.
             */
            std::unordered_map<std::string, std::unique_ptr<Job>> m_jobs;

        public:
            // No copy nor move constructors.
            exported World(const World& other) = delete;
            exported World(World&& other) = delete;

            /**
             * Destruction of the World instance.
             */
            exported virtual ~World() noexcept;

            /**
             * Clear all data of the current World.
             */
            exported void clear();

            /**
             * Create an Entity instance.
             * @return The created Entity instance.
             */
            exported Entity createEntity();

            /**
             * Get a System by its name. If it does not exist, it is created.
             * @param name Name of the System to get.
             * @return Pointer to the wanted system.
             */
            template <class SystemClass>
            exported SystemClass* system(const std::string& name);

            /**
             * Add a Job used to run Systems concurrently.
             */
            exported void addJob(
                const std::string& name,
                std::list<std::string>& systemNames,
                const uint8_t threadCount
            );

            /**
             * Delete an Entity and all its attached Components.
             * @param entity ID of the Entity to delete.
             */
            exported void destroy(const Entity& entity);
            
            /**
             * Run all the registered Jobs/Systems in the World.
             */
            exported void run();

            /**
             * Stop all the Jobs.
             */
            exported void stop();

            // No copy nor move assignment operator.
            World& operator=(const World& other) = delete;
            World& operator=(World&& other) = delete;

        private:
            /**
             * Remove an Entity from the Systems using it.
             * @param entity ID of the Entity to delete.
             */
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