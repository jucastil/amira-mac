/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Benjamin GRANGE (Aug 2006)
**=======================================================================*/


#ifndef SO_UNIFORM_GRID_CLIPPING
#define SO_UNIFORM_GRID_CLIPPING

#include <Inventor/nodes/SoTexture2.h>
#include <Inventor/fields/SoSFBox3f.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/SbBox.h>
#include <Inventor/STL/vector>
#include <LDM/SoLDMTileID.h>

class SoShaderObject;
class SoShaderProgram;
class SoFragmentShader;
class SoVertexShader;
class SoState;
class SoVolumeData;
class SoROI;
class SoLDMNodeFrontMgrOctree;

/**
* @VREXT Clips a volume using a 2D surface.
*
* @ingroup VolumeVizNodes
*
* @DESCRIPTION
* This class defines a clipping surface which is a height field defined
* by a 2D texture and a bounding box in modeling coordinates.  This can
* be used, for example, to clip a seismic volume against a horizon surface.
*
* Each texel value is interpreted as a value in the range 0..1.
* The height value of the surface at each texel is the range of the height #axis
* (default axis is Y) of the specified bounding box, multiplied by the 0..1 texel value.
*
* By default all voxels above the surface are clipped. But the clipping behavior can
* be changed with the #clipBelow, #clipAbove and #thickness fields.
*
* Since the clipping surface is an SoTexture, all the usual texturing parameters apply. 
* Wrapping and filtering modes are particularly important. Setting wrap mode to something other
* than CLAMP_TO_EDGE may cause unwanted interpolation on edges. Setting filter mode
* to nearest will give a blocky result which may or may not be desired.
*
* Each surface must be assigned to a different texture unit not used for the same
* rendering. By default, the transfer function (SoTransferFunction)
* is in unit 0 and the volume data (SoVolumeData) is in unit 1, so unit 2 is available
* for use (assuming there is only one data set). 
* Use an SoTextureUnit node to specify the texture unit:
*
*@TABLE_1B
*      @TR Clipping surface @TD Clipping applied to a volume
*         @TR  @IMAGE clipgrid.jpg
*                   @TD @IMAGE clipgrid_result.jpg
*      @TABLE_END
*
* For best performance, the texture internal format should be one of the LUMINANCE* types.
* For example, a grayscale .png file will automatically be in this format.
* When the format is not luminance, only the red component is used. If no red component is
* available (ALPHA texture...), the surface will be totally flat.
*
* The following code loads the clipping surface "horizon2D.png" and puts it in texture unit 2:
* \oivnetdoc
*   \code
*   SoTextureUnit texUnit2 = new SoTextureUnit();
*   texUnit2.unit.SetValue( 2 );
*   SoUniformGridClipping grid = new SoUniformGridClipping();
*   grid.filename.SetValue( "horizon2D.png" );
*   root.AddChild(texUnit2);
*   root.AddChild(grid);
*   root.AddChild(transferFunction);
*   root.AddChild(volumeData);
*   root.AddChild(volumeRender);
*   \endcode
* \else
*   \code
*   SoTextureUnit *texUnit2 = new SoTextureUnit();
*   texUnit2->unit = 2;
*   SoUniformGridClipping *grid = new SoUniformGridClipping();
*   grid->filename = "horizon2D.png"
*   root->addChild(texUnit2);
*   root->addChild(grid);
*   root->addChild(transferFunction);
*   root->addChild(volumeData);
*   root->addChild(volumeRender);
*   \endcode
* \endoivnetdoc
*
* @B Notes: @b 
* @UL 
*  @LI When using a custom SoVolumeShader with this node and redefining the @I main() @i
*   function, you must call @I VVizClipVoxel() @i in the @I main() @i function if you are writing a
*   fragment shader or @I VVizCalcDistToUniformGrid() @i if it's a vertex shader. If you don't
*   do this, you will get a GLSL compilation error or clipping won't work.
*  @LI This node uses predefined shaders internally and searches for them in the
*   following directories in this order: current directory, $IVVR_SHADERS_PATH, and
*   $OIVHOME/data/volumeviz/shaders. On Windows, the directory containing the VolumeViz DLL
*   is searched last.
* @ul
*
* @B Limitations: @b
* @UL
*  @LI Only graphics cards supporting the GLSL language can use this node.
*  @LI The maximum number of SoUniformGridClipping nodes that can be
*   applied to the same volume is limited to getMaxNumberOfUniformGrids().
*   This limitation depends on the maximum number of GLSL "varying" parameters
*   supported by your graphics card.
* @ul
*
 * @FILE_FORMAT_DEFAULT
 *    UniformGridClipping {
 *    @TABLE_FILE_FORMAT
 *       @TR axis                     @TD Y
 *       @TR extent                   @TD 2 1 2
 *       @TR filename                 @TD ""
 *       @TR image                    @TD 0 0 0
 *       @TR wrapS                    @TD CLAMP_TO_EDGE
 *       @TR wrapT                    @TD CLAMP_TO_EDGE
 *       @TR model                    @TD MODULATE
 *       @TR enableCompressedTexture  @TD FALSE
 *       @TR blendColor               @TD 0 0 0
 *       @TR enableBorder             @TD FALSE
 *       @TR borderColor              @TD 0 0 0 0
 *       @TR maxAnisotropy            @TD 1.0
 *       @TR minFilter                @TD AUTO
 *       @TR magFilter                @TD AUTO
 *       @TR loadingMode              @TD AUTO
 *       @TR useAutoMipmap            @TD FALSE
 *       @TR internalFormat           @TD AUTO_INTERNAL_FORMAT
 *       @TR thickness                @TD 0
 *       @TR clipBelow                @TD FALSE
 *       @TR clipAbove                @TD TRUE
 *    @TABLE_END
 *    }
* @SEE_ALSO
*  SoVolumeRender,
*  SoPreferences,
*  SoShaderProgram,
*  SoTexture2,
*  SoTextureUnit,
*  SoVolumeClippingGroup,
*  SoVolumeIsosurface,
*  SoVolumeRenderingQuality
*
*/
class VOLUMEVIZ_API SoUniformGridClipping : public SoTexture2 {
  SO_NODE_HEADER(SoUniformGridClipping);

public:
  /**
   * Constructor.
   */
  SoUniformGridClipping();

