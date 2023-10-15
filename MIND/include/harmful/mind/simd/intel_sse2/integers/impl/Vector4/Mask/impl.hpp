                                                /** CONSTRUCTION / DESTRUCTION **/
template <typename Type>
Vector4<Type>::Mask::Mask() {}

template <typename Type>
Vector4<Type>::Mask::Mask(
    const bool& b0,
    const bool& b1,
    const bool& b2,
    const bool& b3
) {
     m_inner.vec = _mm_setr_epi32(b0, b1, b2, b3) ;
}

template <typename Type>
Vector4<Type>::Mask::Mask(const bool& value) {
    m_inner.vec = _mm_set1_epi32(value) ;
}

template <typename Type>
Vector4<Type>::Mask::Mask(const __m128i vec) {
    m_inner.vec = vec ;
}


                                                              /*** UTILITIES ***/
#ifdef ALIGNED_ARRAY
    template <typename Type>
    inline void Vector4<Type>::Mask::get(Array4i& array) {
        int32_t* data = array.data() ;
        _mm_store_si128((__m128i*) data, m_inner.vec) ;
    }
#else
    template <typename Type>
    inline void Vector4<Type>::Mask::get(Array4i& array) {
        int32_t* data = array.data() ;
        _mm_storeu_si128((__m128i*) data, m_inner.vec) ;
    }
#endif

template <typename Type>
inline bool Vector4<Type>::Mask::get(const unsigned int& index) {
    Array4i tmp ;
    get(tmp) ;
    return tmp[index] ;
}

template <typename Type>
inline size_t Vector4<Type>::Mask::length() const {
    return size() ;
}

template <typename Type>
inline size_t Vector4<Type>::Mask::size() {
    return 4 ;
}


                                                              /*** OPERATORS ***/
                                                        /** AFFECT OPERATORS **/
template <typename Type>
inline typename Vector4<Type>::Mask& Vector4<Type>::Mask::operator=(const bool& value) {
    m_inner.vec = _mm_set1_epi32(-int32_t(value)) ;
    return *this ;
}

template <typename Type>
inline typename Vector4<Type>::Mask& Vector4<Type>::Mask::operator=(const __m128i vec) {
    m_inner.vec = vec ;
    return *this ;
}

template <typename Type>
inline typename Vector4<Type>::Mask& Vector4<Type>::Mask::operator=(const __m128 vec) {
    m_inner.vec = _mm_castps_si128(vec) ;
    return *this ;
}

                                                            /** CAST OPERATORS **/
template <typename Type>
inline Vector4<Type>::Mask::operator __m128i() const {
    return m_inner.vec ;
}

template <typename Type>
inline Vector4<Type>::Mask::operator __m128() const {
    return _mm_castsi128_ps(m_inner.vec) ;
}
