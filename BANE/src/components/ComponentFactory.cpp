#include "components/ComponentFactory.hpp"
#include <list>

using namespace Bane;

Component* ComponentFactory::createComponentFor(const Entity& entity) {
    if (!isCreationAllowedFor(entity)) {
        return nullptr;
    }

    auto&& componentData = createDataFor(entity);
    Component newComponent(entity, std::move(componentData));

    size_t entityPosition = position(entity);

    if (m_componentsPerEntity.size() < entity.id()) {
        m_componentsPerEntity.resize(entity.id());
    }

    m_componentsPerEntity[entityPosition].push_back(std::move(newComponent));

    auto newComponentPtr = &m_componentsPerEntity[entityPosition].back();
    m_components.insert(newComponentPtr);

    return newComponentPtr;
}

std::list<Component*> ComponentFactory::componentsOf(const Entity& entity) {
    std::list<Component*> returnedList;
    size_t entityPosition = position(entity);

    for (auto& component : m_componentsPerEntity[entityPosition]) {
        returnedList.push_back(&component);
    }

    return returnedList;
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