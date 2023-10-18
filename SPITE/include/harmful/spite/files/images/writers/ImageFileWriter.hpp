#ifndef __SPITE__IMAGE_FILE_WRITER__
#define __SPITE__IMAGE_FILE_WRITER__

#include <filesystem>
#include <functional>
#include <vector>
#include <map>
#include <harmful/doom/utils/Platform.hpp>
#include "harmful/spite/files/images/writers/ImageWriter.hpp"

namespace fs = std::filesystem ;

namespace Spite {
    /// <summary>
    /// Dedicated class to store compressed images in files.
    /// </summary>
    class ImageFileWriter final : public ImageWriter {
        private:
            using Functor = std::function<bool(RawImage&, const std::string&)> ;

            /// <summary>
            /// Bind extensions to their functor to save file on disk.
            /// </summary>
            static const std::map<std::string, Functor> ExtensionFileSave ;

            /// <summary>
            /// Path to the file to save.
            /// </summary>
            fs::path m_path ;

        public:
            /// <summary>
            /// Create a new ImageFileWriter to write compressed data in a file.
            /// </summary>
            /// <param name="data">
            /// Binary data containing raw picture data.
            /// </param>
            /// <param name="path">Path of the file to save to.</param>
            /// <param name="verticalFlip">
            /// true to flip vertically; false otherwise.
            /// </param>
            exported ImageFileWriter(
                RawImage& data,
                const fs::path& path,
                const bool verticalFlip = false
            ) ;

        private:
            /// <summary>
            /// Perform save.
            /// </summary>
            /// <returns>true on success; false otherwise.</returns>
            exported bool processSpecific() override ;

            /// <summary>
            /// Save PNG file.
            /// </summary>
            /// <param name="image">Raw data of the image to save.</param>
            /// <param name="path">Path to write the file.</param>
            /// <returns>true on success; false otherwise.</returns>
            exported static bool SavePNG(
                RawImage& image,
                const std::string& path
            ) ;

            /// <summary>
            /// Save JPEG file.
            /// </summary>
            /// <param name="image">Raw data of the image to save.</param>
            /// <param name="path">Path to write the file.</param>
            /// <returns>true on success; false otherwise.</returns>
            exported static bool SaveJPEG(
                RawImage& image,
                const std::string& path
            ) ;

            /// <summary>
            /// Save TGA file.
            /// </summary>
            /// <param name="image">Raw data of the image to save.</param>
            /// <param name="path">Path to write the file.</param>
            /// <returns>true on success; false otherwise.</returns>
            exported static bool SaveTGA(
                RawImage& image,
                const std::string& path
            ) ;

            /// <summary>
            /// Save BMP file.
            /// </summary>
            /// <param name="image">Raw data of the image to save.</param>
            /// <param name="path">Path to write the file.</param>
            /// <returns>true on success; false otherwise.</returns>
            exported static bool SaveBMP(
                RawImage& image,
                const std::string& path
            ) ;

            /// <summary>
            /// Save HDR file.
            /// </summary>
            /// <param name="image">Raw data of the image to save.</param>
            /// <param name="path">Path to write the file.</param>
            /// <returns>true on success; false otherwise.</returns>
            exported static bool SaveHDR(
                RawImage& image,
                const std::string& path
            ) ;
    } ;
}

#endif