  /**
   * Bounding box of the surface in 3D geometric coordinates. @BR
   * Default is a box of size (2, 1, 2) with its back left corner at (-1, 0, -1). @BR
   * @FIELD_SINCE_OIV 8.0
   */
  SoSFBox3f extent;

  /** Slice Axis */
  enum Axis {
    /** X Axis */
    X,
    /** Y Axis (Default) */
    Y,
    /** Z Axis */
    Z
  };

  /**
   * Height axis: X, Y, or Z. Default is Y. @BR
   * @FIELD_SINCE_OIV 8.0
   */
  SoSFEnum axis;

  /**
   * Defines a clipping thickness area in the axis direction, ignored if set to 0.
   * Default is 0;
   *
   * Notes: If thickness is 0 and clipBelow and clipAbove are both TRUE then the 
   * whole volume is clipped.
   *
   * @FIELD_SINCE_OIV 8.6
   */
  SoSFFloat thickness;

  /**
   * Clip voxels below the surface.
   * Default is FALSE;
   *
   * @FIELD_SINCE_OIV 8.6
   */
  SoSFBool clipBelow;

  /**
   * Clip voxels above the surface.
   * Default is TRUE;
   *
   * @FIELD_SINCE_OIV 8.6
   */
  SoSFBool clipAbove;

  /**
   * @deprecated Use SoUniformGridClipping::#extent instead.
   * @DEPRECATED_SINCE_OIV 8.0
   */
#ifndef VolumeViz_EXPORTS
  SoDEPRECATED
#endif
   SoSFBox3f size;

  /**
   * Returns TRUE if uniform grid clipping is supported by the graphics board.
   * The GPU must support GLSL. Check the maximum number of clipping surfaces
   * using getMaxNumberofUniformGrids.
   */
  static SbBool isSupported(SoState* state=NULL) ;

