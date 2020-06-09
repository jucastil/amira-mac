/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef _SO_BIGIMAGE_RENDERER_
#define _SO_BIGIMAGE_RENDERER_


#include <Inventor/SoOffscreenRenderer.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoBigImageRenderer
//
//  This file contains the definition of the SoBigImageRenderer class.
//  This class is used for rendering a scene graph to an offscreen memory
//  buffer which can be used for printing or generating textures.
//  Unlike the SoOffscreenRenderer class, this class allows the user 
//  to render images biger than 2048*2048 pixels.
//
//  This class uses an X Pixmap or Win32 bitmap for rendering.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * 
 * @VSGEXT Obsolete class. Renders to an off-screen buffer for printing or generating textures. There is no
 * size limit (except available memory).
 * 
 * @ingroup General
 * 
 * @DESCRIPTION
 *   This class is now obsolete.
 *   Please use the #SoOffscreenRenderer class.
 * 
 * @SEE_ALSO
 *    SoOffscreenRenderer
 * 
 * 
 * [OIV-WRAPPER-NO-WRAP]
 */ 

class INVENTOR_API SoBigImageRenderer : public SoOffscreenRenderer {
  
public :
  /**
   * Constructor. An internal instance of an SoGLRenderAction will be
   * maintained with a viewport
   * region set to the one passed in by the constructor.
   */
  SoBigImageRenderer(const SbViewportRegion &viewportRegion);
  /**
   * Constructor. The render action passed to the constructor 
   * will be used in all subsequent offscreen renderings.
   */
  SoBigImageRenderer(SoGLRenderAction *ra);
};

#endif // _SO_BIGIMAGE_RENDERER_

