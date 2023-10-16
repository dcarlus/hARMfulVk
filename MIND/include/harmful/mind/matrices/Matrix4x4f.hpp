#ifndef __MIND__MATRIX_4X4F__
#define __MIND__MATRIX_4X4F__

#include <harmful/doom/utils/Platform.hpp>
#include "harmful/mind/matrices/SquareMatrixf.hpp"
#include "harmful/mind/geometry/points/Point3Df.hpp"
#include "harmful/mind/geometry/points/Point4Df.hpp"
#include "harmful/mind/geometry/quaternions/Quaternion.hpp"

namespace Mind {
    class Matrix3x3f ;

    /// <summary>
    /// 4x4 square matrix.
    /// </summary>
    class Matrix4x4f final : public SquareMatrixf {
        public:
            /// <summary>
            /// Total size of the matrix.
            /// </summary>
            static const int MatrixSize = 4*4 ;

            /// <summary>
            /// Create a square matrix of size equal to 4.
            /// </summary>
            /// <param name="value">
            /// Value of the matrix when created or cleared. The default value
            /// is zero.
            /// </param>
            exported Matrix4x4f(const Scalar value = 0.f) ;

            /// <summary>
            /// Create a square matrix of size equal to 4 from a Matrix3x3f.
            /// </summary>
            /// <param name="mat3x3">
            /// The matrix to convert to a matrix 4x4.
            /// </param>
            exported Matrix4x4f(const Matrix3x3f& mat3x3) ;

            /// <summary>
            /// Extract the data of the matrix.
            /// </summary>
            /// <param name="output">
            /// Output data containing the matrix values.
            /// </param>
            exported void data(std::vector<float>& output) override ;

            /// <summary>
            /// Multiply the current Matrix4x4 by another one. The result is
            /// set in the current Matrix4x4.
            /// </summary>
            /// <param name="other">
            /// The other Matrix4x4 used in the product.
            /// </param>
            exported void multiply(const Matrix4x4f& other) ;

            /// <summary>
            /// Decompose the matrix 4x4 to translation, rotation and scale
            /// values.
            /// </summary>
            /// <param name="translation">
            /// Output translation vector contained in the matrix.
            /// </param>
            /// <param name="rotation">
            /// Output rotation contained in the matrix.
            /// </param>
            /// <param name="scale">
            /// Output scale vector contained in the matrix.
            /// </param>
            exported void decompose(
                Vector3f& translation,
                Quaternion& rotation,
                Vector3f& scale
            ) ;

            /// <summary>
            /// Compose the matrix 4x4 to store translation, rotation and scale
            /// values inside.
            /// </summary>
            /// <param name="translation">
            /// Input translation vector contained in the matrix.
            /// </param>
            /// <param name="rotation">
            /// Input rotation contained in the matrix.
            /// </param>
            /// <param name="scale">
            /// Input scale vector contained in the matrix.
            /// </param>
            exported void compose(
                const Vector3f& translation,
                const Quaternion& rotation,
                const Vector3f& scale
            ) ;

            /// <summary>
            /// Extract the translation from the current matrix.
            /// </summary>
            /// <returns>
            /// Translation vector contained in the matrix.
            /// </returns>
            exported Vector3f extractTranslation() const ;

            /// <summary>
            /// Extract the rotation from the current matrix.
            /// </summary>
            /// <returns>Quaternion contained in the matrix.</returns>
            exported Quaternion extractRotation() const ;

            /// <summary>
            /// Extract the scale from the current matrix.
            /// </summary>
            /// <returns>Scale vector contained in the matrix.</returns>
            exported Vector3f extractScale() const ;

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
            /// Set the values of a column from a Point4D.
            /// </summary>
            /// <param name="column">
            /// Index of the column in the SquareMatrix.
            /// </param>
            /// <param name="values">Values to set.</param>
            exported void setColumnValues(
                const unsigned int column,
                const Point4Df& values
            ) ;

            /// <summary>
            /// Get the values of a column.
            /// </summary>
            /// <param name="column">
            /// Index of the column in the SquareMatrix.
            /// </param>
            /// <returns>Values of the column.</returns>
            exported Point4Df getColumnValues(const unsigned int column) const ;

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
            /// Set the values of a row from a Point3D.
            /// </summary>
            /// <param name="row">
            /// Index of the row in the SquareMatrix.
            /// </param>
            /// <param name="values">Values to set.</param>
            exported virtual void setRowValues(
                const unsigned int row,
                const Point3Df& values
            ) final ;

            /// <summary>
            /// Set the values of a row from a Point4D.
            /// </summary>
            /// <param name="row">
            /// Index of the row in the SquareMatrix.
            /// </param>
            /// <param name="values">Values to set.</param>
            exported void setRowValues(
                const unsigned int row,
                const Point4Df& values
            ) ;

