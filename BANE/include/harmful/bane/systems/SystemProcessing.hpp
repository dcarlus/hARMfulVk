#ifndef __BANE_SYSTEM_PROCESSING__
#define __BANE_SYSTEM_PROCESSING__

#include "harmful/bane/entities/Entity.hpp"
#include <harmful/doom/utils/Platform.hpp>
#include <functional>
#include <unordered_map>
#include <vector>

namespace Bane {
	class System;

	/// <summary>
	/// Class for processing the Components of a System.
	/// </summary>
	class SystemProcessing {
		using DropEntityList = std::vector<id_t>;

		private:
			/// <summary>
			/// List of Entities the associated System has marked as to be
			/// removed from the application.
			/// </summary>
			DropEntityList m_dropEntities;

		public:
			/// <summary>
			/// Do something when an entity is removed.
			/// </summary>
			/// <param name="entity">
			/// Entity that is about to be removed.
			/// </param>
			exported virtual void onDelete(const Entity& entity) {}

			/// <summary>
			/// Perform the Components processing.
			/// </summary>
			/// <param name="linkedSystems">
			/// List of Systems the current one relies on (dependencies).
			/// </param>
			/// <param name="fromIndex">
			/// Start index in the list of Components to process.
			/// </param>
			/// <param name="toIndex">
			/// End index in the list of Components to process.
			/// </param>
			/// <returns>
			/// A list of Entities to be removed by the World.
			/// </returns>
			exported virtual std::list<Entity> run(
				std::unordered_map<std::string, System*> linkedSystems,
				const size_t fromIndex,
				const size_t toIndex
			) = 0;

			/// <summary>
			/// Get the Entities to be dropped.
			/// </summary>
			/// <returns>The Entities to be dropped.</returns>
			exported const DropEntityList& dropEntities() const {
				return m_dropEntities;
			}

		protected:
			/// <summary>
			/// Get the Entities to be dropped. The list can be modified.
			/// </summary>
			/// <returns>The Entities to be dropped.</returns>
			exported DropEntityList& dropEntities() {
				return m_dropEntities;
			}
	};
}

#endif