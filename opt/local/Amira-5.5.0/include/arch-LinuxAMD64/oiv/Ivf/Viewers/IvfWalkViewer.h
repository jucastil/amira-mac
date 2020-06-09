/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef __IVFWALKVWR_H__
#define __IVFWALKVWR_H__

#include <Ivf/viewers/IvfStdViewer.h>

class SoWinWalkViewer;

/**
 * Ivf wrapper for an SoWinWalkViewer.
 * 
 * @ingroup Ivf_Classes
 * 
 * @DESCRIPTION
 *   The paradigm for this viewer is a walk-through of an architectural model. Its
 *   primary behavior is forward, backward, and left/right turning motion while
 *   maintaining a constant "eye level". It is also possible to stop and look around
 *   at the scene. The eye level plane can be disabled, allowing the viewer to
 *   proceed in the "look at" direction, as if on an escalator. The eye level plane
 *   can also be translated up and down - similar to an elevator.
 *   
 *   See the SoWinWalkViewer description for additional information.
 *   
 *   Note: Although the class name is CIvfWalkViewer, the header file name is
 *   IvfWalkViewer.h.
 * 
 * @SEE_ALSO
 *    SoWinWalkViewer
 * 
 * 
 */ 

class IVF_API CIvfWalkViewer : public CIvfStdViewer
{
 public:
  /** Constructor */
  CIvfWalkViewer() ;
  
  virtual void IvfCreateComponent(CWnd *pWnd, void *pCreateArgs);
  virtual void IvfDestroyComponent();
        
 protected: //PROTECTED_TO_DOCUMENT
  /** Destructor */
  virtual ~CIvfWalkViewer() ;
} ;
#endif

