#ifndef __MIND__MATRIX2D__
#define __MIND__MATRIX2D__

#include <iostream>
#include <vector>
#include <cstddef>
#include <harmful/doom/utils/Platform.hpp>
#include "harmful/mind/MINDTypes.hpp"

namespace Mind {
    /**
     * Resizable matrix to store data with an unknown final size.
     */
    template<class T>
    class Matrix2D final {
        private:
            /** Dynamic matrix itself, handled through vectors. */
            std::vector<std::vector<T>> m_data ;

        public:
            /**
             * Create a dynamically resizable Matrix with initial sizes.
             * @param   cols    Amount of columns in the Matrix.
             * @param   rows    Amount of rows in the Matrix.
             * @param   value   Initial value in the Matrix.
             */
            exported Matrix2D(
                const size_t cols = 1,
                const size_t rows = 1,
                const T value = {}
            ) ;

            /**
             * Copy a Matrix2D.
             * @param copy  The matrix to copy.
             */
            exported Matrix2D(const Matrix2D& copy) = default ;

            /**
             * Move a Matrix2D.
             * @param move  The matrix to move.
             */
            exported Matrix2D(Matrix2D&& move) = default ;

            /** Destroy the matrix. */
            exported virtual ~Matrix2D() ;

            /** Clear the matrix. */
            exported void clear() ;

            /**
             * Resize the matrix. Use 0 to leave a dimension with the current
             * size.
             * @param   cols    Amount of columns in the Matrix.
             * @param   rows    Amount of rows in the Matrix.
             * @param   value   Initial value in the Matrix.
             */
            exported void resize(
                const size_t cols,
                const size_t rows,
                const T value = {}
            ) ;

            /**
             * Reserve space in the matrix.
             * @param cols Amount of columns to reserve.
             * @param rows Amount of rows to reserve.
             */
            exported void reserve(const size_t cols, const size_t rows) ;

            /** Get the element a the specified position. */
            exported T& at(const size_t col, const size_t row) ;


            /** Get the number of rows in the matrix. */
            exported size_t rows() const ;

            /** Get the number of cols in the matrix. */
            exported size_t cols() const ;

            /**
             * Assignment operator to copy a Matrix2D.
             * @return  The current Matrix2D with the copied values.
             */
            exported Matrix2D& operator=(const Matrix2D& other) = default ;

            /**
             * Assignment operator to move a Matrix2D.
             * @return  The current Matrix2D with the moved values.
             */
            exported Matrix2D& operator=(Matrix2D&& other) = default ;

            /** Get a row from the matrix. */
            exported std::vector<T>& operator[] (const size_t iIndex) ;
    } ;

    /** Echo the matrix on console. */
    template<class T>
    exported std::ostream& operator<<(std::ostream& s, Matrix2D<T>& mat) ;




    /****************************** IMPLEMENTATION *******************************/
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
