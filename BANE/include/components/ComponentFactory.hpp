#ifndef __BANE_COMPONENTFACTORY__
#define __BANE_COMPONENTFACTORY__

#include "entities/Entity.hpp"
#include "components/Component.hpp"
#include <unordered_set>
#include <list>
#include <vector>

namespace Bane {
	/**
	 * Factory to generate and destroy Component instances of type
	 * ComponentType.
	 * @warning There should be only one ComponentFactory per
	 *          ComponentType in an application.
	 */
	template <class ComponentType>
	class ComponentFactory {
		private:
			/**
			 * List of all the created Components of type ComponentType.
			 */
			std::unordered_set<ComponentType*> m_components;

			/**
			 * List of all the created Components of type ComponentType.
			 * They are listed per Entity in the order of the Entity ID.
			 * m_componentsPerEntity[entity_id][list_of_components]
			 */
			std::vector<std::vector<std::unique_ptr<ComponentType>>> m_componentsPerEntity;

		public:
			/**
			 * Create a new ComponentFactory instance.
			 */
			exported ComponentFactory();

			/**
			 * Create a new Component instance, attached to a given Entity
			 * and store it in the ComponentFactory.
			 * @param entity Entity the new Component is attached to.
			 * @return The created Component if it can be added to the given
			 *         Entity, nullptr if the Entity cannot bear more Component
			 *         of ComponentType type.
			 */
			exported ComponentType* createComponentFor(Entity& entity);

			/**
			 * Get the amount of Components for all Entities.
			 * @return Amount of Components of ComponentType type created
			 *	       by the current ComponentFactory
			 */
			exported size_t count() const;

			/**
			 * Get all the active Components in the current ComponentFactory.
			 * @return All the Components in the current ComponentFactory.
			 */
			exported const std::unordered_set<ComponentType*>& components() const;

			/**
			 * Get all the Components attached to an Entity.
			 * @param entity Entity for which getting all the Components
			 *        of type ComponentType.
			 * @return All the components attached to the Entity.
			 */
			exported std::list<ComponentType*> componentsOf(Entity& entity) const;

			/**
			 * Delete the Component instances born by the Entity and
			 * remove them from the ComponentFactory.
			 */
			exported void destroyComponentsOf(Entity& entity);

		private:
			/**
			 * Get the position of an IDObject in a zero-based container.
			 */
			size_t position(const Doom::IDObject& object);
	};

	template <class ComponentType>
	ComponentFactory<ComponentType>::ComponentFactory() {
		static_assert(std::is_base_of_v<Component, ComponentType>);
		m_components.reserve(512);
		m_componentsPerEntity.reserve(512);
	}

	
	template <class ComponentType>
	ComponentType* ComponentFactory<ComponentType>::createComponentFor(Entity& entity) {
		auto newComponent = std::make_unique<ComponentType>(entity);
		auto newComponentPtr = newComponent.get();

		if (m_componentsPerEntity.size() < entity.id()) {
			m_componentsPerEntity.resize(entity.id());
		}

		bool canAddComponent = true;
		size_t entityPosition = position(entity);

		if (m_componentsPerEntity[entityPosition].size() > 1) {
			auto acceptedQuantity = newComponent -> quantity();
			bool acceptOnlyOne = acceptedQuantity == Component::Quantity::One;
			auto alreadyQuantity = m_componentsPerEntity[entityPosition].size();
			bool alreadyOne = alreadyQuantity == 1;

			if (acceptOnlyOne && alreadyOne) {
				canAddComponent = false;
			}			
		}

		if (!canAddComponent) {
			return nullptr;
		}

		m_componentsPerEntity[entityPosition].push_back(std::move(newComponent));
		m_components.insert(newComponentPtr);
		return newComponentPtr;
	}

	template <class ComponentType>
	const std::unordered_set<ComponentType*>& ComponentFactory<ComponentType>::components() const {
		return m_components;
	}

	template <class ComponentType>
	size_t ComponentFactory<ComponentType>::count() const
	{
		return m_components.size();
	}

	template <class ComponentType>
	std::list<ComponentType*> ComponentFactory<ComponentType>::componentsOf(Entity& entity) const {
		std::list<ComponentType*> returnedList;
		size_t entityPosition = position(entity);

		for (auto& component : m_componentsPerEntity[entityPosition]) {
			returnedList.push_back(component.get());
		}
		
		return returnedList;
	}

	template <class ComponentType>
	void ComponentFactory<ComponentType>::destroyComponentsOf(Entity& entity) {
		size_t entityPosition = position(entity);

		if (m_componentsPerEntity[entityPosition].size() == 0) {
			return;
		}

		for (auto& component : m_componentsPerEntity[entityPosition]) {
			m_components.erase(component.get());
		}

		m_componentsPerEntity[entityPosition].clear();
	}

	template <class ComponentType>
	size_t ComponentFactory<ComponentType>::position(const Doom::IDObject& object) {
		if (!object.isValid()) {
			throw std::runtime_error("");
		}

		return (object.id()) - 1;
	}
}

#endif