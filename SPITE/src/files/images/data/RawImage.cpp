#include <stdexcept>
#include <string.h>
#include "harmful/spite/files/images/data/RawImage.hpp"
#include "harmful/spite/SPITEStrings.hpp"

using namespace Spite ;

RawImage::RawImage(
    const ColorFormat::ID format,
    const ColorFormat::ComponentType type
) : m_format(format),
    m_type(type) {}

void RawImage::setDimensions(
    const uint32_t& width,
    const uint32_t& height
) {
    if (m_format == ColorFormat::UnknownID || m_type == ColorFormat::UnknownType) {
        throw std::runtime_error(RawImageMsg::Error::UndefinedColorFormatWhenSettingSize) ;
    }

    m_width = width ;
    m_height = height ;
    m_pixelData.clear();
    m_pixelData.resize(width * height * format().pixelSizeInBytes()) ;
}

void RawImage::setFormat(
    const ColorFormat::ID format,
    const ColorFormat::ComponentType type
) {
    m_format = format ;
    m_type = type ;
    m_pixelData.clear();
}

const ColorFormat& RawImage::format() {
    return ColorFormat::Get(m_format, m_type) ;
}

std::vector<uint8_t>& RawImage::data() {
    return m_pixelData ;
}

uint32_t RawImage::width() const {
    return m_width ;
}

uint32_t RawImage::height() const {
    return m_height ;
}
