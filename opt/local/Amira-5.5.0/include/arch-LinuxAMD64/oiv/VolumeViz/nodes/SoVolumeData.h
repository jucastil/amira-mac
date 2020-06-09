/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : P. ESTRADE (Feb 2000)
**=======================================================================*/
#ifndef  _SO_VOLUME_DATA_
#define  _SO_VOLUME_DATA_

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#pragma warning(disable:4996)
#endif

#include <Inventor/STL/map>
#include <Inventor/STL/vector>

#include <Inventor/SbBox.h>
#include <Inventor/SbPList.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFMemObj.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFUShort.h>
#include <Inventor/fields/SoSFArray3D.h>

#include <LDM/SoLDMDataAccess.h>
#include <LDM/SoLDMMediator.h>
#include <LDM/SoLDMTileID.h>
#include <LDM/nodes/SoDataSet.h>
#include <LDM/nodes/SoTransferFunction.h>
#include <LDM/readers/SoVolumeReader.h>

#include <VolumeViz/nodes/SoVolumeRendering.h>

class SoGLRenderAction;
class SoCallbackAction;
class SoWriteAction;
class SoVolumeReader;
class SoCache;
class SoState;
class SoVolumePaging;
class SoGLVolCacheList;
class SoVolumeHistogram;
class SoDataCompositor;
class SoVolumeShader;

// LDM
class SoLDMTileManager;
class SoLDMTileVisitor;
class SoLDMNodeFrontManager;
class SoLDMTextureManager;
class SoLDMGeometry;
class SoLDMResourceManager;

// Algorithms
class SoDataExtract;
class LDMDefaultSliceAccessor;
class SoVolumeData;

/*
* @deprecated use SoDataSet::SoLDMDataTransformCB instead.
* Data transforming function type for LDM mode.
* @DEPRECATED_SINCE_OIV 7.0
* REMOVED IN OIV 8.0 see compatibility doc issues
*/
//typedef void
//SoLDMDataTransformCB(SoVolumeData* ds,
//                     const SbVec3i32& bufferDimension, //tile dim
//                     void* bufferToTransform,
//                     const SbBox3i32& dataBox,      //position of tile in data space
//                     int resolutionLevel,	  //resolution level of the tile
//                     void* userData);



