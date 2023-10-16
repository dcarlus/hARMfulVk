#include "harmful/mind/geometry/rectangles/Rectangle2Df.hpp"
#include "harmful/mind/Math.hpp"
#include <algorithm>

namespace Mind {
    Rectangle2Df::Rectangle2Df() : Rectangle2Df(0.f, 0.f, 0.f, 0.f, false) {}

    Rectangle2Df::Rectangle2Df(
        const Point2Df& location,
        const Dimension2Df& size,
        const bool centered
    ) : Rectangle2Df(
            location.get(Point2Df::Axis::X),
            location.get(Point2Df::Axis::Y),
            size.width(),
            size.height(),
            centered
        ) {}

    Rectangle2Df::Rectangle2Df(
        const Scalar x,
        const Scalar y,
        const Scalar w,
        const Scalar h,
        const bool centered
    ) : m_isCentered(centered),
        m_hasChanged(true),
        m_size(w, h)
    {
        m_size = Dimension2Df(w, h) ;

        if (centered) {
            Scalar halfWidth = w / 2.f ;
            Scalar halfHeight = h / 2.f ;
            m_bottomLeftCorner = Point2Df(x - halfWidth, y - halfHeight) ;
        }
        else {
            m_bottomLeftCorner = Point2Df(x, y) ;
        }

        computeMaxPoint() ;
    }

    Rectangle2Df::Rectangle2Df(
        const Point2Df& p1,
        const Point2Df& p2
    ) : Rectangle2Df(
            p1.get(Point2Df::Axis::X),
            p1.get(Point2Df::Axis::Y),
            p2.get(Point2Df::Axis::X),
            p2.get(Point2Df::Axis::Y)
        ) {}

    Rectangle2Df::Rectangle2Df(
        const Scalar x1,
        const Scalar y1,
        const Scalar x2,
        const Scalar y2
    ) : m_isCentered(false),
        m_hasChanged(false) {
        std::pair<Scalar, Scalar> minMax_X = std::minmax(x1, x2) ;
        std::pair<Scalar, Scalar> minMax_Y = std::minmax(y1, y2) ;

        m_bottomLeftCorner = Point2Df(minMax_X.first, minMax_Y.first) ;
        m_upRightCorner = Point2Df(minMax_X.second, minMax_Y.second) ;
        // m_upRightCorner = Point2Df(minMax_X.second, minMax_Y.first) ;
        m_size = Dimension2Df(minMax_X.second - minMax_X.first,
                                minMax_Y.second - minMax_Y.first) ;
    }

    void Rectangle2Df::translate(
        const Scalar x,
        const Scalar y
    ) {
        setAt(m_bottomLeftCorner.get(Point2Df::Axis::X) + x, m_bottomLeftCorner.get(Point2Df::Axis::Y) + y) ;
    }

    bool Rectangle2Df::contains(
        const Scalar x,
        const Scalar y
    ) {
        computeMaxPoint() ;
        return ((x >= m_bottomLeftCorner.get(Point2Df::Axis::X)) && (x <= m_upRightCorner.get(Point2Df::Axis::X))
                    && (y >= m_bottomLeftCorner.get(Point2Df::Axis::Y)) && (y <= m_upRightCorner.get(Point2Df::Axis::Y))) ;
    }

    bool Rectangle2Df::contains(const Point2Df& point) {
        computeMaxPoint() ;

        Scalar x = point.get(Point2Df::Axis::X) ;
        Scalar y = point.get(Point2Df::Axis::Y) ;
        return (
                ((x >= bottomLeftCornerX()) && (x <= upRightCornerX()))
                 &&
                ((y >= bottomLeftCornerY()) && (y <= upRightCornerY()))
               ) ;
    }

    bool Rectangle2Df::contains(
        const Scalar x,
        const Scalar y,
        const Scalar w,
        const Scalar h
    ) {
        Scalar x2 = x + w ;
        Scalar y2 = y + h ;
        return (contains(x, y) && contains(x2, y2)) ;
    }

    bool Rectangle2Df::contains(Rectangle2Df& boundaries) {
        return contains(
            boundaries.bottomLeftCornerX(),
            boundaries.bottomLeftCornerY(),
            boundaries.width(),
            boundaries.height()
        ) ;
    }

    bool Rectangle2Df::intersects(
        const Scalar x,
        const Scalar y,
        const Scalar w,
        const Scalar h
    ) {
        if (isEmpty() || ((w == 0.f) || (h == 0.f))) {
            return false ;
        }

        Scalar xThis = bottomLeftCornerX() ;
        Scalar yThis = bottomLeftCornerY() ;
        Scalar x2This = upRightCornerX() ;
        Scalar y2This = upRightCornerY() ;

        return (
                ((x + w) > xThis)
                    && ((y + h) > yThis)
                    && (x < x2This)
                    && (y < y2This)
               ) ;
    }

