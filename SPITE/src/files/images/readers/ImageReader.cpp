#include "harmful/spite/files/images/readers/ImageReader.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "harmful/spite/third_party/stb_image.h"

using namespace Spite ;

const float ImageReader::GammaCorrection = 2.2f ;
const float ImageReader::HDRScale = 1.f ;

ImageReader::ImageReader(const bool verticalFlip)
    : m_verticalFlip(verticalFlip) {}

bool ImageReader::verticalFlip() const {
    return m_verticalFlip ;
}

bool ImageReader::postRead(
    RawImage& image,
    int width,
    int height,
    uint8_t* imageData
) {
    image.setDimensions(width, height) ;
    auto& rawPixelData = image.data() ;
    const auto& imageFormat = image.format() ;

    size_t width_64 = width ;
    size_t height_64 = height ;
    size_t pixelSize_64 = imageFormat.pixelSizeInBytes() ;
    size_t imageDataSize = width_64 * height_64 * pixelSize_64 ;
    rawPixelData.insert(rawPixelData.begin(), imageData, imageData + imageDataSize) ;
    stbi_image_free(imageData) ;

    return (rawPixelData.size()) > 0 ;
}