/**
* @VREXT Volume data property node.
*
* @ingroup VolumeVizNodes
*
* @DESCRIPTION
*   This class defines the data volume and its properties, and also provides utilities for
*   extracting a subset of the volume and for resampling the volume. The data can be
*   stored in memory, read from a file or accessed via a user-defined reader.
*   This node provides the data for the volume rendering shape nodes (SoVolumeRender, 
*   SoOrthoSlice, SoObliqueSlice, etc.) and is the parent class for some specialized
*   data nodes (SoHeightFieldGeometry, SoVolumeMask, etc.).
*
* The data volume can be specified by:
*
*   - Setting the #data field @BR
*      This implies that the entire volume has already been loaded
*      into a contiguous block of system memory (RAM).
*
*   - Setting the #fileName field @BR
*      This implies that the volume is stored on disk, in one of the file
*      formats for which VolumeViz has a built-in reader. VolumeViz
*     will automatically select a volume reader class based on the file extension,
*     for example ".am" for the AmiraMesh file format.  If the filename does not
*     have an extension or does not have the appropriate extension, the
*     application must specify a volume reader explicitly using setReader().
*     See the supported file formats below. Note that SoVolumeData and its
*     derived classes do not search the SoInput directory list to find files.
*
*  - Calling the setReader() method @BR
*     This is the most general method because an application can
*     specify one of the standard VolumeViz readers or implement
*     a custom subclass of SoVolumeReader.
*     VolumeViz will get the volume properties (dimensions, size, data type, etc) and
*     access the volume data through the specified reader object. This allows the
*     application to completely control how, and from where, the data is loaded.
*
*     Note: When using a custom reader, any reader method that changes the volume
*     properties (dimension, size, data type, etc) should notify the SoVolumeData
*     node by calling the reader's touch() method.  If this notification is not done,
*     SoVolumeData fields, for example #extent, won't be updated correctly.
*
*  @B Volume Properties: @b
*   - Dimensions @BR
*     The dimensions of the volume (number of voxels on each axis) are normally
*     determined by the volume reader from information in ithe data file(s), the
*     number of images in the stack, etc.  (When you set the #data field directly
*     you specify the volume dimensions.)  You can query the volume dimensions 
*     using the #data field.  For example, in C++:
*     \oivnetdoc
*       \code
*       SbVec3i32 voldim = VolumeData.data.GetSize();
*       \endcode
*     \else
*       \code
*       SbVec3i32 voldim = pVolumeData->data.getSize();
*       \endcode
*     \endoivnetdoc
*
*   - Size @BR
*     The geometric size of the volume (3D extent) is initially determined by the
*     volume reader but can also be set using the #extent field. The volume size
*     is the bounding box of the volume in world coordinates. It also (indirectly)
*     specifies the voxel size/spacing.  You can query the volume size using the 
*     #extent field.  For example, in C++:
*     \oivnetdoc
*     \code
*        SbBox3f volext = VolumeData.extent.GetValue();
*     \endcode
*     \else
*     \code
*        SbBox3f volext = pVolumeData->extent.getValue();
*     \endcode
*     \endoivnetdoc
*     Note: The volume size and orientation (like geometry) can be modified by
*     transformation nodes in the scene graph and this in turn modifies the
*     appearance of volume rendering nodes (SoVolumeRender, SoOrthoSlice, etc).
*     However the same transformation must be applied to the volume data node
*     and all volume rendering nodes associated with that volume.  So effectively
*     any transformation nodes that affect the volume must be placed @B before @b
*     the volume data node.
*
*   - Voxel size/spacing @BR
*     If the volume data is uniformly sampled, the volume size is typically set equal
*     to the dimensions of the volume or to values that are proportional to the volume
*     dimensions.  For example, -1 to 1 on the longest axis of the volume. In this 
*     case voxels along each axis are spaced the same. If the voxel spacing is 
*     different on one or more axes, set the volume size to reflect the actual voxel
*     spacing.
*
*   - Data type @BR
*     VolumeViz supports volumes containing signed and unsigned integer values (byte,
*     short, int), floating point values and RGBA values.  The data type is 
*     determined by the reader (or when setting the #data field).  You can query the 
*     data type and/or number of bytes per voxel using methods inherited from SoDataSet.  
*     For example in C++:
*     \oivnetdoc
*     \code
*       int bytesPerVoxel = VolumeData.GetDataSize();
*     \endcode
*     \else
*     \code
*       int bytesPerVoxel = pVolumeData->getDataSize();
*     \endcode
*     \endoivnetdoc
*
*   - Data range @BR
*     In volumes using data types larger than byte, the actual range of data values
*     is usually smaller than the range of the data type.  The application should
*     use an SoDataRange node to specify the range of values that will be mapped
*     into the transfer function.  You can query the actual minimum and maximum
*     values in the volume using the getMinMax methods.  For example, C++:
*     \oivnetdoc
*     \code
*       double minval, maxval;
*       bool ok = VolumeData.GetMinMax( out minval, out maxval );
*     \endcode
*     \else
*     \code
*       double minval, maxval;
*       SbBool ok = pVolumeData->getMinMax( minval, maxval );
*     \endcode
*     \endoivnetdoc
*     Note: These methods might force VolumeViz to load the entire data set if the
*     volume reader does not respond to the getMinMax query. For example in an LDM 
*     format data set, the min and max values are stored in the LDM header and the
*     query is very fast. For other data sets VolumeViz may be forced to load the 
*     entire data set to compute the min and max values. For a large data set this 
*     may take a long time. 
*
*   - Other: @BR
*     Many other volume properties can be specified using fields of SoDataSet and
*     SoVolumeData.  For example, the way the volume is stored on the GPU depends 
*     on the #storageHint field. (If an SoVolumeIsosurface or an 
*     SoVolumeRenderingQuality node is present, this field is ignored and TEX3D is
*     always used.)  The #ldmResourceParameters field contains an
*     SoLDMResourceParameters object that controls, for example, the amount of
*     CPU memory and GPU memory that the volume can use.
*
*  @B Volume visualization: @b
*
*     Basic volume visualization tools:
*   - The volume data is specified by an SoVolumeData node.  (Multiple data sets
*     can also be specified.  See the next section.)
*
*   - The region of voxels to be rendered (the "region of interest") can be
*     specified using an SoROI node.  This node limits the extent of all
*     rendering nodes including slices.
*
*   - The range of data values to be mapped into the transfer function can be
*     specified using an SoDataRange node.
*
*   - The color and opacity associated with each data value can be specified
*     using an SoTransferFunction node.
*
*   - The base material properties of the voxels, e.g. emissive and specular
*     color, can be specified using an SoMaterial node.
*
*   - Advanced rendering effects, e.g. lighting, and image quality settings
*     can be specified using an SoVolumeRenderingQuality node.
*     (You should enable lighting using this node, not the lighting field of
*     SoVolumeRender.)  Shadows can be enabled using an SoShadowGroup node.
*
*   - Many parameters related to memory management and performance optimizations
*     can be specified using SoLDMGlobalResourceParameters and SoLDMResourceParameters.
*
*   - VolumeViz provides many different ways of visualizing volume data, including:
*     - SoOrthoSlice: Renders a single axis aligned slice.
*     - SoObliqueSlice: Renders a single arbitrarily aligned slice.
*     - SoFenceSlice: Renders a "strip" of connected oblique slices.
*     - SoVolumeSkin: Renders the faces of the current Region of Interest (see SoROI).
*       Effectively a set of ortho slices.
*     - SoVolumeIndexedFaceSet (etc): Renders a "slice" made up of arbitrary
*       geometry, for example a curved or cylindrical slice.
*     - SoVolumeIsosurface: Renders the isosurface defined by the specified data
*       value. (This is done completely on the GPU. To get the geometry of an
*       isosurface back on the CPU see the MeshViz extension.)
*     - SoVolumeRender: Renders the volume using direct volume rendering.
*
*   Advanced volume visualization:
*   - Custom transfer functions, as well as custom rendering effects, can be
*     specified using an SoVolumeShader node and a GLSL shader program.
*     VolumeViz provides a framework of prebuilt shader functions for commonly
*     used calculations and effects.
*
*   - Clipping:
*       - Volume visualizations can be clipped against arbitrary polygon geometry
*         using an SoVolumeClippingGroup node.
*       - Volume visualizations can be clipping against a surface defined by a "height 
*         field" (for example a seismic horizon) using an SoUniformGridClipping node.
*       - Volume visualizations can be clipped against arbitrary voxel regions using
*         an SoVolumeMask node.  SoVolumeMask also allows applying different transfer
*         functions to different regions and other powerful features.
*
*   - Volume data can transformed "on the fly" at several stages in the pipeline:
*       - The SoLDMDataTransform class (see the dataTransform field of SoDataSet) 
*         applies a computation to each LDM data tile requested from the volume reader 
*         before the tile is stored in system memory.
*       - The SoVolumeTransform node applies a computation to LDM data tiles just 
*         before they are sent to the GPU. 
*         Both mechanisms can be used to create multiple data sets from a single data set.
*
*   - Volume computations can take advantage of the Open Inventor computing 
*     framework to manage data, devices and algorithms on the CPU and GPU (using
*     CUDA or OpenCL).  See SoDevice, SoBufferObject, SoArithmetic, etc.
*
*  @B Multiple data sets: @b
*
*   Multiple SoVolumeData nodes can be inserted in a scene graph and combined together to do render
*   compositing (SoVolumeShader) or data compositing (SoDataCompositor).
*   This feature is only supported in LDM mode and you must use an SoMultiDataSeparator
*   as the parent of the nodes that will be composited.
*
*   Render compositing is a way of combining multiple volumes at render time
*   using a fragment shader. The volumes can each have their own transfer function
*   or they can all use the same one.
*   Render compositing can be used, for example, to realize
*   RGB blending with a different input for each channel (multi-channel rendering).
*   The number of volumes to compose is limited by the number of OpenGL texture units supported by the
*   graphics board. This number is returned by the #getMaxNumDataSets function.
*
*   Data compositing allows you to combine multiple volume data sets
*   (see SoDataCompositor) or
*   to transform a single data set in memory (see #setLDMDataTransformFunction()) instead of having to store
*   the combined data sets on disk.
*   For example, it can be used to visualize the result of the difference between two data sets.
*   There is no limit on the number of volumes that can be composed.
*
*   The #dataSetId field is used to differentiate SoVolumeData nodes when doing
*   render or data compositing.
*
*   Some rules must be observed when doing render or data compositing:
*
*   - Each SoVolumeData node must have a unique #dataSetId. @BR
*
*   - All the SoVolumeData nodes to be composited must have the same volume dimensions
*     (number of voxels in X, Y, and Z), tile size and tile overlap. @BR
*
*   - All the SoVolumeData nodes to be composited, as well as the compositing node
*     and rendering node, must be under an SoMultiDataSeparator node.
*
*   - Each SoVolumeData node has its own resource settings (see field #ldmResourceParameters).
*     The resources required for the composition are the sum of the resources for
*     all of the SoVolumeData nodes involved. @BR
*
*   - A volume data node used in a data compositing scheme should not be inserted multiple
*     times in the scene graph. Use another volume data node pointing to the same file.
*
*   When using a fragment shader to do render compositing, texture coordinates can be retrieved from
*   texture unit 0 (texture coordinates are sent using glTexCoord function).
*   To minimize the number of texture units needed, all the transfer functions (see
*   SoTransferFunction) for the volumes to be composited are stored in a single 2D texture.
*   By default this texture is loaded in texture unit 0.  However this default behavior can be
*   changed through SoPreferences using the environment variable IVVR_TF_TEX_UNIT.
*   Each volume's data is loaded in the texture unit specified by its #dataSetId.  Therefore
*   do not set #dataSetId to the texture unit used to store the transfer functions.
*
* @B RGBA Data @b
*
*   Voxels in an RGBA volume are UNSIGNED_INT32, containing 8 bits each of Red, Green, Blue
*   and Alpha. All rendering nodes (slices, volume rendering, etc) work with RGBA volumes.
*   Region of Interest, clipping and other features also work with RGBA volumes.  However
*   because the volume already specifies the colors to be used for rendering, the data
*   range and transfer function are ignored.  Lighting works with RGBA volumes using
*   gradient vectors computed from the luminance value of the voxels.
*
* @B Supported file formats: @b
*
*   @TABLE_1B
*   @TR @B File extension @b  @TD @B Reader class @b     @TD @B Description @b
*   @TR .am                   @TD SoVRAmFileReader       @TD Avizo Mesh file format
*   @TR .dc3, .dic, .dicom    @TD SoVRDicomFileReader    @TD DICOM file format
*   @TR .fld                  @TD SoVRAvsFileReader      @TD AVS field file format
*   @TR .lda or .ldm          @TD SoVRLdmFileReader      @TD LDM file format
*   @TR .sgy or .segy         @TD SoVRSegyFileReader     @TD SEG Y rev 1 file format
*   @TR .vol                  @TD SoVRVolFileReader      @TD Vol file format
*   @TR .vox                  @TD SoVRVoxFileReader      @TD Vox file format
*   @TR .lst                  @TD SoVRRasterStackReader  @TD Lst file format
*   @TABLE_END
*
*   File format notes:
*   - Avizo mesh @BR
*     Avizo mesh is a general purpose file format that can contain many different kinds of data. The
*     VolumeViz file reader can load Avizo mesh files containing a 3-dimensional "Lattice" data object
*     with uniform coordinates and any data type.  See SoVRAmFileReader.
*
*   - AVS field @BR
*     AVS field is a general purpose file format that can contain many different kinds of data. The
*     VolumeViz file reader can load AVS field files containing 3-dimensional, uniform data of type
*     "byte". See SoVRAvsFileReader.
*
*   - DICOM @BR
*     A widely used format for storing medical image data (CT, MRI, etc), defined by the National
*     Electrical Manufacturers Association (NEMA) (medical.nema.org). See SoVRDicomFileReader
*
*   - LDM @BR
*     LDM is a format defined by VSG for storing hierarchical multi-resolution volume data.
*     VolumeViz includes a utility program that can convert any other format supported by VolumeViz
*     into this format (see SoVolumeConverter). Preprocessing volume data into this format provides
*     the maximum benefits from the VolumeViz large data management (LDM) features. See SoVRLdmFileReader.
*
*   - SEGY @BR
*     A widely used format for storing seismic trace data, defined by the Society of Exploration
*     Geophysicists publication "Digital Tape Standards" (www.seg.org). The VolumeViz reader
*     supports all sizes of integer and float data, and can correctly determine the number of
*     samples per trace in many cases. However the reader also has many options to adapt to
*     differences in SEGY file headers.  See SoVRSegyFileReader.
*
*   - VOL @BR
*     A simple volume interchange format (see "Introduction to Volume Rendering", Lichtenbelt,
*     Crane, Naqvi, 1998). The VolumeViz reader can load files containing 8- or 16-bit voxels.
*     See SoVRVolFileReader.
*
*   - VOX @BR
*     A volume interchange format defined by TeraRecon Inc. (www.terarecon.com). The VolumeViz
*     reader can load "Vox1999a" files containing 8- or 16-bit voxels (first volume only).
*     See SOVRVoxFileReader.
*
*   - LST @BR
*     A simple format for loading a stack of images.
*     Specify the names of the image files in a .lst file. See SoVRRasterStackReader.
*
* @FILE_FORMAT_DEFAULT
*    VolumeData {
*    @TABLE_FILE_FORMAT
*       @TR fileName                   @TD ""
*       @TR storageHint                @TD AUTO
*       @TR usePalettedTexture         @TD TRUE
*       @TR texturePrecision           @TD 8
*       @TR useSharedPalettedTexture   @TD TRUE
*       @TR useCompressedTexture       @TD TRUE
*       @TR useExtendedData            @TD FALSE
*       @TR dataSetId                  @TD 1
*       @TR data                       @TD NODATA 0 0 0 UBYTE 8
*       @TR dataRGBA                   @TD FALSE 
*    @TABLE_END
*    }
*
* @ACTION_BEHAVIOR
* SoCallbackAction,
* SoGLRenderAction,
* SoGetBoundingBoxAction,
* SoPickAction,
* SoWriteAction @BR
* Sets volume data parameters in the traversal state.
*
* @SEE_ALSO
*    SoVolumeRender,
*    SoOrthoSlice,
*    SoObliqueSlice,
*    SoVolumeReader,
*    SoVolumeSkin,
*    SoDataCompositor,
*    SoLDMGlobalResourceParameters,
*    SoLDMResourceParameters
*
*/


