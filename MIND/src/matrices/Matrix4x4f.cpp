#include "harmful/mind/matrices/Matrix4x4f.hpp"
#include "harmful/mind/matrices/Matrix3x3f.hpp"
#include "harmful/mind/Math.hpp"
#include <iomanip>

#ifdef USE_SIMD // for compilations where SSE or NEON are available

namespace Mind {
    Matrix4x4f::Matrix4x4f(const Scalar value) : SquareMatrixf(4, value) {}

    Matrix4x4f::Matrix4x4f(const Matrix3x3f& mat3x3) : SquareMatrixf(mat3x3) {
        // Make sure the last row and column are zeroed.
        setRowValues(3, Vector4f()) ;
        setColumnValues(3, Vector4f()) ;
    }

    void Matrix4x4f::multiply(const Matrix4x4f& other) {
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

    void Matrix4x4f::compose(
        const Vector3f& translation,
        const Quaternion& rotation,
        const Vector3f& scale
    ) {
        // Compose the matrix in this order: scale, rotation and translation.
        // First, convert the quaternion to a 3x3 rotation matrix.
        Matrix3x3f rotationMatrix ;
        rotation.to(rotationMatrix) ;

        // Then multiply scale by rotation matrix values and put it in the
        // current transformation matrix.
        Point3Df xRow = Point3Df(rotationMatrix[0][0], rotationMatrix[0][1], rotationMatrix[0][2]) * scale[Point3Df::X] ;
        Point3Df yRow = Point3Df(rotationMatrix[1][0], rotationMatrix[1][1], rotationMatrix[1][2]) * scale[Point3Df::Y] ;
        Point3Df zRow = Point3Df(rotationMatrix[2][0], rotationMatrix[2][1], rotationMatrix[2][2]) * scale[Point3Df::Z] ;

        setRowValues(0, xRow) ;
        setRowValues(1, yRow) ;
        setRowValues(2, zRow) ;

        // Put the translation value in the last column.
        setColumnValues(3, translation) ;

        // No projection.
        Point4Df noProjection(0.f, 0.f, 0.f, 1.f) ;
        setRowValues(3, noProjection) ;
    }

    void Matrix4x4f::setColumnValues(
        const unsigned int column,
        const Point2Df& values
    ) {
        m_data[0][column] = values.get(Point2Df::Axis::X) ;
        m_data[1][column] = values.get(Point2Df::Axis::Y) ;
    }

    void Matrix4x4f::setColumnValues(
        const unsigned int column,
        const Point3Df& values
    ) {
        m_data[0][column] = values.get(Point3Df::Axis::X) ;
        m_data[1][column] = values.get(Point3Df::Axis::Y) ;
        m_data[2][column] = values.get(Point3Df::Axis::Z) ;
    }

    void Matrix4x4f::setColumnValues(
        const unsigned int column,
        const Point4Df& values
    ) {
        m_data[0][column] = values.get(Point4Df::Axis::X) ;
        m_data[1][column] = values.get(Point4Df::Axis::Y) ;
        m_data[2][column] = values.get(Point4Df::Axis::Z) ;
        m_data[3][column] = values.get(Point4Df::Axis::W) ;
    }

    Point4Df Matrix4x4f::getColumnValues(const unsigned int column) const {
        Point4Df tmp ;
        tmp.set(
            m_data[0][column],
            m_data[1][column],
            m_data[2][column],
            m_data[3][column]
        );
        return tmp ;
    }

    void Matrix4x4f::setRowValues(
        const unsigned int row,
        const Point2Df& values
    ) {
        m_data[row][0] = values.get(Point2Df::Axis::X) ;
        m_data[row][1] = values.get(Point2Df::Axis::Y) ;
    }

    void Matrix4x4f::setRowValues(
        const unsigned int row,
        const Point3Df& values
    ) {
        m_data[row][0] = values.get(Point3Df::Axis::X) ;
        m_data[row][1] = values.get(Point3Df::Axis::Y) ;
        m_data[row][2] = values.get(Point3Df::Axis::Z) ;
    }

    void Matrix4x4f::setRowValues(
        const unsigned int row,
        const Point4Df& values
    ) {
        m_data[row][0] = values.get(Point4Df::Axis::X) ;
        m_data[row][1] = values.get(Point4Df::Axis::Y) ;
        m_data[row][2] = values.get(Point4Df::Axis::Z) ;
        m_data[row][3] = values.get(Point4Df::Axis::W) ;
    }

    Point4Df Matrix4x4f::getRowValues(const unsigned int row) const {
        Point4Df tmp ;
        tmp.set(
            m_data[row][0],
            m_data[row][1],
            m_data[row][2],
            m_data[row][3]
        );
        return tmp ;
    }

    std::array<Scalar, 16> Matrix4x4f::toArray() const {
        return {
            m_data[0][0], m_data[0][1], m_data[0][2], m_data[0][3],
            m_data[1][0], m_data[1][1], m_data[1][2], m_data[1][3],
            m_data[2][0], m_data[2][1], m_data[2][2], m_data[2][3],
            m_data[3][0], m_data[3][1], m_data[3][2], m_data[3][3]
        } ;
    }

    Matrix4x4f& Matrix4x4f::operator*=(const Scalar scalar) {
        unsigned int length = static_cast<unsigned int>(size()) ;
        for (unsigned int rowIndex = 0 ; rowIndex < length ; rowIndex++) {
            m_data[rowIndex] *= scalar ;
        }
        return *this ;
    }

    Vector4f Matrix4x4f::operator*(const Vector4f& vec4) const {
        Vector4f result ;

        unsigned int length = static_cast<unsigned int>(size()) ;
        for (unsigned int colIndex = 0 ; colIndex < length ; colIndex++) {
            Vector4f column = getColumnValues(colIndex) ;

            Vector4f::Axis axis = static_cast<Vector4f::Axis>(colIndex) ;
            Vector4f columnProduct = column * vec4.get(axis) ;

            result += columnProduct ;
        }

        return result ;
    }

    Matrix4x4f& Matrix4x4f::operator*=(const Matrix4x4f& other) {
        *this = *this * other ;
        return *this ;
    }

    Matrix4x4f operator*(const Matrix4x4f& a, const Matrix4x4f& b) {
        Matrix4x4f result ;

        // Transpose the matrix to easily compute the product of each line of
        // "this" by each column of "other".
        Matrix4x4f bTransposed ;
        b.transposed(bTransposed) ;

        // Multiply each line of "this" by each column of "other".
        // Then add each element of the resulting row and store it in "this".
        unsigned int length = static_cast<unsigned int>(a.size()) ;
        for (unsigned int aRowIndex = 0 ; aRowIndex < length ; aRowIndex++) {
            Array4f rowResult ;
            for(unsigned int bRowIndex = 0 ; bRowIndex < length ; bRowIndex++) {
                SIMD::Vector4f mulRow = a.m_data[aRowIndex] * bTransposed.m_data[bRowIndex] ;
                Scalar value = mulRow.horizontalAdd() ;
                rowResult[bRowIndex] = value ;
            }
            result.m_data[aRowIndex].set(rowResult) ;
        }

        return result ;
    }

    Matrix4x4f& Matrix4x4f::operator+=(const Matrix4x4f& other) {
        unsigned int length = static_cast<unsigned int>(size()) ;
        for (unsigned int rowIndex = 0 ; rowIndex < length ; rowIndex++) {
            m_data[rowIndex] += other[rowIndex] ;
        }
        return *this ;
    }

    Vector3f Matrix4x4f::extractTranslation(Matrix4x4f& matrix) {
        // Translation vector is stored in the last column.
        const int TranslationVectorColumnIndex = 3;
        Vector3f translation = static_cast<Vector3f>(matrix.getColumnValues(TranslationVectorColumnIndex)) ;

        // Clear values in the matrix (with w = 1).
        matrix.setColumnValues(TranslationVectorColumnIndex, Vector4f(0, 0, 0, 1)) ;

        return translation ;
    }

    Vector3f Matrix4x4f::extractScale(Matrix4x4f& matrix) {
        const int Vector3Size = 3;

        Vector3f scale ;

        // Take the length of the (remaining) column vectors.
        // This will be the scale vector.
        for (int columnIndex = 0; columnIndex < Vector3Size; ++columnIndex)
        {
            Vector3f tmpVector = static_cast<Vector3f>(matrix.getColumnValues(columnIndex)) ;
            scale[columnIndex] = tmpVector.length() ;
        }

        return scale ;
    }

    Quaternion Matrix4x4f::extractRotation(
        Matrix4x4f& matrix,
        const Vector3f& scale
    ) {
        const int Vector3Size = 3;

        // Divide the matrix columns with the previously computed scale vector
        // components.
        // This will give the rotation matrix that can be converted to quaternion.
        for (int columnIndex = 0; columnIndex < Vector3Size; ++columnIndex)
        {
            Vector3f tmpVector = static_cast<Vector3f>(matrix.getColumnValues(columnIndex)) ;
            tmpVector = tmpVector / scale[columnIndex];
            matrix.setColumnValues(columnIndex, tmpVector);
        }

        Matrix3x3f rotationMatrix;
        rotationMatrix.setRowValues(0, static_cast<Vector3f>(matrix.getRowValues(0))) ;
        rotationMatrix.setRowValues(1, static_cast<Vector3f>(matrix.getRowValues(1))) ;
        rotationMatrix.setRowValues(2, static_cast<Vector3f>(matrix.getRowValues(2))) ;
        return Quaternion(rotationMatrix);
    }
} ;

#endif
