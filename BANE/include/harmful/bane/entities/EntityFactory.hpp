#ifndef __BANE_ENTITYFACTORY__
#define __BANE_ENTITYFACTORY__

#include "harmful/bane/entities/Entity.hpp"
#include <harmful/doom/utils/Platform.hpp>
#include <unordered_set>

namespace Bane {
	/**
	 * Factory to generate and destroy Entity instances.
	 */
	class EntityFactory final {
		private:
			/**
			 * List of the available entities in the application.
			 */
			std::unordered_set<id_t> m_entities;

		public:
			/**
			 * Create a new EntityFactory instance.
			 * @warning There should be only one EntityFactory by application.
			 */
			exported EntityFactory() = default;

			/**
			 * Destruction of the EntityFactory instance.
			 */
			exported virtual ~EntityFactory() noexcept = default;

			/**
			 * Create a new Entity instance and store it in the EntityFactory.
			 */
			exported Entity create();

			/**
			 * Destroy an Entity instance and remove it from the EntityFactory.
			 */
			exported void destroy(const Entity& entity);

			/**
			 * Destroy an Entity instance and remove it from the EntityFactory.
			 */
			exported void destroy(const id_t& entity);

			/**
			 * Check if the given Entity exists.
			 */
			exported bool contains(const Entity& entity) const;

			/**
			 * Check if the given Entity exists.
			 */
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