//LDM
//   @B LDM mode and paging mode @b @BR
//   Some methods can be used exclusively with LDM mode, others exclusively with
//    paging mode, and a few can be used in either mode.
//    With the exception of #getMinMax, #getHistogram and #updateRegions, which are supported
//    in both paging mode and LDM mode,
//    any methods that are not called using LDMDataAccess,
//    LDMManagerAccess, or  LDMResourceParameter are used for paging mode only.
//    You can use the methods
//    #setLDM and #setPaging to set LDM mode and paging mode respectively. These modes
//    are mutually exclusive: it is not possible to have both in effect at the same time.
//    In VolumeViz 5, LDM mode is set by default.
class VOLUMEVIZ_API SoVolumeData : public SoDataSet, public SoVolumeRendering
{
  SO_NODE_HEADER( SoVolumeData );

public:
  using SoDataSet::getTexData;

  //compatibility issues:
  typedef SoLDMDataAccess        LDMDataAccess;
  typedef SoLDMMediator::LDMManagerAccess     LDMManagerAccess;
  typedef ::LDMResourceParameter LDMResourceParameter;

  /**
  * Constructor.
  */
  SoVolumeData();

  /**
   * @deprecated Use SoDataSet::#dataSetId instead.
   * @DEPRECATED_SINCE_OIV 7.0
   */
#ifndef HIDDEN_FROM_DOC
  SoSFUShort volumeDataId;
#else
  SoDEPRECATED SoSFUShort volumeDataId;
#endif

  /**
  * Indicates how the data is stored in Open Inventor/OpenGL.
  * Use enum #StorageHint. Default is AUTO.
  *
  * There is a hierarchy of rendering techniques, as follows:
  *
  * - 3D textures (TEX3D) (best)
  *
  * - 2D textures (TEX2D)
  *
  * - Memory (MEMORY) (worst)
  *
  * AUTO tells the system to use the best mechanism available depending on the
  * platform capabilities. First, it tries to use 3D textures. If that fails,
  * it will use 2D textures.
  *
  * If the storage is MEMORY, then the volume data is kept only in main memory.
  * SoOrthoSlice and SoObliqueSlice will still render, but SoVolumeRender will
  * not.
  *
  * For #storageHint values such as TEX3D or TEX2D, Open Inventor tries
  * to use the requested technique. If requested technique fails, it will try to use
  * the other texturing techniques, in descending order.
  *
  * For example, if 3D texturing is requested, but no 3D texturing support is
  * available or if the system is not able to load the 3D texture, Open Inventor
  * will use 2D textures instead.
  *
  * 3D textures are usually slower than 2D textures. However, 3D textures use
  * less texture memory (because three sets of 2D textures must be loaded
  * for each brick) and generally provide better image quality.
  *
  * Note for AUTO and TEX3D rendering: Some low-end boards report that 3D textures are
  * supported, but in fact the rendering is not hardware accelerated and is very
  * slow.  VolumeViz is able to detect this situation (and use 2D textures instead)
  * in most, but not all cases.  If necessary, set storageHint to TEX2D explicitly.
  *
  */
  SoSFEnum	 storageHint;

  /** Storage Hints mode */
  enum StorageHint {
    /** Auto (Default) */
    AUTO,
    /** Multi-texture 2D */
    TEX2D_MULTI,
    /** (synonym for TEXT2D_MULTI) */
    TEX2D = TEX2D_MULTI,
    /** Texture 3D */
    TEX3D,
    /** In memory */
    MEMORY,
#ifndef HIDDEN_FROM_DOC
    /** kept from 7.2, only for .NET binary compatibility issues */
    VOLUMEPRO,
    /** Single Texture 2D */
    TEX2D_SINGLE
#endif // HIDDEN_FROM_DOC
  };


 /**
  * Controls use of color index textures to load volume data onto the graphics
  * board (the name is historical). Default is TRUE meaning to use color index
  * textures. Normally this is done using programmable shaders. On older hardware
  * it may be done using the OpenGL paletted texture extension or texture color
  * table extension. FALSE means to use RGBA textures. A significant advantage of
  *color index textures is that they conserve texture memory space. For example,
  * an 8-bit color index texture uses about a quarter the memory of a 32-bit RGBA
  * texture with the same width and height. Indexed textures are also preferred
  * because they allow dynamic modification of the transfer function (colormap).
  * The number of possible colors depends on the value of the #texturePrecision
  * field.
  * 
  * @NOTES: If current data are RGBA then this field is ignored and RGBA Texture 
  * will be used in any case.
  */
  SoSFBool   usePalettedTexture;


  /**
  * Note: On graphics boards that support programmable shaders, this field is ignored.@BR
  * @BR
  * Controls use of the OpenGL shared texture palette extension (if available). FALSE
  * means don't use it. Default is TRUE. On machines that support paletted textures,
  * using a shared palette conserves texture memory because a single palette (color map)
  * can be used for all the textures.
  */
  SoSFBool   useSharedPalettedTexture;

  /**
   *
   * If TRUE, VolumeViz stores an additional copy of each loaded tile.
   * There is an additional memory cost but the performance of SoOrthoSlice roaming will
   * be roughly the same along each axis.
   *
   * @FIELD_SINCE_OIV 6.0
   */
  SoSFBool   useExtendedData;

