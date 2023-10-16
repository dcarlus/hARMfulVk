#ifndef __MIND__GEOMETRY_QUATERNION__
#define __MIND__GEOMETRY_QUATERNION__

#include <iostream>
#include <harmful/doom/utils/Platform.hpp>
#include "harmful/mind/MINDTypes.hpp"
#include "harmful/mind/simd/SIMDVector.hpp"
#include "harmful/mind/geometry/points/Point3Df.hpp"
#include "harmful/mind/matrices/Matrix3x3f.hpp"
#include "harmful/mind/FastMath.hpp"
#include "harmful/mind/Math.hpp"

namespace Mind {
    /// <summary>
    /// A Point is a very simple element that can be used in a space to place
    /// elements, get distances between elements, etc.
    /// 
    /// Implemented with the help of Quaternion Computation by Neil Dantam
    /// (ntd@gatech.edu), Institute for Robotics and Intelligent Machines,
    /// Georgia Institute of Technology, Atlanta, GA, USA.
    /// http://www.neil.dantam.name/note/dantam-quaternion.pdf
    /// </summary>
    class Quaternion final {
        public:
            /// <summary>
            /// Axis in the Quaternion. Made to add some semantic to the code
            /// instead of hardcoded values.
            /// </summary>
            enum Axis : unsigned int { X, Y, Z, W } ;

            /// <summary>
            /// Quaternion with all its components set to zero.
            /// </summary>
            static const Quaternion Zero ;

            /// <summary>
            /// Quaternion with all its components set to zero but W is one.
            /// </summary>
            static const Quaternion Identity ;

        private:
            /// <summary>
            /// Threshold to consider a value near zero.
            /// </summary>
            static const Scalar Epsilon ;

            #ifdef USE_NO_SIMD
                /// <summary>
                /// Values of the Quaternion.
                /// </summary>
                Array4f m_values ;
            #else
                /// <summary>
                /// Used to extract the vector part of a Quaternion.
                /// </summary>
                static const SIMD::Vector4f VectorPartExtractor ;

                /// <summary>
                /// Values of the Quaternion.
                /// </summary>
                SIMD::Vector4f m_values{ 0.f, 0.f, 0.f, 0.f };

                /// <summary>
                /// Create a Quaternion from a Vector4f.
                /// </summary>
                /// <param name="values">
                /// Vector4f to convert to Quaternion.
                /// </param>
                Quaternion(const SIMD::Vector4f& values) ;
            #endif

        public:
            // Default constructors/assignemnts.
            exported Quaternion() = default;
            exported Quaternion(const Quaternion& copied) = default;
            exported Quaternion(Quaternion&& moved) = default;
            exported Quaternion& operator=(const Quaternion& copied) = default;
            exported Quaternion& operator=(Quaternion&& moved) = default;
            exported ~Quaternion() noexcept = default;

            /// <summary>
            /// Create a Quaternion from the given value, as is.
            /// </summary>
            /// <param name="x">Individual value of coordinate X.</param>
            /// <param name="y">Individual value of coordinate Y.</param>
            /// <param name="z">Individual value of coordinate Z.</param>
            /// <param name="w">Individual value of coordinate W.</param>
            inline Quaternion(
                const Scalar x,
                const Scalar y,
                const Scalar z,
                const Scalar w
            ) ;

            /// <summary>
            /// Create a Quaternion from Euler angles.
            /// </summary>
            /// <param name="roll">Value of the roll angle in degrees.</param>
            /// <param name="pitch">Value of the pitch angle in degrees.</param>
            /// <param name="yaw">Value of the yaw angle in degrees.</param>
            inline Quaternion(
                const Scalar roll,
                const Scalar pitch,
                const Scalar yaw
            ) ;

            /// <summary>
            /// Create a Quaternion from a rotation matrix.
            /// </summary>
            /// <param name="matrix">
            /// Rotation matrix to generate a Quaternion from.
            /// </param>
            inline Quaternion(const Matrix3x3f& matrix) ;

            /// <summary>
            /// Create a Quaternion from a vector and an angle.
            /// </summary>
            /// <param name="vector">
            /// Vector on representing the axis on which the rotation is
            /// applied.
            /// </param>
            /// <param name="radAngle">
            /// Angle of the rotation in radians.
            /// </param>
            inline Quaternion(const Vector3f& vector, const Scalar radAngle) ;

