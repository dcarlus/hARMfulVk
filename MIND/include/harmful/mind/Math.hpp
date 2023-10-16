#ifndef __MIND__MATH__
#define __MIND__MATH__

#include <utility>
#include <vector>
#include <cstdint>
#include <cmath>
#include <harmful/doom/utils/Platform.hpp>
#include "harmful/mind/MINDTypes.hpp"

namespace Mind {
    /// <summary>
    /// Additional math operations for convenient use.
    /// </summary>
    namespace Math {
        /// <summary>
        /// Respresent very small values. Under epsilon, zero is considered.
        /// </summary>
        const Scalar Epsilon = 1.e-8f ;

        /// <summary>
        /// Perigon angle is a 360 degrees angle.
        /// </summary>
        const Scalar PerigonAngleDegrees = 360.f ;

        /// <summary>
        /// Straight angle is a 180 degrees angle.
        /// </summary>
        const Scalar StraightAngleDegrees = Math::PerigonAngleDegrees / 2.f ;

        /// <summary>
        /// Right is a 90 degrees angle.
        /// </summary>
        const Scalar RightAngleDegrees = Math::PerigonAngleDegrees / 4.f ;

        /// <summary>
        /// Approximation of PI value.
        /// </summary>
        const Scalar Pi = 4.f * atan(1.f) ;

        /// <summary>
        /// Approximation of PI/2 value.
        /// </summary>
        const Scalar HalfPi = Math::Pi / 2.f ;

        /// <summary>
        /// Approximation of PI/4 value.
        /// </summary>
        const Scalar QuartPi = Math::Pi / 4.f ;

        /// <summary>
        /// Approximation of PI*2 value.
        /// </summary>
        const Scalar PiTwice = Math::Pi * 2.f ;

        /// <summary>
        /// Computation of PI / 360.
        /// </summary>
        const Scalar PiOver360 = Math::Pi / Math::PerigonAngleDegrees ;

        /// <summary>
        /// Approximation of PI^2 value.
        /// </summary>
        const Scalar SquaredPi = Math::Pi * Math::Pi ;

        /// <summary>
        /// Value used to convert degrees to radians.
        /// </summary>
        const Scalar DegreesToRadians = Math::Pi / Math::StraightAngleDegrees ;

        /// <summary>
        /// Value used to convert radians to degrees.
        /// </summary>
        const Scalar RadiansToDegrees = Math::StraightAngleDegrees / Math::Pi ;

        /// <summary>
        /// Convert degrees to radians.
        /// </summary>
        /// <param name="degrees">Value of the angle in degrees.</param>
        /// <returns>Value of the angle in radians.</returns>
        inline Scalar toRadians(const Scalar degrees) ;

        /// <summary>
        /// Convert radians to degrees.
        /// </summary>
        /// <param name="radians">Value of the angle in radians.</param>
        /// <returns>Value of the angle in degrees.</returns>
        inline Scalar toDegrees(const Scalar radians) ;

        /// <summary>
        /// Returns sqrt(x^2 + y^2) without intermediate overflow or underflow.
        /// </summary>
        /// <typeparam name="T">Numerical type.</typeparam>
        /// <param name="x">X value.</param>
        /// <param name="y">Y value.</param>
        /// <returns>Length of the hypotenuse.</returns>
        template <class T>
        Scalar hypot(const T x, const T y) ;

        /// <summary>
        /// Check if a Scalar value is negative.
        /// </summary>
        /// <param name="value">Value to check.</param>
        /// <returns>true if value is negative, false otherwise.</returns>
        exported bool isNegative(const Scalar value) ;

        /// <summary>
        /// Check if a Scalar value is not a number.
        /// </summary>
        /// <param name="value">Value to check.</param>
        /// <returns>true if value is NaN, false otherwise.</returns>
        exported bool isNaN(const Scalar value) ;

        /// <summary>
        /// Check if a Scalar value is infinite.
        /// </summary>
        /// <param name="value">Value to check.</param>
        /// <returns>true if value is infinite, false otherwise.</returns>
        exported bool isInf(const Scalar value) ;

        /// <summary>
        /// Test if two scalar values are close enough to consider them as
        /// equal.
        /// </summary>
        /// <param name="a">First value.</param>
        /// <param name="b">Second value.</param>
        /// <param name="epsilon">
        /// Minimal distance between values to consider them different from
        /// each other.
        /// </param>
        /// <returns>
        /// true if the values are distant enough to be considered as
        /// different, false otherwise.
        /// </returns>
        exported bool equal(
            const Scalar a,
            const Scalar b,
            const Scalar epsilon = Epsilon
        ) ;

        /// <summary>
        /// Get the lower closest power of 2 for the given value.
        /// </summary>
        /// <param name="value">
        /// The value to get the closest power of 2.
        /// </param>
        /// <returns>The closest power of 2 of value.</returns>
        exported unsigned int lowClosestPower2(const unsigned int value) ;

        /// <summary>
        /// Get the closest power of 2 for the given value.
        /// </summary>
        /// <param name="value">
        /// The value to get the closest power of 2.
        /// </param>
        /// <returns>The closest power of 2 of value.</returns>
        exported unsigned int closestPower2(const unsigned int value) ;

        /// <summary>
        /// Get the higher closest power of 2 for the given value.
        /// </summary>
        /// <param name="value">
        /// The value to get the closest power of 2.
        /// </param>
        /// <returns>
        /// The closest power of 2 of value.
        /// </returns>
        exported unsigned int highClosestPower2(const unsigned int value) ;
    } ;

    Scalar Math::toRadians(const Scalar degrees) {
        return degrees * Math::DegreesToRadians ;
    }


    Scalar Math::toDegrees(const Scalar radians) {
        return radians * Math::RadiansToDegrees ;
    }

    template <class T>
    Scalar Math::hypot(const T x, const T y) {
        return sqrt((x * x) + (y * y)) ;
    }


    /// <summary>
    /// Convert degrees to radians.
    /// </summary>
    /// <param name="degrees">Value of the angle in degrees.</param>
    /// <returns>Value of the angle in radians.</returns>
    inline long double operator"" _deg(const long double degrees) {
        return degrees * Math::DegreesToRadians ;
    }

    /// <summary>
    /// Convert radians to degrees.
    /// </summary>
    /// <param name="radians">Value of the angle in radians.</param>
    /// <returns>Value of the angle in degrees.</returns>
    inline long double operator"" _rad(const long double radians) {
        return radians * Math::RadiansToDegrees ;
    }
} ;

#endif
