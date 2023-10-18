#include <stdexcept>
#include <iostream>
#include "harmful/spite/files/images/data/ColorFormat.hpp"
#include "harmful/spite/SPITEStrings.hpp"

#define ByteSizeInBits  8

using namespace Spite ;

std::map<int, ColorFormat> ColorFormat::ColorFormats ;

ColorFormat::ColorFormat(
    const ColorFormat::ID id,
    const std::string& name,
    const uint8_t amountComponents,
    const uint8_t componentSize,
	const ColorFormat::ComponentType type
) : m_id(id),
    m_name(name),
    m_amountComponents(amountComponents),
    m_componentSize(componentSize),
    m_pixelSize(m_amountComponents * m_componentSize),
    m_colorDepth(amountComponents * ByteSizeInBits),
	m_type(type),
    m_isInitialized(true) {}


void ColorFormat::Create(
	const ColorFormat::ID id,
	const ColorFormat::ComponentType type
) {
    auto format = static_cast<uint32_t>(id) | static_cast<uint32_t>(type) ;

    if (ColorFormats.count(format) == 0) {
        // Get the data on the wanted color format.
        std::string name ;
		unsigned char amountComponents ;
        unsigned char componentSize ;
        SetDataForFormat(id, type, name, amountComponents, componentSize) ;
        // Apply the data to the color format.
        ColorFormats[format] = ColorFormat(
            id,
            name,
            amountComponents,
            componentSize,
			type
        ) ;
    }
}

void ColorFormat::Clear() {
    ColorFormats.clear() ;
}

const ColorFormat& ColorFormat::Get(
    const ColorFormat::ID id,
	const ColorFormat::ComponentType type
) {
    auto format = static_cast<uint32_t>(id) | static_cast<uint32_t>(type) ;

    Create(id, type) ;
    return ColorFormats.at(format) ;
}

ColorFormat::ID ColorFormat::id() const {
    return m_id ;
}

const std::string& ColorFormat::name() const {
    return m_name ;
}

uint8_t ColorFormat::amountOfComponents() const {
    return m_amountComponents ;
}

uint8_t ColorFormat::pixelSizeInBytes() const {
    return m_pixelSize ;
}

uint8_t ColorFormat::colorDepth() const {
    return m_colorDepth ;
}

uint8_t ColorFormat::componentSize() const {
    return m_componentSize ;
}

ColorFormat::ComponentType ColorFormat::type() const {
	return m_type ;
}

bool ColorFormat::isInitialized() const {
    return m_isInitialized ;
}

void ColorFormat::SetDataForFormat(
    const ColorFormat::ID& id,
    const ColorFormat::ComponentType& type,
    std::string& name,
    uint8_t& amountComponents,
    uint8_t& componentSize
) {
    switch (id) {
        case Gray:
            name = "Gray";
			amountComponents = 1 ;
            break;

        case GrayAlpha:
            name = "GrayAlpha";
            amountComponents = 2 ;
            break;

        case RGB:
            name = "RGB" ;
			amountComponents = 3 ;
            break ;

        case RGBA:
            name = "RGBA" ;
			amountComponents = 4 ;
            break ;

        default:
            throw std::invalid_argument(ColorFormatMsg::Error::UnknownFormat) ;
            break ;
    }

	switch (type) {
		case Byte:
			componentSize = static_cast<unsigned char>(sizeof(unsigned char)) ;
			break ;

        case Short:
			componentSize = static_cast<unsigned char>(sizeof(unsigned short)) ;
			break ;

		case FloatingPoint:
			componentSize = static_cast<unsigned char>(sizeof(float)) ;
			break ;

		default:
			throw std::invalid_argument(ColorFormatMsg::Error::UnknownFormat) ;
			break ;
	}
}
