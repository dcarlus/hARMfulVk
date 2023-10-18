#ifndef __SPITE__IMAGE_WRITER__
#define __SPITE__IMAGE_WRITER__

#include <functional>
#include <harmful/doom/utils/Platform.hpp>
#include "harmful/spite/files/images/data/RawImage.hpp"

namespace Spite {
    /// <summary>
    /// Dedicated class to store compressed images.
    /// </summary>
    class ImageWriter {
        public:
            /// <summary>
            /// Filter algorithms on data for optimum compression.
            /// </summary>
            enum PNGFilter {
                None,
                Sub,
                Up,
                Average,
                Paeth
            } ;

        protected:
            /// <summary>
            /// JPEG quality.
            /// </summary>
            static int JPEGQuality ;

        private:
            /// <summary>
            /// Data to save.
            /// </summary>
            std::reference_wrapper<RawImage> m_data ;

            /// <summary>
            /// true to flip vertically on save; false otherwise.
            /// </summary>
            bool m_verticalFlip = false ;

        public:
            /// <summary>
            /// Create a new ImageWriter to write compressed data in a file.
            /// </summary>
            /// <param name="data">
            /// Binary data containing raw picture data.
            /// </param>
            /// <param name="verticalFlip">
            /// true to flip vertically; false otherwise.
            /// </param>
            exported ImageWriter(
                RawImage& data,
                const bool verticalFlip = false
            ) ;

            /// <summary>
            /// Perform save.
            /// </summary>
            /// <returns>true on success; false otherwise.</returns>
            exported bool process() ;

            /**
             * 
             * @param   level   
             *                  
             */

            /// <summary>
            /// Set the PNG compression level. Default is 8.
            /// </summary>
            /// <param name="level">
            /// Compression level between 0 (no compression) and 9 (highly
            /// compressed).
            /// </param>
            exported static void SetPNGCompressionLevel(const int level) ;

            /// <summary>
            /// Set the PNG filter, applied before compression.
            /// Default is None.
            /// </summary>
            /// <param name="filter">
            /// Filter algorithms on data for optimum compression.
            /// </param>
            exported static void SetPNGFilter(const PNGFilter filter) ;

            /// <summary>
            /// Set the JPEG quality. Default is 90.
            /// </summary>
            /// <param name="quality">
            /// JPEG quality between 1 (highly compressed but ugly) and 100
            /// (nice image but heavier on disk).
            /// </param>
            //exported static void SetJPEGQuality(const int quality) ;

            /// <summary>
            /// Write TGA files with RLE compression. Default is true.
            /// </summary>
            /// <param name="rleEnabled">
            /// true to enable; false otherwise.
            /// </param>
            exported static void SetCompressTGAWithRLE(const bool rleEnabled) ;

        protected:
            /// <summary>
            /// Perform save.
            /// </summary>
            /// <returns>true on success; false otherwise.</returns>
            virtual exported bool processSpecific() = 0 ;

            /// <summary>
            /// Get the data to write.
            /// </summary>
            /// <returns>Raw data of the picture.</returns>
            exported RawImage& data() {
                return m_data.get() ;
            }

            /// <summary>
            /// Flag to flip the picture vertically.
            /// </summary>
            /// <returns>
            /// true to flip vertically on load; false otherwise.
            /// </returns>
            exported bool verticalFlip() {
                return m_verticalFlip ;
            }
    } ;
}

#endif
