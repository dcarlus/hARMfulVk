#include <stdexcept>
#include "harmful/spite/files/images/ImageUtils.hpp"
#include "harmful/spite/SPITEStrings.hpp"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "harmful/spite/third_party/stb_image_resize.h"

using namespace Spite ;

const std::string ImageUtils::PNGFileExtension = ".png" ;
const std::string ImageUtils::JPGFileExtension = ".jpg" ;
const std::string ImageUtils::JPEGFileExtension = ".jpeg" ;
const std::string ImageUtils::BMPFileExtension = ".bmp" ;
const std::string ImageUtils::RLEFileExtension = ".rle" ;
const std::string ImageUtils::DIBFileExtension = ".dib" ;
const std::string ImageUtils::TGAFileExtension = ".tga" ;
const std::string ImageUtils::TPICFileExtension = ".tpic" ;
const std::string ImageUtils::HDRFileExtension = ".hdr" ;

RawImage ImageUtils::Resize(
    RawImage& original,
    const unsigned int width,
    const unsigned int height
) {
    auto& format = original.format() ;
    unsigned int amountChannels = format.amountOfComponents() ;
    const unsigned int StrideInBytes = 0 ;

    unsigned int originalWidth = original.width() ;
    unsigned int originalHeight = original.height() ;
    auto& originalBytes = original.data() ;

    RawImage resized ;
    resized.setFormat(format.id(), format.type()) ;
    resized.setDimensions(width, height) ;

    switch (format.type()) {
        case ColorFormat::Byte:
        {
            auto& resizedBytes = resized.data() ;

            stbir_resize_uint8_generic(
                originalBytes.data(),
                originalWidth,
                originalHeight,
                StrideInBytes,
                resizedBytes.data(),
                width,
                height,
                StrideInBytes,
                amountChannels,
                STBIR_ALPHA_CHANNEL_NONE,
                0,
                STBIR_EDGE_CLAMP,
                STBIR_FILTER_CUBICBSPLINE,
                STBIR_COLORSPACE_LINEAR,
                nullptr
            ) ;
        }
        break ;

        case ColorFormat::FloatingPoint:
        {
            std::vector<float> resizedPixels(width * height * amountChannels) ;
            auto* originalPixels = reinterpret_cast<float*>(originalBytes.data()) ;

            stbir_resize_float_generic(
                originalPixels,
                originalWidth,
                originalHeight,
                StrideInBytes,
                resizedPixels.data(),
                width,
                height,
                StrideInBytes,
                amountChannels,
                STBIR_ALPHA_CHANNEL_NONE,
                0,
                STBIR_EDGE_CLAMP,
                STBIR_FILTER_CUBICBSPLINE,
                STBIR_COLORSPACE_SRGB,
                nullptr
            ) ;

            auto* resizedPixelBytes = reinterpret_cast<unsigned char*>(resizedPixels.data()) ;
            resized.data().insert(
                resized.data().begin(),
                resizedPixelBytes,
                resizedPixelBytes + (resizedPixels.size() * sizeof(float))
            ) ;
        }
        break ;

        default:
            throw std::runtime_error(ColorFormatMsg::Error::UnknownFormat) ;
    }

    return resized ;
}
