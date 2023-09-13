#include "entities/Entity.hpp"

#include <utils/Chrono.hpp>

using namespace Bane;
using namespace Doom;

Entity::Entity()
	: IDObject(IDObject::Generate()) {}