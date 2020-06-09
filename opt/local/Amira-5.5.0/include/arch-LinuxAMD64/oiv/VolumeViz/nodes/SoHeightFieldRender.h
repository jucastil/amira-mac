/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_HEIGHTFIELD_RENDER_H
#define  _SO_HEIGHTFIELD_RENDER_H

#ifdef _WIN32
#pragma warning( push )
#pragma warning(disable:4251)
#endif

#include <Inventor/SbBox.h>
#include <Inventor/STL/vector>
#include <Inventor/STL/pair>

#include <LDM/SoLDMTileID.h>

#include <VolumeViz/nodes/SoSlice.h>

class SoVolumeStateHeightField;
class SoGLVBOCache;
class SoFrameBufferObject;
class SoShaderProgram;
class SoLDMTextureCache;
class SoHeightFieldDetail;
class SoPerfCounter;

/**
 *
 * @VREXT Heightfield rendering node.
 *
 * @ingroup VolumeVizNodes
 *
 * @DESCRIPTION
 * SoHeightFieldRender displays a uniform grid in the XY plane whose vertices are
 * height (Z) values stored in 2D LDM format (any LDM data set with the Z dimension
 * equal to 1).  Storing only height values is a very efficient way to represent a
 * surface and LDM supports 8 and 16 bit integer data in addition to float (and other
 * types). Adding the combination of LDM data management with advanced GPU features
 * provides a way to handle extremely large surfaces. Just as with volume data, LDM
 * uses tiles of data and multiple levels of resolution to enable interactive frame
 * rates even for data sets that cannot fit in system memory. Using an advanced GPU
 * feature called a "geometry shader", SoHeightFieldRender generates triangles for
 * the surface on the graphics board, so no additional system memory is needed for
 * the triangle representation.
 *
 * This node is used similar to SoVolumeRender, but instead of an SoVolumeData node,
 * you use an SoHeightFieldGeometry for the data set (height values) and one or more
 * SoHeightFieldProperty nodes for property data sets. Generally it obeys the same
 * rules regarding multiple data sets (see SoMultiDataSeparator).
 *
 * Data set values are converted to height values in 3D space in two ways depending
 * on the data type:
 * - Integer values are normalized between [0,1]  ([-1,1] for signed types)
 *   based on the range of values for the specific data type.  For example, for
 *   UNSIGNED BYTE values the range 0..255 is mapped to 0..1.
 * - Floating point values are not normalized (are used "as is").
 *
 * Any grid vertices whose value is equal to the "undefined" value will be rendered
 * as holes in the grid. The undefined value can be specified during the LDM conversion
 * using the "-u" option to the LDM converter:
 * <PRE>
 *    convert -u 127 -b 1 inputFile.lst
 * </PRE>
 * Or by setting the SoHeightFieldGeometry::undefinedValue field of SoHeightFieldGeometry node.
 * The default value is NaN (Not a Number).
 *
 *      @TABLE_1B
 *         @TR @IMAGE horizon.jpg
 *         @TR A lighted heightfield
 *      @TABLE_END
 *
 * The number triangles used for rendering can be limited using the SoLDMResourceParameters
 * maxNumTriangles field and the SoLDMGlobalResourceParameters::setMaxNumTriangles() method.
 * Limiting the number of triangles may force the use of lower resolution data tiles.
 * The default value (0) allows any number of triangles to be used.
 *
 * VolumeViz provides default shaders that conveniently color the surface using a single
 * property, as shown in the images. However it is also possible to combine multiple
 * properties using a custom shader program, in the same way that you would combine multiple
 * volumes.
 *
 * Multidata rules apply to the creation of a scene graph using a SoHeightFieldRender
 * (see SoMultiDataSeparator). A minimal scene graph displaying a heightfield is:
 * \oivnetdoc
 *   \code
 *   SoMultiDataSeparator mds = new SoMultiDataSeparator();
 *   mds.AddChild( transferFunction );
 *   mds.AddChild( heightFieldProperty );
 *   mds.AddChild( heightFieldGeometry );
 *   mds.AddChild( heightFieldRender );
 *   \endcode
 * \else
 *   \code
 *   SoMultiDataSeparator* mds = new SoMultiDataSeparator;
 *   mds->addChild( transferFunction );
 *   mds->addChild( heightFieldProperty );
 *   mds->addChild( heightFieldGeometry );
 *   mds->addChild( heightFieldRender );
 *   \endcode
 * \endoivnetdoc
 *
 * When used with an SoVolumeShader, a new shader function is available to compute
 * lighting:
 *  - @I@B vec4 VVizComputeFrontColor(vec3 normal, vec4 color))@b@i:
 *   Add lighting to the color @I col@i.
 *
 * The following shader code code will light a heightfield:
 * \code
 * vec4 VVizComputeVolumeRendering(float sf);
 * float VVizCombineData(vec2 tcoord);
 * vec3 VVizComputeCoordinates(const vec3);
 * void VVizOutputColor(vec4 color);
 * vec4 VVizComputeFrontColor(vec3 n, vec4 col);
 * vec3 VVizComputeGradient(vec3 tcoord);
 *
 * void main()
 * {
 *   vec3 tCoord0 = VVizComputeCoordinates(gl_TexCoord[0].xyz);
 *   vec3 grad = VVizComputeGradient(tCoord0);
 *   vec3 normal = normalize(gl_NormalMatrix*grad);
 *
 *   float sf = VVizCombineData(tCoord0.xy);
 *   vec4 col = VVizComputeVolumeRendering(sf);
 *
 *   col = VVizComputeFrontColor(normal, col);*
 *   VVizOutputColor(col);
 * }\endcode
 *
 * @B Limitations: @b
 * @UL
 *  @LI Only graphics cards that support the OpenGL Geometry Shader feature
 *      (GL_EXT_geometry_shader4 extension, also known as Shader Model 4.0)
 *      can render this node. For example NVIDIA 8800 and later boards.
 *      The #isSupported method returns TRUE if the necessary features are present.
 *  @LI At least one SoHeightFieldProperty which defines a property data set associated with the grid
 *      must be in the state.
 *  @LI In order to avoid holes between tiles, the data set must have been converted to LDM format
 *      with a border (overlap) of at least 1.
 *  @LI If an SoROI is in the state, SoHeightFieldRender renders only one box of the ROI
 *  (ie: correct rendering only if SoROI's flag field is set to SUB_VOLUME)
 *  @LI Only SoHeightFieldGeometry data sets with a depth of 1 can be rendered.
 *  @LI Lighting is limited to directional light and base color.
 *      Other kind of lights must be implemented manually using a custom shader.
 *  @LI The #enableBumpMapping field is not supported on this node
 * @ul
 *
 * @FILE_FORMAT_DEFAULT
 *    HeightFieldRender {
 *    @TABLE_FILE_FORMAT
 *       @TR enableBumpMapping @TD FALSE
 *       @TR bumpScale       @TD 1.0
 *       @TR alternateRep    @TD NULL
 *       @TR useRGBA         @TD FALSE
 *       @TR normalPrecision @TD HIGH
 *    @TABLE_END
 *    }
 *
 * @SEE_ALSO
 *    SoHeightFieldProperty,
 *    SoHeightFieldGeometry,
 *    SoMultiDataSeparator
*/
class VOLUMEVIZ_API SoHeightFieldRender : public SoSlice
{
  SO_NODE_HEADER( SoHeightFieldRender );

public:

