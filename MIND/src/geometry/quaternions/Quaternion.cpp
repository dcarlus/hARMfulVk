#include "harmful/mind/geometry/quaternions/Quaternion.hpp"
#include "harmful/mind/Math.hpp"

#ifdef USE_SIMD // for compilations where SSE or NEON are available

namespace Mind {
    const Scalar Quaternion::Epsilon = static_cast<Scalar>(1e-3) ;
    const Quaternion Quaternion::Zero = Quaternion() ;
    const Quaternion Quaternion::Identity = Quaternion(0.f, 0.f, 0.f, 1.f) ;
    const SIMD::Vector4f Quaternion::VectorPartExtractor = SIMD::Vector4f(1.f, 1.f, 1.f, 0.f) ;

    Quaternion::Quaternion(
        const Vector3f& xAxis,
        const Vector3f& yAxis,
        const Vector3f& zAxis
    ) {
        from(xAxis, yAxis, zAxis) ;
    }

    Quaternion Quaternion::inverse() const {
        Scalar squaredLength = this -> dot(*this) ;
        if (squaredLength > 0.f) {
            Scalar invertedSquaredLength = 1.f / squaredLength ;
            SIMD::Vector4f factor(
                -invertedSquaredLength,
                -invertedSquaredLength,
                -invertedSquaredLength,
                 invertedSquaredLength
            ) ;
            return Quaternion(m_values * factor) ;
        }
        else {
            return Quaternion::Zero ;
        }
    }

    Quaternion Quaternion::exp() const {
        SIMD::Vector4f vectorPart = m_values * VectorPartExtractor ;
        Scalar normV = vectorPart.norm() ;

        Scalar angleSin = std::sin(normV) ;
        Scalar angleCos = std::cos(normV) ;

        Scalar w = m_values[Axis::W] ;
        Scalar expW = std::exp(w) ;

        Scalar resultW ;
        // Avoid a division by zero...
        if (std::abs(normV) < Epsilon) {
            resultW = expW ;
            vectorPart *= expW ;
        }
        else {
            resultW = angleCos * expW ;
            Scalar coeff = expW * (angleSin / normV) ;
            vectorPart *= coeff ;
        }

        return Quaternion(
            vectorPart[Axis::X] ,
            vectorPart[Axis::Y],
            vectorPart[Axis::Z],
            resultW
        ) ;
    }

    Quaternion Quaternion::ln() const {
        Quaternion unitQuaternion = *this ;
        unitQuaternion.normalize() ;

        Scalar unitW = unitQuaternion.m_values[Axis::W] ;
        SIMD::Vector4f vectorPart = unitQuaternion.m_values * VectorPartExtractor ;

        if (std::abs(vectorPart[Axis::W]) < 1.f) {
            Scalar normV = vectorPart.norm() ;
            Scalar angle = std::atan2(normV, unitW) ;

            Scalar angleSin = std::sin(angle) ;
            if (std::abs(angleSin) >= Epsilon) {
                Scalar coeff = angle / angleSin ;
                vectorPart *= coeff ;
            }
        }

        return Quaternion(
            vectorPart[Axis::X],
            vectorPart[Axis::Y],
            vectorPart[Axis::Z],
            vectorPart[Axis::W]
        ) ;
    }

    Quaternion Quaternion::slerp(
        Scalar time,
        const Quaternion& from,
        const Quaternion& to,
        bool shortestPath
    ) {
        Scalar cos = from.dot(to) ;
        Quaternion usedTo ;

        if ((cos < 0.f) && shortestPath) {
            cos = -cos ;
            usedTo = -to ;
        }
        else {
            usedTo = to ;
        }

        if (std::abs(cos) < (1.f - Epsilon)) {
            // Standard case for SLERP
            Scalar sin = FastMath::sqrt(1.f - (cos * cos)) ;
            Scalar angle = std::atan2(sin, cos) ;
            Scalar invertedSin = 1.f / sin ;
            Scalar coeffFrom = std::sin((1.f - time) * angle) * invertedSin ;
            Scalar coeffTo = std::sin(time * angle) * invertedSin ;
            return (from * coeffFrom) + (usedTo * coeffTo) ;
        }
        else {
            // Two cases here that do not correspond to the standard case:
            // 1. "from" and "to" are very close, so a linerar interpolation can
            //    be done;
            // 2. "from" and "to" are close to be inverse one of the other, so
            //    there is an infinite amount of solution. To solve it, a linear
            //    interpolation is used as well.
            Quaternion result = (from * (1.f - time)) + (usedTo * time) ;
            result.normalize() ;
            return result ;
        }
    }

