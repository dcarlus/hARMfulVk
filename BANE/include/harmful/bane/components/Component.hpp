#ifndef __BANE_COMPONENT__
#define __BANE_COMPONENT__

#include <functional>
#include <harmful/doom/utils/Platform.hpp>
#include "harmful/bane/entities/Entity.hpp"
#include "harmful/bane/components/ComponentData.hpp"

namespace Bane {
	/// <summary>
	/// Component of the ECS architecture.
	/// It is a very simple structure that contains data in a composite 
	/// ComponentData class.
	/// </summary>
	class Component final {
		friend class ComponentFactory;

		private:
			/// <summary>
			/// ID of the Entity bearing the current Component.
			/// </summary>
			id_t m_entityID = 0;

			/// <summary>
			/// Data the Component contains for its process.
			/// </summary>
			std::unique_ptr<ComponentData> m_data = nullptr;

		protected:
			/// <summary>
			/// Create a new Component instance.
			/// </summary>
			/// <param name="entity">
			/// Entity to which the new Component is attached to.
			/// </param>
			/// <param name="data">Data of the new Component.</param>
			Component(
				const Entity& entity,
				std::unique_ptr<ComponentData>&& data
			);

		public:
			/// <summary>
			/// Move constructor.
			/// </summary>
			/// <param name="other">Component to be moved.</param>
			exported Component(Component&& other) = default;

			/// <summary>
			/// Destruction of the current Component instance.
			/// </summary>
			exported ~Component() = default;

			/// <summary>
			/// Get the ID of the Entity the current Component is attached to.
			/// </summary>
			/// <returns>ID of the Entity.</returns>
			exported id_t entityID() const {
				return m_entityID;
			}

			/// <summary>
			/// Get the data of the Component.
			/// </summary>
			/// <returns>Raw pointer to the inner ComponentData.</returns>
			/// <remarks>Do not try to delete the data!</remarks>
			exported ComponentData* data() const {
				return m_data.get();
			}

			/// <summary>
			/// Move operator.
			/// </summary>
			/// <param name="other">Component to be moved.</param>
			exported Component& operator=(Component&& other) = default;

		private:
			// Disable copy.
			Component(const Component& other) = delete;
			Component& operator=(const Component& other) = delete;
	};
}

#endif