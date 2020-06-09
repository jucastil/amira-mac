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


#ifndef  _SO_LIGHT_
#define  _SO_LIGHT_

#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/SbViewportRegion.h>

class SoCamera;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoLight
//
//  Abstract base light source node.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Abstract base class for all light source nodes.
 *
 * @ingroup LightNodes
 *
 * @DESCRIPTION
 *   SoLight is the abstract base class for all light nodes. A light node defines an
 *   illumination source that may affect subsequent shapes in the scene graph,
 *   depending on the current lighting style. Light sources are affected by the
 *   current transformation. A light node under a separator does not affect any
 *   objects outside that separator.
 *
 *   You can also use a node kit to create a light; see the reference page for
 *   SoLightKit.
 *
 * @FILE_FORMAT_DEFAULT
 *    This is an abstract class. See the reference page of a derived class for the
 *   format and default values.
 *
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction @BR
 *        Activates this light (if so specified) during traversal. All shape nodes that
 *        come after this light in the scene graph are illuminated by this light.
 *
 *
 * @SEE_ALSO
 *    SoDirectionalLight,
 *    SoEnvironment,
 *    SoLightKit,
 *    SoLightModel,
 *    SoMaterial,
 *    SoPointLight,
 *    SoSpotLight
 *
 *
 */

class INVENTOR_API SoLight : public SoNode {

  SO_NODE_ABSTRACT_HEADER(SoLight);

 public:
  /**
   * Determines whether the source is active or inactive. When inactive, the source
   * does not illuminate at all.
   *
   */
  SoSFBool            on;
  /**
   * Illumination intensity of light source. Valid values range from 0.0 (no
   * illumination) to 1.0 (maximum illumination).
   *
   */
  SoSFFloat           intensity;
  /**
   * Light source illumination color.
   *
   */
  SoSFColor           color;

 SoINTERNAL public:
  /** Return a camera associated to the light */
  virtual inline SoCamera* getCamera(SoState* state, SoPath* scene, float visibilityLength);

  static void initClass();
  static void exitClass();

  virtual void    callback(SoCallbackAction *action);
  virtual void    doAction(SoAction *action) ;

  // Returns the OpenGL light Id.
  int32_t getGLLightId() const ;

  // Returns the light Id.
  int32_t getLightId() const ;

  /** Set needed uniforms to enable this light in shader */
  void setShaderLight(SoState *state);

 protected:
  struct Members
  {
    Members();
    ~Members();
    void unref();

    int32_t  m_GLLightId ;
    /** Camera used for shadowmapping */
    SoCamera* m_camera;
  };
  SbThreadStorage<Members*> m_members;

  /** Return per threads members  */
  static SoLight::Members* getMembers(const SoLight* sg);

  SoLight();                          // Makes this abstract

  virtual ~SoLight();

  void setGLLightId(int32_t id);
};

/*******************************************************************************/
SoCamera*
SoLight::getCamera(SoState*, SoPath*, float)
{
  return NULL;
}

#endif /* _SO_LIGHT_ */

