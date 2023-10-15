#ifndef __BANE_COMPONENT_FACTORY__
#define __BANE_COMPONENT_FACTORY__

#include <harmful/doom/utils/Platform.hpp>
#include "harmful/bane/components/Component.hpp"
#include "harmful/bane/components/ComponentData.hpp"

namespace Bane {
    /// <summary>
    /// Base class for factories to generate and destroy Component instances.
    /// </summary>
    class ComponentFactory {
		private:
			/// <summary>
			/// List of all the created Components by the current ComponentFactory.
			/// </summary>
			std::unordered_set<Component*> m_components;

			/// <summary>
			/// List of all the created Components by the current
			/// ComponentFactory. They are listed per Entity in the order of
			/// the Entity ID.
			/// m_componentsPerEntity[entity_id][list_of_components]
			/// </summary>
			std::vector<std::vector<Component>> m_componentsPerEntity;

		public:
			/// <summary>
			/// Create a new Component instance, attached to a given Entity
			/// and store it in the ComponentFactory.
			/// </summary>
			/// <param name="entity">
			/// Entity the new Component is attached to.
			/// </param>
			/// <returns>
			/// The created Component if it can be added to the given Entity,
			/// the already attached Component in case a new one cannot be
			/// added to the Entity.
			/// </returns>
			exported Component* createComponentFor(const Entity& entity);

			/// <summary>
			/// Get the amount of Components for all Entities.
			/// </summary>
			/// <returns>
			/// Amount of Components created by the current ComponentFactory.
			/// </returns>
			exported size_t count() const {
				return m_components.size();
			}

			/// <summary>
			/// Get the amount of Components for one Entity.
			/// </summary>
			/// <param name="entity">
			/// Entity to get the amount of Components attached to it (from the
			/// current ComponentFactory).
			/// </param>
			/// <returns>
			/// Amount of Components created by the current ComponentFactory
			/// for the given Entity.
			/// </returns>
			exported size_t countFor(const Entity& entity) const;

			/// <summary>
			/// Get all the active Components in the current ComponentFactory.
			/// </summary>
			/// <returns>
			/// All the Components in the current ComponentFactory.
			/// </returns>
			exported const std::unordered_set<Component*>& components() const {
				return m_components;
			}

			/// <summary>
			/// Get all the Components attached to an Entity.
			/// </summary>
			/// <param name="entity">
			/// Entity for which getting all the Components.
			/// </param>
			/// <returns>
			/// All the Components attached to the Entity.
			/// </returns>
			exported std::list<Component*> componentsOf(const Entity& entity);

			/// <summary>
			/// Get the first Component in the list of the ones attached to an
			/// Entity.
			/// </summary>
			/// <param name="entity">
			/// Entity for which getting the first Component.
			/// </param>
			/// <returns>
			/// The first Component attached to the Entity; nullptr if the
			/// Entity is not found.
			/// </returns>
			exported Component* firstOf(const Entity& entity);

			/// <summary>
			/// Delete the Component instances born by the Entity and remove
			/// them from the ComponentFactory.
			/// </summary>
			/// <param name="entity">
			/// The Entity for which the Components must be destroyed.
			/// </param>
			exported void destroyComponentsOf(const Entity& entity);

			/// <summary>
			/// Get the allowed quantity of Component with the data type the
			/// current ComponentFactory deals with on a single Entity.
			/// </summary>
			/// <returns>
			/// Allowed quantity of Component on a single Entity.
			/// </returns>
			virtual ComponentData::Quantity allowedQuantity() = 0;

		protected:
			/// <summary>
			/// Create the ComponentData for a new Component instance.
			/// </summary>
			/// <param name="entity">
			/// Entity for which the ComponentData instance is created.
			/// </param>
			/// <returns>
			/// A new instance of ComponentData of the data type the current
			/// ComponentFactory deals with.
			/// </returns>
			virtual std::unique_ptr<ComponentData>&& createDataFor(const Entity& entity) = 0;

		private:
			/// <summary>
			/// Generic algorithm for checking if the given Entity can bear
			/// another Component with the data type the current
			/// ComponentFactory deals with.
			/// </summary>
			/// <param name="entity">Entity to be checked.</param>
			/// <returns>
			/// true if the creation is allowed for the given Entity; false
			/// otherwise.
			/// </returns>
			bool isCreationAllowedFor(const Entity& entity);

			/// <summary>
			/// Get the position of an IDObject in a zero-based container.
			/// </summary>
			/// <param name="object">Object to get the position.</param>
			/// <returns>
			/// The position of the object in a zero-based container.
			/// </returns>
			size_t position(const Doom::IDObject& object) const;
    };
}

#endif