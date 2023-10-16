#ifndef __MIND__SIMD_VECTOR4_INT__
#define __MIND__SIMD_VECTOR4_INT__

#include "harmful/mind/MINDOptions.hpp"
#include "harmful/mind/simd/SIMDTypes.hpp"
#include "harmful/mind/simd/intel_sse2/integers/SIMDVector4.hpp"
#include <iostream>

namespace Mind {
    namespace SSE2 {
        /// <summary>
        /// A vector of four integer values.
        /// </summary>
        class Vector4i : public Vector4int32 {
            public:
                /// <summary>
                /// Create an empty vector.
                /// </summary>
                /// <remarks>
                /// The content of this vector is not guaranteed!
                /// </remarks>
                Vector4i() ;

                /// <summary>
                /// Create a Vector4i defining all its values.
                /// </summary>
                /// <param name="i1">First component of the Vector4i.</param>
                /// <param name="i2">Second component of the Vector4i.</param>
                /// <param name="i3">Third component of the Vector4i.</param>
                /// <param name="i4">Fourth component of the Vector4i.</param>
                Vector4i(
                    const int32_t& i1,
                    const int32_t& i2,
                    const int32_t& i3 = 0.f,
                    const int32_t& i4 = 0.f
                ) ;

                /// <summary>
                /// Create a Vector4i in which all values are the given one.
                /// </summary>
                /// <param name="value">
                /// The value to copy in the four components of the Vector4i.
                /// </param>
                Vector4i(const int32_t& value) ;

                /// <summary>
                /// Create directly from internally used data type.
                /// </summary>
                /// <param name="vec">Data using the inner data type.</param>
                Vector4i(const __m128i vec) ;

                /// <summary>
                /// Create from data of a Vector4f.
                /// </summary>
                /// <param name="vec">
                /// Data using the inner data type of Vector4f.
                /// </param>
                Vector4i(const __m128 vec) ;

                /// <summary>
                /// Generate a constant vector of 4 integers stored in memory.
                /// Can be converted to any integer vector type.
                /// </summary>
                /// <typeparam name="i0">First value of the Vector4i.</typeparam>
                /// <typeparam name="i1">Second value of the Vector4i.</typeparam>
                /// <typeparam name="i2">Third value of the Vector4i.</typeparam>
                /// <typeparam name="i3">Fourth value of the Vector4i.</typeparam>
                /// <returns></returns>
                template <int32_t i0, int32_t i1, int32_t i2, int32_t i3>
                static __m128i constant() ;

                /// <summary>
                /// Get a minimal Vector4i. It is the consensus of a and b,
                /// picking only the smallest value for a given element:
                /// <code>dst[i] = min(a[i], b[i]);</code>
                /// </summary>
                /// <param name="a">First Vector4i to test.</param>
                /// <param name="b">Second Vector4i to test.</param>
                /// <returns>
                /// A Vector4i containing the minimal values contained in a or
                /// b.
                /// </returns>
                static Vector4i min(const Vector4i& a, const Vector4i& b) ;

                /// <summary>
                /// Get a maximal Vector4i. It is the consensus of a and b,
                /// picking only the greatest value for a given element:
                /// <code>dst[i] = max(a[i], b[i]);</code>
                /// </summary>
                /// <param name="a">First Vector4i to test.</param>
                /// <param name="b">Second Vector4i to test.</param>
                /// <returns>
                /// A Vector4i containing the maximal values contained in a or
                /// b.
                /// </returns>
                static Vector4i max(const Vector4i& a, const Vector4i& b) ;

                /// <summary>
                /// Get a copy of the given Vector4i in which all elements are
                /// absolute values.
                /// </summary>
                /// <param name="vec">
                /// Vector4i to get its absolute values.
                /// </param>
                /// <returns>
                /// Vector4i in which the values are absolute values from vec.
                /// </returns>
                static Vector4i abs(const Vector4i& vec) ;

                /// <summary>
                /// Print the content of the Vector on the console output.
                /// </summary>
                void print() ;
        } ;

        #include "impl/Vector4/Vector4i/operators.hpp"
        #include "impl/Vector4/Vector4i/impl.hpp"
    } ;
} ;


#endif
