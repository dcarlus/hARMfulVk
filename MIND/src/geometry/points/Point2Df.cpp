#include "geometry/points/Point2Df.hpp"

#ifdef USE_SIMD // for compilations where SSE or NEON are available
#include "geometry/lines/Line2Df.hpp"
#include "FastMath.hpp"
#include "Math.hpp"

const int X = 0 ;
const int Y = 1 ;

namespace Mind {
    Point2Df::Point2Df() {
        m_values = SIMD::Vector4f(0.f, 0.f, 0.f, 0.f) ;
    }

    Point2Df::Point2Df(const SIMD::Vector4f& values) : m_values(values) {}

    Point2Df::Point2Df(const Scalar x, const Scalar y) {
        m_values = SIMD::Vector4f(x, y, 0.f, 0.f) ;
    }

    void Point2Df::translate(const Scalar x, const Scalar y) {
        m_values += SIMD::Vector4f(x, y, 0.f, 0.f) ;
    }

    void Point2Df::translate(const Point2Df& offset) {
        m_values += offset.m_values ;
    }

    Scalar Point2Df::dot(const Point2Df& other) const {
        return m_values.dot(other.m_values) ;
    }

    void Point2Df::normalize() {
        m_values /= m_values.norm() ;
    }

    Point2Df Point2Df::round(const Point2Df& point) {
        return Point2Df(SIMD::Vector4f::round(point.m_values)) ;
    }

    Point2Df Point2Df::floor(const Point2Df& point) {
        return Point2Df(SIMD::Vector4f::floor(point.m_values)) ;
    }

    Point2Df Point2Df::ceil(const Point2Df& point) {
        return Point2Df(SIMD::Vector4f::ceil(point.m_values)) ;
    }

    Point2Df Point2Df::merge(const Point2Df& a, const Point2Df& b) {
        SIMD::Vector4f middle = (a.m_values + b.m_values) / 2.f ;
        return Point2Df(middle) ;
    }

    Point2Df Point2Df::mul(const Point2Df& p, const Point2Df& other) {
        return Point2Df(p.m_values * other.m_values) ;
    }

    Scalar Point2Df::distanceX(const Point2Df& a, const Point2Df& b) {
        SIMD::Vector4f diff = a.m_values - b.m_values ;
        return std::abs(diff[X]) ;
    }

    Scalar Point2Df::distanceY(const Point2Df& a, const Point2Df& b) {
        SIMD::Vector4f diff = a.m_values - b.m_values ;
        return std::abs(diff[Y]) ;
    }

    Scalar Point2Df::distance(const Point2Df& a, const Point2Df& b) {
        SIMD::Vector4f::Mask comp = a.m_values == b.m_values ;
        SIMD::Vector4f diff = a.m_values - b.m_values ;

        bool isXEqual = comp.get(X) ;
        bool isYEqual = comp.get(Y) ;

        if (isXEqual) {
            return std::abs(diff[Y]) ;
        }
        else if (isYEqual) {
            return std::abs(diff[X]) ;
        }
        else {
            return Math::hypot(
                std::abs(diff[X]),
                std::abs(diff[Y])
            ) ;
        }
    }

    Scalar Point2Df::length() {
        SIMD::Vector4f squared = SIMD::Vector4f::square(m_values) ;
        Scalar squaredTotal = squared.horizontalAdd() ;
        return FastMath::sqrt(squaredTotal) ;
    }

    Scalar Point2Df::angle(
        const Point2Df& b,
        const Point2Df& c,
        const Point2Df& d
    ) {
        // Line between B and C
        Line2Df b_side(b, c) ;
        // Line between B and D
        Line2Df c_side(b, d) ;
        // Line between C and D
        Line2Df d_side(c, d) ;

        double angle =
        (
            b_side.lengthSquared() +
            d_side.lengthSquared() -
            c_side.lengthSquared()) /
            (2 * b_side.length() * d_side.length()
        ) ;

        return Math::toDegrees(static_cast<Scalar>(acos(angle))) ;
    }

    int Point2Df::angleOrientation(
        const Point2Df& a,
        const Point2Df& b,
        const Point2Df& c
    ) {
        Point2Df relativeAToB = a - b ;
        Point2Df relativeCToB = c - b ;

        // Compute:
        // ((relativeAToB.m_x * relativeCToB.m_y) - (relativeAToB.m_y * relativeCToB.m_x))
        relativeCToB.m_values.permute<1,0,2,3>() ;
        SIMD::Vector4f product = (relativeAToB.m_values * relativeCToB.m_values) ;
        return static_cast<int>(product.horizontalSub()) ;
    }

    Scalar Point2Df::get(const Axis axis) const {
        return m_values[axis] ;
    }

    Array4f& Point2Df::getCoordinates(Array4f& output) const {
        m_values.get(output) ;
        return output ;
    }

    void Point2Df::set(const Axis axis, const Scalar value) {
        m_values[axis] = value ;
    }

    void Point2Df::set(const Scalar x, const Scalar y) {
        m_values[X] = x ;
        m_values[Y] = y ;
    }

    void Point2Df::set(const Point2Df& position) {
        m_values = position.m_values ;
    }

    std::array<float, 2> Point2Df::toArray() const {
        return {m_values[0], m_values[1]} ;
    }

    Point2Df::operator Dimension2Df() {
        return Dimension2Df(m_values[X], m_values[Y]) ;
    }

    Point2Df::operator Point3Df() {
        return Point3Df(m_values[X], m_values[Y], 0.f) ;
    }

    Point2Df& Point2Df::operator+=(Point2Df& other) {
        m_values += other.m_values ;
        return *this ;
    }

    Point2Df& Point2Df::operator-=(Point2Df& other) {
        m_values -= other.m_values ;
        return *this ;
    }

    Point2Df& Point2Df::operator*=(Scalar coeff) {
        m_values *= coeff ;
        return *this ;
    }

    Point2Df& Point2Df::operator/=(Scalar coeff) {
        m_values /= coeff ;
        return *this ;
    }

    bool Point2Df::operator==(const Point2Df& other) const {
        if (this != &other) {
            SIMD::Vector4i::Mask equals = (SIMD::Vector4i::Mask) (m_values == other.m_values) ;
            return ((equals.get(X) != 0) && (equals.get(Y) != 0)) ;
        }

        return true ;
    }

    bool Point2Df::operator!=(const Point2Df& other) const {
        return !(*this == other) ;
    }

    Scalar Point2Df::operator[](const int axis) const {
        return m_values[axis] ;
    }

    Scalar& Point2Df::operator[](const int axis) {
        return m_values[axis] ;
    }

    Point2Df operator-(const Point2Df& p) {
        return Point2Df(-p.m_values) ;
    }

    Point2Df operator+(const Point2Df& a, const Point2Df& b) {
        return Point2Df(a.m_values + b.m_values) ;
    }

    Point2Df operator-(const Point2Df& a, const Point2Df& b) {
        return Point2Df(a.m_values - b.m_values) ;
    }

    Scalar operator*(const Point2Df& a, const Point2Df& b) {
        return a.dot(b) ;
    }

    Point2Df operator*(const Point2Df& p, Scalar coeff) {
        return Point2Df(p.m_values * coeff) ;
    }

    Point2Df operator/(const Point2Df& p, Scalar coeff) {
        return Point2Df(p.m_values / coeff) ;
    }

    std::ostream& operator<<(std::ostream& s, const Point2Df& p) {
        s << "Point2Df ("
            << p.get(Point2Df::Axis::X) << ","
            << p.get(Point2Df::Axis::Y) << ")" ;
        return s ;
    }
} ;

#endif
