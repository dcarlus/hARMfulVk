#ifndef __MIND__FAST_MATH__
#define __MIND__FAST_MATH__

#include <harmful/doom/utils/Platform.hpp>
#include "harmful/mind/MINDTypes.hpp"
#include "harmful/mind/Math.hpp"

namespace Mind {
    /// <summary>
    /// Fast math are speed-up mathematic operations, by caching values or some
    /// mystical yet really fast ways to get approximated results.
    /// </summary>
    namespace FastMath {
        /// <summary>
        /// Initialize the FastMath namespace.
        /// </summary>
        /// <param name="steps">
        /// FastMath can be initialized with a given amount of steps to
        /// pre-compute some of the sinus, cosinus and tangent values. It can
        /// then be adapted to the needs of the application.
        /// For convenient use, the default value is set to 360. That way, you
        /// can use integer values as angle expressed in degrees. For instance,
        /// you can call later the function FastMath::sin(45) to get the value
        /// of sin(45 degrees).
        /// </param>
        exported void init(const unsigned int steps = 360) ;

        /// <summary>
        /// Get the value of sinus for the cached value of sin(PI/x).
        /// </summary>
        /// <param name="x">
        /// Value of x in the sin(PI/x) equation (angle in degrees).
        /// </param>
        /// <returns>The value of sin(PI/x).</returns>
        exported float sin(const unsigned int x) ;

        /// <summary>
        /// Get the value of cosinus for the cached value of cos(PI/x).
        /// </summary>
        /// <param name="x">
        /// Value of x in the cos(PI/x) equation (angle in degrees).
        /// </param>
        /// <returns>The value of cos(PI/x).</returns>
        exported float cos(const unsigned int x) ;

        /// <summary>
        /// Get the value of cosinus for the cached value of tan(PI/x).
        /// </summary>
        /// <param name="x">
        /// Value of x in the tan(PI/x) equation (angle in degrees).
        /// </param>
        /// <returns>The value of tan(PI/x).</returns>
        exported float tan(const unsigned int x) ;

        /// <summary>
        /// Get a rounded value of the given one.
        /// </summary>
        /// <param name="value">Value to round.</param>
        /// <returns>
        /// If value is smaller than x.5, x is returned. Otherwise, x+1 is
        /// returned.
        /// </returns>
        exported int round(const Scalar value) ;

        /// <summary>
        /// Round a value upward.
        /// </summary>
        /// <param name="value">Value to round ceil.</param>
        /// <returns>
        /// The smallest integer value that is not less than the given value.
        /// </returns>
        exported int ceil(const Scalar value) ;

        /// <summary>
        /// Round a value downward.
        /// </summary>
        /// <param name="value">Value to round floor.</param>
        /// <returns>
        /// The smallest integer value that is not greater than the given
        /// value.
        /// </returns>
        exported int floor(const Scalar value) ;

        /// <summary>
        /// Compute value^exponent, with positive exponent only.
        /// </summary>
        /// <param name="value">The value to power.</param>
        /// <param name="exponent">
        /// Exponent to compute the power of value. It can only be integer
        /// positive value (if possible, lower than 15).
        /// </param>
        /// <returns>The value of value^exponent.</returns>
        /// <remarks>
        /// As the function uses integer values to optimize computational time,
        /// no result is insured for exponents greater or equal to 15.
        /// </remarks>
        exported long pow(const int value, const unsigned char exponent) ;

        /// <summary>
        /// Compute the square root of the given value.
        /// </summary>
        /// <param name="value">
        /// Value for which the square root is wanted.
        /// </param>
        /// <returns>Square root of the given value.</returns>
        exported Scalar sqrt(const Scalar value) ;
    } ;
} ;

#endif
