#ifndef __MIND__SIMD_VECTOR4__
#define __MIND__SIMD_VECTOR4__

#include "harmful/mind/MINDOptions.hpp"
#include "harmful/mind/simd/SIMDTypes.hpp"
#include "harmful/mind/MINDTypes.hpp"
#include <typeinfo>

namespace Mind {
    namespace SSE2 {
        /// <summary>
        /// A vector of four integer values.
        /// Used to optimize operations on such data structure by using SSE2
        /// instructions on Intel/AMD CPUs.
        /// 
        /// This class is highly inspired by the work of Agner Fog.
        /// http://www.agner.org/optimize/
        /// </summary>
        /// <typeparam name="Type">Type of integer value.</typeparam>
        template <typename Type>
        class Vector4 {
            public:
                #include "impl/Vector4/Mask/inner.hpp"

            protected:
                /// <summary>
                /// Inner vector data.
                /// </summary>
                Int32x4 m_inner ;

                /**
                 * 
                 * 
                 * 
                 * @param     selector     
                 *                         
                 * @param     a             
                 * @param     b             
                 * @return    
                 *            
                 */

                /// <summary>
                /// Get the combination of two inner objects. It follows this
                /// case: <code>dst[i] = selector[i] ? a[i] : b[i] ;</code>
                /// </summary>
                /// <param name="selector">
                /// Mask to select elements from a if true, from b if false.
                /// </param>
                /// <param name="a">First vector to pick values in.</param>
                /// <param name="b">Second vector to pick values in.</param>
                /// <returns>
                /// An inner data object combining a and b following th
                ///  content of selector.
                /// </returns>
                static __m128i selection(
                    const __m128i selector,
                    const __m128i a,
                    const __m128i b
                ) ;


            public:
                /// <summary>
                /// Create an empty vector.
                /// </summary>
                Vector4() ;

                /// <summary>
                /// Create a Vector4 defining all its values.
                /// </summary>
                /// <param name="f1">First component of the Vector4.</param>
                /// <param name="f2">Second component of the Vector4.</param>
                /// <param name="f3">Third component of the Vector4.</param>
                /// <param name="f4">Fourth component of the Vector4.</param>
                Vector4(
                    const Type& f1,
                    const Type& f2,
                    const Type& f3 = 0.f,
                    const Type& f4 = 0.f
                ) ;

                /// <summary>
                /// Create a Vector4 in which all values are the given one.
                /// </summary>
                /// <param name="value">
                /// The value to copy in the four components of the Vector4.
                /// </param>
                Vector4(const Type& value) ;

                /// <summary>
                /// Create directly from internally used data type.
                /// </summary>
                /// <param name="vec">Data using the inner data type.</param>
                Vector4(const __m128i vec) ;

                /// <summary>
                /// Create from data of a Vector4f.
                /// </summary>
                /// <param name="vec">
                /// Data using the inner data type of Vector4f.
                /// </param>
                Vector4(const __m128 vec) ;

                /// <summary>
                /// Compute the sum of elements in the Vector4f.
                /// </summary>
                /// <returns>The sum of all elements in Vector4.</returns>
                Type horizontalAdd() ;

                /// <summary>
                /// Get the length of the Vector4f.
                /// </summary>
                /// <returns>The length of the Vector4f.</returns>
                size_t length() const ;

                /// <summary>
                /// Size of a Vector4f.
                /// </summary>
                /// <returns>The length of a Vector4f.</returns>
                static size_t size() ;

                /// <summary>
                /// Cast the current Vector4 to its inner data type.
                /// </summary>
                operator __m128i() const ;
        } ;


        #include "impl/Vector4/Mask/operators.hpp"
        #include "impl/Vector4/Mask/impl.hpp"

        #include "impl/Vector4/impl.hpp"

        typedef Vector4<int32_t> Vector4int32 ;
        typedef Vector4<uint32_t> Vector4uint32 ;
    } ;
} ;

#endif
