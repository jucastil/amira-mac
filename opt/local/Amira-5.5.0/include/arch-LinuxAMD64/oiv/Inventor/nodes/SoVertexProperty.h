/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Alan Norton (MMM yyyy)
** Modified by : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/



#ifndef  _SO_VERTEX_PROPERTY
#define  _SO_VERTEX_PROPERTY

#include <Inventor/fields/SoMFUInt32.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoMFVec2f.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/elements/SoMaterialBindingElement.h>

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

class SoColorPacker;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVertexProperty
//
//  SoNode class that manages arrays of data for GLVertex Array Extension.
//  Data arrays include: vertices, normals, colors, texture coordinates.
//  Also has NormalBinding and MaterialBinding fields
//
//////////////////////////////////////////////////////////////////////////////

class SoVertexPropertyCache;

/**
 * Vertex property node.
 * 
 * @ingroup PropertyNodes
 * 
 * @DESCRIPTION
 *   This property node may be used to efficiently specify coordinates, normals,
 *   texture coordinates, colors, transparency values, material binding and normal
 *   binding for vertex-based shapes, i.e., shapes of class SoVertexShape. An
 *   SoVertexProperty node can be used as a child of a group node in a scene graph,
 *   in which case the properties it specifies are inherited by subsequent shape
 *   nodes in the graph. It can also be directly referenced as the
 *   @B VertexProperty @b SoSFField of a vertex-based shape, bypassing scene graph
 *   inheritance.
 *   
 *   When directly referenced by a @B VertexProperty @b SoSFField of a vertex-based
 *   shape, the SoVertexProperty node is the most efficient way of specifying
 *   vertex-based shapes. Use of the directly referenced SoVertexProperty node
 *   results in significantly faster scene rendering than scene graph inheritance of
 *   vertex properties, provided all required vertex properties are specified in the
 *   SoVertexProperty node.
 *   
 *   Because the class SoVertexProperty is derived from SoNode, a vertex property node
 *   can be inserted as a child node in a scene graph. When inserted as a node in a
 *   scene graph, the SoVertexProperty node is traversed as any other property node
 *   and the properties it specifies are inherited by subsequent shape nodes in the
 *   scene graph. It specifies the current material and normal bindings, and can be
 *   used to specify the current 3D coordinates, the current normals, the current
 *   texture coordinates, the current diffuse colors, and the current
 *   transparencies.
 *   
 *   All multiple-valued fields in the SoVertexProperty node are optional. If a field
 *   is not present (i.e. if it has 0 values), then shapes that require the missing
 *   information are required to obtain it from the current traversal state. However,
 *   users are cautioned that, for optimal performance, the vertex property node
 *   should be referenced as the @B VertexProperty @b field of an SoVertexShape, and
 *   should specify in its fields all values required to render that shape.
 *   
 *   The various fields in a vertex property node can be used in place of
 *   corresponding fields in other property nodes, as follows: The #vertex
 *   field contains 3D coordinates, as in the @B point @b field of an SoCoordinate3
 *   node. The #normal field contains normal vectors, as in the @B vector @b
 *   field of the SoNormal node. The #orderedRGBA field contains packed colors
 *   in the hexadecimal format @B 0xrrggbbaa @b, where @B rr @b is the red value
 *   (between 00 and 0xFF hex) @B gg @b is the green value (between 00 and 0xFF hex)
 *   @B bb @b is the blue value (between 00 and 0xFF hex) @B aa @b is the alpha
 *   value (between 00 = transparent and 0xFF = opaque). The packed colors are
 *   equivalent to an SoPackedColor node, and provide values for both diffuse color
 *   and transparency. The #texCoord field replaces the @B point @b field of
 *   the SoTextureCoordinate2 node.
 *   
 *   If the transparency type is SoGLRenderAction::SCREEN_DOOR(), only the first
 *   transparency value will be used. With other transparency types, multiple
 *   transparencies will be used.
 *   
 *   The #materialBinding field replaces the @B value @b field of the
 *   SoMaterialBinding node. The #materialBinding field in a directly
 *   referenced SoVertexProperty node has no effect unless there is a nonempty
 *   #orderedRGBA field, in which case the material binding specifies the
 *   assignment of diffuse colors and alpha values to the shape. The
 *   #materialBinding field can take as value any of the material bindings
 *   supported by Open Inventor.
 *   
 *   The #normalBinding field replaces the @B value @b field of the
 *   SoNormalBinding node. The #normalBinding field of a directly referenced
 *   SoVertexProperty node has no effect unless there is a nonempty #normal
 *   field, in which case the normal binding specifies the assignment of normal
 *   vectors to the shape. The value of the #normalBinding field can be any of
 *   the normal bindings supported by Open Inventor.
 * 
 * @FILE_FORMAT_DEFAULT
 *    VertexProperty {
 *    @TABLE_FILE_FORMAT
 *       @TR vertex            @TD [ ]
 *       @TR normal            @TD [ ]
 *       @TR texCoord          @TD [ ]
 *       @TR texCoord3         @TD [ ]
 *       @TR orderedRGBA       @TD [ ]
 *       @TR materialBinding   @TD OVERALL
 *       @TR normalBinding     @TD PER_VERTEX_INDEXED
 *       @TR forceSending   @TD FALSE
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction,  SoPickAction @BR
 *        When traversed in a scene graph, sets coordinates, normals, texture
 *        coordinates, diffuse colors, transparency, normal binding and material binding
 *        in current traversal state. If not traversed, has no effect on current traversal
 *        state associated with action. The normalBinding field has no effect if there are
 *        no normals. The materialBinding has no effect if there are no packed colors.
 *        Sets: SoCoordinateElement, SoNormalElement, SoNormalBindingElement, SoLazyElement
 *              SoMaterialBindingElement, SoTextureCoordinateElement
 * 
 *    SoGetBoundingBoxAction @BR
 *        When traversed in a scene graph, sets coordinates in current traversal state.
 *        If not traversed, has no effect on current traversal state associated with
 *        action. Sets: SoCoordinateElement
 * 
 * 
 * @SEE_ALSO
 *    SoIndexedTriangleStripSet,
 *    SoIndexedFaceSet,
 *    SoIndexedLineSet,
 *    SoTriangleStripSet,
 *    SoLineSet,
 *    SoFaceSet,
 *    SoPointSet,
 *    SoQuadMesh,
 *    SoVertexShape,
 *    SoIndexedShape,
 *    SoNonIndexedShape
 * 
 * 
 */ 

