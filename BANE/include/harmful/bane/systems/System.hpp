#ifndef __BANE_SYSTEM__
#define __BANE_SYSTEM__

#include "harmful/bane/components/ComponentFactory.hpp"
#include "harmful/bane/systems/SystemProcessing.hpp"
#include <harmful/doom/utils/Platform.hpp>
#include <unordered_map>
#include <memory>
#include <string>

namespace Bane {

	/**
	 * Class for defining a System of the ECS architecture.
	 */
	class System {
		private:
			/**
			 * Name of the System.
			 */
			std::string m_name;

			/**
			 * true if the System can be run in several threads at the same
			 * time; false if it can only run in a single thread.
			 * true is the default value.
			 */
			bool m_multithreadable{ true };

			/**
			 * List of Systems the current one relies on (dependencies).
			 */
			std::unordered_map<std::string, System*> m_linkedSystems;

			/**
			 * The factory containing the Components the System works on.
			 */
			std::unique_ptr<ComponentFactory> m_components = nullptr;

			/**
			 * Dedicated class for the processing of the Component data.
			 */
			std::unique_ptr<SystemProcessing> m_processing = nullptr;

		public:
			/**
			 * Create a new System instance.
			 */
			exported System(const std::string& name);

			/**
			 * Set up the System.
			 * @warning This method MUST be called just after its
			 *          initialization and before using the System.
			 */
			exported void setup();

			/**
			 * If the Entity has no Component of the wanted type, it creates a
			 * new Component and attach it to the provided Entity.
             * In the case where the Entity already has a Component of the
			 * wanted type and cannot have more than one Component of this
			 * type, it returns the previously created Component attached to
			 * that Entity.
			 * @param entity Entity for which a new Component should be
			 *               created.
			 */
			exported Component* create(const Entity& entity);

			/**
			 * Delete the Components attached to an Entity.
			 * @param entity Entity for which Components have to be deleted.
			 */
			exported void destroy(const Entity& entity);

			/**
			 * Link another System to the current one.
			 * @param system System to link to the current one.
			 */
			exported void link(System* system);

			/**
			 * Unlink a System from the current one.
			 * @param system System to unlink from the current one.
			 */
			exported void unlink(System* system);

			/**
			 * Get the amount of Components managed by the current System.
			 * @param Amount of Components managed by the current System.
			 */
			exported size_t componentsCount() const {
				return m_components -> count();
			}

			/**
			 * Get all the Components managed by the current System.
			 * @return All the Components managed by the current System.
			 */
			exported const std::unordered_set<Component*>& components() const {
				return m_components -> components();
			}

			/**
			 * Get the first Component found for the given Entity.
			 * @return The first Component for the given Entity; nullptr if
			 *         none found.
			 */
			exported Component* componentOf(const Entity& entity) {
				return m_components -> firstOf(entity);
			}

			/**
			 * Get all the Components found for the given entity.
			 * @return All the Components found for the given entity.
			 */
			exported std::list<Component*> componentsOf(const Entity& entity) {
				return m_components -> componentsOf(entity);
			}

			/**
			 * Run the Components processing.
			 * @return A list of Entities to be removed by the World.
			 */
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

			/**
			 * Get the name of the System.
			 * @return Name of the System.
			 */
			exported const std::string& name() const {
				return m_name;
			}

			/**
			 * Set the multithreadable flag of the System. true is the default
			 * value.
			 * @param threaded true if the System can be run in several threads
			 *                 at the same time; false if it can only run in a
			 *			       single thread.
			 */
			exported void setMultithreadable(const bool threaded) {
				m_multithreadable = threaded;
			}

			/**
			 * Get the multithreadable flag of the System.
			 * @return true if the System can be run in several threads at the
			 *         same time; false if it can only run in a single thread.
			 *         true is the default value.
			 */
			exported bool isMultithreadable() const {
				return m_multithreadable;
			}

			/**
			 * Get the SystemProcessing instance of the current System.
			 */
			exported SystemProcessing* processing() const {
				return m_processing.get();
			}

			/**
			 * Conversion to std::string type (get the name of the System).
			 */
			exported operator std::string() const {
				return m_name;
			}

		protected:
			/**
			 * Create the ComponentFactory used by the System.
			 */
			exported virtual std::unique_ptr<ComponentFactory>&& createFactory() = 0;

			/**
			 * Create the SystemProcessing used by the System.
			 */
			exported virtual std::unique_ptr<SystemProcessing>&& createProcessing() = 0;
	};
}

#endif