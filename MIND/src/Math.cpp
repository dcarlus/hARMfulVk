#include "Math.hpp"

namespace Mind {
    namespace Math {
        bool isNegative(const Scalar value) {
            // Float structure :
            // [ S | EEEEEEEE | FFFFFFFFFFFFFFFFFFFFFFF ]
            // -> 1 bit for Sign (S)
            // -> 8 bits for Exponent (E)
            // -> 23 bits for Fraction (F)
            // Convert the extended sign vector to a Mask (containing either 0x00000000
            // or 0xFFFFFFFF).
            auto removedSignBitPtr = reinterpret_cast<const uint32_t*>(&value) ;
            return ((*removedSignBitPtr) >> 31) & 1 ;
        }

        bool isNaN(const Scalar value) {
            // Float structure :
            // [ S | EEEEEEEE | FFFFFFFFFFFFFFFFFFFFFFF ]
            // -> 1 bit for Sign (S)
            // -> 8 bits for Exponent (E)
            // -> 23 bits for Fraction (F)
            const uint32_t MaskExponent = 0xFF000000 ;
            const uint32_t MaskFraction = ~MaskExponent ;

            auto removedSignBitPtr = reinterpret_cast<const uint32_t*>(&value) ;
            uint32_t removedSignBit = (*removedSignBitPtr) << 1 ;
            uint32_t extractedExponent = removedSignBit & MaskExponent ;
            uint32_t extractedFraction = removedSignBit & MaskFraction ;
            return ((extractedExponent == MaskExponent) & (extractedFraction != 0)) ;
        }

        bool isInf(const Scalar value) {
            // Float structure :
            // [ S | EEEEEEEE | FFFFFFFFFFFFFFFFFFFFFFF ]
            // -> 1 bit for Sign (S)
            // -> 8 bits for Exponent (E)
            // -> 23 bits for Fraction (F)
            const uint32_t MaskInfiniteExponent = 0xFF000000 ;

            auto removedSignBitPtr = reinterpret_cast<const uint32_t*>(&value) ;
            uint32_t removedSignBit = (*removedSignBitPtr) << 1 ;
            return (removedSignBit == MaskInfiniteExponent) ;
        }

        bool equal(
            const Scalar a,
            const Scalar b,
            const Scalar epsilon
        ) {
            Scalar diff = std::abs(a - b) ;
            return diff < epsilon ;
        }

        unsigned int lowClosestPower2(const unsigned int value) {
            static const auto Log2 = std::log(2.) ;
            auto logValue = std::log(static_cast<double>(value)) ;
            auto power2 = std::pow(2., std::floor(logValue / Log2)) ;
            return static_cast<unsigned int>(power2) ;
        }

        unsigned int closestPower2(const unsigned int value) {
            static const auto Log2 = std::log(2.) ;
            auto logValue = std::log(static_cast<double>(value)) ;
            auto power2 = std::pow(2., std::round(logValue / Log2)) ;
            return static_cast<unsigned int>(power2) ;
        }

        unsigned int highClosestPower2(const unsigned int value) {
            static const auto Log2 = std::log(2.) ;
            auto logValue = std::log(static_cast<double>(value)) ;
            auto power2 = std::pow(2., std::ceil(logValue / Log2)) ;
            return static_cast<unsigned int>(power2) ;
        }
    } ;
} ;
