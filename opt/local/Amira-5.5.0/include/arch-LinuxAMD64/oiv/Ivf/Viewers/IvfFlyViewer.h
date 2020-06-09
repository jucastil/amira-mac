/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef __IVFFLYVWR_H__
#define __IVFFLYVWR_H__

#include <Ivf/viewers/IvfStdViewer.h>

class SoWinFlyViewer;

/**
 * Ivf wrapper for an SoWinFlyViewer.
 * 
 * @ingroup Ivf_Classes
 * 
 * @DESCRIPTION
 *   Fly Viewer - this viewer is intended to simulate flight through space, with a
 *   constant world up direction. The viewer only constrains the camera to keep the
 *   user from flying upside down. No mouse buttons need to be pressed in order to
 *   fly. The mouse position is used only for steering, while mouse clicks are used
 *   to increase or decrease the viewer speed.
 *   
 *   The viewer allows you to tilt your head up/down/right/left and move in the
 *   direction you are looking (forward or backward). The viewer also supports seek
 *   to quickly move the camera to a desired object or point.
 *   
 *   See the SoWinFlyViewer description for additional information.
 *   
 *   Note: Although the class name is CIvfFlyViewer, the header file name is
 *   IvfFlyViewer.h.
 * 
 * @SEE_ALSO
 *    SoWinFlyViewer
 * 
 * 
 */ 

class IVF_API CIvfFlyViewer : public CIvfStdViewer
{
 public:
  CIvfFlyViewer() ;

  /** Overload component Creation */
  virtual void IvfCreateComponent(CWnd *pWnd, void *pCreateArgs);

  virtual void IvfDestroyComponent();
  
 protected: //PROTECTED_TO_DOCUMENT
  /** Destructor */
  virtual ~CIvfFlyViewer() ;
} ;
#endif

