#ifndef __SPITE__FILE_WRITER__
#define __SPITE__FILE_WRITER__

#include <fstream>
#include <harmful/doom/utils/Platform.hpp>

namespace Spite {
    /// <summary>
    /// A FileWriter is used to write the content of a File.
    /// </summary>
    class FileWriter {
        protected:
            /// <summary>
            /// The filestream used to parse a file.
            /// </summary>
            std::fstream* m_stream ;

        public:
            /// <summary>
            /// Create a FileWriter.
            /// </summary>
            exported FileWriter() = default ;

            /// <summary>
            /// Destruction of the FileWriter.
            /// </summary>
            exported virtual ~FileWriter() = default ;

            /// <summary>
            /// Clear the stream.
            /// </summary>
            exported void clear() {
                m_stream -> clear() ;
            }

            /// <summary>
            /// Set the stream of the FileWriter.
            /// </summary>
            /// <param name="stream">The stream to use.</param>
            exported void setFileStream(std::fstream* stream) {
                m_stream = stream ;
            }

            // Remove copy/move operations.
            exported FileWriter(const FileWriter& copied) = default;
            exported FileWriter(FileWriter&& moved) = default;
            exported FileWriter& operator=(const FileWriter& copied) = default;
            exported FileWriter& operator=(FileWriter&& moved) = default;
    } ;
}

#endif
