#ifndef __MIND__GEOMETRY_RECTANGLE2DF__
#define __MIND__GEOMETRY_RECTANGLE2DF__

#include <iostream>

#include "Math.hpp"
#include "MINDTypes.hpp"
#include "geometry/points/Point2Df.hpp"
#include "geometry/lines/Line2Df.hpp"
#include "geometry/dimensions/Dimension2Df.hpp"

namespace Mind {
    class Line2Df ;

    /**
     * A Rectangle is an area defined by the location of its upper-left corner
     * at (x, y) and its dimension (width, height).
     */
    class Rectangle2Df {
        public:
            /**
             * Bitmask that indicates that a point lies on a side of the
             * Rectangle.
             */
            enum PointPosition {
                PointInside    = 0,    // Point inside the rectangle
                PointOnLeft    = 1,    // Point lies on the left
                PointAbove     = 2,    // Point lies above
                PointOnRight   = 4,    // Point lies on the right
                PointBelow     = 8     // Point lies below
            } ;

        private:
            /**
             * To know if the boundaries of the Rectangle are computed
             * relatively to its center.
             */
            bool m_isCentered ;

            /** Test if the size of the Rectangle has changed. */
            bool m_hasChanged ;

            /** Location of the bottom-left corner of the Rectangle. */
            Point2Df m_bottomLeftCorner ;

            /** Size of the rectangle. */
            Dimension2Df m_size ;

            /**
             * Location of the up right corner, cached to accelerate some
             * computations.
             */
            Point2Df m_upRightCorner ;

        public:
            /** Create an empty Rectangle. */
            exported Rectangle2Df() ;

            /**
             * Copy a Rectangle.
             * @param   copied      The Rectangle to be copied.
             */
            exported Rectangle2Df(const Rectangle2Df& copied) = default ;

            /**
             * Move a Rectangle.
             * @param   moved      The Rectangle to be move.
             */
            exported Rectangle2Df(Rectangle2Df&& moved) = default ;

            /**
             * Create a Rectangle at the given position and with the given size.
             * @param   location    Location of the Rectangle.
             * @param   size        Size of the Rectangle.
             * @param   centered    If TRUE, the given location correspond to
             *                      the center of the Rectangle.
             *                      FALSE by default, so that the bottom-left
             *                      corner is set to the given location.
             */
            exported Rectangle2Df(
                const Point2Df& location,
                const Dimension2Df& size,
                const bool centered
            ) ;

            /**
             * Create a Rectangle at the given position and with the given size.
             * @param   x           Coordinate on X axis.
             * @param   y           Coordinate on Y axis.
             * @param   w           Width.
             * @param   h           Height.
             * @param   centered    If TRUE, the given location correspond to
             *                      the center of the Rectangle.
             *                      If FALSE, the bottom-left corner is set to
             *                      the given location.
             */
            exported Rectangle2Df(
                const Scalar x,
                const Scalar y,
                const Scalar w,
                const Scalar h,
                const bool centered
            ) ;

            /**
             * Create a Rectangle whose boundaries correspond to the
             *          given points.
             * @param   p1          First point of the boundaries.
             * @param   p2          Second point of the boundaries.
             */
            exported Rectangle2Df(const Point2Df& p1, const Point2Df& p2) ;

            /**
             * Create a Rectangle from the given boundaries.
             * @param   x1          Coordinate on X axis on first Point.
             * @param   y1          Coordinate on Y axis on first Point
             * @param   x2          Coordinate on X axis on second Point
             * @param   y2          Coordinate on Y axis on second Point
             */
            exported Rectangle2Df(
                const Scalar x1,
                const Scalar y1,
                const Scalar x2,
                const Scalar y2
            ) ;

            /** Destroy the Rectangle. */
            exported virtual ~Rectangle2Df() = default ;

            /**
             * Translate the rectangle on the X and the Y axis.
             * @param   x    Horizontal shift.
             * @param   y    Vertical shift.
             */
            exported void translate(const Scalar x, const Scalar y) ;

