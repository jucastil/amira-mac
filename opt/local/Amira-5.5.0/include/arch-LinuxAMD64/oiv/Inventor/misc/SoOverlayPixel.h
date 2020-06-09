/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _SO_OVERLAY_PIXELS_
#define _SO_OVERLAY_PIXELS_

#ifndef HIDDEN_FROM_DOC

#include <Inventor/SbBasic.h>

#define NUM_OVERLAY_PIXELS 8

/**
 * class that handle current overlay usage.
 */
SoINTERNAL class INVENTOR_API SoOverlayPixel 
{
 public:
  /**
   * return pixel format used for overlay of indice ind.
   */
  static int getOverlayPixel(int ind);
  /**
   * return number of overlay initialized.
   */
  static int getNumOverlayPixels();
  /**
   * enable overlay.
   */
  static void setOverlayVisual(SbBool val);

  /**
   * return TRUE if overlay was enabled.
   */
  static SbBool isOverlayVisual();
  
  /**
   * store the pixel format for each overlay.
   */
  static int overlayPixelMap[NUM_OVERLAY_PIXELS];
  
 private:
   // overlay enable flag.
  static SbBool m_overlayVisual;
};

#endif /* HIDDEN_FROM_DOC */

#endif /* _SO_OVERLAY_PIXELS_ */
