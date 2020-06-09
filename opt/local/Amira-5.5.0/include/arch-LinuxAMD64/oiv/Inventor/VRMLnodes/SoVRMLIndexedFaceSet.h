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


#ifndef  _SO_VRMLINDEXED_FACE_SET_
#define  _SO_VRMLINDEXED_FACE_SET_

#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/SbColor.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/VRMLnodes/SoVRMLIndexedShape.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLIndexedFaceSet
//
//  Indexed set of faces. Each face consists of 3 or more vertices,
//  each of which is denoted by an integer index (from the coordIndex
//  field) into the current coordinates. Depending on the current
//  material and normal binding values, the materials and normals for
//  the faces or vertices may be accessed in order or indexed. If they
//  are indexed, the colorIndex and normalIndex fields are used.
//
//////////////////////////////////////////////////////////////////////////////

// This coordinate index indicates that the current face ends and the
// next face begins
#define SO_END_FACE_INDEX       (-1)

class SoNormalBundle;
class SoCoordinateElement;
class SoShapeStyleElement;

/**
 * @VSGEXT Indexed polygonal face shape node.
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   See the VRML97 Specification, below.
 * 
 *   OpenGL vertex arrays are used
 *     - if they are available, @I and@i
 *     - the environment variable IV_NO_VERTEX_ARRAY is not set, @I and@i
 *     - the #colorIndex, #normalIndex, and #textureCoordIndex fields
 *       are exactly identical to the #coordIndex field, or are set to
 *       their default value (i.e., -1).
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
 *   The SoVRMLIndexedFaceSet node represents a 3D shape formed by constructing faces
 *   (polygons) from vertices listed in the @B coord @b field. The @B coord @b
 *   field must contain an SoVRMLCoordinate node. SoVRMLIndexedFaceSet uses the
 *   indices in its #coordIndex field to specify the polygonal faces. An index
 *   of -1 indicates that the current face has ended and the next one begins. The
 *   last face may (but does not have to be) followed by a -1. If the greatest index
 *   in the #coordIndex field is N, then the SoVRMLCoordinate node must contain
 *   N+1 coordinates (indexed as 0-N). SoVRMLIndexedFaceSet is specified in the local
 *   coordinate system and is affected by parent transformations.
 *   
 *   For descriptions of the @B coord @b, @B normal @b, and @B texCoord @b fields,
 *   see the SoVRMLCoordinate, SoVRMLNormal, and SoVRMLTextureCoordinate nodes.
 *   
 *   See "Concepts - Lighting Model" for details on lighting equations and the
 *   interaction between textures, materials, and geometries.
 *   
 *   If the color field is not NULL then it must contain an SoVRMLColor node, whose
 *   colors are applied to the vertices or faces of the SoVRMLIndexedFaceSet as
 *   follows: 
 *   
 *   - If @B colorPerVertex @b is FALSE, colors are applied to each face, as follows:
 *   
 *   - If the @B colorIndex @b field is not empty, then they are used to choose one
 *   color for each face of the SoVRMLIndexedFaceSet. There must be at least as many
 *   indices in the @B colorIndex @b field as there are faces in the
 *   SoVRMLIndexedFaceSet. If the greatest index in the @B colorIndex @b field is N,
 *   then there must be N+1 colors in the SoVRMLColor node. The @B colorIndex @b
 *   field must not contain any negative entries. 
 *   
 *   - If the @B colorIndex @b field is empty, then the colors are applied to each
 *   face of the SoVRMLIndexedFaceSet in order. There must be at least as many colors
 *   in the SoVRMLColor node as there are faces. 
 *   
 *   - If @B colorPerVertex @b is TRUE, colors are applied to each vertex, as
 *   follows: 
 *   
 *   - If the @B colorIndex @b field is not empty, then it is used to choose colors
 *   for each vertex of the SoVRMLIndexedFaceSet in exactly the same manner that the
 *   #coordIndex field is used to choose coordinates for each vertex from the
 *   SoVRMLCoordinate node. The @B colorIndex @b field must contain at least as many
 *   indices as the #coordIndex field, and must contain end-of-face markers
 *   (-1) in exactly the same places as the #coordIndex field. If the greatest
 *   index in the @B colorIndex @b field is N, then there must be N+1 colors in the
 *   SoVRMLColor node. 
 *   
 *   - If the @B colorIndex @b field is empty, then the #coordIndex field is
 *   used to choose colors from the SoVRMLColor node. If the greatest index in the
 *   #coordIndex field is N, then there must be N+1 colors in the SoVRMLColor
 *   node. 
 *   
 *   If the @B normal @b field is NULL, then the browser should automatically
 *   generate normals, using #creaseAngle to determine if and how normals are
 *   smoothed across shared vertices.
 *   
 *   If the @B normal @b field is not NULL, then it must contain an SoVRMLNormal
 *   node, whose normals are applied to the vertices or faces of the
 *   SoVRMLIndexedFaceSet in a manner exactly equivalent to that described above for
 *   applying colors to vertices/faces. 
 *   
 *   If the @B texCoord @b field is not NULL, then it must contain an
 *   SoVRMLTextureCoordinate node. The texture coordinates in that node are applied
 *   to the vertices of the SoVRMLIndexedFaceSet as follows: 
 *   
 *   - If the @B texCoordIndex @b field is not empty, then it is used to choose
 *   texture coordinates for each vertex of the SoVRMLIndexedFaceSet in exactly the
 *   same manner that the #coordIndex field is used to choose coordinates for
 *   each vertex from the SoVRMLCoordinate node. The @B texCoordIndex @b field must
 *   contain at least as many indices as the #coordIndex field, and must
 *   contain end-of-face markers (-1) in exactly the same places as the
 *   #coordIndex field. If the greatest index in the @B texCoordIndex @b field
 *   is N, then there must be N+1 texture coordinates in the SoVRMLTextureCoordinate
 *   node. 
 *   
 *   - If the @B texCoordIndex @b field is empty, then the #coordIndex array is
 *   used to choose texture coordinates from the SoVRMLTextureCoordinate node. If the
 *   greatest index in the #coordIndex field is N, then there must be N+1
 *   texture coordinates in the SoVRMLTextureCoordinate node. 
 *   
 *   If the @B texCoord @b field is NULL, a default texture coordinate mapping is
 *   calculated using the bounding box of the shape. The longest dimension of the
 *   bounding box defines the S coordinates, and the next longest defines the T
 *   coordinates. If two or all three dimensions of the bounding box are equal, then
 *   ties should be broken by choosing the X, Y, or Z dimension in that order of
 *   preference. The value of the S coordinate ranges from 0 to 1, from one end of
 *   the bounding box to the other. The T coordinate ranges between 0 and the ratio
 *   of the second greatest dimension of the bounding box to the greatest dimension.
 *   See the figure below for an illustration of default texture coordinates for a
 *   simple box shaped SoVRMLIndexedFaceSet with a bounding box with X dimension
 *   twice as large as the Z dimension which is twice as large as the Y dimension:
 *   
 *   @IMAGE ifstext11.gif 
 *   
 *   
 *   @IMAGE ifstext21.gif 
 *   
 *   See the introductory "Concepts - Geometry" section for a description of the
 *   #ccw, #solid, #convex, and #creaseAngle fields. 
 *   
 *   NOTE: An indexed face set may not render or pick correctly if any of its polygons
 *   are self-intersecting or non-planar.
 *
 * @FILE_FORMAT_DEFAULT
 *    VRMLIndexedFaceSet {
 *    @TABLE_FILE_FORMAT
 *       @TR color             @TD NULL
 *       @TR coord             @TD NULL
 *       @TR normal            @TD NULL
 *       @TR texCoord          @TD NULL
 *       @TR ccw               @TD TRUE
 *       @TR colorIndex        @TD []
 *       @TR colorPerVertex    @TD TRUE
 *       @TR convex            @TD TRUE
 *       @TR coordIndex        @TD []
 *       @TR creaseAngle       @TD 0
 *       @TR normalIndex       @TD []
 *       @TR normalPerVertex   @TD TRUE
 *       @TR solid             @TD TRUE
 *       @TR texCoordIndex     @TD []
 *       @TR metadata     @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction,  SoRayPickAction,  SoGetBoundingBoxAction,  SoCallbackAction  @BR
 * 
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoMFint32   @TD   set_colorIndex      
 *       @TR   SoMFint32   @TD   set_coordIndex      
 *       @TR   SoMFint32   @TD   set_normalIndex      
 *       @TR   SoMFint32   @TD   set_texCoordIndex      
 *       @TR   SoSFNode   @TD   set_color      
 *       @TR   SoSFNode   @TD   set_coord      
 *       @TR   SoSFNode   @TD   set_normal      
 *       @TR   SoSFNode   @TD   set_texCoord
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFNode   @TD   color_changed      
 *       @TR   SoSFNode   @TD   coord_changed      
 *       @TR   SoSFNode   @TD   normal_changed      
 *       @TR   SoSFNode   @TD   texCoord_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLIndexedFaceSet : public SoVRMLIndexedShape {

  SO_NODE_HEADER(SoVRMLIndexedFaceSet);

 public:
  // Fields

  /**
   * Indicates whether the vertices are ordered in a counterclockwise direction when
   * viewed from the outside (TRUE) or in a clockwise direction (FALSE).
   * 
   */
  SoSFBool            ccw;
  /**
   * If you know that the shape encloses a volume, set this value to TRUE. 
   * Then backface culling will be performed. 
   * 
   */
  SoSFBool            solid;
  /**
   * Indicates whether faces of a shape are convex (TRUE). If nothing is known about
   * the faces, set this value to FALSE.
   * 
   */
  SoSFBool            convex;
  /**
   * Indicates the minimum angle (in radians) between two adjacent face normals
   * required to form a sharp crease at the edge when default normals are computed
   * and used.
   * 
   */
  SoSFFloat           creaseAngle;

  /**
   * Constructor.
   */
  SoVRMLIndexedFaceSet();

 SoEXTENDER public:
  // Implements actions
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        generatePick(SoRayPickAction *action, SoNode *node);
  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);


  // Generates default normals using the given normal bundle.
  // Returns TRUE.
  virtual SbBool      generateDefaultNormals(SoState *state,
                                             SoNormalBundle *nb);

  // Typedef of pointer to method on IndexedFaceSet;
  // This will be used to simplify declaration and initialization.
  typedef void (SoVRMLIndexedFaceSet::*PMFS)(SoGLRenderAction *);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();
 
 protected:
    // This enum is used to indicate the current material or normal binding
	enum Binding {
    OVERALL, PER_FACE, PER_FACE_INDEXED, PER_VERTEX,
    PER_VERTEX_INDEXED
  };
  // Generates triangles representing faces
  virtual void        generatePrimitives(SoAction *action);

  // Overrides standard method to create an SoFaceDetail instance
  virtual SoDetail *  createTriangleDetail(SoRayPickAction *action,
                                           const SoPrimitiveVertex *v1,
                                           const SoPrimitiveVertex *v2,
                                           const SoPrimitiveVertex *v3,
                                           SoPickedPoint *pp);
  ~SoVRMLIndexedFaceSet();

 private:
  // Saves normal binding when generating primitives for picking
  Binding             savedNormalBinding;

  // Returns current material or normal binding from action's state
  static Binding getMaterialBinding(SoAction *action);
  Binding getNormalBinding(SoAction *action, SoNormalBundle *nb);

  // Figures out normals, if necessary. Returns TRUE if normals were
  // generated
  SbBool              figureNormals(SoState *state, SoNormalBundle *nb);

  // set numTris/Quads/Faces to -1 when notified
  virtual void        notify(SoNotList *list);

  // Set number of triangles/quads/faces, based on coordIndex array.
  void setupNumTrisQuadsFaces();

  // Number of triangles, quads, (n>4)-vertex faces
  int     numTris, numQuads, numFaces;

  // 18*3ferent render functions; names are formed like this:
  // Om -- overall material
  // Fm -- per face material Vm -- per vertex material
  // On -- overall normal
  // Fn -- per face normal   Vm -- per vertex normal
  // T  -- per vertex texture coordinates
  void TriOmOn(SoGLRenderAction *); void TriOmOnT(SoGLRenderAction *);
  void TriOmFn(SoGLRenderAction *); void TriOmFnT(SoGLRenderAction *);
  void TriOmVn(SoGLRenderAction *); void TriOmVnT(SoGLRenderAction *);
  void TriFmOn(SoGLRenderAction *); void TriFmOnT(SoGLRenderAction *);
  void TriFmFn(SoGLRenderAction *); void TriFmFnT(SoGLRenderAction *);
  void TriFmVn(SoGLRenderAction *); void TriFmVnT(SoGLRenderAction *);
  void TriVmOn(SoGLRenderAction *); void TriVmOnT(SoGLRenderAction *);
  void TriVmFn(SoGLRenderAction *); void TriVmFnT(SoGLRenderAction *);
  void TriVmVn(SoGLRenderAction *); void TriVmVnT(SoGLRenderAction *);
  void QuadOmOn(SoGLRenderAction *);void QuadOmOnT(SoGLRenderAction *);
  void QuadOmFn(SoGLRenderAction *); void QuadOmFnT(SoGLRenderAction *);
  void QuadOmVn(SoGLRenderAction *); void QuadOmVnT(SoGLRenderAction *);
  void QuadFmOn(SoGLRenderAction *); void QuadFmOnT(SoGLRenderAction *);
  void QuadFmFn(SoGLRenderAction *); void QuadFmFnT(SoGLRenderAction *);
  void QuadFmVn(SoGLRenderAction *); void QuadFmVnT(SoGLRenderAction *);
  void QuadVmOn(SoGLRenderAction *); void QuadVmOnT(SoGLRenderAction *);
  void QuadVmFn(SoGLRenderAction *); void QuadVmFnT(SoGLRenderAction *);
  void QuadVmVn(SoGLRenderAction *); void QuadVmVnT(SoGLRenderAction *);
  void GenOmOn(SoGLRenderAction *); void GenOmOnT(SoGLRenderAction *);
  void GenOmFn(SoGLRenderAction *); void GenOmFnT(SoGLRenderAction *);
  void GenOmVn(SoGLRenderAction *); void GenOmVnT(SoGLRenderAction *);
  void GenFmOn(SoGLRenderAction *); void GenFmOnT(SoGLRenderAction *);
  void GenFmFn(SoGLRenderAction *); void GenFmFnT(SoGLRenderAction *);
  void GenFmVn(SoGLRenderAction *); void GenFmVnT(SoGLRenderAction *);
  void GenVmOn(SoGLRenderAction *); void GenVmOnT(SoGLRenderAction *);
  void GenVmFn(SoGLRenderAction *); void GenVmFnT(SoGLRenderAction *);
  void GenVmVn(SoGLRenderAction *); void GenVmVnT(SoGLRenderAction *);

  // Array of function pointers to render functions:
  static PMFS TriRenderFunc[32];
  static PMFS QuadRenderFunc[32];
  static PMFS GenRenderFunc[32];

  static const int AUTO_CACHE_MIN_WITHOUT_VP;
  static const int AUTO_CACHE_MAX;

 private:
  int va_normal_cache;
  int va_flag_normal;
  char *va_normalArray;
  int va_normalArray_size;

  int va_texCoord_cache;
  int va_flag_texCoord;
  char *va_texCoordArray;
  int va_texCoordArray_size;

  int va_color_cache;
  int va_flag_color;
  char *va_color1Array;
  int va_color1Array_size;
  char *va_color2Array;
  int va_color2Array_size;

  static int *va_array1;
  static int va_array1_size;

  void vaCheckTexCoord();
  void vaCheckNormal();
  void vaCheckTexCoord_Normal();
  void vaCheckColor();
  void vaCheckTexCoord_Color();
  void vaCheckNormal_Color();
  void vaCheckTexCoord_Normal_Color();
  typedef void (SoVRMLIndexedFaceSet::*va_PMFS)();
  static va_PMFS va_RenderFunc[32];
};

#endif /* _SO_VRMLINDEXED_FACE_SET_ */

