#include "utils/LogSystem.hpp"
#include "utils/Translation.hpp"

using namespace Doom ;

const std::string LogSystem::LogFileExtension = ".log" ;
std::unique_ptr<LogSystem> LogSystem::LogInstance = nullptr ;
std::mutex LogSystem::ClassMutex ;

LogSystem::LogSystem(const std::string& path, const Gravity minLevel) {
    m_minLevel = minLevel ;
    m_printer = std::make_unique<FilePrinter>(path) ;
}

std::string LogSystem::FormatCurrentDateTime() {
    return "[" + Time::GetDateTime() + "] " ;
}

void LogSystem::Initialize(const std::string& path, const Gravity minLevel) {
    ClassMutex.lock() ;
    {
        // The instance has already been initialized. This is not supported
        // and this behavior throws an exception. However, this is not a
        // critical error and the exception can be caught to continue the
        // execution.
        if (!LogInstance) {
            LogInstance = std::unique_ptr<LogSystem>(new LogSystem(path + LogFileExtension, minLevel)) ;
        }
    }
    ClassMutex.unlock() ;
}
