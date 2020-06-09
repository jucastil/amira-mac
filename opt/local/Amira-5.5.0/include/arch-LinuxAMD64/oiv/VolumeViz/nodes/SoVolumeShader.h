/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Benjamin GRANGE (Aug 2005)
**=======================================================================*/


#ifndef _SO_VOLUME_SHADER_H_
#define _SO_VOLUME_SHADER_H_


#include <Inventor/nodes/SoShaderProgram.h>
#include <Inventor/nodes/SoShaderObject.h>
#include <Inventor/nodes/SoFragmentShader.h>
#include <Inventor/nodes/SoVertexShader.h>
#include <Inventor/sensors/SoNodeSensor.h>

#include <Inventor/STL/cassert>
#include <Inventor/STL/string>

/*----------------------------------------------------------------------------*/

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable : 4251)
#endif

class SoVolumeData;
class SoGLTexture;
class SoIsosurfaceTexture;
class SoVolumeRenderingQuality;
class SoVolumeDataDrawStyle;

/**
 * @VREXT Shader node for volume rendering.
 *
 * @ingroup VolumeVizNodes
 *
 * @DESCRIPTION
 * This node is the same as SoShaderProgram except that the field #shaderObject
 * contains a set of predefined vertex and fragment shader functions used for volume
 * and isosurface rendering.  These functions may also be used by application defined
 * shader programs and are described in the text below.  SoVolumeShader allows you to
 * apply shaders to all VolumeViz rendering nodes (SoVolumeRender, SoOrthoSlice, etc.).
 *
 * GLSL is the only shading language supported by this node.
 *
 * No more than one SoVolumeShader can be used with one volume visualization node,
 * e.g. SoVolumeRender. Since SoVolumeIsosurface and SoVolumeRenderingQuality are
 * derived from this class, only one (or none) of these three nodes can be used at 
 * the same time.  Exception: Since Open Inventor 7.1 it is possible to use
 * both SoVolumeRenderingQuality and SoVolumeIsosurface with SoVolumeRender.
 *
 * Remember this is a shader node. The effect will usually be undesirable if it is
 * applied to standard geometry (polygons, lines, etc).  Therefore applications
 * should generally keep the volume visualization nodes and standard geometry
 * nodes separate in the scene graph (i.e. under different SoSeparator nodes).
 *
 * This node searches for its @B predefined shader @b files in the following directories in
 * this order: current directory, $OIV_FILE_SEARCH_PATHS, SoInput directory list (see the
 * addDirectoryXXX methods), $IVVR_SHADERS_PATH, then $OIVHOME/data/volumeviz/shaders
 * (this last location is where the default shader files are installed by the SDK).
 * On Windows, the directory containing the VolumeViz DLL is also searched (last).
 * Note that application shader files are searched for using the usual Open Inventor
 * rules: current directory, $OIV_FILE_SEARCH_PATHS, then the SoInput directory list.
 *
 * The following #define macros are dynamicly added to the shader program by VolumeViz:
 *
 *  -@I@B VVIZ_DATARGBA @b@i: Is true if VVizData (VolumeViz input data) contains RGBA values. @BR
 *   In this case each value in VVizData is a vec4.  Otherwise each value is a float.
 *   (Before Open Inventor 8.5 only float values were supported.)
 *
 *  -@I@B VVIZ_DATATYPE @b@i: Defines the GLSL data type contained in the volume (VVizData). @BR
 *    If VVIZ_DATARGBA is true, then VVIZ_DATATYPE is defined as "vec4", in all other cases
 *    it is defined as "float".  (Before Open Inventor 8.5 only type float was supported.)
 *
 * The following functions are provided for use in vertex shaders:
 *
 *  - @I@B @anchor VVizComputeFrontSliceTexCoord void VVizComputeFrontSliceTexCoord()@b@i:
 *    put the texture coordinates of the front slice into gl_TexCoord[0]. These coordinates are
 *    used for indexing the volume data texture.
 *
 *  - @I@B @anchor VVizTexGen vec3 VVizTexGen()@b@i: Computes "object linear" texture
 *    coordinates using planes defined by VolumeViz in texture unit 0.
 *    Texture coordinates computed are relative to the current tile.
 *    These coordinates are normally used in the fragment shader to look up the voxel data
 *    value for the current fragment.
 *
 *  - @I@B @anchor VVizTexGenVol vec3 VVizTexGenVol()@b@i: Computes "object linear" texture
 *    coordinates using planes defined by VolumeViz in texture unit 1.
 *    Texture coordinates computed are relative to the entire volume.
 *    These coordinates may be used in a fragment shader when the position of the voxel
 *    in the volume is needed. The volume dimensions in voxels are available to the
 *    shader in the (vec3) VVizVolumeDimensions uniform parameter.
 *
 *  - @I@B  @anchor VVizComputeBackSliceTexCoord void VVizComputeBackSliceTexCoord()@b@i: put the
 *  texture coordinates of the
 *  back slice into gl_TexCoord[1]. These coordinates allow you to retrieve the volume data
 *  which is in the alignment of the eye and the front slice volume data. In the picture
 *  below, the texture coordinates of Sf will be in gl_TexCoord[0] and those of Sb in
 *  gl_TexCoord[1]. This function only works in view-aligned slice mode.
 *  @IMAGE schema_slices.jpg
 *
 *  - @I@B void VVizComputeBackSliceTexCoordOrtho()@b@i: Same thing but with an orthographic
 *  camera
 *
 *  - @I@B @anchor VVizComputeLightingVectors void VVizComputeLightingVectors()@b@i: Computes the following lighting vectors:
 *         - @I VVizLightingVec@i: directional light vector in object space. The first directional
 *                                    light found in the scene graph is used for this computation.
 *         - @I VVizViewVec@i: vertex to eye vector in object space
 *         - @I VVizHalfVec@i: half vector in object space (VVizViewVec+VVizLightingVec)/2
 *
 * - @I@B void VVizComputeLightingVectorsOrtho()@b@i: Same thing but with an orthographic camera
 *
 * -  @I@B vec4 VVizGenerateVertex()@b@i: Returns the current vertex being processed.
 *    When SoVolumeRender::gpuVertexGen field is set to true, it generates the slice's vertex, otherwise
 *    it returns gl_Vertex. It should be the first called function in the vertex shader
 *    (see $OIVHOME/data/VolumeViz/shaders/vvizdefvertex_vert.glsl for an usage example).
 *
 * - @I@B void VVizCalcDistToUniformGrid(vec4 vertex)@b@i: This function needs to be called in your @I main @i
 *   function if you are using an SoUniformGridClipping node. The vertex parameter must be in view space.
 *
 * The following functions are provided for use in fragment shaders:
 *  - @I@B @anchor VVizComputeVolumeRendering vec4 VVizComputeVolumeRendering(VVIZ_DATATYPE sf)@b@i:
 *  Convert the volume data
 *  @I sf@i to color by fetching the colormap.
 *
 *  - @I@B vec4 VVizComputePreintegrated(VVIZ_DATATYPE sf, VVIZ_DATATYPE sb)@b@i: Convert the volume
 *  data @I (sf, sb)@i in color by fetching in the pre-integrated table. The pre-integrated
 *  table is a pre-computed table which gives an approximation of the volume rendering
 *  integral between two slices. Because it needs a special texture, this function can be
 *  used only in SoVolumeRenderingQuality.
 *
 *  - @I@B @anchor VVizComputeVolumeRenderingLighting vec4 VVizComputeVolumeRenderingLighting(vec4 col)@b@i: Add lighting to
 *  the color @I col@i. @I col@i is usually the result of VVizComputeVolumeRendering.
 *
 *  - @I@B @anchor VVizComputePreintegratedLighting vec4 VVizComputePreintegratedLighting(vec4 col)@b@i: Add lighting to
 *  the color @I col@i in the case of  pre-integrated rendering.  @I col@i is usually the
 *  result of VVizComputePreintegrated. The difference with the previous function is that
 *  the normal used for lighting is at the middle of the space between the front and the
 *  back slice. Because it needs a special texture, this function can be used only
 *  in SoVolumeRenderingQuality. Lighting is computed with the first directional light found
 *  in the scene graph.
 *
 *  - @I@B vec4 VVizComputeIsoMaterial(VVIZ_DATATYPE sf, VVIZ_DATATYPE sb)@b@i: returns the color of the
 *  lighted pixel belonging to the isosurface. @I sf@i and @I sb@i are usually the volume
 *  data which have the texture coordinate gl_TexCoord[0] and gl_TexCoord[1] computed by
 *  VVizCompute{Front,Back}SliceTexCoord. If there is no isosurface between @I sf@i and
 *  @I sb@i, a transparent pixel will be returned.
 *  Because it needs a special texture, this function can be
 *  used only in SoVolumeIsosurface. Lighting is computed with the first directional light found
 *  in the scene graph.
 *
 *  - @I@B @anchor VVizBumpSlice vec4 VVizBumpSlice(vec4 col, float bumpScale)@b@i:
 *  This function is intended to be used for adding a bump mapping effect to ortho and oblique slices.
 *  @I bumpScale@i changes the intensity of the bump mapping effect, when this value is 0
 *  the surface is not bump mapped.
 *  @I col@i is usually the result of @anchor VVizComputeVolumeRendering VVizComputeVolumeRendering.
 *  The returned value is the color resulting from lighting. Lighting is computed with the first
 *  directional light found
 *  in the scene graph.
 *
 *  - @I@B void VVizClipVoxel()@b@i: Do clipping when using an SoVolumeClippingGroup or
 *  SoUniformGridClipping node. If no SoUniformGridClipping or SoVolumeClippingGroup nodes are
 *  present in the scene graph, this function will have no effect.
 *
 * - @I@B vec3 VVizComputeCoordinates(const vec3)@b@i: This function computes voxel coordinates
 *   and it must be used instead of @I gl_TexCoord[0].xyz@i. If not used, texture coordinates
 *   may not be clamped, scaled... as necessary in order to have correct rendering.
 *   Its parameter usually is @I gl_TexCoord[0].xyz@i.
 *   The returned coordinates must be passed to @I VVizCombineData@i.
 *
 * - @I@B vec2 VVizComputeCoordinates(const vec2)@b@i: This function computes voxel coordinates for 2D shapes
 *  (slices, volume skin...) and it must be used instead of @I gl_TexCoord[0].xy@i. If not used, texture coordinates
 *   may not be clamped, scaled... as necessary in order to have correct rendering.
 *   Its parameter usually is @I gl_TexCoord[0].xy@i.
 *   The returned coordinates must be passed to @I VVizCombineData@i.
 *
 * - @I@B vec4 VVizTransferFunction(float pos, int tfId)@b@i: return the color at the normalized pos in the
 * transfer function of id @I tfId @i
 *
 * - @I@B vec4 VVizTransferFunction(VVIZ_DATATYPE frontVoxel, VVIZ_DATATYPE backVoxel, int tfId)@b@i: return the preintegrated color between front voxel
 * and back voxel for the transfer function of id @I tfId @i
 *
 * - @I@B vec4 VVizApplyBoundary(vec4 fragColor, int maskFront, vec3 texCoordFront, vec3 texCoordBack)@b@i: This method is used to apply
 * mask on the volume and should be called in a custom shader in order to support the SoVolumeMask node
 *
 * - @I@B int VVizGetMask(vec3 tcoord)@b@i: Return the mask value at the given texture coordinate. If there is no
 * SoVolumeMask, the returned value is the id of the transfer function on the state.
 *
 * - @I@B VVIZ_DATATYPE VVizGetData(sampler3D tex, vec3 tcoord)@b@i: This function retrieves the voxel at the
 * given coordinates. It may apply interpolation (cubic, linear...) according to the settings of the
 * SoVolumeRenderingQuality and SoVolumeRender nodes.
 *
 * - @I@B VVIZ_DATATYPE VVizGetData(sampler2D tex, vec2 tcoord)@b@i: This is the 2D version of VVizGetData for
 * slices and volume skin nodes.
 *
 * - @I@B vec4 VVizApplyNpr(vec4 fragColor, vec3 tcoord)@b@i: This function applies various
 *   non-photorealistic rendering algorithms on the given color (edge detection, jittering...).
 *
 * - @I@B void VVizOutputColor(vec4 color)@b@i: This function sends the final fragment color
 *   to OpenGL. It should be used instead of directly setting gl_FragColor, in order to
 *   allow VolumeViz to do final manipulation of the color.
 *
 * The following uniform variables are automatically set by VolumeViz for use in vertex
 * or fragment shaders:
 * - @I VVizVolumeDimensions@i: vec3 containing volume dimensions in voxels.
 * - @I VVizTileDimensions@i: vec3 containing tile dimensions in voxels.
 * - @I VVizTileMinIJK@i: vec3 containing tile minimum coordinate in voxels.
 * - @I VVizTileMaxIJK@i: vec3 containing tile maximum coordinate in voxels.
 * - @I VVizOrthoSliceAxis@i: int containing 0 for X axis, 1 for Y axis, 2 for Z axis. @BR
 *   (only set by SoOrthoSlice)
 * - @I VvizDu@i: vec3 containing the minimum value to add to texture coordinates in order to move to the next voxel along X @BR
 * - @I VvizDv@i: vec3 containing the minimum value to add to texture coordinates in order to move to the next voxel along Y @BR
 * - @I VvizDw@i: vec3 containing the minimum value to add to texture coordinates in order to move to the next voxel along Z @BR
 *
 * The following varying variables are set by the predefined vertex shader functions
 * for use in fragment shaders
 * (when VVizComputeLightingVectors has been called in the vertex shader):
 *  - @I VVizLightingVec@i: directional light vector in object space. The first directional
 *                          light found in the scene graph is used for this computation.
 *  - @I VVizViewVec@i: vertex-to-eye vector in object space
 *  - @I VVizHalfVec@i: half vector in object space (VVizViewVec+VVizLightingVec)/2
 *
 * Reserved texture units: @BR @BR
 * Because some rendering methods need to create and use special textures, some texture
 * units must be reserved for internal use.  The application can specify which texture
 * units VolumeViz should use by setting environment variables (see SoPreferences).
 * The texture units between OIV_FIRST_RESERVED_TEXTURE_UNIT and
 * OIV_FIRST_RESERVED_TEXTURE_UNIT+SoShaderProgram::getNumReservedTextures()-1
 * inclusive are reserved for internal VolumeViz use.
 * If OIV_FIRST_RESERVED_TEXTURE_UNIT is not set, its default value is
 * SoFragmentShader::getMaxTextureImageUnit()-SoShaderProgram::getNumReservedTextures().
 * Note: The value returned by SoShaderProgram::getNumReservedTextures() may change between
 * VolumeViz versions.  The total number of available texture units depends on the graphics
 * hardware.
 *
 * @B Limitations: @b
 * @UL
 *  @LI Only graphics cards supporting the GLSL language can use this node.
 *  @LI The set of fragment shaders needs the 3D texture mode of SoVolumeData
 *      to be enabled. The set of vertex shaders doesn't need this.
 * @ul
 *
 * @B Note: @b
 * Since the GLSL specification doesn't currently allow the use of the @I include @i directive,
 * it is necessary to
 * write the declaration of the functions at the beginning of the shader which uses them.
 * The following is an exhaustive list of functions exposed by the SoVolumeShader
 * node and can be used to do a fast
 * copy-and-paste between this documentation and the application's shader.
 *
 * Available vertex program functions are:
 * <PRE>
 * void VVizComputeBackSliceTexCoord();
 * void VVizComputeFrontSliceTexCoord();
 * void VVizComputeLightingVectors();
 * void VVizComputeTangentSpaceLightingVectors();
 * void VVizCalcDistToUniformGrid();
  * </PRE>
 *
 * Available fragment program functions are:
 * <PRE>
 * vec4 VVizComputeIsoMaterial(VVIZ_DATATYPE sf, VVIZ_DATATYPE sb);
 * vec4 VVizComputePreIntegrated(VVIZ_DATATYPE sf, VVIZ_DATATYPE sb);
 * vec4 VVizComputeVolumeRendering(VVIZ_DATATYPE sf);
 * vec4 VVizComputePreintegratedLighting(vec4 col);
 * vec4 VVizComputeVolumeRenderingLighting(vec4 col);
 * vec4 VVizBumpSlice(vec4 col, float bumpScale);
 * VVIZ_DATATYPE VVizCombineData(vec3 tcoord);
 * VVIZ_DATATYPE VVizCombineData(vec2 tcoord);
 * void VVizClipVoxel();
 * vec3 VVizComputeCoordinates(const vec3);
 * vec2 VVizComputeCoordinates(const vec2);
 * void VVizOutputColor(vec4 color);
 * vec4 VVizApplyNpr(vec4 fragColor, vec3 tcoord);
 * VVIZ_DATATYPE VVizGetData(sampler3D tex, vec3 tcoord);
 * VVIZ_DATATYPE VVizGetData(sampler2D tex, vec2 tcoord);
 * vec4 VVizTransferFunction(VVIZ_DATATYPE pos, int tfId);
 * vec4 VVizTransferFunction(VVIZ_DATATYPE frontVoxel, VVIZ_DATATYPE backVoxel, int tfId);
 * int VVizGetMask(vec3 tcoord);
 * vec4 VVizApplyBoundary(vec4 fragColor, int maskFront, vec3 texCoordFront, vec3 texCoordBack);
 * </PRE>
 *
 * @EXAMPLE
 * \oivnetdoc
 * \code
 *   // Shader program with one fragment shader with one uniform parameter.
 *   // First load the fragment shader code
 *   SoFragmentShader fragmentShader = new SoFragmentShader();
 *   fragmentShader.sourceProgram.SetValue(SHADER_FILENAME);
 *      
 *   // Set the shader uniform parameter
 *   SoShaderParameter1i paramTex1 = new SoShaderParameter1i();
 *   paramTex1.name.SetValue("data1");
 *   paramTex1.value.SetValue(1);
 *   fragmentShader.parameter.Set1Value(0, paramTex1);
 *      
 *   // Associate fragment shader with a volume shader program node
 *   SoVolumeShader volShader = new SoVolumeShader();
 *   volShader.shaderObject.Set1Value(
 *      (int)SoVolumeShader.ShaderPositions.FRAGMENT_MAIN, 
 *      fragmentShader );
 *   root.AddChild( volShader );
 * \endcode
 * \else
 * \code
 *   // Shader program with one fragment shader with one uniform parameter.
 *   // First load the fragment shader code
 *   SoFragmentShader* pFragmentShader = new SoFragmentShader();
 *   pFragmentShader->sourceProgram.setValue( SHADER_FILENAME );
 * 
 *   // Set the shader parameter
 *   // The addShaderParameter1i method is equivalent to:
 *   //     SoShaderParameter1i *paramTex1 = new SoShaderParameter1i;
 *   //     paramTex1->name = "data1";
 *   //     paramTex1->value.setValue(1);
 *   //     fragmentShader->parameter.set1Value(0, paramTex1);
 *   pFragmentShader->addShaderParameter1i( "data1", 1 );
 * 
 *   // Associate fragment shader with a volume shader node
 *   SoVolumeShader* pVolShader = new SoVolumeShader;
 *   pVolShader->shaderObject.set1Value(SoVolumeShader::FRAGMENT_MAIN, pFragmentShader);
 *   pRootNode->addChild( pVolShader );
 * \endcode
 * \endoivnetdoc
 *
 * @FILE_FORMAT_DEFAULT
 *    SoShaderProgram {
 *      @TABLE_FILE_FORMAT
 *        @TR shaderObject     @TD [ DATA_COMBINE_FUNCTIONshader,
 *        @TR @TD VERTEX_MAINshader,
 *        @TR @TD FRAGMENT_MAINshader ]
 *        @TR forVolumeOnly @TD FALSE
 *      @TABLE_END
 *    }
 *
 * @SEE_ALSO
 *  SoShaderProgram,
 *  SoVolumeRenderingQuality,
 *  SoVolumeIsosurface,
 *  SoPreferences
 *
 */

