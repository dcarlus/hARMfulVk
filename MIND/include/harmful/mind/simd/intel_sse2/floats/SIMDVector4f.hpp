#ifndef __MIND__SIMD_VECTOR4_FLOAT__
#define __MIND__SIMD_VECTOR4_FLOAT__

#include <typeinfo>
#include "harmful/mind/simd/SIMDTypes.hpp"
#include "harmful/mind/MINDTypes.hpp"
#include "harmful/mind/simd/intel_sse2/integers/SIMDVector4.hpp"
#include "harmful/mind/simd/intel_sse2/integers/SIMDVector4i.hpp"
#include "harmful/mind/simd/intel_sse2/integers/SIMDVector4ui.hpp"

namespace Mind {
    namespace SSE2 {
        /// <summary>
        /// A vector of four single float values.
        /// Used to optimize operations on such data structure by using SSE2
        /// instructions on Intel/AMD CPUs.
        /// 
        /// This class is highly inspired by the work of Agner Fog.
        /// http://www.agner.org/optimize/
        /// </summary>
        class Vector4f {
            public:
                #include "impl/Vector4f/Mask/inner.hpp"

            private:
                /// <summary>
                /// Inner vector data.
                /// </summary>
                Float32x4 m_inner ;

                /// <summary>
                /// Get the combination of two inner objects. It
                /// follows this case:
                /// <code>dst[i] = selector[i] ? a[i] : b[i] ;</code>
                /// </summary>
                /// <param name="selector">
                /// Mask to select elements from a if true, from b if false.
                /// </param>
                /// <param name="a">First vector to pick values in.</param>
                /// <param name="b">Second vector to pick values in.</param>
                /// <returns>
                /// An inner data object combining a and b following the
                /// content of selector.
                /// </returns>
                static __m128 selection(
                    const __m128 selector,
                    const __m128 a,
                    const __m128 b
                ) ;

            public:
                /// <summary>
                /// Create an empty vector.
                /// </summary>
                Vector4f() ;

                /// <summary>
                /// Create a Vector4f defining all its values.
                /// </summary>
                /// <param name="f1">First component of the Vector4f.</param>
                /// <param name="f2">Second component of the Vector4f.</param>
                /// <param name="f3">Third component of the Vector4f.</param>
                /// <param name="f4">Fourth component of the Vector4f.</param>
                Vector4f(
                    const Scalar f1,
                    const Scalar f2,
                    const Scalar f3 = 0.f,
                    const Scalar f4 = 0.f
                ) ;

                /// <summary>
                /// Create a Vector4f in which all values are the given one.
                /// </summary>
                /// <param name="value">
                /// The value to copy in the four components of the Vector4f.
                /// </param>
                Vector4f(const Scalar value) ;

                /// <summary>
                /// Create directly from internally used data type.
                /// </summary>
                /// <param name="vec">
                /// Data using the inner data type.
                /// </param>
                Vector4f(const __m128 vec) ;

                /// <summary>
                /// Compute the sum of elements in the Vector4f.
                /// </summary>
                /// <returns>The sum of all elements in Vector4f.</returns>
                Scalar horizontalAdd() ;

                /// <summary>
                /// Compute the difference of elements in the Vector4f.
                /// </summary>
                /// <returns>
                /// The difference of all elements in Vector4f.
                /// </returns>
                Scalar horizontalSub() ;

                /// <summary>
                /// Make all values of the current Vector4f to absolute values.
                /// </summary>
                void abs() ;

                /// <summary>
                /// Multiply each value of the current Vector4f by itself.
                /// </summary>
                void squared() ;

                /**
                 * 
                 * 
                 * 
                 * 
                 * 
                 * 
                 *            
                 * 
                 * 
                 * 
                 * </code>
                 * @warning Cause an assertion fail if template values are not
                 *          inside interval [-1 ; 3].
                 */

