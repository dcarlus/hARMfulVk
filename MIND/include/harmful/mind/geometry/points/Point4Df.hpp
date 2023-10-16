#ifndef __MIND__GEOMETRY_POINT4DF__
#define __MIND__GEOMETRY_POINT4DF__

#include <array>
#include <iostream>
#include <harmful/doom/utils/Platform.hpp>
#include "harmful/mind/MINDTypes.hpp"
#include "harmful/mind/simd/SIMDVector.hpp"
#include "harmful/mind/geometry/points/Point2Df.hpp"
#include "harmful/mind/geometry/points/Point3Df.hpp"
#include "harmful/mind/geometry/dimensions/Dimension2Df.hpp"
#include "harmful/mind/geometry/dimensions/Dimension3Df.hpp"

namespace Mind {
    class Matrix4x4f ;

    /// <summary>
    /// A Point is a very simple element that can be used in a space to place
    /// elements, get distances between elements, etc.
    /// </summary>
    class Point4Df {
        public:
            /// <summary>
            /// Amount of coordinates.
            /// </summary>
            static const int AmountCoords = 4 ;

            /// <summary>
            /// Axis to get coordinates of the Point4D.
            /// </summary>
            enum Axis {
                X,
                Y,
                Z,
                W
            } ;

        private:
            #ifdef USE_NO_SIMD
                /// <summary>
                /// Values of the Point4Df.
                /// </summary>
                std::array<float, 4> m_values ;
            #else
                /// <summary>
                /// Values of the Point4Df.
                /// </summary>
                SIMD::Vector4f m_values ;

                /// <summary>
                /// Create a Point4Df from a Vector4f.
                /// </summary>
                /// <param name="values">
                /// The Vector4f to convert to Point4Df.
                /// </param>
                Point4Df(const SIMD::Vector4f& values) ;
            #endif

        public:
            // Default constructors/assignemnts.
            exported Point4Df() = default;
            exported Point4Df(const Point4Df& copied) = default;
            exported Point4Df(Point4Df&& moved) = default;
            exported Point4Df& operator=(const Point4Df& copied) = default;
            exported Point4Df& operator=(Point4Df&& moved) = default;
            exported ~Point4Df() noexcept = default;

            /// <summary>
            /// Copy a Point.
            /// </summary>
            /// <param name="copy">Point to copy.</param>
            exported Point4Df(const Point3Df& copy);

            /// <summary>
            /// Create a Point.
            /// </summary>
            /// <param name="copy">Point to copy.</param>
            exported Point4Df(const Point2Df& copy) ;

            /// <summary>
            /// Create a Point at the given position.
            /// </summary>
            /// <param name="x">Coordinate on X axis.</param>
            /// <param name="y">Coordinate on Y axis.</param>
            /// <param name="z">Coordinate on Z axis.</param>
            /// <param name="w">Coordinate on W axis.</param>
            exported Point4Df(
                const Scalar x,
                const Scalar y,
                const Scalar z,
                const Scalar w
            ) ;

            /// <summary>
            /// Translate a point of the given offsets.
            /// </summary>
            /// <param name="x">Offset on X axis.</param>
            /// <param name="y">Offset on Y axis.</param>
            /// <param name="z">Offset on Z axis.</param>
            /// <param name="w">Offset on W axis.</param>
            exported void translate(
                const Scalar x,
                const Scalar y,
                const Scalar z,
                const Scalar w
            ) ;

            /// <summary>
            /// Translate a point of the given offsets.
            /// </summary>
            /// <param name="offset">Offset on the four axes.</param>
            exported void translate(const Point4Df& offset) ;

            /// <summary>
            /// Dot product between the current Point and another one.
            /// </summary>
            /// <param name="other">
            /// Another Point to compute the dot product.
            /// </param>
            /// <returns>The result of the dot product.</returns>
            exported Scalar dot(const Point4Df& other) const ;

            /// <summary>
            /// Cross product between the current Point and another one.
            /// The result is put in the current Point.
            /// </summary>
            /// <param name="other">
            /// Another Point to compute the cross product.
            /// </param>
            /// <returns>Result of the cross product.</returns>
            exported Point4Df cross(const Point4Df& other) const ;

            /// <summary>
            /// Normalize the coordinates of the Point so that they are defined
            /// in [0, 1].
            /// </summary>
            exported void normalize() ;

            /// <summary>
            /// Round the values of the point.
            /// </summary>
            /// <param name="point">Point to get rounded values of.</param>
            /// <returns>The point with rounded values.</returns>
            exported static Point4Df round(const Point4Df& point) ;

            /// <summary>
            /// Round the values of the point to lower.
            /// </summary>
            /// <param name="point">Point to get rounded values of.</param>
            /// <returns>The point with rounded values.</returns>
            exported static Point4Df floor(const Point4Df& point) ;

            /// <summary>
            /// Round the values of the point to upper.
            /// </summary>
            /// <param name="point">Point to get rounded values of.</param>
            /// <returns>The point with rounded values.</returns>
            exported static Point4Df ceil(const Point4Df& point) ;

