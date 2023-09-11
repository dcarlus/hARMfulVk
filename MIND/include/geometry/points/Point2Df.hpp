#ifndef __MIND__GEOMETRY_POINT2DF__
#define __MIND__GEOMETRY_POINT2DF__

#include <array>
#include <iostream>

#include "MINDTypes.hpp"
#include "simd/SIMDVector.hpp"
#include "geometry/points/Point3Df.hpp"
#include "geometry/dimensions/Dimension2Df.hpp"

namespace Mind {
    class Dimension2Df ;
    class Point3Df ;

    /**
     * A Point is a very simple element that can be used in a space to place
     * elements, get distances between elements, etc.
     */
    class Point2Df {
        public:
            /**
             * Amount of coordinates.
             */
            static const int AmountCoords = 2 ;

            /**
             * Axis to get coordinates of the Point3D.
             */
            enum Axis {
                X,
                Y
            } ;

        private:
            #ifdef USE_NO_SIMD
                /** Values of the Point2Df. */
                std::array<float, 2> m_values ;
            #else
                /** Values of the Point2Df. */
                SIMD::Vector4f m_values ;

                /**
                 * Create a Point3Df from a Vector4f.
                 */
                Point2Df(const SIMD::Vector4f& values) ;
            #endif


        public:
            /** Create a Point at the origin. */
            exported Point2Df() ;

            /**
             * Create a Point at the given position.
             * @param   x   Coordinate on X axis.
             * @param   y   Coordinate on Y axis.
             */
            exported Point2Df(const Scalar x, const Scalar y) ;

            /**
             * Translate a point of the given offsets.
             * @param   x   Offset on X axis.
             * @param   y   Offset on Y axis.
             */
            exported void translate(const Scalar x, const Scalar y) ;

            /**
             * Translate a point of the given offsets.
             * @param   offset  Offset on the two axes.
             */
            exported void translate(const Point2Df& offset) ;

            /**
             * Dot product between the current Point and another one.
             * @param   other   Another Point to compute the dot product.
             * @return  The result of the dot product.
             */
            exported Scalar dot(const Point2Df& other) const ;

            /**
             * Normalize the coordinates of the Point so that they are defined
             * in [0, 1].
             */
            exported void normalize() ;

            /**
             * Round the values of the point.
             * @param   point   Point to get rounded values of.
             * @return  The point with rounded values.
             */
            exported static Point2Df round(const Point2Df& point) ;

            /**
             * Round the values of the point to lower.
             * @param   point   Point to get rounded values of.
             * @return  The point with rounded values.
             */
            exported static Point2Df floor(const Point2Df& point) ;

            /**
             * Round the values of the point to upper.
             * @param   point   Point to get rounded values of.
             * @return  The point with rounded values.
             */
            exported static Point2Df ceil(const Point2Df& point) ;

            /**
             * Merge two points at a middle point.
             * @param a The first point to merge.
             * @param b The second point to merge.
             * @return  The merged point at the center between both given points.
             */
            exported static Point2Df merge(const Point2Df& a, const Point2Df& b) ;

            /**
             * Multiply a Point coordinates by another.
             * @param   p       Point whose coordinates must be multiplied.
             * @param   other   Another Point
             */
            exported static Point2Df mul(const Point2Df& p, const Point2Df& other) ;

            /**
             * Get the distance between two points on X axis.
             * @param a First point.
             * @param b Second point.
             * @return  The distance between the points on the X axis.
             */
            exported static Scalar distanceX(const Point2Df& a, const Point2Df& b) ;

            /**
             * Get the distance between two points on Y axis.
             * @param a First point.
             * @param b Second point.
             * @return  The distance between the points on the Y axis.
             */
            exported static Scalar distanceY(const Point2Df& a, const Point2Df& b) ;

            /**
             * Give the distance between two points.
             * @param a First point.
             * @param b Second point.
             * @return  Distance between A and B.
             */
            exported static Scalar distance(const Point2Df& a, const Point2Df& b) ;

            /**
              * Compute the length of a vector.
              * @return  The length of the vector.
              */
            exported Scalar length() ;

            /**
             * Compute the angle at the center of three points.
             * Use the cosinus law:<br/>
             * Angle at C = arccos((A² + B² - C²) / (2AB))
             * @param b First point of the angle.
             * @param c Center oint where is computed the angle.
             * @param d Third point of the angle.
             * @return  The angle in degrees at point C.
             */
            exported static Scalar angle(
                const Point2Df& b,
                const Point2Df& c,
                const Point2Df& d
            ) ;

            /**
             * Get the orientation of the angle at the center of three
             *          points.
             * @param b First point of the angle.
             * @param c Center oint where is computed the angle.
             * @param d Third point of the angle.
             * @return  The orientation of the angle at point B.
             */
            exported static int angleOrientation(
                const Point2Df& a,
                const Point2Df& b,
                const Point2Df& c
            ) ;