                /// <summary>
                /// Permute elements in the current Vector4f.
                /// The new positions are set into the template.
                /// Positions can be set between 0 and 3 for existing positions.
                /// If position is set to -1, it is zeroed.
                /// 
                /// <code>
                /// Vector4f vec4f ;
                /// // Rotate positions.
                /// permute<3,0,1,2>(vec4f) ;
                /// // Zero in the first value.
                /// permute<-1,1,2,3>(vec4f) ;
                /// </code>
                /// </summary>
                /// <typeparam name="i0">New position of the first value.</typeparam>
                /// <typeparam name="i1">New position of the second value.</typeparam>
                /// <typeparam name="i2">New position of the third value.</typeparam>
                /// <typeparam name="i3">New position of the fourth value.</typeparam>
                template <int i0, int i1, int i2, int i3>
                void permute() ;

                /// <summary>
                /// Change the sign of elements in the current Vector4f.
                /// <code>
                /// Vector4f vec4f ;
                /// // Invert sign of first value
                /// changeSign<1,0,0,0>(vec4f) ;
                /// </code>
                /// </summary>
                /// <typeparam name="i0">true to change the sign of the first value.</typeparam>
                /// <typeparam name="i1">true to change the sign of the second value.</typeparam>
                /// <typeparam name="i2">true to change the sign of the third value.</typeparam>
                /// <typeparam name="i3">true to change the sign of the fourth value.</typeparam>
                template <bool i0, bool i1, bool i2, bool i3>
                void changeSign() ;

                /// <summary>
                /// Add elements of another Vector4f for which the mask is true:
                /// <code>
                /// this[i] = mask[i] ? this[i] + add[i] : this[i] ;
                /// </code>
                /// </summary>
                /// <param name="mask">Mask to add some elements only.</param>
                /// <param name="add">
                /// The Vector4f to add to the current one for values being
                /// true in the Mask.
                /// </param>
                void addIf(const Mask& mask, const Vector4f& add) ;

                /// <summary>
                /// Multiply elements of another Vector4f for which the mask is
                /// true:
                /// <code>
                /// this[i] = mask[i] ? this[i] * mul[i] : this[i] ;
                /// </code>
                /// </summary>
                /// <param name="mask">Mask to add some elements only.</param>
                /// <param name="mul">
                /// The Vector4f to mulitply to the current one for values
                /// being true in the Mask.
                /// </param>
                void mulIf(const Mask& mask, const Vector4f& mul) ;

                /// <summary>
                /// Get the dot product of the current Vector4f with another
                /// one.
                /// </summary>
                /// <param name="other">
                /// The other Vector4f to compute dot product.
                /// </param>
                /// <returns>Dot product of the two Vector4f.</returns>
                Scalar dot(const Vector4f& other) const ;

                /// <summary>
                /// Compute the cross product of the current Vector4f with an
                /// other one.
                /// </summary>
                /// <param name="other">
                /// The second operand of the cross product.
                /// </param>
                /// <returns>Resulting Vector4f of the cross product.</returns>
                Vector4f cross(const Vector4f& other) const ;

                /// <summary>
                /// Compute the norm of the Vector4f.
                /// </summary>
                /// <returns>The norm of the Vector4f.</returns>
                Scalar norm() const ;

                /// <summary>
                /// Get the combination of two Vector4f objects. It follows
                /// this case:
                /// <code>dst[i] = selector[i] ? a[i] : b[i] ;</code>
                /// </summary>
                /// <param name="selector">
                /// Mask to select elements from a if true, from b if false.
                /// </param>
                /// <param name="a">First Vector4f to pick values in.</param>
                /// <param name="b">Second Vector4f to pick values in.</param>
                /// <returns>
                /// A Vector4f combining a and b following the content of
                /// selector.
                /// </returns>
                static Vector4f select(
                    const Mask& selector,
                    const Vector4f& a,
                    const Vector4f& b
                ) ;

