#include "MINDStrings.hpp"

/**
 * Tag to be detected when using xgettext on this file.
 * @param  str The string to be detected by xgettext.
 * @return     The same string as input.
 */
#define i18n(str) str

namespace Mind {
    namespace Texts {
        const std::string Quaternion_TimeMustBeGreaterOrEqualZero = i18n("Time must be greater or equal to zero.") ;
        const std::string Quaternion_TimeMustBeLowerOrEqualOne    = i18n("Time must be lower or equal to one.") ;
    } ;
} ;
