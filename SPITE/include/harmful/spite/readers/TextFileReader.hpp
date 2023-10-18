#ifndef __SPITE__TEXT_FILE_READER__
#define __SPITE__TEXT_FILE_READER__

#include <string>
#include <harmful/doom/utils/Platform.hpp>
#include "harmful/spite/readers/FileReader.hpp"

namespace Spite {
    /// <summary>
    /// A TextFileReader is used to read text files.
    /// </summary>
    class TextFileReader : public FileReader {
        public:
            /// <summary>
            /// Read a line into the file.
            /// </summary>
            /// <param name="readLine">The line that is read.</param>
            /// <returns>The line that is read.</returns>
            exported std::string& readLine(std::string& readLine) {
                getline(*m_stream, readLine) ;
                return readLine ;
            }

            /// <summary>
            /// Read the whole content of a text at once.
            /// </summary>
            /// <param name="content">
            /// Output the whole content of the file.
            /// </param>
            exported void readAll(std::string& content) ;
    } ;
}

#endif