    bool Rectangle2Df::intersects(const Line2Df& line) {
        Scalar x = std::min(line.startX(), line.endX()) ;
        Scalar y = std::min(line.startY(), line.endY()) ;
        Scalar w = std::abs(line.endX() - line.startX()) ;
        Scalar h = std::abs(line.endY() - line.startY()) ;
        return intersects(x, y, w, h) ;
    }

    bool Rectangle2Df::intersects(const Rectangle2Df& boundaries) {
        return intersects(
            ((Rectangle2Df)boundaries).bottomLeftCornerX(),
            ((Rectangle2Df)boundaries).bottomLeftCornerY(),
            ((Rectangle2Df)boundaries).width(),
            ((Rectangle2Df)boundaries).height()
        ) ;
    }

    int8_t Rectangle2Df::position(Scalar x, Scalar y) {
        char pos = 0 ;

        if (width() <= 0) {
            pos = PointOnLeft | PointOnRight ;
        }
        else if (x < bottomLeftCornerX()) {
            pos = PointOnLeft ;
        }
        else if (x > upRightCornerX()) {
            pos = PointOnRight ;
        }

        if (height() <= 0) {
            return pos | PointAbove | PointBelow ;
        }
        else if (y > upRightCornerY()) {
            return pos | PointAbove ;
        }
        else if (y < bottomRightCornerY()) {
            return pos | PointBelow ;
        }

        return pos ;
    }

    int8_t Rectangle2Df::position(const Point2Df& p) {
        return position(p.get(Point2Df::Axis::X), p.get(Point2Df::Axis::Y)) ;
    }

    Scalar Rectangle2Df::upLeftCornerX() {
        return m_bottomLeftCorner.get(Point2Df::Axis::X) ;
    }

    Scalar Rectangle2Df::upLeftCornerY() {
        computeMaxPoint() ;
        return m_upRightCorner.get(Point2Df::Axis::Y) ;
    }

    Scalar Rectangle2Df::upRightCornerX() {
        computeMaxPoint() ;
        return m_upRightCorner.get(Point2Df::Axis::X) ;
    }

    Scalar Rectangle2Df::upRightCornerY()  {
        computeMaxPoint() ;
        return m_upRightCorner.get(Point2Df::Axis::Y) ;
    }

    Scalar Rectangle2Df::bottomLeftCornerX() const {
        return m_bottomLeftCorner.get(Point2Df::Axis::X) ;
    }

    Scalar Rectangle2Df::bottomLeftCornerY() const {
        return m_bottomLeftCorner.get(Point2Df::Axis::Y) ;
    }

    Scalar Rectangle2Df::bottomRightCornerX() {
        computeMaxPoint() ;
        return m_upRightCorner.get(Point2Df::Axis::X) ;
    }

    Scalar Rectangle2Df::bottomRightCornerY() {
        return m_bottomLeftCorner.get(Point2Df::Axis::Y) ;
    }

    const Dimension2Df& Rectangle2Df::size() const {
        return m_size ;
    }

    Scalar Rectangle2Df::width() const {
        return m_size.width() ;
    }

    Scalar Rectangle2Df::height() const {
        return m_size.height() ;
    }

    bool Rectangle2Df::isEmpty() const {
        return ((m_size.width() == 0.f) || (m_size.height() == 0.f)) ;
    }

    void Rectangle2Df::computeMaxPoint() {
        if (m_hasChanged) {
            m_upRightCorner.set(
                m_bottomLeftCorner.get(Point2Df::Axis::X) + m_size.width(),
                m_bottomLeftCorner.get(Point2Df::Axis::Y) + m_size.height()
            ) ;
            m_hasChanged = false ;
        }
    }

    void Rectangle2Df::setX(const Scalar x) {
        if (m_isCentered) {
            m_bottomLeftCorner.set(Point2Df::Axis::X, x - (width() / 2.f)) ;
        }
        else {
            m_bottomLeftCorner.set(Point2Df::Axis::X, x) ;
        }
        m_hasChanged = true ;
    }

    void Rectangle2Df::setY(const Scalar y) {
        if (m_isCentered) {
            m_bottomLeftCorner.set(Point2Df::Axis::Y, y - (height() / 2.f)) ;
        }
        else {
            m_bottomLeftCorner.set(Point2Df::Axis::Y, y) ;
        }
        m_hasChanged = true ;
    }

