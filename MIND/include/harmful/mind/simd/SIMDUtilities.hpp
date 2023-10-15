#ifndef __MIND__SIMDVECTOR_UTILITIES__
#define __MIND__SIMDVECTOR_UTILITIES__

#define BoolToUInt32(value) uint32_t(-int32_t(value))
#define BoolToFloat(value)  static_cast<float>(uint32_t(-int32_t(value)))

#endif
