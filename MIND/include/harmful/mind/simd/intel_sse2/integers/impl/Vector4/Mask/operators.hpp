                                                                     /** AND **/
/**
 * Bitwise AND operator on two Masks.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  A Mask in which values are TRUE if they are TRUE if both parameters.
 *          They are FALSE if at least one operand has FALSE at that position.
 */
template <typename Type>
static inline typename Vector4<Type>::Mask operator&(
    const typename Vector4<Type>::Mask& a,
    const typename Vector4<Type>::Mask& b
) {
    return _mm_and_si128(a, b) ;
}

/**
 * Bitwise AND operator on two Masks. The result is affected to the first
 * operand.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  A Mask in which values are TRUE if they are TRUE if both parameters.
 *          They are FALSE if at least one operand has FALSE at that position.
 */
template <typename Type>
static inline typename Vector4<Type>::Mask& operator&=(
    const typename Vector4<Type>::Mask& a,
    const typename Vector4<Type>::Mask& b
) {
    a = a & b ;
    return a ;
}


                                                                      /** OR **/
/**
 * Bitwise OR operator on two Masks.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  A Mask in which values are FALSE if they are FALSE if both
 *          parameters. They are TRUE if at least one operand has TRUE at that
 *          position.
 */
template <typename Type>
static inline typename Vector4<Type>::Mask operator|(
    const typename Vector4<Type>::Mask& a,
    const typename Vector4<Type>::Mask& b
) {
    return _mm_or_si128(a, b) ;
}

/**
 * Bitwise OR operator on two Masks. The result is affected to the first
 * operand.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  A Mask in which values are FALSE if they are FALSE if both
 *          parameters. They are TRUE if at least one operand has TRUE at that
 *          position.
 */
template <typename Type>
static inline typename Vector4<Type>::Mask& operator|=(
    const typename Vector4<Type>::Mask& a,
    const typename Vector4<Type>::Mask& b
) {
    a = a | b ;
    return a ;
}


                                                                     /** XOR **/
/**
 * Bitwise XOR operator on two Masks.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  A Mask in which values are TRUE only when the two operands have
 *          different values at a same given position.
 */
template <typename Type>
static inline typename Vector4<Type>::Mask operator^(
    const typename Vector4<Type>::Mask& a,
    const typename Vector4<Type>::Mask& b
) {
    return _mm_xor_si128(a, b) ;
}

/**
 * Bitwise XOR operator on two Masks. The result is affected to the first
 * operand.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  A Mask in which values are TRUE only when the two operands have
 *          different values at a same given position.
 */
template <typename Type>
static inline typename Vector4<Type>::Mask& operator^=(
    const typename Vector4<Type>::Mask& a,
    const typename Vector4<Type>::Mask& b
) {
    a = a ^ b ;
    return a ;
}


                                                                     /** NOT **/
/**
 * Reverse each boolean value.
 * @param   a   The Mask for which bits must be reversed.
 * @return  The result Mask, for which bit are reversed compared to input.
 */
template <typename Type>
static inline typename Vector4<Type>::Mask operator~(const typename Vector4<Type>::Mask& a) {
    return _mm_xor_si128(a, _mm_set1_epi32(-1)) ;
}