class INVENTOR_API SoVertexProperty : public SoNode {

  SO_NODE_HEADER(SoVertexProperty);

 public:

  /**
   * Vertex coordinate(s).
   */
  SoMFVec3f vertex;
  /**
   * 2D texture coordinate(s).
   */
  SoMFVec2f texCoord;
  /**
   * 3D texture coordinate(s).
   */
  SoMFVec3f texCoord3;

  /**
   * Forces the texture coordinates to be sent to OpenGL
   * even if no texture is bound.
   */
  SoSFBool forceSending; 

  /**
   * Normal vector(s).
   */
  SoMFVec3f normal;

  /**
   * Normal binding.
   * Use enum #Binding. Default is PER_VERTEX_INDEXED.
   */
  SoSFEnum normalBinding;

  /**
   * Packed color(s), including transparencies.
   */
  SoMFUInt32 orderedRGBA;

  /**
   * Material binding.
   * Use enum #Binding. Default is OVERALL.
   */
  SoSFEnum materialBinding;

   
    /** Binding */
  enum Binding {
    /**
     *  Whole object has same material/normal 
     */
    OVERALL = SoMaterialBindingElement::OVERALL,
    /**
     *  One material/normal for each part of object 
     */
    PER_PART = SoMaterialBindingElement::PER_PART,
    /**
     *  One material/normal for each part, indexed 
     */
    PER_PART_INDEXED = SoMaterialBindingElement::PER_PART_INDEXED,
    /**
     *  One material/normal for each face of object 
     */
    PER_FACE = SoMaterialBindingElement::PER_FACE,
    /**
     *  One material/normal for each face, indexed 
     */
    PER_FACE_INDEXED = SoMaterialBindingElement::PER_FACE_INDEXED,
    /**
     *  One material/normal for each vertex of object 
     */
    PER_VERTEX = SoMaterialBindingElement::PER_VERTEX,
    /**
     *  One material/normal for each vertex, indexed 
     */
    PER_VERTEX_INDEXED = SoMaterialBindingElement::PER_VERTEX_INDEXED
  };

  /**
   * Creates an SoVertexProperty node with default settings.
   */
  SoVertexProperty();

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
  virtual void doAction(SoAction *action);
  virtual void GLRender(SoGLRenderAction *action);
  virtual void getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void callback(SoCallbackAction *action);
  virtual void pick(SoPickAction *action);
  virtual void getPrimitiveCount(SoGetPrimitiveCountAction *action);

  SbBool isTransparent();

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

  SoSFBool override;

  SoColorPacker *getColorPacker2() const;
  enum Transparent {
    YES,
    NO,
    UNKNOWN
  };

  inline uint32_t getVextexTimeStamp() const
  { return m_vertexTimeStamp; }

 protected:
  virtual ~SoVertexProperty();

  SoColorPacker *getColorPacker() const;

 private:
  // check for transparency when field changes.
  virtual void        notify(SoNotList *list);
  // store whether transparent or not
  Transparent transparent;
  uint32_t m_vertexTimeStamp;
  mutable SoColorPacker *m_colorPacker2;
  mutable SoColorPacker *m_colorPacker;
};


#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif /* _SO_VERTEX_PROPERTY */

