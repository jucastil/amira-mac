/***************************************************************
 *
 * DLL export/import definitions for Windows
 *
 ***************************************************************/

#ifndef MYPACKAGE_API_H
#define MYPACKAGE_API_H

#ifdef HX_OS_WIN
    #ifdef MYPACKAGE_EXPORTS
        #define MYPACKAGE_API __declspec(dllexport)
    #else
        #define MYPACKAGE_API __declspec(dllimport)
    #endif
#else
    #define MYPACKAGE_API
#endif

#endif // MYPACKAGE_API_H
