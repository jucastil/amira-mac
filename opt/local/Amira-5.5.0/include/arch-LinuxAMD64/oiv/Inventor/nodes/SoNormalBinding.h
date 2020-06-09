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


#ifndef  _SO_NORMAL_BINDING_
#define  _SO_NORMAL_BINDING_

#include <Inventor/elements/SoNormalBindingElement.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/nodes/SoNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoNormalBinding
//
//  Normal binding node. This indicates how multiple surface normals are
//  to be distributed over an object.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Node that specifies how multiple surface normals are bound to shapes.
 * 
 * @ingroup PropertyNodes
 * 
 * @DESCRIPTION
 *   This node specifies how the current normals are bound to shapes that follow in
 *   the scene graph. Each shape node may interpret bindings differently.
 *   
 *   The bindings for faces and vertices are meaningful only for shapes that are made
 *   from faces and vertices. Similarly, the indexed bindings are only used by the
 *   shapes that allow indexing. For bindings that require multiple normals, be sure
 *   to have at least as many normals defined as are necessary; otherwise, errors
 *   will occur.
 * 
 * @FILE_FORMAT_DEFAULT
 *    NormalBinding {
 *    @TABLE_FILE_FORMAT
 *       @TR value   @TD PER_VERTEX_INDEXED
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction,  SoRayPickAction @BR
 *        Sets the current normal binding type. Sets: SoNormalBindingElement
 * 
 * 
 * @SEE_ALSO
 *    SoMaterialBinding,
 *    SoNormal,
 *    SoTextureCoordinateBinding,
 *    SoVertexShape,
 *    SoVertexProperty
 * 
 * 
 */ 

class INVENTOR_API SoNormalBinding : public SoNode {

  SO_NODE_HEADER(SoNormalBinding);

 public:

   /** Binding */
  enum Binding {
    /**
     *  Whole object has same normal 
     */
    OVERALL           = SoNormalBindingElement::OVERALL,
    /**
     *  One normal for each part of object 
     */
    PER_PART          = SoNormalBindingElement::PER_PART,
    /**
     *  One normal for each part, indexed 
     */
    PER_PART_INDEXED  = SoNormalBindingElement::PER_PART_INDEXED,
    /**
     *  One normal for each face of object 
     */
    PER_FACE          = SoNormalBindingElement::PER_FACE,
    /**
     *  One normal for each face, indexed 
     */
    PER_FACE_INDEXED  = SoNormalBindingElement::PER_FACE_INDEXED,
    /**
     *  One normal for each vertex of object 
     */
    PER_VERTEX        = SoNormalBindingElement::PER_VERTEX,
    /**
     *  One normal for each vertex, indexed 
     */
    PER_VERTEX_INDEXED= SoNormalBindingElement::PER_VERTEX_INDEXED

#ifndef IV_STRICT
    // Obsolete bindings:
    ,
    DEFAULT           = PER_VERTEX_INDEXED,
    NONE              = PER_VERTEX_INDEXED
#endif
  };

  // Fields
  /**
   * Specifies how to bind normals to shapes.
   * Use enum #Binding. Default is PER_VERTEX_INDEXED.
   * 
   */
  SoSFEnum            value;

  /**
   * Creates a normal binding node with default settings.
   */
  SoNormalBinding();

 SoEXTENDER public:
  virtual void        doAction(SoAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        pick(SoPickAction *action);
  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoNormalBinding();

  // Reads stuff into instance. Upgrades old bindings.
  virtual SbBool      readInstance(SoInput *in, unsigned short flags);
};

#endif /* _SO_NORMAL_BINDING_ */

