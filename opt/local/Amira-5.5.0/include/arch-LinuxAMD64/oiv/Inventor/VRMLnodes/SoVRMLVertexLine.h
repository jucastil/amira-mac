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


#ifndef  _SO_VRMLVERTEX_LINE_
#define  _SO_VRMLVERTEX_LINE_

#include <Inventor/SbBasic.h>

#include <Inventor/fields/SoMFUInt32.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/fields/SoSFBool.h>

#include <Inventor/nodes/SoMaterialBinding.h>
#include <Inventor/nodes/SoTextureCoordinateBinding.h>
#include <Inventor/VRMLnodes/SoVRMLGeometry.h>
#include <Inventor/elements/SoShapeStyleElement.h>
#include <Inventor/elements/SoMaterialBindingElement.h>


#ifndef HIDDEN_FROM_DOC
class SoVRMLVertexLine;

typedef WINGDIAPI void APIENTRY SoVPCacheFunc(const char *const);

/**
 * [OIV-WRAPPER-NO-WRAP]
 */
SoEXTENDER class INVENTOR_API SoVRMLLinePropertyCache {
 public:

  // API used by shapes:

  SbBool mightNeedSomethingFromState(const SoShapeStyleElement *sse) const
    { return needFromState & sse->getRenderCaseMask(); }

  void        fillInCache(SoNode *, SoNode *, SoNode *, 
                          const int32_t *, const int32_t *, 
                          SbBool ,  SoState *);

  int         getRenderCase(const SoShapeStyleElement *sse) const
    { return renderCase & sse->getRenderCaseMask(); }

  void        sendVertex(const char *vp) const
    { (*vertexFunc)(vp); }
  void        sendColor(const char *cp) const
    { (*colorFunc)(cp); }

  int         getNumVertices() const { return numVerts; }
  int         getNumColors() const { return numColors; }

  const char *getVertices(int i) const
    { return vertexPtr + vertexStride*i; }
  const char *getColors(int i) const
    { return colorPtr + colorStride*i; }

  SbBool colorIsInVtxProp() const {return colorIsInVP;}

  //Indicates if non-opaque transparency is in vertex property.
  SbBool transpIsInVtxProp() const {return transpIsInVP;}

  void setTranspIsInVP(SbBool flag){ transpIsInVP = flag;}

  int         getVertexStride() const { return vertexStride; }
  int         getColorStride() const { return colorStride; }


  SoMaterialBindingElement::Binding   getMaterialBinding()
    { return (SoMaterialBindingElement::Binding)materialBinding; }


  void        invalidate() { needFromState = ALL_FROM_STATE_BITS; }

  // Constructor.   Initializes everything.
  SoVRMLLinePropertyCache();

 public:

  // Tables of functions, data, and strides to increment through data.
  SoVPCacheFunc *vertexFunc;
  const char *vertexPtr;
  int vertexStride, numVerts;
  SoVPCacheFunc *colorFunc;
  const char *colorPtr;
  int colorStride, numColors;

  unsigned char needFromState;

  // 32 rendering cases.  Non-indexed shapes can get away with just
  // looking at the low 5 bits.  The bits are arranged like this:
  // 43210  BITS
  // -----  ----
  // 00...  Overall color
  // 01...  Part color
  // 10...  Face color
  // 11...  Vtx color
  // ..00.  Overall/No norm
  // ..01.  Part norm
  // ..10.  Face norm
  // ..11.  Vtx norm
  // ....?  Explicit exture coordinates needed
 SoINTERNAL public:
  enum {
    COLOR_BITS = 0x18,
    PART_COLOR = 0x8,
    FACE_COLOR = 0x10,
    VERTEX_COLOR = 0x18,

    NORMAL_BITS = 0x6,
    PART_NORMAL = 0x2,
    FACE_NORMAL = 0x4,
    VERTEX_NORMAL = 0x6,

    TEXCOORD_BIT = 0x1
  };
  // Bit-mask, set by ::fillInCache method
  // Bits use same as above, plus one for coords and one for
  // overrides (diffuse color, material binding, transparency)

  enum {
    OVERRIDE_FROM_STATE_BIT = 0x40,
    COORD_FROM_STATE_BIT = 0x20,
    COLOR_FROM_STATE_BITS = COLOR_BITS,
    NORMAL_FROM_STATE_BITS = NORMAL_BITS,
    TEXCOORD_FROM_STATE_BIT = TEXCOORD_BIT,
    ALL_FROM_STATE_BITS = 0x7F
  };
 private:

  //
  // VertexPropertyCache also stores whether or not colors, normals and
  // texture coordinates should be indexed.  Suggestion for writing
  // rendering loops:
  //
  // To minimize loop overhead, loop unrolling is a good idea.
  // Doing two iterations per loop makes it about 20% faster.  Doing
  // three iterations per loop makes it about 28% faster (only 8%
  // more than two iterations).
  //
  // On 200MHZ machines, an unrolled-by-3 loop can do close to 5
  // million iterations per second, assuming one call per iteration
  // (e.g. one-color, unlit polygons).
  //
  unsigned char materialBinding;
  unsigned char renderCase;
  unsigned char colorIsInVP;
  SbBool transpIsInVP;
};

