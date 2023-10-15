#include "harmful/bane/entities/EntityFactory.hpp"

using namespace Bane;
using namespace Doom;

Entity EntityFactory::create() {
	Entity newEntity;
	m_entities.insert(newEntity.id());
	return newEntity;
}

void EntityFactory::destroy(const Entity& entity) {
	if (m_entities.contains(entity.id())) {
		m_entities.erase(entity.id());
	}
}

void EntityFactory::destroy(const id_t& entity) {
	if (m_entities.contains(entity)) {
		m_entities.erase(entity);
	}
}

bool EntityFactory::contains(const Entity& entity) const {
	return m_entities.contains(entity.id());
}

bool EntityFactory::contains(const id_t& entity) const {
	return m_entities.contains(entity);
}