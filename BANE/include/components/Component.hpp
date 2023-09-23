#ifndef __BANE_COMPONENT__
#define __BANE_COMPONENT__

#include <functional>
#include <utils/Platform.hpp>
#include "entities/Entity.hpp"
#include "components/ComponentData.hpp"

namespace Bane {
	/**
	 * Component of the ECS architecture.
	 * It is a very simple structure that contains data in a composite
	 * ComponentData class.
	 */
	class Component final {
		friend class ComponentFactory;

		private:
			/**
			 * ID of the Entity bearing the current Component.
			 */
			id_t m_entityID = 0;

			/**
			 * Data the Component contains for its process.
			 */
			std::unique_ptr<ComponentData> m_data = nullptr;

		protected:
			/**
			 * Create a new Component instance.
			 * @param entity Entity to which the new Component is attached to.
			 * @param data Data of the new Component.
			 */
			Component(
				const Entity& entity,
				std::unique_ptr<ComponentData>&& data
			);

		public:
			/**
			 * Move constructor.
			 */
			exported Component(Component&& other) = default;

			/**
			 * Destruction of the current Component instance.
			 */
			exported ~Component() = default;

			/**
			 * Get the ID of the Entity the current Component is attached to.
			 * @return ID of the Entity.
			 */
			exported id_t entityID() const {
				return m_entityID;
			}

			/**
			 * Get the data of the Component.
			 * @return Raw pointer to the inner ComponentData.
			 * @warning Do not try to delete the data!
			 */
			exported ComponentData* data() const {
				return m_data.get();
			}

			/**
			 * Move operator.
			 */
			exported Component& operator=(Component&& other) = default;

		private:
			// Disable copy.
			Component(const Component& other) = delete;
			Component& operator=(const Component& other) = delete;
	};
}

#endif