#ifndef __DOOM__LOG_SYSTEM__
#define __DOOM__LOG_SYSTEM__

#include "harmful/doom/utils/Platform.hpp"
#include "harmful/doom/utils/Time.hpp"
#include "harmful/doom/utils/printers/Console.hpp"
#include "harmful/doom/utils/printers/FilePrinter.hpp"
#include "harmful/doom/DOOMStrings.hpp"
#include <cstdint>
#include <memory>
#include <mutex>

namespace Doom {
    /// <summary>
    /// System to write logs in the Console and/or in a file.
    /// </summary>
    class LogSystem final {
        public:
            /// <summary>
            /// Extension of the log file.
            /// </summary>
            static const inline std::string LogFileExtension = ".log";

            /// <summary>
            /// Level of gravity of the log messages.
            /// </summary>
            enum class Gravity: int8_t {
                Critical = 0,
                Error,
                Warning,
                Info,
                Debug
            } ;

        private:
            /// <summary>
            /// The unique instance of the LogSystem.
            /// </summary>
            static inline std::unique_ptr<LogSystem> LogInstance = nullptr;

            /// <summary>
            /// Mutex for the static methods of the class.
            /// </summary>
            static inline std::mutex ClassMutex ;

            /// <summary>
            /// Avoid concurrent accesses to the LogSystem.
            /// </summary>
            std::mutex m_mutex ;

            /// <summary>
            /// Console of the LogSystem.
            /// </summary>
            Console m_console ;

            /// <summary>
            /// File printer to save important log messages.
            /// </summary>
            std::unique_ptr<FilePrinter> m_printer = nullptr ;

            /// <summary>
            /// Minimal level to write logs, lower gravity messages are ignored.
            /// </summary>
            Gravity m_minLevel ;

        private:
            /// <summary>
            /// Instantiate the LogSystem.
            /// </summary>
            /// <param name="path">
            /// Path to the file that will contain the output log messages.
            /// </param>
            /// <param name="minLevel">
            /// Minimal level of the log system messages to be written.
            /// </param>
            LogSystem(
                const std::string& path,
                const Gravity minLevel
             ) ;

            /// <summary>
            /// Format the current date and time to be printed in the logs.
            /// </summary>
            /// <returns>
            /// String representing the printed date and time in the logs.
            /// </returns>
            exported static std::string FormatCurrentDateTime() ;

        public:
            /// <summary>
            /// Initialize the LogSystem. This is required before any call to
            /// the GetInstance function.
            /// </summary>
            /// <param name="path">
            /// Path to the file that will contain the output log messages.
            /// </param>
            /// <param name="minLevel">
            /// Minimal level of the log system messages to be written.
            /// </param>
            exported static void Initialize(
                const std::string& path,
                const Gravity minLevel
            ) ;

            /// <summary>
            /// To know if the LogSystem is ready to be used.
            /// </summary>
            /// <see cref="Initialize"/>
            exported static bool Ready() {
                return LogInstance != nullptr ;
            }

            /// <summary>
            /// Write a message on the Console and the FilePrinter.
            /// </summary>
            /// <param name="level">Level of gravity for the provided value.</param>
            /// <param name="value">The value to be printed.</param>
            template<class T>
            exported static void WriteLine(const Gravity level, const T& value) {
                if (!LogInstance) {
                    throw std::runtime_error(Doom::Texts::LogSys_NotInitialized) ;
                }

                if (level <= LogInstance -> m_minLevel) {
                    std::string dateTime = FormatCurrentDateTime() ;

                    LogInstance -> m_mutex.lock() ;
                    {
                        LogInstance -> m_console.writeLine(dateTime, value) ;
                        LogInstance -> m_printer -> writeLine(dateTime, value) ;
                    }
                    LogInstance -> m_mutex.unlock() ;
                }
            }

            /// <summary>
            /// Write a message on the Console and the FilePrinter.
            /// </summary>
            /// <param name="level">Level of gravity for the provided value.</param>
            /// <param name="value">The value to be printed.</param>
            /// <param name="args">Remaining arguments to be printed.</param>
            template<class T, class ... Args>
            exported static void WriteLine(
                const Gravity level, 
                const T& value, 
                const Args& ... args
            ) {
                if (!LogInstance) {
                    throw std::runtime_error(Doom::Texts::LogSys_NotInitialized) ;
                }

                if (level <= LogInstance -> m_minLevel) {
                    std::string dateTime = FormatCurrentDateTime() ;

                    LogInstance -> m_mutex.lock() ;
                    {
                        LogInstance -> m_console.write(dateTime) ;
                        LogInstance -> m_console.writeLine(value, args...) ;

                        LogInstance -> m_printer -> write(dateTime) ;
                        LogInstance -> m_printer -> writeLine(value, args...) ;
                    }
                    LogInstance -> m_mutex.unlock() ;
                }
            }

            /// <summary>
            /// Write a message on the Console.
            /// </summary>
            /// <param name="level">Level of gravity for the provided value.</param>
            /// <param name="value">The value to be printed.</param>
            template<class T>
            exported static void PrintLine(const Gravity level, const T& value) {
                if (!LogInstance) {
                    throw std::runtime_error(Doom::Texts::LogSys_NotInitialized) ;
                }

                if (level <= LogInstance -> m_minLevel) {
                    std::string dateTime = FormatCurrentDateTime() ;

                    LogInstance -> m_mutex.lock() ;
                    {
                        LogInstance -> m_console.writeLine(dateTime, value) ;
                    }
                    LogInstance -> m_mutex.unlock() ;
                }
            }

            /// <summary>
            /// Write a message on the Console.
            /// </summary>
            /// <param name="level">Level of gravity for the provided value.</param>
            /// <param name="value">The value to be printed.</param>
            /// <param name="args">Remaining arguments to be printed.</param>
            template<class T, class ... Args>
            exported static void PrintLine(
                const Gravity level,
                const T& value,
                const Args& ... args
            ) {
                if (!LogInstance) {
                    throw std::runtime_error(Doom::Texts::LogSys_NotInitialized) ;
                }

                if (level <= LogInstance -> m_minLevel) {
                    std::string dateTime = FormatCurrentDateTime() ;

                    LogInstance -> m_mutex.lock() ;
                    {
                        LogInstance -> m_console.write(dateTime) ;
                        LogInstance -> m_console.writeLine(value, args...) ;
                    }
                    LogInstance -> m_mutex.unlock() ;
                }
            }

            /// <summary>
            /// Write a message on the Console by replacing the text on the
            /// current line.
            /// </summary>
            /// <param name="level">Level of gravity for the provided value.</param>
            /// <param name="value">The value to be printed.</param>
            /// <param name="args">Remaining arguments to be printed.</param>
            template<class T, class ... Args>
            exported static void PrintLineReplace(
                const Gravity level, 
                const T& value,
                const Args& ... args
            ) {
                if (!LogInstance) {
                    throw std::runtime_error(Doom::Texts::LogSys_NotInitialized) ;
                }

                if (level <= LogInstance -> m_minLevel) {
                    std::string dateTime = FormatCurrentDateTime() ;

                    LogInstance -> m_mutex.lock() ;
                    {
                        LogInstance -> m_console.write(dateTime) ;
                        LogInstance -> m_console.write(value, args...) ;
                        LogInstance -> m_console.write("\r") ;
                    }
                    LogInstance -> m_mutex.unlock() ;
                }
            }
    } ;
}

#endif