                /// <summary>
                /// Shuffle the values in a Vector4f and return the
                /// corresponding result.
                /// </summary>
                /// <typeparam name="i0">New position of the first value.</typeparam>
                /// <typeparam name="i1">New position of the second value.</typeparam>
                /// <typeparam name="i2">New position of the third value.</typeparam>
                /// <typeparam name="i3">New position of the fourth value.</typeparam>
                /// <param name="input">
                /// Vector from which value must be shuffled.
                /// </param>
                /// <param name="output">Resulting shuffle.</param>
                /// <returns>
                /// Same reference as output for convenient use.
                /// </returns>
                template <unsigned char i0, unsigned char i1, unsigned char i2, unsigned char i3>
                static Vector4f& shuffle(
                    const Vector4f& input,
                    Vector4f& output
                ) ;

                /// <summary>
                /// Get a minimal Vector4f. It is the consensus of a and b,
                /// picking only the smallest value for a given element:
                /// <code>
                /// dst[i] = min(a[i], b[i]);
                /// </code>
                /// </summary>
                /// <param name="a">First Vector4f to test.</param>
                /// <param name="b">Second Vector4f to test.</param>
                /// <returns>
                /// A Vector4f containing the minimal values contained in a or
                /// b.
                /// </returns>
                static Vector4f min(const Vector4f& a, const Vector4f& b) ;

                /// <summary>
                /// Get a maximal Vector4f. It is the consensus of a and b,
                /// picking only the greatest value for a given element:
                /// <code>
                /// dst[i] = max(a[i], b[i]);
                /// </code>
                /// </summary>
                /// <param name="a">First Vector4f to test.</param>
                /// <param name="b">Second Vector4f to test.</param>
                /// <returns>
                /// A Vector4f containing the maximal values contained in a or
                /// b.
                /// </returns>
                static Vector4f max(const Vector4f& a, const Vector4f& b) ;

                /// <summary>
                /// Get a copy of the given Vector4f in which all elements are
                /// absolute values.
                /// </summary>
                /// <param name="vec">
                /// Vector4f to get its absolute values.
                /// </param>
                /// <returns>
                /// Vector4f in which the values are absolute values from vec.
                /// </returns>
                static Vector4f abs(const Vector4f& vec) ;

                #if defined (USE_INTEL_SSE4_1)
                    /// <summary>
                    /// Get a copy of the given Vector4f in which all elements
                    /// are rounded values to closer integer.
                    /// </summary>
                    /// <param name="vec">
                    /// Vector4f to get its absolute values.
                    /// </param>
                    /// <returns>
                    /// Vector4f in which the values are the closer integer
                    /// value.
                    /// </returns>
                    static Vector4f round(const Vector4f& vec) ;

                    /// <summary>
                    /// Get a copy of the given Vector4f in which all elements
                    /// are nearest lower values.
                    /// </summary>
                    /// <param name="vec">
                    /// Vector4f to get its absolute values.
                    /// </param>
                    /// <returns>
                    /// Vector4f in which the values are the closer lower
                    /// integer value.
                    /// </returns>
                    static Vector4f floor(const Vector4f& vec) ;

                    /// <summary>
                    /// Get a copy of the given Vector4f in which all elements
                    /// are nearest upper values.
                    /// </summary>
                    /// <param name="vec">
                    /// Vector4f to get its absolute values.
                    /// </param>
                    /// <returns>
                    /// Vector4f in which the values are the closer upper
                    /// integer value.
                    /// </returns>
                    static Vector4f ceil(const Vector4f& vec) ;
                #endif

                /// <summary>
                /// Compute squareroot for each element of vec.
                /// </summary>
                /// <param name="vec">
                /// Values for which to get squareroot.
                /// </param>
                /// <returns>
                /// A Vector4f containing the squareroots of elements from vec.
                /// </returns>
                static Vector4f sqrt(const Vector4f& vec) ;

