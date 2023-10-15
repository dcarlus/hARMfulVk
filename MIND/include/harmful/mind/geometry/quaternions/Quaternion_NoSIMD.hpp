inline Quaternion::Quaternion() : Quaternion(0.f, 0.f, 0.f, 0.f) {}

inline Quaternion::Quaternion(
    const Scalar x,
    const Scalar y,
    const Scalar z,
    const Scalar w
) {
    m_values[Axis::X] = x ;
    m_values[Axis::Y] = y ;
    m_values[Axis::Z] = z ;
    m_values[Axis::W] = w ;
}

inline Quaternion::Quaternion(
    const Scalar roll,
    const Scalar pitch,
    const Scalar yaw
) {
    from(roll, pitch, yaw) ;
}

inline Quaternion::Quaternion(const Matrix3x3f& matrix) {
    from(matrix) ;
}

inline Quaternion::Quaternion(const Vector3f& vector, const Scalar radAngle) {
    from(vector, radAngle) ;
}

inline Quaternion::Quaternion(
    const Vector3f& xAxis,
    const Vector3f& yAxis,
    const Vector3f& zAxis
) {
    from(xAxis, yAxis, zAxis) ;
}

inline Scalar Quaternion::dot(const Quaternion& other) const {
    return (m_values[Axis::X] * other.m_values[Axis::X]) +
            (m_values[Axis::Y] * other.m_values[Axis::Y]) +
            (m_values[Axis::Z] * other.m_values[Axis::Z]) +
            (m_values[Axis::W] * other.m_values[Axis::W]) ;
}

inline Scalar Quaternion::norm() const {
    return std::sqrt(
        (m_values[Axis::X] * m_values[Axis::X]) +
        (m_values[Axis::Y] * m_values[Axis::Y]) +
        (m_values[Axis::Z] * m_values[Axis::Z]) +
        (m_values[Axis::W] * m_values[Axis::W])
    ) ;
}

inline Scalar Quaternion::normalize() {
    Scalar length = norm() ;
    *this *= (1.f / length) ;
    return length ;
}

inline bool Quaternion::closeTo(
    const Quaternion& other,
    const Scalar radiansEpsilon
) const {
     Scalar distance = this -> dot(other) ;
     Scalar angle = std::acos((2.f * distance * distance) - 1.f) ;
     return std::abs(angle) <= radiansEpsilon ;
}

inline void Quaternion::swap(Quaternion& other) {
    std::swap(m_values[Axis::X], other.m_values[Axis::X]) ;
    std::swap(m_values[Axis::Y], other.m_values[Axis::Y]) ;
    std::swap(m_values[Axis::Z], other.m_values[Axis::Z]) ;
    std::swap(m_values[Axis::W], other.m_values[Axis::W]) ;
}

inline Scalar Quaternion::operator[](const Axis axis) const {
    return m_values[axis] ;
}

inline Scalar& Quaternion::operator[](const Axis axis) {
    return m_values[axis] ;
}

inline Quaternion& Quaternion::operator+=(const Quaternion& other) {
    size_t axes = m_values.size() ;
    for (size_t axis = 0 ; axis < axes ; axis++) {
        m_values[axis] += other.m_values[axis] ;
    }
    return *this ;
}

inline Quaternion Quaternion::operator+(const Quaternion& other) const {
    Quaternion tmp ;

    size_t axes = m_values.size() ;
    for (size_t axis = 0 ; axis < axes ; axis++) {
        tmp.m_values[axis] = m_values[axis] + other.m_values[axis] ;
    }

    return tmp ;
}

inline Quaternion& Quaternion::operator-=(const Quaternion& other) {
    size_t axes = m_values.size() ;
    for (size_t axis = 0 ; axis < axes ; axis++) {
        m_values[axis] -= other.m_values[axis] ;
    }
    return *this ;
}

inline Quaternion Quaternion::operator-(const Quaternion& other) const {
    Quaternion tmp ;

    size_t axes = m_values.size() ;
    for (size_t axis = 0 ; axis < axes ; axis++) {
        tmp.m_values[axis] = m_values[axis] - other.m_values[axis] ;
    }

    return tmp ;
}

inline Quaternion Quaternion::operator-() const {
    Quaternion tmp ;

    size_t axes = m_values.size() ;
    for (size_t axis = 0 ; axis < axes ; axis++) {
        tmp.m_values[axis] = -m_values[axis] ;
    }

    return tmp ;
}

inline Quaternion& Quaternion::operator*=(const Scalar scalar) {
    size_t axes = m_values.size() ;
    for (size_t axis = 0 ; axis < axes ; axis++) {
        m_values[axis] *= scalar ;
    }
    return *this ;
}

inline Quaternion Quaternion::operator*(const Scalar scalar) const {
    Quaternion tmp ;

    size_t axes = m_values.size() ;
    for (size_t axis = 0 ; axis < axes ; axis++) {
        tmp.m_values[axis] = m_values[axis] * scalar ;
    }

    return tmp ;
}

inline bool Quaternion::operator==(const Quaternion& other) const {
    return (m_values[Axis::X] == other.m_values[Axis::X]) &&
                (m_values[Axis::Y] == other.m_values[Axis::Y]) &&
                (m_values[Axis::Z] == other.m_values[Axis::Z]) &&
                (m_values[Axis::W] == other.m_values[Axis::W]) ;
}

inline bool Quaternion::operator!=(const Quaternion& other) const {
    return !(*this == other) ;
}

inline std::ostream& operator<<(std::ostream& s, const Quaternion& p) {
    s << "Quaternion: "
        << p.m_values[Quaternion::Axis::X] << ", "
        << p.m_values[Quaternion::Axis::Y] << ", "
        << p.m_values[Quaternion::Axis::Z] << ", "
        << p.m_values[Quaternion::Axis::W]
    << std::endl ;
    return s ;
}
