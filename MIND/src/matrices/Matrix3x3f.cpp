#include "harmful/mind/matrices/Matrix3x3f.hpp"
#include "harmful/mind/matrices/Matrix4x4f.hpp"

#ifdef USE_SIMD // for compilations where SSE or NEON are available

namespace Mind {
    Matrix3x3f::Matrix3x3f(const Scalar value) : SquareMatrixf(3, value) {}

    Matrix3x3f::Matrix3x3f(const Matrix4x4f& mat4x4) : SquareMatrixf(mat4x4) {
        // Make sure the last row and column are zeroed.
        setRowValues(3, Vector3f()) ;
        setColumnValues(3, Vector3f()) ;
    }

    void Matrix3x3f::multiply(const Matrix3x3f& other) {
        // Copy data from the other matrix.
        SIMD::Vector4f transposedOther[] = {
            other.m_data[0],
            other.m_data[1],
            other.m_data[2],
            other.m_data[3]
        } ;

        // Transpose the rows of the other matrix to compute the product.
        SIMD::Vector4f::transposeMatrix(
            transposedOther[0],
            transposedOther[1],
            transposedOther[2],
            transposedOther[3]
        ) ;

        // Multiply the vectors of the matrices.
        m_data[0] = m_data[0] * transposedOther[0] ;
        m_data[1] = m_data[1] * transposedOther[1] ;
        m_data[2] = m_data[2] * transposedOther[2] ;
        m_data[3] = m_data[3] * transposedOther[3] ;
    }

    void Matrix3x3f::setColumnValues(
        const unsigned int column,
        const Point2Df& values
    ) {
        m_data[0][column] = values.get(Vector2f::Axis::X) ;
        m_data[1][column] = values.get(Vector2f::Axis::Y) ;
    }

    void Matrix3x3f::setColumnValues(
        const unsigned int column,
        const Point3Df& values
    ) {
        m_data[0][column] = values.get(Vector3f::Axis::X) ;
        m_data[1][column] = values.get(Vector3f::Axis::Y) ;
        m_data[2][column] = values.get(Vector3f::Axis::Z) ;
    }

    Point3Df Matrix3x3f::getColumnValues(const unsigned int column) const {
        Point3Df tmp ;
        tmp.set(
            m_data[0][column],
            m_data[1][column],
            m_data[2][column]
        );
        return tmp ;
    }

    void Matrix3x3f::setRowValues(
        const unsigned int row,
        const Point2Df& values
    ) {
        m_data[row][0] = values.get(Vector2f::Axis::X) ;
        m_data[row][1] = values.get(Vector2f::Axis::Y) ;
    }

    void Matrix3x3f::setRowValues(
        const unsigned int row,
        const Point3Df& values
    ) {
        m_data[row][0] = values.get(Vector3f::Axis::X) ;
        m_data[row][1] = values.get(Vector3f::Axis::Y) ;
        m_data[row][2] = values.get(Vector3f::Axis::Z) ;
    }

    Point3Df Matrix3x3f::getRowValues(const unsigned int row) const {
        Point3Df tmp ;
        tmp.set(
            m_data[row][0],
            m_data[row][1],
            m_data[row][2]
        );
        return tmp ;
    }

    std::array<Scalar, 9> Matrix3x3f::toArray() const {
        return {
            m_data[0][0], m_data[0][1], m_data[0][2],
            m_data[1][0], m_data[1][1], m_data[1][2],
            m_data[2][0], m_data[2][1], m_data[2][2]
        } ;
    }

    Matrix3x3f& Matrix3x3f::operator*=(const Scalar scalar) {
        unsigned int length = static_cast<unsigned int>(size()) ;
        for (unsigned int rowIndex = 0 ; rowIndex < length ; rowIndex++) {
            m_data[rowIndex] *= scalar ;
        }
        return *this ;
    }

    Matrix3x3f& Matrix3x3f::operator*=(const Matrix3x3f& other) {
        *this = *this * other ;
        return *this ;
    }

    Matrix3x3f operator*(const Matrix3x3f& a, const Matrix3x3f& b) {
        Matrix3x3f result ;

        // Transpose the matrix to easily compute the product of each line of
        // "this" by each column of "other".
        Matrix3x3f bTransposed ;
        b.transposed(bTransposed) ;

        // Multiply each line of "this" by each column of "other".
        // Then add each element of the resulting row and store it in "this".
        unsigned int length = static_cast<unsigned int>(a.size()) ;
        for (unsigned int aRowIndex = 0 ; aRowIndex < length ; aRowIndex++) {
            Array4f rowResult ;
            for(unsigned int bTransposedIndex = 0 ; bTransposedIndex < length ; bTransposedIndex++) {
                SIMD::Vector4f mulRow = a.m_data[aRowIndex] * bTransposed.m_data[bTransposedIndex] ;
                Scalar value = mulRow.horizontalAdd() ;
                rowResult[bTransposedIndex] = value ;
            }
            result.m_data[aRowIndex].set(rowResult) ;
        }

        return result ;
    }

    Vector3f Matrix3x3f::operator*(const Vector3f& vec3) const {
        Vector3f result ;

        unsigned int length = static_cast<unsigned int>(size()) ;
        for (unsigned int colIndex = 0 ; colIndex < length ; colIndex++) {
            Vector3f column = getColumnValues(colIndex) ;

            Vector3f::Axis axis = static_cast<Vector3f::Axis>(colIndex) ;
            Vector3f columnProduct = column * vec3.get(axis) ;

            result += columnProduct ;
        }

        return result ;
    }

    Matrix3x3f& Matrix3x3f::operator+=(const Matrix3x3f& other) {
        unsigned int length = static_cast<unsigned int>(size()) ;
        for (unsigned int rowIndex = 0 ; rowIndex < length ; rowIndex++) {
            m_data[rowIndex] += other[rowIndex] ;
        }
        return *this ;
    }
} ;

#endif
