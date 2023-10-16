#include "harmful/mind/geometry/dimensions/Dimension2Di.hpp"
#include <cmath>

namespace Mind {
    Dimension2Di::Dimension2Di(
        const uint32_t width,
        const uint32_t height
    ): m_width(width),
       m_height(height) {}

    uint32_t Dimension2Di::width() const {
        return m_width ;
    }

    uint32_t Dimension2Di::height() const {
        return m_height ;
    }

    void Dimension2Di::setWidth(const uint32_t width) {
        m_width = width ;
    }

    void Dimension2Di::setHeight(const uint32_t height) {
        m_height = height ;
    }

    void Dimension2Di::set(const uint32_t width, const uint32_t height) {
        m_width = width ;
        m_height = height ;
    }

    Dimension2Di& Dimension2Di::operator+=(Dimension2Di& other) {
        m_width += other.m_width ;
        m_height += other.m_height ;
        return *this ;
    }

    Dimension2Di& Dimension2Di::operator-=(Dimension2Di& other) {
        m_width = (other.m_width > m_width) ? 0 : m_width - other.m_width ;
        m_height = (other.m_height > m_height) ? 0 : m_height - other.m_height ;

        return *this ;
    }

    Dimension2Di& Dimension2Di::operator*=(const uint32_t coeff) {
        m_width *= coeff ;
        m_height *= coeff ;
        return *this ;
    }

    Dimension2Di& Dimension2Di::operator/=(const uint32_t coeff) {
        m_width /= coeff ;
        m_height /= coeff ;
        return *this ;
    }

    bool Dimension2Di::operator==(const Dimension2Di& other) const {
        return ((this == &other) ||
                    ((m_width == other.m_width) && (m_height == other.m_height))) ;
    }

    bool Dimension2Di::operator!=(const Dimension2Di& other) const {
        return !(*this == other) ;
    }

    Dimension2Di operator+(const Dimension2Di& a, const Dimension2Di& b) {
        return Dimension2Di(
            a.width() + b.width(),
            a.height() + b.height()
        ) ;
    }

    Dimension2Di operator-(const Dimension2Di& a, const Dimension2Di& b) {
        return Dimension2Di(
            a.width() - b.width(),
            a.height() - b.height()
        ) ;
    }

    Dimension2Di operator*(const Dimension2Di& d, const uint32_t coeff) {
        return Dimension2Di(
            d.width() * coeff,
            d.height() * coeff
        ) ;
    }

    Dimension2Di operator/(const Dimension2Di& d, const uint32_t coeff) {
        return Dimension2Di(
            d.width() / coeff,
            d.height() / coeff
        ) ;
    }

    std::ostream& operator<<(std::ostream& s, const Dimension2Di& p) {
        s << "Dimension2Di {" <<
                                 p.width() << "," <<
                                 p.height() <<
                           "}" ;
        return s ;
    }
} ;
