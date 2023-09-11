#ifndef __MIND__MATRIX_3X3F__
#define __MIND__MATRIX_3X3F__

#include "matrices/SquareMatrixf.hpp"

namespace Mind {
    class Matrix4x4f ;

    /**
     * 3x3 square matrix.
     */
    class Matrix3x3f final : public SquareMatrixf {
        public:
            /**
             * Total size of the matrix.
             */
            static const int MatrixSize = 9 ;


            /**
             * Create a square matrix of size equal to 3.
             * @param   value   Value of the matrix when created or cleared.
             *                  The default value is zero.
             */
            exported Matrix3x3f(const Scalar value = 0.f) ;

            /**
             * Create a square matrix of size equal to 3 from a Matrix4x4f.
             * @param   mat4x4  The matrix to convert to a matrix 3x3.
             */
            exported Matrix3x3f(const Matrix4x4f& mat4x4) ;

            /**
             * Extract the data of the matrix.
             */
            exported void data(float* output) override ;

            /**
             * Multiply the current Matrix3x3 by another one.
             * The result is set in the current Matrix3x3.
             * @param   other   The other Matrix3x3 used in the product.
             */
            exported void multiply(const Matrix3x3f& other) ;

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
             * Get the values of a column.
             * @param   column  Index of the column in the SquareMatrix.
             * @return  Values of the column.
             */
            exported Point3Df getColumnValues(const unsigned int column) const ;

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
             * Get the values of a row.
             * @param   row     Index of the row in the SquareMatrix.
             * @return  Values of the row.
             */
            exported Point3Df getRowValues(const unsigned int row) const ;

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
            exported Matrix3x3f& operator*=(const Scalar scalar) ;

            /**
             * Multiply the current matrix by a scalar value.
             * The result is put into a new matrix.
             * @param   mat     The matrix to multiply.
             * @param   scalar  The scalar value to multiply each component of
             *                  the matrix with.
             * @return  The result of the multiplication.
             */
            exported Matrix3x3f operator*(const Scalar scalar) ;

            /**
             * Multiply the current matrix by another matrix.
             * The result is put into the current matrix.
             * @param   other   The other matrix to multiply with the current
             *                  one.
             * @return  The result of the multiplication.
             */
            exported Matrix3x3f& operator*=(const Matrix3x3f& other) ;

            /**
             * Multiplication of two matrices.
             * @param   a   First matrix.
             * @param   b   Second matrix.
             * @return  Result of the multiplication.
             */
            exported friend Matrix3x3f operator*(const Matrix3x3f& a, const Matrix3x3f& b) ;

            /**
             * Multiply the current matrix by a vector.
             * @param   vec3    The vector to multiply the current matrix with.
             * @return  The result of the multiplication.
             */
            exported Vector3f operator*(const Vector3f& vec3) const ;

            /**
             * Addition of the current matrix with another one.
             * The result is put into the current matrix.
             * @param   other   The other matrix to add to the current one.
             * @return  The result of the addition.
             */
            exported Matrix3x3f& operator+=(const Matrix3x3f& other) ;

            /**
             * Addition of the current matrix with another one.
             * The result is put into a new matrix.
             * @param   mat     The matrix to add.
             * @param   other   The other matrix to add to the current one.
             * @return  The result of the addition.
             */
            exported Matrix3x3f operator+(const Matrix3x3f& other) ;
    } ;

    inline void Matrix3x3f::data(float* output) {
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