            /// <summary>
            /// Merge two points at a middle point.
            /// </summary>
            /// <param name="a">The first point to merge.</param>
            /// <param name="b">The second point to merge.</param>
            /// <returns>
            /// The merged point at the center between both given points.
            /// </returns>
            exported static Point4Df merge(const Point4Df& a, const Point4Df& b) ;

            /// <summary>
            /// Multiply a Point coordinates by another.
            /// </summary>
            /// <param name="p">
            /// Point whose coordinates must be multiplied.
            /// </param>
            /// <param name="other">Another Point</param>
            /// <returns>Result of the multiplication.</returns>
            exported static Point4Df mul(const Point4Df& p, const Point4Df& other) ;

            /// <summary>
            /// Get the distance between two points on X axis.
            /// </summary>
            /// <param name="a">First point.</param>
            /// <param name="b">Second point.</param>
            /// <returns>
            /// The distance between the points on the X axis.
            /// </returns>
            exported static Scalar distanceX(const Point4Df& a, const Point4Df& b) ;

            /// <summary>
            /// Get the distance between two points on Y axis.
            /// </summary>
            /// <param name="a">First point.</param>
            /// <param name="b">Second point.</param>
            /// <returns>
            /// The distance between the points on the Y axis.
            /// </returns>
            exported static Scalar distanceY(const Point4Df& a, const Point4Df& b) ;

            /// <summary>
            /// Get the distance between two points on Z axis.
            /// </summary>
            /// <param name="a">First point.</param>
            /// <param name="b">Second point.</param>
            /// <returns>
            /// The distance between the points on the Z axis.
            /// </returns>
            exported static Scalar distanceZ(const Point4Df& a, const Point4Df& b) ;

            /// <summary>
            /// Get the distance between two points on W axis.
            /// </summary>
            /// <param name="a">First point.</param>
            /// <param name="b">Second point.</param>
            /// <returns>
            /// The distance between the points on the W axis.
            /// </returns>
            exported static Scalar distanceW(const Point4Df& a, const Point4Df& b) ;

            /// <summary>
            /// Give the distance between two points.
            /// </summary>
            /// <param name="a">First point.</param>
            /// <param name="b">Second point.</param>
            /// <returns>Distance between A and B.</returns>
            exported static Scalar distance(const Point4Df& a, const Point4Df& b) ;

            /// <summary>
            /// Compute the length of a vector.
            /// </summary>
            /// <returns>The length of the vector.</returns>
            exported Scalar length() ;

            /// <summary>
            /// Get a coordinate.
            /// </summary>
            /// <param name="axis">Axis of the coordinate to get.</param>
            /// <returns>Value of the wanted coordinate.</returns>
            exported Scalar get(const Axis axis) const ;

            /// <summary>
            /// Set a coordinate.
            /// </summary>
            /// <param name="axis">Axis of the coordinate to set.</param>
            /// <param name="value">Value of the coordinate.</param>
            exported void set(const Axis axis, const Scalar value) ;

            /// <summary>
            /// Move the point to the specified coordinates.
            /// </summary>
            /// <param name="x">Coordinate on X axis.</param>
            /// <param name="y">Coordinate on Y axis.</param>
            /// <param name="z">Coordinate on Z axis.</param>
            /// <param name="w">Coordinate on W axis.</param>
            exported void set(
                const Scalar x,
                const Scalar y,
                const Scalar z,
                const Scalar w
            ) ;

            /// <summary>
            /// Move the point to the specified coordinates.
            /// </summary>
            /// <param name="position">
            /// Position at which the point should be set.
            /// </param>
            exported void set(const Point4Df& position) ;

            /// <summary>
            /// Convert the point to array.
            /// </summary>
            /// <returns>
            /// Array containing the coordinates of the point.
            /// </returns>
            exported std::array<float, 4> toArray() const ;

            /// <summary>
            /// Conversion from Point3D to Dimension2D.
            /// </summary>
            exported explicit operator Dimension2Df() ;

            /// <summary>
            /// Conversion from Point3D to Dimension3D.
            /// </summary>
            exported explicit operator Dimension3Df() ;

            /// <summary>
            /// Conversion from Point3D to Point2D.
            /// </summary>
            exported explicit operator Point2Df() ;

            /// <summary>
            /// Conversion from Point3D to Point3D.
            /// </summary>
            exported explicit operator Point3Df() ;

            /// <summary>
            /// Add a Point and affect the result.
            /// </summary>
            /// <param name="other">The other Point to add.</param>
            /// <returns>The sum of the two Points.</returns>
            exported Point4Df& operator+=(Point4Df& other) ;

            /// <summary>
            /// Substract a Point and affect the result.
            /// </summary>
            /// <param name="other">The other Point to substract.</param>
            /// <returns>The substract of the two Points.</returns>
            exported Point4Df& operator-=(Point4Df& other) ;

            /// <summary>
            /// Multiply a Point by a scalar value and affect the result.
            /// </summary>
            /// <param name="coeff">
            /// The coeff to multiply the Point coordinates by.
            /// </param>
            /// <returns>The result of the multiplication.</returns>
            exported Point4Df& operator*=(Scalar coeff) ;

