#include "harmful/mind/geometry/dimensions/Dimension2Df.hpp"
#include "harmful/mind/geometry/dimensions/Dimension3Df.hpp"
#include <cmath>

namespace Mind {
    Dimension2Df::Dimension2Df() : m_width(0.f), m_height(0.f) {}

    Dimension2Df::Dimension2Df(
        const Scalar width,
        const Scalar height
    ): m_width(width),
       m_height(height) {}

    void Dimension2Df::absolute() {
        m_width = std::fabs(m_width) ;
        m_height = std::fabs(m_height) ;
    }

    Scalar Dimension2Df::width() const {
        return m_width ;
    }


    Scalar Dimension2Df::height() const {
        return m_height ;
    }

    void Dimension2Df::setWidth(const Scalar width) {
        m_width = std::fabs(width) ;
    }

    void Dimension2Df::setHeight(const Scalar height) {
        m_height = std::fabs(height) ;
    }

    void Dimension2Df::set(const Scalar width, const Scalar height) {
        m_width = std::fabs(width) ;
        m_height = std::fabs(height) ;
    }

    Dimension2Df::operator Point2Df() {
        return Point2Df(m_width, m_height) ;
    }

    Dimension2Df::operator Dimension3Df() {
        return Dimension3Df(m_width, m_height, 0.f) ;
    }

    Dimension2Df& Dimension2Df::operator+=(Dimension2Df& other) {
        m_width += other.m_width ;
        m_height += other.m_height ;
        return *this ;
    }

    Dimension2Df& Dimension2Df::operator-=(Dimension2Df& other) {
        m_width = (other.m_width > m_width) ? 0 : m_width - other.m_width ;
        m_height = (other.m_height > m_height) ? 0 : m_height - other.m_height ;

        return *this ;
    }

    Dimension2Df& Dimension2Df::operator*=(const Scalar coeff) {
        m_width *= coeff ;
        m_height *= coeff ;
        return *this ;
    }

    Dimension2Df& Dimension2Df::operator/=(const Scalar coeff) {
        m_width /= coeff ;
        m_height /= coeff ;
        return *this ;
    }

    bool Dimension2Df::operator==(const Dimension2Df& other) const {
        return ((this == &other) ||
                    ((m_width == other.m_width) && (m_height == other.m_height))) ;
    }

    bool Dimension2Df::operator!=(const Dimension2Df& other) const {
        return !(*this == other) ;
    }

    Dimension2Df operator+(const Dimension2Df& a, const Dimension2Df& b) {
        return Dimension2Df(
            a.width() + b.width(),
            a.height() + b.height()
        ) ;
    }

    Dimension2Df operator-(const Dimension2Df& a, const Dimension2Df& b) {
        return Dimension2Df(
            a.width() - b.width(),
            a.height() - b.height()
        ) ;
    }

    Dimension2Df operator*(const Dimension2Df& d, const Scalar coeff) {
        return Dimension2Df(
            d.width() * coeff,
            d.height() * coeff
        ) ;
    }

    Dimension2Df operator/(const Dimension2Df& d, const Scalar coeff) {
        return Dimension2Df(
            d.width() / coeff,
            d.height() / coeff
        ) ;
    }

    std::ostream& operator<<(std::ostream& s, const Dimension2Df& p) {
        s << "Dimension2Df {" <<
                                 p.width() << "," <<
                                 p.height() <<
                           "}" ;
        return s ;
    }
} ;