  /** Normal precision mode */
  enum NormalPrecision
  {
    /** Normals are saved in a memory efficient format */
    NORMAL,

    /** Normals are saved in a high precision format but use more GPU memory */
    HIGH
  };

  /** 
   * Numeric precision of normal vectors.
   * Setting this field to NORMAL will save memory but may result in rendering
   * artifacts on datasets with high variance. 
   * Use enum #NormalPrecision. Default is HIGH.
   *
   * @FIELD_SINCE_OIV 8.1
   */
  SoSFEnum normalPrecision;

  /** Constructor */
  SoHeightFieldRender();

  /** Returns true if graphic card can render a SoHeightFieldRender.
   * GPU must support geometry shaders, floating point textures and
   * vertex buffer objects (VBO) 
   */
  static SbBool isSupported(SoState* state=NULL);

SoEXTENDER public:
  /** Compute the bounding box */
  void computeBBox(SoAction *, SbBox3f &box, SbVec3f &center);

  /** Picking */
  void rayPick(SoRayPickAction* action);

SoINTERNAL public:
  static void initClass();
  static void exitClass();

  /**
   * Handle field change
   */
  virtual void notify(SoNotList *list);

protected:
  /** Convert number of triangles into number of 2D textures */
  virtual unsigned int getSumOfMaxTextures2D(SoLDMNodeFrontManager* nfm);

