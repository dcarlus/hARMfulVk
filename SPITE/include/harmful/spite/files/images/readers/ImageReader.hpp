#ifndef __SPITE__IMAGE_READER__
#define __SPITE__IMAGE_READER__

#include <string>
#include <harmful/doom/utils/Platform.hpp>
#include "harmful/spite/files/images/data/RawImage.hpp"

namespace Spite {
    /// <summary>
    /// Dedicated class to red compressed images.
    /// </summary>
    class ImageReader {
        protected:
            static const float GammaCorrection ;
            static const float HDRScale ;

        private:
            /// <summary>
            /// true to flip vertically on load; false otherwise.
            /// </summary>
            bool m_verticalFlip = false ;

        public:
            /// <summary>
            /// Create a new ImageReader to write compressed data in a file.
            /// </summary>
            /// <param name="verticalFlip">
            /// true to flip vertically; false otherwise.
            /// </param>
            exported ImageReader(const bool verticalFlip = false) ;

            /// <summary>
            /// Perform read of the file.
            /// </summary>
            /// <returns>Raw data of the read picture.</returns>
            exported virtual RawImage process() = 0 ;

        protected:
            /// <summary>
            /// Flag to flip the picture vertically.
            /// </summary>
            /// <returns>
            /// true to flip vertically on load; false otherwise.
            /// </returns>
            bool verticalFlip() const ;

            /// <summary>
            /// Common post-read action.
            /// </summary>
            /// <param name="image">The read picture.</param>
            /// <param name="width">Width of the picture.</param>
            /// <param name="height">Height of the picture.</param>
            /// <param name="imageData">
            /// Data to put in the raw image.
            /// </param>
            /// <returns>true on success; false otherwise.</returns>
            bool postRead(
                RawImage& image,
                int width,
                int height,
                uint8_t* imageData
            ) ;
    } ;
}

#endif
