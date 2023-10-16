#ifndef __MIND__GEOMETRY_DIMENSION3DI__
#define __MIND__GEOMETRY_DIMENSION3DI__

#include <iostream>
#include <harmful/doom/utils/Platform.hpp>
#include "harmful/mind/MINDTypes.hpp"
#include "harmful/mind/geometry/dimensions/Dimension2Di.hpp"

namespace Mind {
    /// <summary>
    /// A Dimension is used to get the size of an element, and so get the area
    /// of the element as a rectangle bounding shape.
    /// </summary>
    class Dimension3Di final {
        private:
            /// <summary>
            /// Width of the Dimension3Di.
            /// </summary>
            uint32_t m_width = 0u ;

            /// <summary>
            /// Height of the Dimension3Di.
            /// </summary>
            uint32_t m_height = 0u ;

            /// <summary>
            /// Depth of the Dimension3Di
            /// </summary>
            uint32_t m_depth = 0u ;

        public:
            // Default constructors/assignemnts.
            exported Dimension3Di() = default;
            exported Dimension3Di(const Dimension3Di& copied) = default;
            exported Dimension3Di(Dimension3Di&& moved) = default;
            exported Dimension3Di& operator=(const Dimension3Di& copied) = default;
            exported Dimension3Di& operator=(Dimension3Di&& moved) = default;
            exported ~Dimension3Di() noexcept = default;

            /// <summary>
            /// Create a Dimension with the given sizes.
            /// </summary>
            /// <param name="width">Width to set the size of the element.</param>
            /// <param name="height">Height to set the size of the element.</param>
            /// <param name="depth">Depth to set the size of the element.</param>
            exported Dimension3Di(
                const uint32_t width,
                const uint32_t height,
                const uint32_t depth
            ) ;

            /// <summary>
            /// Get the width of the dimension.
            /// </summary>
            /// <returns>The width.</returns>
            exported uint32_t width() const ;

            /// <summary>
            /// Get the height of the dimension.
            /// </summary>
            /// <returns>The height.</returns>
            exported uint32_t height() const ;

            /// <summary>
            /// Get the depth of the dimension.
            /// </summary>
            /// <returns>The depth.</returns>
            exported uint32_t depth() const ;

            /// <summary>
            /// Set the width of the dimension.
            /// </summary>
            /// <param name="width">Width of the dimension.</param>
            exported void setWidth(const uint32_t width) ;

            /// <summary>
            /// Set the height of the dimension.
            /// </summary>
            /// <param name="height">Height of the dimension.</param>
            exported void setHeight(const uint32_t height) ;

            /// <summary>
            /// Set the depth of the dimension.
            /// </summary>
            /// <param name="depth">Depth of the dimension.</param>
            exported void setDepth(const uint32_t depth) ;

            /// <summary>
            /// Set the width, height and depth of the dimension.
            /// </summary>
            /// <param name="width">Width of the dimension.</param>
            /// <param name="height">Height of the dimension.</param>
            /// <param name="depth">Depth of the dimension.</param>
            exported void set(
                const uint32_t width,
                const uint32_t height,
                const uint32_t depth
            ) ;

            /// <summary>
            /// Conversion from Dimension3D to Dimension2D.
            /// </summary>
            exported explicit operator Dimension2Di() ;

            /// <summary>
            /// Add a Dimension and affect the result.
            /// </summary>
            /// <param name="other">The other Dimension to add.</param>
            /// <returns>The sum of the two Dimensions.</returns>
            exported Dimension3Di& operator+=(Dimension3Di& other) ;

            /// <summary>
            /// Substract a Dimension and affect the result.
            /// </summary>
            /// <param name="other">The other Dimension to substract.</param>
            /// <returns>The substract of the two Dimensions.</returns>
            exported Dimension3Di& operator-=(Dimension3Di& other) ;

            /// <summary>
            /// Multiply a Dimension by a uint32_t value and affect the result.
            /// </summary>
            /// <param name="coeff">
            /// The coeff to multiply the Dimension coordinates by.
            /// </param>
            /// <returns>The result of the multiplication.</returns>
            exported Dimension3Di& operator*=(const uint32_t coeff) ;

            /// <summary>
            /// Divide a Dimension by a uint32_t value and affect the result.
            /// </summary>
            /// <param name="coeff">
            /// The coeff to divide the Dimension coordinates by.
            /// </param>
            /// <returns>The result of the division.</returns>
            exported Dimension3Di& operator/=(const uint32_t coeff) ;

            /// <summary>
            /// Test if two Dimension have the same size.
            /// </summary>
            /// <param name="other">
            /// An other Dimension to compare to the current one.
            /// </param>
            /// <returns>
            /// true if the Dimension have the same size, false else.
            /// </returns>
            exported bool operator==(const Dimension3Di& other) const ;

            /// <summary>
            /// Test if two Dimension have not the same size.
            /// </summary>
            /// <param name="other">
            /// An other Dimension to compare to the current one.
            /// </param>
            /// <returns>
            /// true if the Dimension have two different size, false else.
            /// </returns>
            exported bool operator!=(const Dimension3Di& other) const ;

            /// <summary>
            /// Add a Dimension to another one.
            /// </summary>
            /// <param name="a">First Dimension.</param>
            /// <param name="b">Second Dimension.</param>
            /// <returns>Point at (a.w + b.w, a.h + b.h, a.d + b.d).</returns>
            exported friend Dimension3Di operator+(const Dimension3Di& a, const Dimension3Di& b) ;

            /// <summary>
            /// Substract a Dimension to another one.
            /// </summary>
            /// <param name="a">First Dimension.</param>
            /// <param name="b">Second Dimension.</param>
            /// <returns>Point at (a.w - b.w, a.h - b.h, a.d - b.d).</returns>
            exported friend Dimension3Di operator-(const Dimension3Di& a, const Dimension3Di& b) ;

            /// <summary>
            /// Multiply a Dimension by a uint32_t value (scale).
            /// </summary>
            /// <param name="d">Dimension to be multiplied.</param>
            /// <param name="coeff">Factor to scale the coordinates.</param>
            /// <returns>Point at (d.w * coeff, d.h * coeff, d.d * coeff).</returns>
            exported friend Dimension3Di operator*(const Dimension3Di& d, const uint32_t coeff) ;

            /// <summary>
            /// Divide a Dimension by a uint32_t value (scale).
            /// </summary>
            /// <param name="d">Dimension to be divided.</param>
            /// <param name="coeff">Factor to scale the coordinates.</param>
            /// <returns>Point at (d.w / coeff, d.h / coeff, d.d / coeff).</returns>
            exported friend Dimension3Di operator/(const Dimension3Di& d, const uint32_t coeff) ;

            /// <summary>
            /// Echo the Dimension size on console.
            /// </summary>
            /// <param name="s">
            /// The stream in which print the formatted coordinates.
            /// </param>
            /// <param name="p">The Dimension to print.</param>
            /// <returns>The stream with the printed Dimension size.</returns>
            exported friend std::ostream& operator<<(std::ostream& s, const Dimension3Di& p) ;
    } ;
} ;

#endif
