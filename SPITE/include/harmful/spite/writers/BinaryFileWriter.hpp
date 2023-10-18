#ifndef __SPITE__BINARY_FILE_WRITER__
#define __SPITE__BINARY_FILE_WRITER__

#include <cstdint>
#include <string>
#include <harmful/doom/utils/Platform.hpp>
#include "harmful/spite/writers/FileWriter.hpp"

namespace Spite {
    /// <summary>
    /// A BinaryFileWriter is used to write binary files.
    /// </summary>
    class BinaryFileWriter : public FileWriter {
        public:
            /// <summary>
            /// Write a 8-bit integer value.
            /// </summary>
            /// <param name="value">The value to write.</param>
            exported virtual void writeChar(int8_t value) = 0 ;

            /// <summary>
            /// Write a 16-bit integer value.
            /// </summary>
            /// <param name="value">The value to write.</param>
            exported virtual void writeShort(int16_t value) = 0 ;

            /// <summary>
            /// Write a 32-bit integer value.
            /// </summary>
            /// <param name="value">The value to write.</param>
            exported virtual void writeInt32(int32_t value) = 0 ;

            /// <summary>
            /// Write a 64-bit integer value.
            /// </summary>
            /// <param name="value">The value to write.</param>
            exported virtual void writeInt64(int64_t value) = 0 ;

            /// <summary>
            /// Write a 32-bit float value.
            /// </summary>
            /// <param name="value">The value to write.</param>
            exported virtual void writeFloat(float value) = 0 ;

            /// <summary>
            /// Write a 64-bit float value.
            /// </summary>
            /// <param name="value">The value to write.</param>
            exported virtual void writeDouble(double value) = 0 ;

            /// <summary>
            /// Write a string byte by byte.
            /// </summary>
            /// <param name="text">Text to write in the File.</param>
            /// <param name="length">Length of the string in byte.</param>
            exported virtual void writeString(
                const char* text,
                const unsigned int length
            ) = 0 ;

            /// <summary>
            /// Write a string byte by byte.
            /// </summary>
            /// <param name="text">Text to write in the File.</param>
            exported virtual void writeString(
                const std::string& text
            ) = 0 ;
    } ;
}

#endif
