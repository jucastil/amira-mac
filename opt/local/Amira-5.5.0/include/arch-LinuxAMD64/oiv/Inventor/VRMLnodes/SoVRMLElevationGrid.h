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


#ifndef  _SO_VRMLELEVATION_GRID_
#define  _SO_VRMLELEVATION_GRID_

#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/VRMLnodes/SoVRMLGridShape.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLElevationGrid
//
//  Creates a rectangular grid of varying height useful in modeling
//  terrain.
//
//////////////////////////////////////////////////////////////////////////////

class SoNormalBundle;
class SoCoordinateElement;
class SoShapeStyleElement;

/**
 * @VSGEXT Specifies a uniform rectangular grid of varying height in the XZ plane.
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   See the VRML97 Specification, below.
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
 *   The SoVRMLElevationGrid node specifies a uniform rectangular grid of varying
 *   height in the XZ plane of the local coordinate system. The geometry is described
 *   by a scalar array of height values that specify the height of a rectangular
 *   surface above each point of the grid. 
 *   
 *   The @B xDimension @b and @B zDimension @b fields indicate the number of
 *   divisions of the grid @B height @b array in the X and Z directions. Both
 *   @B xDimension @b and @B zDimension @b must be > 1. The vertex locations for
 *   the rectangles are defined by the @B height @b field and the @B xSpacing @b
 *   and @B zSpacing @b fields: 
 *   
 *   - The @B height @b field is an @B xDimension @b by @B zDimension @b array of
 *   scalar values representing the height above the grid for each vertex the height
 *   values are stored in row major order. 
 *   
 *   - The @B xSpacing @b and @B zSpacing @b fields indicates the distance between
 *   vertices in the X and Z directions respectively, and must be >= 0. 
 *   
 *   Thus, the vertex corresponding to the point, P[@I i, @i j], on the grid is
 *   placed at:
 *   
 *   <PRE>
 *    P[i,j].x = @I xSpacing @i * i 
 *    P[i,j].y = @I height @i[ i + j * @I zDimension @i] 
 *    P[i,j].z = @I zSpacing @i * j
 *    </PRE>
 *    where 0<i<@I xDimension @i and 0<j<@I zDimension @i. 
 *   
 *   The @B set_height @b eventIn allows the height MFFloat field to be changed to
 *   allow animated SoVRMLElevationGrids.
 *   
 *   The default texture coordinates range from [0,0] at the first vertex to [1,1] at
 *   the last vertex. The S texture coordinate will be aligned with X, and the T
 *   texture coordinate with Z. 
 *   
 *   The @B colorPerVertex @b field determines whether colors (if specified in the
 *   color field) should be applied to each vertex or each quadrilateral of the
 *   SoVRMLElevationGrid. If @B colorPerVertex @b is FALSE and the @B color @b
 *   field is not NULL, then the @B color @b field must contain a Color node
 *   containing at least (@B xDimension-1) @b*(@B zDimension-1) @b colors. If
 *   @B colorPerVertex @b is TRUE and the @B color @b field is not NULL, then the
 *   @B color @b field must contain a Color node containing at least
 *   @B xDimension @b*@B zDimension @b colors. 
 *   
 *   See the "Concepts - Geometry" for a description of the #ccw, #solid,
 *   and #creaseAngle fields. 
 *   
 *   By default, the rectangles are defined with a counterclockwise ordering, so the Y
 *   component of the normal is positive. Setting the #ccw field to FALSE
 *   reverses the normal direction. Backface culling is enabled when the #ccw
 *   field and the #solid field are both TRUE (the default).
 *
 *   NOTE: An elevation grid may not render or pick correctly if any of its polygons
 *   are self-intersecting or non-planar.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLElevationGrid {
 *    @TABLE_FILE_FORMAT
 *       @TR color             @TD NULL
 *       @TR normal            @TD NULL
 *       @TR texCoord          @TD NULL
 *       @TR height            @TD []
 *       @TR ccw               @TD TRUE
 *       @TR colorPerVertex    @TD TRUE
 *       @TR creaseAngle       @TD 0
 *       @TR normalPerVertex   @TD TRUE
 *       @TR solid             @TD TRUE
 *       @TR xDimension        @TD 0
 *       @TR xSpacing          @TD 0.0
 *       @TR zDimension        @TD 0
 *       @TR zSpacing          @TD 0.0
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
 *       @TR   SoMFFloat   @TD   set_height      
 *       @TR   SoSFNode   @TD   set_color      
 *       @TR   SoSFNode   @TD   set_normal      
 *       @TR   SoSFNode   @TD   set_texCoord
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFNode   @TD   color_changed      
 *       @TR   SoSFNode   @TD   normal_changed      
 *       @TR   SoSFNode   @TD   texCoord_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLElevationGrid : public SoVRMLGridShape {

  SO_NODE_HEADER(SoVRMLElevationGrid);

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
   * @FIELD_SINCE_OIV 5.0
   *
   * @B NOTE 2:@b This field is not compatible with VRML97.
   * If you specify a non-default value for this field, when 
   * this node is written to a VRML file, the file will contain
   * this incompatible field and standard VRML97 file readers 
   * will not be able to read it.
   */
  SoSFBool            solid;
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
  SoVRMLElevationGrid();

 SoEXTENDER public:
  // Implements actions
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        generatePick(SoRayPickAction *action, SoNode *node);
  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);


  // Generates default normals using the given normal bundle. 
  // Returns TRUE.
  virtual SbBool      generateDefaultNormals(SoState *state,
                                             SoNormalBundle *nb);
  // This handles bounding box computation for all shapes derived
  // from this class. It sets the bounding box to contain all
  // vertices of the shape, assuming that the shape uses the
  // coordinates indexed by all non-negative values in the
  // coordIndex field. It also sets the center to the average of the
  // vertices' coordinates.
  virtual void        computeBBox(SoAction *action, SbBox3f &box,
                                  SbVec3f &center);

  // Typedef of pointer to method on IndexedFaceSet;
  // This will be used to simplify declaration and initialization.
  typedef void (SoVRMLElevationGrid::*PMFS)(SoGLRenderAction *);
                                                  
 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  // This enum is used to indicate the current material or normal binding
  enum Binding {
    OVERALL, PER_ROW, PER_QUAD, PER_VERTEX
  };
  void                setupCoordinates(SoVRMLCoordinate *myCoord);
  // Generates triangles representing faces
  virtual void        generatePrimitives(SoAction *action);

  // Per-instance mutex to protect access to the normalCache
  SbThreadRWMutex *normalCacheMutex;

  // Per-instance mutex to protect access to the vpCache
  SbThreadRWMutex *vpCacheMutex;

  // Overrides standard method to create an SoFaceDetail instance
  virtual SoDetail *  createTriangleDetail(SoRayPickAction *action,
                                           const SoPrimitiveVertex *v1,
                                           const SoPrimitiveVertex *v2,
                                           const SoPrimitiveVertex *v3,
                                           SoPickedPoint *pp);
  ~SoVRMLElevationGrid();

 private:
  SbVec3f             *generatedNormals;      // Array of generated normals
  void doRendering(SoGLRenderAction *action, const SoShapeStyleElement* shapeStyle);

  // Saves normal binding when generating primitives for picking
  Binding             savedNormalBinding;

  // Returns current material or normal binding from action's state
  Binding getMaterialBinding() const;
  Binding getNormalBinding(SoAction* action, SoNormalBundle* nb);

  // Returns index (of material or normal) based on given binding
  static int          getBindIndex(Binding binding, int vert,
                                   int row, int quad);

  // Figures out normals, if necessary.
  SbBool              figureNormals(SoState *state, SoNormalBundle *nb);

  // set numTris/Quads/Faces to -1 when notified
  //virtual void      notify(SoNotList *list);

  // This stores the total number of vertices; we use this
  // information to influence Separator's auto-caching algorithm
  // (shapes with very few triangles should be cached because
  // traversing them can be expensive, shapes with lots of triangles
  // shouldn't be cached because they'll take up too much memory).
    
  // Number of quads 
  int     numQuads, totalNumVertices;
    
  // Set number of triangles/quads/faces, based on coordIndex array.
  void setupNumTrisQuadsFaces();
 
  // This stores the total number of vertices; we use this
  // information to influence Separator's auto-caching algorithm
  // (shapes with very few triangles should be cached because
  // traversing them can be expensive, shapes with lots of triangles
  // shouldn't be cached because they'll take up too much memory).
  SbBool genNorms;

  static const int AUTO_CACHE_MIN_WITHOUT_VP;
  static const int AUTO_CACHE_MAX;

};

#endif /* _SO_VRMLELEVATION_GRID_ */

