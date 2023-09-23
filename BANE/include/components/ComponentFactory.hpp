#ifndef __BANE_COMPONENT_FACTORY__
#define __BANE_COMPONENT_FACTORY__

#include <utils/Platform.hpp>
#include "components/Component.hpp"
#include "components/ComponentData.hpp"

namespace Bane {
	/**
	 * Base class for factories to generate and destroy Component instances.
	 * @warning There should be only one ComponentFactory in an application.
	 */
    class ComponentFactory {
		private:
			/**
			 * List of all the created Components by the current
			 * ComponentFactory.
			 */
			std::unordered_set<Component*> m_components;

			/**
			 * List of all the created Components by the current
			 * ComponentFactory.
			 * They are listed per Entity in the order of the Entity ID.
			 * m_componentsPerEntity[entity_id][list_of_components]
			 */
			std::vector<std::vector<Component>> m_componentsPerEntity;

		public:
			/**
			 * Create a new Component instance, attached to a given Entity
			 * and store it in the ComponentFactory.
			 * @param entity Entity the new Component is attached to.
			 * @return The created Component if it can be added to the given
			 *         Entity, nullptr if the Entity cannot bear more Component
			 *         of the component type.
			 */
			exported Component* createComponentFor(const Entity& entity);

			/**
			 * Get the amount of Components for all Entities.
			 * @return Amount of Components created by the current
			 *         ComponentFactory
			 */
			exported size_t count() const {
				return m_components.size();
			}

			/**
			 * Get all the active Components in the current ComponentFactory.
			 * @return All the Components in the current ComponentFactory.
			 */
			exported const std::unordered_set<Component*>& components() const {
				return m_components;
			}

			/**
			 * Get all the Components attached to an Entity.
			 * @param entity Entity for which getting all the Components
			 *        of type ComponentType.
			 * @return All the components attached to the Entity.
			 */
			exported std::list<Component*> componentsOf(const Entity& entity);

			/**
			 * Delete the Component instances born by the Entity and
			 * remove them from the ComponentFactory.
			 */
			exported void destroyComponentsOf(const Entity& entity);

		protected:
			/**
			 * Get the allowed quantity of Component with the data type the
			 * current ComponentFactory deals with on a single Entity.
			 * @return Allowed quantity of Component on a single Entity.
			 */
			virtual ComponentData::Quantity allowedQuantity() = 0;

			/**
			 * Create the ComponentData for a new Component instance.
			 * @return A new instance of ComponentData of the data type the
			 * current ComponentFactory deals with.
			 */
			virtual std::unique_ptr<ComponentData>&& createDataFor(const Entity& entity) = 0;

		private:
			/**
			 * Generic algorithm for checking if the given Entity can bear
			 * another Component with the data type the current
			 * ComponentFactory deals with.
			 * @return true if the creation is allowed for the given Entity;
			 *         false otherwise.
			 */
			bool isCreationAllowedFor(const Entity& entity);

			/**
			 * Get the position of an IDObject in a zero-based container.
			 */
			size_t position(const Doom::IDObject& object) const;
    };
}

#endif