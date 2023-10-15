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
    /**
     * A Point is a very simple element that can be used in a space to place
     * elements, get distances between elements, etc.
     *
     * Implemented with the help of Quaternion Computation by Neil Dantam
     * (ntd@gatech.edu), Institute for Robotics and Intelligent Machines,
     * Georgia Institute of Technology, Atlanta, GA, USA.
     * http://www.neil.dantam.name/note/dantam-quaternion.pdf
     */
    class Quaternion final {
        public:
            /**
             * Axis in the Quaternion. Made to add some semantic to the code
             * instead of hardcoded values.
             */
            enum Axis : unsigned int { X, Y, Z, W } ;

            /** Quaternion with all its components set to zero. */
            static const Quaternion Zero ;

            /** Quaternion with all its components set to zero but W is one. */
            static const Quaternion Identity ;

        private:
            /**
             * Threshold to consider a value near zero.
             */
            static const Scalar Epsilon ;

            #ifdef USE_NO_SIMD
                /** Values of the Quaternion. */
                Array4f m_values ;
            #else
                /**
                 * Used to extract the vector part of a Quaternion.
                 */
                static const SIMD::Vector4f VectorPartExtractor ;

                /** Values of the Quaternion. */
                SIMD::Vector4f m_values ;

                /**
                 * Create a Quaternion from a Vector4f.
                 */
                Quaternion(const SIMD::Vector4f& values) ;
            #endif

        public:
            /**
             * Create a default Quaternion. It is initialized to a zero degree
             * rotation.
             */
            inline Quaternion() ;

            /**
             * Create a Quaternion from the given value, as is.
             * @param   x   Individual value of coordinate X.
             * @param   y   Individual value of coordinate Y.
             * @param   z   Individual value of coordinate Z.
             * @param   w   Individual value of coordinate W.
             */
            inline Quaternion(
                const Scalar x,
                const Scalar y,
                const Scalar z,
                const Scalar w
            ) ;

            /**
             * Create a Quaternion from Euler angles.
             * @param roll  Value of the roll angle in degrees.
             * @param pitch Value of the pitch angle in degrees.
             * @param yaw   Value of the yaw angle in degrees.
             */
            inline Quaternion(
                const Scalar roll,
                const Scalar pitch,
                const Scalar yaw
            ) ;

            /**
             * Create a Quaternion from a rotation matrix.
             * @param   matrix  Rotation matrix to generate a Quaternion from.
             */
            inline Quaternion(const Matrix3x3f& matrix) ;

            /**
             * Create a Quaternion from a vector and an angle.
             * @param   vector  Vector on representing the axis on which the
             *                  rotation is applied.
             * @param   angle   Angle of the rotation in radians.
             */
            inline Quaternion(const Vector3f& vector, const Scalar radAngle) ;

            /**
             * Create a Quaternion from three orthonormal axis.
             * @param xAxis Values of rotation for the X axis.
             * @param yAxis Values of rotation for the Y axis.
             * @param zAxis Values of rotation for the Z axis.
             */
            inline Quaternion(
                const Vector3f& xAxis,
                const Vector3f& yAxis,
                const Vector3f& zAxis
            ) ;

            /**
             * Dot product between the current Quaternion and another one.
             * @param   other   Another Quaternion to compute the dot product.
             * @return  The result of the dot product.
             */
            inline Scalar dot(const Quaternion& other) const ;

            /**
             * Norm of the Quaternion.
             * @return Norm of the Quaternion.
             */
            inline Scalar norm() const ;

            /**
             * Normalize the current Quaternion. The norm before normalization
             * is returned.
             * @return The norm of the Quaternion before the normalization is
             *         applied.
             */
            inline Scalar normalize() ;

            /**
             * Compute the inverse Quaternion of the current one.
             * There is no change in the current Quaternion components values.
             * @return The inverse of the current Quaternion.
             */
            exported Quaternion inverse() const ;

            /**
             * Calculate the exponential of the current Quaternion.
             * This method converts a pure Quaternion to a unit Quaternion.
             * @return The exponential of the current Quaternion.
             */
            exported Quaternion exp() const ;

            /**
             * Calculate the natural logarithm of the current Quaternion.
             * @return The natural logarithm of the current Quaternion.
             * @warning This only works on unit quaternions.
             */
            exported Quaternion ln() const ;

            /**
             * Spherical linear rotation interpolation using Quaternions.
             * It is slower than NLERP.
             * @param  time         Normalized time to get the corresponding
             *                      interpolated rotation.
             * @param  from         The starting rotation of the interpolation.
             * @param  to           The ending rotation of the interpolation.
             * @param  shortestPath TRUE to have a torque-minimal rotation,
             *                      FALSE otherwise.
             * @return              Result of the interpolation at the provided
             *                      @a time.
             * @remark The interpolations are NOT commutative!
             * @see    nlerp
             */
            exported static Quaternion slerp(
                const Scalar time,
                const Quaternion& from,
                const Quaternion& to,
                bool shortestPath
            ) ;

            /**
             * Normalized linear rotation interpolation using Quaternions.
             * It is faster than SLERP.
             * @param  time         Normalized time to get the corresponding
             *                      interpolated rotation.
             * @param  from         The starting rotation of the interpolation.
             * @param  to           The ending rotation of the interpolation.
             * @param  shortestPath TRUE to have a torque-minimal rotation,
             *                      FALSE otherwise.
             * @return              Result of the interpolation at the provided
             *                      @a time.
             * @remark The interpolations ARE commutative!
             * @see    slerp
             */
            exported static Quaternion nlerp(
                const Scalar time,
                const Quaternion& from,
                const Quaternion& to,
                bool shortestPath
            ) ;

            /**
             * Check if the current Quaternion and an @a other one are close
             * enough, using a tolerance value.
             * @param  other          The other Quaternion to compare.
             * @param  radiansEpsilon Tolerance value to consider the
             *                        Quaternions represent the same rotation,
             *                        or not.
             * @return                TRUE if the rotation are quite equal
             *                        (depending on the @a angleEpsilon value)
             *                        or FALSE if not.
             */
            inline bool closeTo(
                const Quaternion& other,
                const Scalar radiansEpsilon
            ) const ;

            /**
             * Swap the current Quaternion with another one.
             * @param other The other Quaternion to swap with the current one.
             */
            inline void swap(Quaternion& other) ;

            /**
             * Set the values of the Quaternion from a rotation matrix.
             * @param matrix Rotation matrix to set the Quaternion values from.
             */
            exported void from(const Matrix3x3f& matrix) ;

            /**
             * Set the values of the Quaternion from axes.
             * @param xAxis Values of rotation for the X axis.
             * @param yAxis Values of rotation for the Y axis.
             * @param zAxis Values of rotation for the Z axis.
             */
            exported void from(
                const Vector3f& xAxis,
                const Vector3f& yAxis,
                const Vector3f& zAxis
            ) ;

            /**
             * Set the values of the Quaternion from Euler angles.
             * @param roll  Value of the roll angle in degrees.
             * @param pitch Value of the pitch angle in degrees.
             * @param yaw   Value of the yaw angle in degrees.
             */
            exported void from(
                const Scalar roll,
                const Scalar pitch,
                const Scalar yaw
            ) ;

            /**
             * Set the values of the Quaternion from a vector (seen as axis) and
             * an angle.
             * @param vector   Vector acting as the axis of the rotation.
             *                 This vector must be normalized.
             * @param radAngle Angle of the rotation in radians.
             */
            exported void from(const Vector3f& vector, const Scalar radAngle) ;

            /**
             * Get the values of the Quaternion as a rotation matrix.
             * @param matrix The Matrix3x3f that will represent the same
             *               rotation than the current quaternion.
             */
            exported void to(Matrix3x3f& matrix) const ;

            /**
             * Get the values of the Quaternion as an axis (@a vector) and an
             * angle applied on this axis.
             * @param vector   Output vector on representing the axis on which
             *                 the rotation is applied.
             * @param radAngle Output angle of the rotation in radians.
             */
            exported void to(Vector3f& vector, Scalar& radAngle) const ;

            /**
             * Get the values of the Quaternion as a serie of three vectors, one
             * for each axis.
             * @param xAxis Values for the X axis.
             * @param yAxis Values for the Y axis.
             * @param zAxis Values for the Z axis.
             */
            exported void to(
                Vector3f& xAxis,
                Vector3f& yAxis,
                Vector3f& zAxis
            ) const ;

            /**
             * Convert the Quaternion to Euler angles.
             * @param roll  X-axis angle value.
             * @param pitch Y-axis angle value.
             * @param yaw   Z-axis angle value.
             */
            exported void to(
                Scalar& roll,
                Scalar& pitch,
                Scalar& yaw
            ) const ;

            /**
             * Access to a component of the Quaternion (read-only).
             * @param  axis  Axis to get value of.
             * @return       Value of the component on the wanted @a axis.
             */
            inline Scalar operator[](const Axis axis) const ;

            /**
             * Access to a component of the Quaternion (read and write).
             * @param  axis  Axis to get value of.
             * @return       Value of the component on the wanted @a axis.
             */
            inline Scalar& operator[](const Axis axis) ;

            /**
             * Addition of two Quaternions.
             * @param  other Another Quaternion that is added to the current
             *               one.
             * @return       Reference on the current Quaternion once it has
             *               been added to the @other one.
             */
            inline Quaternion& operator+=(const Quaternion& other) ;

            /**
             * Addition of two Quaternions.
             * @param  other Another Quaternion that is added to the current
             *               one.
             * @return       The result of the addition.
             */
            inline Quaternion operator+(const Quaternion& other) const ;

            /**
             * Soustraction of two Quaternions.
             * @param  other Another Quaternion that is substracted from the
             *               current one.
             * @return       Reference on the current Quaternion once it has
             *               been subtracted from the @other one.
             */
            inline Quaternion& operator-=(const Quaternion& other) ;

            /**
             * Soustraction of two Quaternions.
             * @param  other Another Quaternion that is substracted from the
             *               current one.
             * @return       The result of the soustraction.
             */
            inline Quaternion operator-(const Quaternion& other) const ;

            /**
             * Inverse the values of the Quaternion (X, Y, Z and W).
             */
            inline Quaternion operator-() const ;

            /**
             * Mulitplication of a Quaternion with a Scalar.
             * @param  scalar Value to multiply each component of the current
             *                Quaternion.
             * @return        Reference on the current Quaternion once it has
             *                been multiplied by @a value.
             */
            inline Quaternion& operator*=(const Scalar scalar) ;

            /**
             * Mulitplication of a Quaternion with a Scalar.
             * @param  scalar Value to multiply each component of the Quaternion.
             * @return        The result of the multiplication.
             */
            inline Quaternion operator*(const Scalar scalar) const ;

            /**
             * Multiplication of a Quaternion with another one.
             * Be aware that the multiplication is not commutative.
             * @param  other Another Quaternion that is multiplied with the
             *               current one.
             * @return       Reference on the current Quaternion once it has
             *               been subtracted from the @other one.
             */
            exported Quaternion& operator*=(const Quaternion& other) ;

            /**
             * Multiplication of a Quaternion with another one.
             * Be aware that the multiplication is not commutative.
             * @param  other Another Quaternion that is multiplied with the
             *               current one.
              * @return      The result of the multiplication.
             */
            exported Quaternion operator*(const Quaternion& other) const ;

            /**
             * Rotation of a Vector3f by the current Quaternion.
             * @param  vec3 The vector to rotate.
             * @return The rotated vector.
             */
            exported Vector3f operator*(const Vector3f& vec3) const ;

            /**
             * Check if two Quaternions have the same values.
             * @param  other Another Quaternion that is compared to the current
             *               one.
             * @return       TRUE if the Quaternions have the same component
             *               values, FALSE otherwise.
             */
            inline bool operator==(const Quaternion& other) const ;

            /**
             * Check if two Quaternions have the different values.
             * @param  other Another Quaternion that is compared to the current
             *               one.
             * @return       TRUE if the Quaternions have different component
             *               values, FALSE otherwise.
             */
            inline bool operator!=(const Quaternion& other) const ;

            /**
            * Echo the Quaternion values on console.
            * @param   s   The stream in which print the formatted coordinates.
            * @param   p   The Quaternion to print.
            * @return  The stream with the printed Quaternion coordinates.
            */
            inline friend std::ostream& operator<<(std::ostream& s, const Quaternion& p) ;
    } ;

    #ifdef USE_SIMD
        #include "Quaternion_SIMD.hpp"
    #else
        #include "Quaternion_NoSIMD.hpp"
    #endif
}

#endif
