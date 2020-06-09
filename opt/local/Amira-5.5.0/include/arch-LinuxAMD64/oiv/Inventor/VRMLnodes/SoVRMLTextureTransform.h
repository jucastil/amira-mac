/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Thaddeus Beier (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_VRMLTEXTURE_TRANSFORM_
#define  _SO_VRMLTEXTURE_TRANSFORM_

#include <Inventor/fields/SoSFVec2f.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/VRMLnodes/SoVRMLNode.h>
//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLTextureTransform
//
//  2D Texture transformation node.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Defines a 2D transformation.
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   The SoVRMLTextureTransform node defines a 2D transformation that is applied to
 *   texture coordinates (see SoVRMLTextureCoordinate). This node affects the way
 *   textures are applied to the surface of geometry. The transformation consists of
 *   (in order) a non-uniform scale about an arbitrary center point, a rotation about
 *   the center point, and a translation. This allows for changes to the size,
 *   orientation, and position of textures on shapes. Note that these changes appear
 *   reversed when viewed in the surface of geometry. For example, a #scale
 *   value of @B 2 @b @B 2 @b will scale the texture coordinates and have the net
 *   effect of shrinking the texture size by a factor of 2 (texture coordinates are
 *   twice as large and thus cause the texture to repeat). A translation of
 *   @B 0.5 @b @B 0.0 @b translates the texture coordinates +.5 units along the
 *   S-axis and has the net effect of translating the texture -0.5 along the S-axis
 *   on the geometry's surface. A rotation of pi/2 of the texture coordinates results
 *   in a - pi/2 rotation of the texture on the geometry.
 *   
 *   Note: The VRML97 specification indicates that transformations should be
 *   performed in the order translate, rotate, and scale. Open Inventor performs the
 *   transformations in the order scale, rotate, translate.
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
 *   The SoVRMLTextureTransform node defines a 2D transformation that is applied to
 *   texture coordinates (see SoVRMLTextureCoordinate). This node affects the way
 *   textures are applied to the surface of geometry. The transformation consists of
 *   (in order) a translation, a rotation about an arbitrary center point, and a
 *   non-uniform scale about the center point. This allows for changes to the size,
 *   orientation, and position of textures on shapes. Note that these changes appear
 *   reversed when viewed in the surface of geometry. For example, a #scale
 *   value of @B 2 @b @B 2 @b will scale the texture coordinates and have the net
 *   effect of shrinking the texture size by a factor of 2 (texture coordinates are
 *   twice as large and thus cause the texture to repeat). A translation of
 *   @B 0.5 @b @B 0.0 @b translates the texture coordinates +.5 units along the
 *   S-axis and has the net effect of translating the texture -0.5 along the S-axis
 *   on the geometry's surface. A rotation of pi/2 of the texture coordinates results
 *   in a - pi/2 rotation of the texture on the geometry.
 *   
 *   The #center field specifies a translation offset in texture coordinate
 *   space about which the #rotation and #scale fields are applied. The
 *   #scale field specifies a scaling factor in S and T of the texture
 *   coordinates about the #center point - #scale values must be >= 0.0.
 *   The #rotation field specifies a rotation in radians of the texture
 *   coordinates about the #center point after the scale has taken place. The
 *   #translation field specifies a translation of the texture coordinates. 
 *   
 *   Given a 2-dimensional texture coordinate @B T @b and an SoVRMLTextureTransform
 *   node, @B T @b is transformed into point @B T @b' by a series of intermediate
 *   transformations. In matrix-transformation notation, where C (center), T
 *   (translation), R (rotation), and S (scale) are the equivalent transformation
 *   matrices,
 *   
 *   <PRE>
 *    @B T' @b = TT x C x R x S x -TC x @B T @b @B  (where T is a column
 *   vector) @b 
 *    </PRE>
 *    Note that SoVRMLTextureTransforms cannot combine or accumulate.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLTextureTransform {
 *    @TABLE_FILE_FORMAT
 *       @TR center        @TD 0 0
 *       @TR rotation      @TD 0
 *       @TR scale         @TD 1 1
 *       @TR translation   @TD 0 0
 *       @TR metadata     @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction,  SoPickAction,  SoCallbackAction,  SoGetMatrixAction  @BR
 *      Sets: SoTextureMatrixElement
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoSFVec2f   @TD   set_center      
 *       @TR   SoSFFloat   @TD   set_rotation      
 *       @TR   SoSFVec2f   @TD   set_scale      
 *       @TR   SoSFVec2f   @TD   set_translation
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFVec2f   @TD   center_changed      
 *       @TR   SoSFFloat   @TD   rotation_changed      
 *       @TR   SoSFVec2f   @TD   scale_changed      
 *       @TR   SoSFVec2f   @TD   translation_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLTextureTransform : public SoVRMLNode {

  SO_NODE_HEADER(SoVRMLTextureTransform);

 public:
  // Fields
  /**
   * Translation in S and T.
   * 
   */
  SoSFVec2f           translation;
  /**
   * Specifies a rotation in radians of the texture coordinates about the center
   * after the scale has taken place.
   * 
   */
  SoSFFloat           rotation;
  /**
   * Scaling factors in S and T.
   * 
   */
  SoSFVec2f           scale;
  /**
   * Specifies a translation offset in texture coordinate space about which the
   * rotation and scale fields are applied.
   * 
   */
  SoSFVec2f           center;

  /**
   * Constructor.
   */
  SoVRMLTextureTransform();

 SoEXTENDER public:
  virtual void        doAction(SoAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        getMatrix(SoGetMatrixAction *action);
  virtual void        pick(SoPickAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoVRMLTextureTransform();
};

#endif /* _SO_VRMLTEXTURE_TRANSFORM_ */

