#ifndef __DOOM__FILE_PRINTER__
#define __DOOM__FILE_PRINTER__

#include "harmful/doom/utils/Platform.hpp"
#include "harmful/doom/utils/printers/Printer.hpp"
#include "harmful/doom/utils/Utils.hpp"
#include <fstream>
#include <string>
#include <mutex>

namespace Doom {
    /**
     * A FilePrinter to write values in a file.
     */
    class FilePrinter final : public Printer {
        private:
            /**
             * Avoid concurrent accesses to the Console.
             */
            std::mutex m_mutex ;

            /**
             * Output stream to print values.
             */
            std::ofstream m_output ;

            /**
             * Disable copy of FilePrinter.
             */
            FilePrinter(const FilePrinter&) ;

            /**
             * Disable move of FilePrinter.
             */
            FilePrinter(FilePrinter&&) noexcept ;

            /**
             * Disable affectation.
             */
            void operator= (const FilePrinter&) ;

            /**
             * Disable move.
             */
            void operator= (FilePrinter&&) noexcept ;

        public:
            /**
             * Instantiate a new FilePrinter object that prints in a file.
             * This constructor makes the file be overwritten if already
             * existing.
             * @param   filepath    Path to the file in which values are
             *                      written.
             */
            exported FilePrinter(const std::string& filepath) ;

           /**
            * Instantiate a new FilePrinter object that prints in a file.
            * @param   filepath     Path to the file in which values are
            *                       written.
            * @param    append      TRUE to append values at the end of the file
            *                       if existing. FALSE to overwrite the full
            *                       content of the file.
            */
            exported FilePrinter(
                const std::string& filepath,
                const bool& append
            ) ;

            /**
             * Destruction of the FilePrinter instance.
             */
            exported virtual ~FilePrinter() noexcept ;

            /**
             * Write a message on the FilePrinter and create a new line in the
             * output stream.
             * @param   value   The value to be printed.
             */
            template<class T>
            exported void writeLine(const T& value) {
                m_mutex.lock() ;
                {
                    m_output << value << std::endl ;
                }
                m_mutex.unlock() ;
            }

            /**
             * Write messages on the FilePrinter and create a new line in the
             * output stream.
             * @param   value   The value to be printed.
             * @param   args    Remaining arguments to be printed.
             */
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

            /**
             * Write a message on the FilePrinter.
             * @param   value   The value to be printed.
             */
            template<class T>
            exported void write(const T& value) {
                m_mutex.lock() ;
                {
                    m_output << value << std::flush ;
                }
                m_mutex.unlock() ;
            }

            /**
             * Write messages on the FilePrinter.
             * @param   value   The value to be printed.
             * @param   args    Remaining arguments to be printed.
             */
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
            /**
             * Get the access mode to the file according. It depends on the @a
             * append value.
             * @param  append TRUE to append new values at the end of the file,
             *                FALSE to overwrite the content of the file.
             * @return        The access mode to the file.
             */
            std::ios_base::openmode getAccessMode(const bool& append) ;
    } ;
} ;

#endif
