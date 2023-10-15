#include "harmful/mind/geometry/points/Point3Df.hpp"

#ifdef USE_SIMD // for compilations where SSE or NEON are available
#include "harmful/mind/geometry/points/Point2Df.hpp"
#include "harmful/mind/geometry/dimensions/Dimension3Df.hpp"
#include "harmful/mind/matrices/Matrix3x3f.hpp"
#include "harmful/mind/FastMath.hpp"
#include "harmful/mind/Math.hpp"

const int X = 0 ;
const int Y = 1 ;
const int Z = 2 ;

namespace Mind {
    Point3Df::Point3Df() {
        m_values = SIMD::Vector4f(0.f, 0.f, 0.f, 0.f) ;
    }

    Point3Df::Point3Df(const Point2Df& copy) {
        m_values = SIMD::Vector4f(
            copy.get(Point2Df::X),
            copy.get(Point2Df::Y),
            0.f,
            0.f
        ) ;
    }

    Point3Df::Point3Df(const SIMD::Vector4f& values) : m_values(values) {}

    Point3Df::Point3Df(const Scalar x, const Scalar y, const Scalar z) {
       m_values = SIMD::Vector4f(x, y, z, 0.f) ;
    }

    void Point3Df::translate(const Scalar x, const Scalar y, const Scalar z) {
        m_values += SIMD::Vector4f(x, y, z, 0.f) ;
    }

    void Point3Df::translate(const Point3Df& offset) {
        m_values += offset.m_values ;
    }

    Scalar Point3Df::dot(const Point3Df& other) const {
        return m_values.dot(other.m_values) ;
    }

    Point3Df Point3Df::cross(const Point3Df& other) const {
        return m_values.cross(other.m_values) ;
    }

    void Point3Df::normalize() {
        m_values /= length() ;
    }

    Point3Df Point3Df::round(const Point3Df& point) {
        return Point3Df(SIMD::Vector4f::round(point.m_values)) ;
    }

    Point3Df Point3Df::floor(const Point3Df& point) {
        return Point3Df(SIMD::Vector4f::floor(point.m_values)) ;
    }

    Point3Df Point3Df::ceil(const Point3Df& point) {
        return Point3Df(SIMD::Vector4f::ceil(point.m_values)) ;
    }

    Point3Df Point3Df::merge(const Point3Df& a, const Point3Df& b) {
        SIMD::Vector4f middle = (a.m_values + b.m_values) / 2.f ;
        return Point3Df(middle) ;
    }

    Point3Df Point3Df::mul(const Point3Df& p, const Point3Df& other) {
        return Point3Df(p.m_values * other.m_values) ;
    }

    Scalar Point3Df::distanceX(const Point3Df& a, const Point3Df& b) {
        SIMD::Vector4f diff = a.m_values - b.m_values ;
        return std::fabs(diff[X]) ;
    }

    Scalar Point3Df::distanceY(const Point3Df& a, const Point3Df& b) {
        SIMD::Vector4f diff = a.m_values - b.m_values ;
        return std::fabs(diff[Y]) ;
    }

    Scalar Point3Df::distanceZ(const Point3Df& a, const Point3Df& b) {
        SIMD::Vector4f diff = a.m_values - b.m_values ;
        return std::fabs(diff[Z]) ;
    }

    Scalar Point3Df::distance(const Point3Df& a, const Point3Df& b) {
        SIMD::Vector4f diff = a.m_values - b.m_values ;
        diff.squared() ;
        Scalar dot = diff.horizontalAdd() ;
        return FastMath::sqrt(dot) ;
    }

    Scalar Point3Df::length() {
        return FastMath::sqrt(this -> dot(*this)) ;
    }

    Scalar Point3Df::get(const Axis axis) const {
        return m_values[axis] ;
    }

    void Point3Df::set(const Axis axis, const Scalar value) {
        m_values[axis] = value ;
    }

    void Point3Df::set(const Scalar x, const Scalar y, const Scalar z) {
        m_values[X] = x ;
        m_values[Y] = y ;
        m_values[Z] = z ;
    }

    void Point3Df::set(const Point3Df& position) {
        m_values = position.m_values ;
    }

    std::array<float, 3> Point3Df::toArray() const {
        return {m_values[0], m_values[1], m_values[2]} ;
    }

    Point3Df::operator Dimension3Df() {
        return Dimension3Df(m_values[X], m_values[Y], m_values[Z]) ;
    }

    Point3Df::operator Point2Df() {
        return Point2Df(m_values[X], m_values[Y]) ;
    }

    Point3Df& Point3Df::operator+=(Point3Df& other) {
        m_values += other.m_values ;
        return *this ;
    }

    Point3Df& Point3Df::operator-=(Point3Df& other) {
        m_values -= other.m_values ;
        return *this ;
    }

    Point3Df& Point3Df::operator*=(const Scalar coeff) {
        m_values *= coeff ;
        return *this ;
    }

    Point3Df& Point3Df::operator*=(const Matrix3x3f& mat3) {
        *this = *this * mat3 ;
        return *this ;
    }

    Point3Df& Point3Df::operator/=(const Scalar coeff) {
        m_values /= coeff ;
        return *this ;
    }

    bool Point3Df::operator==(const Point3Df& other) const {
        if (this != &other) {
            SIMD::Vector4i::Mask equals = (SIMD::Vector4i::Mask) (m_values == other.m_values) ;
            return (
                        (equals.get(X) != 0)
                        && (equals.get(Y) != 0)
                        && (equals.get(Z) != 0)
                    ) ;
        }

        return true ;
    }

    bool Point3Df::operator!=(const Point3Df& other) const {
        return !(*this == other) ;
    }

    Scalar Point3Df::operator[](const int axis) const {
        return m_values[axis] ;
    }

    Scalar& Point3Df::operator[](const int axis) {
        return m_values[axis] ;
    }

    Point3Df operator-(const Point3Df& p) {
        return Point3Df(-p.m_values) ;
    }

    Point3Df operator+(const Point3Df& a, const Point3Df& b) {
        return Point3Df(a.m_values + b.m_values) ;
    }

    Point3Df operator-(const Point3Df& a, const Point3Df& b) {
        return Point3Df(a.m_values - b.m_values) ;
    }

    Scalar operator*(const Point3Df& a, const Point3Df& b) {
        return a.dot(b) ;
    }

    Point3Df operator*(const Point3Df& vec, const Matrix3x3f& mat) {
        Point3Df result ;

        unsigned int length = static_cast<unsigned int>(mat.size()) ;
        for (unsigned int rowIndex = 0 ; rowIndex < length ; rowIndex++) {
            Point3Df row = mat.getRowValues(rowIndex) ;

            Point3Df::Axis axis = static_cast<Point3Df::Axis>(rowIndex) ;
            Point3Df rowProduct = row * vec.get(axis) ;
            result += rowProduct ;
        }

        return result ;
    }

    Point3Df operator*(const Point3Df& p, const Scalar coeff) {
        return Point3Df(p.m_values * coeff) ;
    }

    Point3Df operator/(const Point3Df& p, const Scalar coeff) {
        return Point3Df(p.m_values / coeff) ;
    }

    std::ostream& operator<<(std::ostream& s, const Point3Df& p) {
        s << "Point3Df (" <<
                             p.get(Point3Df::Axis::X) << "," <<
                             p.get(Point3Df::Axis::Y) << "," <<
                             p.get(Point3Df::Axis::Z) <<
                      ")" ;
        return s ;
    }
} ;

#endif