  /**
   * Specifies the volume data, including dimensions, data type and number of significant bits.
   * Use this field if your volume data is already loaded into memory in a contiguous block
   * of memory.  Otherwise use the #fileName field or the #setReader method.
   *
   * The @B numSigBits @b parameter of SoSFArray3D::setValue indicates the number of bits really
   * used for each value.
   * If it equals 0, that means to use all bits, e.g., 8 bits if @B type @b = UNSIGNED_BYTE,
   * 16 bits if @B type @b = UNSIGNED_SHORT and so on. This parameter is useful particularly when
   * textures are loaded in paletted mode. Currently most hardware supports only 8 bits,
   * so VolumeViz must discard the least significant bits. For example if @B type @b is
   * UNSIGNED_SHORT, by default in paletted mode VolumeViz will discard the lowest 8 bits. If
   * you specify @B numSigBits @b = 10, VolumeViz will discard only the lowest 2 bits.
   *
   * Calling SoSFArray3D::setValue with a CopyPolicy set to NO_COPY is equivalent to calling the deprecated
   * SoVolumeData::setValue method.
   * @FIELD_SINCE_OIV 7.1
   */
  SoSFArray3D data;

  /**
   * Contains TRUE if the volume contains RGBA values rather than scalar values. @BR
   * This field is set automatically by volume readers. If the application is setting
   * an in-memory volume into the #data field, the #data field must be set to
   * UNSIGNED_INT32 format and the #dataRGBA field must be set to TRUE.
   * Default is FALSE.
   * @FIELD_SINCE_OIV 9.0
   */
  SoSFBool dataRGBA;

  /**
   * @deprecated Use the field #data: data.getSize()
   * @DEPRECATED_SINCE_OIV 8.0
   */
  SoDEPRECATED SbVec3i32 getDimension() { return SoDataSet::getDimension(); }

  /**
   * @deprecated Use the field #extent: extent.setValue(size)
   * @DEPRECATED_SINCE_OIV 7.0
   */
  SoDEPRECATED void setVolumeSize( const SbBox3f &size );

  /**
   * @deprecated Use the field #extent: extent.getValue()
   * @DEPRECATED_SINCE_OIV 7.0
   */
  SoDEPRECATED const SbBox3f& getVolumeSize();

  /**
   * @deprecated Please use the field #data: data.setValue()
   *
   * Note that by default the contents of the #data field will be written into the
   * output file if an SoWriteAction is applied to the scene graph (this was not
   * the case when using setVolumeData).  This may produce an extremely large file,
   * particularly if using the relatively verbose ASCII file format.  To avoid
   * writing data into the file see the method SoSFArray3D::setNeverWrite.
   *
   * @DEPRECATED_SINCE_OIV 7.0
   */
  SoDEPRECATED void setVolumeData( const SbVec3i32 &dimension, SoMemoryObject* data, SoDataSet::DataType type=UNSIGNED_BYTE, int numSignificantBits = 0 );

  /**
   * @deprecated Please use the field #data: data.setValue()
   * @DEPRECATED_SINCE_OIV 7.0
   * [OIV-WRAPPER-ARG IN,ARRAY,IN,IN]
   */
  SoDEPRECATED void setVolumeData( const SbVec3i32 &dimension, void *data, SoDataSet::DataType type=UNSIGNED_BYTE, int numSignificantBits = 0 );

  /**
   * @deprecated Use the field #data: data.getValue()
   * @DEPRECATED_SINCE_OIV 7.0
   */
  SoDEPRECATED SbBool getVolumeData( SbVec3i32 &dimension, void *&data, SoDataSet::DataType &type, int *numSignificantBits = NULL );

  /**
  * @deprecated Please use the int64 or double version.
  *
  * Returns @B min @b and @B max @b values of the volume data. Returns FALSE if
  * the requested data is not available (for example, if no data volume exists).
  *
  * NOTE: This method might force VolumeViz to load the @I entire @i data set if
  * the volume reader does not respond to the getMinMax query. Normally for an
  * LDM format data set, the min and max values are stored in the LDM header.
  * For a non-LDM data set, if a filename and/or reader have been specified and
  * the data set has not yet been loaded, VolumeViz will load the entire data set to
  * compute the min and max values. For a large data set this may take a long time.
  *
  * @DEPRECATED_SINCE_OIV 7.0
  * [OIVJAVA-WRAPPER NAME{getIntMinMax}]
  */
  SoDEPRECATED SbBool getMinMax( int &min, int &max);

  /**
  * Returns @B min @b and @B max @b values of the volume data. Returns FALSE if
  * the requested data is not available (for example, if no data volume exists).
  *
  * NOTE: This method might force VolumeViz to load the @I entire @i data set if
  * the volume reader does not respond to the getMinMax query. Normally for an
  * LDM format data set, the min and max values are stored in the LDM header.
  * For a non-LDM data set, if a filename and/or reader have been specified and
  * the data set has not yet been loaded, VolumeViz will load the entire data set to
  * compute the min and max values. For a large data set this may take a long time.
  */
  virtual SbBool getMinMax( int64_t &min, int64_t &max);

  /**
  * Returns @B min @b and @B max @b values of the volume data. Returns FALSE if
  * the requested data is not available (for example, if no data volume exists).
  *
  * NOTE: This method might force VolumeViz to load the @I entire @i data set if
  * the volume reader does not respond to the getMinMax query. Normally for an
  * LDM format data set, the min and max values are stored in the LDM header.
  * For a non-LDM data set, if a filename and/or reader have been specified and
  * the data set has not yet been loaded, VolumeViz will load the entire data set to
  * compute the min and max values. For a large data set this may take a long time.
  * [OIVJAVA-WRAPPER NAME{getDoubleMinMax}]
  */
  virtual SbBool getMinMax( double &min, double &max);

  /**
  * Deprecated.  Please use the int64 method.
  *
  * Returns the histogram of the volume data. Returns FALSE if the requested data is
  * not available.
  *
  * NOTE: This method might force VolumeViz to load the @I entire @i data set if
  * the volume reader does not respond to the getHistogram query. Normally for an
  * LDM format data set, the histogram values are stored in the LDM header.
  * For a non-LDM data set, if a filename and/or reader have been specified and
  * the data set has not yet been loaded, VolumeViz will load the entire data set to
  * compute these values. For a large data set this may take a long time.
  * [OIV-WRAPPER-NOT-WRAP]
  */
  SbBool getHistogram ( int &length, int* &histogram);

  /**
  * Returns the histogram of the volume data. Returns FALSE if the requested data is
  * not available.
  *
  * NOTE: This method might force VolumeViz to load the @I entire @i data set if
  * the volume reader does not respond to the getHistogram query. Normally for an
  * LDM format data set, the histogram values are stored in the LDM header.
  * For a non-LDM data set, if a filename and/or reader have been specified and
  * the data set has not yet been loaded, VolumeViz will load the entire data set to
  * compute these values. For a large data set this may take a long time.
  * [OIV-WRAPPER-CUSTOM-CODE]
  */
  //LDM
  // This method must be used for LDM files and can also be used for other file formats.

  SbBool getHistogram( int &length, int64_t* &histogram);

  /**
  * Extracts the data volume defined by @B region@b. If a reader is
  * specified, the original volume data is not loaded.
  */
  SoVolumeData *subSetting( const SbBox3i32 &region );

  /**
  * Updates regions of the volume that have been modified.
  * This method notifies VolumeViz that voxels in the specified regions
  * have been modified by the application and textures may need to be
  * recreated.  Only bricks currently needed for rendering some volume
  * geometry, e.g., a slice or subvolume, are immediately updated.
  * [OIV-WRAPPER-ARG ARRAY,NO_WRAP{(region != NULL? region->get_Length(): 0)}]
  */
  void updateRegions(const SbBox3i32 *region, int num_regions);

  /**
  * Reloads textures corresponding to the given tile IDs. Only supported in LDM mode.
  * Useful for a bottom-up approach (a custom tile manager starts loading full resolution
  * and returns fake data for lower resolution. Once the real low resolution data is in memory,
  * update).
  * [OIV-WRAPPER-ARG ARRAY,NO_WRAP{(tiles != NULL? tiles->get_Length(): 0)}]
  */
  void updateTilesInTextureMemory(SoLDMTileID* tiles, int numTiles);

