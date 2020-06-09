/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef SO_SLICE_H
#define SO_SLICE_H

#include <VolumeViz/nodes/SoVolumeShape.h>

class SoVolumeData;
class SoFragmentShader;
class SoSliceInterface;

/**
*
* @VREXT Abstract base class for slice shape nodes.
*
* @ingroup VolumeVizNodes
*
* @DESCRIPTION
*
*   This class defines common properties for the SoOrthoSlice, SoObliqueSlice, 
*   SoFenceSlice, SoVolumeSkin and SoHeightFieldRender nodes.
*
*   The #alphaUse field controls how the voxel's alpha component is used when drawing the slice.
*
*   The #enableBumpMapping and #bumpScale fields control a rendering effect called bump
*   mapping that simulates displacement of the slice surface using the gradient vectors
*   (computed on the GPU) as normal vectors.
*
*   The #largeSliceSupport field enables direct loading of full resolution slice data
*   from the volume reader, without (necessarily) loading complete tiles.
*
* @SEE_ALSO
*    SoObliqueSlice,
*    SoOrthoSlice,
*    SoFenceSlice,
*    SoVolumeSkin
*
*
*/
class VOLUMEVIZ_API SoSlice : public SoVolumeShape {
  SO_NODE_ABSTRACT_HEADER(SoSlice);

public:

  /**
  * Specifies if a bump mapping effect will be applied to the slice.
  * Default is FALSE.
  * Bump mapping is a rendering effect that simulates displacement of the slice 
  * surface using the gradient vectors (computed on the GPU) as normal vectors.
  * Normally lighting should be enabled to maximize the visual effect of bump mapping.
  *
  * This mode requires a graphics card supporting the OpenGL GLSL shading language.
  * If your graphics card does not have the necessary support, the slice will be
  * rendered without bump mapping.
  *
  * Bump mapping is not available for the SoHeightFieldRender node.
  *
  * @FIELD_SINCE_OIV 6.0
  */
  SoSFBool enableBumpMapping;

  /**
  * Specifies the intensity of the bump mapping effect.
  * Default value is 1.0. Valid values range from 0 (no bump mapping)
  * to no upper limit. (2 is a fairly large value.)
  *
  * @FIELD_SINCE_OIV 6.0
  */
  SoSFFloat bumpScale;

  /**
  * This field optionally holds a subgraph containing only core Open Inventor nodes
  * that can be used for rendering when VolumeViz is not available.
  * For example, the alternate representation for an SoOrthoSlice could be a small
  * scene graph containing an SoTexture2 and an SoIndexedFaceSet.  Such a scene graph
  * could be converted and exported as a PDF3D file or an X3D/VRML file.
  * Default is NULL. But an alternateRep scene graph is automatically created during 
  * a write action if SoVolumeRendering::setWriteAlternateRep(TRUE) was called.
  *
  * @FIELD_SINCE_OIV 4.0
  */
  SoSFNode alternateRep;

  /** Alpha component usage mode 
   *  Used in the #alphaUse field
   */
  enum AlphaUse {
    /** Use alpha values as is */
    ALPHA_AS_IS,
    /** Ignore alpha values (slice is opaque) */
    ALPHA_OPAQUE,
    /** Use Alpha in binary mode (Default) */
    ALPHA_BINARY
  };

  /**
  * Specifies how to use the alpha component of each voxel's RGBA value.
  * Use enum #AlphaUse. Default is ALPHA_BINARY.
  * The alpha component will typically come from the transfer function, but
  * (since Open Inventor 8.5) could come from direct rendering of an RGBA volume.
  * The alpha values used for rendering the slice will vary depending on the value of this field.
  *
  * The following table shows how the alpha value is computed according to this
  * field and the incoming voxel alpha values:
  *
  *    @TABLE_1B
  *       @TR When alphaUse field is:    @TD ALPHA_BINARY    @TD ALPHA_OPAQUE    @TD ALPHA_AS_IS
  *       @TR @B Incoming Alpha value@b  @TD @B Alpha Value Actually Used@b
  *       @TR = 0                        @TD 0 (Invisible)   @TD 1 (Opaque)      @TD 0 (Invisible)
  *       @TR &gt; 0                     @TD 1 (Opaque)      @TD 1 (Opaque)      @TD same as incoming
  *    @TABLE_END
  */
  SoSFEnum alphaUse;

  /**
  * Specifies whether to create RGBA textures.
  * Default is FALSE.
  * If useRGBA is FALSE, indexed textures will be used if the graphics board supports
  * them.
  * If useRGBA is TRUE, RGBA textures will be used instead of indexed textures.
  * RGBA textures allow higher precision but are slower to load and use more
  * texture memory.
  * 
  * @IMPORTANT_NOTE If the dataSet is RGBA then this field is ignored and RGBA textures are used. @BR
  *
  * @FIELD_SINCE_OIV 5.0
  */
  SoSFBool useRGBA;

  /**
   * Activate/deactivate direct loading of full resolution slice data. 
   * Default is FALSE.
   * When TRUE, if all the required full resolution tiles have already been loaded, then
   * the slice data is taken from LDM system memory cache as usual. But if some required 
   * tiles are not currently in memory, the required slice data will be loaded directly 
   * from the volume reader @I without @i loading the complete tiles. This reduces disk I/O
   * and reduces the amount of system memory required to display the slice at full resolution,
   * so larger (or more) slices can be displayed. The required tiles are then scheduled to be
   * loaded asynchronously in case adjacent slices are displayed later. 
   * For example, loading a 1024x1024 SoOrthoSlice from an 8-bit dataset with 128x128x128
   * tiles would normally require loading 1024x1024x128 bytes of data (as complete tiles). 
   * With largeSliceSupport enabled, only 1024x1024 bytes (maximum) of data need to
   * be loaded (in the worst case where no high resolution data is currently in memory).
   *
   * @FIELD_SINCE_OIV 8.0
   *
   * @B Limitations @b :
   * - This feature is only available for SoOrthoSlice and SoVolumeSkin.
   * - This feature can only be enabled for volumes loaded from an LDM format file,
   *       i.e. using the reader class SoVRLdmFileReader.
   */
  SoSFBool largeSliceSupport;

SoINTERNAL public:
  // Define callback used in computeGeometryAndTex
  typedef int textureCreateCB( int dimx, int dimy, unsigned int *texData, void *userData );

  static void initClass();
  static void exitClass();

  bool requireDefaultShader();

  /**
   * Return TRUE if an external shader is used. textype is forced to 2D if the color map is
   * fragment based.
   */
  virtual bool enableColorMap(SoState *state,
                              SoTransferFunction::GLColorMapType colorMapInstalled,
                              int &texType);

  /** True if using atlas */
  bool isUsingTextureAtlas();

SoEXTENDER public:
  void GLRender(SoGLRenderAction *action);

protected:

  /**
  * Constructor
  */
  SoSlice();

  /**
  * Destructor
  */
  virtual ~SoSlice();

#ifndef HIDDEN_FROM_DOC

  //Return false if normal rendering can't be done
  bool handleAlternateRep(SoGLRenderAction *action, SoVolumeData *volumeDataNode);

  virtual bool isTransparent(SoState *state);

  /**
   * Install clipping planes if needed
   */
  virtual void installClippingPlanes() {}

#endif // HIDDEN_FROM_DOC
  SoSliceInterface* m_commonSliceInterface;
};

#endif
