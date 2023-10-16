#ifndef __MIND__MATRIX2D__
#define __MIND__MATRIX2D__

#include <iostream>
#include <vector>
#include <cstddef>
#include <harmful/doom/utils/Platform.hpp>
#include "harmful/mind/MINDTypes.hpp"

namespace Mind {
    /// <summary>
    /// Resizable matrix to store data with an unknown final size.
    /// </summary>
    /// <typeparam name="T">Any element type.</typeparam>
    template<class T>
    class Matrix2D final {
        private:
            /// <summary>
            /// Dynamic matrix itself, handled through vectors.
            /// </summary>
            std::vector<std::vector<T>> m_data ;

        public:
            /// <summary>
            /// Create a dynamically resizable Matrix with initial sizes.
            /// </summary>
            /// <param name="cols">Amount of columns in the Matrix.</param>
            /// <param name="rows">Amount of rows in the Matrix.</param>
            /// <param name="value">Initial value in the Matrix.</param>
            exported Matrix2D(
                const size_t cols = 1,
                const size_t rows = 1,
                const T value = {}
            ) ;

            /// <summary>
            /// Copy a Matrix2D.
            /// </summary>
            /// <param name="copy">The matrix to copy.</param>
            exported Matrix2D(const Matrix2D& copy) = default ;

            /// <summary>
            /// Move a Matrix2D.
            /// </summary>
            /// <param name="move">The matrix to move.</param>
            exported Matrix2D(Matrix2D&& move) = default ;

            /// <summary>
            /// Destroy the Matrix2D.
            /// </summary>
            exported virtual ~Matrix2D() ;

            /// <summary>
            /// Clear the matrix.
            /// </summary>
            exported void clear() ;

            /// <summary>
            /// Resize the matrix. Use 0 to leave a dimension with the current
            /// size.
            /// </summary>
            /// <param name="cols">Amount of columns in the Matrix.</param>
            /// <param name="rows">Amount of rows in the Matrix.</param>
            /// <param name="value">Initial value in the Matrix.</param>
            exported void resize(
                const size_t cols,
                const size_t rows,
                const T value = {}
            ) ;

            /// <summary>
            /// Reserve space in the matrix.
            /// </summary>
            /// <param name="cols">Amount of columns to reserve.</param>
            /// <param name="rows">Amount of rows to reserve.</param>
            exported void reserve(const size_t cols, const size_t rows) ;

            /// <summary>
            /// Get the element a the specified position.
            /// </summary>
            /// <param name="col">Column of the element.</param>
            /// <param name="row">Row  of the element.</param>
            /// <returns>The element at [col, row].</returns>
            exported T& at(const size_t col, const size_t row) ;

            /// <summary>
            /// Get the number of rows in the matrix.
            /// </summary>
            /// <returns>Amount of rows in the matrix.</returns>
            exported size_t rows() const ;

            /// <summary>
            /// Get the number of cols in the matrix.
            /// </summary>
            /// <returns>Amount of columns in the matrix.</returns>
            exported size_t cols() const ;

            /// <summary>
            /// Assignment operator to copy a Matrix2D.
            /// </summary>
            /// <param name="other">The matrix to copy.</param>
            /// <returns>The current Matrix2D with the copied values.</returns>
            exported Matrix2D& operator=(const Matrix2D& other) = default ;

            /// <summary>
            /// Assignment operator to move a Matrix2D.
            /// </summary>
            /// <param name="other">The matrix to move.</param>
            /// <returns>The current Matrix2D with the moved values.</returns>
            exported Matrix2D& operator=(Matrix2D&& other) = default ;

            /// <summary>
            /// Get a row from the matrix.
            /// </summary>
            /// <param name="iIndex">Index of the row to get.</param>
            /// <returns>The wanted row.</returns>
            exported std::vector<T>& operator[] (const size_t iIndex) ;
    } ;

    /// <summary>
    /// Echo the matrix on console.
    /// </summary>
    /// <typeparam name="T">Any element type.</typeparam>
    /// <param name="s">The stream in which print the matrix.</param>
    /// <param name="mat">The matrix to print.</param>
    /// <returns>The stream with the printed matrix.</returns>
    template<class T>
    exported std::ostream& operator<<(std::ostream& s, Matrix2D<T>& mat) ;

    template <class T>
    Matrix2D<T>::Matrix2D(
        const size_t rows,
        const size_t cols,
        const T value
    ) {
        m_data = std::vector<std::vector<T>>(rows, std::vector<T>(cols, value)) ;
    }

    template <class T>
    Matrix2D<T>::~Matrix2D() {
        clear() ;
    }


    template <class T>
    void Matrix2D<T>::clear() {
        for (size_t row = 0 ; row < m_data.size() ; row++)
            m_data[row].clear() ;
        m_data.clear() ;
    }

    template <class T>
    void Matrix2D<T>::resize(
        const size_t rows,
        const size_t cols,
        const T value
    ) {
        m_data.resize(rows) ;
        for (size_t row = 0 ; row < m_data.size() ; row++) {
            m_data[row].resize(cols, value) ;
        }
    }

    template <class T>
    void Matrix2D<T>::reserve(
        const size_t rows,
        const size_t cols
    ) {
        m_data.reserve(rows) ;
        for (size_t row = 0 ; row < m_data.size() ; row++)
            m_data[row].reserve(cols) ;
    }

    template <class T>
    T& Matrix2D<T>::at(
        const size_t row,
        const size_t col
    ) {
        return m_data[row][col] ;
    }

    template <class T>
    size_t Matrix2D<T>::rows() const {
        return m_data[0].size() ;
    }

    template <class T>
    size_t Matrix2D<T>::cols() const {
        return m_data.size() ;
    }

    template <class T>
    std::vector<T>& Matrix2D<T>::operator[] (const size_t iIndex) {
        return m_data[iIndex] ;
    }

    template<class T>
    std::ostream& operator<<(std::ostream& s, Matrix2D<T>& mat) {
        const size_t cols = mat.cols() ;
        const size_t rows = mat.rows() ;
        const size_t lastRow = rows - 1 ;

        for (size_t col = 0 ; col < cols ; col++) {
            s << "[" ;
                for (size_t row = 0 ; row < rows ; row++) {
                    s << mat.at(row, col) ;
                    if (row < lastRow)
                        s << "," ;
                }
            s << "]" << std::endl ;
        }

        return s ;
    }
} ;

#endif