            /** Get a coordinate. */
            exported Scalar get(const Axis axis) const ;

            /**
              * Get the coordinates of the Vector3f in an Array4f.
              * The last indices are set to zero.
              * @param   output  Output parameter that will contain the values.
              * @return  The @a output parameter for convenient use.
              */
            exported Array4f& getCoordinates(Array4f& output) const ;

            /** Set a coordinate. */
            exported void set(const Axis axis, const Scalar value) ;

            /**
             * Move the point to the specified coordinates.
             * @param   x   Coordinate on X axis.
             * @param   y   Coordinate on Y axis.
             */
            exported void set(const Scalar x, const Scalar y) ;

            /**
             * Move the point to the specified coordinates.
             * @param   position    Position at which the point should be set.
             */
            exported void set(const Point2Df& position) ;

            /**
             * Convert the point to array.
             */
            exported std::array<float, 2> toArray() const ;

            /** Conversion from Point2D to Dimension2D. */
            exported explicit operator Dimension2Df() ;

            /** Conversion from Point2D to Point3D. */
            exported explicit operator Point3Df() ;

            /**
             * Add a Point and affect the result.
             * @param   other   The other Point to add.
             * @return  The sum of the two Points.
             */
            exported Point2Df& operator+=(Point2Df& other) ;

            /**
             * Substract a Point and affect the result.
             * @param   other   The other Point to substract.
             * @return  The substract of the two Points.
             */
            exported Point2Df& operator-=(Point2Df& other) ;

            /**
             * Multiply a Point by a scalar value and affect the result.
             * @param   coeff   The coeff to multiply the Point coordinates by.
             * @return  The result of the multiplication.
             */
            exported Point2Df& operator*=(const Scalar coeff) ;

            /**
             * Divide a Point by a scalar value and affect the result.
             * @param   coeff   The coeff to divide the Point coordinates by.
             * @return  The result of the division.
             */
            exported Point2Df& operator/=(const Scalar coeff) ;

            /**
             * Test if two Points are at the same position.
             * @param   other   An other Point to compare to the current one.
             * @return  TRUE if the Points are at the same position, FALSE else.
             */
            exported bool operator==(const Point2Df& other) const ;

            /**
             * Test if two Points are at two different positions.
             * @param   other   An other Point to compare to the current one.
             * @return  TRUE if the Points are at two different positions, FALSE
             *          else.
             */
            exported bool operator!=(const Point2Df& other) const ;

            /**
             * Access a value in the Point2Df.
             * @param  axis  Axis of the coordinate to get in the Point3Df.
             * @return       Value at the @a axis.
             */
            exported Scalar operator[](const int axis) const ;

            /**
             * Access a value in the Point2Df.
             * @param  axis  Axis of the coordinate to get in the Point3Df.
             * @return       Value at the @a axis.
             */
            exported Scalar& operator[](const int axis) ;

            /**
              * Negate the coordinates of the point.
              * @param   p   The point to negate.
              * @return  The negate version of the point @a p.
              */
            exported friend Point2Df operator-(const Point2Df& p) ;

            /**
             * Add a Point coordinates to another ones.
             * @param   a   First Point.
             * @param   b   Second Point.
             * @return  Point at (a.x + b.x, a.y + b.y).
             */
            exported friend Point2Df operator+(const Point2Df& a, const Point2Df& b) ;

            /**
             * Substract a Point coordinates to another ones.
             * @param   a   First Point.
             * @param   b   Second Point.
             * @return  Point at (a.x - b.x, a.y - b.y).
             */
            exported friend Point2Df operator-(const Point2Df& a, const Point2Df& b) ;

            /**
             * Dot product of two Points (A.B).
             * @param   a   Point whose coordinates must be multiplied.
             * @param   b   Another Point to compute the dot product.
             * @return  Result of the dot product A.B.
             */
            exported friend Scalar operator*(const Point2Df& a, const Point2Df& b) ;

            /**
             * Multiply a Point coordinates by a scalar value (scale).
             * @param   p       Point whose coordinates must be multiplied.
             * @param   coeff   Factor to scale the coordinates.
             * @return  Point at (a.x * coeff, a.y * coeff).
             */
            exported friend Point2Df operator*(const Point2Df& p, Scalar coeff) ;

            /**
             * Divide a Point coordinates by a scalar value (scale).
             * @param   a       Point whose coordinates must be divided.
             * @param   coeff   Factor to scale the coordinates.
             * @return  Point at (a.x / coeff, a.y / coeff).
             */
            exported friend Point2Df operator/(const Point2Df& p, Scalar coeff) ;

            /**
             * Echo the Point coordinates on console.
             * @param   s   The stream in which print the formatted coordinates.
             * @param   p   The Point to print.
             * @return  The stream with the printed Point coordinates.
             */
            exported friend std::ostream& operator<<(std::ostream& s, const Point2Df& p) ;
    } ;

    typedef Point2Df Vector2f ;
} ;

#endif
