/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_MATERIAL_
#define  _SO_MATERIAL_

#include <Inventor/fields/SoMFColor.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/nodes/SoNode.h>
class SoColorPacker;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoMaterial
//
//  Surface material node.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Surface material definition node.
 *
 * @ingroup LightNodes
 *
 * @DESCRIPTION
 *   This node defines the current surface material properties for all subsequent
 *   shapes. SoMaterial sets several components of the current material during
 *   traversal.
 *
 *   Multiple values can be specified for the #diffuseColor and
 *   #transparency. Different shapes interpret materials with multiple values
 *   differently. To bind materials to shapes, use an SoMaterialBinding node.
 *
 * @FILE_FORMAT_DEFAULT
 *    Material {
 *    @TABLE_FILE_FORMAT
 *       @TR ambientColor    @TD 0.2 0.2 0.2
 *       @TR diffuseColor    @TD 0.8 0.8 0.8
 *       @TR specularColor   @TD 0 0 0
 *       @TR reflectiveColor @TD 0 0 0
 *       @TR emissiveColor   @TD 0 0 0
 *       @TR shininess       @TD 0.2
 *       @TR transparency    @TD 0
 *       @TR receiveShadow   @TD FALSE
 *    @TABLE_END
 *    }
 *
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction @BR
 *        Sets the ambient color, the diffuse color, the specular color, the emissive
 *        color, the shininess, and the transparency of the current material.
 *    Sets: SoLazyElement, SoMaterialElement
 *
 * @SEE_ALSO
 *    SoBaseColor,
 *    SoLightModel,
 *    SoMaterialBinding,
 *    SoPackedColor,
 *    SoVertexProperty,
 *    SoDirectVizManager.
 *
 *
 */

class INVENTOR_API SoMaterial : public SoNode {

  SO_NODE_HEADER(SoMaterial);

 public:
  // Fields
  /**
   * Ambient color of the surface.
   *
   */
  SoMFColor           ambientColor;
  /**
   * Diffuse color(s) of the surface.
   *
   */
  SoMFColor           diffuseColor;
  /**
   * Specular color of the surface.
   *
   */
  SoMFColor           specularColor;
  /**
   * Emissive color of the surface.
   *
   */
  SoMFColor           emissiveColor;
  /**
   * Shininess coefficient of the surface. Values can range from 0.0 to 1.0.
   *
   * The dot product of the vector reflected by the surface normal and 
   * the inverted light vector is raised to the "Shininess" power. 
   * The higher the shininess number, the smaller the resulting specular 
   * highlight turns out to be.
   */
  SoMFFloat           shininess;
  /**
   * Transparency value(s) of the surface. Values can range from 0.0 for opaque
   * surfaces to 1.0 for completely transparent surfaces. If the transparency type is
   * SoGLRenderAction::SCREEN_DOOR() then only the first transparency value will
   * be used. With other transparency types, multiple transparencies will be used, if
   * the SoMaterial node contains as many transparencies as diffuse colors. If there
   * are not as many transparencies as diffuse colors, only the first transparency
   * will be used.
   *
   */
  SoMFFloat           transparency;

   /**
   * DirectViz parameter. Specifies that all the shapes using this material node will
   * receive shadows from other shapes when rendering using DirectViz.
   *
   * @FIELD_SINCE_OIV 6.1
   */
  SoSFBool              receiveShadow;

   /**
   * DirectViz parameter. Specifies the reflective color of the shape.
   * When set to black (0,0,0), the object is not reflective.
   * To simulate a perfect mirror, the reflectiveColor should be set to white (1, 1, 1),
   * and all other color field values to black (0, 0, 0).
   * The reflective component is added to the overall color of the object.
   *
   * @FIELD_SINCE_OIV 6.1
   */
  SoMFColor           reflectiveColor;

  /**
   * Creates a material node with default settings.
   */
  SoMaterial();

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
  virtual void        doAction(SoAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        write(SoWriteAction *writeAction);
  virtual void        rayPick(SoRayPickAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

  SoSFBool override;

 protected:
  virtual ~SoMaterial();
  SoColorPacker *colorPacker;
};

#endif /* _SO_MATERIAL_ */

