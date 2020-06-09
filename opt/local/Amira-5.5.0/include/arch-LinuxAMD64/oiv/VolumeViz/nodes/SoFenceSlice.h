/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_FENCE_SLICE_
#define  _SO_FENCE_SLICE_

#ifdef _WIN32
#pragma warning( push )
#pragma warning(disable:4251)
#endif

#include <Inventor/fields/SoMFVec2f.h>
#include <Inventor/SbBox.h>
#include <Inventor/STL/vector>
#include <Inventor/STL/pair>

#include <LDM/SoLDMTileID.h>

#include <VolumeViz/nodes/SoSlice.h>

class SoCache ;
class SoFenceSliceInterface;
class SoFenceSliceLdm;
class SoFenceSlicePaging;
class SoFragmentShader;
class SoFrameBufferObject;
class SoGLTexture;
class SoGLVBOCache;
class SoGLVolCacheList;
class SoLDMNodeFrontManager;
class SoLDMOrthoSliceGeom;
class SoShaderProgram;
class SoVolumeData;
class SoVolumeStateFenceSlice;

/**
 * @VREXT Fence slice shape node.
 *
 * @ingroup VolumeVizNodes
 *
 * @DESCRIPTION
 * This node renders a strip (connected series) of slices.  The strip is defined
 * by a set of 2D vertices that form a polyline.  Each segment of the polyline
 * is extruded along the axis specified in the #axis field to form (in effect)
 * an oblique slice.
 * The default axis is Z, so the 2D points are treated as (X,Y) values. A similar
 * effect could be obtained using volume geometry (e.g. SoVolumeFaceSet), but
 * SoFenceSlice is more convenient and is optimized for this specific case.
 *
 *   For a non-RGBA (scalar valued) volume,
 *   each voxel's RGBA value is determined by the current SoDataRange and SoTransferFunction.
 *   The current @B diffuse color @b and @B transparency @b (set, for example, with
 *   an SoMaterial node) modify the appearance of the slice.  This means that, for
 *   example, the current transparency can be used as a @I global alpha @i value
 *   to modulate the overall opacity of the slice.
 *   For an RGBA volume each voxel's RGBA value comes directly from the volume data.
 *
 * The #interpolation field controls how the texture is interpolated.
 *
 * The #alphaUse field (SoSlice) controls how the voxel's alpha component is used when drawing the fence slice.
 *
 * The #composition field controls how the fence slice is blended with other objects
 * in the scene.
 *
 * Optionally a bump mapping effect may be applied. Normal vectors are automatically
 * computed from the data value gradient.  The #enableBumpMapping and #bumpScale
 * fields (SoSlice) control whether bump mapping is active and the intensity of the effect.
 *
 * The current SoROI (Region of Interest) node, if any, limits the slice to a
 * subvolume.  Volume clipping nodes (SoVolumeClippingGroup, SoUniformGridClipping)
 * may also be used to limit the extent of the slice.
 *
 * The current SoVolumeShader node, if any, allows custom shaders to be defined for
 * special computation or rendering effects, including blending multiple volumes.
 *
 *     Note: The volume size and orientation (like geometry) can be modified by
 *     transformation nodes in the scene graph and this in turn modifies the
 *     appearance of volume rendering nodes like SoFenceSlice.
 *     However the same transformation must be applied to the volume data node
 *     and all volume rendering nodes associated with that volume.  So effectively
 *     any transformation nodes that affect the volume must be placed @B before @b
 *     the volume data node.
 *
 * @B NOTE: @b
 * This node needs a graphic card with support for GLSL shader, vertex buffer 
 * objects (VBO) and framebuffer object (FBO). Use the isSupported() method to
 * check if the current graphics board can render a FenceSlice.
 *
 * @FILE_FORMAT_DEFAULT
 *    FenceSlice {
 *    @TABLE_FILE_FORMAT
 *       @TR points          @TD [ ]
 *       @TR axis            @TD Z
 *       @TR interpolation   @TD LINEAR
 *       @TR alphaUse        @TD ALPHA_BINARY
 *       @TR composition     @TD ALPHA_BLENDING
 *       @TR useRGBA         @TD FALSE
 *       @TR alternateRep    @TD NULL
 *       @TR enableBumpMapping @TD FALSE
 *       @TR bumpScale       @TD 1.0
 *    @TABLE_END
 *    }
 *
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction @BR
 *        Draws a textured shape based on current SoVolumeData, SoTransferFunction,
 *        and SoROI nodes.
 *
 *    SoGetBoundingBoxAction @BR
 *        Computes the bounding box that encloses the fence slice.
 *
 *
 * @SEE_ALSO
 *    SoVolumeData,
 *    SoDataRange,
 *    SoTransferFunction,
 *    SoROI,
 *    SoSlice
 *    SoObliqueSlice,
 *    SoOrthoSlice
 *
 *
 */

