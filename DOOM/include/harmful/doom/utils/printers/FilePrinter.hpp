#ifndef __DOOM__FILE_PRINTER__
#define __DOOM__FILE_PRINTER__

#include "harmful/doom/utils/Platform.hpp"
#include "harmful/doom/utils/printers/Printer.hpp"
#include "harmful/doom/utils/Utils.hpp"
#include <fstream>
#include <string>
#include <mutex>

namespace Doom {
    /// <summary>
    /// A FilePrinter to write values in a file.
    /// </summary>
    class FilePrinter final : public Printer {
        private:
            /// <summary>
            /// Avoid concurrent accesses to the FilePrinter.
            /// </summary>
            std::mutex m_mutex ;

            /// <summary>
            /// Output stream to print values.
            /// </summary>
            std::ofstream m_output ;

            /// <summary>
            /// Disable copy of FilePrinter.
            /// </summary>
            FilePrinter(const FilePrinter&) = delete ;

            /// <summary>
            /// Disable move of FilePrinter.
            /// </summary>
            FilePrinter(FilePrinter&&) = delete ;

            /// <summary>
            /// Disable affectation.
            /// </summary>
            void operator= (const FilePrinter&) = delete ;

            /// <summary>
            /// Disable move.
            /// </summary>
            void operator= (FilePrinter&&) = delete ;

        public:
            /// <summary>
            /// Instantiate a new FilePrinter object that prints in a file.
            /// This constructor makes the file be overwritten if already
            /// existing.
            /// </summary>
            /// <param name="filepath">Path to the file in which values are written.</param>
            exported FilePrinter(const std::string& filepath) ;

            /// <summary>
            /// Instantiate a new FilePrinter object that prints in a file.
            /// </summary>
            /// <param name="filepath">Path to the file in which values are written.</param>
            /// <param name="append">
            /// true to append values at the end of the file if existing.
            /// false to overwrite the full content of the file.
            /// </param>
            exported FilePrinter(
                const std::string& filepath,
                const bool& append
            ) ;

            /// <summary>
            /// Destruction of the FilePrinter instance.
            /// </summary>
            exported virtual ~FilePrinter() noexcept ;

            /// <summary>
            /// Write a message on the FilePrinter and create a new line in the
            /// output stream.
            /// </summary>
            /// <param name="value">The value to be printed.</param>
            template<class T>
            exported void writeLine(const T& value) {
                m_mutex.lock() ;
                {
                    m_output << value << std::endl ;
                }
                m_mutex.unlock() ;
            }

            /// <summary>
            /// Write messages on the FilePrinter and create a new line in the
            /// output stream.
            /// </summary>
            /// <param name="value">The value to be printed.</param>
            /// <param name="args">Remaining arguments to be printed.</param>
            template<class T, class ... Args>
            exported void writeLine(const T& value, const Args& ... args) {
                m_mutex.lock() ;
                {
                    m_output << value ;
                    auto value = { Printer::ValuePrinter(m_output, args)... } ;
                    UNUSED(value) ;
                    m_output << std::endl ;
                }
                m_mutex.unlock() ;
            }

            /// <summary>
            /// Write a message on the FilePrinter.
            /// </summary>
            /// <param name="value">The value to be printed.</param>
            template<class T>
            exported void write(const T& value) {
                m_mutex.lock() ;
                {
                    m_output << value << std::flush ;
                }
                m_mutex.unlock() ;
            }

            /// <summary>
            /// Write a message on the FilePrinter.
            /// </summary>
            /// <param name="value">The value to be printed.</param>
            /// <param name="args">Remaining arguments to be printed.</param>
            template<class T, class ... Args>
            exported void write(const T& value, const Args& ... args) {
                m_mutex.lock() ;
                {
                    m_output << value ;
                    auto value = { Printer::ValuePrinter(m_output, args)... } ;
                    UNUSED(value) ;
                    m_output << std::flush ;
                }
                m_mutex.unlock() ;
            }

        private:
            /// <summary>
            /// Get the access mode to the file according. It depends on the
            /// append value.
            /// </summary>
            /// <param name="append">
            /// true to append new values at the end of the file.
            /// false to overwrite the content of the file.
            /// </param>
            /// <returns>The access mode to the file.</returns>
            std::ios_base::openmode getAccessMode(const bool& append) ;
    } ;
} ;

#endif
