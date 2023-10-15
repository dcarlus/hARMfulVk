#ifndef __BANE_SYSTEM_PROCESSING__
#define __BANE_SYSTEM_PROCESSING__

#include "harmful/bane/entities/Entity.hpp"
#include <harmful/doom/utils/Platform.hpp>
#include <functional>
#include <unordered_map>
#include <vector>

namespace Bane {
	class System;

	/**
	 * Class for processing the Components of a System.
	 */
	class SystemProcessing {
		using DropEntityList = std::vector<id_t>;

		private:
			/**
			 * List of Entities the associated System has marked
			 * as to be removed from the application.
			 */
			DropEntityList m_dropEntities;

		public:
			/**
			 * Do something when an entity is removed.
			 * @param entity Entity that is about to be removed.
			 */
			exported virtual void onDelete(const Entity& entity) {}

			/**
			 * Perform the Components processing.
			 */
			exported virtual std::list<Entity> run(
				std::unordered_map<std::string, System*> linkedSystems,
				const size_t fromIndex,
				const size_t toIndex
			) = 0;

			/**
			 * Get the Entities to be dropped.
			 * @return The Entities to be dropped.
			 */
			exported const DropEntityList& dropEntities() const {
				return m_dropEntities;
			}

		protected:
			/**
			 * Get the Entities to be dropped. The list can be modified.
			 * @return The Entities to be dropped.
			 */
			exported DropEntityList& dropEntities() {
				return m_dropEntities;
			}
	};
}

#endif