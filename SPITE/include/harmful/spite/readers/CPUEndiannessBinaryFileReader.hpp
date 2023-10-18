#ifndef __SPITE__CPU_ENDIANNESS_BINARY_FILE_READER__
#define __SPITE__CPU_ENDIANNESS_BINARY_FILE_READER__

#include <ios>
#include <harmful/doom/utils/Platform.hpp>
#include "harmful/spite/readers/BinaryFileReader.hpp"
#include "harmful/spite/SPITEStrings.hpp"

namespace Spite {
    /// <summary>
    /// A CPUEndiannessBinaryFileReader can read data from binary files written
    /// using the same endianness than the processor.
    /// </summary>
    class CPUEndiannessBinaryFileReader : public BinaryFileReader {
        public:
            /// <summary>
            /// Read a 8-bit integer value.
            /// </summary>
            /// <returns>The read value.</returns>
            exported int8_t readChar() {
                int8_t tmp ;
                m_stream -> read((char*) &tmp, sizeof(tmp)) ;
                return tmp ;
            }

            /// <summary>
            /// Read a 16-bit integer value.
            /// </summary>
            /// <returns>The read value.</returns>
            exported int16_t readShort() {
                int16_t tmp ;
                m_stream -> read((char*) &tmp, sizeof(tmp)) ;
                return tmp ;
            }

            /// <summary>
            /// Read a 32-bit integer value.
            /// </summary>
            /// <returns>The read value.</returns>
            exported int32_t readInt32() {
                int32_t tmp ;
                m_stream -> read((char*) &tmp, sizeof(tmp)) ;
                return tmp ;
            }

            /// <summary>
            /// Read a 64-bit integer value.
            /// </summary>
            /// <returns>The read value.</returns>
            exported int64_t readInt64() {
                int64_t tmp ;
                m_stream -> read((char*) &tmp, sizeof(tmp)) ;
                return tmp ;
            }

            /// <summary>
            /// Read a 32-bit float value.
            /// </summary>
            /// <returns>The read value.</returns>
            exported float readFloat() {
                float tmp ;
                m_stream -> read((char*) &tmp, sizeof(tmp)) ;
                return tmp ;
            }

            /// <summary>
            /// Read a 64-bit float value.
            /// </summary>
            /// <returns>The read value.</returns>
            exported double readDouble() {
                double tmp ;
                m_stream -> read((char*) &tmp, sizeof(tmp)) ;
                return tmp ;
            }

            /// <summary>
            /// Read a string byte by byte.
            /// </summary>
            /// <param name="string">
            /// Buffer to store the content of the string.
            /// </param>
            /// <param name="length">
            /// Length of the string in byte.
            /// </param>
            /// <remarks>
            /// No null character inserted at the end of the string.
            /// </remarks>
            exported void readString(char string[], const unsigned int length) {
                for (unsigned int index = 0 ; index < length ; ++index) {
                    m_stream -> read((char*) &string[index], sizeof(char)) ;
                }
            }

            /// <summary>
            /// Read a string byte by byte.
            /// </summary>
            /// <param name="buffer">
            /// Buffer to store the characters of the string.
            /// </param>
            /// <param name="length">
            /// Length of the string in byte.
            /// </param>
            exported void readString(std::string& buffer, const unsigned int length) {
                buffer.clear() ;
                buffer.reserve(length) ;

                char read ;
                for (unsigned int index = 0 ; index < length ; ++index) {
                    m_stream -> read((char*) &read, sizeof(read)) ;
                    buffer.push_back(read) ;
                }
            }
    } ;
}

#endif
