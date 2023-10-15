#ifndef __DOOM_NUMBER_LITERALS__
#define __DOOM_NUMBER_LITERALS__

#include <cstdint>

inline constexpr uint8_t operator "" _uchar(unsigned long long int arg) noexcept {
    return static_cast<uint8_t>(arg) ;
}

inline constexpr uint16_t operator "" _ushort(unsigned long long int arg) noexcept {
    return static_cast<uint16_t>(arg) ;
}

#endif
