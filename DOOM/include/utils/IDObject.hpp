#ifndef __DOOM_IDOBJECT__
#define __DOOM_IDOBJECT__

#include "utils/Platform.hpp"
#include <cstdint>
#include <mutex>
#include <unordered_set>

namespace Doom {
    /**
     * Base class for objects that need an internally generated and managed ID.
     */
    class IDObject {
        private:
            /**
             * Invalid ID.
             */
            static const uint32_t InvalidID = 0 ;

            /**
             * Current ID to generate a new unique Entity.
             * A value of zero is invalid.
             */
            static uint32_t CurrentID ;

            /**
             * List of the available IDs from old Entities that have been
             * erased.
             */
            static std::unordered_set<uint32_t> AvailableIDs ;

            /**
             * Value of the current Entity ID.
             */
            uint32_t m_id = InvalidID ;

            /**
             * Mutex for the class data so that they can be safely handled in a
             * multithreaded context.
             */
            static std::mutex ClassMutex ;

        protected:
            /**
             * Create a new IDObject instance.
             */
            IDObject(const uint32_t id = InvalidID): m_id(id) {}

            /**
             * Generate a new ID either by incrementing the CurrentID or getting
             * an ID from the AvailableIDs list
             * @return The generated ID.
             */
            static uint32_t Generate() ;

            /**
             * Free an ID by keeping its value in AvailableIDs and setting it to
             * 0, making it invalid.
             */
            static void Free(IDObject& obj) ;

        public:
            /**
             * Get the value of the ID of the current object.
             * @return Current IDObject value.
             */
            uint32_t id() const {
                return m_id ;
            }

            /**
             * Check if the Entity ID is valid (true) or not (false).
             * @return true if valid; false otherwise.
             */
            inline bool isValid() const {
                return m_id != InvalidID ;
            }
    };
}

#endif
