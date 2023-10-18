#include <streambuf>
#include "harmful/spite/readers/TextFileReader.hpp"

using namespace Spite ;

void TextFileReader::readAll(std::string& content) {
    // Reserve the required space to put all the characters in a single string.
    // It will avoid a lot of reallocations while reading the whole file.
    m_stream -> seekg(0, std::ios::end) ;
    content.reserve(m_stream -> tellg()) ;
    m_stream -> seekg(0, std::ios::beg) ;

    // Read all the content and put it in the string.
    content.assign(
        std::istreambuf_iterator<char>(*m_stream),
        std::istreambuf_iterator<char>()
    ) ;
}
