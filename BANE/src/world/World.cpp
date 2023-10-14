#include "world/World.hpp"

using namespace Bane;

World::~World() noexcept {
    clear();
}

void World::clear() {
    for (auto& entity : m_entityList) {
        removeEntity(entity);
    }

    m_entityList.clear();
}

Entity World::createEntity() {
    auto newEntity = m_entities.create();
    m_entityList.insert(newEntity);
    return newEntity;
}

void World::addJob(
    const std::string& name,
    std::list<std::string>& systemNames,
    const uint8_t threadCount
) {
    if (m_jobs.contains(name)) {
        return;
    }

    std::vector<System*> systems;

    for (auto& sysName : systemNames) {
        if (m_systems.contains(sysName)) {
            systems.push_back(m_systems[sysName].get());
        }
    }

    m_jobs[name] = std::make_unique<Job>(name, systems, threadCount);
}

void World::destroy(const Entity& entity) {
    removeEntity(entity);
    m_entityList.erase(entity);
}

void World::run() {
    for (auto const& [name, job] : m_jobs) {
        job -> execute();

        // Clear the entities before running the next job.
        auto& clearEntitiesList = job -> dropEntities();

        for (auto& entity : clearEntitiesList) {
            destroy(entity);
        }
    }
}

void World::stop() {
    for (auto const& [name, job] : m_jobs) {
        job -> stop();
    }
}

void World::removeEntity(const Entity& entity) {
    for (auto const& [name, system] : m_systems) {
        if (m_entities.contains(entity)) {
            system -> destroy(entity);
        }
    }

    m_entities.destroy(entity);
}