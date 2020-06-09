/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef __IVFPLANEVWR_H__
#define __IVFPLANEVWR_H__

#include <Ivf/viewers/IvfStdViewer.h>

class SoWinPlaneViewer;

/**
 * Ivf wrapper for an SoWinPlaneViewer.
 * 
 * @ingroup Viewers
 * 
 * @DESCRIPTION
 *   The Plane viewer component allows the user to translate the camera in the
 *   viewing plane, as well as dolly (move foward/backward) and zoom in and out. The
 *   viewer also allows the user to roll the camera (rotate around the forward
 *   direction) and seek to objects which will specify a new viewing plane. This
 *   viewer could be used for modeling, in drafting, and architectural work. The
 *   camera can be aligned to the X, Y or Z axes.
 *   
 *   See the SoWinPlaneViewer description for additional information.
 *   
 *   Note: Although the class name is CIvfPlaneViewer, the header file name is
 *   IvfPlaneViewer.h.
 * 
 * @SEE_ALSO
 *    SoWinPlaneViewer
 * 
 * 
 */ 

class IVF_API CIvfPlaneViewer : public CIvfStdViewer
{
 public:
  CIvfPlaneViewer() ;
  
  /** Overload component Creation */
  virtual void IvfCreateComponent(CWnd *pWnd, void *pCreateArgs);

  virtual void IvfDestroyComponent();
  
 protected: //PROTECTED_TO_DOCUMENT
  /** Destructor */
  virtual ~CIvfPlaneViewer() ;
} ;
#endif

