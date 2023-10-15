#ifndef __MIND__SIMD_TYPES__
#define __MIND__SIMD_TYPES__

#include "harmful/mind/simd/SIMDArrays.hpp"

    #if defined(USE_INTEL_SSE2)
        #include <harmful/mind/simd/intel_sse2/SSETypes.hpp>
    #elif defined(USE_ARM_NEON)
        // Not yet available.
    #endif

#endif