            /**
             * Test if the given coordinate is inside the Line boundaries.
             * @param   x           oordinate on X axis.
             * @param   y           Coordinate on Y axis.
             * @return  FALSE because a line has no area.
             */
            exported bool contains(const Scalar x, const Scalar y) ;

            /**
             * Test if the given coordinate is inside the Rectangle
             *          boundaries.
             * @param   point       Point to test.
             * @return  FALSE because a line has no area.
             */
            exported bool contains(const Point2Df& point) ;

            /**
             * Test if the given shape is entirely inside the Rectangle
             *          boundaries.
             * @param   x           Coordinate on X axis.
             * @param   y           Coordinate on Y axis.
             * @param   w           Width.
             * @param   h           Height.
             * @return  FALSE because a line has no area.
             */
            exported bool contains(
                const Scalar x,
                const Scalar y,
                const Scalar w,
                const Scalar h
            ) ;

            /**
             * Test if the given shape is entirely inside the Rectangle
             *          boundaries.
             * @param   boundaries  Boundaries of the shape to test.
             * @return  FALSE because a line has no area.
             */
            exported bool contains(Rectangle2Df& boundaries) ;

            /**
             * Test if the Rectangle intersects another one.
             * @param   x           Coordinate on X axis.
             * @param   y           Coordinate on Y axis.
             * @param   w           Width.
             * @param   h           Height.
             * @return  TRUE if the two Rectangles intersect, FALSE otherwise.
             */
            exported bool intersects(
                const Scalar x,
                const Scalar y,
                const Scalar w,
                const Scalar h
            ) ;

            /**
             * Test if the Rectangle intersects a Line.
             * @param    line        The other Line to test.
             * @return   TRUE if the Rectangle and Line intersect, FALSE
             *           otherwise.
             */
            exported bool intersects(const Line2Df& line) ;

            /**
             * Test if the Rectangle intersects a shape throught its
             *           boundaries.
             * @param    boundaries  Boundaries to test.
             * @return   TRUE if the two shapes intersect, FALSE otherwise.
             */
            exported bool intersects(const Rectangle2Df& boundaries) ;

            /**
             * Determine where the given Point lies in respect of the
             *          Rectangle boundaries.
             * @param   x       X coordinate of the Point.
             * @param   y       Y coordinate of the Point.
             * @return  Bitmask of the positions where the Point is relatively
             *          to the Rectangle boundaries.
             */
            exported char position(const Scalar x, const Scalar y) ;

            /**
             * Determine where the given Point lies in respect of the
             *          Rectangle boundaries.
             * @param   p       The Point to test.
             * @return  Bitmask of the positions where the Point is relatively
             *          to the Rectangle boundaries.
             */
            exported char position(const Point2Df& p) ;

            /**
              * Get the X coordinate of the upper-left corner.
              * @return  Up left corner coordinate X.
              */
            exported Scalar upLeftCornerX() ;

            /**
              * Get the Y coordinate of the upper-left corner.
              * @return  Up left corner coordinate Y.
              */
            exported Scalar upLeftCornerY() ;

            /**
              * Get the X coordinate of the upper-right corner.
              * @return  Up right corner coordinate X.
              */
            exported Scalar upRightCornerX() ;

            /**
              * Get the Y coordinate of the upper-right corner.
              * @return  Up right corner coordinate Y.
              */
            exported Scalar upRightCornerY() ;

            /**
              * Get the X coordinate of the bottom-left corner.
              * @return  Bottom left corner coordinate X.
              */
            exported Scalar bottomLeftCornerX() const ;

            /**
              * Get the Y coordinate of the bottom-left corner.
              * @return  Bottom left corner coordinate Y.
              */
            exported Scalar bottomLeftCornerY() const ;

            /**
              * Get the X coordinate of the bottom-right corner.
              * @return  Bottom right corner coordinate X.
              */
            exported Scalar bottomRightCornerX() ;