class VOLUMEVIZ_API SoVolumeShader : public SoShaderProgram {

  SO_NODE_HEADER(SoVolumeShader);

public:
  /**
   * Constructor
   */
  SoVolumeShader();

  /**
   * Specifies the position of the different shaders in the field
   * #shaderObject. In other words, use these enumeration values for
   * the first parameter of the set1Value method.
   */
  enum ShaderPosition {
#ifndef HIDDEN_FROM_DOC
    VERTEX_TOOLS = 0,
    FRAGMENT_TOOLS,
    VERTEX_GEN_FUNCTION,
    VERTEX_TEXCOORD_FUNCTION,
    COMPUTE_COORDINATES,
    VERTEX_CLIPPING_FUNCTION,
    VERTEX_VOLGEOM_VERTEX_CLIPPING_FUNCTION,
    FRAGMENT_LIGHTING_FUNCTION,
    VERTEX_LIGHTING_FUNCTION,
    VERTEX_BUMP_FUNCTION,
    FRAGMENT_VOLUME_MASK_GET_FUNCTION,
    FRAGMENT_VOLUME_MASK_APPLY_FUNCTION,
    FRAGMENT_TRANSFER_FUNCTION,
    FRAGMENT_GRADIENT_FUNCTION,
    FRAGMENT_BUMP_FUNCTION,
    FRAGMENT_CLIPPING_FUNCTION,
    FRAGMENT_CLIPPING_VOL_GRID_FUNCTION,
    FRAGMENT_CLIPPING_GEOMETRY_FUNCTION,
    FRAGMENT_FRONT2BACK_FUNCTION,
    FRAGMENT_JITTER_FUNCTION,
    FRAGMENT_EDGE_COLORING_FUNCTION,
    FRAGMENT_NPR_FUNCTION,
    FRAGMENT_BOUNDARY_OPACITY_FUNCTION,
    FRAGMENT_EDGE_IMAGE_SPACE_FUNCTION,
    FRAGMENT_MRT_FUNCTION,
    FRAGMENT_SHADOW_FUNCTION,
    FRAGMENT_LIGHTING_MODEL_FUNCTION,
    FRAGMENT_TEXCOORD_INTERPOLATION_FUNCTION,
    FRAGMENT_COMPUTE_MINMAX_TEXCOORD_FUNCTION,
    GEOMETRY_MAIN,
#endif
#ifdef OIV_NET_DOC
	/**
	* This shader is used for GPU multidata composition.
	*/

#else
	/**
	* This shader is used for GPU multidata composition.
	* It must contain the user-defined data combine functions whose prototypes are:
	* <PRE>
	* VVIZ_DATATYPE VVizCombineData(vec3 tcoord) // for volume
	* VVIZ_DATATYPE VVizCombineData(vec2 tcoord) // for ortho and oblique slice
	* </PRE>
	* The default functions are GLSL's texture3D() and texture2D():
	* @code
	* uniform sampler3D VVizData;
	* uniform sampler2D VVizSliceData;
	*
	* VVIZ_DATATYPE VVizCombineData(vec3 tcoord)
	* {
  * #ifndef VVIZ_DATARGBA
	*   return texture3D(VVizData, tcoord).w;
  * #else
  *   return texture3D(VVizData, tcoord);
  * #endif
	* }
	*
	* VVIZ_DATATYPE VVizCombineData(vec2 tcoord)
	* {
  * #ifndef VVIZ_DATARGBA
	*   return texture2D(VVizData, tcoord).w;
  * #else
	*   return texture2D(VVizData, tcoord);
  * #endif
	* }
	* @endcode
	*
	* @ref VVizComputeVolumeRenderingLighting,
	* @ref VVizComputePreintegratedLighting, and
	* the predefined
	* FRAGMENT_MAIN shader of SoVolumeIsosurface and SoVolumeRenderingQuality use VVizCombineData
	* for accessing the volume data texture.
	*
	* The following example shows a typical use of this node:
	* @code
	* SoFragmentShader* fragmentShader = new SoFragmentShader;
	* fragmentShader->sourceProgram.setValue("mydatacombine_frag.glsl");
	*
	* SoVolumeShader* pVolShader = new SoVolumeShader;
	* pVolShader->shaderObject.set1Value(SoVolumeShader::DATA_COMBINE_FUNCTION, fragmentShader);
	* @endcode
	*
	* The subtraction of two volumes could be written like this:
	* @code
	* uniform sampler3D data1;
	* uniform sampler3D data2;
	*
	* VVIZ_DATATYPE VVizCombineData(vec3 tcoord)
	* {
	*  VVIZ_DATATYPE d1 = VVizGetData(data1, tcoord);
	*  VVIZ_DATATYPE d2 = VVizGetData(data2, tcoord);
	*  return d1-d2;
	* }
	* @endcode
	*      @TABLE_1B
	*      @TR First volume @TD Second volume @TD Subtraction
	*         @TR @IMAGE iso_compose_vol1.jpg
	*                   @TD @IMAGE iso_compose_vol2.jpg
	*                   @TD @IMAGE iso_compose.jpg
	*      @TABLE_END
	*
	* This function can also be used to apply filters on the volume data.
	* The following example shows how to make a smoothing filter which will remove some noise:
	* @code
	* uniform sampler3D data;
	*
	* VVIZ_DATATYPE VVizCombineData(vec3 tcoord)
	* {
	*  vec3 du = vec3(1./64., 0., 0.); //64 is the size of a tile
	*  vec3 dv = vec3(0., 1./64., 0.);
	*  vec3 dw = vec3(0., 0., 1./64.);
	*
	*  return 1./6.*(VVizGetData(data, tcoord-du).w+VVizGetData(data, tcoord+du).w+
	*                VVizGetData(data, tcoord-dv).w+VVizGetData(data, tcoord+dv).w+
	*                VVizGetData(data, tcoord-dw).w+VVizGetData(data, tcoord+dw).w);
	*
	* }
	* @endcode
	*      @TABLE_1B
	*      @TR Non filtered data @TD Filtered data
	*         @TR @IMAGE iso_nofilter.jpg
	*                   @TD @IMAGE iso_filter.jpg
	*      @TABLE_END
	*
	* @B Limitation@b: If lighting functions are applied on a composited volume, all volume
	* data must have the same tile size otherwise the lighting computation will be erroneous.
	*/

#endif //OIV_NET_DOC
    DATA_COMBINE_FUNCTION,
    GET_DATA_FUNCTION,
    /**
    * The main vertex program used for rendering (default: set texture coordinates
    * with @ref VVizComputeFrontSliceTexCoord and
    * @ref VVizComputeBackSliceTexCoord, compute lighting
    * vectors with @ref VVizComputeLightingVectors).
    *
    */
    VERTEX_MAIN,
     /**
     * The main fragment program used for rendering (default: standard volume rendering).
     * FRAGMENT_MAIN+1 and subsequent positions are freely available for user-defined shaders
     * objects.
     */
    FRAGMENT_MAIN
 };

