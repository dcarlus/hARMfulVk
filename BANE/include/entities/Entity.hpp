#ifndef __BANE_ENTITY__
#define __BANE_ENTITY__

#include <utils/IDObject.hpp>

namespace Bane {
	/**
	 * Obscur ID type for an Entity.
	 */
	class Entity final : public Doom::IDObject {
		public:
			/**
			 * Create a new Entity instance.
			 */
			exported Entity();
	};
}

#endif