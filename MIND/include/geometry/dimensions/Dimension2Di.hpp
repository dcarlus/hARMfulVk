#ifndef __MIND__GEOMETRY_DIMENSION2DI__
#define __MIND__GEOMETRY_DIMENSION2DI__

#include <cstdint>
#include <iostream>
#include "utils/Platform.hpp"

namespace Mind {

    /**
     * A Dimension is used to get the size of an element, and so get the area of
     * the element as a rectangle bounding shape.
     */
    class Dimension2Di final {
        private:
            /** Width of the Dimension2Di. */
            uint32_t m_width ;

            /** Height of the Dimension2Di. */
            uint32_t m_height ;


        public:
            /** Create a Dimension of zero by zero. */
            exported Dimension2Di() ;

            /**
             * Create a Dimension with the given sizes.
             * @param   width   Width to set the size of the element.
             * @param   height  Height to set the size of the element.
             */
            exported Dimension2Di(const uint32_t width, const uint32_t height) ;

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
             * Set the height of the dimension.
             * @param   width   Width of the dimension.
             * @param   height  Height of the dimension.
             */
            exported void set(const uint32_t width, const uint32_t height) ;


            /**
             * Add a Dimension and affect the result.
             * @param   other   The other Dimension to add.
             * @return  The sum of the two Dimension.
             */
            exported Dimension2Di& operator+=(Dimension2Di& other) ;

            /**
             * Substract a Dimension and affect the result.
             * @param   other   The other Dimension to substract.
             * @return  The substract of the two Dimension.
             */
            exported Dimension2Di& operator-=(Dimension2Di& other) ;

            /**
             * Multiply a Dimension by a scalar value and affect the result.
             * @param    coeff   The coeff to multiply the Dimension coordinates
             *                   by.
             * @return   The result of the multiplication.
             */
            exported Dimension2Di& operator*=(const uint32_t coeff) ;

            /**
             * Divide a Dimension by a scalar value and affect the result.
             * @param   coeff   The coeff to divide the Dimension coordinates by.
             * @return  The result of the division.
             */
            exported Dimension2Di& operator/=(const uint32_t coeff) ;


            /**
             * Test if two Dimension have the same size.
             * @param   other   An other Dimension to compare to the current one.
             * @return  TRUE if the Dimension have the same size, FALSE else.
             */
            exported bool operator==(const Dimension2Di& other) const ;

            /**
             * Test if two Dimension have not the same size.
             * @param   other   An other Dimension to compare to the current one.
             * @return  TRUE if the Dimension have two different size, FALSE else.
             */
            exported bool operator!=(const Dimension2Di& other) const ;

            /**
             * Add a Dimension to another one.
             * @param   a   First Dimension.
             * @param   b   Second Dimension.
             * @return  Dimension of (a.w + b.w, a.h + b.h).
             */
            exported friend Dimension2Di operator+(const Dimension2Di& a, const Dimension2Di& b) ;


            /**
             * Substract a Dimension to another one.
             * @param   a   First Dimension.
             * @param   b   Second Dimension.
             * @return  Dimension of (a.w - b.w, a.h - b.h).
             */
            exported friend Dimension2Di operator-(const Dimension2Di& a, const Dimension2Di& b) ;


            /**
             * Multiply a Dimension coordinates by a scalar value (scale).
             * @param   d       Dimension to be multiplied.
             * @param   coeff   Factor to scale the coordinates.
             * @return  Dimension at (d.w * coeff, d.w * coeff).
             */
            exported friend Dimension2Di operator*(const Dimension2Di& d, const uint32_t coeff) ;


            /**
             * Divide a Dimension coordinates by a scalar value (scale).
             * @param   d       Dimension to be divided.
             * @param   coeff   Factor to scale the coordinates.
             * @return  Dimension of (d.w / coeff, d.h / coeff).
             */
            exported friend Dimension2Di operator/(const Dimension2Di& d, const uint32_t coeff) ;


            /**
             * Echo the Dimension size on console.
             * @param   s   The stream in which print the formatted coordinates.
             * @param   d   The Dimension to print.
             * @return  The stream with the printed Dimension size.
             */
            exported friend std::ostream& operator<<(std::ostream& s, const Dimension2Di& d) ;
    } ;
} ;

#endif
