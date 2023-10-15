#ifndef __BANE_ENTITY__
#define __BANE_ENTITY__

#include <harmful/doom/utils/Platform.hpp>
#include <harmful/doom/utils/IDObject.hpp>

namespace Bane {
	/// <summary>
	/// Obscur ID type for an Entity.
	/// </summary>
	class Entity final : public Doom::IDObject {
		public:
			/// <summary>
			/// Create a new Entity instance.
			/// </summary>
			exported Entity();
	};
}

#endif