/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : SGI (MMM YYYY)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : Julien SALLANNE (Jun 2009)
**=======================================================================*/

#ifndef  _SO_VRMLGEOELEVATIONGRID_
#define  _SO_VRMLGEOELEVATIONGRID_

#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/nodes/SoGeoProjection.h>
#include <Inventor/VRMLnodes/SoVRMLElevationGrid.h>
#include <Inventor/VRMLnodes/SoVRMLGridShape.h>

class SoVRMLTextureCoordinate;

/** 
 * @VSGEXT Specifies a uniform grid of elevation values within some spatial 
 *         reference frame.
 * 
 * @ingroup GeoVRML
 * 
 * @DESCRIPTION
 *    The SoVRMLGeoElevationGrid allows to create terrain models for local or large
 *   areas (automatically introduces correct degree of earth curvature).
 * 
 * @VRMLX3D_SPECIFICATION
 *    This section describes the expected behavior of the node in a conforming X3D / VRML97
 *   browser application. In some cases, the application is responsible for
 *   implementing portions of the expected behavior. Open Inventor viewer classes and
 *   IVF classes implement some of the application behaviors.
 *   
 *    This section may reference portions of the X3D specification that are not
 *   present in this help file. The complete X3D spec is available at
 *   @B http://www.web3d.org @b.
 * 
 *    The SoVRMLGeoElevationGrid node specifies a uniform grid of elevation values 
 *   within some spatial reference frame. These are then transparently transformed 
 *   into a geocentric, curved-earth representation. For example, this would allow 
 *   a geographer to create a height field where all coordinates are specified in 
 *   terms of latitude, longitude, and elevation.
 *   The fields #color, #colorPerVertex, #texCoord, #normal, and #normalPerVertex
 *   all have the same meaning as for ElevationGrid (see 13.3.4 ElevationGrid).
 *   The #ccw, #solid, and #creaseAngle fields are described 
 *   in 11.2.3 Common geometry fields.
 *   The #geoOrigin field is used to specify a local coordinate frame for extended 
 *   precision as described in 25.2.5 Dealing with high-precision coordinates.
 *   The #geoSystem field is used to define the spatial reference frame and is 
 *   described in 25.2.3 Specifying a spatial reference frame.
 *   The #geoGridOrigin field specifies the geographic coordinate for the south-west
 *   corner (bottom-left) of the dataset. This value should be specified as described
 *   in 25.2.4 Specifying geospatial coordinates.
 *   The #height array contains (#xDimension * #zDimension) floating point values that
 *   represent elevation above the ellipsoid or the geoid, as appropriate. These
 *   values are given in row-major order from west to east, south to north. When 
 *   the #geoSystem is "GD", #xSpacing refers to the number of degrees of longitude
 *   between adjacent height values and #zSpacing refers to the number of degrees
 *   of latitude between vertical height values. When the geoSystem is "UTM",
 *   #xSpacing refers to the number of eastings (meters) between adjacent height
 *   values and #zSpacing refers to the number of northings (meters) between
 *   vertical height values.
 *   EXAMPLE  If xDimension = n and the grid spans d units horizontally, 
 *   the xSpacing value should be set to: d / (n-1).
 *   The #yScale value can be used to produce a vertical exaggeration of the data
 *   when it is displayed. By default, this value is 1.0 (no exaggeration).
 *   If this value is set greater than 1.0, all heights will appear larger than actual.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLGeoElevationGrid {
 *    @TABLE_FILE_FORMAT
 *       @TR color            @TD NULL
 *       @TR metadata         @TD NULL
 *       @TR normal           @TD NULL
 *       @TR texCoord         @TD NULL
 *       @TR yScale           @TD 1.0
 *       @TR ccw              @TD TRUE
 *       @TR colorPerVertex   @TD TRUE
 *       @TR creaseAngle      @TD 0
 *       @TR geoGridOrigin    @TD 0 0 0
 *       @TR geoOrigin        @TD NULL
 *       @TR geoSystem        @TD ["GD","WE"]
 *       @TR height           @TD []
 *       @TR normalPerVertex  @TD TRUE
 *       @TR solid            @TD TRUE
 *       @TR xDimension       @TD 0
 *       @TR xSpacing         @TD 1.0
 *       @TR zDimension       @TD 0
 *       @TR zSpacing         @TD 1.0
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction  @BR
 * 
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoMFFloat  @TD   set_height
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
 */

class INVENTOR_API SoVRMLGeoElevationGrid : public SoVRMLElevationGrid {

  SO_NODE_HEADER(SoVRMLGeoElevationGrid);

 public:
  // Fields
  /**
   * The yScale value can be used to produce a vertical exaggeration of the data
   * when it is displayed. By default, this value is 1.0 (no exaggeration).
   * If this value is set greater than 1.0, all heights will appear larger than actual. 
   */
  SoSFFloat         yScale;

  /**
   * Specifies the geographic coordinate for the south-west
   * corner (bottom-left) of the dataset.
   */
  SoSFVec3f         geoGridOrigin;

  /**
   * Defines the spatial reference frame. @BR
   * Valid values are:
   * - GC: Earth-fixed Geocentric with respect to the WGS84 ellipsoid.
   * - GD: Geodetic spatial reference frame. @BR
   *   An optional second string may be used to specify the ellipsoid using
   *   one of the ellipsoid codes that are defined in X3D. If no ellipsoid is 
   *   specified, then "WE" is assumed (the WGS84 ellipsoid).
   * - UTM: Universal Transverse Mercator @BR
   *   One further required argument must be supplied for UTM in order to
   *   specify the zone number (1..60). This is given in the form "Z<n>", where
   *   <n> is the zone number. An optional argument of "S" may be supplied in 
   *   order to specify that the coordinates are in the southern hemisphere
   *  (otherwise, northern hemisphere will be assumed).
   */
  SoMFString        geoSystem;

  /**
   * An SoVRMLGeoOrigin node specifying the origin of the local coordinate system.
   */
  SoSFNode           geoOrigin;

  /**
   * Constructor.
   */
  SoVRMLGeoElevationGrid();

 SoEXTENDER public:
  // Implements actions
  virtual void        GLRender(SoGLRenderAction *action);


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
  typedef void (SoVRMLGeoElevationGrid::*PMFS)(SoGLRenderAction *);
                                                  
 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  // This enum is used to indicate the current material or normal binding
  enum Binding {
    OVERALL, PER_ROW, PER_QUAD, PER_VERTEX
  };
  void                setupCoordinates(SoAction *action, SoVRMLCoordinate *myCoord, SoVRMLTextureCoordinate *myTexCoord);
  // Generates triangles representing faces
  virtual void        generatePrimitives(SoAction *action);

  // Per-instance mutex to protect access to the normalCache
  SbThreadRWMutex *normalCacheMutex;

  // Per-instance mutex to protect access to the vpCache
  SbThreadRWMutex *vpCacheMutex;

  ~SoVRMLGeoElevationGrid();

 private:
   SoVRMLTextureCoordinate     *myTexCoord;

   float computeHeight(int index);

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

#endif /* _SO_VRMLGEOELEVATIONGRID_ */