  /**
   * @deprecated Use the field #forVolumeOnly.
   * @DEPRECATED_SINCE_OIV 7.0
   */
  SoDEPRECATED void setForVolumeOnly(SbBool volOnly) { forVolumeOnly = volOnly; }

  /**
  * Set to TRUE if the shader should be called for volume rendering and to FALSE
  * if it should be called for SoOrthoSlice, SoObliqueSlice and SoVolumeSkin.
  * Default is FALSE.
  */
  SoSFBool forVolumeOnly;

  /**
   * Indicates if volume shader is supported by your graphics board.
   */
  static SbBool isSupported(SoState* state=NULL) ;

  /**
   * Create a fragment shader with the given filename and
   * add it at the given pos. Return value is the new fragment shader.
   */
  virtual SoFragmentShader* setFragmentShader(int pos, const SbString& filenameOrSource,
                                              SoShaderObject::SourceType sourceType = SoShaderObject::FILENAME);

  /**
   * Create a vertex shader with the given filename and
   * add it at the given pos. Return value is the new vertex shader.
   */
  virtual SoVertexShader* setVertexShader(int pos, const SbString& filenameOrSource,
                                          SoShaderObject::SourceType sourceType = SoShaderObject::FILENAME);

#ifndef HIDDEN_FROM_DOC
SoINTERNAL public:
  /**
   * Return true if frag is a default fragment main
   */
  bool isInternalFragment(SoFragmentShader* frag) const;