            /// <summary>
            /// Multiply a Point by a matrix and affect the result.
            /// </summary>
            /// <param name="mat4">
            /// The matrix to multiply the Point with.
            /// </param>
            /// <returns>The result of the multiplication.</returns>
            exported Point4Df& operator*=(const Matrix4x4f& mat4) ;

            /// <summary>
            /// Divide a Point by a scalar value and affect the result.
            /// </summary>
            /// <param name="coeff">
            /// The coeff to divide the Point coordinates by.
            /// </param>
            /// <returns>The result of the division.</returns>
            exported Point4Df& operator/=(Scalar coeff) ;

            /// <summary>
            /// Test if two Points are at the same position.
            /// </summary>
            /// <param name="other">
            /// An other Point to compare to the current one.
            /// </param>
            /// <returns>
            /// true if the Points are at the same position, false else.
            /// </returns>
            exported bool operator==(const Point4Df& other) const ;

            /// <summary>
            /// Test if two Points are at two different positions.
            /// </summary>
            /// <param name="other">
            /// An other Point to compare to the current one.
            /// </param>
            /// <returns>
            /// true if the Points are at two different positions, false else.
            /// </returns>
            exported bool operator!=(const Point4Df& other) const ;

            /// <summary>
            /// Access a value in the Point4Df.
            /// </summary>
            /// <param name="axis">
            /// Axis of the coordinate to get in the Point4Df.
            /// </param>
            /// <returns>Value at the axis.</returns>
            exported Scalar operator[](const int axis) const ;

            /// <summary>
            /// Access a value in the Point4Df.
            /// </summary>
            /// <param name="axis">
            /// Axis of the coordinate to get in the Point4Df.
            /// </param>
            /// <returns>Value at the axis.</returns>
            exported Scalar& operator[](const int axis) ;

            /// <summary>
            /// Negate the coordinates of the point.
            /// </summary>
            /// <param name="p">The point to negate.</param>
            /// <returns>The negate version of the point p.</returns>
            exported friend Point4Df operator-(const Point4Df& p) ;

            /// <summary>
            /// Add a Point coordinates to another ones.
            /// </summary>
            /// <param name="a">First Point.</param>
            /// <param name="b">Second Point.</param>
            /// <returns>
            /// Point at (a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w).
            /// </returns>
            exported friend Point4Df operator+(const Point4Df& a, const Point4Df& b) ;

            /// <summary>
            /// Substract a Point coordinates to another ones.
            /// </summary>
            /// <param name="a">First Point.</param>
            /// <param name="b">Second Point.</param>
            /// <returns>
            /// Point at (a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w).
            /// </returns>
            exported friend Point4Df operator-(const Point4Df& a, const Point4Df& b) ;

            /// <summary>
            /// Dot product of two Points (A.B).
            /// </summary>
            /// <param name="a">
            /// Point whose coordinates must be multiplied.
            /// </param>
            /// <param name="b">
            /// Another Point to compute the dot product.
            /// </param>
            /// <returns>Result of the dot product (A.B).</returns>
            exported friend Scalar operator*(const Point4Df& a, const Point4Df& b) ;

            /// <summary>
            /// Multiply a vector by a matrix.
            /// </summary>
            /// <param name="vec">Vector to multiply.</param>
            /// <param name="mat">Matrix to multiply.</param>
            /// <returns>Result of the multiplication vec * mat.</returns>
            exported friend Point4Df operator*(const Point4Df& vec, const Matrix4x4f& mat) ;

            /// <summary>
            /// Multiply a Point coordinates by a scalar value (scale).
            /// </summary>
            /// <param name="p">
            /// Point whose coordinates must be multiplied.
            /// </param>
            /// <param name="coeff">Factor to scale the coordinates.</param>
            /// <returns>
            /// Point at (a.x * coeff, a.y * coeff, a.z * coeff, a.w * coeff).
            /// </returns>
            exported friend Point4Df operator*(const Point4Df& p, Scalar coeff) ;

            /// <summary>
            /// Divide a Point coordinates 3by a scalar value (scale).
            /// </summary>
            /// <param name="p">
            /// Point whose coordinates must be divided.
            /// </param>
            /// <param name="coeff">
            /// Factor to scale the coordinates.
            /// </param>
            /// <returns>
            /// Point at (a.x / coeff, a.y / coeff, a.z / coeff, a.w / coeff).
            /// </returns>
            exported friend Point4Df operator/(const Point4Df& p, Scalar coeff) ;

            /// <summary>
            /// Echo the Point coordinates on console.
            /// </summary>
            /// <param name="s">
            /// The stream in which print the formatted coordinates.
            /// </param>
            /// <param name="p">
            /// The Point to print.
            /// </param>
            /// <returns>
            /// The stream with the printed Point coordinates.
            /// </returns>
            exported friend std::ostream& operator<<(std::ostream& s, const Point4Df& p) ;
    } ;

    typedef Point4Df Vector4f ;
} ;


#endif
