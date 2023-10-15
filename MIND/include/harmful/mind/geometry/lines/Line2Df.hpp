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

    /**
     * A Line is a straight path through two points.
     */
    class Line2Df final {
        private:
            /** Start point. */
            Point2Df m_start ;

            /** End point. */
            Point2Df m_end ;

            /** Test if the Line has changed. */
            bool m_isChanged = false ;

            /** Length of the Line. */
            Scalar m_length ;

        public:
            /** Create an empty Line. */
            exported Line2Df() ;

            /**
             * Copy a Line.
             * @param   copied      Line to copy.
             */
            exported Line2Df(const Line2Df& copied) = default ;

            /**
             * Move a Line.
             * @param   moved       Line to move.
             */
            exported Line2Df(Line2Df&& moved) = default ;

            /**
             * Create an Line through the given points.
             * @param   start       The start point.
             * @param   end         The end point.
             */
            exported Line2Df(const Point2Df& start, const Point2Df& end) ;

            /** Destroy the Line. */
            exported virtual ~Line2Df() = default ;

            /**
             * Get the length of the Line.
             * @return  The length of the Line.
             */
            exported Scalar length() ;

            /**
             * Get the length of the Line.
             * @return  The length of the Line.
             */
            exported Scalar lengthSquared() ;

            /**
             * Test if a Line is contiguous to this one.
             * @param s     The other Line to test to the current Line.
             * @return TRUE if a Point is common to both segments, FALSE else.
             */
            exported bool isContiguousTo(const Line2Df& other) ;

            /**
             * This is similar to the Line2D.relativeCCW() function from Java2D.
             * @param l The Line used as reference.
             * @param p The Point to compare to the segment.
             */
            exported static char CCW(const Line2Df& l, const Point2Df& p) ;

            /**
             * Get the same Line without constraint about its position. The
             * start point of the Line is set as the origin of the plan.
             * @param l     The Line to express as an relative segment to the
             *              origin.
             * @return  A Line similar to the one give, expressed to the origin
             *          of the plan.
             */
            exported static Line2Df relative(const Line2Df& l) ;

            /**
             * Test if the Line intersects another one.
             * @param   line        The other Line to test.
             * @return  TRUE if the two Lines intersect, FALSE otherwise.
             */
            exported bool intersects(const Line2Df& line) ;

            /**
             * Compute the distance of the Line to the given Point.
             * @param   point       Point to measure its distance to the Line.
             * @return  Distance between the Line and the Point.
             */
            exported virtual Scalar distanceTo(const Point2Df& point) ;

            /**
             * Compute the distance of the Line to the given Point.
             * @param   x           Coordinate on X axis.
             * @param   y           Coordinate on Y axis.
             * @return  Distance between the Line and the Point.
             */
            exported virtual Scalar distanceTo(const Scalar x, const Scalar y) ;

            /**
             * Compute the squared distance of the Line to the given Point.
             * @param   point       Point to measure its distance to the Line.
             * @return  Distance between the Line and the Point.
             */
            exported virtual Scalar distanceSquaredTo(const Point2Df& point) ;

            /**
             * Compute the squared distance of the Line to the given Point.
             * @param   x           Coordinate on X axis.
             * @param   y           Coordinate on Y axis.
             * @return  Distance between the Line and the Point.
             */
            exported virtual Scalar distanceSquaredTo(const Scalar x, const Scalar y) ;

            /**
             * Get the Rectangle that represents the boundaries of the Line.
             * @return  The Rectangle representing the boundaries of the line.
             */
            exported const Rectangle2Df bounds() const ;

            /**
             * Get the starting point of the Line.
             * @return  The start point of the Line.
             */
            exported const Point2Df& startPoint() const ;

            /**
             * Get the ending point of the Line.
             * @return  The ending point of the Line.
             */
            exported const Point2Df& endPoint() const ;

            /**
             * Get the X coordinate of the start point.
             * @return  The X coordinate of the start point.
             */
            exported Scalar startX() const ;

            /**
             * Get the Y coordinate of the start point.
             * @return  The Y coordinate of the start point.
             */
            exported Scalar startY() const ;

            /**
             * Get the X coordinate of the end point.
             * @return  The X coordinate of the end point.
             */
            exported Scalar endX() const ;

            /**
             * Get the Y coordinate of the end point.
             * @return  The Y coordinate of the end point.
             */
            exported Scalar endY() const ;

            /**
             * Test if the Line is empty (no length).
             */
            exported bool isEmpty() const ;

            /**
             * Assignment operator to copy a Line.
             * @return  The current Line with the copied values.
             */
            exported Line2Df& operator=(const Line2Df& other) ;

            /**
             * Assignment operator to move a Line.
             * @return  The current Line with the moved values.
             */
            exported Line2Df& operator=(Line2Df&& other) = default ;

            /**
             * Test if two Lines are at the same position.
             * @param   other   An other Line to compare to the current one.
             * @return  TRUE if the Lines are at the same position, FALSE else.
             */
            exported bool operator==(const Line2Df& other) const ;

            /**
             * Test if two Lines are at two different positions.
             * @param   other   An other Line to compare to the current one.
             * @return  TRUE if the Lines are at two different positions, FALSE
             *          else.
             */
            exported bool operator!=(const Line2Df& other) const ;

            /**
             * Echo the Line coordinates on console.
             * @param   s   The stream in which print the formatted coordinates.
             * @param   l   The Line to print.
             * @return  The stream with the printed Line coordinates.
             */
            friend std::ostream& operator<<(std::ostream& s, const Line2Df& l) ;
    } ;
} ;

#endif
