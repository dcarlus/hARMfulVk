#ifndef __MIND__GEOMETRY_POINT2DF__
#define __MIND__GEOMETRY_POINT2DF__

#include <array>
#include <iostream>
#include <harmful/doom/utils/Platform.hpp>
#include "harmful/mind/MINDTypes.hpp"
#include "harmful/mind/simd/SIMDVector.hpp"
#include "harmful/mind/geometry/points/Point3Df.hpp"
#include "harmful/mind/geometry/dimensions/Dimension2Df.hpp"

namespace Mind {
    class Dimension2Df ;
    class Point3Df ;

    /// <summary>
    /// A Point is a very simple element that can be used in a space to place
    /// elements, get distances between elements, etc.
    /// </summary>
    class Point2Df {
        public:
            /// <summary>
            /// Amount of coordinates.
            /// </summary>
            static const int AmountCoords = 2 ;

            /// <summary>
            /// Axis to get coordinates of the Point.
            /// </summary>
            enum Axis {
                X,
                Y
            } ;

        private:
            #ifdef USE_NO_SIMD
                /// <summary>
                /// Values of the Point2Df.
                /// </summary>
                std::array<float, 2> m_values ;
            #else
                /// <summary>
                /// Values of the Point2Df.
                /// </summary>
                SIMD::Vector4f m_values{ 0.f, 0.f, 0.f, 0.f };

                /// <summary>
                /// Create a Point2Df from a Vector4f.
                /// </summary>
                /// <param name="values">
                /// The Vector4f to convert to Point2Df.
                /// </param>
                Point2Df(const SIMD::Vector4f& values) ;
            #endif

        public:
            // Default constructors/assignemnts.
            exported Point2Df() = default;
            exported Point2Df(const Point2Df& copied) = default;
            exported Point2Df(Point2Df&& moved) = default;
            exported Point2Df& operator=(const Point2Df& copied) = default;
            exported Point2Df& operator=(Point2Df&& moved) = default;
            exported ~Point2Df() noexcept = default;

            /// <summary>
            /// Create a Point at the given position.
            /// </summary>
            /// <param name="x">Coordinate on X axis.</param>
            /// <param name="y">Coordinate on Y axis.</param>
            exported Point2Df(const Scalar x, const Scalar y) ;

            /// <summary>
            /// Translate a point of the given offsets.
            /// </summary>
            /// <param name="x">Offset on X axis.</param>
            /// <param name="y">Offset on Y axis.</param>
            exported void translate(const Scalar x, const Scalar y) ;

            /// <summary>
            /// Translate a point of the given offsets.
            /// </summary>
            /// <param name="offset">Offset on the two axes.</param>
            exported void translate(const Point2Df& offset) ;

            /// <summary>
            /// Dot product between the current Point and another one.
            /// </summary>
            /// <param name="other">
            /// Another Point to compute the dot product.
            /// </param>
            /// <returns>The result of the dot product.</returns>
            exported Scalar dot(const Point2Df& other) const ;

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
            exported static Point2Df round(const Point2Df& point) ;

            /// <summary>
            /// Round the values of the point to lower.
            /// </summary>
            /// <param name="point">Point to get rounded values of.</param>
            /// <returns>The point with rounded values.</returns>
            exported static Point2Df floor(const Point2Df& point) ;

            /// <summary>
            /// Round the values of the point to upper.
            /// </summary>
            /// <param name="point">Point to get rounded values of.</param>
            /// <returns>The point with rounded values.</returns>
            exported static Point2Df ceil(const Point2Df& point) ;

            /// <summary>
            /// Merge two points at a middle point.
            /// </summary>
            /// <param name="a">The first point to merge.</param>
            /// <param name="b">The second point to merge.</param>
            /// <returns>
            /// The merged point at the center between both given points.
            /// </returns>
            exported static Point2Df merge(const Point2Df& a, const Point2Df& b) ;

            /// <summary>
            /// Multiply a Point coordinates by another.
            /// </summary>
            /// <param name="p">
            /// Point whose coordinates must be multiplied.
            /// </param>
            /// <param name="other">Another Point</param>
            /// <returns>Result of the multiplication.</returns>
            exported static Point2Df mul(
                const Point2Df& p,
                const Point2Df& other
            ) ;

