#include "EntityFactory.hpp"

using namespace Bane;
using namespace Doom;

Entity EntityFactory::create() {
	Entity newEntity;
	m_entities.insert(newEntity.id());
	return newEntity;
}

void EntityFactory::destroy(const Entity& entity) {
	/*
	        try:
            self.m_entities.remove(entity.value)
            Entity.Free(entity)
        except:
            return
	*/

	if (m_entities.count(entity.id() == 1)) {
		m_entities.erase(entity.id());
	}
}

bool EntityFactory::contains(const Entity& entity) const {
	return m_entities.count(entity.id() == 1);
}