            /// <summary>
            /// Create a Quaternion from three orthonormal axis.
            /// </summary>
            /// <param name="xAxis">
            /// Values of rotation for the X axis.
            /// </param>
            /// <param name="yAxis">
            /// Values of rotation for the Y axis.
            /// </param>
            /// <param name="zAxis">
            /// Values of rotation for the Z axis.
            /// </param>
            inline Quaternion(
                const Vector3f& xAxis,
                const Vector3f& yAxis,
                const Vector3f& zAxis
            ) ;

            /// <summary>
            /// Dot product between the current Quaternion and another one.
            /// </summary>
            /// <param name="other">
            /// Another Quaternion to compute the dot product.
            /// </param>
            /// <returns>The result of the dot product.</returns>
            inline Scalar dot(const Quaternion& other) const ;

            /// <summary>
            /// Norm of the Quaternion.
            /// </summary>
            /// <returns>Norm of the Quaternion.</returns>
            inline Scalar norm() const ;

            /// <summary>
            /// Normalize the current Quaternion. The norm before normalization
            /// is returned.
            /// </summary>
            /// <returns>
            /// The norm of the Quaternion before the normalization is applied.
            /// </returns>
            inline Scalar normalize() ;

            /// <summary>
            /// Compute the inverse Quaternion of the current one.
            /// There is no change in the current Quaternion components values.
            /// </summary>
            /// <returns>The inverse of the current Quaternion.</returns>
            exported Quaternion inverse() const ;

            /// <summary>
            /// Calculate the exponential of the current Quaternion.
            /// This method converts a pure Quaternion to a unit Quaternion.
            /// </summary>
            /// <returns>The exponential of the current Quaternion.</returns>
            exported Quaternion exp() const ;

            /// <summary>
            /// Calculate the natural logarithm of the current Quaternion.
            /// </summary>
            /// <returns>
            /// The natural logarithm of the current Quaternion.
            /// </returns>
            /// <remarks>
            /// This only works on unit quaternions.
            /// </remarks>
            exported Quaternion ln() const ;

            /// <summary>
            /// Spherical linear rotation interpolation using Quaternions.
            /// It is slower than NLERP.
            /// </summary>
            /// <param name="time">
            /// Normalized time to get the corresponding interpolated rotation.
            /// </param>
            /// <param name="from">
            /// The starting rotation of the interpolation.
            /// </param>
            /// <param name="to">
            /// The ending rotation of the interpolation.
            /// </param>
            /// <param name="shortestPath">
            /// true to have a torque-minimal rotation, false otherwise.
            /// </param>
            /// <returns>
            /// Result of the interpolation at the provided time.
            /// </returns>
            exported static Quaternion slerp(
                const Scalar time,
                const Quaternion& from,
                const Quaternion& to,
                bool shortestPath
            ) ;

            /// <summary>
            /// Normalized linear rotation interpolation using Quaternions.
            /// It is faster than SLERP.
            /// </summary>
            /// <param name="time">
            /// Normalized time to get the corresponding interpolated rotation.
            /// </param>
            /// <param name="from">
            /// The starting rotation of the interpolation.
            /// </param>
            /// <param name="to">
            /// The ending rotation of the interpolation.
            /// </param>
            /// <param name="shortestPath">
            /// true to have a torque-minimal rotation, false otherwise.
            /// </param>
            /// <returns>
            /// Result of the interpolation at the provided time.
            /// </returns>
            /// <remarks>
            /// The interpolations ARE commutative!
            /// </remarks>
            exported static Quaternion nlerp(
                const Scalar time,
                const Quaternion& from,
                const Quaternion& to,
                bool shortestPath
            ) ;

            /// <summary>
            /// Check if the current Quaternion and an @a other one are close
            /// enough, using a tolerance value.
            /// </summary>
            /// <param name="other">The other Quaternion to compare.</param>
            /// <param name="radiansEpsilon">
            /// Tolerance value to consider the Quaternions represent the same
            /// rotation, or not.
            /// /param>
            /// <returns>
            /// true if the rotation are quite equal (depending on the
            /// angleEpsilon value) or false if not.
            /// </returns>
            inline bool closeTo(
                const Quaternion& other,
                const Scalar radiansEpsilon
            ) const ;