                /// <summary>
                /// Square the values of a Vector4f.
                /// </summary>
                /// <param name="vec">
                /// Values for which to get squared values.
                /// </param>
                /// <returns>
                /// A Vector4f containing the squared values of vec.
                /// </returns>
                static Vector4f square(const Vector4f& vec) ;

                /// <summary>
                /// Get the dot product of a Vector4f.
                /// </summary>
                /// <param name="a">First Vector4f in dot product.</param>
                /// <param name="b">Second Vector4f in dot product.</param>
                /// <returns>The dot product of the given Vector4f.</returns>
                static Scalar dot(const Vector4f& a, const Vector4f& b) ;

                /// <summary>
                /// Get the cross product of a Vector4f.
                /// </summary>
                /// <param name="a">First Vector4f in cross product.</param>
                /// <param name="b"Second Vector4f in cross product.></param>
                /// <returns>The cross product of the given Vector4f.</returns>
                static Vector4f cross(const Vector4f& a, const Vector4f& b) ;

                /// <summary>
                /// Compute for each element of vec 1 / vec[i].
                /// The maximum relative error for this approximation is less
                /// than 1.5*2^-12.
                /// </summary>
                /// <param name="vec">
                /// The Vector4f for which compute the reciprocal.
                /// </param>
                /// <returns>The reciprocal of vec.</returns>
                static Vector4f fast_recriprocal(const Vector4f& vec) ;

                /// <summary>
                /// Compute for each element of vec 1 / sqrt(vec[i]).
                /// The maximum relative error for this approximation is less
                /// than 1.5*2^-12.
                /// </summary>
                /// <param name="vec">
                /// Vector4f for which compute the reverse squareroot.
                /// </param>
                /// <returns>
                /// Vector4f containing the reverse squareroot of each element
                /// in vec.
                /// </returns>
                static Vector4f fast_rsqrt(const Vector4f& vec) ;

                /// <summary>
                /// Compute for each element of vec sqrt(vec[i]).
                /// The maximum relative error for this approximation is less
                /// than 1.5*2^-12.
                /// </summary>
                /// <param name="vec">
                /// Vector4f for which compute the squareroot.
                /// </param>
                /// <returns>
                /// Vector4f containing the squareroot of each element in vec.
                /// </returns>
                static Vector4f fast_sqrt(const Vector4f& vec) ;


                /// <summary>
                /// Blend two vectors applying a mask.
                /// </summary>
                /// <param name="a">First vector.</param>
                /// <param name="b">Second vector.</param>
                /// <param name="mask">Mask for blending vectors.</param>
                /// <returns>Result of the blending.</returns>
                static Vector4f blend(
                    const Vector4f& a,
                    const Vector4f& b,
                    const Vector4f::Mask& mask
                ) ;

                /// <summary>
                /// Multiply two Vector4f then add a third one.
                /// </summary>
                /// <param name="mula">
                /// First operand of the multiplication.
                /// </param>
                /// <param name="mulb">
                /// Second operand of the multiplication.
                /// </param>
                /// <param name="add">
                /// The Vector4f to add to the product of mula by mulb.
                /// </param>
                /// <returns>The result of the operation.</returns>
                static Vector4f mul_add(
                    const Vector4f& mula,
                    const Vector4f& mulb,
                    const Vector4f& add
                ) ;

                /// <summary>
                /// Multiply two Vector4f then substract a third one.
                /// </summary>
                /// <param name="mula">
                /// First operand of the multiplication.
                /// </param>
                /// <param name="mulb">
                /// Second operand of the multiplication.
                /// </param>
                /// <param name="sub">
                /// The Vector4f to substract to the product of mula by mulb.
                /// </param>
                /// <returns>The result of the operation.</returns>
                static Vector4f mul_sub(
                    const Vector4f& mula,
                    const Vector4f& mulb,
                    const Vector4f& sub
                ) ;

