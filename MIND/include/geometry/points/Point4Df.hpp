#ifndef __MIND__GEOMETRY_POINT4DF__
#define __MIND__GEOMETRY_POINT4DF__

#include <array>
#include <iostream>

#include "MINDTypes.hpp"
#include "simd/SIMDVector.hpp"
#include "geometry/points/Point2Df.hpp"
#include "geometry/points/Point3Df.hpp"
#include "geometry/dimensions/Dimension2Df.hpp"
#include "geometry/dimensions/Dimension3Df.hpp"

namespace Mind {
    class Matrix4x4f ;

    /**
     * A Point is a very simple element that can be used in a space to place
     * elements, get distances between elements, etc.
     */
    class Point4Df {
        public:
            /**
             * Amount of coordinates.
             */
            static const int AmountCoords = 4 ;

            /**
             * Axis to get coordinates of the Point4D.
             */
            enum Axis {
                X,
                Y,
                Z,
                W
            } ;

        private:
            #ifdef USE_NO_SIMD
                /** Values of the Point2Df. */
                std::array<float, 4> m_values ;
            #else
                /** Values of the Point4Df. */
                SIMD::Vector4f m_values ;

                /**
                  * Create a Point4Df from a Vector4f.
                  */
                Point4Df(const SIMD::Vector4f& values) ;
            #endif

        public:
            /** Create a Point at the origin. */
            exported Point4Df() ;

            /** Create a Point. */
            exported Point4Df(const Point3Df& copy) ;

            /** Create a Point. */
            exported Point4Df(const Point2Df& copy) ;

            /**
             * Create a Point at the given position.
             * @param   x   Coordinate on X axis.
             * @param   y   Coordinate on Y axis.
             * @param   z   Coordinate on Z axis.
             * @param   w   Coordinate on W axis.
             */
            exported Point4Df(
                const Scalar x,
                const Scalar y,
                const Scalar z,
                const Scalar w
            ) ;

            /**
             * Translate a point of the given offsets.
             * @param   x   Offset on X axis.
             * @param   y   Offset on Y axis.
             * @param   z   Offset on Z axis.
             * @param   w   Offset on W axis.
             */
            exported void translate(
                const Scalar x,
                const Scalar y,
                const Scalar z,
                const Scalar w
            ) ;

            /**
             * Translate a point of the given offsets.
             * @param   offset  Offset on the four axes.
             */
            exported void translate(const Point4Df& offset) ;

            /**
             * Dot product between the current Point and another one.
             * @param   other   Another Point to compute the dot product.
             * @return  The result of the dot product.
             */
            exported Scalar dot(const Point4Df& other) const ;

            /**
             * Cross product between the current Point and another one.
             * The result is put in the current Point.
             * @param   other   Another Point to compute the cross product.
             */
            exported Point4Df cross(const Point4Df& other) const ;

            /**
             * Normalize the coordinates of the Point so that they are
             *          defined in [0, 1].
             */
            exported void normalize() ;

            /**
             * Round the values of the point.
             * @param   point   Point to get rounded values of.
             * @return  The point with rounded values.
             */
            exported static Point4Df round(const Point4Df& point) ;

            /**
             * Round the values of the point to lower.
             * @param   point   Point to get rounded values of.
             * @return  The point with rounded values.
             */
            exported static Point4Df floor(const Point4Df& point) ;

            /**
             * Round the values of the point to upper.
             * @param   point   Point to get rounded values of.
             * @return  The point with rounded values.
             */
            exported static Point4Df ceil(const Point4Df& point) ;

            /**
             * Merge two points at a middle point.
             * @param a The first point to merge.
             * @param b The second point to merge.
             * @return  The merged point at the center between both given points.
             */
            exported static Point4Df merge(const Point4Df& a, const Point4Df& b) ;

            /**
             * Multiply a Point coordinates by another.
             * @param   p       Point whose coordinates must be multiplied.
             * @param   other   Another Point
             */
            exported static Point4Df mul(const Point4Df& p, const Point4Df& other) ;

            /**
             * Get the distance between two points on X axis.
             * @param a First point.
             * @param b Second point.
             * @return  The distance between the points on the X axis.
             */
            exported static Scalar distanceX(const Point4Df& a, const Point4Df& b) ;

            /**
             * Get the distance between two points on Y axis.
             * @param a First point.
             * @param b Second point.
             * @return  The distance between the points on the Y axis.
             */
            exported static Scalar distanceY(const Point4Df& a, const Point4Df& b) ;

            /**
             * Get the distance between two points on Z axis.
             * @param a First point.
             * @param b Second point.
             * @return  The distance between the points on the Z axis.
             */
            exported static Scalar distanceZ(const Point4Df& a, const Point4Df& b) ;

            /**
             * Get the distance between two points on W axis.
             * @param a First point.
             * @param b Second point.
             * @return  The distance between the points on the Z axis.
             */
            exported static Scalar distanceW(const Point4Df& a, const Point4Df& b) ;

            /**
             * Give the distance between two points.
             * @param a First point.
             * @param b Second point.
             * @return  Distance between A and B.
             */
            exported static Scalar distance(const Point4Df& a, const Point4Df& b) ;

            /**
              * Compute the length of a vector.
              * @return  The length of the vector.
              */
            exported Scalar length() ;

            /** Get a coordinate. */
            exported Scalar get(const Axis axis) const ;

            /** Set a coordinate. */
            exported void set(const Axis axis, const Scalar value) ;

