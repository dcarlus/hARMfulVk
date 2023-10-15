#ifndef __DOOM__PLATFORM__
#define __DOOM__PLATFORM__

    #ifdef __linux__
        #define LinuxPlatform
        #define exported
    #elif _WIN32 || _WIN64
        #define WindowsPlatform

        #if COMPILE_SHARED_LIBS
            // Required on Visual C++ to generate a .lib file alongside the .dll.
            #define exported __declspec(dllexport)
        #else
            // Required on Visual C++ to generate a .lib file alongside the .dll.
            #define exported __declspec(dllimport)
        #endif

        // Disable warning:
        // C++ exception specification ignored except to indicate a function is
        // not __declspec(nothrow)
        #pragma warning(disable: 4290)
    #else
        #error "Unsupported compiler and/or platform"
    #endif

#endif
