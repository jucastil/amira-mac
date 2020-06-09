/***************************************************************
 *
 * DLL export/import definitions for Windows
 *
 ***************************************************************/
#ifndef MYPACKAGE_WIN_DLL_API_H
#define MYPACKAGE_WIN_DLL_API_H

#ifdef _WIN32
#  ifdef MYPACKAGE_EXPORTS
#     define MYPACKAGE_API __declspec(dllexport)
#  else
#     define MYPACKAGE_API __declspec(dllimport)
#  endif
#else
#   define MYPACKAGE_API 
#endif

#endif