  /**
   * Return true if obj is a default shader object
   */
  bool isInternalShaderObject(SoShaderObject* obj) const;

  /**
   * GLrender action.
   */
  void GLRender(SoGLRenderAction *action);

  /** register class. */
  static void initClass() ;

  /** unregister class. */
  static void exitClass() ;

  /**
   * Return true if this shader is only for volume (ie: not for orthoslice,
   * obliqueslice and volume skin)
   */
  SbBool isForVolumeOnly() { return forVolumeOnly.getValue(); }

  /**
   * Enable or disable fragment for front to back composition
   * If action is not NULL, do a GLRender in order to have the modified
   * shader in OpenGL state.
   */
  void useFrontToBack(bool flag, SoGLRenderAction* action);

  /**
   * Send uniform parameters allowing shader to compute texcoords
   * relative to the entire volume (instead of per-tile).
   */
  static void setTexCoordVolUniform(SoState* state, bool useExternalShaderProg, const SbBox3f &volSize) ;

  /**
   * Set per-volume parameters useful for computation in shader.
   */
  static void setDimensionUniforms( SoState* state,
                                    bool useExternalShaderProg,
                                    const SbVec3i32 &volumeDim,
                                    const SbVec3i32 &tileDim );

  /**
   * Set per-tile parameters useful for computation in shader.
   */
  void setPerTileUniforms(bool useExternalShaderProg,
                          const SbVec3i32 &tileMinIJK,
                          const SbVec3i32 &tileMaxIJK );

