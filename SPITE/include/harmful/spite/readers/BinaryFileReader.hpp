#ifndef __SPITE__BINARY_FILE_READER__
#define __SPITE__BINARY_FILE_READER__

#include <stdint.h>
#include <string>
#include <vector>
#include <harmful/doom/utils/Platform.hpp>
#include "harmful/spite/readers/FileReader.hpp"

namespace Spite {
    /// <summary>
    /// A BinaryFileReader is used to read binary files.
    /// </summary>
    class BinaryFileReader : public FileReader {
        public:
            /// <summary>
            /// Read a 8-bit integer value.
            /// </summary>
            /// <returns>The read value.</returns>
            exported virtual int8_t readChar() = 0 ;

            /// <summary>
            /// Read a 16-bit integer value.
            /// </summary>
            /// <returns>The read value.</returns>
            exported virtual int16_t readShort() = 0 ;

            /// <summary>
            /// Read a 32-bit integer value.
            /// </summary>
            /// <returns>The read value.</returns>
            exported virtual int32_t readInt32() = 0 ;

            /// <summary>
            /// Read a 64-bit integer value.
            /// </summary>
            /// <returns>The read value.</returns>
            exported virtual int64_t readInt64() = 0 ;

            /// <summary>
            /// Read a 32-bit float value.
            /// </summary>
            /// <returns>The read value.</returns>
            exported virtual float readFloat() = 0 ;

            /// <summary>
            /// Read a 64-bit float value.
            /// </summary>
            /// <returns>The read value.</returns>
            exported virtual double readDouble() = 0 ;

            /// <summary>
            /// Read a string byte by byte.
            /// </summary>
            /// <param name="string">
            /// Buffer to store the content of the string.
            /// </param>
            /// <param name="length">
            /// Length of the string in byte.
            /// </param>
            exported virtual void readString(
                char string[],
                const unsigned int length
            ) = 0 ;

            /// <summary>
            /// Read a string byte by byte.
            /// </summary>
            /// <param name="buffer">
            /// Buffer to store the characters of the string.
            /// </param>
            /// <param name="length">
            /// Length of the string in byte.
            /// </param>
            exported virtual void readString(
                std::string& buffer,
                const unsigned int length
            ) = 0 ;

            /// <summary>
            /// Read all the bytes from a binary file.
            /// </summary>
            /// <param name="blob">Blob data got from the file.</param>
            /// <param name="size">Size of the blob.</param>
            exported void readAllBytes(char* blob, const size_t size) ;

            /// <summary>
            /// Read all the bytes from a binary file.
            /// </summary>
            /// <param name="blob">Blob data got from the file.</param>
            exported void readAllBytes(std::vector<char>& blob) ;

            /// <summary>
            /// Read all the bytes from a binary file.
            /// </summary>
            /// <param name="blob">Blob data got from the file.</param>
            exported void readAllBytes(std::vector<unsigned char>& blob) ;
    } ;
}

#endif
