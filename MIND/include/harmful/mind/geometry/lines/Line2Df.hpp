#ifndef __MIND__GEOMETRY_LINE2DF__
#define __MIND__GEOMETRY_LINE2DF__

#include <iostream>
#include <harmful/doom/utils/Platform.hpp>
#include "harmful/mind/MINDTypes.hpp"
#include "harmful/mind/geometry/rectangles/Rectangle2Df.hpp"

namespace Mind {
    class Rectangle2Df ;

    // Pre-declare operator overloadings
    class Line2Df ;
    std::ostream& operator<<(std::ostream& s, const Line2Df& l) ;

    /// <summary>
    /// A Line is a straight path through two points.
    /// </summary>
    class Line2Df final {
        private:
            /// <summary>
            /// Start point.
            /// </summary>
            Point2Df m_start ;

            /// <summary>
            /// End point.
            /// </summary>
            Point2Df m_end ;

            /// <summary>
            /// Test if the Line has changed.
            /// </summary>
            bool m_isChanged{ false };

            /// <summary>
            /// Length of the Line.
            /// </summary>
            Scalar m_length = 0.f;

        public:
            // Default constructors/assignemnts.
            exported Line2Df() = default;
            exported Line2Df(const Line2Df& copied) = default;
            exported Line2Df(Line2Df&& moved) = default;
            exported Line2Df& operator=(const Line2Df& copied) = default;
            exported Line2Df& operator=(Line2Df&& moved) = default;
            exported ~Line2Df() noexcept = default;

            /// <summary>
            /// Create an Line through the given points.
            /// </summary>
            /// <param name="start">The start point.</param>
            /// <param name="end">The end point.</param>
            exported Line2Df(const Point2Df& start, const Point2Df& end) ;

            /// <summary>
            /// Get the length of the Line.
            /// </summary>
            /// <returns>The length of the Line.</returns>
            exported Scalar length() ;

            /// <summary>
            /// Get the squared length of the Line.
            /// </summary>
            /// <returns>Squared length of the Line.</returns>
            exported Scalar lengthSquared() ;

            /// <summary>
            /// Test if a Line is contiguous to this one.
            /// </summary>
            /// <param name="other">
            /// The other Line to test to the current Line.
            /// </param>
            /// <returns>
            /// true if a Point is common to both segments, false else.
            /// </returns>
            exported bool isContiguousTo(const Line2Df& other) ;

            /// <summary>
            /// This is similar to the Line2D.relativeCCW() function from
            /// Java2D.
            /// </summary>
            /// <param name="l">The Line used as reference.</param>
            /// <param name="p">The Point to compare to the segment.</param>
            /// <returns>
            /// An indicator of where the specified point (px,py) lies with
            /// respect to this line segment.
            /// </returns>
            exported static int8_t CCW(const Line2Df& l, const Point2Df& p) ;

            /// <summary>
            /// Get the same Line without constraint about its position. The
            /// start point of the Line is set as the origin of the plan.
            /// </summary>
            /// <param name="l">
            /// The Line to express as an relative segment to the origin.
            /// </param>
            /// <returns>
            /// A Line similar to the one give, expressed to the origin of the
            /// plan.
            /// </returns>
            exported static Line2Df relative(const Line2Df& l) ;

            /// <summary>
            /// Test if the Line intersects another one.
            /// </summary>
            /// <param name="line">The other Line to test.</param>
            /// <returns>
            /// true if the two Lines intersect, false otherwise.
            /// </returns>
            exported bool intersects(const Line2Df& line) ;

            /// <summary>
            /// Compute the distance of the Line to the given Point.
            /// </summary>
            /// <param name="point">
            /// Point to measure its distance to the Line.
            /// </param>
            /// <returns>
            /// Distance between the Line and the Point.
            /// </returns>
            exported virtual Scalar distanceTo(const Point2Df& point) ;

            /// <summary>
            /// Compute the distance of the Line to the given Point.
            /// </summary>
            /// <param name="x">Coordinate on X axis.</param>
            /// <param name="y">Coordinate on Y axis.</param>
            /// <returns>Distance between the Line and the Point.</returns>
            exported virtual Scalar distanceTo(const Scalar x, const Scalar y) ;

            /// <summary>
            /// Compute the squared distance of the Line to the given Point.
            /// </summary>
            /// <param name="point">
            /// Point to measure its distance to the Line.
            /// </param>
            /// <returns>Distance between the Line and the Point.</returns>
            exported virtual Scalar distanceSquaredTo(const Point2Df& point) ;

            /// <summary>
            /// Compute the squared distance of the Line to the given Point.
            /// </summary>
            /// <param name="x">Coordinate of the Point on X axis.</param>
            /// <param name="y">Coordinate of the Point on Y axis.</param>
            /// <returns>Distance between the Line and the Point.</returns>
            exported virtual Scalar distanceSquaredTo(const Scalar x, const Scalar y) ;

            /// <summary>
            /// Get the Rectangle that represents the boundaries of the Line.
            /// </summary>
            /// <returns>
            /// The Rectangle representing the boundaries of the line.
            /// </returns>
            exported const Rectangle2Df bounds() const ;

            /// <summary>
            /// Get the starting point of the Line.
            /// </summary>
            /// <returns>The start point of the Line.</returns>
            exported const Point2Df& startPoint() const ;

            /// <summary>
            /// Get the ending point of the Line.
            /// </summary>
            /// <returns>The ending point of the Line.</returns>
            exported const Point2Df& endPoint() const ;

            /// <summary>
            /// Get the X coordinate of the start point.
            /// </summary>
            /// <returns>The X coordinate of the start point.</returns>
            exported Scalar startX() const ;

            /// <summary>
            /// Get the Y coordinate of the start point.
            /// </summary>
            /// <returns>The Y coordinate of the start point.</returns>
            exported Scalar startY() const ;

            /// <summary>
            /// Get the X coordinate of the end point.
            /// </summary>
            /// <returns>The X coordinate of the end point.</returns>
            exported Scalar endX() const ;

            /// <summary>
            /// Get the Y coordinate of the end point.
            /// </summary>
            /// <returns>The Y coordinate of the end point.</returns>
            exported Scalar endY() const ;

            /// <summary>
            /// Test if the Line is empty (no length).
            /// </summary>
            /// <returns>true if the length is 0, false otherwise.</returns>
            exported bool isEmpty() const ;

            /// <summary>
            /// Test if two Lines are at the same position.
            /// </summary>
            /// <param name="other">
            /// An other Line to compare to the current one.
            /// </param>
            /// <returns>
            /// true if the Lines are at the same position, false else.
            /// </returns>
            exported bool operator==(const Line2Df& other) const ;

            /// <summary>
            /// Test if two Lines are at two different positions.
            /// </summary>
            /// <param name="other">
            /// An other Line to compare to the current one.
            /// </param>
            /// <returns>
            /// true if the Lines are at two different positions, false else.
            /// </returns>
            exported bool operator!=(const Line2Df& other) const ;

            /// <summary>
            /// Echo the Line coordinates on console.
            /// </summary>
            /// <param name="s">
            /// The stream in which print the formatted coordinates.
            /// </param>
            /// <param name="l">The Line to print.</param>
            /// <returns>
            /// The stream with the printed Line coordinates.
            /// </returns>
            friend std::ostream& operator<<(std::ostream& s, const Line2Df& l) ;
    } ;
} ;

#endif
