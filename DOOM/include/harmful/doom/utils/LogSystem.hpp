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
    /**
     * System to write logs in the Console and/or in a file.
     */
    class LogSystem final {
        public:
            /**
             * Extension of the log file.
             */
            static const std::string LogFileExtension ;

            /**
             * Level of gravity of the log messages.
             */
            enum class Gravity: int8_t {
                Critical = 0,
                Error,
                Warning,
                Info,
                Debug
            } ;

        private:
            /**
             * The unique instance of the LogSystem.
             */
            static std::unique_ptr<LogSystem> LogInstance ;

            /**
             * Mutex for the static methods of the class.
             */
            static std::mutex ClassMutex ;

            /**
             * Avoid concurrent accesses to the LogSystem.
             */
            std::mutex m_mutex ;

            /**
             * Console of the LogSystem.
             */
            Console m_console ;

            /**
             * File printer to save important log messages.
             */
            std::unique_ptr<FilePrinter> m_printer = nullptr ;

            /**
             * Minimal level to write logs, lower gravity messages are ignored.
             */
            Gravity m_minLevel ;

        private:
            /**
             * Instantiate the LogSystem.
             * @param   path        Path to the file that will contain the
             *                      output log messages.
             * @param   minLevel    Minimal level of the log system messages to
             *                      be written.
             */
            LogSystem(
                const std::string& path,
                const Gravity minLevel
             ) ;

            /**
             * Format the current date and time to be printed in the logs.
             * @return String representing the printed date and time in the
             *         logs.
             */
            exported static std::string FormatCurrentDateTime() ;

        public:
            /**
             * Initialize the LogSystem. This is required before any call to the
             * GetInstance function.
             * @param   path        Path to the file that will contain the
             *                      output log messages.
             * @param   minLevel    Minimal level of the log system messages to
             *                      be written.
             * @exception   An exception is thrown if the LogSystem is
             *              initialized more than once.
             */
            exported static void Initialize(
                const std::string& path,
                const Gravity minLevel
            ) ;

            /**
             * To know if the LogSystem is ready to be used.
             * @see Initialize()
             */
            exported static bool Ready() {
                return LogInstance != nullptr ;
            }

            /**
             * Write a message on the Console and the FilePrinter.
             * @param   level   Level of gravity for the provided value.
             * @param   value   The value to be printed.
             */
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

            /**
             * Write a message on the Console and the FilePrinter.
             * @param   level   Level of gravity for the provided value.
             * @param   value   The value to be printed.
             * @param   args    Remaining arguments to be printed.
             */
            template<class T, class ... Args>
            exported static void WriteLine(const Gravity level, const T& value, const Args& ... args) {
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

            /**
             * Write a message on the Console.
             * @param   level   Level of gravity for the provided value.
             * @param   value   The value to be printed.
             */
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

            /**
             * Write a message on the Console.
             * @param   level   Level of gravity for the provided value.
             * @param   value   The value to be printed.
             * @param   args    Remaining arguments to be printed.
             */
            template<class T, class ... Args>
            exported static void PrintLine(const Gravity level, const T& value, const Args& ... args) {
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

            /**
             * Write a message on the Console.
             * @param   level   Level of gravity for the provided value.
             * @param   value   The value to be printed.
             * @param   args    Remaining arguments to be printed.
             */
            template<class T, class ... Args>
            exported static void PrintLineReplace(const Gravity level, const T& value, const Args& ... args) {
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
