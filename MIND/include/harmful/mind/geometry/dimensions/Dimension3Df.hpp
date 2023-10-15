#ifndef __MIND__GEOMETRY_DIMENSION3DF__
#define __MIND__GEOMETRY_DIMENSION3DF__

#include <iostream>
#include <harmful/doom/utils/Platform.hpp>
#include "harmful/mind/MINDTypes.hpp"
#include "harmful/mind/geometry/points/Point3Df.hpp"
#include "harmful/mind/geometry/dimensions/Dimension2Df.hpp"

namespace Mind {
    class Dimension2Df ;
    class Point3Df ;

    /**
     * A Dimension is used to get the size of an element, and so get the area of
     * the element as a rectangle bounding shape.
     */
    class Dimension3Df final {
        private:
            /** Width of the Dimension2Df. */
            Scalar m_width ;

            /** Height of the Dimension2Df. */
            Scalar m_height ;

            /** Depth of the Dimension2Df. */
            Scalar m_depth ;


        public:
            /** Create a Dimension of zero by zero. */
            exported Dimension3Df() ;

            /**
             * Create a Dimension with the given sizes.
             * @param   width   Width to set the size of the element.
             * @param   height  Height to set the size of the element.
             * @param   depth   Depth to set the size of the element.
             */
            exported Dimension3Df(
                const Scalar width,
                const Scalar height,
                const Scalar depth
            ) ;


            /** Set the Dimension as absolute values. */
            exported void absolute() ;

            /**
             * Get the width of the dimension.
             * @return  The width.
             */
            exported Scalar width() const ;

            /**
             * Get the height of the dimension.
             * @return  The height.
             */
            exported Scalar height() const ;

            /**
             * Get the depth of the dimension.
             * @return  The depth.
             */
            exported Scalar depth() const ;

            /**
             * Set the width of the dimension.
             * @param   width   Width of the dimension.
             */
            exported void setWidth(const Scalar width) ;

            /**
             * Set the height of the dimension.
             * @param   height  Height of the dimension.
             */
            exported void setHeight(const Scalar height) ;

            /**
             * Set the depth of the dimension.
             * @param   depth   Depth of the dimension.
             */
            exported void setDepth(const Scalar depth) ;

            /**
             * Set the depth of the dimension.
             * @param   width   Width of the dimension.
             * @param   height  Height of the dimension.
             * @param   depth   Depth of the dimension.
             */
            exported void set(
                const Scalar width,
                const Scalar height,
                const Scalar depth
            ) ;

            /** Conversion from Dimension3D to Point3D. */
            exported explicit operator Point3Df() ;

            /** Conversion from Dimension3D to Dimension2D. */
            exported explicit operator Dimension2Df() ;

            /**
             * Add a Dimension and affect the result.
             * @param   other   The other Dimension to add.
             * @return  The sum of the two Dimensions.
             */
            exported Dimension3Df& operator+=(Dimension3Df& other) ;

            /**
             * Substract a Dimension and affect the result.
             * @param   other   The other Dimension to substract.
             * @return  The substract of the two Dimensions.
             */
            exported Dimension3Df& operator-=(Dimension3Df& other) ;

            /**
             * Multiply a Dimension by a scalar value and affect the result.
             * @param   coeff   The coeff to multiply the Dimension coordinates by.
             * @return  The result of the multiplication.
             */
            exported Dimension3Df& operator*=(const Scalar coeff) ;

            /**
             * Divide a Dimension by a scalar value and affect the result.
             * @param   coeff   The coeff to divide the Dimension coordinates by.
             * @return  The result of the division.
             */
            exported Dimension3Df& operator/=(const Scalar coeff) ;

            /**
             * Test if two Dimension have the same size.
             * @param   other   An other Dimension to compare to the current one.
             * @return  TRUE if the Dimension have the same size, FALSE else.
             */
            exported bool operator==(const Dimension3Df& other) const ;

            /**
             * Test if two Dimension have not the same size.
             * @param   other   An other Dimension to compare to the current one.
             * @return  TRUE if the Dimension have two different size, FALSE else.
             */
            exported bool operator!=(const Dimension3Df& other) const ;

            /**
             * Add a Dimension to another one.
             * @param   a   First Dimension.
             * @param   b   Second Dimension.
             * @return  Point at (a.w + b.w, a.h + b.h).
             */
            exported friend Dimension3Df operator+(const Dimension3Df& a, const Dimension3Df& b) ;

            /**
             * Substract a Dimension to another one.
             * @param   a   First Dimension.
             * @param   b   Second Dimension.
             * @return  Point at (a.w - b.w, a.h - b.h).
             */
            exported friend Dimension3Df operator-(const Dimension3Df& a, const Dimension3Df& b) ;

            /**
             * Multiply a Dimension by a scalar value (scale).
             * @param   p       Dimension to be multiplied.
             * @param   coeff   Factor to scale the coordinates.
             * @return  Point at (d.w * coeff, d.h * coeff).
             */
            exported friend Dimension3Df operator*(const Dimension3Df& d, const Scalar coeff) ;

            /**
             * Divide a Dimension by a scalar value (scale).
             * @param   a       Dimension to be divided.
             * @param   coeff   Factor to scale the coordinates.
             * @return  Point at (d.w / coeff, d.h / coeff).
             */
            exported friend Dimension3Df operator/(const Dimension3Df& d, const Scalar coeff) ;

            /**
             * Echo the Dimension size on console.
             * @param   s   The stream in which print the formatted coordinates.
             * @param   p   The Dimension to print.
             * @return  The stream with the printed Dimension size.
             */
            exported friend std::ostream& operator<<(std::ostream& s, const Dimension3Df& p) ;
    } ;
} ;

#endif