            /// <summary>
            /// Swap the current Quaternion with another one.
            /// </summary>
            /// <param name="other">
            /// The other Quaternion to swap with the current one.
            /// </param>
            inline void swap(Quaternion& other) ;

            /// <summary>
            /// Set the values of the Quaternion from a rotation matrix.
            /// </summary>
            /// <param name="matrix">
            /// Rotation matrix to set the Quaternion values from.
            /// </param>
            exported void from(const Matrix3x3f& matrix) ;

            /// <summary>
            /// Set the values of the Quaternion from axes.
            /// </summary>
            /// <param name="xAxis">
            /// Values of rotation for the X axis.
            /// </param>
            /// <param name="yAxis">
            /// Values of rotation for the Y axis.
            /// </param>
            /// <param name="zAxis">
            /// Values of rotation for the Z axis.
            /// </param>
            exported void from(
                const Vector3f& xAxis,
                const Vector3f& yAxis,
                const Vector3f& zAxis
            ) ;

            /// <summary>
            /// Set the values of the Quaternion from Euler angles.
            /// </summary>
            /// <param name="roll">Value of the roll angle in degrees.</param>
            /// <param name="pitch">Value of the pitch angle in degrees.</param>
            /// <param name="yaw">Value of the yaw angle in degrees.</param>
            exported void from(
                const Scalar roll,
                const Scalar pitch,
                const Scalar yaw
            ) ;

            /// <summary>
            /// Set the values of the Quaternion from a vector (seen as axis)
            /// and an angle.
            /// </summary>
            /// <param name="vector">
            /// Vector acting as the axis of the rotation. This vector must be
            /// normalized.
            /// </param>
            /// <param name="radAngle">
            /// Angle of the rotation in radians.
            /// </param>
            exported void from(const Vector3f& vector, const Scalar radAngle) ;

            /// <summary>
            /// Get the values of the Quaternion as a rotation matrix.
            /// </summary>
            /// <param name="matrix">
            /// The Matrix3x3f that will represent the same rotation than the
            /// current quaternion.
            /// </param>
            exported void to(Matrix3x3f& matrix) const ;

            /// <summary>
            /// Get the values of the Quaternion as an axis (@a vector) and an
            /// angle applied on this axis.
            /// </summary>
            /// <param name="vector">
            /// Output vector on representing the axis on which the rotation
            /// is applied.
            /// </param>
            /// <param name="radAngle">
            /// Output angle of the rotation in radians.
            /// </param>
            exported void to(Vector3f& vector, Scalar& radAngle) const ;

            /// <summary>
            /// Get the values of the Quaternion as a serie of three vectors,
            /// one for each axis.
            /// </summary>
            /// <param name="xAxis">Values for the X axis.</param>
            /// <param name="yAxis">Values for the Y axis.</param>
            /// <param name="zAxis">Values for the Z axis.</param>
            exported void to(
                Vector3f& xAxis,
                Vector3f& yAxis,
                Vector3f& zAxis
            ) const ;

            /// <summary>
            /// Convert the Quaternion to Euler angles.
            /// </summary>
            /// <param name="roll">X-axis angle value.</param>
            /// <param name="pitch">Y-axis angle value.</param>
            /// <param name="yaw">Z-axis angle value.</param>
            exported void to(
                Scalar& roll,
                Scalar& pitch,
                Scalar& yaw
            ) const ;

            /// <summary>
            /// Access to a component of the Quaternion (read-only).
            /// </summary>
            /// <param name="axis">Axis to get value of.</param>
            /// <returns>
            /// Value of the component on the wanted axis.
            /// </returns>
            inline Scalar operator[](const Axis axis) const ;

            /// <summary>
            /// Access to a component of the Quaternion (read and write).
            /// </summary>
            /// <param name="axis">Axis to get value of.</param>
            /// <returns>Value of the component on the wanted axis.</returns>
            inline Scalar& operator[](const Axis axis) ;

            /// <summary>
            /// Addition of two Quaternions.
            /// </summary>
            /// <param name="other">
            /// Another Quaternion that is added to the current one.
            /// </param>
            /// <returns>
            /// Reference on the current Quaternion once it has been added to
            /// the other one.
            /// </returns>
            inline Quaternion& operator+=(const Quaternion& other) ;

