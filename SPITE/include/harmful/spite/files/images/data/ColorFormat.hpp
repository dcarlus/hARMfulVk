#ifndef __SPITE__COLOR_FORMAT__
#define __SPITE__COLOR_FORMAT__

#include <string>
#include <map>
#include <harmful/doom/utils/Platform.hpp>

namespace Spite {
    /// <summary>
    /// Class to contain informations on color format used by pictures.
    /// </summary>
    class ColorFormat final {
        public:
            /// <summary>
            /// Format to identity the supported color formats.
            /// </summary>
            enum ID {
                UnknownID 	= 0x00,
                Gray 		= 0x01,
                GrayAlpha 	= 0x02,
                RGB 		= 0x03,
                RGBA 		= 0x04
            } ;

			/// <summary>
			/// Format of data storage in the picture for each component.
			/// </summary>
			enum ComponentType {
				UnknownType   = 0x10,
				Byte		  = 0x20,
                Short         = 0x40,
				FloatingPoint = 0x30
			} ;

        private:
            /// <summary>
            /// Amount of available IDs.
            /// </summary>
			static const unsigned char AmountOfIDs = 5 ;

            /// <summary>
            /// Amount of available types.
            /// </summary>
			static const unsigned char AmountOfTypes = 3 ;

			/// <summary>
			/// Amount of available formats.
			/// </summary>
			static const unsigned char AmountOfFormats = AmountOfIDs * AmountOfTypes ;

			/// <summary>
			/// All the available ColorFormat to describe the organization of
            /// data inside the raw images.
			/// </summary>
			static std::map<int, ColorFormat> ColorFormats ;

            /// <summary>
            /// ID of the color format.
            /// </summary>
            ID m_id = ID::UnknownID ;

            /// <summary>
            /// Name of the ColorFormat.
            /// </summary>
            std::string m_name ;

			/// <summary>
			/// Amount color components.
			/// </summary>
			uint8_t m_amountComponents = 0 ;

            /// <summary>
            /// Size of each component in bytes.
            /// </summary>
            uint8_t m_componentSize = 0 ;

            /// <summary>
            /// Total size of each pixel information in bytes.
            /// </summary>
            uint8_t m_pixelSize = 0 ;

            /// <summary>
            /// Color depth of the ColorFormat.
            /// </summary>
            uint8_t m_colorDepth = 0 ;

			/// <summary>
			/// Format of data storage in the picture for each component.
			/// </summary>
			ComponentType m_type = ComponentType::UnknownType ;

            /// <summary>
            /// To check if a ColorFormat has been initialized.
            /// </summary>
            bool m_isInitialized = false ;

        public:
            /// <summary>
            /// Empty constructor, just for optimization.
            /// </summary>
            exported ColorFormat() = default ;

            // Rule of 5 stuff.
            exported ColorFormat(const ColorFormat& copied) = default;
            exported ColorFormat(ColorFormat&& moved) = default;
            exported ColorFormat& operator=(const ColorFormat& copied) = default;
            exported ColorFormat& operator=(ColorFormat&& moved) = default;
            exported virtual ~ColorFormat() noexcept = default;

            /// <summary>
            /// Create a new ColorFormat.
            /// </summary>
            /// <param name="id">ID of the ColorFormat.</param>
            /// <param name="name">Name of the ColorFormat.</param>
            /// <param name="amountComponents">Amount of components.</param>
            /// <param name="componentSize">Size of each component in bytes.</param>
            /// <param name="type">Format of data storage.</param>
            exported ColorFormat(
				const ColorFormat::ID id,
			    const std::string& name,
			    const uint8_t amountComponents,
			    const uint8_t componentSize,
				const ColorFormat::ComponentType type
            ) ;

            /// <summary>
            /// Create a ColorFormat.
            /// </summary>
            /// <param name="id">ID of the ColorFormat.</param>
            /// <param name="type">Data type.</param>
            exported static void Create(
				const ColorFormat::ID id,
				const ColorFormat::ComponentType type
			) ;

            /// <summary>
            /// Clear all ColorFormat instances.
            /// </summary>
            exported static void Clear() ;

            /// <summary>
            /// Get the wanted ColorFormat.
            /// </summary>
            /// <param name="id">ID of the ColorFormat.</param>
            /// <param name="type">Data type.</param>
            /// <returns>The wanted ColorFormat.</returns>
            exported static const ColorFormat& Get(
                const ColorFormat::ID id,
				const ColorFormat::ComponentType type
            ) ;

            /// <summary>
            /// Get the ID of the ColorFormat.
            /// </summary>
            /// <returns>ID of the ColorFormat.</returns>
            exported ID id() const ;

            /// <summary>
            /// Get the name of the ColorFormat.
            /// </summary>
            /// <returns>Name of the ColorFormat.</returns>
            exported const std::string& name() const ;

            /// <summary>
            /// Get the amount of components used in the ColorFormat.
            /// </summary>
            /// <returns>Amount of components in the ColorFormat.</returns>
            exported uint8_t amountOfComponents() const ;

            /// <summary>
            /// Get the total size in bytes of each pixel information.
            /// </summary>
            /// <returns>
            /// Amount of bytes used to represent each pixel of an image.
            /// </returns>
            exported uint8_t pixelSizeInBytes() const ;

            /// <summary>
            /// Get the color depth of the ColorFormat.
            /// </summary>
            /// <returns>Color depth in bits.</returns>
            exported uint8_t colorDepth() const ;

            /// <summary>
            /// Get the size of each component in bytes.
            /// </summary>
            /// <returns>Size of a component in bytes.</returns>
            exported uint8_t componentSize() const ;

			/// <summary>
			/// Format of data storage in the picture for each component.
			/// </summary>
			/// <returns>Format of data storage.</returns>
			exported ComponentType type() const ;

        private:
            /// <summary>
            /// Check if a ColorFormat has been initialized.
            /// </summary>
            /// <returns>true if initialized, false else.</returns>
            bool isInitialized() const ;

            /// <summary>
            /// Set the data for the given ID of color format.
            /// </summary>
            /// <param name="id">ID of the ColorFormat.</param>
            /// <param name="type">Format of data storage.</param>
            /// <param name="name">Name of the ColorFormat.</param>
            /// <param name="amountComponents">Amount of components.</param>
            /// <param name="componentSize">Size of each component in bytes.</param>
            static void SetDataForFormat(
				const ColorFormat::ID& id,
                const ColorFormat::ComponentType& type,
			    std::string& name,
			    uint8_t& amountComponents,
                uint8_t& componentSize
            ) ;
    } ;
}

#endif
