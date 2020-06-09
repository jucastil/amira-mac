/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef __IVFEXAMVWR_H__
#define __IVFEXAMVWR_H__

#include <Ivf/viewers/IvfStdViewer.h>

class SoWinExaminerViewer;

/**
 * Ivf wrapper for an SoWinExaminerViewer.
 * 
 * @ingroup Ivf_Classes
 * 
 * @DESCRIPTION
 *   The Examiner viewer component allows you to rotate the view around a point of
 *   interest using a virtual trackball. The viewer uses the camera
 *   @B focalDistance @b field to figure out the point of rotation, which is usually
 *   set to be at the center of the scene. In addition to allowing you to rotate the
 *   camera around the point of interest, this viewer also allows you to translate
 *   the camera in the viewer plane, as well as dolly (move forward and backward) to
 *   get closer to or further away from the point of interest. The viewer also
 *   supports seek to quickly move the camera to a desired object or point.
 *   
 *   See the SoWinExaminerViewer description for additional information.
 *   
 *   Note: Although the class name is CIvfExaminerViewer, the header file name is
 *   IvfExaminerViewer.h.
 * 
 * @SEE_ALSO
 *    SoWinExaminerViewer
 * 
 * 
 */ 

class IVF_API CIvfExaminerViewer : public CIvfStdViewer
{
 public:
  CIvfExaminerViewer() ;
  
  /** Overload component Creation */
  virtual void IvfCreateComponent(CWnd *pWnd, void *pCreateArgs);

  virtual void IvfDestroyComponent();
  
 protected: //PROTECTED_TO_DOCUMENT
  /** Destructor */
  virtual ~CIvfExaminerViewer() ;
} ;
#endif

