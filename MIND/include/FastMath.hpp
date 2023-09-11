#ifndef __MIND__FAST_MATH__
#define __MIND__FAST_MATH__

#include <utils/Platform.hpp>
#include "MINDTypes.hpp"
#include "Math.hpp"

namespace Mind {
    /**
     * Fast math are speed-up mathematic operations, by caching values or some
     * mystical yet really fast ways to get approximated results.
     */
    namespace FastMath {
        /**
         * Initialize the FastMath namespace.
         * @param    steps   FastMath can be initialized with a given amount of
         *                   steps to pre-compute some of the sinus, cosinus and
         *                   tangent values. It can then be adapted to the needs
         *                   of the application.
         *                   For convenient use, the default value is set to 360.
         *                   That way, you can use integer values as angle
         *                   expressed in degrees. For instance, you can call
         *                   later the function FastMath::sin(45) to get the
         *                   value of sin(45 degrees).
         */
        exported void init(const unsigned int steps = 360) ;


        /**
         * Get the value of sinus for the cached value of sin(PI/x).
         * @param   x   Value of x in the sin(PI/x) equation (angle in degrees).
         * @return  The value of sin(PI/x).
         */
        exported float sin(const unsigned int x) ;

        /**
         * Get the value of cosinus for the cached value of cos(PI/x).
         * @param   x   Value of x in the cos(PI/x) equation (angle in degrees).
         * @return  The value of cos(PI/x).
         */
        exported float cos(const unsigned int x) ;

        /**
         * Get the value of cosinus for the cached value of tan(PI/x).
         * @param   x   Value of x in the tan(PI/x) equation (angle in degrees).
         * @return  The value of tan(PI/x).
         */
        exported float tan(const unsigned int x) ;



        /**
         * Get a rounded value of the given one.
         * @param   value   Value to round.
         * @return  If value is smaller than x.5, x is returned. Otherwise, x+1 is
         *          returned.
         */
        exported int round(const Scalar value) ;

        /**
         * Round a value upward.
         * @param   value   Value to round ceil.
         * @return  The smallest integer value that is not less than the given
         *          value.
         */
        exported int ceil(const Scalar value) ;

        /**
         * Round a value downward.
         * @param   value   Value to round floor.
         * @return  The smallest integer value that is not greater than the given
         *          value.
         */
        exported int floor(const Scalar value) ;

        /**
         * Compute value^exponent, with positive exponent only.
         * @param   value       The value to power.
         * @param   exponent    Exponent to compute the power of value. It can only
         *                      be integer positive value (if possible, lower than
         *                      15).
         * @return  The value of value^exponent.
         * @warning As the function uses integer values to optimize computational
         *          time, no result is insured for exponents greater or equal to 15.
         */
        exported long pow(const int value, const unsigned char exponent) ;

        /**
         * Compute the square root of the given value.
         * @param   value   Value for which the square root is wanted.
         * @return  Square root of the given value.
         */
        exported Scalar sqrt(const Scalar value) ;
    } ;
} ;

#endif
