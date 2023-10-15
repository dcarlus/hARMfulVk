#ifndef __DOOM__STRING_EXTENSION__
#define __DOOM__STRING_EXTENSION__

#include "harmful/doom/utils/Platform.hpp"
#include <string>
#include <vector>

namespace Doom {
    /// <summary>
    /// Extension of functions for the C++ string type.
    /// </summary>
    namespace StringExt {
        /// <summary>
        /// Offset between the upper and lower case alphabetic characters in
        /// the ASCII table.
        /// </summary>
        enum class CharacterCase : int8_t {
            Upper = 'A' - 'a',  // from lower to upper case in the ASCII table
            Lower = 'a' - 'A'   // from upper to lower case in the ASCII table
        } ;

        /// <summary>
        /// Convert a letter in the string to the wanted case.
        /// </summary>
        /// <param name="stringCap">The string to modify.</param>
        /// <param name="position">
        /// Position of the character in the string to uppercase.
        /// </param>
        /// <param name="charCase">Resulting case of the letter.</param>
        exported void CaseChar(
            std::string& stringCap,
            const size_t position,
            CharacterCase charCase
        ) ;

        /// <summary>
        /// Convert the first character in the string to the wanted case.
        /// </summary>
        /// <param name="stringCap">The string to modify.</param>
        /// <param name="charCase">Resulting case of the letters.</param>
        exported void CaseFirst(
            std::string& stringCap,
            CharacterCase charCase
        ) ;

        /// <summary>
        /// Convert the first character of each word in the string to the
        /// wanted case.
        /// </summary>
        /// <param name="stringCap">The string to modify.</param>
        /// <param name="charCase">Resulting case of the letters.</param>
        exported void CaseWords(
            std::string& stringCap,
            CharacterCase charCase
        ) ;

        /// <summary>
        /// Change each letter in the string to the wanted case.
        /// </summary>
        /// <param name="stringCap">The string to modify.</param>
        /// <param name="charCase">Resulting case of the letters.</param>
        exported void TextCase(
            std::string& stringCap,
            CharacterCase charCase
        ) ;

        /// <summary>
        /// Remove white spaces (spaces, tabulations, new lines...) from the
        /// left and the right of a string.
        /// </summary>
        /// <param name="stringToTrim">The string to trim.</param>
        exported void Trim(std::string& stringToTrim) ;

        /// <summary>
        /// Split a string at the given characters positions.
        /// </summary>
        /// <param name="toSplit">The string to split.</param>
        /// <param name="characters">
        /// List of the characters to split the string at their position.
        /// </param>
        /// <returns>List of the resulting substrings.</returns>
        exported std::vector<std::string> Split(
            const std::string& toSplit,
            const std::string& characters
        ) ;

        /// <summary>
        /// Convert an integer value to its string representation.
        /// </summary>
        /// <param name="value">The value to convert.</param>
        /// <param name="base">Base used to represent the value.</param>
        /// <returns>The string containing the value representation.</returns>
        exported std::string ToStringi(
            const int32_t value,
            const unsigned char base = 10
        ) ;

        /// <summary>
        /// Convert a floating value to its string representation.
        /// </summary>
        /// <param name="value">The value to convert.</param>
        /// <param name="precision">Precision of the representation.</param>
        /// <returns>The string containing the value representation.</returns>
        exported std::string ToStringf(
            const float value,
            const unsigned char precision = 2
        ) ;

        /// <summary>
        /// Create a random string with numbers, uppercase and lowercase
        /// letters.
        /// </summary>
        /// <param name="length">Length of the random string.</param>
        /// <returns>The generated string.</returns>
        exported std::string Random(const unsigned int length) ;

        /// <summary>
        /// Create a random string with the provided characters.
        /// </summary>
        /// <param name="length">Length of the random string.</param>
        /// <param name="characters">
        /// Characters that can be used in the string generation.
        /// </param>
        /// <returns>The generated string.</returns>
        exported std::string Random(
            const unsigned int length,
            const std::string& characters
        ) ;
    }
}


#endif