  /**
   * Return true if per-tile uniforms must be set
   */
  inline bool hasPerTileUniforms() const;

  static int getFirstUsedTextureUnit();

  /**
   * handle texture and shader setup for uniform/rectilinear grids
   */
  void setupRectilinearCoordinates(SoState *state);

  /**
   * configure per tile rectilinear informations
   */
  void setPerTileRectilinear(const SbVec3f& tileOrigin,
                             const SbVec3f& tileFactor,
                             const SbVec3f&, const SbVec3f&);
  /**
   * Return the texture unit used to bind the current color buffer
   */
  static unsigned int getEarlyzTextureUnit();

  /**
   * Enable special clipping function for
   * volume geometry rendering
   */
  void enableVolumeGeometryClipShader(bool flag);

  /** Choose lighting frament to use according to state */
  void chooseLightConfig(SoState* state, bool forbidVertexTwoSide = false);

  /** Install textures needed for shaders */
  virtual void installTextures(SoGLRenderAction* action);

  /**
   * If false, do nearest interpolation when computing  colors
   * but still do it when computing gradients
   */
  void enableColorInterpolation(bool flag);

  /** Return main fragment filename according to state */
  virtual SbString getNeededFragmentMainFilename(SoState* state);

protected:
  enum GradientMethod
  {
    GRADIENT_FORWARD_DIFF = 0,
    GRADIENT_CENTRAL_DIFF,
    GRADIENT_SOBEL,
    GRADIENT_LAST
  };

