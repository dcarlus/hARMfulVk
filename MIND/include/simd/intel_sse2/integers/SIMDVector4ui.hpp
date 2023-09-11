#ifndef __MIND__SIMD_VECTOR4_UNSIGNED_INT__
#define __MIND__SIMD_VECTOR4_UNSIGNED_INT__

#include "MINDOptions.hpp"
#include "simd/SIMDTypes.hpp"
#include <iostream>

#include "SIMDVector4.hpp"

namespace Mind {
    namespace SSE2 {
        class Vector4ui : public Vector4uint32 {
            public:
                                              /** CONSTRUCTION / DESTRUCTION **/
                /**
                 * Create an empty vector.
                 * @warning The content of this vector is not guaranteed!
                 */
                Vector4ui() ;

                /**
                 * Create a Vector4ui defining all its values.
                 * @param   i1  First component of the Vector4ui.
                 * @param   i2  Second component of the Vector4ui.
                 * @param   i3  Third component of the Vector4ui.
                 * @param   i4  Fourth component of the Vector4ui.
                 */
                Vector4ui(
                    const uint32_t& i1,
                    const uint32_t& i2,
                    const uint32_t& i3 = 0.f,
                    const uint32_t& i4 = 0.f
                ) ;

                /**
                 * Create a Vector4ui in which all values are the given one.
                 * @param   value   The value to copy in the four components of
                 *                  the Vector4ui.
                 */
                Vector4ui(const uint32_t& value) ;

                /**
                 * Create directly from internally used data type.
                 * @param   vec     Data using the inner data type.
                 */
                Vector4ui(const __m128i vec) ;

                /**
                 * Create from data of a Vector4f.
                 * @param   vec     Data using the inner data type of Vector4f.
                 */
                Vector4ui(const __m128 vec) ;


                                                        /** STATIC FUNCTIONS **/
                /**
                 * Generate a constant vector of 4 integers stored in memory.
                 * Can be converted to any integer vector type.
                 */
                template <uint32_t i0, uint32_t i1, uint32_t i2, uint32_t i3>
                static __m128i constant() ;

                /**
                 * Get a minimal Vector4ui. It is the consensus of a and b,
                 * picking only the smallest value for a given element:
                 * <code>
                 * dst[i] = min(a[i], b[i]) ;
                 * </code>
                 * @param     a     First Vector4ui to test.
                 * @param     b     Second Vector4ui to test.
                 * @return     A Vector4ui containing the minimal values contained
                 *            in a or b.
                 */
                static Vector4ui min(const Vector4ui& a, const Vector4ui& b) ;

                /**
                 * Get a maximal Vector4ui. It is the consensus of a and b,
                 * picking only the greatest value for a given element:
                 * <code>
                 * dst[i] = max(a[i], b[i]) ;
                 * </code>
                 * @param     a     First Vector4ui to test.
                 * @param     b     Second Vector4ui to test.
                 * @return     A Vector4ui containing the maximal values contained
                 *            in a or b.
                 */
                static Vector4ui max(const Vector4ui& a, const Vector4ui& b) ;

                /**
                 * Print the content of the Vector on the console output.
                 */
                void print() ;
        } ;

        #include "impl/Vector4/Vector4ui/operators.hpp"


        template <uint32_t i0, uint32_t i1, uint32_t i2, uint32_t i3>
        inline __m128i Vector4ui::constant() {
            static const union {
                unsigned int integer[4] ;
                __m128i vector ;
            } u = {{i0, i1, i2, i3}} ;
            return u.vector ;
        }

    } ;

} ;


#endif
