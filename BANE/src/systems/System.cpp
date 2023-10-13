#include "systems/System.hpp"

using namespace Bane;

System::System(const std::string& name)
    : m_name(name) {}

void System::setup() {
    m_components = createFactory();
    m_processing = createProcessing();
}

Component* System::create(const Entity& entity) {
    auto allowedQuantity = m_components -> allowedQuantity();
    auto componentCount = m_components -> countFor(entity);

    if (allowedQuantity == ComponentData::Quantity::One) {
        if (componentCount > 0) {
            return m_components -> firstOf(entity);
        }
    }

    return m_components -> createComponentFor(entity);
}

void System::destroy(const Entity& entity) {
    m_processing -> onDelete(entity);
    m_components -> destroyComponentsOf(entity);
}

void System::link(System* system) {
    auto systemName = system -> name();
    m_linkedSystems[systemName] = system;
}

void System::unlink(System* system) {
    auto systemName = system->name();

    if (m_linkedSystems.contains(systemName)) {
        m_linkedSystems.erase(systemName);
    }
}