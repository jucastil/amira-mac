/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : C. HUFSCHMITT (Jul 2001)
**=======================================================================*/

                                                             /* include files */
#ifndef _SO_MPEGFRAMERENDERER_
#define _SO_MPEGFRAMERENDERER_

#include <Inventor/MPEG/SoMPEGRenderer.h>
#include <Inventor/SoOffscreenRenderer.h>
#include <Inventor/SbViewportRegion.h>

/*----------------------------------------------------------------------------*/

/**
 * @VSGEXT Generates MPEG output, frame by frame.
 * 
 * @ingroup MPEG
 * 
 * @DESCRIPTION
 *   This class generates MPEG output, frame by frame.
 *
 *   See the parent class SoMPEGRenderer for methods to specify the file and
 *   recording parameters.
 *   
 * @SEE_ALSO
 *    SoMPEGRenderer, SoMPEGNavRenderer
 * 
 * 
 */ 

class INVENTOR_API SoMPEGFrameRenderer : public SoMPEGRenderer {

 public:
  /**
   * Constructor.
   */
  SoMPEGFrameRenderer ();

  /**
   * Destructor.
   */
  virtual ~SoMPEGFrameRenderer ();

  /**
   * Adds a new frame to the current MPEG output.
   * The duration (specified in seconds) is used to determine how many times 
   * this frame must be played in the MPEG output depending on the current 
   * number of frames per second (as specified by the method 
   * SoMPEGRenderer::setNumFramesPerSecond()).
   */
  void recordFrame(float duration=0) ;

  /*----------------------------------------------------------------------------*/

 private:
  SoOffscreenRenderer *m_OSRenderer;
  SbViewportRegion *m_View;

} ;/*----------------------------------------------------------------------------*/

#endif /* _SO_MPEGFRAMERENDERER_ */
