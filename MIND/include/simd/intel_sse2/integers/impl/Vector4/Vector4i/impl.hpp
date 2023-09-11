                                              /** CONSTRUCTION / DESTRUCTION **/
inline Vector4i::Vector4i() : Vector4int32() {}

inline Vector4i::Vector4i(
    const int32_t& i1,
    const int32_t& i2,
    const int32_t& i3,
    const int32_t& i4
) : Vector4int32(i1, i2, i3, i4) {}

inline Vector4i::Vector4i(const int32_t& value) : Vector4int32(value) {}

inline Vector4i::Vector4i(const __m128i vec) : Vector4int32(vec) {}

inline Vector4i::Vector4i(const __m128 vec) : Vector4int32(vec) {}


                                                        /** STATIC FUNCTIONS **/
template <int32_t i0, int32_t i1, int32_t i2, int32_t i3>
inline __m128i Vector4i::constant() {
    static const union {
        int integer[4] ;
        __m128i vector ;
    } u = {{i0, i1, i2, i3}} ;
    return u.vector ;
}

inline Vector4i Vector4i::min(const Vector4i& a, const Vector4i& b) {
    #if defined(USE_INTEL_SSE4_1)
        return _mm_min_epi32((__m128i) a, (__m128i) b) ;
    #else
        __m128i greater = _mm_cmpgt_epi32((__m128i) a, (__m128i) b) ;
        return Vector4::selection(greater, (__m128i) b, (__m128i) a) ;
    #endif
}

inline Vector4i Vector4i::max(const Vector4i& a, const Vector4i& b) {
    #if defined(USE_INTEL_SSE4_1)
        return _mm_max_epi32((__m128i) a, (__m128i) b) ;
    #else
        __m128i greater = _mm_cmpgt_epi32((__m128i) a, (__m128i) b) ;
        return Vector4::selection(greater, (__m128i) a, (__m128i) b) ;
    #endif
}

inline Vector4i Vector4i::abs(const Vector4i& vec) {
    #if defined(USE_INTEL_SSSE3)
        return _mm_sign_epi32(vec, vec) ;
    #else
        // Get the sign of vector values.
        __m128i sign = _mm_srai_epi32((__m128i) vec, 31) ;
        // Invert bits for negative values.
        __m128i inv  = _mm_xor_si128((__m128i) vec, (__m128i) sign) ;
        // Add one to the inverted values (through shifted sign) to retrieve
        // absolute values of vec.
        return _mm_sub_epi32(inv, sign) ;
    #endif
}

inline void Vector4i::print() {
    Array4i& splitted = m_inner.arr ;
    std::cout << "Vector4i @"
                            << std::hex << this << std::dec << "= { "
                                << splitted[0] << ", "
                                << splitted[1] << ", "
                                << splitted[2] << ", "
                                << splitted[3]
                            << " }"
                        << std::endl ;
}
