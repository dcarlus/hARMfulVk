#ifndef __SPITE__REVERSED_CPU_ENDIANNESS_BINARY_FILE_READER__
#define __SPITE__REVERSED_CPU_ENDIANNESS_BINARY_FILE_READER__

#include <harmful/doom/utils/Platform.hpp>
#include "harmful/spite/readers/BinaryFileReader.hpp"

namespace Spite {
    /// <summary>
    /// A ReversedCPUEndiannessBinaryFileReader can read data from binary files
    /// written using the other known endianness from the processor.
    /// For example, use a ReversedCPUEndiannessBinaryFileReader to read a Big
    /// Endian file on a Little Endian CPU.
    /// </summary>
    class ReversedCPUEndiannessBinaryFileReader : public BinaryFileReader {
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

                // Switch bytes for good endianness [HIGH | LOW] --> [LOW | HIGH]
                int16_t little = ((tmp << 8) | (tmp >> 8)) ;
                return little ;
            }

            /// <summary>
            /// Read a 32-bit integer value.
            /// </summary>
            /// <returns>The read value.</returns>
            exported int32_t readInt32() {
                int32_t tmp ;
                m_stream -> read((char*) &tmp, sizeof(tmp)) ;
                return swapInt32(tmp) ;
            }

            /// <summary>
            /// Read a 64-bit integer value.
            /// </summary>
            /// <returns>The read value.</returns>
            exported int64_t readInt64() {
                int64_t tmp ;
                m_stream -> read((char*) &tmp, sizeof(tmp)) ;
                return swapInt64(tmp) ;
            }

            /// <summary>
            /// Read a 32-bit float value.
            /// </summary>
            /// <returns>The read value.</returns>
            exported float readFloat() {
                // Union used to swap the float value bytes.
                union SwapEndianness {
                    float fValue ;
                    int32_t iValue ;
                } swapper ;

                // Read the float.
                m_stream -> read((char*) &swapper.fValue, sizeof(swapper.fValue)) ;
                // Swap its bytes.
                swapper.iValue = swapInt32(swapper.iValue) ;
                return swapper.fValue ;
            }

            /// <summary>
            /// Read a 64-bit float value.
            /// </summary>
            /// <returns>The read value.</returns>
            exported double readDouble() {
                // Union used to swap the float value bytes.
                union SwapEndianness {
                    double dValue ;
                    int64_t lValue ;
                } swapper ;

                // Read the float.
                m_stream -> read((char*) &swapper.dValue, sizeof(swapper.dValue)) ;
                // Swap its bytes.
                swapper.lValue = swapInt64(swapper.lValue) ;
                return swapper.dValue ;
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

        private:
            /// <summary>
            /// Swap the bytes of a 32-bit integer value.
            /// </summary>
            /// <param name="value">The value to swap.</param>
            /// <returns>The swapped value.</returns>
            int32_t swapInt32(int32_t value) {
                // Switch bytes for good endianness:
                // [ 1 | 2 | 3 | 4 ] --> [ 4 | 3 | 2 | 1 ]
                return ((value & 0x000000FF) << 24
                            | (value & 0x0000FF00) << 8
                            | (value & 0x00FF0000) >> 8
                            | (value & 0xFF000000) >> 24) ;
            }

            /// <summary>
            /// Swap the bytes of a 64-bit integer value.
            /// </summary>
            /// <param name="value">The value to swap.</param>
            /// <returns>The swapped value.</returns>
            int64_t swapInt64(int64_t value) {
                // Switch bytes for good endianness
                // [ 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 ] --> [ 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 ]
                return ((value & 0x00000000000000FF) << 56
                            | (value & 0x000000000000FF00) << 40
                            | (value & 0x0000000000FF0000) << 24
                            | (value & 0x00000000FF000000) << 8
                            | (value & 0x000000FF00000000) >> 8
                            | (value & 0x0000FF0000000000) >> 24
                            | (value & 0x00FF000000000000) >> 40
                            | (value & 0xFF00000000000000) >> 56) ;
            }
    } ;
}

#endif