            /// <summary>
            /// Addition of two Quaternions.
            /// </summary>
            /// <param name="other">
            /// Another Quaternion that is added to the current one.
            /// </param>
            /// <returns>The result of the addition.</returns>
            inline Quaternion operator+(const Quaternion& other) const ;

            /// <summary>
            /// Substraction of two Quaternions.
            /// </summary>
            /// <param name="other">
            /// Another Quaternion that is substracted from the current one.
            /// </param>
            /// <returns>
            /// Reference on the current Quaternion once it has been subtracted
            /// from the @other one.
            /// </returns>
            inline Quaternion& operator-=(const Quaternion& other) ;

            /// <summary>
            /// Substraction of two Quaternions.
            /// </summary>
            /// <param name="other">
            /// Another Quaternion that is substracted from the current one.
            /// </param>
            /// <returns>The result of the soustraction.</returns>
            inline Quaternion operator-(const Quaternion& other) const ;

            /// <summary>
            /// Inverse the values of the Quaternion (X, Y, Z and W).
            /// </summary>
            /// <returns>Quaternion with inverted values.</returns>
            inline Quaternion operator-() const ;

            /// <summary>
            /// Mulitplication of a Quaternion with a Scalar.
            /// </summary>
            /// <param name="scalar">
            /// Value to multiply each component of the current Quaternion.
            /// </param>
            /// <returns>
            /// Reference on the current Quaternion once it has been multiplied
            /// by value.
            /// </returns>
            inline Quaternion& operator*=(const Scalar scalar) ;

            /// <summary>
            /// Mulitplication of a Quaternion with a Scalar.
            /// </summary>
            /// <param name="scalar">
            /// Value to multiply each component of the Quaternion.
            /// </param>
            /// <returns>The result of the multiplication.</returns>
            inline Quaternion operator*(const Scalar scalar) const ;

            /// <summary>
            /// Multiplication of a Quaternion with another one.
            /// Be aware that the multiplication is not commutative.
            /// </summary>
            /// <param name="other">
            /// Another Quaternion that is multiplied with the current one.
            /// </param>
            /// <returns>
            /// Reference on the current Quaternion once it has been subtracted
            /// from the @other one.
            /// </returns>
            exported Quaternion& operator*=(const Quaternion& other) ;

            /// <summary>
            /// Multiplication of a Quaternion with another one.
            /// e aware that the multiplication is not commutative.
            /// </summary>
            /// <param name="other">
            /// Another Quaternion that is multiplied with the current one.
            /// </param>
            /// <returns>The result of the multiplication.</returns>
            exported Quaternion operator*(const Quaternion& other) const ;

            /// <summary>
            /// Rotation of a Vector3f by the current Quaternion.
            /// </summary>
            /// <param name="vec3">The vector to rotate.</param>
            /// <returns>The rotated vector.</returns>
            exported Vector3f operator*(const Vector3f& vec3) const ;

            /// <summary>
            /// Check if two Quaternions have the same values.
            /// </summary>
            /// <param name="other">
            /// Another Quaternion that is compared to the current one.
            /// </param>
            /// <returns>
            /// true if the Quaternions have the same component values, false
            /// otherwise.
            /// </returns>
            inline bool operator==(const Quaternion& other) const ;

            /// <summary>
            /// Check if two Quaternions have the different values.
            /// </summary>
            /// <param name="other">
            /// Another Quaternion that is compared to the current one.
            /// </param>
            /// <returns>
            /// true if the Quaternions have different component values, false
            /// otherwise.
            /// </returns>
            inline bool operator!=(const Quaternion& other) const ;

            /// <summary>
            /// Echo the Quaternion values on console.
            /// </summary>
            /// <param name="s">
            /// The stream in which print the formatted coordinates.
            /// </param>
            /// <param name="p">
            /// The Quaternion to print.
            /// </param>
            /// <returns>
            /// The stream with the printed Quaternion coordinates.
            /// </returns>
            inline friend std::ostream& operator<<(std::ostream& s, const Quaternion& p) ;
    } ;

    #ifdef USE_SIMD
        #include "Quaternion_SIMD.hpp"
    #else
        #include "Quaternion_NoSIMD.hpp"
    #endif
}

#endif
