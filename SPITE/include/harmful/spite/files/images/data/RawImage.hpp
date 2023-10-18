#ifndef __SPITE__RAW_IMAGE_DATA__
#define __SPITE__RAW_IMAGE_DATA__

#include <vector>
#include <harmful/doom/utils/Platform.hpp>
#include "harmful/spite/files/images/data/ColorFormat.hpp"

namespace Spite {
    /// <summary>
    /// Image containing raw uncompressed data.
    /// </summary>
    class RawImage final {
        private:
            /// <summary>
            /// Width of the picture.
            /// </summary>
            uint32_t m_width = 0 ;

            /// <summary>
            /// Height of the picture
            /// </summary>
            uint32_t m_height = 0 ;

            /// <summary>
            /// Picture pixel data.
            /// </summary>
            std::vector<uint8_t> m_pixelData ;

            /// <summary>
            /// Format of the picture.
            /// </summary>
            ColorFormat::ID m_format ;

			/// <summary>
			/// Data type of the picture.
			/// </summary>
			ColorFormat::ComponentType m_type ;

        public:
            /// <summary>
            /// Create a new RawImage.
            /// </summary>
            /// <param name="format">Format of the RawImage.</param>
            /// <param name="type">Data type of the picture.</param>
            exported RawImage(
                const ColorFormat::ID format = ColorFormat::UnknownID,
                const ColorFormat::ComponentType type = ColorFormat::UnknownType
            ) ;

            /// <summary>
            /// Set the dimensions of the picture.
            /// </summary>
            /// <param name="width">Width of the picture.</param>
            /// <param name="height">Height of the picture</param>
            exported void setDimensions(
                const uint32_t& width,
                const uint32_t& height
            ) ;

            /// <summary>
            /// Set the color format of the picture.
            /// </summary>
            /// <param name="format">The format of the picture.</param>
            /// <param name="type">Data type of the picture.</param>
            exported void setFormat(
                const ColorFormat::ID format,
                const ColorFormat::ComponentType type
            ) ;

            /// <summary>
            /// Get the ColorFormat used by the RawImage.
            /// </summary>
            /// <returns>ColorFormat used by the RawImage.</returns>
            exported const ColorFormat& format() ;

            /// <summary>
            /// Get the image raw data.
            /// </summary>
            /// <returns>
            /// Output the raw data of the image. Data is expected to be an
            /// array of bytes.
            /// </returns>
            /// <remarks>
            /// data should not be initialized, an array is allocated on
            /// getting data.
            /// </remarks>
            exported std::vector<uint8_t>& data() ;

            /// <summary>
            /// Width of the image.
            /// </summary>
            /// <returns>The width of the image.</returns>
            exported uint32_t width() const ;

            /// <summary>
            /// Height of the image.
            /// </summary>
            /// <returns>The height of the image.</returns>
            exported uint32_t height() const ;
    } ;
}

 #endif