class VOLUMEVIZ_API SoFenceSlice : public SoSlice
{
  SO_NODE_HEADER( SoFenceSlice );

public:
  /**
   * Constructor.
   */
  SoFenceSlice();

  /**
   * Set of points defining a lineset. @BR
   * If #axis is:
   * - X: points are Y,Z coordinates
   * - Y: points are Z,X coordinates
   * - Z: points are X,Y coordinates
   *
   * All points should be inside the 3D extent of the volume.
   */
  SoMFVec2f points;

  enum Axis {
    X,
    Y,
    /** (Default) */
    Z
  };

  /**
   * Extrusion axis: X, Y, or Z.
   * Use enum #Axis. Default is Z.
   */
  SoSFEnum axis;

  /**
   * Returns true if the shape intersects the given tile
   */
  virtual bool intersect(SoLDMNodeFrontManager* nfm, const SoLDMTileID& tileId);

  /** Returns true if graphic card can render an SoFenceSlice.
   * GPU must support GLSL, vertex buffer objects (VBO) and 
   * frame buffer objects (FBO).
   */
  static SbBool isSupported(SoState* state=NULL);

SoEXTENDER public:
  /**
   * Compute the bounding box
   */
  void computeBBox(SoAction *, SbBox3f &box, SbVec3f &center);

SoINTERNAL public:
  static void initClass();
  static void exitClass();

  /** Handle notification */
  virtual void notify(SoNotList *list);

  /** Return true if the given tile has geometry */
  bool intersectGeometry(const SoLDMTileID& tile) const;

protected:
  /**
   * Generate primitive for the raypick action
   */
  virtual void generatePrimitives(SoAction *action);

  /**
   * Render the fence
   */
  virtual void doRendering(SoGLRenderAction *action);

  /**
   * Destructor
   */
  virtual ~SoFenceSlice();

  /** Volume state*/
  SoVolumeStateFenceSlice* m_vs;

private:
  /** Used to index m_texGenFrag */
  enum FragmentMode
  {
    LUMINANCE,
    RGBA
  };

  /**
   * A vertex
   */
  struct Vertex
  {
    SbVec3f normal;
    SbVec3f coord;
    SbVec2f uv;
  };
  typedef std::vector<Vertex> VertexVector;
  typedef std::vector<Vertex> Polygon;

  typedef std::vector<VertexVector> TileVerticesIndexMap;

  typedef std::vector<SoGLTexture*> TextureList;

  typedef std::vector<TextureList> TileTextureMap;

  typedef std::pair<size_t, size_t> OffsetSizePair;

  typedef std::vector<OffsetSizePair> TileGeometryMap;

  typedef std::vector<SbVec4f> TexCoordGenFunc;

  typedef std::pair<float, float> FloatPair;

  /** Set OpenGL clipping plane around the box */
  void setupGLClipPlanes(const SbBox3f& box, bool exclude) const;

  /**
   * Fill each texture with data from the corresponding
   * dataset and the given tile id
   */
  void loadTextureGpu(SoState* state,
                      const SoFenceSlice::TextureList& textures,
                      const SoLDMTileID& texTile);
  /**
   * Fill textures with a SoGLTexture for each dataset
   */
  void generateTextures(TextureList& textures);

