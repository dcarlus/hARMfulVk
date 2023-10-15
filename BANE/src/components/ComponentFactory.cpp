#include "harmful/bane/components/ComponentFactory.hpp"
#include <list>

using namespace Bane;

Component* ComponentFactory::createComponentFor(const Entity& entity) {
    size_t entityPosition = position(entity);

    if (!isCreationAllowedFor(entity)) {
        return &m_componentsPerEntity[entityPosition].back();
    }

    auto&& componentData = createDataFor(entity);
    Component newComponent(entity, std::move(componentData));

    if (m_componentsPerEntity.size() < entity.id()) {
        m_componentsPerEntity.resize(entity.id());
    }

    m_componentsPerEntity[entityPosition].push_back(std::move(newComponent));

    auto newComponentPtr = &m_componentsPerEntity[entityPosition].back();
    m_components.insert(newComponentPtr);

    return newComponentPtr;
}

size_t ComponentFactory::countFor(const Entity& entity) const {
    size_t entityPosition = position(entity);

    if (m_componentsPerEntity.size() > entity.id()) {
        return 0;
    }

    return m_componentsPerEntity[entityPosition].size();
}

std::list<Component*> ComponentFactory::componentsOf(const Entity& entity) {
    std::list<Component*> returnedList;
    size_t entityPosition = position(entity);

    if (m_componentsPerEntity.size() > entity.id()) {
        return returnedList;
    }

    for (auto& component : m_componentsPerEntity[entityPosition]) {
        returnedList.push_back(&component);
    }

    return returnedList;
}

Component* ComponentFactory::firstOf(const Entity& entity) {
    size_t entityPosition = position(entity);

    if (m_componentsPerEntity.size() > entity.id()) {
        return nullptr;
    }

    return &m_componentsPerEntity[entityPosition].front();
}

void ComponentFactory::destroyComponentsOf(const Entity& entity) {
    size_t entityPosition = position(entity);

    if (m_componentsPerEntity[entityPosition].size() == 0) {
        return;
    }

    for (auto& component : m_componentsPerEntity[entityPosition]) {
        m_components.erase(&component);
    }

    m_componentsPerEntity[entityPosition].clear();
}

bool ComponentFactory::isCreationAllowedFor(const Entity& entity) {
    size_t entityPosition = position(entity);

    auto acceptedQuantity = allowedQuantity();
    bool acceptOnlyOne = acceptedQuantity == ComponentData::Quantity::One;
    auto alreadyQuantity = m_componentsPerEntity[entityPosition].size();
    bool alreadyOne = alreadyQuantity == 1;

    if (acceptOnlyOne && alreadyOne) {
        return false;
    }

    return true;
}

size_t ComponentFactory::position(const Doom::IDObject& object) const {
    if (!object.isValid()) {
        throw std::runtime_error("");
    }

    return (object.id()) - 1;
}