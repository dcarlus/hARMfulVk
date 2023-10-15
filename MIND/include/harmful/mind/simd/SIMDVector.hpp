#ifndef __MIND__SIMDVECTOR_SELECTOR__
#define __MIND__SIMDVECTOR_SELECTOR__

#include "harmful/mind/MINDOptions.hpp"
#include "harmful/mind/simd/SIMDTypes.hpp"

    #if defined(USE_INTEL_SSE2)
        #define PARALLELIZATION_ENABLED
        #include <harmful/mind/simd/intel_sse2/integers/SIMDVector4.hpp>
        #include <harmful/mind/simd/intel_sse2/integers/SIMDVector4i.hpp>
        #include <harmful/mind/simd/intel_sse2/integers/SIMDVector4ui.hpp>
        #include <harmful/mind/simd/intel_sse2/floats/SIMDVector4f.hpp>
        #include <harmful/mind/simd/intel_sse2/floats/FloatUtils.hpp>
    #elif defined(USE_ARM_NEON)
        #define PARALLELIZATION_ENABLED
        #include <harmful/mind/simd/arm_neon/integers/SIMDVector4.hpp>
        #include <harmful/mind/simd/arm_neon/integers/SIMDVector4i.hpp>
        #include <harmful/mind/simd/arm_neon/integers/SIMDVector4ui.hpp>
        #include <harmful/mind/simd/arm_neon/floats/SIMDVector4f.hpp>
        #include <harmful/mind/simd/arm_neon/floats/FloatUtils.hpp>
    #endif

#endif
