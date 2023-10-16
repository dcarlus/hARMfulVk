#ifndef __MIND__GEOMETRY_RECTANGLE2DF__
#define __MIND__GEOMETRY_RECTANGLE2DF__

#include <iostream>
#include <harmful/doom/utils/Platform.hpp>
#include "harmful/mind/Math.hpp"
#include "harmful/mind/MINDTypes.hpp"
#include "harmful/mind/geometry/points/Point2Df.hpp"
#include "harmful/mind/geometry/lines/Line2Df.hpp"
#include "harmful/mind/geometry/dimensions/Dimension2Df.hpp"

namespace Mind {
    class Line2Df ;

    /// <summary>
    /// A Rectangle is an area defined by the location of its upper-left corner
    /// at (x, y) and its dimension (width, height).
    /// </summary>
    class Rectangle2Df {
        public:
            /// <summary>
            /// Bitmask that indicates that a point lies on a side of the
            /// Rectangle.
            /// </summary>
            enum PointPosition {
                PointInside    = 0,    // Point inside the rectangle
                PointOnLeft    = 1,    // Point lies on the left
                PointAbove     = 2,    // Point lies above
                PointOnRight   = 4,    // Point lies on the right
                PointBelow     = 8     // Point lies below
            } ;

        private:
            /// <summary>
            /// To know if the boundaries of the Rectangle are computed
            /// relatively to its center.
            /// </summary>
            bool m_isCentered ;

            /// <summary>
            /// Test if the size of the Rectangle has changed.
            /// </summary>
            bool m_hasChanged ;

            /// <summary>
            /// Location of the bottom-left corner of the Rectangle.
            /// </summary>
            Point2Df m_bottomLeftCorner ;

            /// <summary>
            /// Size of the rectangle.
            /// </summary>
            Dimension2Df m_size ;

            /// <summary>
            /// Location of the up right corner, cached to accelerate some
            /// computations.
            /// </summary>
            Point2Df m_upRightCorner ;

        public:
            /// <summary>
            /// Create an empty Rectangle.
            /// </summary>
            exported Rectangle2Df() ;

            /// <summary>
            /// Copy a Rectangle.
            /// </summary>
            /// <param name="copied">The Rectangle to be copied.</param>
            exported Rectangle2Df(const Rectangle2Df& copied) = default ;

            /// <summary>
            /// Move a Rectangle.
            /// </summary>
            /// <param name="moved">The Rectangle to be move.</param>
            exported Rectangle2Df(Rectangle2Df&& moved) = default ;

            /// <summary>
            /// Create a Rectangle at the given position and with the given
            /// size.
            /// </summary>
            /// <param name="location">Location of the Rectangle.</param>
            /// <param name="size">Size of the Rectangle.</param>
            /// <param name="centered">
            /// If true, the given location correspond to the center of the
            /// Rectangle. false by default, so that the bottom-left corner is
            /// set to the given location.
            /// </param>
            exported Rectangle2Df(
                const Point2Df& location,
                const Dimension2Df& size,
                const bool centered
            ) ;

            /// <summary>
            /// Create a Rectangle at the given position and with the given
            /// size.
            /// </summary>
            /// <param name="x">Coordinate on X axis.</param>
            /// <param name="y">Coordinate on Y axis.</param>
            /// <param name="w">Width.</param>
            /// <param name="h">Height.</param>
            /// <param name="centered">
            /// If true, the given location correspond to the center of the
            /// Rectangle. false by default, so that the bottom-left corner is
            /// set to the given location.
            /// </param>
            exported Rectangle2Df(
                const Scalar x,
                const Scalar y,
                const Scalar w,
                const Scalar h,
                const bool centered
            ) ;

            /// <summary>
            /// Create a Rectangle whose boundaries correspond to the given
            /// points.
            /// </summary>
            /// <param name="p1">First point of the boundaries.</param>
            /// <param name="p2">Second point of the boundaries.</param>
            exported Rectangle2Df(const Point2Df& p1, const Point2Df& p2) ;

