#ifndef __DOOM_IDOBJECT__
#define __DOOM_IDOBJECT__

#include "utils/Platform.hpp"
#include <cstdint>
#include <mutex>
#include <unordered_set>

using id_t = uint32_t;

namespace Doom {
    /**
     * Base class for objects that need an internally generated and managed ID.
     */
    class IDObject {
        private:
            /**
             * Invalid ID.
             */
            static const id_t InvalidID = 0 ;

            /**
             * Current ID to generate a new unique Entity.
             * A value of zero is invalid.
             */
            static id_t CurrentID ;

            /**
             * List of the available IDs from old Entities that have been
             * erased.
             */
            static std::unordered_set<id_t> AvailableIDs ;

            /**
             * Value of the current Entity ID.
             */
            id_t m_id = InvalidID ;

            /**
             * Mutex for the class data so that they can be safely handled in a
             * multithreaded context.
             */
            static std::mutex ClassMutex ;

        protected:
            /**
             * Create a new IDObject instance.
             * @param id ID of the current object.
             */
            exported IDObject(const id_t id = InvalidID): m_id(id) {}

            /**
             * Generate a new ID either by incrementing the CurrentID or getting
             * an ID from the AvailableIDs list
             * @return The generated ID.
             */
            exported static id_t Generate() ;

            /**
             * Free an ID by keeping its value in AvailableIDs and setting it to
             * 0, making it invalid.
             */
            exported static void Free(IDObject& obj) ;

        public:
            /**
             * Copy constructor.
             */
            exported IDObject(const IDObject& other) = default;

            /**
             * Move constructor.
             */
            exported IDObject(IDObject&& other) = default;

            /**
             * Destruction of the current IDObject instance.
             */
            exported virtual ~IDObject() noexcept;
            
            /**
             * Get the value of the ID of the current object.
             * @return Current IDObject value.
             */
            exported id_t id() const {
                return m_id ;
            }

            /**
             * Check if the Entity ID is valid (true) or not (false).
             * @return true if valid; false otherwise.
             */
            exported inline bool isValid() const {
                return m_id != InvalidID ;
            }

            /**
             * Check if the current IDObject is the same as another one.
             */
            exported bool operator==(const IDObject& other);

            /**
             * Check if the current IDObject is different from another one.
             */
            exported bool operator!=(const IDObject& other);

            /**
             * Check if two IDObject are equal.
             */
            friend bool operator==(
                const IDObject& left,
                const IDObject& right
            ) {
                return left.id() == right.id();
            }

            /**
             * Check if two IDObject are different.
             */
            friend bool operator!=(
                const IDObject& left,
                const IDObject& right
            ) {
                return left.id() != right.id();
            }

            /**
             * Ordering operator.
             */
            friend bool operator<(const IDObject& first, const IDObject& second) {
                return first.id() < second.id();
            }

            /**
             * Ordering operator.
             */
            friend bool operator>(const IDObject& first, const IDObject& second) {
                return first.id() > second.id();
            }

            /**
             * Copy operator.
             */
            exported IDObject& operator=(const IDObject& other) = default;

            /**
             * Move operator.
             */
            exported IDObject& operator=(IDObject&& other) = default;
    };
}

#endif
