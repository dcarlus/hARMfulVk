#include "harmful/bane/entities/Entity.hpp"
#include <harmful/doom/utils/Chrono.hpp>

using namespace Bane;
using namespace Doom;

Entity::Entity()
	: IDObject(IDObject::Generate()) {}