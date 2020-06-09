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


#ifndef  _SO_VRMLGEOMETRY_
#define  _SO_VRMLGEOMETRY_

#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/SbColor.h>
#include <Inventor/elements/SoTextureCoordinateBindingElement.h>
#include <Inventor/elements/SoMaterialBindingElement.h>
#include <Inventor/elements/SoNormalBindingElement.h>

class SoColorPacker;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLGeometry
//
//  Abstract base shape node class, which provides some convenience
//  functions for its subclasses.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Abstract base class for all VRML97 and X3D geometry nodes.
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   The SoVRMLGeometry node is the abstract base class for all VRML geometry nodes.
 *
 * @FILE_FORMAT_DEFAULT
 *   This is an abstract class. See the reference page of a derived class for the
 *   format and default values.
 * 
 * @ACTION_BEHAVIOR
 *      SoRayPickAction  @BR 
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 *
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 *
 * 
 */ 

class INVENTOR_API SoVRMLGeometry : public SoShape {

  SO_NODE_ABSTRACT_HEADER(SoVRMLGeometry);

 public:
  // Fields

  /**
   * Specifies the metadata node
   * 
   */
  SoSFNode            metadata;

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 SoEXTENDER public:
  virtual void        generatePick(SoRayPickAction *action, SoNode *);

  // This can be used by subclasses when the complexity type is
  // SCREEN_SPACE to determine how many window pixels are covered by
  // the shape. It returns in rectSize the number of pixels in the
  // window rectangle that covers the given 3D bounding box.
  static void         getScreenSize(SoState *state,
                                    const SbBox3f &boundingBox,
                                    SbVec2s &rectSize);

  SbBool              isTransparent() {return transparent;}

 protected:
  // Constructor
  SoVRMLGeometry();

  SoColorPacker *colorPacker;

  SbBool  transparent;

  // Returns TRUE if the shape should be rendered. Subclasses can
  // call this in their rendering methods to determine whether to
  // continue.
  virtual SbBool      shouldGLRender(SoGLRenderAction *action,
                                     SbBool isPointsOrLines = FALSE);

  virtual ~SoVRMLGeometry();
    
   void        setupForTexture(SoAction *action);

  // Temporary storage during traversal
  static SbColor   *white_color; 
  static SoMFFloat *transp_1;

  // Count instances so we can cleanup temporary storage
  static int instanceCounter;


  // below are variables related to auto caching
  static int autoCacheMinValue;
  static int autoCacheMaxValue;

  // Count instances so we can cleanup temporary storage
  // static int instanceCounter;

  // This variable indicates if we use the full modulate mode like in OpenInventor.
  static SbBool s_textureModelSupport;
};
#ifndef HIDDEN_FROM_DOC
#include <Inventor/elements/SoShapeStyleElement.h>
typedef WINGDIAPI void APIENTRY SoVPCacheFunc(const char *const);

/**
 * [OIV-WRAPPER-NO-WRAP]
 */
SoEXTENDER class INVENTOR_API SoVRMLVertexPropertyCache {
 public:

  // API used by shapes:

  SbBool mightNeedSomethingFromState(const SoShapeStyleElement *sse) const
    { return needFromState & sse->getRenderCaseMask(); }

  void        fillInCache(SoNode *, SoNode *, SoNode *, 
                          SoNode *, SoNode *,const int32_t *, 
                          const int32_t *,const int32_t *,const int32_t *, 
                          SbBool , SbBool ,  SoState *);

  SbBool      shouldGenerateNormals(const SoShapeStyleElement *sse) const
    { return (generateNormals && sse->needNormals()); }

  SbBool      shouldGenerateTexCoords(const SoShapeStyleElement *sse) const
    { return (generateTexCoords && sse->needTexCoords()); }

  int         getRenderCase(const SoShapeStyleElement *sse) const
    { return renderCase & sse->getRenderCaseMask(); }

  SbBool      haveTexCoordsInVP()
    { return needFromState & TEXTURE_FUNCTION_BIT; }

  void        sendVertex(const char *vp) const
    { (*vertexFunc)(vp); }
  void        sendNormal(const char *np) const
    { (*normalFunc)(np); }
  void        sendColor(const char *cp) const
    { (*colorFunc)(cp); }
  void        sendTexCoord(const char *tcp) const
    { (*texCoordFunc)(tcp); }

  int         getNumVertices() const { return numVerts; }
  int         getNumNormals() const { return numNorms; }
  int         getNumColors() const { return numColors; }
  int         getNumTexCoords() const { return numTexCoords; }

  const char *getVertices(int i) const
    { return vertexPtr + vertexStride*i; }
  const char *getNormals(int i) const
    { return normalPtr + normalStride*i; }
  const char *getColors(int i) const
    { return colorPtr + colorStride*i; }
  const char *getTexCoords(int i) const
    { return texCoordPtr + texCoordStride*i; }

  SbBool colorIsInVtxProp() const {return colorIsInVP;}

  //Indicates if non-opaque transparency is in vertex property.
  SbBool transpIsInVtxProp() const {return transpIsInVP;}

  void setTranspIsInVP(SbBool flag){ transpIsInVP = flag;}

  int         getVertexStride() const { return vertexStride; }
  int         getNormalStride() const { return normalStride; }
  int         getColorStride() const { return colorStride; }
  int         getTexCoordStride() const { return texCoordStride; }

  SoNormalBindingElement::Binding     getNormalBinding()
    { return (SoNormalBindingElement::Binding)normalBinding; }

  SoMaterialBindingElement::Binding   getMaterialBinding()
    { return (SoMaterialBindingElement::Binding)materialBinding; }


  SoTextureCoordinateBindingElement::Binding  getTexCoordBinding()
    { return (SoTextureCoordinateBindingElement::Binding)texCoordBinding; }

  void        invalidate() { needFromState = ALL_FROM_STATE_BITS; }

  // Constructor.   Initializes everything.
  SoVRMLVertexPropertyCache();

 public:

  // Tables of functions, data, and strides to increment through data.
  SoVPCacheFunc *vertexFunc;
  const char *vertexPtr;
  int vertexStride, numVerts;
  SoVPCacheFunc *normalFunc;
  const char *normalPtr;
  int normalStride, numNorms;
  SoVPCacheFunc *colorFunc;
  const char *colorPtr;
  int colorStride, numColors;
  SoVPCacheFunc *texCoordFunc;
  const char *texCoordPtr;
  int texCoordStride, numTexCoords;

  SbBool generateNormals;
  SbBool generateTexCoords;

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
    TEXTURE_FUNCTION_BIT = 0x80,
    OVERRIDE_FROM_STATE_BIT = 0x40,
    COORD_FROM_STATE_BIT = 0x20,
    COLOR_FROM_STATE_BITS = COLOR_BITS,
    NORMAL_FROM_STATE_BITS = NORMAL_BITS,
    TEXCOORD_FROM_STATE_BIT = TEXCOORD_BIT,
    ALL_FROM_STATE_BITS = 0xFF
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
  unsigned char normalBinding;
  unsigned char materialBinding;
  unsigned char texCoordBinding;
  unsigned char renderCase;
  unsigned char colorIsInVP;
  SbBool transpIsInVP;
};
#endif // HIDDEN_FROM_DOC

#endif /* _SO_VRMLGEOMETRY_ */