    Quaternion Quaternion::nlerp(
        Scalar time,
        const Quaternion& from,
        const Quaternion& to,
        bool shortestPath
    ) {
        Quaternion usedTo ;
        Quaternion result ;
        Scalar cos = from.dot(to) ;

        if ((cos < 0.f) && shortestPath) {
            usedTo = -to ;
        }
        else {
            usedTo = to ;
        }

        result = from + ((usedTo - from) * time) ;
        result.normalize() ;
        return result ;
    }

    // From Ken Shoemake's explanations on quaternions.
    // http://www.cs.ucr.edu/~vbz/resources/quatut.pdf
    void Quaternion::from(const Matrix3x3f& matrix) {
        static const int QuaternionSize = 4 ;
        Scalar quaternionValues[QuaternionSize] ;
        Scalar trace = matrix.trace() ;

        if (trace >= 0.f) {
            Scalar root = FastMath::sqrt(trace + 1.f) ;
            Scalar quartRoot = 0.5f / root ;

            m_values = SIMD::Vector4f(
                matrix.at(2,1) - matrix.at(1,2),
                matrix.at(0,2) - matrix.at(2,0),
                matrix.at(1,0) - matrix.at(0,1),
                0.5f
            ) ;

            // Multiply the values of the quaternion by their corresponding root
            // or [1/4 root].
            SIMD::Vector4f factorsSIMD(
                quartRoot,
                quartRoot,
                quartRoot,
                root
            ) ;

            m_values = m_values * factorsSIMD ;
        }
        else {
            // Shuffle axes according to the values on the diagonal of the
            // matrix.
            static Axis axes[3] = { Axis::Y, Axis::Z, Axis::X } ;
            Axis iAxis = Axis::X ;
            if (matrix.at(Axis::Y, Axis::Y) > matrix.at(iAxis, iAxis)) {
                iAxis = Axis::Y ;
            }

            if (matrix.at(Axis::Z, Axis::Z) > matrix.at(iAxis, iAxis)) {
                iAxis = Axis::Z ;
            }
            Axis jAxis = axes[iAxis] ;
            Axis kAxis = axes[jAxis] ;

            // Set the values according to the axis shuffle.
            // This avoids many possible cases with quite the same code.
            Scalar* refValues[] = {
                &quaternionValues[Axis::X],
                &quaternionValues[Axis::Y],
                &quaternionValues[Axis::Z]
            } ;

            Scalar root = matrix.at(iAxis,iAxis) - matrix.at(jAxis,jAxis) - matrix.at(kAxis,kAxis) + 1.f ;
            root = FastMath::sqrt(root) ;
            Scalar quartRoot = 0.5f / root ;
            *refValues[iAxis] = 0.5f ;
            *refValues[jAxis] = matrix.at(jAxis,iAxis) - matrix.at(iAxis,jAxis) ;
            *refValues[kAxis] = matrix.at(kAxis,iAxis) - matrix.at(iAxis,kAxis) ;
            quaternionValues[Axis::W] = matrix.at(kAxis,jAxis) - matrix.at(jAxis,kAxis) ;

            m_values = SIMD::Vector4f(
                quaternionValues[Axis::X],
                quaternionValues[Axis::Y],
                quaternionValues[Axis::Z],
                quaternionValues[Axis::W]
            ) ;

            // Multiply the values of the quaternion by their corresponding root
            // or [1/4 root].
            Scalar factors[4] ;
            factors[iAxis] = root ;
            factors[jAxis] = quartRoot ;
            factors[kAxis] = quartRoot ;
            factors[Axis::W] = quartRoot ;

            SIMD::Vector4f factorsSIMD(
                factors[Axis::X],
                factors[Axis::Y],
                factors[Axis::Z],
                factors[Axis::W]
            ) ;

            m_values = m_values * factorsSIMD ;
        }
    }

    void Quaternion::from(
        const Vector3f& xAxis,
        const Vector3f& yAxis,
        const Vector3f& zAxis
    ) {
        // Convert the vector to a rotation matrix, used then to generate the
        // quaternion values.
        Matrix3x3f rotationMatrix ;

        for (unsigned int column = 0 ; column < 3 ; ++column) {
            rotationMatrix.at(0, column) = xAxis[column] ;
            rotationMatrix.at(1, column) = yAxis[column] ;
            rotationMatrix.at(2, column) = zAxis[column] ;
        }

        from(rotationMatrix) ;
    }

