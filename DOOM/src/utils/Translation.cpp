#include "utils/Translation.hpp"

#ifdef __linux__
    // Apply translations on GNU/Linux systems.
    #include <libintl.h>
    #include <clocale>

    namespace Doom {
        namespace Translation {
            void Init(const std::string& domain, const std::string& path) {
                setlocale(LC_ALL, "") ;
                bindtextdomain(domain.c_str(), path.c_str()) ;
                textdomain(domain.c_str()) ;
            }

            std::string Get(const std::string& str) {
                return std::string(gettext(str.c_str())) ;
            }
        } ;
    } ;

#else
    // Do not apply translations on other systems.
    namespace Doom {
        namespace Translation {
            void Init(const std::string&, const std::string&) {}

            std::string Get(const std::string& str) {
                return str ;
            }
        } ;
    } ;

#endif
