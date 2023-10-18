#ifndef __SPITE__IMAGE_MEMORY_WRITER__
#define __SPITE__IMAGE_MEMORY_WRITER__

#include <functional>
#include <vector>
#include <map>
#include <harmful/doom/utils/Platform.hpp>
#include "harmful/spite/files/images/writers/ImageWriter.hpp"

namespace Spite {
    /// <summary>
    /// Dedicated class to store compressed images in memory.
    /// </summary>
    class ImageMemoryWriter final : public ImageWriter {
        private:
            using Functor = std::function<bool(RawImage&, std::vector<uint8_t>&)> ;

            /// <summary>
            /// Bind extensions to their functor to store compressed image in
            /// memory.
            /// </summary>
            static const std::map<std::string, Functor> ExtensionMemorySave ;

            /// <summary>
            /// Memory buffer where the data are saved.
            /// </summary>
            std::vector<uint8_t> m_buffer ;

        public:
            /// <summary>
            /// Create a new ImageFileWriter to write compressed data in a
            /// file.
            /// </summary>
            /// <param name="data">
            /// Binary data containing raw picture data.
            /// </param>
            /// <param name="verticalFlip">
            /// true to flip vertically; false otherwise.
            /// </param>
            exported ImageMemoryWriter(
                RawImage& data,
                const bool verticalFlip = false
            ) ;

            /// <summary>
            /// Get the memory buffer containing the data.
            /// </summary>
            /// <returns></returns>
            std::vector<uint8_t>& buffer() ;

        private:
            /// <summary>
            /// Perform save.
            /// </summary>
            /// <returns>true on success; false otherwise.</returns>
            exported bool processSpecific() override ;

            /// <summary>
            /// Callback to write bytes in memory buffer.
            /// Called several times until the file is totally written.
            /// </summary>
            /// <param name="context">Pointer to the memory buffer.</param>
            /// <param name="data">
            /// Bytes of data that have been processed and to put into the
            /// buffer.
            /// </param>
            /// <param name="size">Size of data.</param>
            exported static void WriteBytesFunc(
                void* context,
                void* data,
                int size
            ) ;

            /// <summary>
            /// Save PNG file.
            /// </summary>
            /// <param name="image">Raw data of the image to save.</param>
            /// <param name="path">Path to write the file.</param>
            /// <returns>true on success; false otherwise.</returns>
            exported static bool SavePNG(
                RawImage& image,
                std::vector<uint8_t>& buffer
            ) ;

            /// <summary>
            /// Save JPEG file.
            /// </summary>
            /// <param name="image">Raw data of the image to save.</param>
            /// <param name="path">Path to write the file.</param>
            /// <returns>true on success; false otherwise.</returns>
            exported static bool SaveJPEG(
                RawImage& image,
                std::vector<uint8_t>& buffer
            ) ;

            /// <summary>
            /// Save TGA file.
            /// </summary>
            /// <param name="image">Raw data of the image to save.</param>
            /// <param name="path">Path to write the file.</param>
            /// <returns>true on success; false otherwise.</returns>
            exported static bool SaveTGA(
                RawImage& image,
                std::vector<uint8_t>& buffer
            ) ;

            /// <summary>
            /// Save BMP file.
            /// </summary>
            /// <param name="image">Raw data of the image to save.</param>
            /// <param name="path">Path to write the file.</param>
            /// <returns>true on success; false otherwise.</returns>
            exported static bool SaveBMP(
                RawImage& image,
                std::vector<uint8_t>& buffer
            ) ;

            /// <summary>
            /// Save HDR file.
            /// </summary>
            /// <param name="image">Raw data of the image to save.</param>
            /// <param name="path">Path to write the file.</param>
            /// <returns>true on success; false otherwise.</returns>
            exported static bool SaveHDR(
                RawImage& image,
                std::vector<uint8_t>& buffer
            ) ;
    } ;
}

#endif