  #ifdef OIV_NET_DOC
 /**
  * This function will load all bricks into system memory that are wholly
  * or partially contained within each of the specified regions.  This
  * can be used to pre-load volume data that will be needed for rendering
  * later.
  *
  * In addition, if @B state @b is not NULL, it will create the corresponding
  * textures and load them in texture memory.  Likewise this can be used
  * to pre-load textures that will be needed for rendering later.  In this
  * case it must only be called when a valid OpenGL context has been made current
  * (generally a context is current if there is an Open Inventor window and at
  * least one render has been done).
  * Normally, VolumeViz will only load bricks that are currently needed for rendering
  * some volume geometry, e.g., a slice or a subvolume. This method allows the
  * application to force other bricks to be loaded, which may be useful to reduce
  * the delay when a new brick is needed to render some volume geometry.
  * [OIV-WRAPPER-ARG ARRAY,NO_WRAP{(region != NULL? region->get_Length(): 0)},IN,IN]
  */
 #else
  /**
  * This function will load all bricks into system memory that are wholly
  * or partially contained within each of the specified regions.  This
  * can be used to pre-load volume data that will be needed for rendering
  * later.
  *
  * In addition, if @B state @b is not NULL, it will create the corresponding
  * textures and load them in texture memory.  Likewise this can be used
  * to pre-load textures that will be needed for rendering later.  In this
  * case it must only be called when a valid OpenGL context has been made current
  * (generally a context is current if there is an Open Inventor window and at
  * least one render has been done).
  * State is normally obtained by querying the current SoGLRenderAction, for
  * example: @BR
  * SoState *state = pViewer->getGLRenderAction()->getState();
  *
  * Normally, VolumeViz will only load bricks that are currently needed for rendering
  * some volume geometry, e.g., a slice or a subvolume. This method allows the
  * application to force other bricks to be loaded, which may be useful to reduce
  * the delay when a new brick is needed to render some volume geometry.
  * [OIV-WRAPPER-ARG ARRAY,NO_WRAP{(region != NULL? region->get_Length(): 0)},IN,IN]
  */
#endif


//LDM
// Note: This method is not supported in LDM mode.

  void loadRegions(const SbBox3i32 * region, int num_regions,SoState* state,SoTransferFunction* transFunc);

  #ifdef OIV_NET_DOC
 /**
  *
  * Turns LDM mode on or off. Default is TRUE. @BR
  * If true, paging mode is turned off if it is on.
  * If LDM mode is off and paging mode is off (#SetPaging),
  * nonLDM and non-paging mode is used (Since OIV 8, this mode must
  * be used instead of paging if LDM is not needed). @BR
  * NOTE: LDM mode does not work with multipipe rendering. @BR
  * NOTE: If you want to do offscreen rendering in LDM mode, you must use
  * SoOffscreen:.SetShareContext(myViewer.GetShareContext()).
  */
 #else
  /**
  * Turns LDM mode on or off. Default is TRUE. @BR
  * If TRUE, paging mode is turned off if it is on.
  * If LDM mode is off and paging mode is off (#setPaging),
  * nonLDM and non-paging mode is used (Since OIV 8, this mode must
  * be used instead of paging if LDM is not needed). @BR
  * NOTE: LDM mode does not work with multipipe rendering. @BR
  * NOTE: If you want to do offscreen rendering in LDM mode, you must use
  * SoOffscreen::setShareContext(myViewer->getShareContext()).
  */
#endif
  virtual void   setLDM(SbBool);

  /**
  * Turns paging mode on or off.  Default is FALSE. @BR
  * Since VolumeViz 5, LDM mode is on by default.
  * To be compatible with version 4 you can either turn LDM mode off
  * by calling setPaging(TRUE) or set the IVVR_40_COMPAT variable to 1
  * in the configuration file (see SoPreferences). @BR
  * Note: In paging mode, multidata (for example SoDataCompositor) is not supported.
  * @DEPRECATED_SINCE_OIV 8.0: Use setLDM(FALSE) for similar functionalities.
  */
//LDM
// If TRUE, LDM mode is turned off if it is currently on.
// If LDM mode is off (#setLDM) and paging mode is off,
// nonLDM and non-paging mode is used (VolumeViz 3 behavior).

  void   setPaging(SbBool);

  /**
   *
   * Returns TRUE if paging is on, FALSE if off.
   */
  SbBool isPaging();

  ////////////////////////////////////////////////////////////////////////////////////////////////
  // deprecated methods
  //

  /** @deprecated No longer used. Use setVolumeData( const SbVec3i32&, void*, SoDataSet::DataType, int ).
   * @DEPRECATED_SINCE_OIV 6.0
   * [OIV-WRAPPER-ARG IN,ARRAY,IN,IN]
   */
  SoDEPRECATED void setVolumeData( const SbVec3s &dimension, void *data,
                                   SoDataSet::DataType type=UNSIGNED_BYTE,
                                   int numSignificantBits = 0 );

  /** @deprecated No longer used. Use field #data: data.getValue()
   * @DEPRECATED_SINCE_OIV 7.0
   */
  SoDEPRECATED SbBool getVolumeData( SbVec3s &dimension, void *&data,
                                     SoDataSet::DataType &type, int *numSignificantBits = NULL );

  /** @deprecated No longer used. Use subSetting( const SbBox3i32& region ).
   * @DEPRECATED_SINCE_OIV 6.0
   */
  SoDEPRECATED SoVolumeData* subSetting( const SbBox3s& region )
  {
    SbBox3i32 regionI32( region.getMin()[0], region.getMin()[1], region.getMin()[2],
                         region.getMax()[0], region.getMax()[1], region.getMax()[2] );
    return subSetting( regionI32 );
  };

  /** @deprecated No longer used. Use updateRegions( const SbBox3i32*, int ).
   * @DEPRECATED_SINCE_OIV 6.0
   * [OIV-WRAPPER-ARG ARRAY,NO_WRAP{region->Length}]
   */
  SoDEPRECATED void updateRegions( const SbBox3s *region, int num_regions )
  {
    if (num_regions <= 0) return;
    SbBox3i32 *regionI32 = new SbBox3i32 [num_regions];
    for (int i = 0; i < num_regions; i++)
      regionI32[i].setBounds( region[i].getMin()[0], region[i].getMin()[1], region[i].getMin()[2],
                              region[i].getMax()[0], region[i].getMax()[1], region[i].getMax()[2] );
    updateRegions( regionI32, num_regions );
    delete [] regionI32;
  };

  /** @deprecated No longer used. Use loadRegions( const SbBox3i32*, int, SoState*, SoTransferFunction* ).
   * @DEPRECATED_SINCE_OIV 6.0
   * [OIV-WRAPPER-ARG ARRAY,NO_WRAP{region->Length},IN,IN]
   */
  SoDEPRECATED void loadRegions( const SbBox3s *region, int num_regions, SoState* state, SoTransferFunction* transFunc )
  {
    if (num_regions <= 0) return;
    SbBox3i32 *regionI32 = new SbBox3i32 [num_regions];
    for (int i = 0; i < num_regions; i++)
      regionI32[i].setBounds( region[i].getMin()[0], region[i].getMin()[1], region[i].getMin()[2],
                              region[i].getMax()[0], region[i].getMax()[1], region[i].getMax()[2] );
    loadRegions( regionI32, num_regions, state, transFunc );
    delete [] regionI32;
  };

  /** @deprecated No longer used. Use setSubSamplingLevel(const SbVec3i32&, const SbVec3i32&).
   * @DEPRECATED_SINCE_OIV 6.0
   */
  SoDEPRECATED void setSubSamplingLevel(const SbVec3s& ROISampling, const SbVec3s& secondarySampling)
  {
    SbVec3i32 ROISamplingI32( ROISampling[0], ROISampling[1], ROISampling[2] );
    SbVec3i32 secondarySamplingI32( secondarySampling[0], secondarySampling[1], secondarySampling[2] );
    setSubSamplingLevel( ROISamplingI32, secondarySamplingI32 );
  };

