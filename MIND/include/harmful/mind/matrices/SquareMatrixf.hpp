#ifndef __MIND__SQUARE_MATRIXF__
#define __MIND__SQUARE_MATRIXF__

#include <cstddef>
#include <iostream>
#include <iomanip>
#include <harmful/doom/utils/Platform.hpp>
#include "harmful/mind/simd/SIMDVector.hpp"
#include "harmful/mind/geometry/points/Point2Df.hpp"
#include "harmful/mind/geometry/points/Point3Df.hpp"

namespace Mind {
    // Pre-declare operator overloadings
    class SquareMatrixf ;
    std::ostream& operator<<(std::ostream& s, const SquareMatrixf& p) ;

    /**
     * Square matrix base class with a fixed size.
     * The maximal size of the matrix is four elements on row and columns.
     */
    class SquareMatrixf {
        protected:
            /**
             * Maximal amount of data in a direction.
             */
            static const size_t MaximalDataSize ;

            /**
             * Size of the SquareMatrix (one side).
             */
            size_t m_size ;

            /**
             * Default value of the cleared SquareMatrix.
             */
            Scalar m_defaultValue ;

            /**
             * SquareMatrix content values.
             */
            SIMD::Vector4f m_data[4] ;

        public:
            /**
             * Create a SquareMatrix with its size.
             * @param	size 	Size of the SquareMatrix. This will produce a
             *					"size x size" matrix.
             * @param	value 	Initial value in the SquareMatrix.
             */
            exported SquareMatrixf(const size_t size, const Scalar value = 0) ;

            /**
             * Copy a SquareMatrixf.
             */
            exported SquareMatrixf(const SquareMatrixf& mat) = default ;

            /**
             * Move a SquareMatrixf.
             */
            exported SquareMatrixf(SquareMatrixf&& mat) = default ;

            /**
             * Destruction of the SquareMatrix.
             */
            exported virtual ~SquareMatrixf() = default ;

            /**
             * Extract the data of the matrix.
             */
            exported virtual void data(float* output) = 0 ;

            /**
             * Fill the SquareMatrix with its default value.
             */
            exported void clear() ;

            /**
             * Fill the SquareMatrix with zero values and put one on
             * matrix diagonal (left to right, top to bottom).
             */
            exported void identity() ;

            /**
             * Compute the trace of the SquareMatrix, that is to say add all its
             * diagonal components.
             * @return Value of the trace of the SquareMatrix.
             */
            exported Scalar trace() const ;

            /**
             * Transpose the matrix.
             */
            exported void transposed(SquareMatrixf& result) const ;

            /**
             * Inverse the matrix.
             * This source code is inspired from GLM library.
             * https://github.com/g-truc/glm/blob/master/glm/simd/matrix.h
             */
            exported void inverse(SquareMatrixf& result) const ;

            /**
             * Set the values of a column from a Point2D.
             * @param   column  Index of the column in the SquareMatrix.
             * @param   values  Values to set.
             */
            exported virtual void setColumnValues(
                const unsigned int column,
                const Point2Df& values
            ) = 0 ;

            /**
             * Set the values of a column from a Point3D.
             * @param   column  Index of the column in the SquareMatrix.
             * @param   values  Values to set.
             */
            exported virtual void setColumnValues(
                const unsigned int column,
                const Point3Df& values
            ) = 0 ;

            /**
             * Set the values of a row from a Point2D.
             * @param   column  Index of the column in the SquareMatrix.
             * @param   values  Values to set.
             */
            exported virtual void setRowValues(
                const unsigned int row,
                const Point2Df& values
            ) = 0 ;

            /**
             * Set the values of a row from a Point3D.
             * @param   column  Index of the column in the SquareMatrix.
             * @param   values  Values to set.
             */
            exported virtual void setRowValues(
                const unsigned int row,
                const Point3Df& values
            ) = 0 ;

