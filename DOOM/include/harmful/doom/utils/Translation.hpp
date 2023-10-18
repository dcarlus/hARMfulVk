#ifndef __DOOM__TRANSLATION__
#define __DOOM__TRANSLATION__

#include "harmful/doom/utils/Platform.hpp"
#include "harmful/doom/DOOMStrings.hpp"

/// <summary>
/// Tag to be detected when using xgettext on this file.
/// </summary>
#ifndef i18n
#define i18n(str) str
#endif i18n

namespace Doom {
    /// <summary>
    /// Namespace dedicated to the translation of libraries and softwares.
    /// </summary>
    namespace Translation {
        /// <summary>
        /// Initialize the translation of the wanted binary (library or
        /// software).
        /// </summary>
        /// <param name="domain">Domain name for translations.</param>
        /// <param name="path">Path to the translation files.</param>
        exported void Init(const std::string& domain, const std::string& path) ;

        /// <summary>
        /// Translate the provided string into the user defined locale, if
        /// available. If the locale is not available, the provided string is
        /// directly used.
        /// </summary>
        /// <param name="str">Text to be translated.</param>
        /// <returns>
        /// The translation of the provided string if the locale is available,
        /// the same text than the provided str if the locale is not defined
        /// for the user current locale.
        /// </returns>
        exported std::string Get(const std::string& str) ;
    } ;
} ;

#endif
