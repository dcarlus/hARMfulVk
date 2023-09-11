                                              /** CONSTRUCTION / DESTRUCTION **/
inline Vector4ui::Vector4ui() : Vector4uint32() {}

inline Vector4ui::Vector4ui(
    const uint32_t& i1,
    const uint32_t& i2,
    const uint32_t& i3,
    const uint32_t& i4
) : Vector4uint32(i1, i2, i3, i4) {}

inline Vector4ui::Vector4ui(const uint32_t& value) : Vector4uint32(value) {}

inline Vector4ui::Vector4ui(const __m128i vec) : Vector4uint32(vec) {}

inline Vector4ui::Vector4ui(const __m128 vec) : Vector4uint32(vec) {}


                                                        /** STATIC FUNCTIONS **/
template <uint32_t i0, uint32_t i1, uint32_t i2, uint32_t i3>
inline __m128i Vector4ui::constant() {
    static const union {
        int integer[4] ;
        __m128i vector ;
    } u = {{i0, i1, i2, i3}} ;
    return u.vector ;
}

inline Vector4ui Vector4ui::min(const Vector4ui& a, const Vector4ui& b) {
    #if defined(USE_INTEL_SSE4_1)
        return _mm_min_epu32(a, b) ;
    #else
        __m128i greater = _mm_cmpgt_epi32(a, b) ;
        return Vector4::selection(greater, b, a) ;
    #endif
}

inline Vector4ui Vector4ui::max(const Vector4ui& a, const Vector4ui& b) {
    #if defined(USE_INTEL_SSE4_1)
        return _mm_max_epu32(a, b) ;
    #else
        __m128i greater = _mm_cmpgt_epi32(a, b) ;
        return Vector4::selection(greater, a, b) ;
    #endif
}

inline void Vector4ui::print() {
    int32_t* splitted = m_inner.arr ;
    std::cout << "Vector4ui @"
                            << std::hex << this << std::dec << "= { "
                                << splitted[0] << ", "
                                << splitted[1] << ", "
                                << splitted[2] << ", "
                                << splitted[3]
                            << " }"
                        << std::endl ;
}
