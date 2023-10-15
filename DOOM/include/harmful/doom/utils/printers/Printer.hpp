#ifndef __DOOM__BASE_PRINTER__
#define __DOOM__BASE_PRINTER__

#include "harmful/doom/utils/Platform.hpp"
#include <iostream>

namespace Doom {
    /// <summary>
    /// Base class to make a printer in a output stream.
    /// </summary>
    class exported Printer {
        protected:
            /// <summary>
            /// A class to print a value on its creation.
            /// </summary>
            class ValuePrinter final {
                public:
                    /// <summary>
                    /// Print the provided values in the provided output stream.
                    /// </summary>
                    /// <typeparam name="T">Type of the initial value.</typeparam>
                    /// <typeparam name="...Args">Types of the additional parameters.</typeparam>
                    /// <param name="stream">Stream in which the value is printed.</param>
                    /// <param name="value">Value to print in the stream.</param>
                    /// <param name="...args">Additional parameters to be printed.</param>
                    template<class T, class ... Args>
                    ValuePrinter(
                        std::ostream& stream,
                        const T& value,
                        const Args& ... args
                    ) {
                        stream << value ;
                    }

                    /// <summary>
                    /// Print the provided value in the provided output stream.
                    /// </summary>
                    /// <typeparam name="T">Type of the value to print.</typeparam>
                    /// <param name="stream">Stream in which the value is printed.</param>
                    /// <param name="value">Value to print in the stream.</param>
                    template<class T>
                    ValuePrinter(std::ostream& stream, const T& value) {
                        stream << value ;
                    }

                    /// <summary>
                    /// Print the provided value in the provided output stream.
                    /// </summary>
                    /// <param name="stream">Stream in which the @a value is printed.</param>
                    ValuePrinter(std::ostream&) {}
            } ;
    } ;
} ;

#endif
