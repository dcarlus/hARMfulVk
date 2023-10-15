#include "harmful/doom/utils/Time.hpp"
#include "harmful/doom/utils/Platform.hpp"
#include <time.h>

namespace Doom {
    std::string Time::GetDateTime() {
        return GetDate() + " " + GetTime() ;
    }

    std::string Time::GetDate() {
        const std::string DateFormat = "%D" ;

        // %D gives the current day as MM/DD/YY
        // The string is so initialized with the right length.
        char buffer[9] ;
        GetTimeInfo(DateFormat, buffer, sizeof(buffer)) ;
        return std::string(buffer) ;
    }

    std::string Time::GetTime() {
        const std::string TimeFormat = "%T" ;

        // %T gives the current day as hh:mm:ss.
        char buffer[9] ;
        GetTimeInfo(TimeFormat, buffer, sizeof(buffer)) ;
        return std::string(buffer) ;
    }

    void Time::GetTimeInfo(
        const std::string& format,
        char* buffer,
        const size_t bufferLength
    ) {
        time_t now ;
        time(&now) ;

        #ifdef WindowsPlatform
    		struct tm timeinfo;
    		localtime_s(&timeinfo, &now);
    		strftime(buffer, bufferLength, format.c_str(), &timeinfo);
        #else
            struct tm* timeinfo ;
            timeinfo = localtime(&now) ;
            strftime(buffer, bufferLength, format.c_str(), timeinfo) ;
        #endif
    }
}
