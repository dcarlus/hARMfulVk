#ifndef __MIND__SIMDVECTOR_SELECTOR__
#define __MIND__SIMDVECTOR_SELECTOR__

#include "MINDOptions.hpp"
#include "simd/SIMDTypes.hpp"

    #if defined(USE_INTEL_SSE2)
        #define PARALLELIZATION_ENABLED
        #include <simd/intel_sse2/integers/SIMDVector4.hpp>
        #include <simd/intel_sse2/integers/SIMDVector4i.hpp>
        #include <simd/intel_sse2/integers/SIMDVector4ui.hpp>
        #include <simd/intel_sse2/floats/SIMDVector4f.hpp>
        #include <simd/intel_sse2/floats/FloatUtils.hpp>
    #elif defined(USE_ARM_NEON)
        #define PARALLELIZATION_ENABLED
        #include <simd/arm_neon/integers/SIMDVector4.hpp>
        #include <simd/arm_neon/integers/SIMDVector4i.hpp>
        #include <simd/arm_neon/integers/SIMDVector4ui.hpp>
        #include <simd/arm_neon/floats/SIMDVector4f.hpp>
        #include <simd/arm_neon/floats/FloatUtils.hpp>
    #endif

#endif
