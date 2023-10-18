#ifndef __SPITE__IMAGE_MEMORY_READER__
#define __SPITE__IMAGE_MEMORY_READER__

#include <string>
#include <vector>
#include <harmful/doom/utils/Platform.hpp>
#include "harmful/spite/files/images/readers/ImageReader.hpp"

namespace Spite {
    /// <summary>
    /// Dedicated class to red compressed images from memory.
    /// </summary>
    class ImageMemoryReader final : public ImageReader {
        private:
            /// <summary>
            /// Buffer containing the bytes to read from.
            /// </summary>
            const std::vector<uint8_t>* m_buffer = nullptr ;

        public:
            /// <summary>
            /// Create a new ImageReader to write compressed data in a file.
            /// </summary>
            /// <param name="buffer">Buffer containing the file bytes.</param>
            /// <param name="verticalFlip">
            /// verticalFlip true to flip vertically; false otherwise.
            /// </param>
            exported ImageMemoryReader(
                const std::vector<uint8_t>& buffer,
                const bool verticalFlip = false
            ) ;

            /// <summary>
            /// Perform read of the file.
            /// </summary>
            /// <returns>Raw data of the read picture.</returns>
            exported RawImage process() ;

            /// <summary>
            /// Shortcut in a single static method
            /// </summary>
            /// <param name="buffer">Buffer containing the file bytes.</param>
            /// <param name="verticalFlip">
            /// true to flip on vertical axis the image; false otherwise.
            /// </param>
            /// <returns>Raw data of the read picture.</returns>
            exported static RawImage Read(
                const std::vector<uint8_t>& buffer,
                const bool verticalFlip = false
            ) {
                ImageMemoryReader reader(buffer, verticalFlip) ;
                return reader.process() ;
            }

        private:
            /// <summary>
            /// Buffer raw bytes.
            /// </summary>
            /// <returns>Bytes in the buffer.</returns>
            exported const uint8_t* bufferData() const {
                return (*m_buffer).data() ;
            }

            /// <summary>
            /// Get the size of the buffer.
            /// </summary>
            /// <returns>Size of the buffer.</returns>
            exported size_t bufferSize() const {
                return (*m_buffer).size() ;
            }

            /// <summary>
            /// Read images.
            /// </summary>
            /// <returns>Raw data of the read picture.</returns>
            exported RawImage readImage() ;

            /// <summary>
            /// Read images with 8-bits per channel.
            /// </summary>
            /// <returns>Raw data of the read picture.</returns>
            exported RawImage read8BitsChannel() ;

            /// <summary>
            /// Read images with 16-bits per channel.
            /// </summary>
            /// <returns>Raw data of the read picture.</returns>
            exported RawImage read16BitsChannel() ;

            /// <summary>
            /// Read HDR file.
            /// </summary>
            /// <returns>Raw data of the read picture.</returns>
            exported RawImage readHDR() ;
    } ;
}

#endif
