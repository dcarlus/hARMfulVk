#include "harmful/spite/files/images/readers/ImageMemoryReader.hpp"
#include "harmful/spite/third_party/stb_image.h"

using namespace Spite ;

ImageMemoryReader::ImageMemoryReader(
    const std::vector<uint8_t>& buffer,
    const bool verticalFlip
) : ImageReader(verticalFlip),
    m_buffer(&buffer) {}

RawImage ImageMemoryReader::process() {
    stbi_set_flip_vertically_on_load(verticalFlip()) ;
    return readImage() ;
}

RawImage ImageMemoryReader::readImage() {
    auto bufferSizeInt = static_cast<int>(bufferSize());
    bool isHDR = stbi_is_hdr_from_memory(bufferData(), bufferSizeInt) ;

    if (isHDR) {
        return readHDR() ;
    }
    else {
        bool is16Bits = stbi_is_16_bit_from_memory(bufferData(), bufferSizeInt) ;

        if (is16Bits) {
            return read16BitsChannel() ;
        }
        else {
            return read8BitsChannel() ;
        }
    }
}

RawImage ImageMemoryReader::read8BitsChannel() {
    uint8_t* imageData = nullptr ;

    int width = 0 ;
    int height = 0 ;
    int amountComponents = 0 ;
    auto bufferSizeInt = static_cast<int>(bufferSize());
    stbi_info_from_memory(bufferData(), bufferSizeInt, &width, &height, &amountComponents) ;

    // Usual pictures store color values in integer values, usually one byte
    // per component color.
    RawImage image(
        static_cast<ColorFormat::ID>(amountComponents),
        ColorFormat::ComponentType::Byte
    ) ;

    stbi_hdr_to_ldr_gamma(ImageReader::GammaCorrection) ;
    stbi_hdr_to_ldr_scale(ImageReader::HDRScale) ;
    imageData = stbi_load_from_memory(bufferData(), bufferSizeInt, &width, &height, &amountComponents, 0) ;
    postRead(image, width, height, imageData) ;
    return image ;
}

RawImage ImageMemoryReader::read16BitsChannel() {
    uint8_t* imageData = nullptr ;

    int width = 0 ;
    int height = 0 ;
    int amountComponents = 0 ;
    auto bufferSizeInt = static_cast<int>(bufferSize());
    stbi_info_from_memory(bufferData(), bufferSizeInt, &width, &height, &amountComponents) ;

    // Usual pictures store color values in integer values, usually one byte
    // per component color.
    RawImage image(
        static_cast<ColorFormat::ID>(amountComponents),
        ColorFormat::ComponentType::Short
    ) ;

    stbi_hdr_to_ldr_gamma(ImageReader::GammaCorrection) ;
    stbi_hdr_to_ldr_scale(ImageReader::HDRScale) ;
    unsigned short* imageDataUS = stbi_load_16_from_memory(bufferData(), bufferSizeInt, &width, &height, &amountComponents, 0) ;
    imageData = reinterpret_cast<uint8_t*>(imageDataUS) ;
    postRead(image, width, height, imageData) ;
    return image ;
}

RawImage ImageMemoryReader::readHDR() {
    uint8_t* imageData = nullptr ;

    int width = 0 ;
    int height = 0 ;
    int amountComponents = 0 ;
    auto bufferSizeInt = static_cast<int>(bufferSize());
    stbi_info_from_memory(bufferData(), bufferSizeInt, &width, &height, &amountComponents) ;

    // HDR pictures store data as floating point values.
    RawImage image(
        static_cast<ColorFormat::ID>(amountComponents),
        ColorFormat::ComponentType::FloatingPoint
    ) ;

    stbi_ldr_to_hdr_scale(ImageReader::HDRScale);
    stbi_ldr_to_hdr_gamma(ImageReader::GammaCorrection);
    float* hdrData = stbi_loadf_from_memory(bufferData(), bufferSizeInt, &width, &height, &amountComponents, 0) ;
    imageData = reinterpret_cast<uint8_t*>(hdrData) ;
    postRead(image, width, height, imageData) ;
    return image ;
}
