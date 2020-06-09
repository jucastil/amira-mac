/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef __IVFRNDRAREA_H__
#define __IVFRNDRAREA_H__

#include <Ivf/IvfComponent.h>

class SoWinRenderArea ;
class SoCamera;
class SoDirectionalLight ;

/**
 * Ivf wrapper for an SoWinRenderArea.
 * 
 * @ingroup Ivf_Classes
 * 
 * @DESCRIPTION
 *   This class provides Open Inventor rendering and message handling inside a
 *   Windows window. There is a routine to specify the scene to render. The scene is
 *   automatically rendered whenever anything under it changes (a data sensor is
 *   attached to the root of the scene), unless explicitly told not to do so (manual
 *   redraws). Users can also set Open Inventor rendering attributes such as the
 *   transparency type, antialiasing on or off, etc. This class employs an
 *   SoSceneManager to manage rendering and message handling.
 *   
 *   Windows messages that occur in the render area can be handled by the application,
 *   by the viewer (if this is really a viewer), or by the nodes in the scene graph.
 *   When a message occurs, it is first passed to the application message callback
 *   function registered with the method SoWinRenderArea::setEventCallback(). 
 *   If this function does not exist or returns FALSE, the message
 *   is either used directly by the viewer or translated to an SoEvent for further
 *   scene graph processing. If the viewer does not handle the message, and an
 *   overlay scene graph exists, the SoEvent is sent to that scene graph by way of an
 *   SoHandleEventAction. If no node in the overlay scene graph handles the message
 *   (i.e., calls SoHandleEventAction::setHandled()), the SoEvent is
 *   passed to the normal scene graph in the same manner.
 *   
 *   See the SoWinRenderArea description for additional information.
 *   
 *   Note: Although the class name is CIvfRenderArea, the header file name is
 *   IvfRenderArea.h.
 * 
 * @SEE_ALSO
 *    SoWinRenderArea
 * 
 * 
 */ 

class IVF_API CIvfRenderArea : public CIvfComponent
{
 public:
  CIvfRenderArea() ;
        
  /**
   * This macro declares the minimum number of methods necessary
   * to create a class derived from CIvfComponent
   */
  IVF_COMPONENT_BASE();

  /**
   * create a spinning text logo
   */
  void IvfSpinText(LPCTSTR pText);

 protected: //PROTECTED_TO_DOCUMENT
  /** Destrcutor */
  virtual ~CIvfRenderArea() ;

  /**
   * Pointer to the render area
   */
  SoWinRenderArea *     m_pViewer;
        
  /**
   * Pointer to the camera
   */
  SoCamera *                    m_pCamera;

  /**
   * Pointer to the light
   */
  SoDirectionalLight *m_pLight;

 private:
  static const SbViewportRegion m_defaultViewportRegion;
};

#endif

