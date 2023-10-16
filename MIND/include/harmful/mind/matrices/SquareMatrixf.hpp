#ifndef __MIND__SQUARE_MATRIXF__
#define __MIND__SQUARE_MATRIXF__

#include <cstddef>
#include <iostream>
#include <iomanip>
#include <vector>
#include <harmful/doom/utils/Platform.hpp>
#include "harmful/mind/simd/SIMDVector.hpp"
#include "harmful/mind/geometry/points/Point2Df.hpp"
#include "harmful/mind/geometry/points/Point3Df.hpp"

namespace Mind {
    // Pre-declare operator overloadings
    class SquareMatrixf ;
    std::ostream& operator<<(std::ostream& s, const SquareMatrixf& p) ;

    /// <summary>
    /// Square matrix base class with a fixed size.
    /// The maximal size of the matrix is four elements on row and columns.
    /// </summary>
    class SquareMatrixf {
        protected:
            /// <summary>
            /// Maximal amount of data in a direction.
            /// </summary>
            static const size_t MaximalDataSize ;

            /// <summary>
            /// Size of the SquareMatrix (one side).
            /// </summary>
            size_t m_size ;

            /// <summary>
            /// Default value of the cleared SquareMatrix.
            /// </summary>
            Scalar m_defaultValue ;

            /// <summary>
            /// SquareMatrix content values.
            /// </summary>
            SIMD::Vector4f m_data[4] ;

        public:
            /// <summary>
            /// Create a SquareMatrix with its size.
            /// </summary>
            /// <param name="size">
            /// Size of the SquareMatrix. This will produce a "size x size"
            /// matrix.
            /// </param>
            /// <param name="value">Initial value in the SquareMatrix.</param>
            exported SquareMatrixf(const size_t size, const Scalar value = 0) ;

            /// <summary>
            /// Copy a SquareMatrixf.
            /// </summary>
            /// <param name="mat">Matrix to copy.</param>
            exported SquareMatrixf(const SquareMatrixf& mat) = default ;

            /// <summary>
            /// Move a SquareMatrixf.
            /// </summary>
            /// <param name="mat">Matrix to move.</param>
            exported SquareMatrixf(SquareMatrixf&& mat) = default ;

            /// <summary>
            /// Destruction of the SquareMatrix.
            /// </summary>
            exported virtual ~SquareMatrixf() = default ;

            /// <summary>
            /// Extract the data of the matrix.
            /// </summary>
            /// <param name="output">
            /// Output data containing the matrix values.
            /// </param>
            exported virtual void data(std::vector<float>& output) = 0 ;

            /// <summary>
            /// Fill the SquareMatrix with its default value.
            /// </summary>
            exported void clear() ;

            /// <summary>
            /// Fill the SquareMatrix with zero values and put one on matrix
            /// diagonal (left to right, top to bottom).
            /// </summary>
            exported void identity() ;

            /// <summary>
            /// Compute the trace of the SquareMatrix, that is to say add all
            /// its diagonal components.
            /// </summary>
            /// <returns>Value of the trace of the SquareMatrix.</returns>
            exported Scalar trace() const ;

            /// <summary>
            /// Transpose the matrix.
            /// </summary>
            /// <param name="result">Transposed matrix output.</param>
            exported void transposed(SquareMatrixf& result) const ;

