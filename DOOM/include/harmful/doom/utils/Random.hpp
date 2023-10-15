#ifndef __DOOM__RANDOM__
#define __DOOM__RANDOM__

#include "harmful/doom/utils/Platform.hpp"

namespace Doom {
    /// <summary>
    /// Simple random generation. This one does not use C++11 and next
    /// capabilities to keep things as simple as possible.
    /// </summary>
    namespace Random {
        /// <summary>
        /// Initialize the generation of random numbers.
        /// </summary>
        /// <param name="force">If true, forces the (re)initialization.</param>
        exported void Initialize(const bool force = false) ;

        /// <summary>
        /// Get an integer value from the pseudo-random value generator.
        /// </summary>
        /// <returns>The generated value.</returns>
        exported int GetInteger() ;

        /// <summary>
        /// Get an integer value into an interval from the pseudo-random value
        /// generator.
        /// </summary>
        /// <param name="min">Minimal value of the interval.</param>
        /// <param name="max">Maximal value of the interval.</param>
        /// <returns>
        /// The generated value. If min >= max, 0 is returned.
        /// </returns>
        exported int GetInteger(const int min, const int max) ;

        /// <summary>
        /// Get a float value normalized from the pseudo-random value generator.
        /// </summary>
        /// <returns>The generated value, the value is between 0 and 1.</returns>
        exported float GetNormalizedFloat() ;
    }
}


#endif
