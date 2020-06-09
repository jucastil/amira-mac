/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SB_VIEWPORT_REGION_
#define  _SB_VIEWPORT_REGION_

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SbViewportRegion
//
//  Class that represents the active viewport region in a display
//  window. It contains the screen-space size of the window as well as
//  the origin and size of the viewport within the window. By default,
//  the viewport is the same as the full window. Methods allow the
//  viewport to be set either in terms of screen space pixels or as
//  normalized coordinates, where (0,0) is the lower-left corner of
//  the window and (1,1) is the upper-right corner.
//
//////////////////////////////////////////////////////////////////////////////

#include <Inventor/SbLinear.h>

/**
 * Class for representing a viewport.
 * 
 * @ingroup Basics
 * 
 * @DESCRIPTION
 *   This class represents the active viewport region in a display window. It
 *   contains the screen-space size of the window as well as the origin and size of
 *   the viewport within the window. By default, the viewport is the same as the full
 *   window. Methods allow the viewport to be set either in terms of screen-space
 *   pixels or as normalized coordinates, where (0,0) is the lower-left corner of the
 *   window and (1,1) is the upper-right corner.
 * 
 * @SEE_ALSO
 *    SbVec2f,
 *    SbVec2s
 * 
 * 
 */ 

class INVENTORBASE_API SbViewportRegion {

 public:
  /**
   * Default constructor. Sets window size to default 100 x 100 pixels.
   */
  SbViewportRegion();
  
  /**
   * Constructor that takes a width and a height in pixels.
   */
  SbViewportRegion(short width, short height, float newScale = 1.0);

  /**
   * Constructor that takes a window size in pixels.
   */
  SbViewportRegion(SbVec2s   winSize, float newScale = 1.0);
  /**
   * Constructor that takes a window size in pixels.
   */
  SbViewportRegion(SbVec2i32 winSize, float newScale = 1.0);
  
  /**
   * Constructor that takes a viewport region.
   */
  SbViewportRegion(const SbViewportRegion &vpReg);
  
  /**
   * Changes window size to given width and height in pixels.
   */
  void setWindowSize(short width, short height)
    { setWindowSize(SbVec2i32(width, height)); }

  /**
   * Changes window size to given width and height in pixels, given as SbVec2s.
   */
  void setWindowSize(SbVec2s winSize);
  /**
   * Changes window size to given width and height in pixels, given as SbVec2i32.
   */
  void setWindowSize(SbVec2i32 winSize);
  
  /**
   * Sets viewport to given region, specified as normalized window coordinates: (0,0)
   * is the lower-left corner, (1,1) is the upper-right.
   */
  void setViewport(float left, float bottom, float width, float height)
    { setViewport(SbVec2f(left, bottom), SbVec2f(width, height)); }
  
  /**
   * Sets viewport to region with given origin (lower-left corner) and size, given as
   * normalized coordinate vectors.
   */
  void setViewport(SbVec2f origin, SbVec2f size);
  
  /**
   * Sets viewport to given region, specified as pixel coordinates in window: (0,0)
   * is the lower-left corner.
   */
  void setViewportPixels(short left, short bottom, short width, short height)
    { setViewportPixels(SbVec2i32(left, bottom), SbVec2i32(width, height)); }

  /**
   * Sets viewport to region with given origin (lower-left corner) and size, given as
   * pixel coordinates.
   */
  void setViewportPixels(SbVec2s origin, SbVec2s size);

  /**
   * Sets viewport to region with given origin (lower-left corner) and size, given as
   * pixel coordinates.
   */
  void setViewportPixels(SbVec2i32 origin, SbVec2i32 size);
  
  /**
   * Returns window size in pixels.
   */
  const SbVec2s &getWindowSize() const;
 
  /**
   * Returns window size in pixels.
   */
  const SbVec2i32 &getWindowSize_i32() const;

  /**
   * Returns viewport origin in normalized coordinates.
   */
  const SbVec2f &getViewportOrigin() const
    { return vpOrigin; }