  enum LightingModel
  {
    OIV6,
    OPENGL,
    LIGHTING_MODEL_LAST
  };

  typedef enum
  {
    ONE_LIGHT_DIR,
    ONE_LIGHT_DIR_2_SIDES,
    N_LIGHTS_DIR,
    N_LIGHTS,
    BASE_COLOR,
    LAST_LIGHTING_CONFIG
  } LightingConfig;

  /** Define current fragment lighting configuration */
  void setLightingConfig(LightingConfig conf);

  /** Install textures needed for isosurface rendering */
  void installIsosurfaceTexture(SoGLRenderAction* action);

  /**
   * Called when node change
   */
  virtual void handleFieldChange(SoField* f);

  /**
   * Fill m_gradientShaders will all needed shaders
   */
  void createGradientShaders();

  /**
   * Set the method used to compute gradient
   */
  void setGradientMethod(GradientMethod method);

  /**
   * Fill m_lightingModelShaders will all needed shaders
   */
  void createLightingModelShaders();

  /**
   * Set the ligting model
   */
  void setLightingModel(LightingModel model);

  /**
   * Enable/disable main npr shader
   */
  void enableNprShader(bool flag, SoVolumeRenderingQuality* vrq);

  /**
   * Enable/disable boundary opacity shader
   */
  void enableBoundaryOpacityShader(bool flag, float boundaryIntensity,
                                   float boundaryThreshold);

