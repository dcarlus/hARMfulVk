#ifndef __DOOM__CONSOLE__
#define __DOOM__CONSOLE__

#include "harmful/doom/utils/Platform.hpp"
#include "harmful/doom/utils/printers/Printer.hpp"
#include "harmful/doom/utils/Utils.hpp"
#include <cstdint>
#include <mutex>

namespace Doom {
    /**
     * A Console to write and get values from user.
     */
    class Console final : public Printer {
        public:

            /**
             * State of the Console.
             */
            enum class State: int8_t {
                Error,
                Bad,
                Fail,
                OK
            } ;

        private:
            /**
             * Avoid concurrent accesses to the Console.
             */
            std::mutex m_mutex ;

            /**
             * State of the Console when reading values.
             */
            State m_inputState = State::OK ;

        public:

            /**
             * Instantiate a new Console object.
             */
            exported Console() ;

            /**
             * Read a value from the Console.
             * @param   output  The read value.
             * @return  State of the Console once data are read.
             */
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

            /**
             * Write a message on the Console and create a new line in the
             * output stream.
             * @param   value   The value to be printed.
             */
            template<class T>
            exported void writeLine(const T& value) {
                m_mutex.lock() ;
                {
                    std::cout << value << std::endl ;
                }
                m_mutex.unlock() ;
            }

            /**
             * Write messages on the Console and create a new line in the output
             * stream.
             * @param   value   The value to be printed.
             * @param   args    Remaining arguments to be printed.
             */
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

            /**
             * Write a message on the Console.
             * @param   value   The value to be printed.
             */
            template<class T>
            exported void write(const T& value) {
                m_mutex.lock() ;
                {
                    std::cout << value << std::flush ;
                }
                m_mutex.unlock() ;
            }

            /**
             * Write messages on the Console.
             * @param   value   The value to be printed.
             * @param   args    Remaining arguments to be printed.
             */
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
            /**
            * Check the status of the input stream and update the
            * state of the Console for reading values.
            */
            void checkInputStream() ;

            /**
             * Clear the input stream of the Console.
             */
            void clearInputStream() ;
    } ;
} ;

#endif
