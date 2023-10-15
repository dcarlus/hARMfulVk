#ifndef __MIND__SIMD_INTELSSE_FLOAT_UTILS__
#define __MIND__SIMD_INTELSSE_FLOAT_UTILS__

// vec(0, 1, 2, 3) -> (vec[x], vec[y], vec[z], vec[w])
#define VecSwizzle(vec, x,y,z,w)           _mm_shuffle_ps(vec, vec, _MM_SHUFFLE(x,y,z,w))
#define VecSwizzle1(vec, x)                _mm_shuffle_ps(vec, vec, _MM_SHUFFLE(x,x,x,x))
// special swizzle
#define VecSwizzle_0101(vec)               _mm_movelh_ps(vec, vec)
#define VecSwizzle_2323(vec)               _mm_movehl_ps(vec, vec)
#define VecSwizzle_0022(vec)               _mm_moveldup_ps(vec)
#define VecSwizzle_1133(vec)               _mm_movehdup_ps(vec)

// return (vec1[x], vec1[y], vec2[z], vec2[w])
#define VecShuffle(vec1, vec2, x,y,z,w)    _mm_shuffle_ps(vec1, vec2, _MM_SHUFFLE(x,y,z,w))
#define VecShuffle1(vec1, vec2, x)         _mm_shuffle_ps(vec1, vec2, _MM_SHUFFLE(x,x,x,x))
// special shuffle
#define VecShuffle_0101(vec1, vec2)        _mm_movelh_ps(vec1, vec2)
#define VecShuffle_2323(vec1, vec2)        _mm_movehl_ps(vec2, vec1)

#endif