  /** @deprecated No longer used. Use getSubSamplingLevel(SbVec3i32 &, SbVec3i32 &).
   *  @DEPRECATED_SINCE_OIV 6.0
   * [OIVJAVA-WRAPPER NO_WRAP]
   */
  SoDEPRECATED void getSubSamplingLevel(SbVec3s &ROISampling, SbVec3s &secondarySampling)
  {
    SbVec3i32 ROISamplingI32;
    SbVec3i32 secondarySamplingI32;
    getSubSamplingLevel( ROISamplingI32, secondarySamplingI32 );
    ROISampling.setValue( (short)ROISamplingI32[0], (short)ROISamplingI32[1], (short)ROISamplingI32[2] );
    secondarySampling.setValue( (short)secondarySamplingI32[0], (short)secondarySamplingI32[1], (short)secondarySamplingI32[2] );
  };

  //
  // end deprecated methods
  ////////////////////////////////////////////////////////////////////////////////////////////////

  ///////////////////////////// OBSOLETE PART/////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  // Memory Control Parameters section (obsolete) ////////////////////////////////

  /**
  * Specifies the maximum texture memory size to use in mega texels. 64 is the default.
  */
  void setTexMemorySize(int size);

  /**
   * Returns the maximum texture memory size to use in mega texels.
   */
  int getTexMemorySize() { return m_pagingMaxMemory; }

  /**
  * Specifies page size in X, Y, and Z direction (uniform). Must be 2^n for some integer n. The default is 128x128x128.
  */
  void setPageSize(int size);

  /**
  * Specifies page size in X, Y, and Z direction. Must be 2^n for some integer n. The default is 128x128x128.
  */
  void setPageSize(SbVec3i32& size);
  /**
  * @deprecated Specifies page size in X, Y, and Z direction. Must be 2^n for some integer n. The default is 128x128x128.
  *  @DEPRECATED_SINCE_OIV 6.0
  */
  SoDEPRECATED void setPageSize(SbVec3s& size) {
    SbVec3i32 size_i32(size[0],size[1],size[2]);
    setPageSize(size_i32);
  };

  /**
   * Returns the page size in X, Y, and Z direction.
   */
  SbVec3i32 getPageSize();

  /**
   * Sub sampling method mode
   */
  enum SubMethod {
    /** Nearest */
    NEAREST,
    /** Max */
    MAX,
    /** Average */
    AVERAGE
  };

  /**
   * Over sampling method mode
   */
  enum OverMethod {
    /** None */
    NONE,
    /** Constant */
    CONSTANT,
    /** Linear */
    LINEAR,
    /** Cubic */
    CUBIC
  };

  /**
  * Re-samples the volume down to or up to the given @B dimension @b using
  * the sub-sampling method #SubMethod() and the over-sampling method
  * #OverMethod(). If a reader is specified, the original volume data is not
  * loaded.
  *
  * Over-sampling is not yet implemented. NONE (default) indicates that no
  * over-sampling is performed. For example if the original dimension is 256x256x64
  * and the reSampling dimension is 128x128x128, the result is a volume of dimension
  * 128x128x64.
  */
  SoVolumeData *reSampling( const SbVec3i32 &dimension, SoVolumeData::SubMethod subMethod, SoVolumeData::OverMethod = NONE);

  /**
  * Specifies if automatic subsampling and unsampling is allowed.
  * If enabled and according to enableAutoSubSampling() and enableAutoUnSampling(),
  * VolumeViz automatically subsamples or unsamples so that all textures fit into the texture
  * memory specified by setTexMemorySize().
  * The default is TRUE.
  */
  void enableSubSampling(SbBool enable);

  /**
  * Returns TRUE if automatic subsampling is allowed.
  */
  SbBool isSubSamplingEnabled() { return m_pagingSubSampling; }

  /**
  * Specifies if automatic subsampling is allowed. See enableSubSampling().
  * The default is TRUE.
  */
  void enableAutoSubSampling(SbBool enable);

  /**
   * Returns TRUE if automatic subsampling is allowed.
   */
  SbBool isAutoSubSamplingEnabled() { return m_pagingAutoSubSampling; }

  /**
  * Specifies if automatic unsampling is allowed. See #enableSubSampling().
  * The default is FALSE.
  */
  void enableAutoUnSampling(SbBool enable);

  /**
   * Returns TRUE if automatic unsampling is allowed.
   */
  SbBool isAutoUnSamplingEnabled() { return m_pagingAutoUnSampling; }

  /**
  * Forces VolumeViz to unsample in order to get the best quality by
  * using the maximum texture memory.
  */
  void unSample();

  /**
  * Specifies the subsampling method used when automatic subsampling is activated.
  * See enableAutoSubSampling().
  * Depending on the kind of data, it may be useful to use a specific method.
  * The default is NEAREST.
  */
  void setSubSamplingMethod(SubMethod method);

  /**
  * Forces VolumeViz to subsample at given values even if automatic subsampling is disabled.
  * See enableAutoSubSampling().
  * @B ROISampling @b corresponds to the sampling values used for the Region Of Interest.
  * @B secondarySampling @b corresponds to the sampling values used for the rest of the
  * volume (not yet used).
  * Values are given in powers of two. For example if @B ROISampling @b is set to (1,1,0),
  * the ROI will be subsampled using the subsampling factors (2,2,1). In this case the Z
  * axis will not be subsampled.
  */
  void setSubSamplingLevel(const SbVec3i32& ROISampling, const SbVec3i32& secondarySampling);

  /**
   * Returns values used to subsample at given values even when automatic subsampling is disabled.
   * See enableAutoSubSampling().
   */
  void getSubSamplingLevel(SbVec3i32 &ROISampling, SbVec3i32 &secondarySampling);

  /**
   * Converts the specified point in voxel coordinates to geometric coordinates.
   * The left bottom coordinate of the voxel is returned.
   */
  virtual SbVec3f voxelToXYZ(const SbVec3f &dataPosition) const;

  /**
   * Converts the specified box in voxel coordinates to geometric coordinates.
   */
  virtual SbBox3f voxelToXYZ(const SbBox3f& box) const;

  /**
   * Converts the specified point in geometric coordinates to voxel coordinates.
   */
  virtual SbVec3f XYZToVoxel(const SbVec3f &dataPosition);

  /**
   * Converts the specified box in geometric coordinates to voxel coordinates.
   */
  virtual SbBox3f XYZToVoxel(const SbBox3f &xyzBox);

   /**
    * @deprecated Use SoDataSet::getMaxNumDataSets.
    * @DEPRECATED_SINCE_OIV 7.0
    */
  SoDEPRECATED static int getMaxNumVolumes() ;

  /**
   * Force data to be considered as RGBA values. @BR
   * Note that this call should be used only when setting data from memory
   * through the #data field and the data format must be UNSIGNED_INT32.
   */
  void setRGBAData(const bool flag);

  SoINTERNAL public:

  /** Return voxel size of the volume data */
  SbVec3f getVoxelSize() const;

  static SoVolumeReader *newAppropriateReader( const SbString& filename);
  virtual void updateTile( const SbBox3i32 &region, const SoLDMTileID& tileId );
  virtual void drawTilesInMainMemory(SoState *state);

  enum Cmd{
    CREATE_NODE,
    UPDATE_REGIONS,
    SET_LDM,
    SET_PAGING
  };

  /**
   * Handle field change
   */
  virtual void notify(SoNotList *list);

  /*
  if the IVVR_CHECK_3DTEX_SIZE env var is enabled, VolumeViz will check if the
  system is able to send 3DTexture of the current size to the graphics board.
  If it fails, VolumeViz will automatically switch to 2DTexture mode.
  */
  void check3DTextureSize(SoState*);

  //=========================================================================================
  //=================================== LDM members =========================================
  //=========================================================================================
  //useful to draw the tiles if we have either only volumeRender or only slice
  SbBool m_tilesInRAMalreadyDrawn;

  //==========================================================================================
  //=================================== PAGING members =======================================
  //==========================================================================================

  void   viewPages(SbBool);
  void   getPagingStats(unsigned int & memoryUsed, unsigned int &pagesLoaded);
  void   setSubSamplingMaxVariation(SbVec3i32 &);

  int64_t getValue (SbVec3i32 &pos, SbBool real = FALSE);
  double  getValueD(const SbVec3i32 &pos, SbBool real = FALSE);
  int64_t loadDataValue(void* value, const SbVec3i32 &pos, void*& data, SoBufferObject *dataBufferObject, SbBool real);
  void   keepSpecifiedPageSize(SbBool);

