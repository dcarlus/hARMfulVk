#ifndef __BANE_SYSTEM__
#define __BANE_SYSTEM__

#include "harmful/bane/components/ComponentFactory.hpp"
#include "harmful/bane/systems/SystemProcessing.hpp"
#include <harmful/doom/utils/Platform.hpp>
#include <unordered_map>
#include <memory>
#include <string>

namespace Bane {
	/// <summary>
	/// Class for defining a System of the ECS architecture.
	/// </summary>
	class System {
		private:
			/// <summary>
			/// Name of the System.
			/// </summary>
			std::string m_name;

			/// <summary>
			/// true if the System can be run in several threads at the same
			/// time; false if it can only run in a single thread.
			/// true is the default value.
			/// </summary>
			bool m_multithreadable{ true };

			/// <summary>
			/// List of Systems the current one relies on (dependencies).
			/// </summary>
			std::unordered_map<std::string, System*> m_linkedSystems;

			/// <summary>
			/// The factory containing the Components the System works on.
			/// </summary>
			std::unique_ptr<ComponentFactory> m_components = nullptr;

			/// <summary>
			/// Dedicated class for the processing of the Component data.
			/// </summary>
			std::unique_ptr<SystemProcessing> m_processing = nullptr;

		public:
			/// <summary>
			/// Create a new System instance.
			/// </summary>
			/// <param name="name">Name of the System.</param>
			exported System(const std::string& name);

			/// <summary>
			/// Set up the System.
			/// </summary>
			/// <remarks>
			/// This method MUST be called just after its initialization and
			/// before using the System.
			/// </remarks>
			exported void setup();

			/// <summary>
			/// If the Entity has no Component of the wanted type, it creates a
			/// new Component and attach it to the provided Entity.
			/// In the case where the Entity already has a Component of the
			/// wanted type and cannot have more than one Component of this
			/// type, it returns the previously created Component attached to
			/// that Entity.
			/// </summary>
			/// <param name="entity">
			/// Entity for which a new Component should be created.
			/// </param>
			/// <returns>A Component attached to the given Entity.</returns>
			exported Component* create(const Entity& entity);

			/// <summary>
			/// Delete the Components attached to an Entity.
			/// </summary>
			/// <param name="entity">
			/// Entity for which Components have to be deleted.
			/// </param>
			exported void destroy(const Entity& entity);

			/// <summary>
			/// Link another System to the current one.
			/// </summary>
			/// <param name="system">System to link to the current one.</param>
			exported void link(System* system);

			/**
			 * Unlink a System from the current one.
			 * @param system System to unlink from the current one.
			 */

			/// <summary>
			/// Unlink a System from the current one.
			/// </summary>
			/// <param name="system">
			/// System to unlink from the current one.
			/// </param>
			exported void unlink(System* system);

			/// <summary>
			/// Get the amount of Components managed by the current System.
			/// </summary>
			/// <returns>
			/// Amount of Components managed by the current System.
			/// </returns>
			exported size_t componentsCount() const {
				return m_components -> count();
			}

			/// <summary>
			/// Get all the Components managed by the current System.
			/// </summary>
			/// <returns>
			/// All the Components managed by the current System.
			/// </returns>
			exported const std::unordered_set<Component*>& components() const {
				return m_components -> components();
			}

			/// <summary>
			/// Get the first Component found for the given Entity.
			/// </summary>
			/// <param name="entity">
			/// The Entity to get the first Component.
			/// </param>
			/// <returns>
			/// The first Component for the given Entity; nullptr if none
			/// found.
			/// </returns>
			exported Component* componentOf(const Entity& entity) {
				return m_components -> firstOf(entity);
			}

			/// <summary>
			/// Get all the Components found for the given entity.
			/// </summary>
			/// <param name="entity">The Entity to get the Components.</param>
			/// <returns>
			/// All the Components found for the given entity.
			/// </returns>
			exported std::list<Component*> componentsOf(const Entity& entity) {
				return m_components -> componentsOf(entity);
			}

			/// <summary>
			/// Run the Components processing.
			/// </summary>
			/// <param name="fromIndex">
			/// Start index in the list of Components to process.
			/// </param>
			/// <param name="toIndex">
			/// End index in the list of Components to process.
			/// </param>
			/// <returns>
			/// A list of Entities to be removed by the World.
			/// </returns>
			exported std::list<Entity> process(
				const size_t fromIndex,
				const size_t toIndex
			) {
				return m_processing -> run(
					m_linkedSystems,
					fromIndex,
					toIndex
				);
			}

			/// <summary>
			/// Get the name of the System.
			/// </summary>
			/// <returns>Name of the System.</returns>
			exported const std::string& name() const {
				return m_name;
			}

			/// <summary>
			/// Set the multithreadable flag of the System. true is the default
			/// value.
			/// </summary>
			/// <param name="threaded">
			/// true if the System can be run in several threads at the same
			/// time; false if it can only run in a single thread.
			/// </param>
			exported void setMultithreadable(const bool threaded) {
				m_multithreadable = threaded;
			}

			/// <summary>
			/// Get the multithreadable flag of the System.
			/// </summary>
			/// <returns>
			/// true if the System can be run in several threads at the same
			/// time; false if it can only run in a single thread.
			/// true is the default value.
			/// </returns>
			exported bool isMultithreadable() const {
				return m_multithreadable;
			}

			/// <summary>
			/// Get the SystemProcessing instance of the current System.
			/// </summary>
			/// <returns>
			/// SystemProcessing instance of the current System.
			/// </returns>
			exported SystemProcessing* processing() const {
				return m_processing.get();
			}

			/// <summary>
			/// Conversion to std::string type (get the name of the System).
			/// </summary>
			/// <returns>Name of the System.</returns>
			exported operator std::string() const {
				return m_name;
			}

		protected:
			/// <summary>
			/// Create the ComponentFactory used by the System.
			/// </summary>
			/// <returns>The ComponentFactory used by the System.</returns>
			exported virtual std::unique_ptr<ComponentFactory>&& createFactory() = 0;

			/// <summary>
			/// Create the SystemProcessing used by the System.
			/// </summary>
			/// <returns>The SystemProcessing used by the System.</returns>
			exported virtual std::unique_ptr<SystemProcessing>&& createProcessing() = 0;
	};
}

#endif