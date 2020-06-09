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



#ifndef  _SO_VRMLFOG_
#define  _SO_VRMLFOG_

#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFTime.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/VRMLnodes/SoVRMLNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLFog
//
//  Node that defines the fog parameters 
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Simulates fog.\ @NO_ACTION
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   The SoVRMLFog node provides a way to simulate atmospheric effects.
 * 
 * @VRML2_SPECIFICATION
 *    This section describes the expected behavior of the node in a conforming VRML97
 *   browser application. In some cases, the application is responsible for
 *   implementing portions of the expected behavior. Open Inventor viewer classes and
 *   IVF classes implement some of the application behaviors.
 *   
 *   This section may reference portions of the VRML97 specification that are not
 *   present in this help file. The complete VRML97 spec is available at
 *   @B http://www.web3d.org @b.
 *   
 *   The SoVRMLFog node provides a way to simulate atmospheric effects by blending
 *   objects with the color specified by the #color field based on the objects'
 *   distances from the viewer. The distances are calculated in the coordinate space
 *   of the SoVRMLFog node. The #visibilityRange specifies the distance (in the
 *   SoVRMLFog node's coordinate space) at which objects are totally obscured by the
 *   fog. Objects located #visibilityRange meters or more away from the viewer
 *   are drawn with a constant color of #color. Objects very close to the
 *   viewer are blended very little with the fog #color. A
 *   #visibilityRange of 0.0 or less disables the SoVRMLFog node. Note that
 *   #visibilityRange is affected by the scaling transformations of the
 *   SoVRMLFog node's parents - translations and rotations have no affect on
 *   #visibilityRange.
 *   
 *   SoVRMLFog nodes are bindable children nodes and thus there exists an SoVRMLFog
 *   stack, in which the top-most SoVRMLFog node on the stack is currently active. To
 *   push an SoVRMLFog node onto the top of the stack, a TRUE value is sent to the
 *   @B set_bind @b eventIn. Once active, the SoVRMLFog is then bound to the
 *   browser's view. A FALSE value of @B set_bind @b pops the SoVRMLFog from the
 *   stack and unbinds it from the browser viewer. See "Concepts - Bindable Children
 *   Nodes" for more details on the SoVRMLFog stack. 
 *   
 *   The #fogType field controls how much of the fog color is blended with the
 *   object as a function of distance. If #fogType is "LINEAR" (the default),
 *   then the amount of blending is a linear function of the distance, resulting in a
 *   depth cuing effect. If #fogType is "EXPONENTIAL" then an exponential
 *   increase in blending should be used, resulting in a more natural fog
 *   appearance.
 *   
 *   For best visual results, the SoVRMLBackground node (which is unaffected by the
 *   SoVRMLFog node) should be the same color as the fog node. The SoVRMLFog node can
 *   also be used in conjunction with the @B visibilityLimit @b field of
 *   SoVRMLNavigationInfo node to provide a smooth fade out of objects as they
 *   approach the far clipping plane.
 *   
 *   See the section "Concepts - Lighting Model" for details on lighting calculations.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLFog {
 *    @TABLE_FILE_FORMAT
 *       @TR color             @TD 1 1 1
 *       @TR fogType           @TD "LINEAR"
 *       @TR visibilityRange   @TD 0
 *       @TR metadata     @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoSFBool   @TD   set_bind      
 *       @TR   SoSFColor   @TD   set_color      
 *       @TR   SoSFString   @TD   set_fogType      
 *       @TR   SoSFFloat   @TD   set_visibilityRange
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFBool   @TD   isBound 
 *       @TR   SoSFBool   @TD   bindTime      
 *       @TR   SoSFColor   @TD   color_changed      
 *       @TR   SoSFString   @TD   fogType_changed      
 *       @TR   SoSFFloat   @TD   visibilityRange_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLFog : public SoVRMLNode {

  SO_NODE_HEADER(SoVRMLFog);

 public:
  // Fields

  SoSFString          fogType;         // Fog blending parameter
  SoSFFloat           visibilityRange; // Distane at which an object 
  //    is not visible
  SoSFColor           color;           // Fog color

  /**
   * Constructor.
   */
  SoVRMLFog();


 SoEXTENDER public:
  // Implements actions
  virtual void        GLRender(SoGLRenderAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  SoSFBool            set_bind;        // eventIn
  SoSFBool             isBound;        // eventOut
  SoSFTime            bindTime;        // eventOut
  virtual ~SoVRMLFog();

  // NOTE: This node has not been fully implemented.
};

#endif /* _SO_VRMLFOG_ */