  SoVolumePaging *m_paging;
  SbBool             m_pagingInit;
  SbBool             m_pagingViewPages;
  int                m_pagingMaxMemory;
  SbVec3i32          m_pagingPageSize;
  SbBool             m_pagingSubSampling;
  SbBool             m_pagingAutoSubSampling;
  SbBool             m_pagingAutoUnSampling;
  SubMethod          m_pagingSubSamplingMethod;
  SbVec3i32          m_pagingROISampling;
  SbVec3i32          m_pagingSecondarySampling;
  SbVec3i32          m_pagingSubSamplingMaxVar;
  SbBool             m_pagingKeepSpecifiedPageSize;

  //==========================================================================================

  static void initClass();
  static void exitClass();

  SB_THREAD_TLS_HEADER();

  //forceTex3D is used for SoVolumeIsosurface and SoVolumeRenderingQuality which only
  //work with 3D textures
  enum StorageHint loadData(SoAction*,SbBool&, SbBool forceTex3D = FALSE);
  void             getTexData(SoTransferFunction*, int, int, int, unsigned int *);
  void             getTexData(SoTransferFunction*, int, SbPlane&, int, unsigned int *);
  int              getIndexedTexData(SoTransferFunction*, int, int, void *);
  void             getTexDataLight(SoTransferFunction*, int, int, unsigned int *);
  void             loadColorTable(enum StorageHint, SoTransferFunction *, int, int32_t *);
  virtual void     updateColorTable(SoState *, SoTransferFunction *,int32_t**,int32_t*);
  void             updateColorTable(SoState *, SoVolumeData::StorageHint textype,SoTransferFunction *,int32_t**,int32_t*);

  SoTransferFunction::GLColorMapType installColorMap(SoState*, bool useShaderARB);
  SoTransferFunction::GLColorMapType getColorMapType(SoState*);
  SbVec3i32&       getDimensionPowerOf2();
  SbVec3f&         getTexRatio();
  void             setLighting(SbBool);
  void             setLightDirection(const SbVec3f&);
  void             setLightIntensity(float);
  virtual bool     isPalettedTexture(SoState* state);
  int              isSharedPalettedTexture();
  int32_t        **get2DTexNames(int context) const;
  int32_t         *get3DTexNames(int context) const;

  SbBool           m_tex3Dbricking;
  SbBox3i32        m_tex3DbrickBox[8];
  SbVec3i32        m_tex3DbrickDimPow2[8];

  //for sceneGraphChange
  static void sceneGraphChangeCB(void* , SoSensor*);

  /** Find texture format according to colorMapType */
  void getTextureFormat(const int colorMapType,
                        GLenum& format, GLenum& dataType,
                        GLint& internalFormat) const;


  SoEXTENDER public:

  virtual void doAction( SoAction *action );
  virtual void GLRender( SoGLRenderAction *action );
  virtual SoLDMFrontTile* getAppropriateFrontTile(SoLDMTileID, SbVec3i32);
  virtual SoLDMTileManager::LDMSliceAccessor* getAppropriateSliceAccessor(const SoLDM::DataSetIdPair& p);
  virtual SoLDMReader* getAppropriateLDMReader( const SbString& pathname);
  virtual void useFakeData(SoLDMTileID tileID, SoBufferObject* bufferObject);

  // ScaleViz specific : force rendering on all oiru in depth compositing mode
  // As VolumeViz shape nodes are considered as transparent (alpha)
  virtual int32_t getRenderUnitID() const;

  SoINTERNAL public:
  virtual SoLDMGeomElement* getAppropriateElement(SoLDMGeometry* v);

protected:
  /**
   * Set to LDM mode without sending notification
   */
  virtual void setLDMInternal(SbBool);

  /**
   * Set to paging mode without sending notification
   */
  virtual void setPagingInternal(SbBool);

  /**
   * Reset the data field,
   * release memory and set the new reader
   */
  virtual void readerChanged();

  /**
   * Set the volume data element on the state
   */
  virtual void setElement(SoState* state);

  virtual SoVolumeReader *getAppropriateReader();

  // Destructor
  virtual ~SoVolumeData();
  void     releaseMemory();

  virtual bool enableMultidata(SoState* state);

  //Return -1 when lighting is on, 0 in RGBA texture mode
  virtual int getTexPrec(SoState*state);

  //Set data characteristic size, extent...
  virtual void readChar();

  /**
   * Call data set unload and release paging.
   */
  virtual void unload();

  /**
   * Called when filename is changed
   */
  virtual void updateFilename();

  /**
   * Returns TRUE if the data represents RGBA color values.
   */
  virtual SbBool isRGBAData();

  /** @copydoc SoDataSet::buildTile */
  virtual void buildTile(SoLDMTileID tileID, SoBufferObject* buffer);

private:
  /**
   * Reset field data to its default value
   * (8bits size(0,0,0))
   */
  void resetData();

  /**
   * Called when data3D changes
   */
  void updateData3D();

  //used to see if we need to check 3dtexture size again
  bool m_check3DTexSize;

  SbBool           m_isPaging;

  SoFieldSensor    m_usePalettedTextureSensor;
  SoFieldSensor    m_useSharedPalettedTextureSensor;
  enum StorageHint m_storage;

  static SoDataExtract* s_dataExtractAlgorithms;

  static void usePalettedTextureCB(void *, SoSensor *);
  static void useSharedPalettedTextureCB(void * instance, SoSensor *);

  void     releaseTextures(enum StorageHint = AUTO,SoState* state = NULL);
  void     setDimension(const SbVec3i32 &);
  void     setDimensionPowerOf2();

  SbBool   initData(SoState*);
  SbBool   initReader();
SoINTERNAL public:

  bool loadInMemory(SoState* s = NULL);

  void drawOctree(SoGLRenderAction* pGLRA);

private:

  SoDataCompositor* m_dataCompositor;

  SbBool   createPagingModule(SbVec3i32, DataType);

  SbBool   loadDataTex2D(SoState *, SoTransferFunction*,int32_t**);
  SbBool   loadDataTex3D(SoState* state,SoTransferFunction*,int32_t*);
  SbBool   loadDataTex3DBricks(SoState* state,SoTransferFunction *,int32_t*);
  SbBool   loadDataTex3DBrick(SoState*, SbVec3i32 &, SbVec3i32 &, SbVec3i32 &, SoTransferFunction *);
  SbBool   loadDataTex3DDirect(SoState* state, SoTransferFunction *);
  SbBool   loadDataTex3DSubImage(SoState* state, SoTransferFunction *);
  SbBool   loadDataTex3DImage(SoState* state, SoTransferFunction *);

  void     setGlPixelTransfer(SoTransferFunction *);
  void     extendData(int, void*);
  void     extendData1(int, int, void*);
  void     extendDataBrick(int, void*, SbVec3i32 &, SbVec3i32 &, SbVec3i32 &, SoTransferFunction *t = 0);
  void     extendDataBrick1(int, int, void*, SbVec3i32 &, SbVec3i32 &, SbVec3i32 &, SoTransferFunction *t = 0);
  void     computeStatData(SbBool flag = FALSE);
  int      fswGetDataChar(SbBox3f &, DataType &, SbVec3i32 &);
  void     fswAbort();
  void     fswSkipSlice(int);
  void*    fswGetNextSlice(int);
  void     fswEnd();
  int64_t  subSample(SoDataSet::DataType,int,SbVec3i32&,void*,int,int,int,int,SoVolumeData::SubMethod);
  double   subSampleD(SoDataSet::DataType,int,SbVec3i32&,void*,int,int,int,int,SoVolumeData::SubMethod);

  void     *m_fswSliceData;
  SoCache  *m_texElementDependency;
  SbVec3i32 m_dimensionPowerOf2;
  SbVec3f   m_texRatio;
  SbBool    m_lighting;
  int       m_lightDir[3];
  int       m_lightInt;
  int       m_ambCol[3];
  int       m_specCol[3];
  int       m_shininess;
  //float     m_transparency;

  // Class static thread local storage
  struct MTstruct {
    SoCache *m_texElementDependency;
    int32_t *m_tex2Dnames[3];
    int     m_tex3Dnames[8];
  };
  SoGLVolCacheList* m_VRTexList;

