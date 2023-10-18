#ifndef __SPITE__TAR_UTILS__
#define __SPITE__TAR_UTILS__

#include <string>
#include <vector>
#include <harmful/doom/utils/Platform.hpp>
#include "harmful/spite/files/archives/TARData.hpp"

namespace Spite {
    /// <summary>
    /// TAR utils (load, save, ...).
    /// </summary>
    class TARUtils final {
        public:
            /// <summary>
            /// Load the content of a TAR archive in a TARData structure.
            /// </summary>
            /// <param name="path">Path to the TAR archive.</param>
            /// <returns>
            /// Object containing all the related data on the opened TAR archive.
            /// </returns>
            exported static TARData Load(const std::string& path) ;

            /// <summary>
            /// Save a TAR archive from a TARData structure.
            /// </summary>
            /// <param name="tarData">Data to write on disk.</param>
            /// <param name="path">Path on disk of the written file.</param>
            exported static void Save(
                TARData& tarData,
                const std::string& path
            ) ;
    } ;
}

#endif
