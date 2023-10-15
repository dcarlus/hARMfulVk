#include "harmful/mind/matrices/SquareMatrixf.hpp"
#include "harmful/mind/Math.hpp"

#ifdef USE_SIMD

namespace Mind {
    const size_t SquareMatrixf::MaximalDataSize = SIMD::Vector4f::size() ;

    template<int shuffleA, int shuffleB, int shuffle0, int shuffle3>
    static SIMD::Vector4f subFactor(const SquareMatrixf& that) {
        SIMD::Vector4f swp0a = VecShuffle1(that[3], that[2], shuffleA) ;
        SIMD::Vector4f swp0b = VecShuffle1(that[3], that[2], shuffleB) ;

        SIMD::Vector4f swp0 = VecShuffle1(that[2], that[1], shuffle0) ;
        SIMD::Vector4f swp1 = VecShuffle(swp0a, swp0a, 2, 0, 0, 0) ;
        SIMD::Vector4f swp2 = VecShuffle(swp0b, swp0b, 2, 0, 0, 0) ;
        SIMD::Vector4f swp3 = VecShuffle1(that[2], that[1], shuffle3) ;

        SIMD::Vector4f mul0 = swp0 * swp1 ;
        SIMD::Vector4f mul1 = swp2 * swp3 ;
        return mul0 - mul1 ;
    }

    template<int shuffle>
    static SIMD::Vector4f predefinedVecShuffle(const SquareMatrixf& that) {
        SIMD::Vector4f Temp = VecShuffle1(that[1], that[0], shuffle) ;
        return VecSwizzle(Temp, 2, 2, 2, 0) ;
    }


    SquareMatrixf::SquareMatrixf(
        const size_t size,
        const Scalar value
    ) : m_size(size),
        m_defaultValue(value) {
        for (size_t row = 0 ; row < MaximalDataSize ; ++row) {
            m_data[row] = SIMD::Vector4f(value) ;
        }
    }

    void SquareMatrixf::identity() {
        for (size_t row = 0 ; row < MaximalDataSize ; ++row) {
            Scalar columns[] = { 0.f, 0.f, 0.f, 0.f } ;

            if (row < m_size) {
                columns[row] = 1.f ;
            }

            m_data[row] = SIMD::Vector4f(
                columns[0],
                columns[1],
                columns[2],
                columns[3]
            ) ;
        }
    }

    Scalar SquareMatrixf::trace() const {
        return SIMD::Vector4f(
            at(0,0),
            at(1,1),
            at(2,2),
            at(3,3)
        ).horizontalAdd() ;
    }

    void SquareMatrixf::transposed(SquareMatrixf& result) const {
        // Copy data from the other matrix.
        SIMD::Vector4f transposed[] = {
            m_data[0],
            m_data[1],
            m_data[2],
            m_data[3]
        } ;

        SIMD::Vector4f::transposeMatrix(
            transposed[0],
            transposed[1],
            transposed[2],
            transposed[3]
        ) ;

        // Put transposed rows into the resulting matrix.
        for (uint8_t row = 0 ; row < MaximalDataSize ; ++row) {
            result.m_data[row] = transposed[row] ;
        }
    }