            /// <summary>
            /// Create a Rectangle from the given boundaries.
            /// </summary>
            /// <param name="x1">Coordinate on X axis on first Point.</param>
            /// <param name="y1">Coordinate on Y axis on first Point.</param>
            /// <param name="x2">Coordinate on X axis on second Point.</param>
            /// <param name="y2">Coordinate on Y axis on second Point.</param>
            exported Rectangle2Df(
                const Scalar x1,
                const Scalar y1,
                const Scalar x2,
                const Scalar y2
            ) ;

            /// <summary>
            /// Destroy the Rectangle.
            /// </summary>
            exported virtual ~Rectangle2Df() = default ;

            /// <summary>
            /// Translate the rectangle on the X and the Y axis.
            /// </summary>
            /// <param name="x">Horizontal shift.</param>
            /// <param name="y">Vertical shift.</param>
            exported void translate(const Scalar x, const Scalar y) ;

            /**
             * 
             * @param   x           
             * @param   y           
             * @return  
             */

            /// <summary>
            /// Test if the given coordinate is inside the Line boundaries.
            /// </summary>
            /// <param name="x">Coordinate on X axis.</param>
            /// <param name="y">Coordinate on Y axis.</param>
            /// <returns>
            /// true if the point is inside the Rectangle; false otherwise.
            /// </returns>
            exported bool contains(const Scalar x, const Scalar y) ;

            /// <summary>
            /// Test if the given coordinate is inside the Line boundaries.
            /// </summary>
            /// <param name="point">Point to test.</param>
            /// <returns>
            /// true if the point is inside the Rectangle; false otherwise.
            /// </returns>
            exported bool contains(const Point2Df& point) ;

            /// <summary>
            /// Test if the given shape is entirely inside the Rectangle
            /// boundaries.
            /// </summary>
            /// <param name="x">Coordinate on X axis.</param>
            /// <param name="y">Coordinate on Y axis.</param>
            /// <param name="w">Width.</param>
            /// <param name="h">Height.</param>
            /// <returns>
            /// true if the shape is inside the Rectangle; false otherwise.
            /// </returns>
            exported bool contains(
                const Scalar x,
                const Scalar y,
                const Scalar w,
                const Scalar h
            ) ;

            /// <summary>
            /// Test if the given shape is entirely inside the Rectangle
            /// boundaries.
            /// </summary>
            /// <param name="boundaries">
            /// Boundaries of the shape to test.
            /// </param>
            /// <returns>
            /// true if the shape is inside the Rectangle; false otherwise.
            /// </returns>
            exported bool contains(Rectangle2Df& boundaries) ;

            /// <summary>
            /// Test if the Rectangle intersects another one.
            /// </summary>
            /// <param name="x">Coordinate on X axis.</param>
            /// <param name="y">Coordinate on Y axis.</param>
            /// <param name="w">Width.</param>
            /// <param name="h">Height.</param>
            /// <returns>
            /// true if the two Rectangles intersect, false otherwise.
            /// </returns>
            exported bool intersects(
                const Scalar x,
                const Scalar y,
                const Scalar w,
                const Scalar h
            ) ;

            /// <summary>
            /// Test if the Rectangle intersects a Line.
            /// </summary>
            /// <param name="line">The Line to test.</param>
            /// <returns>
            /// true if the Rectangle and Line intersect, false otherwise.
            /// </returns>
            exported bool intersects(const Line2Df& line) ;

            /// <summary>
            /// Test if the Rectangle intersects a shape throught its
            /// boundaries.
            /// </summary>
            /// <param name="boundaries">Boundaries to test.</param>
            /// <returns>
            /// true if the two shapes intersect, false otherwise.
            /// </returns>
            exported bool intersects(const Rectangle2Df& boundaries) ;

