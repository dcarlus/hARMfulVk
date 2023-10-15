#ifndef __MIND__OPTIONS__
#define __MIND__OPTIONS__

#include <harmful/doom/utils/Platform.hpp>

// List of macros used by MINDful :
// ================================
// Optimizations:
// --------------
// USE_APPROXIMATION                - Use some fast operations instead of slow
//                                    and precises ones

// FPU EXTENSIONS :
// ----------------
// USE_INTEL_SSE2                   - Use SSE and SSE2 on Intel/ARM processors
// USE_INTEL_SSE3                   - Use SSE3 on Intel/ARM processors
// USE_INTEL_SSSE3                  - Use SSSE3 on Intel/ARM processors
// USE_INTEL_SSE4_1                 - Use SSE4.1 on Intel/ARM processors
// USE_INTEL_SSE4_2                 - Use SSE4.2 on Intel/ARM processors
// USE_ARM_NEON                     - Use NEON on ARM processors
// USE_NO_SIMD                      - No use of SIMD on unable processors


    #define USE_APPROXIMATION

    // INTEL - AMD
    // __SSE2__ on Linux ; _M_X64 on Windows (Visual Studio) for x64.
    #if (defined __SSE2__ || defined _M_X64) && !defined(FORCE_EMULATED_SIMD)
        #define USE_SIMD
        // At least SSE2 is required to run algorithms on Intel/AMD SIMD
        #define USE_INTEL_SSE2
        #define SIMD    SSE2    // Generic namespace to use SIMD extensions
        #include <mmintrin.h>   // MMX  instructions set
        #include <xmmintrin.h>  // SSE  instructions set
        #include <emmintrin.h>  // SSE2 instructions set
        #define ALIGNMENT_ON_STACK  16

		#ifdef LinuxPlatform
			// Extra SSE instructions for modern processors
			#if defined (__SSE3__)
				#define USE_INTEL_SSE3
				#include <pmmintrin.h>  // SSE3 instructions set
			#endif
			#if defined ( __SSSE3__ )
				#define USE_INTEL_SSSE3
				#include <tmmintrin.h>  // SSSE3 instructions set
			#endif
			#if defined (__SSE4_1__)
				#define USE_INTEL_SSE4_1
				#include <smmintrin.h>  // SSE4.1 instructions set
			#endif
			#if defined (__SSE4_2__)
				#define USE_INTEL_SSE4_2
				#include <nmmintrin.h>  // SSE4.2 instructions set
			#endif

			#if defined (__FMA__)
				#define USE_FMA
				#include <immintrin.h>  // FMA instructions set
			#endif
			#if defined (__FMA4__)
				#define USE_FMA4        // FMA4 instructions set
				#include <fma4intrin.h>
			#endif
		#endif

		#ifdef WindowsPlatform
			// Extra SSE instructions for modern processors
			#define USE_INTEL_SSE3
			#include <pmmintrin.h>  // SSE3 instructions set

			#define USE_INTEL_SSSE3
			#include <tmmintrin.h>  // SSSE3 instructions set

			#define USE_INTEL_SSE4_1
			#include <smmintrin.h>  // SSE4.1 instructions set

			#define USE_INTEL_SSE4_2
			#include <nmmintrin.h>  // SSE4.2 instructions set
		#endif

    // ARM
    #elif defined (__ARM_NEON__) && !defined(FORCE_EMULATED_SIMD)
        #define USE_SIMD
        #define USE_ARM_NEON
        #define SIMD    NEON    // Generic namespace to use SIMD extensions
        #include <arm_neon.h>   // NEON instructions set
        #define ALIGNMENT_ON_STACK  (1 << __ARM_ALIGN_MAX_PWR)
    // Other CPUs
    #else
        #error "Only SIMD CPUs are supported"
    #endif

    #define __STDC_FORMAT_MACROS
    #include <cstdint>

#endif
