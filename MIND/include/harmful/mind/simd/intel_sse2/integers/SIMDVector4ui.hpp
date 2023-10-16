#ifndef __MIND__SIMD_VECTOR4_UNSIGNED_INT__
#define __MIND__SIMD_VECTOR4_UNSIGNED_INT__

#include "harmful/mind/MINDOptions.hpp"
#include "harmful/mind/simd/SIMDTypes.hpp"
#include "harmful/mind/simd/intel_sse2/integers/SIMDVector4.hpp"
#include <iostream>

namespace Mind {
    namespace SSE2 {
        /// <summary>
        /// A vector of four unsigned integer values.
        /// </summary>
        class Vector4ui : public Vector4uint32 {
            public:
                /// <summary>
                /// Create an empty vector.
                /// </summary>
                /// <remarks>
                /// The content of this vector is not guaranteed!
                /// </remarks>
                Vector4ui() ;

                /// <summary>
                /// Create a Vector4ui defining all its values.
                /// </summary>
                /// <param name="i1">First component of the Vector4ui.</param>
                /// <param name="i2">Second component of the Vector4ui.</param>
                /// <param name="i3">Third component of the Vector4ui.</param>
                /// <param name="i4">Fourth component of the Vector4ui.</param>
                Vector4ui(
                    const uint32_t& i1,
                    const uint32_t& i2,
                    const uint32_t& i3 = 0.f,
                    const uint32_t& i4 = 0.f
                ) ;

                /// <summary>
                /// Create a Vector4ui in which all values are the given one.
                /// </summary>
                /// <param name="value">
                /// The value to copy in the four components of the Vector4i.
                /// </param>
                Vector4ui(const uint32_t& value) ;

                /// <summary>
                /// Create directly from internally used data type.
                /// </summary>
                /// <param name="vec">Data using the inner data type.</param>
                Vector4ui(const __m128i vec) ;

                /// <summary>
                /// Create from data of a Vector4f.
                /// </summary>
                /// <param name="vec">
                /// Data using the inner data type of Vector4f.
                /// </param>
                Vector4ui(const __m128 vec) ;

                /// <summary>
                /// Generate a constant vector of 4 integers stored in memory.
                /// Can be converted to any integer vector type.
                /// </summary>
                /// <typeparam name="i0">First value of the Vector4ui.</typeparam>
                /// <typeparam name="i1">Second value of the Vector4ui.</typeparam>
                /// <typeparam name="i2">Third value of the Vector4ui.</typeparam>
                /// <typeparam name="i3">Fourth value of the Vector4ui.</typeparam>
                /// <returns></returns>
                template <uint32_t i0, uint32_t i1, uint32_t i2, uint32_t i3>
                static __m128i constant() ;

                /// <summary>
                /// Get a minimal Vector4ui. It is the consensus of a and b,
                /// picking only the smallest value for a given element:
                /// <code>dst[i] = min(a[i], b[i]);</code>
                /// </summary>
                /// <param name="a">First Vector4ui to test.</param>
                /// <param name="b">Second Vector4ui to test.</param>
                /// <returns>
                /// A Vector4ui containing the minimal values contained in a or
                /// b.
                /// </returns>
                static Vector4ui min(const Vector4ui& a, const Vector4ui& b) ;

                /// <summary>
                /// Get a maximal Vector4ui. It is the consensus of a and b,
                /// picking only the greatest value for a given element:
                /// <code>dst[i] = max(a[i], b[i]);</code>
                /// </summary>
                /// <param name="a">First Vector4ui to test.</param>
                /// <param name="b">Second Vector4ui to test.</param>
                /// <returns>
                /// A Vector4ui containing the maximal values contained in a or
                /// b.
                /// </returns>
                static Vector4ui max(const Vector4ui& a, const Vector4ui& b) ;

                /// <summary>
                /// Print the content of the Vector on the console output.
                /// </summary>
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
