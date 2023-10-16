/// <summary>
/// Bitwise AND operator on two Masks.
/// </summary>
/// <typeparam name="Type">Integer value type.</typeparam>
/// <param name="a">First operand.</param>
/// <param name="b">Second operand.</param>
/// <returns>
/// A Mask in which values are true if they are true if both parameters.
/// They are false if at least one operand has false at that position.
/// </returns>
template <typename Type>
static inline typename Vector4<Type>::Mask operator&(
    const typename Vector4<Type>::Mask& a,
    const typename Vector4<Type>::Mask& b
) {
    return _mm_and_si128(a, b) ;
}

/// <summary>
/// Bitwise AND operator on two Masks. The result is affected to the first
/// operand.
/// </summary>
/// <typeparam name="Type">Integer value type.</typeparam>
/// <param name="a">First operand.</param>
/// <param name="b">Second operand.</param>
/// <returns>
/// A Mask in which values are true if they are true if both parameters.
/// They are false if at least one operand has false at that position.
/// </returns>
template <typename Type>
static inline typename Vector4<Type>::Mask& operator&=(
    const typename Vector4<Type>::Mask& a,
    const typename Vector4<Type>::Mask& b
) {
    a = a & b ;
    return a ;
}

/// <summary>
/// Bitwise OR operator on two Masks.
/// </summary>
/// <typeparam name="Type">Integer value type.</typeparam>
/// <param name="a">First operand.</param>
/// <param name="b">Second operand.</param>
/// <returns>
/// A Mask in which values are false if they are false if both parameters. They
/// are true if at least one operand has true at that position.
/// </returns>
template <typename Type>
static inline typename Vector4<Type>::Mask operator|(
    const typename Vector4<Type>::Mask& a,
    const typename Vector4<Type>::Mask& b
) {
    return _mm_or_si128(a, b) ;
}

/// <summary>
/// Bitwise OR operator on two Masks. The result is affected to the first
/// operand.
/// </summary>
/// <typeparam name="Type">Integer value type.</typeparam>
/// <param name="a">First operand.</param>
/// <param name="b">Second operand.</param>
/// <returns>
/// A Mask in which values are false if they are false if both parameters. They
/// are true if at least one operand has true at that position.
/// </returns>
template <typename Type>
static inline typename Vector4<Type>::Mask& operator|=(
    const typename Vector4<Type>::Mask& a,
    const typename Vector4<Type>::Mask& b
) {
    a = a | b ;
    return a ;
}

/// <summary>
/// Bitwise XOR operator on two Masks.
/// </summary>
/// <typeparam name="Type">Integer value type.</typeparam>
/// <param name="a">First operand.</param>
/// <param name="b">Second operand.</param>
/// <returns>
/// A Mask in which values are true only when the two operands have different
/// values at a same given position.
/// </returns>
template <typename Type>
static inline typename Vector4<Type>::Mask operator^(
    const typename Vector4<Type>::Mask& a,
    const typename Vector4<Type>::Mask& b
) {
    return _mm_xor_si128(a, b) ;
}

/// <summary>
/// Bitwise XOR operator on two Masks. The result is affected to the first
/// operand.
/// </summary>
/// <typeparam name="Type">Integer value type.</typeparam>
/// <param name="a">First operand.</param>
/// <param name="b">Second operand.</param>
/// <returns>
/// A Mask in which values are true only when the two operands have different
/// values at a same given position.
/// </returns>
template <typename Type>
static inline typename Vector4<Type>::Mask& operator^=(
    const typename Vector4<Type>::Mask& a,
    const typename Vector4<Type>::Mask& b
) {
    a = a ^ b ;
    return a ;
}

/// <summary>
/// Reverse each boolean value.
/// </summary>
/// <typeparam name="Type">Integer value type.</typeparam>
/// <param name="a">The Mask for which bits must be reversed.</param>
/// <returns>
/// The result Mask, for which bit are reversed compared to input.
/// </returns>
template <typename Type>
static inline typename Vector4<Type>::Mask operator~(const typename Vector4<Type>::Mask& a) {
    return _mm_xor_si128(a, _mm_set1_epi32(-1)) ;
}
