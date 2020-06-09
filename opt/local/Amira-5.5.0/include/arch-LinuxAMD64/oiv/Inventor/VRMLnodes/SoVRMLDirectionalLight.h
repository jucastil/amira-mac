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


#ifndef  _SO_VRMLDIRECTIONAL_LIGHT_
#define  _SO_VRMLDIRECTIONAL_LIGHT_

#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/VRMLnodes/SoVRMLLight.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLDirectionalLight
//
//  Directional light source node. A directional light illuminates in
//  rays parallel to a given direction vector. It is equivalent to the
//  GL's "infinite" light source, so named because it is like a point
//  source at an infinite distance (which seems to me to be a pretty
//  bizarre way of naming things.)
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Node representing a directional light source.
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   The SoVRMLDirectionalLight node defines a directional light source that
 *   illuminates along rays parallel to a given 3-dimensional vector. 
 *   
 *   The #direction field specifies the direction vector within the local
 *   coordinate system that the light illuminates in. Light is emitted along parallel
 *   rays from an infinite distance away. A directional light source illuminates only
 *   the objects in its enclosing parent group. The light may illuminate everything
 *   within this coordinate system, including all children and descendants of its
 *   parent group. The accumulated transformations of the parent nodes affect the
 *   light.
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
 *   The SoVRMLDirectionalLight node defines a directional light source that
 *   illuminates along rays parallel to a given 3-dimensional vector. See "Concepts -
 *   Lights" for a definition of the @B ambientIntensity @b, @B color @b,
 *   @B intensity @b, and @B on @b fields.
 *   
 *   The #direction field specifies the direction vector within the local
 *   coordinate system that the light illuminates in. Light is emitted along parallel
 *   rays from an infinite distance away. A directional light source illuminates only
 *   the objects in its enclosing parent group. The light may illuminate everything
 *   within this coordinate system, including all children and descendants of its
 *   parent group. The accumulated transformations of the parent nodes affect the
 *   light.
 *   
 *   See "Concepts - Lighting Model" for a precise description of VRML's lighting
 *   equations. 
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLDirectionalLight {
 *    @TABLE_FILE_FORMAT
 *       @TR ambientIntensity   @TD 0
 *       @TR color              @TD 1 1 1
 *       @TR direction          @TD 0 0 -1
 *       @TR intensity          @TD 1
 *       @TR on                 @TD TRUE
 *       @TR metadata     @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction  @BR
 *        Sets: SoGLLightIdElement
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoSFFloat   @TD   set_ambientIntensity      
 *       @TR   SoSFColor   @TD   set_color      
 *       @TR   SoSFVec3f   @TD   set_direction      
 *       @TR   SoSFFloat   @TD   set_intensity      
 *       @TR   SoSFBool   @TD   set_on
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFFloat   @TD   ambientIntensity_changed      
 *       @TR   SoSFColor   @TD   color_changed      
 *       @TR   SoSFVec3f   @TD   direction_changed      
 *       @TR   SoSFFloat   @TD   intensity_changed      
 *       @TR   SoSFBool   @TD   on_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLDirectionalLight : public SoVRMLLight {

  SO_NODE_HEADER(SoVRMLDirectionalLight);

 public:
  /**
   * Illumination direction vector.
   * 
   */
  SoSFVec3f           direction;

  /**
   * Constructor.
   */
  SoVRMLDirectionalLight();

 SoEXTENDER public:
  // Creates a light source during rendering
  virtual void        GLRender(SoGLRenderAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoVRMLDirectionalLight();
};

#endif /* _SO_VRMLDIRECTIONAL_LIGHT_ */

