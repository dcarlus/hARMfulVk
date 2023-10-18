#ifndef __SPITE__STRINGS__
#define __SPITE__STRINGS__

#include "harmful/doom/utils/Translation.hpp"
#include <string>

namespace Spite {
    namespace FileMsg {
        namespace Error {
            static const std::string UnableToOpen = i18n("Unable to open ");
            static const std::string OnlyRegularFiles = i18n("Only open regular files are allowed.");
            static const std::string UnsupportedPlatform = i18n("Unsupported platform.");
            static const std::string MkdirFailed = i18n("MKDIR unable to create ");

            static const std::string CannotSaveFile = i18n("Cannot save file at ");
            static const std::string NoOutputMode = i18n(": not opened in output mode.");
            static const std::string CannotReadFile = i18n("Cannot read file at ");
            static const std::string NoInputMode = i18n(": not opened in input mode.");

            static const std::string InsufficientMemory = i18n("Unable to open %s because of memory lack.");
            static const std::string FailureOnOpening = i18n("An unexpected error occured while opening file ");
            static const std::string UnknownAccessMode = i18n("Unknown file access mode.");

            static const std::string BadAccessMode = i18n("This file type can only be opened in ReadOnly or WriteOnly modes.");
        };
    };

    namespace JPEGMsg {
        namespace Error {
            static const std::string DecompressiongInitFailed = i18n("Error on initialization of JPEG decompression for ");
            static const std::string FailureWhileDecompressing = i18n("An error occurred while decompressing ");
        };
    };

    namespace PNGMsg {
        namespace Error {
            static const std::string NotPNGFile = i18n("The provided file is not a PNG image: %s.");
            static const std::string BadPNGHeaderSize = i18n("The header size of the PNG file does not match with the expected length. Is it a PNG file?");
            static const std::string InitializationStructureFailed = i18n("Unable to initialize PNG structure for ");
            static const std::string InitializationInfosFailed = i18n("Unable to initialize PNG infos for ");
        };
    };

    namespace ColorFormatMsg {
        namespace Error {
            static const std::string UnknownFormat = i18n("Unknown color format.");
        }
    };

    namespace RawImageMsg {
        namespace Error {
            static const std::string UndefinedColorFormatWhenSettingSize = i18n("Color format must be defined before setting the image size.");
        }
    }

    namespace WriterMsg {
        namespace Error {
            static const std::string EndOfFile = i18n("End of file is reached while writing.");
        }

        namespace Info {
            // Keep final space!
            static const std::string HDRExtensionNotMatching = i18n("The extension of the file is modified to fit its HDR file format: ");
            // Keep final space!
            static const std::string ImageWrittenOK = i18n("The image file has successfully been written: ");
        }
    }

    namespace ReaderMsg {
        namespace Error {
            static const std::string EndOfFile = i18n("End of file is reached while reading.");
        }
    }
} ;

// Files
#define STR_ERROR__FILE__MEMORY_LACK "Unable to open %s because of memory lack."
#define STR_ERROR__FILE__ERROR_ON_OPENING "An unexpected error occured while opening file "
#define STR_EROOR__FILE__UNKNOWN_ACCESS_MODE "Unknown file access mode."

// JPEG
#define STR_ERROR__FILE__JPEG_DECOMPRESSION_INIT "Error on initialization of JPEG decompression for "
#define STR_ERROR__FILE__JPEG_WHILE_DECOMPRESSING "An error occurred while decompressing "

// PNG
#define STR_ERROR__FILE__PNG_NOT_A_PNG "The provided file is not a PNG image: %s."
#define STR_ERROR__FILE__PNG_INIT_STRUCT "Unable to initialize PNG structure for "
#define STR_ERROR__FILE__PNG_INIT_INFOS "Unable to initialize PNG infos for "


// Color formats
#define STR_ERROR__COLOR_FORMAT__UNKNOWN "Unknown color format."

// Raw image
#define STR_ERROR__RAW_IMAGE__DEFINE_COLOR_FORMAT_BEFORE_SIZE "Color format must be defined before setting the image size."


// Writers
#define STR_ERROR__WRITERS__EOF "End of file is reached while writing."

// Readers
#define STR_ERROR__READERS__EOF "End of file is reached while reading."

#endif
