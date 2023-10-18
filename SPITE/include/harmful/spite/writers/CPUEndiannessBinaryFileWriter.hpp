#ifndef __SPITE__CPU_ENDIANNESS_BINARY_FILE_WRITER__
#define __SPITE__CPU_ENDIANNESS_BINARY_FILE_WRITER__

#include <harmful/doom/utils/Platform.hpp>
#include "harmful/spite/writers/BinaryFileWriter.hpp"

namespace Spite {
    /// <summary>
    /// A CPUEndiannessBinaryFileWriter can write data in binary files using
    /// the same endianness than the processor.
    /// </summary>
    class CPUEndiannessBinaryFileWriter : public BinaryFileWriter {
        public:
            /// <summary>
            /// Write a 8-bit integer value.
            /// </summary>
            /// <param name="value">The value to write.</param>
            exported void writeChar(int8_t value) {
                m_stream -> write((char*) &value, sizeof(value)) ;
            }

            /// <summary>
            /// Write a 16-bit integer value.
            /// </summary>
            /// <param name="value">The value to write.</param>
            exported void writeShort(int16_t value) {
                m_stream -> write((char*) &value, sizeof(value)) ;
            }

            /// <summary>
            /// Write a 32-bit integer value.
            /// </summary>
            /// <param name="value">The value to write.</param>
            exported void writeInt32(int32_t value) {
                m_stream -> write((char*) &value, sizeof(value)) ;
            }

            /// <summary>
            /// Write a 64-bit integer value.
            /// </summary>
            /// <param name="value">The value to write.</param>
            exported void writeInt64(int64_t value) {
                m_stream -> write((char*) &value, sizeof(value)) ;
            }

            /// <summary>
            /// Write a 32-bit float value.
            /// </summary>
            /// <param name="value">The value to write.</param>
            exported void writeFloat(float value) {
                m_stream -> write((char*) &value, sizeof(value)) ;
            }

            /// <summary>
            /// Write a 64-bit float value.
            /// </summary>
            /// <param name="value">The value to write.</param>
            exported void writeDouble(double value) {
                m_stream -> write((char*) &value, sizeof(value)) ;
            }

            /// <summary>
            /// Write a string byte by byte.
            /// </summary>
            /// <param name="text">Text to write in the File.</param>
            /// <param name="length">Length of the string in byte.</param>
            exported void writeString(
                const char* text,
                const unsigned int length
            ) {
                for (unsigned int index = 0 ; index < length ; ++index) {
                    m_stream -> write((char*) &text[index], sizeof(char)) ;
                }
            }

            /// <summary>
            /// Write a string byte by byte.
            /// </summary>
            /// <param name="text">Text to write in the File.</param>
            exported void writeString(const std::string& text) {
                size_t length = text.size() ;
                for (unsigned int index = 0 ; index < length ; ++index) {
                    m_stream -> write((char*) &text[index], sizeof(char)) ;
                }
            }
    } ;
}

#endif
