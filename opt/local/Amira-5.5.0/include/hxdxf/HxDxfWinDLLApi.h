/*

Parts of the code herein is distributed under the following copyright
and license:

 (C) COPYRIGHT International Business Machines Corp. 1995

 Permission to use, copy, modify, and distribute this software and its
 documentation for any purpose and without fee is hereby granted,
 provided that the above copyright notice appear in all copies and that
 both that copyright notice and this permission notice appear in
 supporting documentation, and that the name of IBM not be
 used in advertising or publicity pertaining to distribution of the
 software without specific prior written permission.

 THE SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF ANY KIND,
 EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY
 WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.

 IBM DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
 ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 PURPOSE. IN NO EVENT SHALL IBM BE LIABLE FOR ANY SPECIAL, INDIRECT
 OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
 OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
 OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE
 OR PERFORMANCE OF THIS SOFTWARE.

*/

/// @addtogroup hxdxf hxdxf
/// @{
#ifndef HXDXF_WIN_DLL_API_H
#define HXDXF_WIN_DLL_API_H

#ifdef _WIN32
#  ifdef HXDXF_EXPORTS
#     define HXDXF_API __declspec(dllexport)
#  else
#     define HXDXF_API __declspec(dllimport)
#  endif
#else
#   define HXDXF_API 
#endif

#endif

/// @}