  /**
   * Returns viewport origin in pixels.
   */
  const SbVec2s &getViewportOriginPixels() const;

  /**
   * Returns viewport origin in pixels.
   */
  const SbVec2i32 &getViewportOriginPixels_i32() const;

  /**
   * Returns viewport size in normalized coordinates.
   */
  const SbVec2f &getViewportSize() const
    { return vpSize; }
  
  /**
   * Returns viewport size in pixels.
   */
  const SbVec2s &getViewportSizePixels() const;

  /**
   * Returns viewport size in pixels.
   */
  const SbVec2i32 &getViewportSizePixels_i32() const;

  /**
   * Returns aspect ratio (width/height) of viewport.
   */
  float getViewportAspectRatio() const;

  /**
   * Scales viewport within window to be the given ratio of its current width, 
   * leaving the resulting viewport centered about the same point as the
   * current one.
   */
  void scaleWidth(float ratio);

  /**
   * Scales viewport within window to be the given ratio of its current
   * height, leaving the resulting viewport centered about the same point as the
   * current one.
   */
  void scaleHeight(float ratio);
  
  /**
   * Sets the pixel-per-inch ratio for the display device the viewport is
   * part of. The default value is 72 (1 pixel per printer's point).
   */
  void setPixelsPerInch(float ppi)
    { pixelsPerInch = ppi; }

  /**
   * Returns the pixel-per-inch ratio for the display device the viewport is
   * part of.
   */
  float getPixelsPerInch() const
    { return pixelsPerInch; }
  
  /**
   * Convenience function that returns number of pixels per printer's point.
   */
  float getPixelsPerPoint() const
    { return (pixelsPerInch / 72.0f); }
  
  /**
   * Equality comparison operator.
   */
  INVENTORBASE_API friend int operator ==(const SbViewportRegion &reg1,
                         const SbViewportRegion &reg2);

 SoINTERNAL public:

  void setViewportScale(float vpScale)
    { viewportScale = vpScale; }

  float getViewportScale() const
    {return viewportScale; }
 
  
 private:
  SbVec2i32 windowSize_i32;  // Window size in pixels
  SbVec2s   windowSize;      // Window size in pixels
  SbVec2f   vpOrigin;        // Viewport origin, normalized
  SbVec2s   vpOriginPix;     // Viewport origin in pixels
  SbVec2i32 vpOriginPix_i32; // Viewport origin in pixels
  SbVec2f   vpSize;          // Viewport size, normalized
  SbVec2s   vpSizePix;       // Viewport size in pixels
  SbVec2i32 vpSizePix_i32;   // Viewport size in pixels
  SbBool    vpSet;           // TRUE if viewport was set explicitly
  float     pixelsPerInch;   // Number of pixels per inch
  float     viewportScale;   // Viewport scale (used for remote rendering)
  
  // Sets viewport to be full window
  void setFullViewport();
  
  // Adjusts viewport pixel size based on new window size or new viewport
  void adjustViewport();
};
 
/**
 * Class to access a MeshViz view.
 * 
 * @ingroup Basics
 * 
 * @DESCRIPTION
 *   This class gives access from the Inventor kernel to the external MeshViz nodes 
 *   managing the views (i.e PoBaseView::viewportOrigin or 
 *   PoBaseView::viewportSize and its derived class fields).
 * 
 * @SEE_ALSO
 *    PoBaseView.
 * 
 * 
 */ 

class INVENTORBASE_API SoGetView {
 public:
  /**
   * Default constructor.
   */
  SoGetView();
  virtual ~SoGetView() {};

  /**
   * Returns TRUE if SoGetView functionalities are enabled, FALSE otherwise.
   * By default, returns FALSE.
   */
  virtual SbBool getViewportIsEnabled() const;

  /**
   * Returns SbViewportRegion origin. Default value = (0,0).
   */
  virtual const SbVec2f getViewportOrigin() const;

  /**
   * Returns SbViewportRegion size. Default value = (1,1).
   */
  virtual const SbVec2f getViewportSize() const;
};

#endif /* _SB_VIEWPORT_REGION_ */

