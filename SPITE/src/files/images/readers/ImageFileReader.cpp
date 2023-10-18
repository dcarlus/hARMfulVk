#include "harmful/spite/files/images/readers/ImageFileReader.hpp"
#include "harmful/spite/third_party/stb_image.h"

using namespace Spite ;

ImageFileReader::ImageFileReader(
    const std::string& path,
    const bool verticalFlip
) : ImageReader(verticalFlip),
    m_filepath(path) {}

RawImage ImageFileReader::process() {
    stbi_set_flip_vertically_on_load(verticalFlip()) ;
    return readImage() ;
}

RawImage ImageFileReader::readImage() {
    bool isHDR = stbi_is_hdr(m_filepath.c_str()) ;

    if (isHDR) {
        return readHDR() ;
    }
    else {
        bool is16Bits = stbi_is_16_bit(m_filepath.c_str()) ;

        if (is16Bits) {
            return read16BitsChannel() ;
        }
        else {
            return read8BitsChannel() ;
        }
    }
}

RawImage ImageFileReader::read8BitsChannel() {
    unsigned char* imageData = nullptr ;

    int width = 0 ;
    int height = 0 ;
    int amountComponents = 0 ;
    stbi_info(m_filepath.c_str(), &width, &height, &amountComponents) ;

    // Usual pictures store color values in integer values, usually one byte
    // per component color.
    RawImage image(
        static_cast<ColorFormat::ID>(amountComponents),
        ColorFormat::ComponentType::Byte
    ) ;

    stbi_hdr_to_ldr_gamma(ImageReader::GammaCorrection) ;
    stbi_hdr_to_ldr_scale(ImageReader::HDRScale) ;
    imageData = stbi_load(m_filepath.c_str(), &width, &height, &amountComponents, 0) ;
    postRead(image, width, height, imageData) ;
    return image ;
}

RawImage ImageFileReader::read16BitsChannel() {
    unsigned char* imageData = nullptr ;

    int width = 0 ;
    int height = 0 ;
    int amountComponents = 0 ;
    stbi_info(m_filepath.c_str(), &width, &height, &amountComponents) ;

    // Usual pictures store color values in integer values, usually one byte
    // per component color.
    RawImage image(
        static_cast<ColorFormat::ID>(amountComponents),
        ColorFormat::ComponentType::Short
    ) ;

    stbi_hdr_to_ldr_gamma(ImageReader::GammaCorrection) ;
    stbi_hdr_to_ldr_scale(ImageReader::HDRScale) ;
    unsigned short* imageDataUS = stbi_load_16(m_filepath.c_str(), &width, &height, &amountComponents, 0) ;
    imageData = reinterpret_cast<unsigned char*>(imageDataUS) ;
    postRead(image, width, height, imageData) ;
    return image ;
}

RawImage ImageFileReader::readHDR() {
    unsigned char* imageData = nullptr ;

    int width = 0 ;
    int height = 0 ;
    int amountComponents = 0 ;
    stbi_info(m_filepath.c_str(), &width, &height, &amountComponents) ;

    // HDR pictures store data as floating point values.
    RawImage image(
        static_cast<ColorFormat::ID>(amountComponents),
        ColorFormat::ComponentType::FloatingPoint
    ) ;

    stbi_ldr_to_hdr_scale(ImageReader::HDRScale);
    stbi_ldr_to_hdr_gamma(ImageReader::GammaCorrection);
    float* hdrData = stbi_loadf(m_filepath.c_str(), &width, &height, &amountComponents, 0) ;
    imageData = reinterpret_cast<unsigned char*>(hdrData) ;
    postRead(image, width, height, imageData) ;
    return image ;
}
