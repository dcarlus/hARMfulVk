#ifndef __BANE_COMPONENT_DATA__
#define __BANE_COMPONENT_DATA__

#include <harmful/doom/utils/Platform.hpp>
#include <cstdint>

namespace Bane {
	/// <summary>
	/// Base class for defining the Component data.
	/// </summary>
	class ComponentData {
		public:
			/// <summary>
			/// Available quantity of a Component type on a single Entity.
			/// </summary>
			enum class Quantity : uint8_t {
				None,
				One,
				Many
			};

			/// <summary>
			/// The AllowedQuantity static function MUST be defined in all the
			/// subclasses of ComponentData for the related ComponentFactory
			/// is able to build it.
			/// 
			/// It defines how many Components with the same data type can be
			/// attached to a same Entity.
			/// </summary>
			/// <returns>
			/// Available quantity of a Component type on a single Entity.
			/// </returns>
			static Quantity AllowedQuantity() {
				return Quantity::None;
			}
	};
}

#endif