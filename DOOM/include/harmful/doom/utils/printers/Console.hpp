#ifndef __DOOM__CONSOLE__
#define __DOOM__CONSOLE__

#include "harmful/doom/utils/Platform.hpp"
#include "harmful/doom/utils/printers/Printer.hpp"
#include "harmful/doom/utils/Utils.hpp"
#include <cstdint>
#include <mutex>

namespace Doom {
    /// <summary>
    /// A Console to write and get values from user.
    /// </summary>
    class Console final : public Printer {
        public:

            /// <summary>
            /// State of the Console.
            /// </summary>
            enum class State: int8_t {
                Error,
                Bad,
                Fail,
                OK
            } ;

        private:
            /// <summary>
            /// Avoid concurrent accesses to the Console.
            /// </summary>
            std::mutex m_mutex ;

            /// <summary>
            /// State of the Console when reading values.
            /// </summary>
            State m_inputState = State::OK ;

            /// <summary>
            /// Disable copy of FilePrinter.
            /// </summary>
            Console(const Console&) = delete;

            /// <summary>
            /// Disable move of FilePrinter.
            /// </summary>
            Console(Console&&) = delete;

            /// <summary>
            /// Disable affectation.
            /// </summary>
            void operator= (const Console&) = delete;

            /// <summary>
            /// Disable move.
            /// </summary>
            void operator= (Console&&) = delete;

        public:
            /// <summary>
            /// Instantiate a new Console object.
            /// </summary>
            exported Console() ;

            /// <summary>
            /// Destruction of the Console instance.
            /// </summary>
            exported virtual ~Console() noexcept = default;

            /// <summary>
            /// Read a value from the Console.
            /// </summary>
            /// <typeparam name="T">Type of the read value in output.</typeparam>
            /// <param name="output">The read value.</param>
            /// <returns>State of the Console once data are read.</returns>
            template<class T>
            exported State read(T& output) {
                State currentState ;

                m_mutex.lock() ;
                {
                    std::cin >> output ;
                    checkInputStream() ;
                    currentState = m_inputState ;
                }
                m_mutex.unlock() ;

                return currentState ;
            }

            /// <summary>
            /// Write a message on the Console and create a new line in the
            /// output stream.
            /// </summary>
            /// <typeparam name="T">Type of the written value.</typeparam>
            /// <param name="value">The value to be printed.</param>
            template<class T>
            exported void writeLine(const T& value) {
                m_mutex.lock() ;
                {
                    std::cout << value << std::endl ;
                }
                m_mutex.unlock() ;
            }

            /// <summary>
            /// Write messages on the Console and create a new line in the
            /// output stream.
            /// </summary>
            /// <param name="value">The value to be printed.</param>
            /// <param name="args">Remaining arguments to be printed.</param>
            template<class T, class ... Args>
            exported void writeLine(const T& value, const Args& ... args) {
                m_mutex.lock() ;
                {
                    std::cout << value ;
                    auto value = { Printer::ValuePrinter(std::cout, args)... } ;
                    UNUSED(value) ;
                    std::cout << std::endl ;
                }
                m_mutex.unlock() ;
            }

            /// <summary>
            /// Write a message on the Console.
            /// </summary>
            /// <param name="value">The value to be printed.</param>
            template<class T>
            exported void write(const T& value) {
                m_mutex.lock() ;
                {
                    std::cout << value << std::flush ;
                }
                m_mutex.unlock() ;
            }

            /// <summary>
            /// Write messages on the Console.
            /// </summary>
            /// <param name="value">The value to be printed.</param>
            /// <param name="args">Remaining arguments to be printed.</param>
            template<class T, class ... Args>
            exported void write(const T& value, const Args& ... args) {
                m_mutex.lock() ;
                {
                    std::cout << value ;
                    auto value = { Printer::ValuePrinter(std::cout, args)... } ;
                    UNUSED(value) ;
                    std::cout << std::flush ;
                }
                m_mutex.unlock() ;
            }

        private:
            /// <summary>
            /// Check the status of the input stream and update the state of
            /// the Console for reading values.
            /// </summary>
            void checkInputStream() ;

            /// <summary>
            /// Clear the input stream of the Console.
            /// </summary>
            void clearInputStream() ;
    } ;
} ;

#endif
