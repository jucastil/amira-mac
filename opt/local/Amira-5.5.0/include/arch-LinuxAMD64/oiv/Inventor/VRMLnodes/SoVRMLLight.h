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


#ifndef  _SO_VRMLLIGHT_
#define  _SO_VRMLLIGHT_

#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/VRMLnodes/SoVRMLNode.h>
//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLLight
//
//  Abstract base light source node.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Abstract base class for all VRML97 light nodes.
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   SoVRMLLight is the abstract base class for all light nodes. A light node defines
 *   an illumination source that may affect subsequent shapes in the scene graph,
 *   depending on the current lighting style. Light sources are affected by the
 *   current transformation. A light node under a transform does not affect any
 *   object outside that transform.
 *
 * @FILE_FORMAT_DEFAULT
 *   This is an abstract class. See the reference page of a derived class for the
 *   format and default values.
 *
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction  @BR
 * 
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoSFFloat   @TD   set_ambientIntensity      
 *       @TR   SoSFColor   @TD   set_color      
 *       @TR   SoSFFloat   @TD   set_intensity      
 *       @TR   SoSFBool   @TD   set_on
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFFloat   @TD   ambientIntensity_changed      
 *       @TR   SoSFColor   @TD   color_changed      
 *       @TR   SoSFFloat   @TD   intensity_changed      
 *       @TR   SoSFBool   @TD   on_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLLight : public SoVRMLNode {

  SO_NODE_ABSTRACT_HEADER(SoVRMLLight);

 public:
  /**
   * Specifies whether the light is on (TRUE) or off (FALSE).
   * 
   */
  SoSFBool            on;
  /**
   * Specifies the brightness of the direct emission from the light.
   * 
   */
  SoSFFloat           intensity;
  /**
   * Specifies the spectral color properties of the light.
   * 
   */
  SoSFColor           color;
  /**
   * Specifies the brightness of the ambient emissions of the light.
   * 
   */
  SoSFFloat           ambientIntensity;
    

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 SoEXTENDER public:
  // Implements actions
  virtual void        GLRender(SoGLRenderAction *action);

 protected:
  SoVRMLLight();                              // Makes this abstract

  virtual ~SoVRMLLight();
};

#endif /* _SO_VRMLLIGHT_ */

