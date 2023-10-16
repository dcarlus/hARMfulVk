                                                                     /** AND **/
/// <summary>
/// Bitwise AND operator on two Masks.
/// </summary>
/// <param name="a">First operand.</param>
/// <param name="b">Second operand.</param>
/// <returns>
/// A Mask in which values are true if they are true if both parameters.
/// They are false if at least one operand has false at that position.
/// </returns>
static inline Vector4f::Mask operator&(
    const Vector4f::Mask& a,
    const Vector4f::Mask& b
) {
    return _mm_and_ps((__m128) a, (__m128) b) ;
}

/// <summary>
/// Bitwise AND operator on two Masks. The result is affected to the first
/// operand.
/// </summary>
/// <param name="a">First operand.</param>
/// <param name="b">Second operand.</param>
/// <returns>
/// A Mask in which values are true if they are true if both parameters.
/// They are false if at least one operand has false at that position.
/// </returns>
static inline Vector4f::Mask& operator&=(
    Vector4f::Mask& a,
    const Vector4f::Mask& b
) {
    a = a & b ;
    return a ;
}


                                                                      /** OR **/
/// <summary>
/// Bitwise OR operator on two Masks.
/// </summary>
/// <param name="a">First operand.</param>
/// <param name="b">Second operand.</param>
/// <returns>
/// A Mask in which values are false if they are false if both parameters.
/// They are true if at least one operand has true at that position.
/// </returns>
static inline Vector4f::Mask operator|(
    const Vector4f::Mask& a,
    const Vector4f::Mask& b
) {
    return _mm_or_ps((__m128) a, (__m128) b) ;
}

/// <summary>
/// Bitwise OR operator on two Masks. The result is affected to the first
/// operand.
/// </summary>
/// <param name="a">First operand.</param>
/// <param name="b">Second operand.</param>
/// <returns>
/// A Mask in which values are false if they are false if both parameters. They
/// are true if at least one operand has true at that position.
/// </returns>
static inline Vector4f::Mask& operator|=(
    Vector4f::Mask& a,
    const Vector4f::Mask& b
) {
    a = a | b ;
    return a ;
}


                                                                     /** XOR **/
/// <summary>
/// Bitwise XOR operator on two Masks.
/// </summary>
/// <param name="a">First operand.</param>
/// <param name="b">Second operand.</param>
/// <returns>
/// A Mask in which values are true only when the two operands have different
/// values at a same given position.
/// </returns>
static inline Vector4f::Mask operator^(
    const Vector4f::Mask& a,
    const Vector4f::Mask& b
) {
    return _mm_xor_ps((__m128) a, (__m128) b) ;
}

/// <summary>
/// Bitwise XOR operator on two Masks. The result is affected to the first
/// operand.
/// </summary>
/// <param name="a">First operand.</param>
/// <param name="b">Second operand.</param>
/// <returns>
/// A Mask in which values are true only when the two operands have different
/// values at a same given position.
/// </returns>
static inline Vector4f::Mask& operator^=(
    Vector4f::Mask& a,
    const Vector4f::Mask& b
) {
    a = a ^ b ;
    return a ;
}


                                                                     /** NOT **/
/// <summary>
/// Reverse each boolean value.
/// </summary>
/// <param name="a">The Mask for which bits must be reversed.</param>
/// <returns>
/// The result Mask, for which bit are reversed compared to input.
/// </returns>
static inline Vector4f::Mask operator~(const Vector4f::Mask& a) {
    return _mm_xor_ps((__m128) a, _mm_castsi128_ps(_mm_set1_epi32(-1))) ;
}
