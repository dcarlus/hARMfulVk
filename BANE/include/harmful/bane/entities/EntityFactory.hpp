#ifndef __BANE_ENTITYFACTORY__
#define __BANE_ENTITYFACTORY__

#include "harmful/bane/entities/Entity.hpp"
#include <harmful/doom/utils/Platform.hpp>
#include <unordered_set>

namespace Bane {
	/// <summary>
	/// Factory to generate and destroy Entity instances.
	/// </summary>
	class EntityFactory final {
		private:
			/// <summary>
			/// List of the available entities in the application.
			/// </summary>
			std::unordered_set<id_t> m_entities;

		public:
			/// <summary>
			/// Create a new EntityFactory instance.
			/// </summary>
			/// <remarks>
			/// There should be only one EntityFactory by application.
			/// </remarks>
			exported EntityFactory() = default;

			/// <summary>
			/// Destruction of the EntityFactory instance.
			/// </summary>
			exported virtual ~EntityFactory() noexcept = default;

			/// <summary>
			/// Create a new Entity instance and store it in the EntityFactory.
			/// </summary>
			/// <returns>The newly created Entity.</returns>
			exported Entity create();

			/// <summary>
			/// Destroy an Entity instance and remove it from the
			/// EntityFactory.
			/// </summary>
			/// <param name="entity">Entity to delete.</param>
			exported void destroy(const Entity& entity);

			/// <summary>
			/// Destroy an Entity instance and remove it from the
			/// EntityFactory.
			/// </summary>
			/// <param name="entity">ID of the Entity to delete.</param>
			exported void destroy(const id_t& entity);

			/// <summary>
			/// Check if the given Entity exists.
			/// </summary>
			/// <param name="entity">Entity to be checked.</param>
			/// <returns>true if the Entity exists; false otherwise.</returns>
			exported bool contains(const Entity& entity) const;

			/// <summary>
			/// Check if the given Entity exists.
			/// </summary>
			/// <param name="entity">ID of the Entity to be checked.</param>
			/// <returns>true if the Entity exists; false otherwise.</returns>
			exported bool contains(const id_t& entity) const;

		private:
			// Disable copy and move.
			EntityFactory(const EntityFactory& other) = delete;
			EntityFactory(EntityFactory&& other) = delete;
			EntityFactory& operator=(const EntityFactory& other) = delete;
			EntityFactory& operator=(EntityFactory&& other) = delete;
	};
}

#endif