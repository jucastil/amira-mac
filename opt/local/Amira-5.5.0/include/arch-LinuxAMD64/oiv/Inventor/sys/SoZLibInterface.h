/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _SOZLIBINTERFACE_H_
#define _SOZLIBINTERFACE_H_

/**
 *
 * @VSGEXT Header to interface ZLib for dynamic loading
 * 
 * @ingroup General
 *
 *  This header must be used in libraries needing the Zlib library.  
 *  For instance PngLib or Freetype.
 *  This header contains pointers to the Zlib functions to be used within other libraries 
 *  in dynamic load management.
 *  If you update the Png library, you need to add:
 *  - #include <Inventor/sys/SoZLibInterface.h> 
 *    after #include "zlib.h" in png.h
 *  - #define SET_ZLIB_PTR 
 *    before #include "png.h" in png.c
 * 
 *  If you update Freetype, you need to add:
 *  - #define SET_ZLIB_PTR 
 *    #include <Inventor/sys/SoZLibInterface.h>
 *    after #include <zlib.h> in ftgzip.c
 * 
 * 
 */ 

#include <Inventor/sys/port.h>
#include <zlib.h>

typedef WINGDIAPI gzFile (*gzopenPtr_t)
                         (const char *path, const char *mode);

typedef WINGDIAPI gzFile (*gzdopenPtr_t)
                         (int fd, const char *mode);

typedef WINGDIAPI int (*gzclosePtr_t)
                      (gzFile file);

typedef WINGDIAPI int (*gzflushPtr_t)
                      (gzFile file, int flush);

typedef WINGDIAPI z_off_t (*gztellPtr_t)
                      (gzFile file);

typedef WINGDIAPI z_off_t (*gzseekPtr_t)
                      (gzFile file, z_off_t offset, int whence);

typedef WINGDIAPI int (*gzeofPtr_t)
                      (gzFile file);

typedef WINGDIAPI int (*gzgetcPtr_t)
                      (gzFile file);

typedef WINGDIAPI int (*gzputcPtr_t)
                      (gzFile file, int c);

typedef WINGDIAPI int (*gzputsPtr_t)
                      (gzFile file, const char* c);

typedef WINGDIAPI int (*gzwritePtr_t)
                      (gzFile file, const voidp buf, unsigned len);                        

typedef WINGDIAPI int (*gzreadPtr_t)
                      (gzFile file, voidp buf, unsigned len);                        

typedef WINGDIAPI uLong (*z_crc32Ptr_t)
                        (uLong crc, const Bytef *buf, uInt len);

typedef WINGDIAPI int (*z_inflateResetPtr_t)
                      (z_streamp strm);

typedef WINGDIAPI int (*z_inflatePtr_t)
                      (z_streamp strm, int flush);

typedef WINGDIAPI int (*z_inflateInit_Ptr_t)
                      (z_streamp strm, const char *version, int stream_size);

typedef WINGDIAPI int (*z_inflateInit2_Ptr_t)
                      (z_streamp strm, int  windowBits,
                       const char *version, int stream_size);

typedef WINGDIAPI int (*z_inflateEndPtr_t)
                      (z_streamp strm);

typedef WINGDIAPI int (*z_deflatePtr_t)
                      (z_streamp strm, int flush);

typedef WINGDIAPI int (*z_deflateEndPtr_t)
                      (z_streamp strm);

typedef WINGDIAPI int (*z_deflateInit2_Ptr_t)
                      (z_streamp strm, int  level, int  method,
                       int windowBits, int memLevel,
                       int strategy, const char *version,
                       int stream_size);

typedef WINGDIAPI int (*z_deflateResetPtr_t)
                      (z_streamp strm);

typedef WINGDIAPI int (*z_compress2Ptr_t)
                      (Bytef *dest,   uLongf *destLen, const Bytef *source, uLong sourceLen,int level);

typedef WINGDIAPI int (*z_uncompressPtr_t)
                       (Bytef *dest,   uLongf *destLen, const Bytef *source, uLong sourceLen);


#ifndef OIV_BUILD_LIBRARY

#include <zlib.h>


#ifdef TGS_AVOID_MULTIPLE_DEFINE
#define TGS_DEFINE_EXTERN extern
#else
#define TGS_DEFINE_EXTERN
#endif

TGS_DEFINE_EXTERN z_crc32Ptr_t         TGScrc32;
TGS_DEFINE_EXTERN z_inflateResetPtr_t  TGSinflateReset;
TGS_DEFINE_EXTERN z_inflatePtr_t       TGSinflate;
TGS_DEFINE_EXTERN z_inflateInit_Ptr_t  TGSinflateInit_;
TGS_DEFINE_EXTERN z_inflateInit2_Ptr_t TGSinflateInit2_;
TGS_DEFINE_EXTERN z_inflateEndPtr_t    TGSinflateEnd;
TGS_DEFINE_EXTERN z_deflatePtr_t       TGSdeflate;
TGS_DEFINE_EXTERN z_deflateEndPtr_t    TGSdeflateEnd;
TGS_DEFINE_EXTERN z_deflateInit2_Ptr_t TGSdeflateInit2_;
TGS_DEFINE_EXTERN z_deflateResetPtr_t  TGSdeflateReset;

TGS_DEFINE_EXTERN z_compress2Ptr_t     TGScompress2;
TGS_DEFINE_EXTERN z_uncompressPtr_t    TGSuncompress;


#undef crc32
#undef inflateReset
#undef inflate 
#undef inflateInit_ 
#undef inflateInit2_
#undef inflateEnd 
#undef deflate 
#undef deflateEnd 
#undef deflateInit2_ 
#undef deflateReset 
#undef compress2
#undef uncompress

#define crc32 TGScrc32
#define inflateReset TGSinflateReset
#define inflate TGSinflate
#define inflateInit_ TGSinflateInit_
#define inflateInit2_ TGSinflateInit2_
#define inflateEnd TGSinflateEnd
#define deflate TGSdeflate
#define deflateEnd TGSdeflateEnd
#define deflateInit2_ TGSdeflateInit2_
#define deflateReset TGSdeflateReset
#define compress2 TGScompress2
#define uncompress TGSuncompress

#ifdef SET_ZLIB_PTR

#if defined(_WIN32)
__declspec(dllexport)
#endif
void TGS_initZLibPointers(z_crc32Ptr_t crc, 
                          z_inflateInit_Ptr_t  infInit, z_inflateInit2_Ptr_t infInit2, z_inflateResetPtr_t infReset, z_inflatePtr_t inf, 
                          z_inflateEndPtr_t infEnd, z_deflateInit2_Ptr_t defInit, z_deflateResetPtr_t defReset, z_deflatePtr_t def, 
                          z_deflateEndPtr_t defEnd,
                          z_compress2Ptr_t comp2, z_uncompressPtr_t uncomp
                          )
{
  TGScrc32 = crc;

  TGSinflateInit_  = infInit;
  TGSinflateInit2_ = infInit2;
  TGSinflateReset  = infReset;
  TGSinflate = inf;
  TGSinflateEnd = infEnd;

  TGSdeflateInit2_ = defInit;
  TGSdeflate = def;
  TGSdeflateEnd = defEnd;
  TGSdeflateReset = defReset;
  
  TGScompress2  = comp2;
  TGSuncompress = uncomp;
}
#endif  /* SET_ZLIB_PTR */
#endif  /* OIV_BUILD_LIBRARY */
#endif  /* _SOZLIBINTERFACE_H_ */