    void Rectangle2Df::setAt(const Scalar x, const Scalar y) {
        if (m_isCentered) {
            m_bottomLeftCorner.set(Point2Df::Axis::X, x - (width() / 2.f)) ;
            m_bottomLeftCorner.set(Point2Df::Axis::Y, y - (height() / 2.f)) ;
        }
        else {
            m_bottomLeftCorner.set(Point2Df::Axis::X, x) ;
            m_bottomLeftCorner.set(Point2Df::Axis::Y, y) ;
        }
        m_hasChanged = true ;
    }

    void Rectangle2Df::setWidth(const Scalar w) {
        if (m_isCentered) {
            Scalar currentWidth = width() ;
            Scalar halfWidthDiff = (currentWidth - w) / 2.f ;
            Scalar currentBottomLeftX = bottomLeftCornerX() ;
            m_bottomLeftCorner.set(Point2Df::Axis::X, currentBottomLeftX + halfWidthDiff) ;
            m_size.setWidth(w) ;
        }
        else {
            m_size.setWidth(w) ;
        }
        m_hasChanged = true ;
    }

    void Rectangle2Df::setHeight(const Scalar h) {
        if (m_isCentered) {
            Scalar currentHeight = height() ;
            Scalar halfHeightDiff = (currentHeight - h) / 2.f ;
            Scalar currentBottomLeftY = bottomLeftCornerY() ;
            m_bottomLeftCorner.set(Point2Df::Axis::Y, currentBottomLeftY + halfHeightDiff) ;
            m_size.setHeight(h) ;
        }
        else {
            m_size.setHeight(h) ;
        }
        m_hasChanged = true ;
    }

    Rectangle2Df& Rectangle2Df::operator=(const Rectangle2Df& other) {
        if (this != &other) {
            m_bottomLeftCorner = other.m_bottomLeftCorner ;
            m_size = other.m_size ;
            m_hasChanged = true ;
        }

        return *this ;
    }

    Rectangle2Df& Rectangle2Df::operator+=(Point2Df& other) {
        *this = (*this) + other ;
        return *this ;
    }

    Rectangle2Df& Rectangle2Df::operator+=(Rectangle2Df& other) {
        *this = (*this) + other ;
        return *this ;
    }

    bool Rectangle2Df::operator==(const Rectangle2Df& other) const {
        return ((this == &other)
                    || ((m_bottomLeftCorner == other.m_bottomLeftCorner)
                            && (m_size == other.m_size))) ;
    }

    bool Rectangle2Df::operator!=(const Rectangle2Df& other) const {
        return !(*this == other) ;
    }

    Rectangle2Df operator+(Rectangle2Df& r, Point2Df& p) {
        if (r.contains(p)) {
            return r ;
        }
        else {
            Scalar x1 = std::min(r.bottomLeftCornerX(), p.get(Point2Df::Axis::X)) ;
            Scalar y1 = std::min(r.bottomLeftCornerY(), p.get(Point2Df::Axis::Y)) ;
            Scalar x2 = std::max(r.upRightCornerX(), p.get(Point2Df::Axis::X)) ;
            Scalar y2 = std::max(r.upRightCornerY(), p.get(Point2Df::Axis::Y)) ;
            return Rectangle2Df(x1, y1, x2, y2) ;
        }
    }

    Rectangle2Df operator+(Rectangle2Df& r1, Rectangle2Df& r2) {
        if (r1.contains(r2)) {
            return r1 ;
        }
        else if (r2.contains(r1)) {
            return r2 ;
        }
        else {
            Scalar x1 = std::min(r1.bottomLeftCornerX(), r2.bottomLeftCornerX()) ;
            Scalar y1 = std::min(r1.bottomLeftCornerY(), r2.bottomLeftCornerY()) ;
            Scalar x2 = std::max(r1.upRightCornerX(), r2.upRightCornerX()) ;
            Scalar y2 = std::max(r1.upRightCornerY(), r2.upRightCornerY()) ;
            return Rectangle2Df(x1, y1, x2, y2) ;
        }
    }

    std::ostream& operator<<(std::ostream& s, const Rectangle2Df& r) {
        s << "Rectangle2Df ("
                    << ((Rectangle2Df)r).bottomLeftCornerX()
                    << ","
                    << ((Rectangle2Df)r).bottomLeftCornerY()
                 << " | "
                    << ((Rectangle2Df)r).upRightCornerX()
                    << ","
                    << ((Rectangle2Df)r).upRightCornerY()
                 << ")" << std::endl ;
        return s ;
    }
} ;
