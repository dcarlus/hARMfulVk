#ifndef __SPITE__FILE_INFO__
#define __SPITE__FILE_INFO__

namespace Spite {
    /// <summary>
    /// Type of the file.
    /// </summary>
    enum class FileType {
        Unknown,
        Text,
        Binary
    };

    /// <summary>
    /// Info data in the total bytes buffer.
    /// </summary>
    struct FileInfo {
        FileType type;
        size_t begin;
        size_t end;
    };
}

#endif