#ifndef __SPITE__TEXT_FILE_WRITER__
#define __SPITE__TEXT_FILE_WRITER__

#include <string>
#include <harmful/doom/utils/Platform.hpp>
#include "harmful/spite/writers/FileWriter.hpp"

namespace Spite {
    /// <summary>
    /// A TextFileWriter is used to write text files.
    /// </summary>
    class TextFileWriter : public FileWriter {
        public:
            /// <summary>
            /// Read a line from the file.
            /// </summary>
            /// <param name="text">The text to write.</param>
            exported void write(const std::string& text) {
                (*m_stream) << text ;
            }
    } ;
}

#endif