    void SquareMatrixf::inverse(SquareMatrixf& result) const {
        SIMD::Vector4f fac0 = subFactor<3, 2, 2, 3>(*this) ;
        SIMD::Vector4f fac1 = subFactor<3, 1, 1, 3>(*this) ;
        SIMD::Vector4f fac2 = subFactor<2, 1, 1, 2>(*this) ;
        SIMD::Vector4f fac3 = subFactor<3, 0, 0, 3>(*this) ;
        SIMD::Vector4f fac4 = subFactor<2, 0, 0, 2>(*this) ;
        SIMD::Vector4f fac5 = subFactor<1, 0, 0, 1>(*this) ;

        SIMD::Vector4f signA(+1, -1, +1, -1) ;
        SIMD::Vector4f signB(-1, +1, -1, +1) ;

        SIMD::Vector4f vec0  = predefinedVecShuffle<0>(*this) ;
        SIMD::Vector4f vec1  = predefinedVecShuffle<1>(*this) ;
        SIMD::Vector4f vec2  = predefinedVecShuffle<2>(*this) ;
        SIMD::Vector4f vec3  = predefinedVecShuffle<3>(*this) ;

        // Column 0.
        SIMD::Vector4f mul0 = vec1 * fac0 ;
    	SIMD::Vector4f mul1 = vec2 * fac1 ;
    	SIMD::Vector4f mul2 = vec3 * fac2 ;
    	SIMD::Vector4f sub0 = mul0 - mul1 ;
    	SIMD::Vector4f add0 = sub0 + mul2 ;
        SIMD::Vector4f inv0 = signB * add0 ;

        // Column 1.
        SIMD::Vector4f mul3 = vec0 * fac0 ;
    	SIMD::Vector4f mul4 = vec2 * fac3 ;
    	SIMD::Vector4f mul5 = vec3 * fac4 ;
    	SIMD::Vector4f sub1 = mul3 - mul4 ;
    	SIMD::Vector4f add1 = sub1 + mul5 ;
        SIMD::Vector4f inv1 = signA * add1 ;

        // Column 2.
        SIMD::Vector4f mul6 = vec0 * fac1 ;
    	SIMD::Vector4f mul7 = vec1 * fac3 ;
    	SIMD::Vector4f mul8 = vec3 * fac5 ;
    	SIMD::Vector4f sub2 = mul6 - mul7 ;
    	SIMD::Vector4f add2 = sub2 + mul8 ;
        SIMD::Vector4f inv2 = signB * add2 ;

        // Column 3.
        SIMD::Vector4f mul9 = vec0 * fac2 ;
    	SIMD::Vector4f mul10 = vec1 * fac4 ;
    	SIMD::Vector4f mul11 = vec2 * fac5 ;
    	SIMD::Vector4f sub3 = mul9 - mul10 ;
    	SIMD::Vector4f add3 = sub3 + mul11 ;
        SIMD::Vector4f inv3 = signA * add3 ;

        // Rows.
        SIMD::Vector4f row0 = VecShuffle1(inv0, inv1, 0) ;
        SIMD::Vector4f row1 = VecShuffle1(inv2, inv3, 0) ;
        SIMD::Vector4f row2 = VecShuffle(row0, row1, 2, 0, 2, 0) ;

        // Determinant.
        const static SIMD::Vector4f One(1.f) ;
        SIMD::Vector4f det0 = m_data[0].dot(row2) ;
        SIMD::Vector4f rcp0 = One / det0 ;

        //	Inverse /= Determinant;
        result[0] = inv0 * rcp0 ;
        result[1] = inv1 * rcp0 ;
        result[2] = inv2 * rcp0 ;
        result[3] = inv3 * rcp0 ;
    }

    size_t SquareMatrixf::size() const {
        return m_size ;
    }

    bool SquareMatrixf::operator==(const SquareMatrixf& other) const {
        if (this != &other) {
            if (size() != other.size()) {
                return false ;
            }

            for (size_t row = 0 ; row < m_size ; ++row) {
                SIMD::Vector4i::Mask equals = (SIMD::Vector4i::Mask) (m_data[row] == other.m_data[row]) ;

                for (unsigned char col = 0 ; col < m_size ; ++col) {
                    if (equals.get(col) == 0) {
                        return false ;
                    }
                }
            }

            return true ;
        }

        return true ;
    }

    bool SquareMatrixf::operator!=(const SquareMatrixf& other) const {
        return !(*this == other) ;
    }

    std::ostream& operator<<(std::ostream& s, const SquareMatrixf& p) {
        s << "SquareMatrixf: " << std::endl ;
            size_t size = p.size() ;
            for (unsigned int row = 0 ; row < size ; ++row) {
                s << "{ " ;
                for (unsigned int col = 0 ; col < size ; ++col) {
                    s << p.m_data[row][col] << " ; " ;
                }
                s << "}" << std::endl ;
            }
        s << std::endl ;
        return s ;
    }

    void SquareMatrixf::clearWith(const Scalar value) {
        Array4f values ;
        for (size_t col = 0 ; col < MaximalDataSize ; ++col) {
            if (col < m_size) {
                values[col] = value ;
            }
            else {
                values[col] = 0.f ;
            }
        }

        for (size_t row = 0 ; row < m_size ; ++row) {
            m_data[row].set(values) ;
        }
    }

    void SquareMatrixf::getData(Scalar* output) {
        size_t outputIndex = 0 ;
        for (size_t row = 0 ; row < m_size ; ++row) {
            output[outputIndex]     = m_data[row][0] ;
            output[outputIndex + 1] = m_data[row][1] ;
            output[outputIndex + 2] = m_data[row][2] ;
            output[outputIndex + 3] = m_data[row][3] ;
            outputIndex += MaximalDataSize ;
        }
    }
} ;

#endif