  /**
   * Enable/disable edge coloring shader
   */
  void enableEdgeColoringShader(bool flag, const SbColor& edgeColor,
                                float threshold);

  /**
   * Enable/disable jittering shader
   */
  void enableJitteringShader(bool flag);

  /**
   * Enable/disable image space edge detector
   */
  void enableEdgeImageSpaceShader(bool flag, unsigned int edge2DMethod);

  /**
   * Output main color to gl_FragData[0] instead of gl_FragColor
   * in order to use MRT.
   */
  void enableMrt(bool flag);

  /**
   * Add needed function for bump on slices
   */
  void enableBumpFunctions(bool flag);

  /**
   * Set default rendering to slice
   */
  void enableSliceDefaultMain(bool flag);

  /**
   *
   * Enable cubic interpolation (works only for volumes).
   * WARNING: requires heavy GPU resources.
   */
  void enableCubicInterpolationShader(bool flag);

  /**
   * Install noise texture in the jitter texture unit
   */
  void installJitteringTexture(SoState* state);

  /**
   * Update color and threshold of edge coloring shader
   */
  void updateEdgeColoringUniforms(const SbVec3f& color, float threshold);

  /**
   * Update the intensity and threshold uniform of edge coloring shader
   */
  void updateBoundaryOpacityUniforms(float intensity, float threshold);

  /**
   * Set the VVizGradientThreshold uniform
   */
  void updateGradientUniform(float threshold);

  //Set various uniforms for VolumeClippingGroup
  void updateVolumeClippingParameters(SoState *state);

  //Set various uniforms for SoHorizonClippingShader
  void updateGridClippingParameters(SoState *state);

  //Reset the clipping shader to the void function
  void resetClippingFunction();

  //Return TRUE if a SoVolumeClippingGroup or SoUniformGridClipping is in the state
  SbBool hasClippingNodesInState(SoState *state);

  //When TRUE, force an update of all clipping parameters
  SbBool m_clippingReseted;

  void installCubicInterpolationTexture(SoState* state);
  ~SoVolumeShader();

  int m_datumSize;

  //Set needed texture samplers
  void setTextureSamplers(SoGLRenderAction* action);

  //Set the VVizUseOrthoCamera to the correct value
  void checkProjectionType(SoGLRenderAction* action);

  //Used by SoVRGenericVolumeRenderingQuality and SoVRGenericIsosurface
  //Check if the volume data size has changed
  bool volDataSizeChanged(SoState *state);

  //Create a vertex shader and search it in the path of the findShaders method
  SoVertexShader *createVertexProgram(const SbString &shader);
  SoFragmentShader *createFragmentProgram(const SbString &shader);

  // Clean a specified path:
  // - converts the path to unix path.
  // - removes the drive is the path is a windows path.
  static SbString cleanUpFilePath( const SbString& string );