            /// <summary>
            /// Determine where the given Point lies in respect of the
            /// Rectangle boundaries.
            /// </summary>
            /// <param name="x">X coordinate of the Point.</param>
            /// <param name="y">Y coordinate of the Point.</param>
            /// <returns>
            /// Bitmask of the positions where the Point is relatively to the
            /// Rectangle boundaries.
            /// </returns>
            exported int8_t position(const Scalar x, const Scalar y) ;

            /// <summary>
            /// Determine where the given Point lies in respect of the
            /// Rectangle boundaries.
            /// </summary>
            /// <param name="p">The Point to test.</param>
            /// <returns>
            /// Bitmask of the positions where the Point is relatively to the
            /// Rectangle boundaries.
            /// </returns>
            exported int8_t position(const Point2Df& p) ;

            /// <summary>
            /// Get the X coordinate of the upper-left corner.
            /// </summary>
            /// <returns>Up left corner coordinate X.</returns>
            exported Scalar upLeftCornerX() ;

            /// <summary>
            /// Get the Y coordinate of the upper-left corner.
            /// </summary>
            /// <returns>Up left corner coordinate Y.</returns>
            exported Scalar upLeftCornerY() ;

            /// <summary>
            /// Get the X coordinate of the upper-right corner.
            /// </summary>
            /// <returns>Up right corner coordinate X.</returns>
            exported Scalar upRightCornerX() ;

            /// <summary>
            /// Get the Y coordinate of the upper-right corner.
            /// </summary>
            /// <returns>Up right corner coordinate Y.</returns>
            exported Scalar upRightCornerY() ;

            /// <summary>
            /// Get the X coordinate of the bottom-left corner.
            /// </summary>
            /// <returns>Bottom left corner coordinate X.</returns>
            exported Scalar bottomLeftCornerX() const ;

            /// <summary>
            /// Get the Y coordinate of the bottom-left corner.
            /// </summary>
            /// <returns>Bottom left corner coordinate Y.</returns>
            exported Scalar bottomLeftCornerY() const ;

            /// <summary>
            /// Get the X coordinate of the bottom-right corner.
            /// </summary>
            /// <returns>Bottom right corner coordinate X.</returns>
            exported Scalar bottomRightCornerX() ;

            /// <summary>
            /// Get the Y coordinate of the bottom-right corner.
            /// </summary>
            /// <returns>Bottom right corner coordinate Y.</returns>
            exported Scalar bottomRightCornerY() ;

            /// <summary>
            /// Get the dimension of the Rectangle.
            /// </summary>
            /// <returns>Dimension of the Rectangle2D.</returns>
            exported const Dimension2Df& size() const ;

            /// <summary>
            /// Get the width of the Rectangle.
            /// </summary>
            /// <returns>Width of the Rectangle2D.</returns>
            exported Scalar width() const ;

            /// <summary>
            /// Get the height of the Rectangle.
            /// </summary>
            /// <returns>Height of the Rectangle2D.</returns>
            exported Scalar height() const ;

            /// <summary>
            /// Test if the Rectangle is empty.
            /// </summary>
            /// <returns>
            /// true if the Rectangle is empty (no width or height), false
            /// otherwise.
            /// </returns>
            exported bool isEmpty() const ;

            /// <summary>
            /// Set the X location of the upper-left corner.
            /// </summary>
            /// <param name="x">
            /// New X location of the upper-left corner.
            /// </param>
            exported void setX(const Scalar x) ;

            /// <summary>
            /// Set the Y location of the upper-left corner.
            /// </summary>
            /// <param name="y">
            /// New Y location of the upper-left corner.
            /// </param>
            exported void setY(const Scalar y) ;

            /// <summary>
            /// Set the location of the upper-left corner.
            /// </summary>
            /// <param name="x">
            /// New X location of the upper-left corner.
            /// </param>
            /// <param name="y">
            /// New Y location of the upper-left corner.
            /// </param>
            exported void setAt(const Scalar x, const Scalar y) ;

