#include "harmful/doom/DOOMStrings.hpp"

/**
 * Tag to be detected when using xgettext on this file.
 * @param  str The string to be detected by xgettext.
 * @return     The same string as input.
 */
#define i18n(str) str

namespace Doom {
    namespace Texts {
        const std::string LogSys_NotInitialized     = i18n("The log system has not been initialized.") ;
        const std::string LogSys_AlreadyInitialized = i18n("The log system has already been initialized.") ;

        /* Keep the space at the end of the string (filepath printed after). */
        const std::string File_NotOpened            = i18n("Unable to open file at ") ;

        /* Keep the space at the end of the string (text printed after). */
        const std::string Profiler_SessionIDTooHigh = i18n("The session ID is too high for ") ;
    } ;
} ;
