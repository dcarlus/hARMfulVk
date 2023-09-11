#ifndef __MIND__MATRIX_4X4F__
#define __MIND__MATRIX_4X4F__

#include "matrices/SquareMatrixf.hpp"
#include "geometry/points/Point3Df.hpp"
#include "geometry/points/Point4Df.hpp"
#include "geometry/quaternions/Quaternion.hpp"

namespace Mind {
    class Matrix3x3f ;

    /**
     * 4x4 square matrix.
     */
    class Matrix4x4f final : public SquareMatrixf {
        public:
            /**
             * Total size of the matrix.
             */
            static const int MatrixSize = 16 ;


            /**
             * Create a square matrix of size equal to 4.
             * @param   value   Value of the matrix when created or cleared.
             *                  The default value is zero.
             */
            exported Matrix4x4f(const Scalar value = 0.f) ;

            /**
             * Create a square matrix of size equal to 4 from a Matrix3x3f.
             * @param   mat3x3  The matrix to convert to a matrix 4x4.
             */
            exported Matrix4x4f(const Matrix3x3f& mat3x3) ;

            /**
             * Extract the data of the matrix.
             */
            exported void data(float* output) override ;

            /**
             * Multiplay the current Matrix4x4 by another one.
             *          The result is set in the current Matrix4x4.
             * @param   other   The other Matrix4x4 used in the product.
             */
            exported void multiply(const Matrix4x4f& other) ;

            /**
             * @brief   Decompose the matrix 4x4 to translation, rotation and
             *          scale values.
             * @param   translation Output translation vector contained in the
             *                      matrix.
             * @param   rotation    Output rotation contained in the matrix.
             * @param   scale       Output scale vector contained in the matrix.
             */
            exported void decompose(
                Vector3f& translation,
                Quaternion& rotation,
                Vector3f& scale
            ) ;

            /**
             * @brief   Compose the matrix 4x4 to store translation, rotation
             *          and scale values inside.
             * @param   translation Input translation vector contained in the
             *                      matrix.
             * @param   rotation    Input rotation contained in the matrix.
             * @param   scale       Input scale vector contained in the matrix.
             */
            exported void compose(
                const Vector3f& translation,
                const Quaternion& rotation,
                const Vector3f& scale
            ) ;

            /**
             * @brief   Extract the translation from the current matrix.
             * @return  Translation vector contained in the matrix.
             */
            exported Vector3f extractTranslation() const ;

            /**
             * @brief   Extract the rotation from the current matrix.
             * @return  Quaternion contained in the matrix.
             */
            exported Quaternion extractRotation() const ;

            /**
             * @brief   Extract the scale from the current matrix.
             * @return  Scale vector contained in the matrix.
             */
            exported Vector3f extractScale() const ;

            /**
             * Set the values of a column from a Point2D.
             * @param   column  Index of the column in the SquareMatrix.
             * @param   values  Values to set.
             */
            exported virtual void setColumnValues(
                const unsigned int column,
                const Point2Df& values
            ) final ;

            /**
             * Set the values of a column from a Point3D.
             * @param   column  Index of the column in the SquareMatrix.
             * @param   values  Values to set.
             */
            exported virtual void setColumnValues(
                const unsigned int column,
                const Point3Df& values
            ) final ;

            /**
             * Set the values of a column from a Point4D.
             * @param   column  Index of the column in the SquareMatrix.
             * @param   values  Values to set.
             */
            exported void setColumnValues(
                const unsigned int column,
                const Point4Df& values
            ) ;

            /**
             * Get the values of a column.
             * @param   column  Index of the column in the SquareMatrix.
             * @return  Values of the column.
             */
            exported Point4Df getColumnValues(const unsigned int column) const ;

            /**
             * Set the values of a row from a Point2D.
             * @param   row     Index of the row in the SquareMatrix.
             * @param   values  Values to set.
             */
            exported virtual void setRowValues(
                const unsigned int row,
                const Point2Df& values
            ) final ;

            /**
             * Set the values of a row from a Point3D.
             * @param   row     Index of the row in the SquareMatrix.
             * @param   values  Values to set.
             */
            exported virtual void setRowValues(
                const unsigned int row,
                const Point3Df& values
            ) final ;

            /**
             * Set the values of a row from a Point4D.
             * @param   row     Index of the row in the SquareMatrix.
             * @param   values  Values to set.
             */
            exported void setRowValues(
                const unsigned int row,
                const Point4Df& values
            ) ;

            /**
             * Get the values of a row.
             * @param   row     Index of the row in the SquareMatrix.
             * @return  Values of the row.
             */
            exported Point4Df getRowValues(const unsigned int row) const ;

            /**
             * Export the matrix as an 1D-array of values.
             */
            exported std::array<Scalar, MatrixSize> toArray() const ;

            /**
             * Multiply the current matrix by a scalar value.
             * The result is put into the current matrix.
             * @param   scalar  The scalar value to multiply each component of
             *                  the matrix with.
             * @return  The result of the multiplication.
             */
            exported Matrix4x4f& operator*=(const Scalar scalar) ;

            /**
             * Multiply the current matrix by a scalar value.
             * The result is put into a new matrix.
             * @param   mat     The matrix to multiply.
             * @param   scalar  The scalar value to multiply each component of
             *                  the matrix with.
             * @return  The result of the multiplication.
             */
            exported Matrix4x4f operator*(const Scalar scalar) ;

            /**
             * Multiply the current matrix by another matrix.
             * The result is put into the current matrix.
             * @param   other   The other matrix to multiply with the current
             *                  one.
             * @return  The result of the multiplication.
             */
            exported Matrix4x4f& operator*=(const Matrix4x4f& other) ;

            /**
             * Multiplication of two matrices.
             * @param   a   First matrix.
             * @param   b   Second matrix.
             * @return  Result of the multiplication.
             */
            exported friend Matrix4x4f operator*(const Matrix4x4f& a, const Matrix4x4f& b) ;

            /**
             * Multiply the current matrix by a vector.
             * @param   vec4    The vector to multiply the current matrix with.
             * @return  The result of the multiplication.
             */
            exported Vector4f operator*(const Vector4f& vec4) const ;

            /**
             * Addition of the current matrix with another one.
             * The result is put into the current matrix.
             * @param   other   The other matrix to add to the current one.
             * @return  The result of the addition.
             */
            exported Matrix4x4f& operator+=(const Matrix4x4f& other) ;

            /**
             * Addition of the current matrix with another one.
             * The result is put into a new matrix.
             * @param   mat     The matrix to add.
             * @param   other   The other matrix to add to the current one.
             * @return  The result of the addition.
             */
            exported Matrix4x4f operator+(const Matrix4x4f& other) ;

        private:
            /**
             * @brief   Extract the translation from the given matrix.
             * @return  Translation vector contained in the matrix.
             */
            exported static Vector3f extractTranslation(Matrix4x4f& matrix) ;

            /**
             * @brief   Extract the scale from the given matrix.
             * @return  Scale vector contained in the matrix.
             */
            exported static Vector3f extractScale(Matrix4x4f& matrix) ;

            /**
             * @brief   Extract the rotation from the given matrix.
             * @param   scale   Scale vector contained in the matrix.
             * @return  Quaternion contained in the matrix.
             */
            exported static Quaternion extractRotation(
                Matrix4x4f& matrix,
                const Vector3f& scale
            ) ;
    } ;

    inline void Matrix4x4f::data(float* output) {
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