            /// <summary>
            /// Get the distance between two points on X axis.
            /// </summary>
            /// <param name="a">First point.</param>
            /// <param name="b">Second point.</param>
            /// <returns>The distance between the points on the X axis.</returns>
            exported static Scalar distanceX(
                const Point2Df& a,
                const Point2Df& b
            ) ;

            /// <summary>
            /// Get the distance between two points on Y axis.
            /// </summary>
            /// <param name="a">First point.</param>
            /// <param name="b">Second point.</param>
            /// <returns>The distance between the points on the Y axis.</returns>
            exported static Scalar distanceY(const Point2Df& a, const Point2Df& b) ;

            /// <summary>
            /// Give the distance between two points.
            /// </summary>
            /// <param name="a">First point.</param>
            /// <param name="b">Second point.</param>
            /// <returns>Distance between A and B.</returns>
            exported static Scalar distance(const Point2Df& a, const Point2Df& b) ;

            /// <summary>
            /// Compute the length of a vector.
            /// </summary>
            /// <returns>The length of the vector.</returns>
            exported Scalar length() ;

            /// <summary>
            /// Compute the angle at the center of three points.
            /// Use the cosinus law:<br/>
            /// Angle at C = arccos((A² + B² - C²) / (2AB))
            /// </summary>
            /// <param name="b">First point of the angle.</param>
            /// <param name="c">Center oint where is computed the angle.</param>
            /// <param name="d">Third point of the angle.</param>
            /// <returns>The angle in degrees at point C.</returns>
            exported static Scalar angle(
                const Point2Df& b,
                const Point2Df& c,
                const Point2Df& d
            ) ;

            /// <summary>
            /// Get the orientation of the angle at the center of three points.
            /// </summary>
            /// <param name="a">First point of the angle.</param>
            /// <param name="b">Center point where is computed the angle.</param>
            /// <param name="c">Third point of the angle.</param>
            /// <returns>The orientation of the angle at point B.</returns>
            exported static int angleOrientation(
                const Point2Df& a,
                const Point2Df& b,
                const Point2Df& c
            ) ;

            /// <summary>
            /// Get a coordinate.
            /// </summary>
            /// <param name="axis">Axis of the coordinate to get.</param>
            /// <returns>Value of the wanted coordinate.</returns>
            exported Scalar get(const Axis axis) const ;

            /// <summary>
            /// Get the coordinates of the Vector3f in an Array4f.
            /// The last indices are set to zero.
            /// </summary>
            /// <param name="output">
            /// Output parameter that will contain the values.
            /// </param>
            /// <returns>The output parameter for convenient use.</returns>
            exported Array4f& getCoordinates(Array4f& output) const ;

            /// <summary>
            /// Set a coordinate.
            /// </summary>
            /// <param name="axis">Axis of the coordinate to get</param>
            /// <param name="value">Value of the coordinate.</param>
            exported void set(const Axis axis, const Scalar value) ;

            /// <summary>
            /// Move the point to the specified coordinates.
            /// </summary>
            /// <param name="x">Coordinate on X axis.</param>
            /// <param name="y">Coordinate on Y axis.</param>
            exported void set(const Scalar x, const Scalar y) ;

            /// <summary>
            /// Move the point to the specified coordinates.
            /// </summary>
            /// <param name="position">
            /// Position at which the point should be set.
            /// </param>
            exported void set(const Point2Df& position) ;

            /// <summary>
            /// Convert the point to array.
            /// </summary>
            /// <returns>
            /// An array containing the coordinates of the point.
            /// </returns>
            exported std::array<float, 2> toArray() const ;

            /// <summary>
            ///  Conversion from Point2D to Dimension2D.
            /// </summary>
            exported explicit operator Dimension2Df() ;

            /// <summary>
            /// Conversion from Point2D to Point3D.
            /// </summary>
            exported explicit operator Point3Df() ;

            /// <summary>
            /// Add a Point and affect the result.
            /// </summary>
            /// <param name="other">The other Point to add.</param>
            /// <returns>The sum of the two Points.</returns>
            exported Point2Df& operator+=(Point2Df& other) ;

            /// <summary>
            /// Substract a Point and affect the result.
            /// </summary>
            /// <param name="other">The other Point to substract.</param>
            /// <returns>The substract of the two Points.</returns>
            exported Point2Df& operator-=(Point2Df& other) ;

