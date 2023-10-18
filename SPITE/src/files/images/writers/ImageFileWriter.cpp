#include <harmful/doom/utils/LogSystem.hpp>
#include <harmful/doom/debug/ErrorsManagement.hpp>
#include <harmful/doom/utils/StringExt.hpp>
#include "harmful/spite/files/images/writers/ImageFileWriter.hpp"
#include "harmful/spite/files/images/ImageUtils.hpp"
#include "harmful/spite/SPITEStrings.hpp"
#include "harmful/spite/third_party/stb_image_write.h"

using namespace Spite ;

const std::map<std::string, ImageFileWriter::Functor> ImageFileWriter::ExtensionFileSave = {
    { ImageUtils::PNGFileExtension, ImageFileWriter::SavePNG },
    { ImageUtils::JPGFileExtension, ImageFileWriter::SaveJPEG },
    { ImageUtils::JPEGFileExtension, ImageFileWriter::SaveJPEG },
    { ImageUtils::BMPFileExtension, ImageFileWriter::SaveBMP },
    { ImageUtils::RLEFileExtension, ImageFileWriter::SaveBMP },
    { ImageUtils::DIBFileExtension, ImageFileWriter::SaveBMP },
    { ImageUtils::TGAFileExtension, ImageFileWriter::SaveTGA },
    { ImageUtils::TPICFileExtension, ImageFileWriter::SaveTGA },
    { ImageUtils::HDRFileExtension, ImageFileWriter::SaveHDR }
} ;

ImageFileWriter::ImageFileWriter(
    RawImage& data,
    const fs::path& path,
    const bool verticalFlip
) : ImageWriter(data, verticalFlip),
    m_path(path)
{}

bool ImageFileWriter::processSpecific() {
    bool success = false ;
    std::string fileExtension ;

    fileExtension = m_path.extension().string() ;
    Doom::StringExt::TextCase(
        fileExtension,
        Doom::StringExt::CharacterCase::Lower
    ) ;

    if ((data().format().type() == ColorFormat::FloatingPoint)
            && (fileExtension != ImageUtils::HDRFileExtension)) {
        Doom::LogSystem::WriteLine(
            Doom::LogSystem::Gravity::Info,
            WriterMsg::Info::HDRExtensionNotMatching,
            m_path.string()
        ) ;

        // It is not possible to convert HDR to another format here!
        m_path.replace_extension(ImageUtils::HDRFileExtension) ;
        fileExtension = ImageUtils::HDRFileExtension ;
    }

    if (ExtensionFileSave.count(fileExtension)) {
        auto save = ExtensionFileSave.at(fileExtension) ;
        success = save(
            data(),
            m_path.string()
        ) ;

        Doom::LogSystem::WriteLine(
            Doom::LogSystem::Gravity::Info,
            WriterMsg::Info::ImageWrittenOK,
            m_path.string()
        ) ;
    }

    return success ;
}

bool ImageFileWriter::SavePNG(
    RawImage& image,
    const std::string& path
) {
    auto amountComponents = image.format().amountOfComponents() ;
    auto pixelSize = image.format().pixelSizeInBytes() ;
    auto& imageBytes = image.data() ;

    return stbi_write_png(
        path.c_str(),
        image.width(),
        image.height(),
        amountComponents,
        imageBytes.data(),
        pixelSize * image.width()
    ) ;
}

bool ImageFileWriter::SaveJPEG(
    RawImage& image,
    const std::string& path
) {
    auto amountComponents = image.format().amountOfComponents() ;
    auto& imageBytes = image.data() ;

    return stbi_write_jpg(
        path.c_str(),
        image.width(),
        image.height(),
        amountComponents,
        imageBytes.data(),
        ImageWriter::JPEGQuality
    ) ;
}

bool ImageFileWriter::SaveTGA(
    RawImage& image,
    const std::string& path
) {
    auto amountComponents = image.format().amountOfComponents() ;
    auto& imageBytes = image.data() ;

    return stbi_write_tga(
        path.c_str(),
        image.width(),
        image.height(),
        amountComponents,
        imageBytes.data()
    ) ;
}

bool ImageFileWriter::SaveBMP(
    RawImage& image,
    const std::string& path
) {
    auto amountComponents = image.format().amountOfComponents() ;
    auto& imageBytes = image.data() ;

    return stbi_write_bmp(
        path.c_str(),
        image.width(),
        image.height(),
        amountComponents,
        imageBytes.data()
    ) ;
}

bool ImageFileWriter::SaveHDR(
    RawImage& image,
    const std::string& path
) {
    auto amountComponents = image.format().amountOfComponents() ;
    auto& imageBytes = image.data() ;
    auto* imageFloat = reinterpret_cast<float*>(imageBytes.data()) ;

    return stbi_write_hdr(
        path.c_str(),
        image.width(),
        image.height(),
        amountComponents,
        imageFloat
    ) ;
}