    void Quaternion::from(
        const Scalar roll,
        const Scalar pitch,
        const Scalar yaw
    ) {
        Scalar halfRoll = Math::toRadians(roll) * Scalar(0.5) ;
        Scalar halfPitch = Math::toRadians(pitch) * Scalar(0.5) ;
        Scalar halfYaw = Math::toRadians(yaw) * Scalar(0.5) ;

        Scalar cosRoll = std::cos(halfRoll) ;
        Scalar cosPitch = std::cos(halfPitch) ;
        Scalar cosYaw = std::cos(halfYaw) ;

        Scalar sinRoll = std::sin(halfRoll) ;
        Scalar sinPitch = std::sin(halfPitch) ;
        Scalar sinYaw = std::sin(halfYaw) ;

        m_values = SIMD::Vector4f(
            (sinRoll * cosPitch * cosYaw) + (cosRoll * sinPitch * sinYaw),
            (cosRoll * sinPitch * cosYaw) - (sinRoll * cosPitch * sinYaw),
            (cosRoll * cosPitch * sinYaw) - (sinRoll * sinPitch * cosYaw),
            (cosRoll * cosPitch * cosYaw) + (sinRoll * sinPitch * sinYaw)
        ) ;
    }

    // From Ken Shoemake's explanations on quaternions.
    // http://www.cs.ucr.edu/~vbz/resources/quatut.pdf
    void Quaternion::from(const Vector3f& vector, Scalar radAngle) {
        Scalar halfAngle = radAngle * 0.5f ;
        Scalar halfAngleSinus = std::sin(halfAngle) ;
        Scalar halfAngleCosinus = std::cos(halfAngle) ;

        m_values = SIMD::Vector4f(
            halfAngleSinus,
            halfAngleSinus,
            halfAngleSinus,
            halfAngleCosinus
        ) ;

        // Multiply only the vector part of the quaternion with the provided
        // vector.
        SIMD::Vector4f::Mask maskMul(true, true, true, false) ;
        SIMD::Vector4f tmp(
            vector.get(Vector3f::Axis::X),
            vector.get(Vector3f::Axis::Y),
            vector.get(Vector3f::Axis::Z),
            0.f
        ) ;
        m_values.mulIf(maskMul, tmp) ;
    }

    // From Ken Shoemake's explanations on quaternions.
    // http://www.cs.ucr.edu/~vbz/resources/quatut.pdf
    void Quaternion::to(Matrix3x3f& matrix) const {
        auto twiceValues = m_values + m_values ;
        auto twiceValuesX = twiceValues * SIMD::Vector4f(m_values[Axis::X]) ;
        auto twiceValuesY = twiceValues * SIMD::Vector4f(m_values[Axis::Y]) ;
        auto twiceValuesZ = twiceValues * SIMD::Vector4f(m_values[Axis::Z]) ;
        auto twiceValuesW = twiceValues * SIMD::Vector4f(m_values[Axis::W]) ;

        matrix.at(0,0, 1.f - (twiceValuesY[Axis::Y] + twiceValuesZ[Axis::Z])) ;
        matrix.at(0,1, twiceValuesX[Axis::Y] - twiceValuesW[Axis::Z]) ;
        matrix.at(0,2, twiceValuesX[Axis::Z] + twiceValuesW[Axis::Y]) ;

        matrix.at(1,0, twiceValuesX[Axis::Y] + twiceValuesW[Axis::Z]) ;
        matrix.at(1,1, 1.f - (twiceValuesX[Axis::X] + twiceValuesZ[Axis::Z])) ;
        matrix.at(1,2, twiceValuesY[Axis::Z] - twiceValuesW[Axis::X]) ;

        matrix.at(2,0, twiceValuesX[Axis::Z] - twiceValuesW[Axis::Y]) ;
        matrix.at(2,1, twiceValuesY[Axis::Z] + twiceValuesW[Axis::X]) ;
        matrix.at(2,2, 1.f - (twiceValuesX[Axis::X] + twiceValuesY[Axis::Y])) ;
    }

    void Quaternion::to(Vector3f& vector, Scalar& radAngle) const {
        // Get the length of the vector part of the quaternion (x,y,z).
        SIMD::Vector4f tmp(
            m_values[Axis::X],
            m_values[Axis::Y],
            m_values[Axis::Z],
            0.f
        ) ;

        Scalar squaredLength = (m_values * tmp).horizontalAdd() ;

        if (squaredLength > 0.) {
            // A unique solution exists.
            vector.set(
                m_values[Axis::X],
                m_values[Axis::Y],
                m_values[Axis::Z]
            ) ;
        }
        else {
            // Several solution can exist (the angle is 0 % 2xPi radians...).
            radAngle = static_cast<Scalar>(0._rad) ;
            vector.set(1.f, 0.f, 0.f) ;
        }
    }

