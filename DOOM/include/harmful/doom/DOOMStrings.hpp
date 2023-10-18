#ifndef __DOOM__STRINGS__
#define __DOOM__STRINGS__

#include <string>

#define i18n(str) str

namespace Doom {
    namespace Texts {
        static const std::string LogSys_NotInitialized = i18n("The log system has not been initialized.");
        static const std::string LogSys_AlreadyInitialized = i18n("The log system has already been initialized.");

        static const std::string File_NotOpened = i18n("Unable to open file at ");

        static const std::string Profiler_SessionIDTooHigh = i18n("The session ID is too high for ");
    } ;
} ;

#endif