  ///////////////////////EXCEPTION METHODS/////////////////////////////////////
  //
  // #grouped getVolumeSize()
  // #grouped getVolumeData(SbVec3i32 & dimension, data , DataType & type)
  // #grouped getReader()
  //
  /////////////////////////////////////////////////////////////////////////////
   friend class SoLDMMediator::LDMManagerAccess;

  std::map<const SoVolumeShader *, bool> m_rectilinearCoordinatesUpdated; /**< keeps track of notified volume shader */


SoINTERNAL public:
  virtual void getDataOneObliqueSlice( const SbVec3i32& tileSize, SoBufferObject* tileData, int Zaxis, const SbPlane& plane, SoBufferObject* slicedata, int interp );
  virtual SoBufferObject* getDataOneSlice( const SbVec3i32& tileSize, SoBufferObject* tileData, int Zaxis, int slice);

  virtual void  computeLighting( const SbVec3i32 & tileSize, SoBufferObject* rgbaBuffer );
  SbBox3f getLDMOutliningBox();

  /**
   * Internal helper function which return LDM tile transformed depending on state
   * see SoVolumetransform for details.
   */
  virtual SoBufferObject *getTransformedTile(const SoLDMTileID& tile,
                                             const SoLDM::DataSetIdPair& p,
                                             SoState * state=NULL,
                                             const bool useExtendedData = false);

public:
  /**
   * Coordinate type used by this data set.
   */
  enum CoordinateType {
  /**
   * Uniform grid spacing along each axis.
   */
	COORDINATES_UNIFORM = SoVolumeReader::COORDINATES_UNIFORM,
  /**
   * Grid spacing defined by x, y, z values.
   */
	COORDINATES_RECTILINEAR = SoVolumeReader::COORDINATES_RECTILINEAR
  };

  CoordinateType getCoordinateType() const
  {
    return m_coordinateType;
  }

  /**
   * Which axis to handle
   * @see getRectilinearCoordinates
   */

  enum Axis {
    X,
    Y,
    Z
  };

  /**
   * Returns a vector describing mapping from uniform space to
   * rectilinear space. You can specify that you want
   * the vector to return the coordinates from the X, Y, or Z axis.
   */
  const std::vector<float>& getRectilinearCoordinates(Axis axis) const;

  /**
  * Initiate a volume editing transaction. @BR
  * Returns a unique transaction id.
  * This value is required for finishing the edit transaction and useful for undoing.
  * May not be called if an editing transaction is already in progress
  * for the current thread.  On error does nothing.
  */
  virtual void startEditing(int &transactionId );

  /**
  * Fill a tile with given data. @BR
  * The buffer size (in bytes) must match the tile size (in bytes) exactly.
  * Returns 0 if successful, else an result code defined by SoLDMDataEditor::ErrorValue.
  */
  virtual int writeTile( const SoLDMTileID& tileId, SoBufferObject* userData );

  /**
  * Fill a subVolume with given data. @BR
  * The buffer size (in bytes) must match the subvolume size (in bytes) exactly.
  * Returns 0 if successful, else an result code defined by SoLDMDataEditor::ErrorValue.
  */
  virtual int writeSubVolume( const SbBox3i32& subVolume, SoBufferObject* userData );

  /**
  * Fill a tile with a value. @BR
  * Returns 0 if successful, else an result code defined by SoLDMDataEditor::ErrorValue.
  */
  virtual int writeTile( const SoLDMTileID& tileId, const double& value );

  /**
  * Fill a subvolume with a value. @BR
  * Returns 0 if successful, else an result code defined by SoLDMDataEditor::ErrorValue.
  */
  virtual int writeSubVolume( const SbBox3i32& subVolume, const double& value );

  /**
  * Terminate an editing transaction. @BR
  * SHould only be called after calling startEditing. On error does nothing.
  */
  virtual void finishEditing(int transactionId);

  /**
  * Undo all modifications associated with specified transaction id. @BR
  * All modified tiles are restored to their original value in the data source.
  * May only be called when no threads are editing, i.e. after all threads that
  * called startEditing have called finishEditing.  On error does nothing.
  * Note that undo does not manage overlapping transactions, meaning that
  * if a tile has been edited in two different transactions,
  * the undo operation will restore the tile from its original state,
  * not from its previous edited state.
  */
  virtual void undoEditing( int transactionId );

  /**
  * Save modifications to a file. @BR
  * All modified tiles are written back to the data file using SoLDMWriter.
  * May only be called when no threads are editing, i.e. after all threads that
  * called startEditing have called finishEditing.  On error does nothing.
  */
  virtual bool saveEditing(bool recomputeLowerResolution = TRUE, const std::vector<char*> convertionParameters = std::vector<char*>() );

  /**
  * Activate/Deactivate notification on multiple editing.
  */
  virtual void setNotifyOnMultiEdit(const bool flag);

  /**
  * Returns the state of notification on multiple editing.
  */
  virtual bool getNotifyOnMultiEdit() const;

  /**
  *  Returns true if VolumeData has edited tiles.
  */
  virtual bool hasEditedTile() const;

SoINTERNAL public:
  /**
  * Returns a vector mapping back a rectilinear coordinates to uniform space.
  */
  const std::vector<float>& getInvertedRectilinearCoordinates(Axis axis) const;

  /**
  * Draw a colored box depending on its state and resolution.
  */
  virtual void drawXYZBox(SoState* state, BoxColor color, const SbBox3f& box);

  /**
  * Use the tileId to know if the tile is really full res
  */
  virtual void drawIJKBox(SoState* state, BoxColor color, const SbBox3f& box, const SoLDMTileID& tile,
                          bool subTile = false);
  virtual void drawIJKBox(SoState* state, BoxColor color, const SbBox3f& box, bool fullRes, bool subTile = false);
  virtual void drawIJKBox(SoState* state, BoxColor color, const SbBox3f& box, bool subTile = false);

  void setupRectilinearCoordinates(const SbVec3i32&);
  bool isRectilinearCoordinatesUpdated(const SoVolumeShader* s);
  void resetRectilinearCoordinatesUpdated(const SoVolumeShader* s);

  SbVec3f computeRectilinearCoordinate(const SbVec3f& vertex);
  SbBox3f computeRectilinearCoordinate(const SbBox3f& box);

  SbVec3f computeInvertedRectilinearCoordinate(const SbVec3f& vertex);
  SbBox3f computeInvertedRectilinearCoordinate(const SbBox3f& box);

  virtual bool isEditedTile( const SoLDMTileID& tileId );
  virtual void setEditedTile( int transactionId, const SoLDM::TileIdVector& tileIds, bool isEdited );
  virtual void setEditedTile( int transactionId, const SoLDMTileID& tileId, bool isEdited );
  virtual bool isEditing();
  virtual bool isCurrentThreadEditing(SbThreadId_t threadId);
  virtual void cleanUnsavedEdition();

  void setDefaultValue( const double defValue );
  double getDefaultValue() const;

private:
  /** Bind current drawstyle and volume data */
  void bindVolumeDataToDrawStyle(SoAction* action);

  template <typename T> void copySliceData(const SbVec3i32& pageSize,
                                           SoBufferObject *pageData, int Zaxis,
                                           const SbPlane& plane, SoBufferObject *slicedata, int interpVal);
  // rectilinear dataset support
  std::vector<float> m_invertedRectilinearCoordinates[3]; /** coordinate mapping along each axis */
  std::vector<float> m_rectilinearCoordinates[3]; /** coordinate mapping along each axis */
  CoordinateType m_coordinateType;

  /**
    * Helper function for compatibility with old setVolumeData API
    */
  void setVolumeDataCompatibily(const SbVec3i32 &dimension,
                                void* dataPtr,
                                SoDataSet::DataType type = UNSIGNED_BYTE,
                                int numSignificantBits = 0);

  /** Used to draw octree */
  static void drawPoint(SoLDMTileID &tileID,int level,float levelmax);

  int m_numRenderCaches;
  SbThreadMutex* m_threadMutex;
  bool m_bNotifyOnMultiEdit;


  // Define the default value of the volumedata
  double m_defaultValue;
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif // _SO_VOLUME_DATA_