    void Quaternion::to(
        Vector3f& xAxis,
        Vector3f& yAxis,
        Vector3f& zAxis
    ) const {
        Matrix3x3f rotationMatrix ;
        to(rotationMatrix) ;

        xAxis.set(
            rotationMatrix.at(0,0),
            rotationMatrix.at(1,0),
            rotationMatrix.at(2,0)
        ) ;

        yAxis.set(
            rotationMatrix.at(0,1),
            rotationMatrix.at(1,1),
            rotationMatrix.at(2,1)
        ) ;

        zAxis.set(
            rotationMatrix.at(0,2),
            rotationMatrix.at(1,2),
            rotationMatrix.at(2,2)
        ) ;
    }

    void Quaternion::to(
        Scalar& roll,
        Scalar& pitch,
        Scalar& yaw
    ) const {
        Scalar squaredY = m_values[Axis::Y] * m_values[Axis::Y] ;

        // Roll (x-axis rotation).
        Scalar t0 = 2.f * (m_values[Axis::W] * m_values[Axis::X] + m_values[Axis::Y] * m_values[Axis::Z]) ;
        Scalar t1 = 1.f - 2.f * (m_values[Axis::X] * m_values[Axis::X] + squaredY) ;
        roll = std::atan2(t0, t1) ;

        // Pitch (y-axis rotation).
        Scalar t2 = 2.f * (m_values[Axis::W] * m_values[Axis::Y] - m_values[Axis::Z] + m_values[Axis::X]) ;
        if (t2 > 1.f) {
            t2 = 1.f ;
        }
        else if (t2 < -1.f) {
            t2 = -1.f ;
        }
        pitch = std::asin(t2) ;

        // Yaw (z-axis rotation).
        Scalar t3 = 2.f * (m_values[Axis::W] * m_values[Axis::Z] + m_values[Axis::X] * m_values[Axis::Y]) ;
        Scalar t4 = 1.f - 2.f * (squaredY + m_values[Axis::Z] * m_values[Axis::Z]) ;
        yaw = std::atan2(t3, t4) ;
    }


    Quaternion& Quaternion::operator*=(const Quaternion& other) {
        Scalar newX ;
        Scalar newY ;
        Scalar newZ ;
        Scalar newW ;

        // Compute new X value of the curent Quaternion.
        // (x * other.w) + (y * other.z) - (z * other.y) + (w * other.x)
        {
            auto permuteOtherX = other.m_values ;
            permuteOtherX.changeSign<false, true, false, false>() ;
            permuteOtherX.permute<3,2,1,0>() ;
            newX = (m_values * permuteOtherX).horizontalAdd() ;
        }

        // Compute new Y value of the curent Quaternion.
        // (x * -other.z) + (y * other.w) + (z * other.x) - (w * other.y)
        {
            auto permuteOtherY = other.m_values ;
            permuteOtherY.permute<2,3,0,1>() ;
            permuteOtherY.changeSign<true, false, false, false>() ;
            newY = (m_values * permuteOtherY).horizontalAdd() ;
        }

        // Compute new Z value of the curent Quaternion.
        // (x * other.y) + (y * -other.x) + (z * other.w) - (w * other.z)
        {
            auto permuteOtherZ = other.m_values ;
            permuteOtherZ.permute<1,0,3,2>() ;
            permuteOtherZ.changeSign<false, true, false, false>() ;
            newZ = (m_values * permuteOtherZ).horizontalAdd() ;
        }

        // Compute new W value of the curent Quaternion.
        // (x * -other.x) + (y * other.y) + (z * -other.z) + (w * other.w)
        {
            auto permuteOtherW = other.m_values ;
            permuteOtherW.changeSign<true, true, true, false>() ;
            newW = (m_values * permuteOtherW).horizontalAdd() ;
        }

        m_values = SIMD::Vector4f(newX, newY, newZ, newW) ;
        return *this ;
    }

    Quaternion Quaternion::operator*(const Quaternion& other) const {
        Quaternion tmp(*this) ;
        tmp *= other ;
        return tmp ;
    }

    Vector3f Quaternion::operator*(const Vector3f& vec3) const {
        // Implementation from the NVidia SDK.
        Vector3f vecPartQuaternion(
            m_values[Axis::X],
            m_values[Axis::Y],
            m_values[Axis::Z]
        ) ;

        // Cross products of the quaternion vector part with the provided
        // vector.
        Vector3f uv = vecPartQuaternion.cross(vec3) ;
        Vector3f uuv = vecPartQuaternion.cross(uv) ;
        uv *= (2.f * m_values[Axis::W]) ;
        uuv *= 2.f ;

        return vec3 + uv + uuv ;
    }
}

#endif
