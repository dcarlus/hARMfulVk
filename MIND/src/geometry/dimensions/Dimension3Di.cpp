#include "harmful/mind/geometry/dimensions/Dimension3Di.hpp"
#include "harmful/mind/geometry/dimensions/Dimension2Df.hpp"
#include <cstdlib>

namespace Mind {
    Dimension3Di::Dimension3Di(
        const uint32_t width,
        const uint32_t height,
        const uint32_t depth
    ) : m_width(width),
        m_height(height),
        m_depth(depth) {}

    uint32_t Dimension3Di::width() const {
        return m_width ;
    }

    uint32_t Dimension3Di::height() const {
        return m_height ;
    }

    uint32_t Dimension3Di::depth() const {
        return m_depth ;
    }

    void Dimension3Di::setWidth(const uint32_t width) {
        m_width = width ;
    }

    void Dimension3Di::setHeight(const uint32_t height) {
        m_height = height ;
    }

    void Dimension3Di::setDepth(const uint32_t depth) {
        m_depth = depth ;
    }

    void Dimension3Di::set(
        const uint32_t width,
        const uint32_t height,
        const uint32_t depth
    ) {
        m_width = width ;
        m_height = height ;
        m_depth = depth ;
    }

    Dimension3Di::operator Dimension2Di() {
        return Dimension2Di(m_width, m_height) ;
    }


    Dimension3Di& Dimension3Di::operator+=(Dimension3Di& other) {
        m_width += other.m_width ;
        m_height += other.m_height ;
        m_depth += other.m_depth ;
        return *this ;
    }

    Dimension3Di& Dimension3Di::operator-=(Dimension3Di& other) {
        m_width = (other.m_width > m_width) ? 0 : m_width - other.m_width ;
        m_height = (other.m_height > m_height) ? 0 : m_height - other.m_height ;
        m_depth = (other.m_depth > m_depth) ? 0 : m_depth - other.m_depth ;

        return *this ;
    }

    Dimension3Di& Dimension3Di::operator*=(const uint32_t coeff) {
        m_width *= coeff ;
        m_height *= coeff ;
        m_depth *= coeff ;
        return *this ;
    }

    Dimension3Di& Dimension3Di::operator/=(const uint32_t coeff) {
        m_width /= coeff ;
        m_height /= coeff ;
        m_depth /= coeff ;
        return *this ;
    }

    bool Dimension3Di::operator==(const Dimension3Di& other) const {
        return ((this == &other) ||
                        ((m_width == other.m_width)
                            && (m_height == other.m_height)
                            && (m_depth == other.m_depth))) ;
    }

    bool Dimension3Di::operator!=(const Dimension3Di& other) const {
        return !(*this == other) ;
    }

    Dimension3Di operator+(const Dimension3Di& a, const Dimension3Di& b) {
        return Dimension3Di(
            a.width() + b.width(),
            a.height() + b.height(),
            a.depth() + b.depth()
        ) ;
    }

    Dimension3Di operator-(const Dimension3Di& a, const Dimension3Di& b) {
        return Dimension3Di(
            a.width() - b.width(),
            a.height() - b.height(),
            a.depth() - b.depth()
        ) ;
    }

    Dimension3Di operator*(const Dimension3Di& d, const uint32_t coeff) {
        return Dimension3Di(
            d.width() * coeff,
            d.height() * coeff,
            d.depth() * coeff
        ) ;
    }

    Dimension3Di operator/(const Dimension3Di& d, const uint32_t coeff) {
        return Dimension3Di(
            d.width() / coeff,
            d.height() / coeff,
            d.depth() / coeff
        ) ;
    }

    std::ostream& operator<<(std::ostream& s, const Dimension3Di& p) {
        s << "Dimension3Di {" <<
                                 p.width() << "," <<
                                 p.height() << "," <<
                                 p.depth() <<
                           "}" ;
        return s ;
    }
} ;
