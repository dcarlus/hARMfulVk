#ifndef __SPITE__BASE_FILE__
#define __SPITE__BASE_FILE__

#include <fstream>
#include <filesystem>
#include <harmful/doom/utils/Platform.hpp>
#include "harmful/spite/readers/TextFileReader.hpp"
#include "harmful/spite/writers/TextFileWriter.hpp"

namespace fs = std::filesystem ;

namespace Spite {
    /// <summary>
    /// Read and write text content from disk.
    /// </summary>
    class TextFileContent {
        private:
            /// <summary>
            /// Path to the file.
            /// </summary>
            fs::path m_path ;

            /// <summary>
            /// Inner TextFile stream to read and/or write data on disk.
            /// </summary>
            std::fstream m_fs ;

            /// <summary>
            /// The TextFileReader used to read informations from the opened
            /// file.
            /// </summary>
            TextFileReader m_reader ;

            /// <summary>
            /// The TextFileWriter used to write into the file.
            /// </summary>
            TextFileWriter m_writer ;

            /// <summary>
            /// Mode in which the file has been opened.
            /// </summary>
            std::ios_base::openmode m_stdOpenMode;

        public:
            /// <summary>
            /// Creation a TextFileContent.
            /// </summary>
            /// <param name="filepath">Path to the file to open.</param>
            exported TextFileContent(const std::string& filepath) ;

            /// <summary>
            /// Destroy the TextFileContent.
            /// </summary>
            exported virtual ~TextFileContent() ;

            /// <summary>
            /// Save a data at a given place on disk.
            /// </summary>
            /// <param name="text">Text to save in the file.</param>
            exported void save(const std::string& text) ;

            /// <summary>
            /// Load a data at a given place on disk.
            /// </summary>
            /// <returns>Content of the file.</returns>
            exported std::string load() ;

        protected:
            /// <summary>
            /// Open the TextFile.
            /// </summary>
            /// <param name="mode">Mode to open the TextFile.</param>
            exported void open_fs(std::ios_base::openmode mode) ;

        private:
            // Remove copy/move operations.
            TextFileContent(const TextFileContent& copied) = delete ;
            TextFileContent(TextFileContent&& moved) = delete ;
            TextFileContent& operator=(const TextFileContent& copied) = delete ;
            TextFileContent& operator=(TextFileContent&& moved) = delete ;
    } ;
}

#endif
