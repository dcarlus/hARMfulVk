template <typename Type>
inline __m128i Vector4<Type>::selection(
                                    const __m128i selector,
                                    const __m128i a,
                                    const __m128i b
                                   ) {
    #if defined(USE_INTEL_SSE4_1)
        return _mm_blendv_epi8 (b, a, selector) ;
    #else
        return _mm_or_si128(
                            _mm_and_si128(selector, a),
                            _mm_andnot_si128(selector, b)
                           ) ;
    #endif
}

                                              /** CONSTRUCTION / DESTRUCTION **/
template <typename Type>
inline Vector4<Type>::Vector4() {}

template <typename Type>
inline Vector4<Type>::Vector4(const Type& i1, const Type& i2, const Type& i3, const Type& i4) {
    m_inner = Int32x4(_mm_setr_epi32(i1, i2, i3, i4)) ;
}

template <typename Type>
inline Vector4<Type>::Vector4(const Type& value) {
    m_inner = Int32x4(_mm_set1_epi32(value)) ;
}

template <typename Type>
inline Vector4<Type>::Vector4(const __m128i vec) {
    m_inner = Int32x4(vec) ;
}

template <typename Type>
inline Vector4<Type>::Vector4(const __m128 vec) {
    m_inner = Int32x4(_mm_castps_si128(vec)) ;
}


                                                              /*** UTILITIES ***/
template <typename Type>
inline Type Vector4<Type>::horizontalAdd() {
    // The goal of this function is to put the sum of vector elements in the
    // lower element (ie. first position) of the result, and finally return the
    // contained value in this lower element.
    #if defined (USE_INTEL_SSSE3)
        // Compute sum of all elements in vector.
        // Notice that _mm_hadd_ps() function only sum adjacent positions
        // (indices 0+1 ; 2+3). It is so necessary to sum twice the vector to
        // sum the four positions.
        __m128i sum1 = _mm_hadd_epi32(m_inner.vec, m_inner.vec) ;
        // Sum twice.
        __m128i sum2 = _mm_hadd_epi32(sum1, sum1) ;
        // Get the lower element from the inner vector, containing the sum of
        // all elements.
        return _mm_cvtsi128_si32(sum2) ;
    #else
        // Shuffle highest elements.
        __m128i tmp1 = _mm_shuffle_epi32(m_inner.vec, 0x0E) ;
        // Then, sum inner to tmp1.
        __m128i tmp2 = _mm_add_epi32(m_inner.vec, tmp1) ;
        __m128i tmp3 = _mm_shuffle_epi32(tmp2, 0x01) ;
        __m128i tmp4 = _mm_add_epi32(tmp2, tmp3) ;
        return _mm_cvtsi128_si32(tmp4) ;
    #endif
}


template <typename Type>
inline size_t Vector4<Type>::length() const {
    return size() ;
}

template <typename Type>
inline size_t Vector4<Type>::size() {
    return 4 ;
}


template <typename Type>
inline Vector4<Type>::operator __m128i() const {
    return m_inner.vec ;
}
