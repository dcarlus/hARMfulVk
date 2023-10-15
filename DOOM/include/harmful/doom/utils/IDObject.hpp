#ifndef __DOOM_IDOBJECT__
#define __DOOM_IDOBJECT__

#include "harmful/doom/utils/Platform.hpp"
#include <cstdint>
#include <mutex>
#include <unordered_set>

using id_t = uint32_t;

namespace Doom {
    /// <summary>
    /// Base class for objects that need an internally generated and managed ID.
    /// </summary>
    class IDObject {
        private:
            /// <summary>
            /// Invalid ID.
            /// </summary>
            static const id_t InvalidID = 0 ;

            /// <summary>
            /// Current ID to generate a new unique Entity.
            /// A value of zero is invalid.
            /// </summary>
            static id_t CurrentID ;

            /// <summary>
            /// List of the available IDs from old Entities that have been
            /// erased.
            /// </summary>
            static std::unordered_set<id_t> AvailableIDs ;

            /// <summary>
            /// Mutex for the class data so that they can be safely handled in
            /// a multithreaded context.
            /// </summary>
            static std::mutex ClassMutex;

            /// <summary>
            /// Value of the current Entity ID.
            /// </summary>
            id_t m_id = InvalidID ;

        protected:
            /// <summary>
            /// Create a new IDObject instance.
            /// </summary>
            /// <param name="id">ID of the current object.</param>
            exported IDObject(const id_t id = InvalidID): m_id(id) {}

            /// <summary>
            /// Generate a new ID either by incrementing the CurrentID or
            /// getting an ID from the AvailableIDs list.
            /// </summary>
            /// <returns>The generated ID.</returns>
            exported static id_t Generate() ;

            /// <summary>
            /// Free an ID by keeping its value in AvailableIDs and setting it
            /// to 0, making it invalid.
            /// </summary>
            /// <param name="obj">The object to free the ID.</param>
            exported static void Free(IDObject& obj) ;

        public:
            /// <summary>
            /// Copy constructor.
            /// </summary>
            /// <param name="other">Object to copy.</param>
            exported IDObject(const IDObject& other) = default;

            /// <summary>
            /// Move constructor.
            /// </summary>
            /// <param name="other">Object to move.</param>
            exported IDObject(IDObject&& other) = default;

            /// <summary>
            /// Destruction of the current IDObject instance.
            /// </summary>
            /// 
            exported virtual ~IDObject() noexcept;
            
            /// <summary>
            /// Get the value of the ID of the current object.
            /// </summary>
            /// <returns>Current IDObject value.</returns>
            exported id_t id() const {
                return m_id ;
            }

            /// <summary>
            /// Check if the Entity ID is valid (true) or not (false).
            /// </summary>
            /// <returns>true if valid; false otherwise.</returns>
            exported inline bool isValid() const {
                return m_id != InvalidID ;
            }

            /// <summary>
            /// Check if the current IDObject is the same as another one.
            /// </summary>
            /// <param name="other">Other object to compare.</param>
            /// <returns>
            /// true if the IDs of the current and the other object are equal;
            /// false otherwise.
            /// </returns>
            exported bool operator==(const IDObject& other);

            /// <summary>
            /// Check if the current IDObject is different from another one.
            /// </summary>
            /// <param name="other">Other object to compare.</param>
            /// <returns>
            /// true if the IDs of the current and the other object are
            /// different; false otherwise.
            /// </returns>
            exported bool operator!=(const IDObject& other);

            /// <summary>
            /// Check if two IDObject are equal.
            /// </summary>
            /// <param name="left">First object to compare.</param>
            /// <param name="right">Second object to compare.</param>
            /// <returns>
            /// true if the IDs of the current and the other object are equal;
            /// false otherwise.
            /// </returns>
            friend bool operator==(
                const IDObject& left,
                const IDObject& right
            ) {
                return left.id() == right.id();
            }

            /// <summary>
            /// Check if the current IDObject is different from another one.
            /// </summary>
            /// <param name="left">First object to compare.</param>
            /// <param name="right">Second object to compare.</param>
            /// <returns>
            /// true if the IDs of the current and the other object are
            /// different; false otherwise.
            /// </returns>
            friend bool operator!=(
                const IDObject& left,
                const IDObject& right
            ) {
                return left.id() != right.id();
            }

            /// <summary>
            /// Ordering operator.
            /// </summary>
            /// <param name="left">First object to compare.</param>
            /// <param name="right">Second object to compare.</param>
            /// <returns>
            /// true if the id of the first object is lower than the id of the
            /// second object; false on the contrary.
            /// </returns>
            friend bool operator<(const IDObject& first, const IDObject& second) {
                return first.id() < second.id();
            }

            /// <summary>
            /// Ordering operator.
            /// </summary>
            /// <param name="left">First object to compare.</param>
            /// <param name="right">Second object to compare.</param>
            /// <returns>
            /// true if the id of the first object is greater than the id of
            /// the second object; false on the contrary.
            /// </returns>
            friend bool operator>(const IDObject& first, const IDObject& second) {
                return first.id() > second.id();
            }

            /// <summary>
            /// Copy operator.
            /// </summary>
            /// <param name="other">Object to copy.</param>
            /// <returns>Reference to the current object.</returns>
            exported IDObject& operator=(const IDObject& other) = default;

            /// <summary>
            /// Move operator.
            /// </summary>
            /// <param name="other">Object to move</param>
            /// <returns>Reference to the current object.</returns>
            exported IDObject& operator=(IDObject&& other) = default;
    };
}

#endif