            /**
              * Get the Y coordinate of the bottom-right corner.
              * @return  Bottom right corner coordinate Y.
              */
            exported Scalar bottomRightCornerY() ;

            /**
              * Get the dimension of the Rectangle.
              * @return  Dimension of the Rectangle2D.
              */
            exported const Dimension2Df& size() const ;

            /**
              * Get the width of the Rectangle.
              * @return  Width of the Rectangle2D.
              */
            exported Scalar width() const ;

            /**
              * Get the height of the Rectangle.
              * @return  Height of the Rectangle2D.
              */
            exported Scalar height() const ;

            /**
              * Test if the Rectangle is empty.
              * @return  TRUE if the Rectangle is empty (no width or height),
              *          FALSE otherwise.
              */
            exported bool isEmpty() const ;

            /** Set the X location of the upper-left corner. */
            exported void setX(const Scalar x) ;

            /** Set the Y location of the upper-left corner. */
            exported void setY(const Scalar y) ;

            /** Set the location of the upper-left corner. */
            exported void setAt(const Scalar x, const Scalar y) ;

            /** Set the width of the Rectangle. */
            exported void setWidth(const Scalar w) ;

            /** Set the height of the Rectangle. */
            exported void setHeight(const Scalar h) ;

        protected:
            /** Compute the bottom right corner that is cached. */
            exported void computeMaxPoint() ;

        public:
            /**
             * Assignment operator to copy a Rectangle.
             * @return  The current Rectangle with the copied values.
             */
            exported Rectangle2Df& operator=(const Rectangle2Df& other) ;

            /**
             * Assignment operator to move a Rectangle.
             * @return  The current Rectangle with the moved values.
             */
            exported Rectangle2Df& operator=(Rectangle2Df&& other) = default ;

            /**
             * Add a Point and affect the result.
             * @param   other   The Point to add.
             * @return  The smallest Rectangle including both the original
             *          Rectangle and the Point.
             */
            exported Rectangle2Df& operator+=(Point2Df& other) ;

            /**
             * Merge two Rectangles and affect the result.
             * @param   other   The Rectangle to add.
             * @return  The smallest Rectangle including the two Rectangles.
             */
            exported Rectangle2Df& operator+=(Rectangle2Df& other) ;

            /**
             * Test if two Rectangles are at the same position.
             * @param   other   An other Rectangle to compare to the current one.
             * @return  TRUE if the Rectangles are at the same position, FALSE
             *          else.
             */
            exported bool operator==(const Rectangle2Df& other) const ;

            /**
             * Test if two Rectangles are at two different positions.
             * @param   other   An other Rectangle to compare to the current one.
             * @return  TRUE if the Rectangles are at two different positions,
             *          FALSE else.
             */
            exported bool operator!=(const Rectangle2Df& other) const ;


            /**
             * Add a Point to the Rectangle.
             * @param   r   Rectangle to include a new Point.
             * @param   p   Point to insert into the Rectangle.
             * @return  The smallest Rectangle including both the original
             *          Rectangle and the added Point. If p was inside the
             *          previous Rectangle, the original Rectangle is returned.
             */
            exported friend Rectangle2Df operator+(Rectangle2Df& r, Point2Df& p) ;

            /**
             * Merge two Rectangles
             * @param   r1  First rectangle.
             * @param   r2  Second Rectangle.
             * @return  The smallest Rectangle including the two Rectangles.
             */
            exported friend Rectangle2Df operator+(Rectangle2Df& r1, Rectangle2Df& r2) ;

            /**
             * Echo the Rectangle2D coordinates on console.
             * @param   s   The stream in which print the formatted coordinates.
             * @param   r   The Rectangle2D to print.
             * @return  The stream with the printed Line coordinates.
             */
            exported friend std::ostream& operator<<(std::ostream& s, const Rectangle2Df& r) ;
    } ;
} ;

#endif
