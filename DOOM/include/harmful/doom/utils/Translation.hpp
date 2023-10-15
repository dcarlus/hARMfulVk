#ifndef __DOOM__TRANSLATION__
#define __DOOM__TRANSLATION__

#include "harmful/doom/utils/Platform.hpp"
#include "harmful/doom/DOOMStrings.hpp"

namespace Doom {
    /**
     * Namespace dedicated to the translation of libraries and softwares.
     */
    namespace Translation {
        /**
         * Initialize the translation of the wanted binary (library or
         * software).
         * @param domain  Domain name for translations.
         * @param path    Path to the translation files.
         */
        exported void Init(const std::string& domain, const std::string& path) ;

        /**
         * Translate the provided string into the user defined locale, if
         * available. If the locale is not available, the provided string is
         * directly used.
         * @param  str Text to be translated.
         * @return     The translation of the provided string if the locale is
         *             available, the same text than the provided @a str if the
         *             locale is not defined for the user current locale.
         */
        exported std::string Get(const std::string& str) ;
    } ;
} ;

#endif