  /** Fill m_tileVertices */
  void createGeometry();

  void createGeometry(const SoLDMTileID& tile, VertexVector& vertices, TexCoordGenFunc& texGenFunc) const;

  /** Generate texture coordinates */
  void generateUvCoordinates(VertexVector& vertices,
                             const SbBox3i32& tileBox,
                             const SbBox3i32& texTileBox,
                             const SbBox3i32& border,
                             const SbVec3i32& tileDim,
                             const SoLDMTileID* tile) const;

  /** Draw the specified tile by combining high resoultion tiles */
  void drawTileGeometry(LDM_TILE_ID_TYPE fileId);

  /**
   * Compute intersecion of tileBbox with segment p0-p1
   * Clipped vertices are put into clippedLine
   * @param alpha holds interpolation factor for the 2 points
   * of clippedLine
   * @return false if no intersection
   */
  bool intersectLine(const SbBox3f& tileBbox, const SbVec2f& p0,
                     const SbVec2f& p1, SbVec2f* clippedLine,
                     FloatPair& alpha) const;

  /** Fill the vbo with computed vertices */
  void createVbo(const TileVerticesIndexMap& vertTileMap);

  /** Delete all textures in TextureList */
  static void deleteTileTextureMap(TileTextureMap::value_type& texList);

  /** Delete textures associated to these tiles */
  void unloadTiles(const SoLDM::TileIdVector & toUnload);

  /** Create textures associated to these tiles */
  void loadTiles(const SoLDM::TileIdVector & toLoad);

  /** Create fbo if necessary and attach the texture to it */
  void setupFbo(const SbVec3i32& tileSize);

  /** Render flat geometry into the texture*/
  void renderUnfoldedGeometry(const VertexVector& pts) const;

  /** Render flat geometry into the texture with border handling*/
  void renderUnfoldedGeometryWithBorder(const VertexVector& pts, const SoLDMTileID *tileId) const;

  /** Change the fragment shader used for texture generation if in RGBA/ALPHA mode */
  void selectFragmentShader(GLenum format);

  /** Display generated textures */
  void debugTextures(const SoLDM::TileIdVector & tiles);

  /** Setup OpenGL's vertexpointer */
  void setupVertexArray() const;

  /** Compute per vertices normal */
  void computeNormals();

  /** Vertices of each tiles */
  TileVerticesIndexMap m_tileVertices;

  /** Current node front manager */
  SoLDMNodeFrontManager* m_nfm;

  /** Roi applied on the volume geometry*/
  std::vector<SbBox3i32> m_roiBoxes;
  SbBox3i32 m_vdBox;

  /** Cache tile's texture*/
  TileTextureMap m_tileTextureMap;

  /** Vbo holding vertices */
  SoGLVBOCache* m_vboVertices;

  /**
   * Give the start and size of geometry for the given tile
   * in m_vboVertices
   */
  TileGeometryMap m_tileGeometryMap;

  /** Display texture outline */
  bool m_drawTileOutline;

  /** Recreate geometry */
  bool m_needUpdate;

  /** 3D texture to use for texture generation */
  SoGLTexture* m_texture3d;

  /** Render target */
  SoGLTexture* m_rtt;

  /** Fbo for tex gen */
  SoFrameBufferObject* m_fbo;

  /** Shader to used to render textures */
  SoShaderProgram* m_texGenShader;

  /** Rgba and alpha fragment */
  SoFragmentShader* m_texGenFrag[2];

  /** Current fragment for texture generation */
  FragmentMode m_fragMode;

  /** Coefficients for texture coords computation */
  std::vector<TexCoordGenFunc> m_texCoordGenFunc;

  /** Temporary storage used for texture creation*/
  std::vector<unsigned int> m_sliceTextureBuffer;

  /** Per faces normals */
  std::vector<SbVec3f> m_normals;

  /** If true display generated textures */
  SbBool s_debugTextures;
};

#ifdef _WIN32
#pragma warning( pop )
#endif
#endif // _SO_FENCE_SLICE_
