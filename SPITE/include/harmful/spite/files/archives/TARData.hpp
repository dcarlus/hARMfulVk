#ifndef __SPITE__TAR_DATA__
#define __SPITE__TAR_DATA__

#include <string>
#include <vector>
#include <map>
#include <set>
#include <filesystem>
#include <harmful/doom/utils/Platform.hpp>
#include <harmful/doom/utils/LogSystem.hpp>
#include "harmful/spite/files/FileInfo.hpp"
#include "harmful/spite/third_party/microtar.h"

namespace fs = std::filesystem ;

namespace Spite {
    /// <summary>
    /// Class for creating a .tar archive file.
    /// </summary>
    class TARData final {
        friend class TARUtils ;

        private:
            /// <summary>
            /// Bytes of the files in memory.
            /// </summary>
            std::vector<uint8_t> m_fileBytes ;

            /// <summary>
            /// List of the directories in the archive.
            /// </summary>
            std::set<fs::path> m_directories ;

            /// <summary>
            /// Infos of the file bytes at a destination path.
            /// </summary>
            std::map<fs::path, FileInfo> m_infos ;

        public:
            /// <summary>
            /// Add a binary file.
            /// </summary>
            /// <param name="filepath">Path to the file.</param>
            /// <param name="bytes">Content of the file.</param>
            /// <returns>true on success; false otherwise.</returns>
            template <typename T>
            exported bool addBinaryFile(
                const fs::path& filepath,
                const std::vector<T> bytes
            ) ;

            /// <summary>
            /// Add a text file.
            /// </summary>
            /// <param name="filepath">Path to the file.</param>
            /// <param name="text">Content of the file.</param>
            /// <returns>true on success; false otherwise.</returns>
            exported bool addTextFile(
                const fs::path& filepath,
                const std::string& text
            ) ;

            /// <summary>
            /// Read the content of a file at a given path in the archive.
            /// </summary>
            /// <param name="filepath">Path of the file.</param>
            /// <param name="fileContent">Content of the file (output).</param>
            /// <returns>true on success; false otherwise.</returns>
            template <typename T>
            exported bool readBinaryFile(
                const fs::path& filepath,
                T& fileContent
            ) ;

            /// <summary>
            /// Read the content of a file at a given path in the archive.
            /// </summary>
            /// <param name="filepath">Path of the file.</param>
            /// <param name="buffer">Content of the file (output).</param>
            /// <returns>true on success; false otherwise.</returns>
            exported bool readBinaryFile(
                const fs::path& filepath,
                std::vector<unsigned char>& buffer
            ) ;

            /// <summary>
            /// Read the content of a file at a given path in the archive.
            /// </summary>
            /// <param name="filepath">Path of the file.</param>
            /// <param name="text">Content of the file (output).</param>
            /// <returns>true on success; false otherwise.</returns>
            exported bool readTextFile(
                const fs::path& filepath,
                std::string& text
            ) ;

            /// <summary>
            /// Get the directory paths contained in the archive.
            /// </summary>
            /// <returns>List of directories in the archive file.</returns>
            exported const std::set<fs::path>& directories() const ;

            /// <summary>
            /// Get the file paths contained in the archive.
            /// </summary>
            /// <returns>List of the file paths in the archive file.</returns>
            exported std::vector<fs::path> paths() const ;

            /// <summary>
            /// Get the file raw data.
            /// </summary>
            /// <returns>Output the raw data of the file.</returns>
            exported std::vector<unsigned char>& data() ;

        private:
            /// <summary>
            /// Initialize TAR archive memory.
            /// </summary>
            /// <param name="tar">Structure from the mtar lib.</param>
            /// <param name="path">Path to the file.</param>
            /// <param name="tarOpenMode">Read mode of the file.</param>
            exported void initialize(
                mtar_t& tar,
                const std::string& path,
                const std::string& tarOpenMode
            ) ;

            /// <summary>
            /// Finalize the archive memory.
            /// </summary>
            /// <param name="tar">Structure from the mtar lib.</param>
            exported void finalize(mtar_t& tar) ;

            /// <summary>
            /// Write directory headers before writing files.
            /// </summary>
            /// <param name="tar">Structure from the mtar lib.</param>
            exported void beforeWrite(mtar_t& tar) ;

            /// <summary>
            /// Write the full content of files into the mtar structure.
            /// </summary>
            /// <param name="tar">Structure from the mtar lib.</param>
            exported void write(mtar_t& tar) ;

            /// <summary>
            /// Write a binary file into the archive.
            /// </summary>
            /// <param name="tar">Structure from the mtar lib.</param>
            /// <param name="filepath">Path to the file.</param>
            /// <param name="infos">File infos.</param>
            /// <returns>true on success; false otherwise.</returns>
            exported bool writeBinary(
                mtar_t& tar,
                const std::string& filepath,
                const FileInfo& infos
            ) ;

            /// <summary>
            /// Write a text file into the archive.
            /// </summary>
            /// <param name="tar">Structure from the mtar lib.</param>
            /// <param name="filepath">Path to the file.</param>
            /// <param name="infos">File infos.</param>
            /// <returns>true on success; false otherwise.</returns>
            exported bool writeText(
                mtar_t& tar,
                const std::string& filepath,
                const FileInfo& infos
            ) ;

            /// <summary>
            /// Read the content of the archive.
            /// </summary>
            /// <param name="tar">Structure from the mtar lib.</param>
            exported void read(mtar_t& tar) ;
    } ;

    template <typename T>
    bool TARData::addBinaryFile(
        const fs::path& filepath,
        const std::vector<T> bytes
    ) {
        if (m_infos.count(filepath) > 1) {
            return false ;
        }

        size_t begin = m_fileBytes.size() ;

        size_t dataSize = bytes.size() * sizeof(T) ;
        auto* rawBytes = reinterpret_cast<const unsigned char*>(bytes.data()) ;
        m_fileBytes.insert(m_fileBytes.end(), rawBytes, rawBytes + dataSize) ;

        size_t end = m_fileBytes.size() ;
        m_infos[filepath] = {
            .type = FileType::Binary,
            .begin = begin,
            .end = end
        } ;

        m_directories.insert(filepath.parent_path()) ;

        return true ;
    }

    template <typename T>
    bool TARData::readBinaryFile(const fs::path& filepath, T& fileContent) {
        if (m_infos.count(filepath) == 0) {
            return false ;
        }

        auto infos = m_infos[filepath] ;
        auto contentLength = infos.end - infos.begin ;
        fileContent.reserve(contentLength) ;

        std::vector<unsigned char> bytes ;
        bytes.reserve(contentLength) ;
        bytes.insert(
            bytes.begin(),
            m_fileBytes.begin() + infos.begin,
            m_fileBytes.begin() + infos.end
        ) ;

        fileContent = reinterpret_cast<T>(bytes.data()) ;

        return true ;
    }
}

#endif
