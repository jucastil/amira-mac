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


#ifndef  _SO_ENVIRONMENT_
#define  _SO_ENVIRONMENT_

#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/nodes/SoNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoEnvironment
//
//  Node that describes global environmental attributes such as
//  ambient lighting, light attenuation, and fog.
//
//  Ambient lighting is the amount of extra light impinging on each
//  surface point when computing Phong lighting. 
//
//  Light attenuation affects all subsequent lights in a scene. It is
//  a quadratic function of distance from a light source to a surface
//  point. The three coefficients are specified in the attenuation
//  field. Attenuation works only for light sources with a fixed
//  location, such as point and spot lights.
//
//  Fog has one of four types, each of which blends each surface point
//  with the specified fog color. Each type interprets the visibility
//  field to be the distance at which fog totally obscures objects. A
//  visibility value of 0 (the default) causes the SoEnvironment node
//  to set up fog so that the visibility is the distance to the far
//  clipping plane of the current camera.
//
//  Note that this node has effect only during rendering, and that it
//  does not inherit field values from other SoEnvironment nodes.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Global environment node.
 * 
 * @ingroup LightNodes
 * 
 * @DESCRIPTION
 *   This node describes global environmental attributes such as ambient lighting,
 *   light attenuation, and fog.
 *   
 *   Ambient lighting is the amount of extra light impinging on each surface point
 *   when the lighting model is Phong (see SoLightModel).
 *   
 *   Light attenuation affects all subsequent lights in a scene (see SoLight). It is a
 *   quadratic function of distance from a light source to a surface point. The three
 *   coefficients are specified in the #attenuation field. Attenuation works
 *   only for light sources with a fixed location, such as point and spot lights.
 *   
 *   Fog has one of four types, each of which blends each surface point with the
 *   specified fog color. Each type interprets the @B visibility @b field to be the
 *   distance at which fog totally obscures objects. A @B visibility @b value of 0
 *   (the default) causes the SoEnvironment node to set up fog so that the visibility
 *   is the distance to the far clipping plane of the current camera.
 *   
 *   Note that this node has effect only during rendering, and that it does not
 *   inherit field values from other SoEnvironment nodes.
 * 
 * @FILE_FORMAT_DEFAULT
 *    Environment {
 *    @TABLE_FILE_FORMAT
 *       @TR ambientIntensity   @TD 0.2
 *       @TR ambientColor       @TD 1 1 1
 *       @TR attenuation        @TD 0 0 1
 *       @TR fogType            @TD NONE
 *       @TR fogColor           @TD 1 1 1
 *       @TR fogVisibility      @TD 0
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction @BR
 *        Sets the current environment parameters to those specified with this node.
 *        Successive geometries will be rendered using this environment.
 *        Sets: SoEnvironmentElement, SoLightAttenuationElement
 * 
 * @SEE_ALSO
 *    SoLight,
 *    SoLightModel
 * 
 * 
 */ 

class INVENTOR_API SoEnvironment : public SoNode {

  SO_NODE_HEADER(SoEnvironment);

 public:
   /** Type of fog */
  enum FogType {
    /**
     *  No fog 
     */
    NONE,
    /**
     *  Linear increase in opacity with distance 
     */
    HAZE,
    /**
     *  Exponential increase in opacity 
     */
    FOG,
    /**
     *  Exponential squared increase in opacity 
     */
    SMOKE
  };

  // Fields

  /**
   * Intensity of ambient lighting (for Phong lighting).
   * 
   */
  SoSFFloat           ambientIntensity;
  /**
   * RGB color of ambient lighting (for Phong lighting).
   * 
   */
  SoSFColor           ambientColor;

  /**
   * Squared, linear, and constant light attenuation coefficients (in that order)
   * with respect to distance of light from surface (for Phong lighting).
   * 
   */
  SoSFVec3f           attenuation;

  /**
   * Type of fog.
   * Use enum #Type. Default is NONE.
   */
  SoSFEnum            fogType;
  /**
   * Fog color.
   */
  SoSFColor           fogColor;
  /**
   * Fog visibility distance, which is the distance at
   * which fog totally obscures objects.
   * 
   */
  SoSFFloat           fogVisibility;

  /**
   * Creates an environment node with default settings.
   */
  SoEnvironment();

  /**
   * Set the state of the override field.
   * see SoNode::setOverride doc.
   */
  inline virtual void setOverride(const SbBool state)
  { override.setValue(state); }

  /**
   * Returns the state of the override field.
   */
  inline virtual SbBool isOverride() const
  { return override.getValue(); }

 SoEXTENDER public:
  // Only rendering is implemented, since this node has no other effects
  virtual void GLRender(SoGLRenderAction *action);
  virtual void callback(SoCallbackAction *action);
  virtual void doAction(SoAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

  SoSFBool override;

 protected:
  virtual ~SoEnvironment();

};

#endif /* _SO_ENVIRONMENT_ */