#endif // HIDDEN_FROM_DOC

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLVertexLine
//
//  Abstract vertex-based shape node class. All nodes derived from
//  this class are shapes that are constructed from vertices at some
//  or all of the current coordinates.  They all have vertexProperty nodes,
//  and vpCaches.
//
//////////////////////////////////////////////////////////////////////////////

class SoState;
class SoVRMLLinePropertyCache;

/**
 * @VSGEXT Abstract base class for SoVRMLIndexedLineSet.
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   This node is an abstract base class for SoVRMLIndexedLineSet.
 * 
 * @FILE_FORMAT_DEFAULT
 *   This is an abstract class. See the reference page of a derived class
 *   for the format and default values.
 *
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction,  SoCallbackAction,  SoGetBoundingBoxAction,  SoRayPickAction  @BR
 * 
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoSFNode   @TD   set_color      
 *       @TR   SoSFNode   @TD   set_coord
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFNode   @TD   color_changed      
 *       @TR   SoSFNode   @TD   coord_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLVertexLine : public SoVRMLGeometry {

  SO_NODE_ABSTRACT_HEADER(SoVRMLVertexLine);
    
 public:
  /**
   * An SoVRMLCoordinate node defining the IndexedLineSet.
   * 
   */
  SoSFNode            coord;
  /**
   * An SoVRMLColor node whose colors are applied to the vertices or lines of the
   * IndexedLineSet.
   * 
   */
  SoSFNode            color;
  /**
   * If TRUE, colors are applied to the vertices of the IndexedLineSet. If FALSE, the
   * colors are applied to the lines.
   * 
   */
  SoSFBool            colorPerVertex;


 SoINTERNAL public:

  static void         initClass();
  static void         exitClass();
  virtual void        doAction(SoAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        search(SoSearchAction *action);
  virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        pick(SoPickAction *action);

  virtual SoChildList *getChildren() const;

  virtual SbBool      validateNewFieldValue(SoField *pField,
                                            void *newValue);

  // Redefines this to invalidate normal cache
  virtual void        notify(SoNotList *list);

  // Copies the contents of the given node into this instance. The
  // default implementation copies just field values and the name.
  virtual void        copyContents(const SoFieldContainer *fromFC,
                                   SbBool copyConnections);

 protected:
#if 0
	enum Binding {
    OVERALL =               SoMaterialBindingElement::OVERALL,
    PER_PART =              SoMaterialBindingElement::PER_PART,
    PER_PART_INDEXED =      SoMaterialBindingElement::PER_PART_INDEXED,
    PER_FACE =              SoMaterialBindingElement::PER_FACE,
    PER_FACE_INDEXED =      SoMaterialBindingElement::PER_FACE_INDEXED,
    PER_VERTEX =            SoMaterialBindingElement::PER_VERTEX,
    PER_VERTEX_INDEXED =    SoMaterialBindingElement::PER_VERTEX_INDEXED
  };
#endif
  // Constructor - makes this abstract
  SoVRMLVertexLine();

  virtual ~SoVRMLVertexLine();
    
  // Returns TRUE if the shape should be rendered. 
  // Checks for transparency in vertexProperty node before invoking
  // render action.
  virtual SbBool      shouldGLRender(SoGLRenderAction *action,
                                     SbBool isPointsOrLines);

  // vpCache stores information from one render to the next about
  // what information needs to be grabbed from the state, etc.
  SoVRMLLinePropertyCache     vpCache;

  // Hack to make paths work for VRML nodes that contain other nodes
  // in their fields...  Nov-96
  SoChildList *children;
  friend class SoPath;    // Need to access "children" in SoPath::truncate()

  // Mutex to protect access to the vpCache
  SbThreadRWMutex *vpCacheMutex;

 private:
  void rebuildChildrenList();

 SoINTERNAL public:
  SoMFUInt32  orderedrgba;
  unsigned char materialBinding;

};

#endif /* _SO_VRMLVERTEX_LINE_ */

