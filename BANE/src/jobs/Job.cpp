#include "jobs/Job.hpp"

using namespace Bane;

Job::Job(
    const std::string& name,
    const std::vector<System*> systems,
    const uint8_t threadCount
) : m_name(name),
    m_syncData(JobSynchronization(threadCount)),
    m_systems(systems) {
    createThreads(threadCount);
    startThreads();
}

void Job::execute() {
    m_dropEntities.clear();
    defineThreadsCharge();

    // Make the threads run their loop.
    m_syncData.condition().notify_all();
    
    // Wait all threads have done their loop.
    m_syncData.syncBarrier().arrive_and_wait();
    
    // Fill the drop entities list.
    for (auto& thread : m_threads) {
        m_dropEntities.splice(
            m_dropEntities.begin(),
            thread.dropEntities()
        );
    }
}

void Job::stop() {
    for (auto& thread : m_threads) {
        thread.stop();
    }
}

void Job::createThreads(const uint8_t threadCount) {
    JobSynchronizationRW jobSync(m_syncData);

    for (uint8_t index = 0; index < threadCount; index++) {
        m_threads.push_back(ThreadJob(jobSync));
    }
}

void Job::startThreads() {
    for (auto& thread : m_threads) {
        thread.setProcessedSystems(m_systems);
        thread.start();
    }
}

void Job::defineThreadsCharge() {
    std::unordered_map<System*, std::vector<uint32_t>> threadCharge;
    computeThreadCharge(threadCharge);
    computeThreadChargeBounds(threadCharge);
}

void Job::computeThreadCharge(std::unordered_map<System*, std::vector<uint32_t>>& threadCharge) {
    size_t amountThreads = m_threads.size();

    for (auto& system : m_systems) {
        size_t amountComponents = system->componentsCount();

        if (!system->isMultithreadable()) {
            threadCharge[system].resize(amountComponents);
        }
        else {
            auto amountComponentsPerThread = static_cast<uint32_t>(amountComponents / amountThreads);
            auto extraAmountComponents = static_cast<uint32_t>(amountComponents % amountThreads);

            const auto ThreadIndexWithExtra = 0;
            threadCharge[system][ThreadIndexWithExtra] = amountComponentsPerThread + extraAmountComponents;

            for (size_t threadIndex = 1; threadIndex < amountThreads; threadIndex++) {
                threadCharge[system][threadIndex] = amountComponentsPerThread;
            }
        }
    }
}

void Job::computeThreadChargeBounds(std::unordered_map<System*, std::vector<uint32_t>>& threadCharge) {
    size_t amountThreads = m_threads.size();

    for (auto& system : m_systems) {
        uint32_t fromIndex = 0;
        uint32_t toIndex = 0;
        size_t amountThreadsForSystem = threadCharge[system].size();

        for (size_t threadIndex = 0; threadIndex < amountThreadsForSystem; threadIndex++) {
            auto& thread = m_threads[threadIndex];
            auto amountComponentsForThread = threadCharge[system][threadIndex];
            toIndex = toIndex + amountComponentsForThread;
            thread.setFromToComponents(system, fromIndex, toIndex);
            fromIndex = fromIndex + amountComponentsForThread;
        }
    }
}