  /**
   * Returns the maximum number of clipping surfaces supported by the hardware.
   */
  static int getMaxNumberOfUniformGrids(SoState* state=NULL);

SoEXTENDER public:
  virtual void GLRender(SoGLRenderAction *action);
  virtual void getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void doAction(SoAction *action);
  virtual void doActionOnRTT(SoAction *action);
  virtual void rayPick(SoRayPickAction *action);

SoINTERNAL public:

  /**
   * Allows to revert elevation values elevation = elevationMax - (elevation - elevationMin).
   * This is usefull when generating elevation map from a normalized depth map 
   * where highest values is 0 and smallest is 1.
   * Default is FALSE;
   * INTERNAL FIELDS only used by SoUniformGridProjectionClipping
   *
   * @FIELD_SINCE_OIV 8.6
   */
  SoSFBool revertMode;

  static void initClass() ;
  static void exitClass() ;

  //Install a ROI box in the state in order to act like a ROI
  void installFakeROIBox(SoAction *action, SoVolumeData *vd);

  /** used by SoUniformGridClippingElement */
  int getTexUnit() { return m_texUnit; }

  //Set needed uniforms (used by SoVolumeShader)
  void setClipmapUniforms(SoGLRenderAction* action, SoShaderProgram* prog, const std::vector<SoUniformGridClipping *> &grids);
  void setPlaneUniforms(SoGLRenderAction* action, SoShaderProgram* prog, const std::vector<SoUniformGridClipping *> &grids);
  void setZScaleUniform(SoGLRenderAction* action, SoShaderProgram* prog, const std::vector<SoUniformGridClipping *> &grids);
  void setClipParamUniforms(SoGLRenderAction* action, SoShaderProgram* prog, const std::vector<SoUniformGridClipping *> &grids);

  // Return true if the box is under the grid's bbox
  virtual SbBool isCulled(const SbBox3f &box);

  // Return the bbox cropped by the plane
  const SbBox3i32& cropBBox(SoState* state, SoVolumeData* vd);

  /** Handle field change*/
  virtual void notify(SoNotList *list);

  static void setVVizUniform(SoGLRenderAction* action);

protected:

  /** Destructor */
  virtual ~SoUniformGridClipping();

  SbBox3f getBBox();

private:
  enum IntersectionType
  {
    ALL_OUT,
    ALL_IN,    
    INTERSECT
  };
  //Return height field min/max
  virtual void getMinMax(float &min, float &max);

  /** False if roi must be recomputed */
  bool isCroppedBboxCacheValid(SoState *state);

  /** Compute clip plane (expressed in local space) enclosing the region not clipped by the grid (plane's normals are pointing inside)
  * If everything is clipped, clipPlanes is empty */
  void computeGridClippingPlanes(const SbBox3f& volumeExtent, std::vector<SbPlane>& clipPlanes);

  /** Return the kind of intersection between the tile and the clip volume. clipPlanes and tileBbox are expressed in 
   * xyz data set space. */
  IntersectionType intersectGeometry(const std::vector<SbPlane>& clipPlanes, const SbBox3f& tileBbox);

  /** Traverse octree until a tile is fully in or out of the clipping volume and extends resultBox*/
  void cropBBoxRec(const std::vector<SbPlane>& clipPlanes, SoLDMNodeFrontMgrOctree* nfm, 
                   SoVolumeData* vd, const SoLDMTileID& tile, SbBox3i32& resultBox);

  /**
   * Find the min and max of the texture (result is in [0,1])
   */
  template <typename T> void findMinMax(float& min, float& max);

  //Texture unit of the SoUniformGridClipping
  int m_texUnit;

  //Finite plane coords in world space
  //[0] is the non normalised (in order to know the plane's bounds) x-axis of the plane's frame
  //[1] y-axis
  //[2] the origin
  SbMatrix m_localModelMat;
  SbMatrix m_localModelView;
  SbVec3f m_planeCoords[3];  
  float m_zScale;

  SbVec3f m_planeCoordsWorld[3];  

  //Used for culling in SoVolumeRender
  float m_minHeight, m_maxHeight;
  SbBool m_recomputeMinMax;

  SoROI* m_roi;
  SoCache* m_croppedBoxCache;
  SbBox3i32 m_croppedBox;
};

#endif
