/*

    mcla is a wrapper library for freely-available LAPACK implementations.

    From the LAPACK Frequently Asked Questions (http://www.netlib.org/lapack/faq.html):

    LAPACK is a freely-available software package. It is available
    from netlib via anonymous ftp and the World Wide Web. Thus, it
    can be included in commercial software packages (and has
    been). We only ask that proper credit be given to the authors.

    Like all software, it is copyrighted. It is not trademarked,
    but we do ask the following:

    If you modify the source for these routines we ask that you
    change the name of the routine and comment the changes made to
    the original.

    We will gladly answer any questions regarding the software. If
    a modification is done, however, it is the responsibility of
    the person who modified the routine to provide support.

*/

/// @addtogroup mcla mcla
/// @{
#ifndef MCLAAPI_H
#define MCLAAPI_H

#ifdef HX_OS_WIN
    // This will be defined by the build system; then we are building the DLL.
    #ifdef MCLA_EXPORTS
        #define MCLA_API __declspec(dllexport)
    #else
        #define MCLA_API __declspec(dllimport)
    #endif
#else
    #define MCLA_API
#endif

#endif // MCLAAPI_H

/// @}
