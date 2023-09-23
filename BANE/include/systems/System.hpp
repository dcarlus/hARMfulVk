#ifndef __BANE_SYSTEM__
#define __BANE_SYSTEM__

#include <utils/Platform.hpp>
#include <string>

namespace Bane {

	/**
	 * Class for defining a System of the ECS architecture.
	 */
	class System {
		private:
			/**
			 * Name of the System.
			 */
			std::string m_name;
	};
}

#endif