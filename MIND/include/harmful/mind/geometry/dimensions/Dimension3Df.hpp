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

    /// <summary>
    /// A Dimension is used to get the size of an element, and so get the area
    /// of the element as a rectangle bounding shape.
    /// </summary>
    class Dimension3Df final {
        private:
            /// <summary>
            /// Width of the Dimension3Df.
            /// </summary>
            Scalar m_width = 0.f ;

            /// <summary>
            /// Height of the Dimension3Df.
            /// </summary>
            Scalar m_height = 0.f ;

            /// <summary>
            /// Depth of the Dimension3Df.
            /// </summary>
            Scalar m_depth = 0.f ;

        public:
            // Default constructors/assignemnts.
            exported Dimension3Df() = default;
            exported Dimension3Df(const Dimension3Df& copied) = default;
            exported Dimension3Df(Dimension3Df&& moved) = default;
            exported Dimension3Df& operator=(const Dimension3Df& copied) = default;
            exported Dimension3Df& operator=(Dimension3Df&& moved) = default;
            exported ~Dimension3Df() noexcept = default;

            /// <summary>
            /// Create a Dimension with the given sizes.
            /// </summary>
            /// <param name="width">Width to set the size of the element.</param>
            /// <param name="height">Height to set the size of the element.</param>
            /// <param name="depth">Depth to set the size of the element.</param>
            exported Dimension3Df(
                const Scalar width,
                const Scalar height,
                const Scalar depth
            ) ;


            /// <summary>
            /// Set the Dimension as absolute values.
            /// </summary>
            exported void absolute() ;

            /// <summary>
            /// Get the width of the dimension.
            /// </summary>
            /// <returns>The width.</returns>
            exported Scalar width() const ;

            /// <summary>
            /// Get the height of the dimension.
            /// </summary>
            /// <returns>The height.</returns>
            exported Scalar height() const ;

            /// <summary>
            /// Get the depth of the dimension.
            /// </summary>
            /// <returns>The depth.</returns>
            exported Scalar depth() const ;

            /// <summary>
            /// Set the width of the dimension.
            /// </summary>
            /// <param name="width">Width of the dimension.</param>
            exported void setWidth(const Scalar width) ;

            /// <summary>
            /// Set the height of the dimension.
            /// </summary>
            /// <param name="height">Height of the dimension.</param>
            exported void setHeight(const Scalar height) ;

            /// <summary>
            /// Set the depth of the dimension.
            /// </summary>
            /// <param name="depth">Depth of the dimension.</param>
            exported void setDepth(const Scalar depth) ;

            /// <summary>
            /// Set the width, height and depth of the dimension.
            /// </summary>
            /// <param name="width">Width of the dimension.</param>
            /// <param name="height">Height of the dimension.</param>
            /// <param name="depth">Depth of the dimension.</param>
            exported void set(
                const Scalar width,
                const Scalar height,
                const Scalar depth
            ) ;

            /// <summary>
            /// Conversion from Dimension3D to Point3D.
            /// </summary>
            exported explicit operator Point3Df() ;

            /// <summary>
            /// Conversion from Dimension3D to Dimension2D.
            /// </summary>
            exported explicit operator Dimension2Df() ;

            /// <summary>
            /// Add a Dimension and affect the result.
            /// </summary>
            /// <param name="other">The other Dimension to add.</param>
            /// <returns>The sum of the two Dimensions.</returns>
            exported Dimension3Df& operator+=(Dimension3Df& other) ;

            /// <summary>
            /// Substract a Dimension and affect the result.
            /// </summary>
            /// <param name="other">The other Dimension to substract.</param>
            /// <returns>The substract of the two Dimensions.</returns>
            exported Dimension3Df& operator-=(Dimension3Df& other) ;

            /// <summary>
            /// Multiply a Dimension by a scalar value and affect the result.
            /// </summary>
            /// <param name="coeff">
            /// The coeff to multiply the Dimension coordinates by.
            /// </param>
            /// <returns>The result of the multiplication.</returns>
            exported Dimension3Df& operator*=(const Scalar coeff) ;

            /// <summary>
            /// Divide a Dimension by a scalar value and affect the result.
            /// </summary>
            /// <param name="coeff">
            /// The coeff to divide the Dimension coordinates by.
            /// </param>
            /// <returns>The result of the division.</returns>
            exported Dimension3Df& operator/=(const Scalar coeff) ;

            /// <summary>
            /// Test if two Dimension have the same size.
            /// </summary>
            /// <param name="other">
            /// An other Dimension to compare to the current one.
            /// </param>
            /// <returns>
            /// true if the Dimension have the same size, false else.
            /// </returns>
            exported bool operator==(const Dimension3Df& other) const ;

            /// <summary>
            /// Test if two Dimension have not the same size.
            /// </summary>
            /// <param name="other">
            /// An other Dimension to compare to the current one.
            /// </param>
            /// <returns>
            /// true if the Dimension have two different size, false else.
            /// </returns>
            exported bool operator!=(const Dimension3Df& other) const ;

            /// <summary>
            /// Add a Dimension to another one.
            /// </summary>
            /// <param name="a">First Dimension.</param>
            /// <param name="b">Second Dimension.</param>
            /// <returns>Point at (a.w + b.w, a.h + b.h).</returns>
            exported friend Dimension3Df operator+(const Dimension3Df& a, const Dimension3Df& b) ;

            /// <summary>
            /// Substract a Dimension to another one.
            /// </summary>
            /// <param name="a">First Dimension.</param>
            /// <param name="b">Second Dimension.</param>
            /// <returns>Point at (a.w - b.w, a.h - b.h).</returns>
            exported friend Dimension3Df operator-(const Dimension3Df& a, const Dimension3Df& b) ;

            /// <summary>
            /// Multiply a Dimension by a scalar value (scale).
            /// </summary>
            /// <param name="d">Dimension to be multiplied.</param>
            /// <param name="coeff">Factor to scale the coordinates.</param>
            /// <returns>Point at (d.w * coeff, d.h * coeff).</returns>
            exported friend Dimension3Df operator*(const Dimension3Df& d, const Scalar coeff) ;

            /// <summary>
            /// Divide a Dimension by a scalar value (scale).
            /// </summary>
            /// <param name="d">Dimension to be divided.</param>
            /// <param name="coeff">Factor to scale the coordinates.</param>
            /// <returns>Point at (d.w / coeff, d.h / coeff).</returns>
            exported friend Dimension3Df operator/(const Dimension3Df& d, const Scalar coeff) ;

            /// <summary>
            /// Echo the Dimension size on console.
            /// </summary>
            /// <param name="s">
            /// The stream in which print the formatted coordinates.
            /// </param>
            /// <param name="p">The Dimension to print.</param>
            /// <returns>The stream with the printed Dimension size.</returns>
            exported friend std::ostream& operator<<(std::ostream& s, const Dimension3Df& p) ;
    } ;
} ;

#endif
