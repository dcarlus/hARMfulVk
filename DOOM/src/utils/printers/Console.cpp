#include "harmful/doom/utils/printers/Console.hpp"

namespace Doom {
    Console::Console() {
        checkInputStream() ;
    }

    void Console::checkInputStream() {
        if (std::cin.eof()) {
            m_inputState = Console::State::Error ;
            clearInputStream() ;
        }
        else if (std::cin.bad()) {
            m_inputState = Console::State::Bad ;
            clearInputStream() ;
        }
        else if (std::cin.fail()) {
            m_inputState = Console::State::Fail ;
            clearInputStream() ;
        }
        else {
            m_inputState = Console::State::OK ;
        }
    }

    void Console::clearInputStream() {
        std::cin.clear() ;
        std::cin.seekg(0, std::ios::end) ;

        if (!std::cin.fail()) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max()) ;
        }
        else {
            std::cin.clear() ;
        }
    }
} ;
