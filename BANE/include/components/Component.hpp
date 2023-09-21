#ifndef __BANE_COMPONENT__
#define __BANE_COMPONENT__

#include <utils/Platform.hpp>
#include <utils/IDObject.hpp>
#include "entities/Entity.hpp"
#include <functional>

namespace Bane {
	/**
	 * Base class for defining a Component of the ECS architecture.
	 */
	class Component {
		public:
			/**
			 * Available quantity of a Component type on a single Entity.
			 */
			enum class Quantity : uint8_t {
				One,
				Many
			};

		private:
			/**
			 * Quantity of the current type of Component that can be
			 * attached to a single Entity.
			 */
			Quantity m_quantity = Quantity::One;

			/**
			 * Entity the current Component is attached to.
			 */
			std::reference_wrapper<Entity> m_entity;

		public:
			/**
			 * Create a new Component instance.
			 * @param quantity Quantity of Component that can be attached
             *                 to a single Entity.
			 * @param entity Entity to attach the Component to.
			 * @warning Exception thrown if entity is a null pointer.
			 */
			exported Component(
				Quantity quantity,
				Entity& entity
			);

			/**
			 * Get the Entity to which the current Component is attached to.
			 * @return Entity the current Component is attached to.
			 */
			exported Entity& entity() const {
				return m_entity;
			}

			/**
			 * Get the ID of the Entity to which the current Component is
			 * attached to.
			 * @return ID of the Entity the current Component is attached to.
			 */
			exported id_t entityID() const {
				return m_entity.get().id();
			}

			/**
			 * Check if the Entity owning the Component is valid.
			 * @return true if the Entity is valid; false otherwise.
			 */
			exported bool hasValidEntity() const {
				return m_entity.get().isValid();
			}

			/**
			 * Get the accepted quantity a the current Component type
			 * for a single Entity.
			 * @return The accepted quantity for a single Entity.
			 */
			exported Quantity quantity() const {
				return m_quantity;
			}
	};
}

#endif