#ifndef __SPITE__IMAGE_FILE_READER__
#define __SPITE__IMAGE_FILE_READER__

#include <string>
#include <harmful/doom/utils/Platform.hpp>
#include "harmful/spite/files/images/readers/ImageReader.hpp"

namespace Spite {
    /// <summary>
    /// Dedicated class to red compressed images from files.
    /// </summary>
    class ImageFileReader final : public ImageReader {
        private:
            /// <summary>
            /// Path to the file to read.
            /// </summary>
            std::string m_filepath ;

        public:
            /// <summary>
            /// Create a new ImageReader to write compressed data in a file.
            /// </summary>
            /// <param name="filepath">Path of the file to read.</param>
            /// <param name="verticalFlip">
            /// true to flip vertically; false otherwise.
            /// </param>
            exported ImageFileReader(
                const std::string& filepath,
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
            /// <param name="filepath">Path to the file to read.</param>
            /// <param name="verticalFlip">
            /// true to flip on vertical axis the image; false otherwise.
            /// </param>
            /// <returns>Raw data of the read picture.</returns>
            exported static RawImage Read(
                const std::string& filepath,
                const bool verticalFlip = false
            ) {
                ImageFileReader reader(filepath, verticalFlip) ;
                return reader.process() ;
            }

        private:
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