            /// <summary>
            /// Get the values of a row.
            /// </summary>
            /// <param name="row">
            /// Index of the row in the SquareMatrix.
            /// </param>
            /// <returns>Values of the row.</returns>
            exported Point4Df getRowValues(const unsigned int row) const ;

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
            exported Matrix4x4f& operator*=(const Scalar scalar) ;

            /// <summary>
            /// Multiply the current matrix by a scalar value.
            /// The result is put into a new matrix.
            /// </summary>
            /// <param name="scalar">
            /// The scalar value to multiply each component of the matrix with.
            /// </param>
            /// <returns>The result of the multiplication.</returns>
            exported Matrix4x4f operator*(const Scalar scalar) ;

            /// <summary>
            /// Multiply the current matrix by another matrix.
            /// The result is put into the current matrix.
            /// </summary>
            /// <param name="other">
            /// The other matrix to multiply with the current one.
            /// </param>
            /// <returns>The result of the multiplication.</returns>
            exported Matrix4x4f& operator*=(const Matrix4x4f& other) ;

            /// <summary>
            /// Multiplication of two matrices.
            /// </summary>
            /// <param name="a">First matrix.</param>
            /// <param name="b">Second matrix.</param>
            /// <returns>Result of the multiplication.</returns>
            exported friend Matrix4x4f operator*(const Matrix4x4f& a, const Matrix4x4f& b) ;

            /// <summary>
            /// Multiply the current matrix by a vector.
            /// </summary>
            /// <param name="vec4">
            /// The vector to multiply the current matrix with.
            /// </param>
            /// <returns>The result of the multiplication.</returns>
            exported Vector4f operator*(const Vector4f& vec4) const ;

            /// <summary>
            /// Addition of the current matrix with another one.
            /// The result is put into the current matrix.
            /// </summary>
            /// <param name="other">
            /// The other matrix to add to the current one.
            /// </param>
            /// <returns>The result of the addition.</returns>
            exported Matrix4x4f& operator+=(const Matrix4x4f& other) ;

            /// <summary>
            /// Addition of the current matrix with another one.
            /// The result is put into a new matrix.
            /// </summary>
            /// <param name="other">
            /// The other matrix to add to the current one.
            /// </param>
            /// <returns>The result of the addition.</returns>
            exported Matrix4x4f operator+(const Matrix4x4f& other) ;

        private:
            /// <summary>
            /// Extract the translation from the given matrix.
            /// </summary>
            /// <param name="matrix">
            /// Matrix to extract the translation vector from.
            /// </param>
            /// <returns>
            /// Translation vector contained in the matrix.
            /// </returns>
            exported static Vector3f extractTranslation(Matrix4x4f& matrix) ;

            /// <summary>
            /// Extract the scale from the given matrix.
            /// </summary>
            /// <param name="matrix">
            /// Matrix to extract the scale vector from.
            /// </param>
            /// <returns>
            /// Scale vector contained in the matrix.
            /// </returns>
            exported static Vector3f extractScale(Matrix4x4f& matrix) ;

            /**
             * @brief   
             * @param   scale   Scale vector contained in the matrix.
             * @return  
             */

            /// <summary>
            /// Extract the rotation from the given matrix.
            /// </summary>
            /// <param name="matrix">
            /// Matrix to extract the rotation quaternion from.
            /// </param>
            /// <param name="scale">
            /// Scale vector to compute the rotation matrix internally.
            /// </param>
            /// <returns>
            /// Quaternion contained in the matrix.
            /// </returns>
            exported static Quaternion extractRotation(
                Matrix4x4f& matrix,
                const Vector3f& scale
            ) ;
    } ;

    inline void Matrix4x4f::data(std::vector<float>& output) {
        output.resize(MatrixSize);

        for (int index = 0; index < MatrixSize ; ++index) {
            output[index] = m_data[index / m_size][index % m_size] ;
        }
    }

    inline void Matrix4x4f::decompose(
        Vector3f& translation,
        Quaternion& rotation,
        Vector3f& scale
    ) {
        Matrix4x4f copy(*this) ;
        translation = extractTranslation(copy) ;
        scale = extractScale(copy) ;
        rotation = extractRotation(copy, scale) ;
    }

    inline Vector3f Matrix4x4f::extractTranslation() const {
        Matrix4x4f copy(*this) ;
        return extractTranslation(copy) ;
    }

    inline Quaternion Matrix4x4f::extractRotation() const {
        Matrix4x4f copy(*this) ;
        Vector3f scale = extractScale(copy) ;
        return extractRotation(copy, scale) ;
    }

    inline Vector3f Matrix4x4f::extractScale() const {
        Matrix4x4f copy(*this) ;
        return extractScale(copy) ;
    }

    inline Matrix4x4f Matrix4x4f::operator*(const Scalar scalar) {
        Matrix4x4f mat(*this) ;
        mat *= scalar ;
        return mat ;
    }

    inline Matrix4x4f Matrix4x4f::operator+(const Matrix4x4f& other) {
        Matrix4x4f mat(*this) ;
        mat += other ;
        return mat ;
    }
} ;

#endif
