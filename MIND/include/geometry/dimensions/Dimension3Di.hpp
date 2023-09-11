#ifndef __MIND__GEOMETRY_DIMENSION3DI__
#define __MIND__GEOMETRY_DIMENSION3DI__

#include <iostream>

#include "MINDTypes.hpp"
#include "geometry/dimensions/Dimension2Di.hpp"

namespace Mind {
    /**
     * A Dimension is used to get the size of an element, and so get the area of
     * the element as a rectangle bounding shape.
     */
    class Dimension3Di final {
        private:
            /** Width of the Dimension2Df. */
            uint32_t m_width ;

            /** Height of the Dimension2Df. */
            uint32_t m_height ;

            /** Depth of the Dimension2Df. */
            uint32_t m_depth ;


        public:
            /** Create a Dimension of zero by zero. */
            exported Dimension3Di() ;

            /**
             * Create a Dimension with the given sizes.
             * @param   width   Width to set the size of the element.
             * @param   height  Height to set the size of the element.
             * @param   depth   Depth to set the size of the element.
             */
            exported Dimension3Di(
                const uint32_t width,
                const uint32_t height,
                const uint32_t depth
            ) ;


            /** Set the Dimension as absolute values. */
            exported void absolute() ;

            /**
             * Get the width of the dimension.
             * @return  The width.
             */
            exported uint32_t width() const ;

            /**
             * Get the height of the dimension.
             * @return  The height.
             */
            exported uint32_t height() const ;

            /**
             * Get the depth of the dimension.
             * @return  The depth.
             */
            exported uint32_t depth() const ;

            /**
             * Set the width of the dimension.
             * @param   width   Width of the dimension.
             */
            exported void setWidth(const uint32_t width) ;

            /**
             * Set the height of the dimension.
             * @param   height  Height of the dimension.
             */
            exported void setHeight(const uint32_t height) ;

            /**
             * Set the depth of the dimension.
             * @param   depth   Depth of the dimension.
             */
            exported void setDepth(const uint32_t depth) ;

            /**
             * Set the depth of the dimension.
             * @param   width   Width of the dimension.
             * @param   height  Height of the dimension.
             * @param   depth   Depth of the dimension.
             */
            exported void set(
                const uint32_t width,
                const uint32_t height,
                const uint32_t depth
            ) ;

            /** Conversion from Dimension3D to Dimension2D. */
            exported explicit operator Dimension2Di() ;

            /**
             * Add a Dimension and affect the result.
             * @param   other   The other Dimension to add.
             * @return  The sum of the two Dimensions.
             */
            exported Dimension3Di& operator+=(Dimension3Di& other) ;

            /**
             * Substract a Dimension and affect the result.
             * @param   other   The other Dimension to substract.
             * @return  The substract of the two Dimensions.
             */
            exported Dimension3Di& operator-=(Dimension3Di& other) ;

            /**
             * Multiply a Dimension by a uint32_t value and affect the result.
             * @param   coeff   The coeff to multiply the Dimension coordinates by.
             * @return  The result of the multiplication.
             */
            exported Dimension3Di& operator*=(const uint32_t coeff) ;

            /**
             * Divide a Dimension by a uint32_t value and affect the result.
             * @param   coeff   The coeff to divide the Dimension coordinates by.
             * @return  The result of the division.
             */
            exported Dimension3Di& operator/=(const uint32_t coeff) ;

            /**
             * Test if two Dimension have the same size.
             * @param   other   An other Dimension to compare to the current one.
             * @return  TRUE if the Dimension have the same size, FALSE else.
             */
            exported bool operator==(const Dimension3Di& other) const ;

            /**
             * Test if two Dimension have not the same size.
             * @param   other   An other Dimension to compare to the current one.
             * @return  TRUE if the Dimension have two different size, FALSE else.
             */
            exported bool operator!=(const Dimension3Di& other) const ;

            /**
             * Add a Dimension to another one.
             * @param   a   First Dimension.
             * @param   b   Second Dimension.
             * @return  Point at (a.w + b.w, a.h + b.h).
             */
            exported friend Dimension3Di operator+(const Dimension3Di& a, const Dimension3Di& b) ;

            /**
             * Substract a Dimension to another one.
             * @param   a   First Dimension.
             * @param   b   Second Dimension.
             * @return  Point at (a.w - b.w, a.h - b.h).
             */
            exported friend Dimension3Di operator-(const Dimension3Di& a, const Dimension3Di& b) ;

            /**
             * Multiply a Dimension by a uint32_t value (scale).
             * @param   p       Dimension to be multiplied.
             * @param   coeff   Factor to scale the coordinates.
             * @return  Point at (d.w * coeff, d.h * coeff).
             */
            exported friend Dimension3Di operator*(const Dimension3Di& d, const uint32_t coeff) ;

            /**
             * Divide a Dimension by a uint32_t value (scale).
             * @param   a       Dimension to be divided.
             * @param   coeff   Factor to scale the coordinates.
             * @return  Point at (d.w / coeff, d.h / coeff).
             */
            exported friend Dimension3Di operator/(const Dimension3Di& d, const uint32_t coeff) ;

            /**
             * Echo the Dimension size on console.
             * @param   s   The stream in which print the formatted coordinates.
             * @param   p   The Dimension to print.
             * @return  The stream with the printed Dimension size.
             */
            exported friend std::ostream& operator<<(std::ostream& s, const Dimension3Di& p) ;
    } ;
} ;

#endif
