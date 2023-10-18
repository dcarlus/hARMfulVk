#include "harmful/spite/readers/BinaryFileReader.hpp"

using namespace Spite ;

void BinaryFileReader::readAllBytes(char* blob, const size_t size) {
    m_stream -> seekg(0, std::ios::beg) ;
    m_stream -> read(blob, size) ;
}

void BinaryFileReader::readAllBytes(std::vector<char>& blob) {
    m_stream -> seekg(0, std::ios::end) ;
    std::ifstream::pos_type pos = m_stream -> tellg();
    blob.resize(pos) ;
    readAllBytes(&blob[0], blob.size()) ;
}

void BinaryFileReader::readAllBytes(std::vector<unsigned char>& blob) {
    m_stream -> seekg(0, std::ios::end) ;
    std::ifstream::pos_type pos = m_stream -> tellg();
    blob.resize(pos) ;

    char* buffer = reinterpret_cast<char*>(&blob[0]) ;
    readAllBytes(buffer, blob.size()) ;
}