  /** Create a shader suitable for shadowmap generation pass */
  virtual SoShaderProgram* generateShadowShader() const;

  /**
   * Default threshold used when computing gradient
   */
  static const float DEFAULT_GRADIENT_THRESHOLD;

  static const float DEFAULT_EDGE_THRESHOLD;

  static const float DEFAULT_BOUNDARY_THRESHOLD;
  static const float DEFAULT_BOUNDARY_INTENSITY;

  /** List of default main source for fragments and vertex */
  std::vector<SbString> m_defaultMainSource;

  SoIsosurfaceTexture* m_isosurfaceTexture;

#endif //HIDEN_FROM_DOC

private:
  /** Update draw style cache if necessary */
  void updateDataDrawStyleCache(SoState* state);

  /** Use shader for shadowmap generation */
  void shadowMapGLRender(SoGLRenderAction* action);

  static const size_t JITTER_TEX_SIZE;

  /** Create various lighting shaders */
  void createLightingFragmentShader();

  /** Create various lighting shaders */
  void createLightingVertexShader();

  /**
   * Create texture used for jittering
   */
  void createJitterTex(SoState* state, size_t size);
  void createCubicInterpolationTex(SoState* state);

  static void fieldChangedCB(void *data, SoSensor *s);

  /**
   * Fetch uniforms location for setPerTileUniforms
   */
  void getUniformsLocation();

  /**
   * Needed for backward compatibility with SoVolumeIsosurface
   * Reset drawstyle to volume rendering if a SoVolumeIsosurface node is on the state
   * */
  void handleFakeSoVolumeIsosurfaceStyle(SoGLRenderAction* action);

  SoGLTexture* m_jitterTex;
  SoGLTexture* m_cubicInterpolationTex;

  int m_previousProjectionType;
  bool m_useFrontToBack;

  enum ClippingMode {
    CLIP_MODE_VOLUME,
    CLIP_MODE_UNIFORM_GRID,
    CLIP_MODE_NONE
  };

   enum DefaultMainPos {
     DEFAULT_FRAG_VOLUME = 0,
     DEFAULT_FRAG_SLICE,
     DEFAULT_FRAG_LAST
   };

  ClippingMode m_currentClippingMode;

  SoGLTexture *m_rectilinearMappingTex;

  SoFragmentShader* m_computeRectilinearCoordinates;
  SoFragmentShader* m_computeUniformCoordinates;

  SoShaderParameter3f* m_VVizRootTileDimensions;
  SoShaderParameter3f* m_VVizTileFactor;
  SoShaderParameter3f* m_VVizTileOrigin;
  SoShaderParameter1i* m_VVizRectilinearMappingSize;

  SoNodeSensor m_nodeSendor;

  SoFragmentShader* m_defaultMainFragment[DEFAULT_FRAG_LAST];

  GLint m_vvizTileMaxIJK;
  GLint m_vvizTileMinIJK;

  size_t m_numUniformGridClipping;

  /**
   * Shaders used for gradient computation
   */
  std::vector<SoFragmentShader*> m_gradientShaders;
  GradientMethod m_currentGradientMethod;

  /**
   * Shaders used for lighting model
   */
  std::vector<SoFragmentShader*> m_lightingModelShaders;
  LightingModel m_currentLightingModel;

  bool m_heightFieldLightingEnaled;

  unsigned int m_edge2dMethod;
  bool m_edgeImageSpaceEnabled;
  bool m_mrtEnabled;
  bool m_boundaryOpacityEnabled;
  bool m_jitterEnabled;
  bool m_edjeColoringEnabled;
  bool m_nprEnabled;
  bool m_nprNeedGradient;

  SbVec3f m_edgeColor;
  float m_edgeThreshold;

  float m_gradientThreshold;

  float m_boundaryOpacityThreshold;
  float m_boundaryOpacityIntensity;
  bool m_cubicInterpolationEnabled;

  bool m_volumeGeometryClipEnabled;

  /** If false don't do interpolation on color but
   * do it only when computing gradient
   */
  bool m_colorInterpolation;

  /**
   * Cache volume clipping parameters
   */
  SoShaderParameter3f* m_vvizOneOverDepthTexSize;
  SoShaderParameter1f* m_vvizExclusive;
  SoShaderParameter1f* m_vvizNumLayers;
  SoShaderParameter1f* m_vvizNumPassUsed;

  /** Shaders for each light configuration */
  std::vector<SoFragmentShader*> m_lightingFragmentShader;
  std::vector<SoVertexShader*> m_lightingVertexShader;
  LightingConfig m_curLight;

  /** Proxy draw style used for compatibility with SoVolumeIsosurface */
  SoVolumeDataDrawStyle* m_volumeDataDrawStyle;

  SoCache* m_dataDrawStyleCache;
};

#ifndef HIDDEN_FROM_DOC
/*******************************************************************************/
bool
SoVolumeShader::hasPerTileUniforms() const
{
  return m_vvizTileMinIJK != -1 || m_vvizTileMaxIJK != -1;
}
#endif // HIDDEN_FROM_DOC

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif /*_SO_VOLUME_SHADER_H_*/