            /// <summary>
            /// Inverse the matrix.
            /// This source code is inspired from GLM library.
            /// https://github.com/g-truc/glm/blob/master/glm/simd/matrix.h
            /// </summary>
            /// <param name="result">Inverse matrix output.</param>
            exported void inverse(SquareMatrixf& result) const ;

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
            ) = 0 ;

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
            ) = 0 ;

            /// <summary>
            /// Set the values of a row from a Point2D.
            /// </summary>
            /// <param name="row">
            /// Index of the column in the SquareMatrix.
            /// </param>
            /// <param name="values">Values to set.</param>
            exported virtual void setRowValues(
                const unsigned int row,
                const Point2Df& values
            ) = 0 ;

            /// <summary>
            /// Set the values of a row from a Point3D.
            /// </summary>
            /// <param name="row">
            /// Index of the column in the SquareMatrix.
            /// </param>
            /// <param name="values">Values to set.</param>
            exported virtual void setRowValues(
                const unsigned int row,
                const Point3Df& values
            ) = 0 ;

            /// <summary>
            /// Get the element a the specified position.
            /// </summary>
            /// <param name="row">Index of the wanted row.</param>
            /// <param name="col">Index of the wanted column.</param>
            /// <returns>
            /// Value the element at the wanted column and row indices.
            /// </returns>
            exported Scalar at(
                const unsigned int row,
                const unsigned int col
            ) const ;

            /// <summary>
            /// Get the element a the specified position.
            /// </summary>
            /// <param name="row">Index of the wanted row.</param>
            /// <param name="col">Index of the wanted column.</param>
            /// <returns>
            /// Reference to the element at the wanted column and row indices.
            /// </returns>
            exported Scalar& at(
                const unsigned int row,
                const unsigned int col
            ) ;

            /// <summary>
            /// Set the element a the specified position.
            /// </summary>
            /// <param name="row">Index of the wanted row.</param>
            /// <param name="col">Index of the wanted column.</param>
            /// <param name="value">
            /// Value to set at the given position.
            /// </param>
            exported void at(
                const unsigned int row,
                const unsigned int col,
                const Scalar value
            ) ;

            /// <summary>
            /// Set or get the element a the specified position.
            /// </summary>
            /// <param name="index">Index of the wanted row.</param>
            /// <returns>Vector at the given row.</returns>
            exported SIMD::Vector4f& operator[](int index) ;
            exported const SIMD::Vector4f& operator[](int index) const ;

            /// <summary>
            /// Get the size of the SquareMatrix.
            /// </summary>
            /// <returns>
            /// Size of the SquareMatrix (amount of both columns and rows).
            /// </returns>
            exported size_t size() const ;

            /// <summary>
            /// Assignment operator to copy a SquareMatrixf.
            /// </summary>
            /// <param name="other">Matrix to copy.</param>
            /// <returns>
            /// The current SquareMatrixf with the copied values.
            /// </returns>
            exported SquareMatrixf& operator=(const SquareMatrixf& other) = default ;

            /// <summary>
            /// Assignment operator to move a SquareMatrixf.
            /// </summary>
            /// <param name="other">Matrix to move.</param>
            /// <returns>
            /// The current SquareMatrixf with the moved values.
            /// </returns>
            exported SquareMatrixf& operator=(SquareMatrixf&& other) = default ;

            /// <summary>
            /// Test if two SquareMatrixf have the same value at same position.
            /// </summary>
            /// <param name="other">
            /// An other matrix to compare to the current one.
            /// </param>
            /// <returns>
            /// true if the matrix have the same values, false else.
            /// </returns>
            exported bool operator==(const SquareMatrixf& other) const ;

            /// <summary>
            /// Test if two SquareMatrixf have different values for a same
            /// position.
            /// </summary>
            /// <param name="other">
            /// An other matrix to compare to the current one.
            /// </param>
            /// <returns>
            /// true if the matrix have different values, false else.
            /// </returns>
            exported bool operator!=(const SquareMatrixf& other) const ;

            /// <summary>
            /// Echo the SquareMatrix values on console.
            /// </summary>
            /// <param name="s">
            /// The stream in which print the formatted coordinates.
            /// </param>
            /// <param name="p">The SquareMatrix to print.</param>
            /// <returns>
            /// The stream with the printed Point coordinates.
            /// </returns>
            friend std::ostream& operator<<(
                std::ostream& s,
                const SquareMatrixf& p
            ) ;

        protected:
            /// <summary>
            /// Get the total size of the SquareMatrix.
            /// </summary>
            /// <returns>Total size of the SquareMatrix.</returns>
            exported size_t totalSize() const ;

            /// <summary>
            /// Clear the matrix with the given value.
            /// </summary>
            /// <param name="value">Value to fill the matrix with.</param>
            exported void clearWith(const Scalar value) ;

            /// <summary>
            /// Get the inner data of the SquareMatrix.
            /// </summary>
            /// <param name="output">Storage of the inner data.</param>
            exported void getData(std::vector<Scalar>& output) ;
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
