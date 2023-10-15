#include "jobs/ThreadJob.hpp"

using namespace Bane;

ThreadJob::ThreadJob(const JobSynchronizationRW& sync)
    : m_syncData(sync) {}

void ThreadJob::setProcessedSystems(const std::vector<System*>& systems) {
    for (auto& system : systems) {
        m_systems.insert(system);
    }
}

void ThreadJob::setFromToComponents(
    System* system,
    const size_t fromIndex,
    const size_t toIndex
) {
    if (!m_systems.contains(system)) {
        return;
    }

    m_fromToComponents[system] = { fromIndex, toIndex };
}

void ThreadJob::start() {
    m_continue = true;
    m_innerThread = std::thread(&ThreadJob::run, this);
}

void ThreadJob::stop() {
    m_continue = false;
}

void ThreadJob::run() {
    while (m_continue) {
        std::unique_lock<std::mutex> lock(m_syncData.mutex());
        m_syncData.condition().wait(
            lock,
            [&]() { return m_syncData.waitFlag(); }
        );
        processSystems();
        m_syncData.syncBarrier().arrive_and_wait();
    }
}

void ThreadJob::processSystems() {
    for (auto& pair : m_fromToComponents) {
        auto system = pair.first;
        auto fromIndex = pair.second.fromIndex;
        auto toIndex = pair.second.toIndex;

        m_dropEntities = system -> process(fromIndex, toIndex);
    }
}