            /**
             * Get the element a the specified position.
             * @param   row     Index of the wanted row.
             * @param   col     Index of the wanted column.
             * @return	Reference to the element at the wanted column and row
             *			indices.
             */
            exported Scalar at(
                const unsigned int row,
                const unsigned int col
            ) const ;

            /**
             * Get the element a the specified position.
             * @param   row     Index of the wanted row.
             * @param   col     Index of the wanted column.
             * @return	Reference to the element at the wanted column and row
             *			indices.
             */
            exported Scalar& at(
                const unsigned int row,
                const unsigned int col
            ) ;

            /**
             * Set the element a the specified position.
             * @param   col     Index of the wanted column.
             * @param   row     Index of the wanted row.
             * @param   value   Value to set at the given position.
             */
            exported void at(
                const unsigned int row,
                const unsigned int col,
                const Scalar value
            ) ;

            /**
             * Set or get the element a the specified position.
             * @param   index   Index of the wanted row.
             */
            exported SIMD::Vector4f& operator[](int index) ;
            exported const SIMD::Vector4f& operator[](int index) const ;

            /**
             * Get the size of the SquareMatrix.
             * @return	Size of the SquareMatrix (amount of both columns and
             *			rows).
             */
            exported size_t size() const ;

            /**
             * Assignment operator to copy a SquareMatrixf.
             * @return  The current SquareMatrixf with the copied values.
             */
            exported SquareMatrixf& operator=(const SquareMatrixf& other) = default ;

            /**
             * Assignment operator to move a SquareMatrixf.
             * @return  The current SquareMatrixf with the moved values.
             */
            exported SquareMatrixf& operator=(SquareMatrixf&& other) = default ;

            /**
             * Test if two SquareMatrixf have the same value at same position.
             * @param   other   An other matrix to compare to the current one.
             * @return  TRUE if the matrix have the same values, FALSE else.
             */
            exported bool operator==(const SquareMatrixf& other) const ;

            /**
             * Test if two SquareMatrixf have different values for a same
             * position.
             * @param   other   An other matrix to compare to the current one.
             * @return  TRUE if the matrix have different values, FALSE else.
             */
            exported bool operator!=(const SquareMatrixf& other) const ;

            /**
            * Echo the SquareMatrix values on console.
            * @param   s   The stream in which print the formatted coordinates.
            * @param   p   The SquareMatrix to print.
            * @return  The stream with the printed Point coordinates.
            */
            friend std::ostream& operator<<(
                std::ostream& s,
                const SquareMatrixf& p
            ) ;

        protected:
            /**
             * Get the total size of the SquareMatrix.
             * @return  Total amount of elements in the SquareMatrix.
             */
            exported unsigned int totalSize() const ;

            /**
             * Clear the matrix with the given value.
             * @param   value   Value to fill the matrix with.
             */
            exported void clearWith(const Scalar value) ;

            /**
             * Get the inner data of the SquareMatrix.
             * @param   output  Storage of the inner data.
             * @warning Output must have the right size as a single array.
             */
            exported void getData(Scalar* output) ;
    } ;

    inline void SquareMatrixf::clear() {
        clearWith(m_defaultValue) ;
    }

    inline Scalar SquareMatrixf::at(
        const unsigned int row,
        const unsigned int col
    ) const {
        return m_data[row][col] ;
    }

    inline Scalar& SquareMatrixf::at(
        const unsigned int row,
        const unsigned int col
    ) {
        return m_data[row][col] ;
    }

    inline void SquareMatrixf::at(
        const unsigned int row,
        const unsigned int col,
        const Scalar value
    ) {
        m_data[row][col] = value ;
    }

    inline SIMD::Vector4f& SquareMatrixf::operator[](int index) {
        return m_data[index] ;
    }

    inline const SIMD::Vector4f& SquareMatrixf::operator[](int index) const {
        return m_data[index] ;
    }
} ;

#endif
