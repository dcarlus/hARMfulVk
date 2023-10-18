#ifndef __SPITE__IMAGE_UTILS__
#define __SPITE__IMAGE_UTILS__

#include <harmful/doom/utils/Platform.hpp>
#include "harmful/spite/files/images/data/RawImage.hpp"

namespace Spite::ImageUtils {
    extern const std::string PNGFileExtension ;
    extern const std::string JPGFileExtension ;
    extern const std::string JPEGFileExtension ;
    extern const std::string BMPFileExtension ;
    extern const std::string RLEFileExtension ;
    extern const std::string DIBFileExtension ;
    extern const std::string TGAFileExtension ;
    extern const std::string TPICFileExtension ;
    extern const std::string HDRFileExtension ;

    /// <summary>
    /// Resize a picture to the wanted size.
    /// </summary>
    /// <param name="original">Original picture data.</param>
    /// <param name="width">Width of th output resized picture.</param>
    /// <param name="height">Height of th output resized picture.</param>
    /// <returns>Resized picture.</returns>
    exported RawImage Resize(
        RawImage& original,
        const unsigned int width,
        const unsigned int height
    ) ;
}

#endif