  /** Generate primitive for the raypick action */
  virtual void generatePrimitives(SoAction *action);

  /**
   * Genrate primitive for given tile
   */
  void generatePrimitives(SoAction *action, const SoLDMTileID& tile);

  /** Render */
  virtual void doRendering(SoGLRenderAction *action);

  /** Destructor */
  virtual ~SoHeightFieldRender();

private:
  /**
   * A vertex
   */
  struct Vertex
  {
    SbVec2f coord;
  };

  /** Vertices and corresponding normal map */
  typedef std::pair<SoGLTexture*, SoGLTexture*> VerticesNormalTexPair;

  typedef std::vector<SoGLTexture*> TextureList;

  typedef std::vector<VerticesNormalTexPair> TileTextureMap;

  typedef std::vector<SoGLVBOCache*> GLVboVector;

  typedef std::map<SoLDMTileID, SoLDMTextureCache*> PropertyTextureMap;

  typedef std::pair<int, int> TileDimPair;

  typedef std::vector<Vertex> VertexList;

  /**
   * A set of indices for each tile size
   * (ie: normal tile size and tiles cropped by borders)
   */
  typedef std::map<TileDimPair, GLVboVector> GLVboVectorMap;

  /** Bind texture geometry and normals of the given tile */
  void bindTexturesGeometry(const SoLDMTileID& texTile);

  /** Add a new element to the property texture list for the given texTile */
  void allocatePropertyCache(const SoLDMTileID& texTile);

  /** Recreate property texture if needed (ie: context change) */
  void recreatePropertiesTexture();

  /**
   * Create property texture for given dataset-idpair and save it
   * into cache entry
   */
  void recreatePropertyTexture(const SoLDM::DataSetIdPair& p,
                               PropertyTextureMap::iterator& propTexIt);

  /** Set scaling and translation needed by shader */
  void setShaderGridTransforms(const SbBox3f& xyzBox, const SbBox3f& uvwBox);

  /** Load tiles in texture memory */
  void loadTiles(const SoLDM::TileIdVector & toLoad);

  /** Free unusued textures */
  void unloadTiles(const SoLDM::TileIdVector& toUnload);

  /** Fill texture with data of given tile */
  void loadTexture(SoGLTexture* texture, const SoLDMTileID& texTile);

  void renderTiles(const SoLDM::TileIdVector& tiles);

  /**
   * Fill detail with properties value
   */
  SoDetail * createTriangleDetail(SoRayPickAction *action,
                                  const SoPrimitiveVertex *v0,
                                  const SoPrimitiveVertex *v1,
                                  const SoPrimitiveVertex *v2,
                                  SoPickedPoint* pp);

    /** Generate a grid of size gridDim */
  void generateGridVboVertices(const SbVec2i32& gridDim);

  /** Generate a index grid of size croppedTileDim
   * indexing an array of size gridDim
   */
  void generateGridVboIndices(SoGLVBOCache* vbo,
                              const SbVec2i32& gridDim,
                              const SbVec2i32& croppedTileDim,
                              size_t level);

  void generateNormalMap(const VerticesNormalTexPair& texPair,
                         const SoLDMTileID& texTile);

