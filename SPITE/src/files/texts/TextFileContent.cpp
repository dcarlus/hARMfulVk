#include <stdexcept>
#include <ios>
#include <harmful/doom/utils/LogSystem.hpp>
#include "harmful/spite/files/texts/TextFileContent.hpp"
#include "harmful/spite/SPITEStrings.hpp"

using namespace Spite ;

TextFileContent::TextFileContent(const std::string& filepath)
    : m_path(filepath) {
    m_reader.setFileStream(&m_fs) ;
    m_writer.setFileStream(&m_fs) ;
}

TextFileContent::~TextFileContent() {
    if (m_fs.is_open()) {
        m_fs.close() ;
    }
}

void TextFileContent::save(const std::string& text) {
    if (m_fs.is_open()) {
        m_fs.close() ;
    }

    open_fs(std::fstream::out) ;

    m_writer.clear() ;
    m_writer.write(text) ;

    if (m_fs.is_open()) {
        m_fs.close() ;
    }
}

std::string TextFileContent::load() {
    if (m_fs.is_open()) {
        m_fs.close() ;
    }

    open_fs(std::fstream::in) ;

    std::string text ;
    m_reader.readAll(text) ;

    if (m_fs.is_open()) {
        m_fs.close() ;
    }

    return text ;
}

void TextFileContent::open_fs(std::ios_base::openmode mode) {
    // If so, open it if not already accessed.
    if (!m_fs.is_open()) {
        // If it is all OK, open the file with wanted mode.
        m_fs.open(fs::absolute(m_path).string(), mode) ;

        if (!m_fs.good()) {
            m_fs.close() ;

            throw std::ios_base::failure(
                FileMsg::Error::FailureOnOpening
                     + fs::absolute(m_path).string()
            ) ;
        }
        else {
            m_stdOpenMode = mode ;
        }
    }
}