                /// <summary>
                /// Substract a Vector to the product of others.
                /// </summary>
                /// <param name="sub">The Vector4f to be substracted.</param>
                /// <param name="mula">First operand of the multiplication.</param>
                /// <param name="mulb">Second operand of the multiplication.</param>
                /// <returns>The result of the operation.</returns>
                static Vector4f sub_mul(
                    const Vector4f& sub,
                    const Vector4f& mula,
                    const Vector4f& mulb
                ) ;

                /// <summary>
                /// Transpose a 4x4 matrix.
                /// </summary>
                /// <param name="row1">
                /// First row of the matrix in which first column is put as
                /// output.
                /// </param>
                /// <param name="row2">
                /// Second row of the matrix in which second column is put as
                /// output.
                /// </param>
                /// <param name="row3">
                /// Third row of the matrix in which third column is put as
                /// output.
                /// </param>
                /// <param name="row4">
                /// Fourth row of the matrix in which fourth column is put as
                /// output.
                /// </param>
                static void transposeMatrix(
                    Vector4f& row1,
                    Vector4f& row2,
                    Vector4f& row3,
                    Vector4f& row4
                ) ;

                /// <summary>
                /// Get a Mask in which elements are true for negative element
                /// in the current Vector4f, false for positive elements in the
                /// current Vector4f.
                /// Works also for -0.0, -INF and -NaN.
                /// </summary>
                /// <returns>
                /// A Mask containing true for negative elements in the current
                /// Vector4f.
                /// </returns>
                Mask isNegative() ;

                /// <summary>
                /// Get a Mask in which elements are true for infinite values
                /// in current Vector4f, false for finite values.
                /// </summary>
                /// <returns>
                /// A Mask containing true for infinite elements in the current
                /// Vector4f.
                /// </returns>
                Mask isInfinite() ;

                /// <summary>
                /// Get a Mask in which elements are true for NaN values in
                /// current Vector4f, false for determined values.
                /// NaN corresponds to a null exponent with a non-null fraction.
                /// </summary>
                /// <returns>
                /// A Mask containing true for NaN elements in the current
                /// Vector4f.
                /// </returns>
                Mask isNaN() ;

                /// <summary>
                /// Load from an array that is not aligned.
                /// </summary>
                /// <param name="array">
                /// The array to load into the Vector4f.
                /// </param>
                void set(const Array4f& array) ;

                /// <summary>
                /// Copy the values on the Vector4f into an unaligned array.
                /// </summary>
                /// <param name="array">
                /// Output parameter in which values of the Vector4f are
                /// stored.
                /// </param>
                void get(Array4f& array) const ;

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
                /// Print the content of the Vector on the console output.
                /// </summary>
                void print() ;

            protected:
                /// <summary>
                /// Read the MXCSR control word.
                /// </summary>
                /// <returns>The current MXCSR control word.</returns>
                static uint32_t getControlWord() ;

                /// <summary>
                /// Write the MXCSR control word.
                /// </summary>
                /// <param name="csr">The new MXCSR control word.</param>
                static void setControlWord(const uint32_t csr) ;

                /// <summary>
                /// Set "Denormals Are Zeros" and "Flush to Zero" mode to avoid
                /// the extremely time-consuming denormals in case of
                /// underflow.
                /// </summary>
                static void noSubnormals() ;

                /// <summary>
                /// Set the MXCSR control word to the default value 0x1F80.
                /// This will mask floating point exceptions, set rounding mode
                /// to nearest (or even), and allow denormals.
                /// </summary>
                static void resetControlWord() ;

            public:
                /// <summary>
                /// Affect the inner value of the Vector4f to the broadcasted
                /// one given as parameter.
                /// </summary>
                /// <param name="value">
                /// The value to put in the Vector4f, to all its values.
                /// </param>
                /// <returns>
                /// The current Vector4f once the value is affected to its
                /// inner data.
                /// </returns>
                Vector4f& operator=(const Scalar value) ;