  /**
   * Compute the xyz and uv box of the given tile
   * @param dataTile is the tile id to render
   * @param texTile is the tile id available in texture memory
   */
  void computeTileBboxes(const SoLDMTileID& dataTile,
                         const SoLDMTileID& texTile,
                         const std::vector<SbBox3i32>& roiBoxes,
                         SbBox3f& xyzBox, SbBox3f& uvwBox) const;
  /**
   * Delete all vbo of the given map entry
   */
  static void clearVboIndicesVector(const GLVboVectorMap::value_type& p);

  /** Clear m_vboVerticesMap */
  void clearVboIndicesVectorMap();

  /** Return vbo indices for given tile size and level
   * @param displayLevel is the level used for rendering
   */
  SoGLVBOCache* getVboIndices(const SbBox3i32& croppedTileBox,
                              size_t displayLevel);

  /**
   * Return list of loaded tiles intersected by the ray
   */
  void findIntersectingBbox(SoRayPickAction* action,
                            const SoLDMTileID& curNode,
                            SoLDM::TileIdVector& intersectingTiles);

  /** Generate indices for tile at given level */
  void generateIndices(std::vector<unsigned int>& indices,
                       const SbVec2i32& tileDim,
                       const SbVec2i32& croppedTileDim,
                       size_t level);

  /** Generate vertices grid for given tile dim */
  void generateGridVertices(VertexList& vertices, const SbVec2i32& tileDim) const;

  /** Compute uv coordinates at given pos */
  SbVec2f computeUv(const SbVec2f& coord, const SbBox3f& uvwBox) const;

  /**
   * Convert uv coordinates to ijk space
   * @param tileDim must be the tile dim at the tile's level
   */
  SbVec2i32 convertUvToIj(const SbVec2f& uv, const SbVec3i32 tileDim,
                          const SbVec3i32 tileOrigin) const;

  /** Get scale and translation to apply on coords for given box */
  void getGridTransforms(const SbBox3f& tileBox, SbVec2f& scale,
                         SbVec2f& translate) const;

  /**
   * Move given coord into grid scape
   * @param coord is between 0 and 1
   * @param box is the grid world box
   */
  SbVec2f convertToGridCoords(const SbVec2f& coord,
                              const SbBox3f& box) const;

  /**
   * Return texture filter mode for normals according to SoNormalBinding
   */
  GLint getNormalFilter() const;

  /** Return grid refinement level to use when displaying textile */
  size_t getDisplayLevel(const SoLDMTileID& dataTile,
                         const SoLDMTileID& texTile) const;

  /** Compute detail and coord in world space of the given vertex */
  void getVerticesInfo(SoHeightFieldDetail* detail, SbVec3f& coord, double& value,
                       const Vertex& vertex, const SbBox3f& xyzBox,
                       const SbBox3f& uvwBox, const SbVec3i32& tileDimAtLevel,
                       const SbVec3i32& origin, SoBufferObject* texData);

  /** Add triangles to the perfcounter */
  void updatePerfCounter(size_t triangles);

  /** Invalidate all textures (geometry and properties) */
  void invalidateTextures();
  static void invalidateVerticesNormalTexPair(const VerticesNormalTexPair& p);
  static void invalidatePropertyTexturePair(const PropertyTextureMap::value_type& p);

  SoVolumeStateHeightField* m_vs;

  TileTextureMap m_texturesMap;

  /** Vbo holding tileDimxtileDim vertices between [0-1]*/
  SoGLVBOCache* m_vboVertices;

  /** Recomput bbox only if dataset change */
  SbBox3f m_cachedBbox;

  /** Properties texture */
  PropertyTextureMap m_propTexMap;

  /**
   * One set of indices for each tile size and for
   * each levels
   */
  GLVboVectorMap m_vboIndicesMap;

  /** Fbo for normal gen */
  SoFrameBufferObject* m_fbo;

  /** Shader to used to compute normals */
  SoShaderProgram* m_normalGenShader;

  /** Profile horizons */
  static bool s_profile;

  /** Performace counter */
  SoPerfCounter* m_perf;
};

#ifdef _WIN32
#pragma warning( pop )
#endif
#endif // _SO_HEIGHTFIELD_RENDER_H
