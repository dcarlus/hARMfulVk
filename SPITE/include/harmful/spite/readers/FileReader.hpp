#ifndef __SPITE__FILE_READER__
#define __SPITE__FILE_READER__

#include <fstream>
#include <harmful/doom/utils/Platform.hpp>

namespace Spite {
    /// <summary>
    /// A FileReader is used to read the content of a File.
    /// </summary>
    class FileReader {
        protected:
            /// <summary>
            /// The filestream used to parse a file.
            /// </summary>
            std::fstream* m_stream ;

        public:
            /// <summary>
            /// Create a FileReader.
            /// </summary>
            /// <returns></returns>
            exported FileReader() = default ;

            /// <summary>
            /// Destruction of the FileReader.
            /// </summary>
            exported virtual ~FileReader() = default ;

            /// <summary>
            /// Set the stream of the FileReader.
            /// </summary>
            /// <param name="stream">The stream to use.</param>
            exported void setFileStream(std::fstream* stream) {
                m_stream = stream ;
            }

            // Remove copy/move operations.
            exported FileReader(const FileReader& copied) = default;
            exported FileReader(FileReader&& moved) = default;
            exported FileReader& operator=(const FileReader& copied) = default;
            exported FileReader& operator=(FileReader&& moved) = default;
    } ;
}

#endif
