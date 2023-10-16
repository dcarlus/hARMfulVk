inline Quaternion::Quaternion(const SIMD::Vector4f& values) : m_values(values) {}

inline Quaternion::Quaternion(
    Scalar x,
    Scalar y,
    Scalar z,
    Scalar w
) {
    m_values = SIMD::Vector4f(x, y, z, w) ;
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

inline Quaternion::Quaternion(const Vector3f& vector, Scalar radAngle) {
    from(vector, radAngle) ;
}

inline Scalar Quaternion::dot(const Quaternion& other) const {
    return m_values.dot(other.m_values) ;
}

inline Scalar Quaternion::norm() const {
    return m_values.norm() ;
}

inline Scalar Quaternion::normalize() {
    Scalar length = norm() ;
    m_values /= length ;
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
    std::swap(m_values, other.m_values) ;
}

inline Scalar Quaternion::operator[](Axis axis) const {
    return m_values[axis] ;
}

inline Scalar& Quaternion::operator[](Axis axis) {
    return m_values[axis] ;
}

inline Quaternion& Quaternion::operator+=(const Quaternion& other) {
    m_values += other.m_values ;
    return *this ;
}

inline Quaternion Quaternion::operator+(const Quaternion& other) const {
    auto copyValues = m_values ;
    return Quaternion(copyValues + other.m_values) ;
}

inline Quaternion& Quaternion::operator-=(const Quaternion& other) {
    m_values -= other.m_values ;
    return *this ;
}

inline Quaternion Quaternion::operator-(const Quaternion& other) const {
    auto copyValues = m_values ;
    return Quaternion(copyValues - other.m_values) ;
}

inline Quaternion Quaternion::operator-() const {
    auto inversedValues = -m_values ;
    return Quaternion(inversedValues) ;
}

inline Quaternion& Quaternion::operator*=(Scalar scalar) {
    m_values *= scalar ;
    return *this ;
}

inline Quaternion Quaternion::operator*(Scalar scalar) const {
    return Quaternion(m_values * scalar) ;
}

inline bool Quaternion::operator==(const Quaternion& other) const {
    SIMD::Vector4f::Mask areEqual = (m_values == other.m_values) ;
    return (areEqual.get(0)
                && areEqual.get(1)
                && areEqual.get(2)
                && areEqual.get(3)
    ) ;
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