            /**
             * Move the point to the specified coordinates.
             * @param   x   Coordinate on X axis.
             * @param   y   Coordinate on Y axis.
             * @param   z   Coordinate on Z axis.
             * @param   w   Coordinate on W axis.
             */
            exported void set(
                const Scalar x,
                const Scalar y,
                const Scalar z,
                const Scalar w
            ) ;

            /**
             * Move the point to the specified coordinates.
             * @param   position    Position at which the point should be set.
             */
            exported void set(const Point4Df& position) ;

            /**
             * Convert the point to array.
             */
            exported std::array<float, 4> toArray() const ;

            /** Conversion from Point3D to Dimension2D. */
            exported explicit operator Dimension2Df() ;

            /** Conversion from Point3D to Dimension3D. */
            exported explicit operator Dimension3Df() ;

            /** Conversion from Point3D to Point2D. */
            exported explicit operator Point2Df() ;

            /** Conversion from Point3D to Point3D. */
            exported explicit operator Point3Df() ;

            /**
             * Add a Point and affect the result.
             * @param   other   The other Point to add.
             * @return  The sum of the two Points.
             */
            exported Point4Df& operator+=(Point4Df& other) ;

            /**
             * Substract a Point and affect the result.
             * @param   other   The other Point to substract.
             * @return  The substract of the two Points.
             */
            exported Point4Df& operator-=(Point4Df& other) ;

            /**
             * Multiply a Point by a scalar value and affect the result.
             * @param   coeff   The coeff to multiply the Point coordinates by.
             * @return  The result of the multiplication.
             */
            exported Point4Df& operator*=(Scalar coeff) ;

            /**
             * Multiply a Point by a matrix and affect the result.
             * @param   mat4    The matrix to multiply the Point with.
             * @return  The result of the multiplication.
             */
            exported Point4Df& operator*=(const Matrix4x4f& mat4) ;

            /**
             * Divide a Point by a scalar value and affect the result.
             * @param   coeff   The coeff to divide the Point coordinates by.
             * @return  The result of the division.
             */
            exported Point4Df& operator/=(Scalar coeff) ;

            /**
             * Test if two Points are at the same position.
             * @param   other   An other Point to compare to the current one.
             * @return  TRUE if the Points are at the same position, FALSE else.
             */
            exported bool operator==(const Point4Df& other) const ;

            /**
             * Test if two Points are at two different positions.
             * @param   other   An other Point to compare to the current one.
             * @return  TRUE if the Points are at two different positions, FALSE
             *          else.
             */
            exported bool operator!=(const Point4Df& other) const ;

            /**
             * Access a value in the Point4Df.
             * @param  axis  Axis of the coordinate to get in the Point4Df.
             * @return       Value at the @a axis.
             */
            exported Scalar operator[](const int axis) const ;

            /**
             * Access a value in the Point4Df.
             * @param  axis  Axis of the coordinate to get in the Point4Df.
             * @return       Value at the @a axis.
             */
            exported Scalar& operator[](const int axis) ;

            /**
              * Negate the coordinates of the point.
              * @param   p   The point to negate.
              * @return  The negate version of the point @a p.
              */
            exported friend Point4Df operator-(const Point4Df& p) ;

            /**
             * Add a Point coordinates to another ones.
             * @param   a   First Point.
             * @param   b   Second Point.
             * @return  Point at (a.x + b.x, a.y + b.y).
             */
            exported friend Point4Df operator+(const Point4Df& a, const Point4Df& b) ;

            /**
             * Substract a Point coordinates to another ones.
             * @param   a   First Point.
             * @param   b   Second Point.
             * @return  Point at (a.x - b.x, a.y - b.y).
             */
            exported friend Point4Df operator-(const Point4Df& a, const Point4Df& b) ;

            /**
             * Dot product of two Points (A.B).
             * @param   a   Point whose coordinates must be multiplied.
             * @param   b   Another Point to compute the dot product.
             * @return  Result of the dot product A.B.
             */
            exported friend Scalar operator*(const Point4Df& a, const Point4Df& b) ;

            /**
             * Multiply a vector by a matrix.
             * @param   vec Vector to multiply.
             * @param   mat Matrix to multiply.
             * @return  Result of the multiplication vec * mat.
             */
            exported friend Point4Df operator*(const Point4Df& vec, const Matrix4x4f& mat) ;

            /**
             * Multiply a Point coordinates by a scalar value (scale).
             * @param   p       Point whose coordinates must be multiplied.
             * @param   coeff   Factor to scale the coordinates.
             * @return  Point at (a.x * coeff, a.y * coeff).
             */
            exported friend Point4Df operator*(const Point4Df& p, Scalar coeff) ;

            /**
             * Divide a Point coordinates 3by a scalar value (scale).
             * @param   a       Point whose coordinates must be divided.
             * @param   coeff   Factor to scale the coordinates.
             * @return  Point at (a.x / coeff, a.y / coeff).
             */
            exported friend Point4Df operator/(const Point4Df& p, Scalar coeff) ;

            /**
             * Echo the Point coordinates on console.
             * @param   s   The stream in which print the formatted coordinates.
             * @param   p   The Point to print.
             * @return  The stream with the printed Point coordinates.
             */
            exported friend std::ostream& operator<<(std::ostream& s, const Point4Df& p) ;
    } ;

    typedef Point4Df Vector4f ;
} ;


#endif
