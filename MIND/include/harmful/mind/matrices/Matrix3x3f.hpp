#ifndef __MIND__MATRIX_3X3F__
#define __MIND__MATRIX_3X3F__

#include <harmful/doom/utils/Platform.hpp>
#include "harmful/mind/matrices/SquareMatrixf.hpp"

namespace Mind {
    class Matrix4x4f ;

    /// <summary>
    /// 3x3 square matrix.
    /// </summary>
    class Matrix3x3f final : public SquareMatrixf {
        public:
            /// <summary>
            /// Total size of the matrix.
            /// </summary>
            static const int MatrixSize = 3*3 ;

            /// <summary>
            /// Create a square matrix of size equal to 3.
            /// </summary>
            /// <param name="value">
            /// Value of the matrix when created or cleared.
            /// The default value is zero.
            /// </param>
            exported Matrix3x3f(const Scalar value = 0.f) ;

            /**
             * 
             * @param   mat4x4  
             */

            /// <summary>
            /// Create a square matrix of size equal to 3 from a Matrix4x4f.
            /// </summary>
            /// <param name="mat4x4">
            /// The matrix to convert to a Matrix3x3f.
            /// </param>
            exported Matrix3x3f(const Matrix4x4f& mat4x4) ;

            /// <summary>
            /// Extract the data of the matrix.
            /// </summary>
            /// <param name="output">
            /// Output data containing the matrix values.
            /// </param>
            exported void data(std::vector<float>& output) override ;

            /// <summary>
            /// Multiply the current Matrix3x3 by another one.
            /// The result is set in the current Matrix3x3.
            /// </summary>
            /// <param name="other">
            /// The other Matrix3x3 used in the product.
            /// </param>
            exported void multiply(const Matrix3x3f& other) ;

            /// <summary>
            /// Set the values of a column from a Point2D.
            /// </summary>
            /// <param name="column">
            /// Index of the column in the SquareMatrix.
            /// </param>
            /// <param name="values">Values to set.</param>
            exported virtual void setColumnValues(
                const unsigned int column,
                const Point2Df& values
            ) final ;

            /// <summary>
            /// Set the values of a column from a Point3D.
            /// </summary>
            /// <param name="column">
            /// Index of the column in the SquareMatrix.
            /// </param>
            /// <param name="values">Values to set.</param>
            exported virtual void setColumnValues(
                const unsigned int column,
                const Point3Df& values
            ) final ;

            /// <summary>
            /// Get the values of a column.
            /// </summary>
            /// <param name="column">
            /// Index of the column in the SquareMatrix.
            /// </param>
            /// <returns>Values of the column.</returns>
            exported Point3Df getColumnValues(const unsigned int column) const ;

            /// <summary>
            /// Set the values of a row from a Point2D.
            /// </summary>
            /// <param name="row">
            /// Index of the row in the SquareMatrix.
            /// </param>
            /// <param name="values">Values to set.</param>
            exported virtual void setRowValues(
                const unsigned int row,
                const Point2Df& values
            ) final ;

            /// <summary>
            /// 
            /// </summary>
            /// <param name="row">
            /// Index of the row in the SquareMatrix.
            /// </param>
            /// <param name="values">
            /// Set the values of a row from a Point3D.
            /// </param>
            exported virtual void setRowValues(
                const unsigned int row,
                const Point3Df& values
            ) final ;

            /// <summary>
            /// Get the values of a row.
            /// </summary>
            /// <param name="row">
            /// Index of the row in the SquareMatrix.
            /// </param>
            /// <returns>Values of the row.</returns>
            exported Point3Df getRowValues(const unsigned int row) const ;

            /// <summary>
            /// Export the matrix as an 1D-array of values.
            /// </summary>
            /// <returns>
            /// 1D array containing the values of the matrix.
            /// </returns>
            exported std::array<Scalar, MatrixSize> toArray() const ;

            /// <summary>
            /// Multiply the current matrix by a scalar value.
            /// The result is put into the current matrix.
            /// </summary>
            /// <param name="scalar">
            /// The scalar value to multiply each component of the matrix with.
            /// </param>
            /// <returns>The result of the multiplication.</returns>
            exported Matrix3x3f& operator*=(const Scalar scalar) ;

            /// <summary>
            /// Multiply the current matrix by a scalar value.
            /// The result is put into a new matrix.
            /// </summary>
            /// <param name="scalar">
            /// The scalar value to multiply each component of the matrix with.
            /// </param>
            /// <returns>The result of the multiplication.</returns>
            exported Matrix3x3f operator*(const Scalar scalar) ;

            /// <summary>
            /// Multiply the current matrix by another matrix.
            /// The result is put into the current matrix.
            /// </summary>
            /// <param name="other">
            /// The other matrix to multiply with the current one.
            /// </param>
            /// <returns>The result of the multiplication.</returns>
            exported Matrix3x3f& operator*=(const Matrix3x3f& other) ;

            /// <summary>
            /// Multiplication of two matrices.
            /// </summary>
            /// <param name="a">First matrix.</param>
            /// <param name="b">Second matrix.</param>
            /// <returns>Result of the multiplication.</returns>
            exported friend Matrix3x3f operator*(const Matrix3x3f& a, const Matrix3x3f& b) ;

            /// <summary>
            /// Multiply the current matrix by a vector.
            /// </summary>
            /// <param name="vec3">
            /// The vector to multiply the current matrix with.
            /// </param>
            /// <returns>The result of the multiplication.</returns>
            exported Vector3f operator*(const Vector3f& vec3) const ;

            /// <summary>
            /// Addition of the current matrix with another one.
            /// The result is put into the current matrix.
            /// </summary>
            /// <param name="other">
            /// The other matrix to add to the current one.
            /// </param>
            /// <returns>The result of the addition.</returns>
            exported Matrix3x3f& operator+=(const Matrix3x3f& other) ;

            /// <summary>
            /// Addition of the current matrix with another one.
            /// The result is put into a new matrix
            /// </summary>
            /// <param name="other">
            /// The other matrix to add to the current one.
            /// </param>
            /// <returns>The result of the addition.</returns>
            exported Matrix3x3f operator+(const Matrix3x3f& other) ;
    } ;

    inline void Matrix3x3f::data(std::vector<float>& output) {
        output.resize(MatrixSize);

        for (int index = 0; index < MatrixSize ; ++index) {
            output[index] = m_data[index / m_size][index % m_size] ;
        }
    }

    inline Matrix3x3f Matrix3x3f::operator*(const Scalar scalar) {
        Matrix3x3f mat(*this) ;
        mat *= scalar ;
        return mat ;
    }

    inline Matrix3x3f Matrix3x3f::operator+(const Matrix3x3f& other) {
        Matrix3x3f mat(*this) ;
        mat += other ;
        return mat ;
    }
} ;

#endif
