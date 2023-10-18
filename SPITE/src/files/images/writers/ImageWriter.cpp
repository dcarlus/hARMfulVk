#include <algorithm>
#include <harmful/doom/utils/StringExt.hpp>
#include <harmful/doom/debug/ErrorsManagement.hpp>
#include <harmful/doom/utils/LogSystem.hpp>
#include "harmful/spite/files/images/writers/ImageWriter.hpp"
#include "harmful/spite/SPITEStrings.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "harmful/spite/third_party/stb_image_write.h"

using namespace Spite ;
namespace fs = std::filesystem ;

int ImageWriter::JPEGQuality = 90 ;

ImageWriter::ImageWriter(
    RawImage& data,
    const bool verticalFlip
) : m_data(data),
    m_verticalFlip(verticalFlip)
{}

bool ImageWriter::process() {
    bool cachedFlipBefore = stbi__flip_vertically_on_write ;
    stbi_flip_vertically_on_write(m_verticalFlip) ;
    bool success = processSpecific() ;
    stbi_flip_vertically_on_write(cachedFlipBefore) ;
    return success ;
}

void ImageWriter::SetPNGCompressionLevel(const int level) {
    const int MinLevel = 0 ;
    const int MaxLevel = 9 ;
    int clampedLevel = std::clamp(level, MinLevel, MaxLevel) ;
    stbi_write_png_compression_level = clampedLevel ;
}

void ImageWriter::SetPNGFilter(const PNGFilter filter) {
    stbi_write_force_png_filter = filter ;
}

void ImageWriter::SetCompressTGAWithRLE(const bool rleEnabled) {
    stbi_write_tga_with_rle = rleEnabled ;
}
