#ifndef __MIND__SIMD_VECTOR4__
#define __MIND__SIMD_VECTOR4__

#include "harmful/mind/MINDOptions.hpp"
#include "harmful/mind/simd/SIMDTypes.hpp"
#include "harmful/mind/MINDTypes.hpp"
#include <typeinfo>

namespace Mind {
    namespace SSE2 {
        /**
         * A vector of four integer values.
         * Used to optimize operations on such
         * data structure by using SSE2 instructions on Intel/AMD CPUs.
         *
         * This class is highly inspired by the work of Agner Fog.
         * http://www.agner.org/optimize/
         */
        template <typename Type>
        class Vector4 {
            public:
                #include "impl/Vector4/Mask/inner.hpp"

            protected:
                /** Inner vector data. */
                Int32x4 m_inner ;

                /**
                 * Get the combination of two inner objects. It follows this
                 * case:
                 * <code>dst[i] = selector[i] ? a[i] : b[i] ;</code>
                 * @param     selector     Mask to select elements from a if TRUE,
                 *                         from b if FALSE.
                 * @param     a             First vector to pick values in.
                 * @param     b             Second vector to pick values in.
                 * @return    An inner data object combining @a a and @a b
                 *            following the content of @a selector.
                 */
                static __m128i selection(
                    const __m128i selector,
                    const __m128i a,
                    const __m128i b
                ) ;


            public:
                                              /** CONSTRUCTION / DESTRUCTION **/
                /**
                 * Create an empty vector.
                 */
                Vector4() ;

                /**
                 * Create a Vector4 defining all its values.
                 * @param   f1  First component of the Vector4.
                 * @param   f2  Second component of the Vector4.
                 * @param   f3  Third component of the Vector4.
                 * @param   f4  Fourth component of the Vector4.
                 */
                Vector4(
                    const Type& f1,
                    const Type& f2,
                    const Type& f3 = 0.f,
                    const Type& f4 = 0.f
                ) ;

                /**
                 * Create a Vector4 in which all values are the given one.
                 * @param   value   The value to copy in the four components of
                 *                  the Vector4.
                 */
                Vector4(const Type& value) ;

                /**
                 * Create directly from internally used data type.
                 * @param   vec     Data using the inner data type.
                 */
                Vector4(const __m128i vec) ;

                /**
                 * Create from data of a Vector4f.
                 * @param   vec     Data using the inner data type of Vector4f.
                 */
                Vector4(const __m128 vec) ;


                                                              /*** UTILITIES ***/
                /**
                 * Compute the sum of elements in the Vector4f.
                 * @return     The sum of all elements in Vector4.
                 */
                Type horizontalAdd() ;

                /**
                 * Get the length of the Vector4f.
                 * @return  The length of the Vector4f.
                 */
                size_t length() const ;

                /**
                 * Size of a Vector4f.
                 * @return  The length of a Vector4f.
                 */
                static size_t size() ;

                                                             /*** OPERATORS ***/
                                                            /** CAST OPERATORS **/
                /**
                 * Cast the current Vector4 to its inner data type.
                 * @return  The inner data.
                 */
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
