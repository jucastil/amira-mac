/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef SO_DATACOMPRESSOR_BADTYPE_EXCEPTION
#define SO_DATACOMPRESSOR_BADTYPE_EXCEPTION

#include <LDM/compressors/exceptions/SoDataCompressorException.h>

/**
* @LDMEXT Data compression exception.
* @ingroup LDMCompressor
* 
* @DESCRIPTION
* This exception will be thrown by the compressor if it is asked to
* work on an unsupported data type.
*
* @SEE_ALSO
* SoDataCompressorException,
* SoDataCompressor,
* SoGzipDataCompressor,
* SoJpegDataCompressor
* 
* 
*/ 
SoINTERNAL class LDM_API SoDataCompressorBadTypeException : public SoDataCompressorException
{
public:
  /**
   * Construct the exception with the given message
   * @param what a string to explain the exception.
   */
  SoDataCompressorBadTypeException(const char *const& what):SoDataCompressorException(what) {}
};

#endif

