#ifndef __MIND__SIMD_ARRAYS__
#define __MIND__SIMD_ARRAYS__

#include <array>
#include <cstdint>
#include <utils/Platform.hpp>
#include "MINDOptions.hpp"

    /** Arrays **/
    #ifdef ALIGNED_ARRAY
        #ifdef WindowsPlatform
            // Visual Studio does not like "alignas" in the "using" statement.
            using Array4i = std::array<int32_t, 4> ;
            using Array4f = std::array<float, 4> ;
        #else
            using Array4i alignas(ALIGNMENT_ON_STACK) = std::array<int32_t, 4> ;
            using Array4f alignas(ALIGNMENT_ON_STACK) = std::array<float, 4> ;
        #endif
    #else
        // Unaligned data may lower performances on old Intel CPUs (Pentium 4,
        // Pentium M, Atom).
        using Array4i = std::array<int32_t, 4> ;
        using Array4f = std::array<float, 4> ;
    #endif

#endif
