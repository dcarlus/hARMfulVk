#ifndef __BANE_COMPONENT_DATA__
#define __BANE_COMPONENT_DATA__

#include <harmful/doom/utils/Platform.hpp>
#include <cstdint>

namespace Bane {
	/**
	 * Base class for defining the Component data.
	 */
	class ComponentData {
		public:
			/**
			 * Available quantity of a Component type on a single Entity.
			 */
			enum class Quantity : uint8_t {
				None,
				One,
				Many
			};

			/**
			 * The AllowedQuantity static function MUST be defined in all the
			 * subclasses of ComponentData for the related ComponentFactory
			 * is able to build it.
			 * 
			 * It defines how many Components with the same data type can be
			 * attached to a same Entity.
			 */
			static Quantity AllowedQuantity() {
				return Quantity::None;
			}
	};
}

#endif