            /// <summary>
            /// Multiply a Point by a scalar value and affect the result.
            /// </summary>
            /// <param name="coeff">
            /// The coeff to multiply the Point coordinates by.
            /// </param>
            /// <returns>The result of the multiplication.</returns>
            exported Point2Df& operator*=(const Scalar coeff) ;

            /// <summary>
            /// Divide a Point by a scalar value and affect the result.
            /// </summary>
            /// <param name="coeff">
            /// The coeff to divide the Point coordinates by.
            /// </param>
            /// <returns>The result of the division.</returns>
            exported Point2Df& operator/=(const Scalar coeff) ;

            /// <summary>
            /// Test if two Points are at the same position.
            /// </summary>
            /// <param name="other">
            /// An other Point to compare to the current one.
            /// </param>
            /// <returns>
            /// true if the Points are at the same position, false else.
            /// </returns>
            exported bool operator==(const Point2Df& other) const ;

            /// <summary>
            /// Test if two Points are at two different positions.
            /// </summary>
            /// <param name="other">
            /// An other Point to compare to the current one.
            /// </param>
            /// <returns>
            /// true if the Points are at two different positions, false else.
            /// </returns>
            exported bool operator!=(const Point2Df& other) const ;

            /// <summary>
            /// Access a value in the Point2Df.
            /// </summary>
            /// <param name="axis">
            /// Axis of the coordinate to get in the Point2Df.
            /// </param>
            /// <returns>
            /// Value at the axis.
            /// </returns>
            exported Scalar operator[](const int axis) const ;

            /// <summary>
            /// Access a value in the Point2Df.
            /// </summary>
            /// <param name="axis">
            /// Axis of the coordinate to get in the Point2Df.
            /// </param>
            /// <returns>
            /// Value at the axis.
            /// </returns>
            exported Scalar& operator[](const int axis) ;

            /// <summary>
            /// Negate the coordinates of the point.
            /// </summary>
            /// <param name="p">The point to negate.</param>
            /// <returns>The negate version of the point p.</returns>
            exported friend Point2Df operator-(const Point2Df& p) ;

            /// <summary>
            /// Add a Point coordinates to another ones.
            /// </summary>
            /// <param name="a">First Point.</param>
            /// <param name="b">Second Point.</param>
            /// <returns>Point at (a.x + b.x, a.y + b.y).</returns>
            exported friend Point2Df operator+(const Point2Df& a, const Point2Df& b) ;

            /// <summary>
            /// Substract a Point coordinates to another ones.
            /// </summary>
            /// <param name="a">First Point.</param>
            /// <param name="b">Second Point.</param>
            /// <returns>Point at (a.x - b.x, a.y - b.y).</returns>
            exported friend Point2Df operator-(const Point2Df& a, const Point2Df& b) ;

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
            exported friend Scalar operator*(const Point2Df& a, const Point2Df& b) ;

            /// <summary>
            /// Multiply a Point coordinates by a scalar value (scale).
            /// </summary>
            /// <param name="p">
            /// Point whose coordinates must be multiplied.
            /// </param>
            /// <param name="coeff">
            /// Factor to scale the coordinates.
            /// </param>
            /// <returns>Point at (a.x * coeff, a.y * coeff).</returns>
            exported friend Point2Df operator*(const Point2Df& p, Scalar coeff) ;

            /// <summary>
            /// Divide a Point coordinates by a scalar value (scale).
            /// </summary>
            /// <param name="p">
            /// Point whose coordinates must be divided.
            /// </param>
            /// <param name="coeff">Factor to scale the coordinates.</param>
            /// <returns>Point at (a.x / coeff, a.y / coeff).</returns>
            exported friend Point2Df operator/(const Point2Df& p, Scalar coeff) ;

            /// <summary>
            /// Echo the Point coordinates on console.
            /// </summary>
            /// <param name="s">
            /// The stream in which print the formatted coordinates.
            /// </param>
            /// <param name="p">The Point to print.</param>
            /// <returns>The stream with the printed Point coordinates.</returns>
            exported friend std::ostream& operator<<(std::ostream& s, const Point2Df& p) ;
    } ;

    typedef Point2Df Vector2f ;
} ;

#endif
