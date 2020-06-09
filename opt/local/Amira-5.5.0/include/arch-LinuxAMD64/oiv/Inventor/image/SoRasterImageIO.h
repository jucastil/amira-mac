/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : C. OGNIER (Jun 2003)
**=======================================================================*/


#ifndef _SORASTERIMAGEIO_
#define _SORASTERIMAGEIO_

#include <Inventor/SoType.h> 

/**
 *
 * @VSGEXT Abstract base class for raster image input and output.
 * 
 * @ingroup Image
 *
 * Abstract class for raster image input and output.
 *
 * 
 * @SEE_ALSO
 *    SoRasterImageRW
 * 
 * 
 */ 
#include <Inventor/image/SoSubRasterImageRW.h>

class INVENTORIMAGE_API SoRasterImageIO {
  SO_IMAGE_RASTER_RW_ABSTRACT_HEADER()

  
public:
  virtual ~SoRasterImageIO(){}
};

#endif
