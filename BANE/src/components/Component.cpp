#include "components/Component.hpp"

using namespace Bane;

Component::Component(
	const Entity& entity,
	std::unique_ptr<ComponentData>&& data
) : m_entityID(entity.id()),
	m_data(std::move(data)) {}