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



#ifndef  _SO_VRMLAPPEARANCE_
#define  _SO_VRMLAPPEARANCE_

#include <Inventor/fields/SoMFColor.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/VRMLnodes/SoVRMLNode.h>

class SoColorPacker;
class SoChildList;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLAppearance
//
//  Node that holds material, texture, and textureTransform nodes
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Specifies the material, texture, textureTransform
 *   fillProperties, and lineProperties nodes.
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   The SoVRMLAppearance node specifies the visual properties of geometry by
 *   defining the material and texture nodes. The value for each of the fields in
 *   this node can be NULL. However, if the field is non-NULL, it must contain one
 *   node of the appropriate type.
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
 *   The SoVRMLAppearance node specifies the visual properties of geometry by defining
 *   the material and texture nodes. The value for each of the fields in this node
 *   can be NULL. However, if the field is non-NULL, it must contain one node of the
 *   appropriate type.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLAppearance {
 *    @TABLE_FILE_FORMAT
 *       @TR material           @TD NULL
 *       @TR texture            @TD NULL
 *       @TR textureTransform   @TD NULL
 *       @TR fillProperties     @TD NULL
 *       @TR lineProperties     @TD NULL
 *       @TR metadata           @TD NULL   
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction,  SoCallbackAction  @BR
 * 
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoSFNode   @TD   set_material      
 *       @TR   SoSFNode   @TD   set_texture      
 *       @TR   SoSFNode   @TD   set_textureTransform
 *       @TR   SoSFNode   @TD   set_fillProperties @NI 
 *       @TR   SoSFNode   @TD   set_lineProperties
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFNode   @TD   material_changed      
 *       @TR   SoSFNode   @TD   texture_changed      
 *       @TR   SoSFNode   @TD   textureTransform_changed
 *       @TR   SoSFNode   @TD   fillProperties_changed @NI  
 *       @TR   SoSFNode   @TD   lineProperties_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLAppearance : public SoVRMLNode {

  SO_NODE_HEADER(SoVRMLAppearance);

 public:
  // Fields

  /**
   * The #material field, if specified, must contain an SoVRMLMaterial node. If
   * the #material field is NULL or unspecified, lighting is off (all lights
   * are ignored during rendering of the object that references this SoVRMLAppearance
   * node) and the unlit object color is (0, 0, 0). See SoVRMLLightfor details of the
   * VRML lighting model.
   * 
   */
  SoSFNode      material;
  /**
   * The #texture field, if specified, must contain one of the various types of
   * texture nodes (SoVRMLImageTexture, SoVRMLMovieTexture, or SoVRMLPixelTexture).
   * If the texture node is NULL or unspecified, the object that references this
   * SoVRMLAppearance is not textured.
   * 
   */
  SoSFNode      texture;
  /**
   * The #textureTransform field, if specified, must contain an
   * SoVRMLTextureTransform node. If the #texture field is NULL or unspecified,
   * or if the #textureTransform is NULL or unspecified, the
   * #textureTransform field has no effect.
   * 
   */
  SoSFNode      textureTransform;
   /**
   *  @NI The #fillProperties field, if specified, must contain an
   * SoVRMLFillProperties node. If the #fillProperties field is NULL
   * or unspecified, the #fillProperties field has no effect.
   *
   * @FIELD_SINCE_OIV 5.0
   *
   * @B NOTE 2:@b This field is not compatible with VRML97.
   * If you specify a non-default value for this field, when this node
   * is written to a VRML file, the file will contain this incompatible
   * field and standard VRML97 file readers will not be able to read it.
   */
  SoSFNode      fillProperties;
   /**
   * The #lineProperties field, if specified, must contain an
   * SoVRMLLineProperties node. If the #linelProperties field is NULL
   * or unspecified, the #lineProperties field has no effect.
   *
   * @FIELD_SINCE_OIV 5.0
   *
   * @B NOTE 2:@b This field is not compatible with VRML97.
   * If you specify a non-default value for this field, when this node
   * is written to a VRML file, the file will contain this incompatible
   * field and standard VRML97 file readers will not be able to read it.
   */
  SoSFNode      lineProperties;
  /**
   * Constructor.
   */
  SoVRMLAppearance();

 SoEXTENDER public:
  // Implement actions
  virtual void        doAction(SoAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        search(SoSearchAction *action);


 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();
  virtual SoChildList *getChildren() const;
  virtual SoChildList *internalGetChildren() const;

  SbBool               validateNewFieldValue(SoField *pField,
                                             void *newValue);
  virtual void        notify(SoNotList *list);
  // Copies the contents of the given node into this instance. The
  // default implementation copies just field values and the name.
  virtual void        copyContents(const SoFieldContainer *fromFC,
                                   SbBool copyConnections);
 protected:
  virtual ~SoVRMLAppearance();
  SoColorPacker *colorPacker;

  SoChildList *children;
  friend class SoPath;    // Need to access "children" in SoPath::truncate()

 private:
  void                rebuildChildrenList();
  // Temporary storage during traversal
  // (traversal state wants SoMF fields and we only have SoSF fields!)
  static SoMFColor    *m_diffuse;
  static SoMFColor    *m_emissive;
  static SoMFColor    *m_specular;
  static SoMFFloat    *m_transparency;
  static SoMFFloat    *m_shininess;
  static SoMFColor    *m_ambient;

  // Count instances of this type so we can clean up the temporary storage
  static int instanceCounter;
};

#endif /* _SO_VRMLAPPEARANCE_ */