                /// <summary>
                /// Affect the inner value to the Vector4f.
                /// </summary>
                /// <param name="vec">
                /// The value to put in the Vector4f.
                /// </param>
                /// <returns>
                /// The current Vector4f once the vec is affected to its inner
                /// data.
                /// </returns>
                Vector4f& operator=(const __m128 vec) ;

                /// <summary>
                /// Get the values from a Vector4i (integers) and put it in
                /// inner data.
                /// </summary>
                /// <param name="vec4">The vector to convert.</param>
                /// <returns>
                /// The current Vector4f once the vec is affected to its inner
                /// data.
                /// </returns>
                Vector4f& operator=(const Vector4i& vec4) ;

                /// <summary>
                /// Get the values from a Vector4ui (integers) and put it in
                /// inner data.
                /// </summary>
                /// <param name="vec4">The vector to convert.</param>
                /// <returns>
                /// The current Vector4f once the vec is affected to its
                /// inner data.
                /// </returns>
                Vector4f& operator=(const Vector4ui& vec4) ;

                /// <summary>
                /// Access a value of the Vector4f.
                /// </summary>
                /// <param name="index">Index in the Vector4f.</param>
                /// <returns>Value at the wanted index.</returns>
                float operator[](const int index) const ;

                /// <summary>
                /// Access a value of the Vector4f.
                /// </summary>
                /// <param name="index">Index in the Vector4f.</param>
                /// <returns>Value at the wanted index.</returns>
                float& operator[](const int index) ;

                /// <summary>
                /// Cast the current Vector4f to its inner data type.
                /// </summary>
                operator __m128() const ;

                /// <summary>
                /// Cast the current Vector4f to an array of float values.
                /// </summary>
                explicit operator Array4f() const ;

                /// <summary>
                /// Cast the current Vector4f to a Vector4i.
                /// </summary>
                explicit operator Vector4i() const ;

                /// <summary>
                /// Cast the current Vector4f to a Vector4ui.
                /// </summary>
                /// <remarks>
                /// Be careful with negative values.
                /// </remarks>
                explicit operator Vector4ui() const ;
        } ;


        #include "impl/Vector4f/Mask/operators.hpp"
        #include "impl/Vector4f/Mask/impl.hpp"

        #include "impl/Vector4f/operators.hpp"
        #include "impl/Vector4f/impl.hpp"