            /// <summary>
            /// Set the width of the Rectangle.
            /// </summary>
            /// <param name="w">New width of the Rectangle.</param>
            exported void setWidth(const Scalar w) ;

            /// <summary>
            /// Set the height of the Rectangle.
            /// </summary>
            /// <param name="h">New height of the Rectangle.</param>
            exported void setHeight(const Scalar h) ;

        protected:
            /// <summary>
            /// Compute the bottom right corner that is cached.
            /// </summary>
            exported void computeMaxPoint() ;

        public:
            /// <summary>
            /// Assignment operator to copy a Rectangle.
            /// </summary>
            /// <param name="other">Rectangle to copy.</param>
            /// <returns>
            /// The current Rectangle with the copied values.
            /// </returns>
            exported Rectangle2Df& operator=(const Rectangle2Df& other) ;

            /// <summary>
            /// Assignment operator to move a Rectangle.
            /// </summary>
            /// <param name="other">Rectangle to move.</param>
            /// <returns>The current Rectangle with the moved values.</returns>
            exported Rectangle2Df& operator=(Rectangle2Df&& other) = default ;

            /// <summary>
            /// Add a Point and affect the result.
            /// </summary>
            /// <param name="other">The Point to add.</param>
            /// <returns>
            /// The smallest Rectangle including both the original Rectangle
            /// and the Point.
            /// </returns>
            exported Rectangle2Df& operator+=(Point2Df& other) ;

            /// <summary>
            /// Merge two Rectangles and affect the result.
            /// </summary>
            /// <param name="other">The Rectangle to add.</param>
            /// <returns>
            /// The smallest Rectangle including the two Rectangles.
            /// </returns>
            exported Rectangle2Df& operator+=(Rectangle2Df& other) ;

            /// <summary>
            /// Test if two Rectangles are at the same position.
            /// </summary>
            /// <param name="other">
            /// An other Rectangle to compare to the current one.
            /// </param>
            /// <returns>
            /// true if the Rectangles are at the same position, false else.
            /// </returns>
            exported bool operator==(const Rectangle2Df& other) const ;

            /// <summary>
            /// Test if two Rectangles are at two different positions.
            /// </summary>
            /// <param name="other">
            /// An other Rectangle to compare to the current one.
            /// </param>
            /// <returns>
            /// true if the Rectangles are at two different positions, false
            /// else.
            /// </returns>
            exported bool operator!=(const Rectangle2Df& other) const ;

            /// <summary>
            /// Add a Point to the Rectangle.
            /// </summary>
            /// <param name="r">Rectangle to include a new Point.</param>
            /// <param name="p">Point to insert into the Rectangle.</param>
            /// <returns>
            /// The smallest Rectangle including both the original Rectangle
            /// and the added Point. If p was inside the previous Rectangle,
            /// the original Rectangle is returned.
            /// </returns>
            exported friend Rectangle2Df operator+(Rectangle2Df& r, Point2Df& p) ;

            /// <summary>
            /// Merge two Rectangles
            /// </summary>
            /// <param name="r1">First rectangle.</param>
            /// <param name="r2">Second Rectangle.</param>
            /// <returns>
            /// The smallest Rectangle including the two Rectangles.
            /// </returns>
            exported friend Rectangle2Df operator+(Rectangle2Df& r1, Rectangle2Df& r2) ;

            /// <summary>
            /// Echo the Rectangle2D coordinates on console.
            /// </summary>
            /// <param name="s">
            /// The stream in which print the formatted coordinates.
            /// </param>
            /// <param name="r">The Rectangle2D to print.</param>
            /// <returns>
            /// The stream with the printed Line coordinates.
            /// </returns>
            exported friend std::ostream& operator<<(std::ostream& s, const Rectangle2Df& r) ;
    } ;
} ;

#endif
