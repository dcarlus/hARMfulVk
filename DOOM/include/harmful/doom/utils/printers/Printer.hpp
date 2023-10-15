#ifndef __DOOM__BASE_PRINTER__
#define __DOOM__BASE_PRINTER__

#include "harmful/doom/utils/Platform.hpp"
#include <iostream>

namespace Doom {
    /**
     * Base class to make a printer in a output stream.
     */
    class exported Printer {
        protected:
            /**
             * A class to print a value on its creation.
             */
            class ValuePrinter final {
                public:
                    /**
                     * Print the provided value in the provided output stream.
                     * @param   stream  Stream in which the @a value is printed.
                     * @param   value   Value to print in the @a stream.
                     */
                    template<class T, class ... Args>
                    ValuePrinter(std::ostream& stream, const T& value, const Args& ... args) {
                        stream << value ;
                    }

                    template<class T>
                    ValuePrinter(std::ostream& stream, const T& value) {
                        stream << value ;
                    }

                    /**
                     * Print the provided value in the provided output stream.
                     * @param   stream  Stream in which the @a value is printed.
                     */
                    ValuePrinter(std::ostream&) {}
            } ;
    } ;
} ;

#endif