        template <int i0, int i1, int i2, int i3>
        void Vector4f::permute() {
            static_assert((i0 <= 3), "Bad value. Expected i0 <= 3") ;
            static_assert((i1 <= 3), "Bad value. Expected i1 <= 3") ;
            static_assert((i2 <= 3), "Bad value. Expected i2 <= 3") ;
            static_assert((i3 <= 3), "Bad value. Expected i3 <= 3") ;

            // Check if shuffling is required.
            const bool NeedShuffle = (i0 > 0)
                                        || ((i1 != 1) && (i1 >= 0))
                                        || ((i2 != 2) && (i2 >= 0))
                                        || ((i3 != 3) && (i3 >= 0)) ;

            // Check if zeroing required.
            const bool DoZero = (((i0 | i1 | i2 | i3) < 0) && ((i0 | i1 | i2 | i3) & 0x80)) ;

            if (DoZero && !NeedShuffle) {
                // Only make some / all positions zeroed in the vector.
                if ((i0 | i1 | i2 | i3) < 0) {
                    // Zero all values.
                    m_inner.vec = _mm_setzero_ps() ;
                }
                else {
                    const __m128i MaskZeroPositions = Vector4i::constant<
                        -int(i0 > -1),
                        -int(i1 > -1),
                        -int(i2 > -1),
                        -int(i3 > -1)
                    >() ;

                    m_inner.vec = _mm_and_ps(m_inner.vec,_mm_castsi128_ps(MaskZeroPositions)) ;
                }
            }
            else if (NeedShuffle && !DoZero) {
                // Only shuffle the values in the vector.
                m_inner.vec = _mm_shuffle_ps(
                    m_inner.vec,
                    m_inner.vec,
                    ((i0) | (i1 << 2) | (i2 << 4) | (i3 << 6))
                ) ;
            }
            else if (((i0 & i1) < 0) && ((i2 | i3) >= 0)) {
                // Zero on lower elements, shuffle higher ones.
                m_inner.vec = _mm_shuffle_ps(_mm_setzero_ps(), m_inner.vec, (i2 << 4) | (i3 <<6));
            }
            else if ((i0 | i1) >= 0 && (i2 & i3) < 0) {
                // Zero on higher elements, shuffle lower ones.
                m_inner.vec = _mm_shuffle_ps(m_inner.vec, _mm_setzero_ps(), (i0 | (i1 << 2))) ;
            }
            else {
                #if defined (USE_INTEL_SSSE3)
                    // With SSSE3 we can do both with the PSHUFB instruction
                    const int j0 = i0 << 2 ;
                    const int j1 = i1 << 2 ;
                    const int j2 = i2 << 2 ;
                    const int j3 = i3 << 2 ;
                    __m128i MaskZeroPositions = Vector4i::constant <
                        i0 < 0 ? -1 : j0 | (j0+1)<<8 | (j0+2)<<16 | (j0+3) << 24,
                        i1 < 0 ? -1 : j1 | (j1+1)<<8 | (j1+2)<<16 | (j1+3) << 24,
                        i2 < 0 ? -1 : j2 | (j2+1)<<8 | (j2+2)<<16 | (j2+3) << 24,
                        i3 < 0 ? -1 : j3 | (j3+1)<<8 | (j3+2)<<16 | (j3+3) << 24
                    > () ;
                    m_inner.vec = _mm_castsi128_ps(_mm_shuffle_epi8(_mm_castps_si128(m_inner.vec), MaskZeroPositions)) ;
                #else
                    __m128 tmp = _mm_shuffle_ps(m_inner.vec, m_inner.vec, ((i0) | (i1 << 2) | (i2 << 4) | (i3 << 6))) ;
                    __m128i MaskZeroPositions = Vector4i::constant<
                        -int(i0 > -1),
                        -int(i1 > -1),
                        -int(i2 > -1),
                        -int(i3 > -1)
                    >() ;
                    m_inner.vec = _mm_and_ps(tmp,_mm_castsi128_ps(MaskZeroPositions)) ;
                #endif
            }
        }

        template <bool i0, bool i1, bool i2, bool i3>
        void Vector4f::changeSign() {
            if ((i0 | i1 | i2 | i3) == true) {
                // Mask to set flip the bit for negative sign (on Scalar values).
                const __m128i MaskNegative = Vector4ui::constant<
                    i0 ? 0x80000000 : 0,
                    i1 ? 0x80000000 : 0,
                    i2 ? 0x80000000 : 0,
                    i3 ? 0x80000000 : 0
                >() ;

                m_inner.vec = _mm_xor_ps(m_inner.vec, _mm_castsi128_ps(MaskNegative)) ;
            }
        }

        template <unsigned char i0, unsigned char i1, unsigned char i2, unsigned char i3>
        Vector4f& Vector4f::shuffle(
            const Vector4f& input,
            Vector4f& output
       ) {
            static_assert((i0 <= 3), "Bad value. Expected i0 <= 3") ;
            static_assert((i1 <= 3), "Bad value. Expected i1 <= 3") ;
            static_assert((i2 <= 3), "Bad value. Expected i2 <= 3") ;
            static_assert((i3 <= 3), "Bad value. Expected i3 <= 3") ;

            output = _mm_shuffle_ps(
                (__m128) input,
                (__m128) input,
                ((i0) | (i1 << 2) | (i2 << 4) | (i3 << 6))
            ) ;

            return output ;
        }

    } ;

} ;

#endif
