#ifndef __MIND__SIMD_SSE_TYPES__
#define __MIND__SIMD_SSE_TYPES__

union Float32x4 {
    __m128 vec ;
    Array4f arr ;

    Float32x4(): vec(_mm_set1_ps(0)) {}
    Float32x4(__m128 data): vec(data) {}
} ;

union Int32x4 {
    __m128i vec ;
    Array4i arr ;

    Int32x4(): vec(_mm_set1_epi32(0)) {}
    Int32x4(__m128i data): vec(data) {}
} ;

#endif
