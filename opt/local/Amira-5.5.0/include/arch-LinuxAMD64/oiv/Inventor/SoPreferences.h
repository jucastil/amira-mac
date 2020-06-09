/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
/*==============================================================================
*   Classes     : SoPreferences
*   Author(s)   : Fabien ARNAUD
*   Date        : Jul, 18 2002
*                 Feb, 20 2003
*==============================================================================
*
* Description : Manage environment variables and configuration file
*
*============================================================================*/


#ifndef _SB_ENVIRONMENT_VARS_H
#define _SB_ENVIRONMENT_VARS_H

#include <Inventor/SbBase.h>
#include <Inventor/SbDict.h>

class SbThreadMutex;
class SbColor;
class SbVec3f;
class SbVec2s;

/** 
 * @VSGEXT Manages Open Inventor configuration parameters.
 *
 * @ingroup General
 *
 * @DESCRIPTION
 *  Open Inventor maintains a configuration database that stores
 *  information about the Open Inventor "environment".
 *  The Open Inventor environment contains configuration parameters and
 *  their values.
 *
 * @B Setting configuration parameters @b@BR
 *  There are several ways that configuration parameter
 *  values are set into the Inventor
 *  configuration database:
 *
 * @B Configuration files: @b
 * When Open Inventor is initialized, two configuration files are
 *    automatically read (if available):
 *
 *     - A system configuration file $OIVHOME/oiv.cfg or the file pointed
 *       to by the OIV_CONFIG_FILE environment variable, and
 *
 *     - a local configuration file named oiv.cfg located in the
 *       application's current working directory.
 *
 *   The configuration parameters specified in the configuration files
 *   are set into Open Inventor's configuration database.
 *
 *   You can request that additional configuration files be read using
 *   SoPreferences::readFile.
 *
 *   The configuration file format is simple. You specify environment
 *   name-value pairs, one per line. The file format is shown below.
 *
 * @B Using SoPreferences methods: @b
 * SoPreferences::setValue sets a configuration parameter in the
 * Open Inventor configuration database. As this value is set in
 * memory, it is local to the application process and can only be
 * retrieved using SoPreferences::getValue. There are convenience
 * methods available for setting specific values of a specific
 * data type, e.g., #setFloat.
 *
 * @B Using system environment variables: @b
 * If a particular configuration parameter has not already been set
 *   via a config file or #setValue, then Open Inventor will check the
 *   system environment. System environment variables are set using
 *   platform-dependent commands (e.g., set, setenv).
 *
 * @B Querying configuration parameters @b@BR
 * To query a specific configuration parameter, use the method
 * SoPreferences::getValue which returns the value of the specified
 * configuration parameter in the Open Inventor configuration
 * database.
 *
 * SoPreferences also provides convenience methods for querying
 * specific data types and providing a default value, e.g.,<pre>
 *        int numFiles = SoPreferences::getInt( "NUM_FILES", 1 ); </pre>
 * requests the value of an integer-valued configuration parameter
 * and returns the default value 1 if this parameter has not been
 * specified. Corresponding "set" methods are also provided.
 *
 * @B Other @b@BR
 * The SoPreferences configuration mechanism is not restricted to
 * Open Inventor parameters. Applications are welcome to use it for
 * their own parameters if appropriate.
  *
  * To request configuration debugging information, use environment variable
  * OIV_DEBUG_CONFIG.
  *
  * @B CONFIGURATION FILE FORMAT@b @anchor Format
  *
  * White space (blank, tab) is ignored, except that there must be at
  * least one space or tab separating the name from its value.
  *
  * System environment variables may be used in a configuration file.
  * Environment variable names begin with a $ and end at the next
  * nonalphanumeric character.
  * They are replaced by their corresponding value.
  *
  *   <PRE>
  *   # comment
  *
  *   # NAME1, NAME2, and NAME3 are defined and associated
  *   # with value1, value2, and value3 respectively.
  *   NAME1     value1
  *   NAME2     value2    # comment
  *   +NAME3    value3
  *
  *   # NAME4 and NAME5 are defined and no values are associated
  *   # with these NAMEs.
  *   NAME4
  *   +NAME5    # comment
  *
  *   # If NAME6 is defined in the system environment or in one
  *   # of the previously loaded config files, it is now undefined.
  *   -NAME6    # comment </PRE>
  *
  * @B ALPHABETICAL LIST OF ENVIRONMENT VARIABLES@b @BR
  * @BR
  * In addition to the environment variables in this alphabetic list, there are also
  * special-purpose debug environment variables that may helpful in certain
  * circumstances. They are listed separately
  * @ref below.
  *
  * @TABLE_1B
  * @TR
  * @ref DIALOGVIZ_SKIN @BR
  * @ref DIALOGVIZ_SKINS_DIR @BR
  * @ref DIRECTVIZ_ACCUMULATION @BR
  * @ref DIRECTVIZ_ADAPTIVE_OVERSAMPLING @BR
  * @ref DIRECTVIZ_ADAPTIVE_OVERSAMPLING_VISUAL @BR
  * @ref DIRECTVIZ_ALWAYS_SUBSAMPLED @BR
  * @ref DIRECTVIZ_CACHE_DIR @BR
  * @ref DIRECTVIZ_CLUSTER @BR
  * @ref DIRECTVIZ_CONTROL_DIALOG @BR
  * @ref DIRECTVIZ_DIALOG_SHORTCUT @BR
  * @ref DIRECTVIZ_ENV_LIGHTS_SCALE @BR
  * @ref DIRECTVIZ_FILE_CACHING @BR
  * @ref DIRECTVIZ_FUZZY_LIGHTS @BR
  * @ref DIRECTVIZ_GLOBAL_SHADOW @BR
  * @ref DIRECTVIZ_GLOSSY_SURFACES @BR
  * @ref DIRECTVIZ_MAX_ACCUMULATION_VALUE @BR
  * @ref DIRECTVIZ_NUM_ENV_LIGHTS @BR
  * @ref DIRECTVIZ_NUM_FUZZY_SAMPLES @BR
  * @ref DIRECTVIZ_NUM_THREADS_MASTER @BR
  * @ref DIRECTVIZ_NUM_THREADS_SLAVE @BR
  * @ref DIRECTVIZ_OPENRTRT_CAMERA_SHADER @BR
  * @ref DIRECTVIZ_PROGRESSIVE_RENDERING @BR
  * @ref DIRECTVIZ_RECURSION_LIMIT @BR
  * @ref DIRECTVIZ_RENDER_STEPS @BR
  * @ref DIRECTVIZ_RENDERING_OBJECT @BR
  * @ref DIRECTVIZ_SAMPLES_PER_PIXEL @BR
  * @ref DIRECTVIZ_SOFT_SHADOWS @BR
  * @ref DIRECTVIZ_SUB_RECURSION @BR
  * @ref DIRECTVIZ_SUBSAMPLING @BR
  * @ref DIRECTVIZ_SUBSAMPLING_FACTOR @BR
  * @ref FXVIZ_SHADOW_TEXTURE_UNIT0 @BR
  * @ref FXVIZ_SHADOW_TEXTURE_UNIT1 @BR
  * @ref IV_ALLOW_LOCATE_HIGHLIGHT @BR
  * @ref IV_AUTO_CACHE_MAX_VALUE @BR
  * @ref IV_AUTO_CACHE_MIN_VALUE @BR
  * @ref IV_NO_TEXTURE_OBJECT @BR
  * @ref IV_NO_VERTEX_ARRAY @BR
  * @ref IV_OCTREE_MAX_DEPTH @BR
  * @ref IV_SEPARATOR_MAX_CACHES @BR
  * @ref IV_TIMER_RESOLUTION @BR
  * @ref IVT_NO_PLUGINS @BR
  * @ref IVT_PLUGINS_DIRECTORY @BR
  * @ref IVVR_40_COMPAT @BR
  * @ref IVVR_CHECK_3DTEX_SIZE @BR
  * @ref IVVR_DEBUG @BR
  * @ref IVVR_DELAY_RENDER @BR
  * @ref IVVR_GPU_PICKING @BR
  * @ref IVVR_IRREGULAR_TRACE_NUM @BR
  * @ref IVVR_INCONSTANT_TRACE_LENGTH @BR
  * @ref IVVR_MAX_NUM_LOADERS @BR
  * @ref IVVR_NUM_LOADERS @BR
  * @ref IVVR_OGL_CLIPPING @BR
  * @ref IVVR_SEGY_DUMP @BR
  * @ref IVVR_SEGY_FLOATISIEEE @BR
  * @ref IVVR_SEGY_SWAPBYTES @BR
  * @ref IVVR_SHADERS_PATH @BR
  * @ref IVVR_TF_TEX_UNIT @BR
  * @ref IVVR_USE_TEX3D @BR
  * @ref IVVR_FIRST_RESERVED_TEXTURE_UNIT @BR
  * @ref LDM_USE_IN_MEM_COMPRESSION @BR
  * @ref MESHVIZ_OCTREE_CACHE_CELLBBOX @BR
  * @ref MESHVIZ_OCTREE_MAX_DEPTH @BR
  * @ref MESHVIZ_OCTREE_MAX_CELL_PER_TILE @BR
  * @ref MESHVIZ_POLYGON_OFFSET @BR
  * @ref MESHVIZ_TESSELLATION_MAX_DEPTH @BR
  * @ref OIV_3DDATA_CREASE_ANGLE @BR
  * @ref OIV_3DDATA_CROSS_SECTION_METHOD @BR
  * @ref OIV_3DDATA_USE_TRIANGLE_STRIP_SET @BR
  * @ref OIV_ALPHA_TEST @BR
  * @ref OIV_ALUT_NAME @BR
  * @ref OIV_AMBIENT_COLOR @BR
  * @ref OIV_AMBIENT_INTENSITY @BR
  * @ref OIV_AUTO_CLIPPING @BR
  * @ref OIV_AUTO_CLIP_TOLERANCE @BR
  * @ref OIV_BACKGROUND_COLOR @BR
  * @ref OIV_BUFFER_REGION_ENABLE @BR
  * @ref OIV_CACHE_MODE @BR
  * @ref OIV_CAMERA_TYPE @BR
  * @ref OIV_CG_FRAG_PROFILE @BR
  * @ref OIV_CG_VTX_PROFILE @BR
  * @ref OIV_CGM_HARDCOPY_BUFSIZE @BR
  * @ref OIV_CLIP_TEXT2 @BR
  * @ref OIV_COLORWHEEL_DBUF @BR
  * @ref OIV_COMPAT_24 @BR
  * @ref OIV_COMPAT_30 @BR
  * @ref OIV_COMPAT_40 @BR
  * @ref OIV_COMPAT_CGM_HARDCOPY_400 @BR
  * @ref OIV_COMPAT_HPGL_HARDCOPY_370 @BR
  * @ref OIV_COMPAT_CONTEXT_80 @BR
  * @ref OIV_COMPLEXITY @BR
  * @ref OIV_COMPLEXITY_TYPE @BR
  * @ref OIV_CONFIG_FILE @BR
  * @ref OIV_CREASE_ANGLE_FIX @BR
  * @ref OIV_CSG_BUFFER_REGION @BR
  * @ref OIV_CURSOR_STYLE @BR
  * @ref OIV_DATABASE_CHECK @BR
  * @ref OIV_DEBUG_CONFIG @BR
  * @ref OIV_DEBUG_PIXEL_FORMAT @BR
  * @ref OIV_DEFAULT_ACTION_USE_ALTERNATEREP @BR
  * @ref OIV_DECIMATION_GOAL_FPS @BR
  * @ref OIV_DECIMATION_GOAL_NUM_OF_TRIANGLES @BR
  * @ref OIV_DECIMATION_PERCENTAGE @BR
  * @ref OIV_DECIMATION_STRATEGY @BR
  * @ref OIV_DELAYED_SORTED_LAYERS_TEXTURE_UNIT @BR
  * @ref OIV_DISABLE_DRAGGER_CTRL_KEY @BR
  * @ref OIV_DISABLED_GL_EXTENSION_LIST @BR
  * @ref OIV_DRAW_OCTREE @BR
  * @ref OIV_ENABLE_PNG_BACKGROUND @BR
  * @ref OIV_ENVIRONMENT_ATTENUATION @BR
  * @ref OIV_EXTRUSION_EPSILON @BR
  * @ref OIV_FACE_TYPE @BR
  * @ref OIV_FILE_SEARCH_PATHS @BR
  * @ref OIV_FOG_COLOR @BR
  * @ref OIV_FOG_TYPE @BR
  * @ref OIV_FOG_VISIBILITY @BR
  * @ref OIV_FONT_NAME @BR
  * @ref OIV_FONT_PATH @BR
  * @ref OIV_FONT_RENDERSTYLE @BR
  * @ref OIV_FONT_SIZE @BR
  * @ref OIV_FORCE_DUAL_TEX_SHADOW @BR
  * @ref OIV_FORCE_GLU_NURBS @BR
  * @ref OIV_FORCE_PIXEL_FORMAT @BR
  * @ref OIV_FORCE_TEX_COORD_SENDING @BR
  * @ref OIV_FORCE_USE_VBO @BR
  * @ref OIV_FREETYPE_NAME @BR
  * @ref OIV_FULL_RENDER_WHEN_STILL @BR
  * @ref OIV_FULL_SCENE_ANTIALIASING @BR
  * @ref OIV_FULL_SCENE_ANTIALIASING_FILTER @BR
  * @ref OIV_GL_SMOOTHING @BR
  * @TD
  * @ref OIV_GLSL_DEBUG @BR
  * @ref OIV_HC_BLACK_AND_WHITE @BR
  * @ref OIV_HCGDI_APPCONTROL @BR
  * @ref OIV_HCGDI_EDGE_WIDTH @BR
  * @ref OIV_HCGDI_POLYGON_COMPAT @BR
  * @ref OIVHOME @BR
  * @ref OIVARCH @BR
  * @ref OIV_INTERACTIVE_DRAW_STYLE @BR
  * @ref OIV_INTERSECT_EPSILON @BR
  * @ref OIV_LD_LIBRARY_PATH @BR
  * @ref OIV_LIBACIS_NAME @BR
  * @ref OIV_LIBDXF_NAME @BR
  * @ref OIV_LIBFLT_NAME @BR
  * @ref OIV_LIBJASPER_NAME @BR
  * @ref OIV_LIBJPEG_NAME @BR
  * @ref OIV_LIBPNG_NAME @BR
  * @ref OIV_LIBPROJ4_NAME @BR
  * @ref OIV_LIBTIFF_NAME @BR
  * @ref OIV_LINE_WIDTH @BR
  * @ref OIV_LOWRESHIGHPERCENT @BR
  * @ref OIV_LOWRESLOWPERCENT @BR
  * @ref OIV_LOWRESRENDER @BR
  * @ref OIV_MATERIALS_PATH @BR
  * @ref OIV_MAX_ANNO_RENDER2D_SIZE @BR
  * @ref OIV_MAX_CACHES @BR
  * @ref OIV_MAX_FONT_CACHES @BR
  * @ref OIV_MAX_TEXTURED_FONT_RES @BR
  * @ref OIV_MIN_TEXTURED_FONT_RES @BR
  * @ref OIV_MIN_VERTEX_VA @BR
  * @ref OIV_MIN_VERTEX_VBO @BR
  * @ref OIV_MIN_VERTEX_VAVBO_NOCACHE @BR
  * @ref OIV_MOUSE_WHEEL_ENABLE @BR
  * @ref OIV_MP_CONFIG_FILE @BR
  * @ref OIV_MULTITHREAD @BR
  * @ref OIV_MULTITEXTURING @BR
  * @ref OIV_NO_FBO @BR
  * @ref OIV_NO_FLEXNET @BR
  * @ref OIV_NURBS_FIX_TRIM_CONNECTIONS @BR
  * @ref OIV_NURBS_FORCE_GLU_CONVEXISATION @BR
  * @ref OIV_NURBS_CHECK_RATIONAL_TRIM_OUTSIDE_DOMAIN @BR
  * @ref OIV_NO_IVTUNE @BR
  * @ref OIV_IVTUNE_SHORTCUT @BR
  * @ref OIV_NO_OVERLAYS @BR
  * @ref OIV_NORMGEN_COMPAT @BR
  * @ref OIV_NORMGEN_TOLERANCE @BR
  * @ref OIV_SEPARATE_SPECULAR_SUPPORT @BR
  * @ref OIV_NO_SHADER_LAYERS_BLEND @BR
  * @ref OIV_NO_TEX_TRIM_NURBS @BR
  * @ref OIV_NO_VBO @BR
  * @ref OIV_NUM_RENDER_PASSES @BR
  * @ref OIV_NUM_SORTED_LAYERS_PASSES @BR
  * @ref OIV_OGLLIB_PATH @BR
  * @ref OIV_OLD_ERROR_HANDLER @BR
  * @ref OIV_OPENAL_NAME @BR
  * @ref OIV_PBUFFER_DEBUG @BR
  * @ref OIV_PBUFFER_ENABLE @BR
  * @ref OIV_PERFCOUNTER_ENABLE @BR
  * @ref OIV_PFD_SUPPORT_COMPOSITION @BR
  * @ref OIV_PFD_SUPPORT_GDI @BR
  * @ref OIV_POLYGON_OFFSET @BR
  * @ref OIV_POLYGON_OFFSET_FACTOR @BR
  * @ref OIV_POLYGON_OFFSET_STYLES @BR
  * @ref OIV_POLYGON_OFFSET_UNITS @BR
  * @ref OIV_PRIORITIZE_CHILDREN_CACHING @BR
  * @ref OIV_PSFONT_PATH @BR
  * @ref OIV_QT_TIMER_THREAD @BR
  * @ref OIV_REMOTE_ENABLE @BR
  * @ref OIV_REMOTE_PORT @BR
  * @ref OIV_REMOTE_TIMING @BR
  * @ref OIV_REMOTERENDER @BR
  * @ref OIV_REMOTERENDER_BUFFER @BR
  * @ref OIV_REMOTERENDER_DEBUG @BR
  * @ref OIV_REMOTERENDER_DISPLAY @BR
  * @ref OIV_REPORT_ZERO_VECTORS @BR
  * @ref OIV_REQUIRE_STENCIL @BR
  * @ref OIV_SEEK_TIME @BR
  * @ref OIV_SHADER_CHECK_INTERVAL @BR
  * @ref OIV_SHAPE_TYPE @BR
  * @ref OIV_SHARE_GEOM_MUTEX @BR
  * @ref OIV_SHARE_LISTS @BR
  * @ref OIV_SORTED_LAYERS_TEXTURE_UNIT @BR
  * @ref OIV_STEREO_ACTIVE @BR
  * @ref OIV_STEREO_BALANCE @BR
  * @ref OIV_STEREO_BALANCE_NEAR_FRAC @BR
  * @ref OIV_STEREO_GREENSHIFT @BR
  * @ref OIV_STEREO_ERROR_DIALOG @BR
  * @ref OIV_STEREO_OFFSET @BR
  * @ref OIV_STEREO_TESTPATTERN @BR
  * @ref OIV_STEREO_TYPE @BR
  * @ref OIV_STILL_DRAW_STYLE @BR
  * @ref OIV_STREAM_BUFFERS_NUMBER @BR
  * @ref OIV_STREAM_BUFFERS_SIZE @BR
  * @ref OIV_STROKE_FONT_PATH @BR
  * @ref OIV_TEXTURE_BORDER_CLAMP_ENABLE @BR
  * @ref OIV_TEXTURE_QUALITY @BR
  * @ref OIV_TEXTURED_TEXT_NO_MIPMAP @BR
  * @ref OIV_TRACKER_DIRECT_MODE @BR
  * @ref OIV_TRANSPARENCY_TYPE @BR
  * @ref OIV_TRANSPARENT_PIXEL @BR
  * @ref OIV_UPDATE_AREA_COMPAT @BR
  * @ref OIV_USE_GLOBALFIELD_TIME @BR
  * @ref OIV_USE_HEADLIGHT @BR
  * @ref OIV_USE_NPOT @BR
  * @ref OIV_USE_OOB @BR
  * @ref OIV_USER_LIBS @BR
  * @ref OIV_VERTEX_ATTRIBS @BR
  * @ref OIV_VERTEX_ORDERING @BR
  * @ref OIV_VIEWER_ANIMATION @BR
  * @ref OIV_VIEWER_DECORATION @BR
  * @ref OIV_VIEWER_POPUP_MENU @BR
  * @ref OIV_VIEWER_SIZE @BR
  * @ref OIV_VIEWERS_SHOW_DIRECTVIZ_ENTRY @BR
  * @ref OIV_VIEWERS_SHOW_RECORD_ENTRY @BR
  * @ref OIV_VIEWERS_SHOW_FSAA_ENTRY @BR
  * @ref OIV_VIEWERS_SHOW_STEREO_ENTRY @BR
  * @ref OIV_VRML_IMAGETEXTURE_MODEL_SUPPORT @BR
  * @ref OIV_WHEEL_DELTA @BR
  * @ref OIV_WINDING_TYPE @BR
  * @ref OIV_ZERO_AREA_CHECK @BR
  * @ref OIV_ZLIB_NAME @BR
  * @ref OIV_SET_RAY_PRECISION @BR
  * @ref SO_DRAGGER_DIR @BR
  * @ref SCALEVIZ_CLUSTERCOM @BR
  * @ref SCALEVIZ_CONFIG_FILE @BR
  * @ref SCALEVIZ_CONNECT_TIMEOUT @BR
  * @ref SCALEVIZ_DISABLE_GUI @BR
  * @ref SCALEVIZ_GUI_SHORTCUT @BR
  * @ref SCALEVIZ_OIRU_DISPLAY @BR
  * @ref SCALEVIZ_OIRU_PATH @BR
  * @ref SCALEVIZ_USER_LIBS @BR
  * @ref SCALEVIZD_RESOURCES_FILE @BR
  * @ref TGS_LICENSE_DEBUG @BR
  * @ref TGS_LICENSE_FILE @BR
  * @ref TVIZ_COMPAT_20 @BR
  * @ref TVIZ_VIEWER_DATA_PATH @BR
  * @ref VSG_LICENSE_DEBUG @BR
  * @ref VSG_LICENSE_FILE @BR
  * @TABLE_END
  *
  * @anchor DIALOGVIZ_SKIN @B DIALOGVIZ_SKIN @b @BR
  * Affects DialogViz. Specifies the skin that will be used for
  * DialogViz 3D component rendering. Default value is "default".
  * The value should be the name of the directory containing
  * the skin components. The skin examples available with Open Inventor
  * are "default", "texture", and "transparent". See also DIALOGVIZ_SKINS_DIR.
  *
  * @anchor DIALOGVIZ_SKINS_DIR @B DIALOGVIZ_SKINS_DIR @b @BR
  * Affects DialogViz. Specifies the path to the directory
  * containing DialogViz skin directories. By default,
  * the skin directory is $OIVHOME/data/DialogViz/Skins/.
  * See also DIALOGVIZ_SKIN.
  *
  * @anchor DIRECTVIZ_ACCUMULATION @B DIRECTVIZ_ACCUMULATION @b @BR
  * Affects DirectViz.
  * If set to 1, enables accumulation oversampling.
  * The value can be set programmatically using the
  * SoDirectVizManager::accumulation field.
  * Default value is 1.
  *
  * @anchor DIRECTVIZ_ADAPTIVE_OVERSAMPLING @B DIRECTVIZ_ADAPTIVE_OVERSAMPLING @b @BR
  * Affects DirectViz.
  * If set to 1, enables adaptive oversampling.
  * The value can be set using the
  * SoDirectVizManager::adaptiveOversampling field.
  * Default value is 0.
  *
  * @anchor DIRECTVIZ_ADAPTIVE_OVERSAMPLING_VISUAL @B DIRECTVIZ_ADAPTIVE_OVERSAMPLING_VISUAL @b @BR
  * Affects DirectViz.
  * If set to 1 and DIRECTVIZ_ADAPTIVE_OVERSAMPLING is set to 1, enables
  * visualisation of adaptive oversampled pixels (Oversampled pixels are then colored).
  * Default value is 0.
  *
  * @anchor DIRECTVIZ_ALWAYS_SUBSAMPLED @B DIRECTVIZ_ALWAYS_SUBSAMPLED @b @BR
  * Affects DirectViz.
  * If set to 1, DirectViz rendering is always subsampled
  * Default value is 0.
  *
  * @anchor DIRECTVIZ_CACHE_DIR @B DIRECTVIZ_CACHE_DIR @b @BR
  * Affects DirectViz.
  * Specifies the directory (absolute path) to contain the DirectViz render caches.
  * The value can be set programmatically using
  * SoDirectVizManager::setCacheDirectory().
  *
  * @anchor DIRECTVIZ_CLUSTER @B DIRECTVIZ_CLUSTER @b @BR
  * Affects DirectViz.
  * If greater than 0, requests that DirectViz be run in cluster mode,
  * and specifies the desired number of slaves. If set to 0,
  * DirectViz runs in stand-alone mode.
  * Default value is 0.
  *
  * @anchor DIRECTVIZ_CONTROL_DIALOG @B DIRECTVIZ_CONTROL_DIALOG @b @BR
  * Affects DirectViz.
  * If set to 1, enables display of the DirectViz control dialog.
  * The value can be set programmatically using the
  * SoDirectVizManager::controlDialog field, or with
  * showDirectVizDialog() of the corresponding Open Inventor viewer.
  * Default value is 1.
  *
  * @anchor DIRECTVIZ_DIALOG_SHORTCUT @B DIRECTVIZ_DIALOG_SHORTCUT @b @BR
  * Affects DirectViz.
  * If set, this value overrides the default keyboard key which combined with the shift key
  * launches the Directviz dialog. The value format is hexadecimal, see SoKeyboardEvent.h
  * for possible values.
  * Default value is 0xFFC5 (F8 key)
  *
  * @anchor DIRECTVIZ_ENV_LIGHTS_SCALE @B DIRECTVIZ_ENV_LIGHTS_SCALE @b @BR
  * Affects DirectViz.
  * Sets the scale applied to environment lights luminance.
  * The value can be set using the
  * SoDirectVizManager::envLightIntensityScale field.
  * Default value is 1.
  *
  * @anchor DIRECTVIZ_FILE_CACHING @B DIRECTVIZ_FILE_CACHING @b @BR
  * Affects DirectViz.
  * If set to 1, enables file caching.
  * The value can be set programmatically using the
  * SoDirectVizManager::fileCaching field.
  * Default value is 0.
  *
  * @anchor DIRECTVIZ_FUZZY_LIGHTS @B DIRECTVIZ_FUZZY_LIGHTS @b @BR
  * Affects DirectViz.
  * If set to 1, enables fuzzy light effects.
  * The value can be set using the
  * SoDirectVizManager::fuzzyLights field.
  * Default value is 0.
  *
  * @anchor DIRECTVIZ_GLOBAL_SHADOW @B DIRECTVIZ_GLOBAL_SHADOW @b @BR
  * Affects DirectViz.
  * If set to 1, enables global shadowing.
  * The value can be set programmatically using the
  * SoDirectVizManager::globalShadowing field.
  * Default value is 0.
  *
  * @anchor DIRECTVIZ_GLOSSY_SURFACES @B DIRECTVIZ_GLOSSY_SURFACES @b @BR
  * Affects DirectViz.
  * If set to 1, enables glossy surfaces effects.
  * The value can be set using the
  * SoDirectVizManager::glossySurfaces field.
  * Default value is 0.
  *
  * @anchor DIRECTVIZ_MAX_ACCUMULATION_VALUE @B DIRECTVIZ_MAX_ACCUMULATION_VALUE @b @BR
  * Affects DirectViz.
  * The value can be set programmatically using the
  * SoDirectVizManager::maxAccumulationValue field.
  * Default value is 10.
  *
  * @anchor DIRECTVIZ_NUM_ENV_LIGHTS @B DIRECTVIZ_NUM_ENV_LIGHTS @b @BR
  * Affects DirectViz.
  * Set the number of environment lights to use.
  * The value can be set using the
  * SoDirectVizManager::numEnvLights field.
  * Default value is 0.
  *
  * @anchor DIRECTVIZ_NUM_FUZZY_SAMPLES @B DIRECTVIZ_NUM_FUZZY_SAMPLES @b @BR
  * Affects DirectViz.
  * Specifies the number of samples used to generate glossy effects and
  * soft shadows.
  * Default value is 1.
  *
  * @anchor DIRECTVIZ_NUM_THREADS_MASTER @B DIRECTVIZ_NUM_THREADS_MASTER @b @BR
  * Affects DirectViz.
  * Specifies the number of threads to be used by a multi-core or
  * multi-processor machine. The number of threads should correspond to the number
  * of processors possibly multiplied by the number of cores of each processor; otherwise there may be some
  * unnecessary overhead.
  * Default value is 4.
  *
  * @anchor DIRECTVIZ_NUM_THREADS_SLAVE @B DIRECTVIZ_NUM_THREADS_SLAVE @b @BR
  * Affects DirectViz.
  * When a multi-processor or multi-core machine is used as a slave in a cluster
  * configuration,
  * specifies the number of threads per slave. The number of threads should correspond to the number
  * of processors possibly multiplied by the number of cores of each processor; otherwise there may be some
  * unnecessary overhead.
  * Default value is 4.
  *
  * @anchor DIRECTVIZ_OPENRTRT_CAMERA_SHADER @B DIRECTVIZ_OPENRTRT_CAMERA_SHADER @b @BR
  * Affects DirectViz.
  * If set to 1, uses OpenRTRT camera shader instead of DirectViz's one.
  * Default value is 0.
  *
  * @anchor DIRECTVIZ_PROGRESSIVE_RENDERING @B DIRECTVIZ_PROGRESSIVE_RENDERING @b @BR
  * Affects DirectViz.
  * If set to 1, enables progressive rendering.
  * The value can be set programmatically using the
  * SoDirectVizManager::progressiveRendering field.
  * Default value is 0.
  *
  * @anchor DIRECTVIZ_RECURSION_LIMIT @B DIRECTVIZ_RECURSION_LIMIT @b @BR
  * Affects DirectViz.
  * The recursion limit is the maximum number of times that a ray can
  * "bounce" within the scene when rendering a frame. The higher the
  * recursion limit is, the more accurate the scene appears.
  * The value can be set programmatically using the
  * SoDirectVizManager::recursionLimit field.
  * Default value is 20.
  *
  * @anchor DIRECTVIZ_RENDER_STEPS @B DIRECTVIZ_RENDER_STEPS @b @BR
  * Affects DirectViz.
  * Specifies the number of steps between a subsampled render and full
  * rendering. Must be greater than 0.
  * The value can be set programmatically using the
  * SoDirectVizManager::numProgressiveRenderingSteps field.
  * Default value is 5.
  *
  * @anchor DIRECTVIZ_RENDERING_OBJECT @B DIRECTVIZ_RENDERING_OBJECT @b @BR
  * Affects DirectViz.
  * Specifies the DirectViz shader package. See the User's Guide
  * for details.
  * Default value is "RTX".
  *
  * @anchor DIRECTVIZ_SUB_RECURSION @B DIRECTVIZ_SUB_RECURSION @b @BR
  * Affects DirectViz.
  * Specifies the recursion depth limit (when sub-sampling is active).
  * The value can be set programmatically using the
  * SoDirectVizManager::subRecursion field.
  * Default value is 1.
  *
  * @anchor DIRECTVIZ_SAMPLES_PER_PIXEL @B DIRECTVIZ_SAMPLES_PER_PIXEL @b @BR
  * Affects DirectViz.
  * Sets the number of per pixel samples.
  * Default value is 1.
  *
  * @anchor DIRECTVIZ_SHOW_VIEWER_ENTRY @B DIRECTVIZ_SHOW_VIEWER_ENTRY @b @BR
  * Affects DirectViz.
  * If set to 0, DirectViz viewer menu entry is not shown
  * Default value is 1.
  *
  * @anchor DIRECTVIZ_SOFT_SHADOWS @B DIRECTVIZ_SOFT_SHADOWS @b @BR
  * Affects DirectViz.
  * If set to 1, enables soft shadows.
  * The value can be set using the
  * SoDirectVizManager::softShadows field.
  * Default value is 0.
  *
  * @anchor DIRECTVIZ_SUBSAMPLING @B DIRECTVIZ_SUBSAMPLING @b @BR
  * Affects DirectViz.
  * If set to 1, enables subsampling.
  * Sub-sampling the scene consists of rendering a smaller (i.e., lower
  * resolution) image when the viewer is not still.
  * The value can be set programmatically using the
  * SoDirectVizManager::subSampling field.
  * Default value is 1.
  *
  * @anchor DIRECTVIZ_SUBSAMPLING_FACTOR @B DIRECTVIZ_SUBSAMPLING_FACTOR @b @BR
  * Affects DirectViz.
  * Specifies the subsampling factor. Values can range from 0.1
  * to 1.0 (full resolution).
  * The value can be set programmatically using the
  * SoDirectVizManager::subSamplingFactor field.
  * Default value is 0.5.
  *
  * @anchor FXVIZ_SHADOW_TEXTURE_UNIT0 @B FXVIZ_SHADOW_TEXTURE_UNIT0 @b @BR
  * SoShadowGroup reserves texture unit FXVIZ_SHADOW_TEXTURE_UNIT0 and FXVIZ_SHADOW_TEXTURE_UNIT1
  * for its rendering. If these values are not set, texture units 1 and 2 are used. These values
  * can't be greater than 3.
  *
  * @anchor FXVIZ_SHADOW_TEXTURE_UNIT1 @B FXVIZ_SHADOW_TEXTURE_UNIT1 @b @BR
  * SoShadowGroup reserves texture unit FXVIZ_SHADOW_TEXTURE_UNIT0 and FXVIZ_SHADOW_TEXTURE_UNIT1
  * for its rendering. If these values are not set, texture units 1 and 2 are used. These values
  * can't be greater than 3.
  *
  * @anchor IV_ALLOW_LOCATE_HIGHLIGHT @B IV_ALLOW_LOCATE_HIGHLIGHT @b @BR
  * Affects SoLocateHighlight. @BR
  * If set, the default SoLocateHighlight mode is set to AUTO.
  * If not set, the default mode is OFF.
  *
  * @anchor IV_AUTO_CACHE_MIN_VALUE @B IV_AUTO_CACHE_MIN_VALUE @b @BR
  * @anchor IV_AUTO_CACHE_MAX_VALUE @B IV_AUTO_CACHE_MAX_VALUE @b @BR
  * These influence when automatic caching happens.
  * If set, then shapes with a number of vertices smaller than IV_AUTO_CACHE_MIN_VALUE
  * or greater than IV_AUTO_CACHE_MAX_VALUE will request that their parent separator
  * not use render caching.  This can be useful, for example, when creating a render
  * cache for a very large geometry would use too much additional memory.
  *
  * @anchor IV_NO_TEXTURE_OBJECT @B IV_NO_TEXTURE_OBJECT @b @BR
  * Tells Open Inventor not to use OpenGL 1.1 texture objects.
  * If some textures are missing or otherwise displayed incorrectly,
  * try setting this variable.
  *
  * @anchor IV_NO_VERTEX_ARRAY @B IV_NO_VERTEX_ARRAY @b @BR
  * Tells Open Inventor not to use OpenGL 1.1 vertex arrays.
  * If some geometry is missing or misshapen, try setting this variable.
  *
  * @anchor IV_OCTREE_MAX_DEPTH @B IV_OCTREE_MAX_DEPTH @b @BR
  * Affects SoOctreeOrdering. @BR
  * Specifies the maximum depth used during octree ordering. Default: 8
  *
  * @anchor IV_SEPARATOR_MAX_CACHES @B IV_SEPARATOR_MAX_CACHES @b [Deprecated] @BR
  * Deprecated, please use OIV_MAX_CACHES instead.
  *
  * @anchor IV_TIMER_RESOLUTION @B IV_TIMER_RESOLUTION @b [Win32 only] @BR
  * Specifies how often Open Inventor's internal clock ticks.
  * Effectively it sets the minimum time between render traversals
  * when animating (including spin animation and animation performed
  * by engines). Make sure the value is less than the time it takes
  * to render one frame of your scene. Default: 10 ms.
  *
  * @anchor IVT_NO_PLUGINS @B IVT_NO_PLUGINS @b @BR
  * Tells IvTune not to load the plugins.
  *
  * @anchor IVT_PLUGINS_DIRECTORY @B IVT_PLUGINS_DIRECTORY @b @BR
  * Specifies the path where IvTune will look for the plugins to load.
  *
  * @anchor IVVR_40_COMPAT @B IVVR_40_COMPAT @b @BR
  * Forces VolumeViz 4.0 compatible behavior. For example, paging mode
  * is the default, slices are not affected by scene graph lights, etc.
  *
  * @anchor IVVR_CHECK_3DTEX_SIZE @B IVVR_CHECK_3DTEX_SIZE @b @BR
  * Set this config parameter to enable 3D texture size checking for VolumeViz.
  * If the current
  * volume cannot be loaded on the hardware as a 3D texture, a warning is posted
  * and VolumeViz automatically switches to 2D textures to draw the picture.
  *
  * @anchor IVVR_DEBUG @B IVVR_DEBUG @b @BR
  * Set to 1 to enable debug trace output for VolumeViz.
  *
  * @anchor IVVR_DELAY_RENDER @B IVVR_DELAY_RENDER @b @BR
  * Sets the VolumeViz delayedRendering flag. @BR
  * When this flag is TRUE (1), VolumeViz drawing nodes (e.g. SoOrthoSlice) are
  * considered "transparent" objects by Open Inventor.  They may be delayed
  * (until after all opaque objects) and/or sorted according to the current
  * transparency type (see SoGLRenderAction). This may result in a more
  * correct image if there is opaque geometry intersecting the volume.
  * However delayed/sorted rendering may slightly decrease performance.
  * For compatibility with earlier versions of VolumeViz the default is FALSE.
  * This flag may also be set using SoVolumeRendering::setDelayedRendering().
  *
  * @anchor IVVR_GPU_PICKING @B IVVR_GPU_PICKING @b @BR
  * When this flag is TRUE (1), SoVolumeRender (VolumeViz) will use the GPU to compute the picked
  * voxel color. Default is TRUE.
  *
  * @anchor IVVR_IRREGULAR_TRACE_NUM @B IVVR_IRREGULAR_TRACE_NUM @b @BR
  * Affects SoVRSegyFileReader. @BR
  * Although in most cases the SEGY reader can automatically detect when the
  * number of traces per line in a SEGY file is not uniform, in some cases it
  * cannot. You can set this environment variable
  * to request the use of a more sophisticated file parsing algorithm.
  * However, be aware that the initialization for file reading will take longer when
  * this environment variable is set.
  *
  * @anchor IVVR_INCONSTANT_TRACE_LENGTH @B IVVR_INCONSTANT_TRACE_LENGTH @b @BR
  * Affects SoVRSegyFileReader. @BR
  * Although in most cases the SEGY reader can automatically detect when the
  * length of traces in a SEGY data file is not uniform, in some cases it cannot.
  * You can set this environment variable
  * to request the use of a more sophisticated file parsing algorithm.
  * However, be aware that the initialization for file reading will take significantly
  * longer when this environment variable is set.
  *
  * @anchor IVVR_MAX_NUM_LOADERS @B IVVR_MAX_NUM_LOADERS @b @BR
  * Affects SoVolumeRender. @BR
  * Specifies the maximum number of loading threads
  * to be used in VolumeViz LDM mode.
  *
  * @anchor IVVR_NUM_LOADERS @B IVVR_NUM_LOADERS @b @BR
  * Affects SoVolumeRender. @BR
  * Specifies the initial number of loading threads
  * to be used in VolumeViz LDM mode. Default is 4.
  * This value can be set programmatically using SoVolumeRendering::setNumIO().
  *
  * @anchor IVVR_OGL_CLIPPING @B IVVR_OGL_CLIPPING @b @BR
  * Affects SoVolumeGeometry. @BR
  * Starting with VolumeViz 6.0, SoVolumeGeometry nodes are clipped using
  * software clipping rather than OpenGL clipping. If
  * you need the version 5.0 behavior, set this environment
  * variable to 1.
  *
  * @anchor IVVR_SEGY_DUMP @B IVVR_SEGY_DUMP @b @BR
  * Affects SoVRSegyFileReader. @BR
  * Requests that the file and trace headers be written to a file while processing
  * the SEGY data file. The output file is named ivvrSegyDump.txt in
  * the current working directory. This information may be helpful
  * if the SEGY reader fails to read the file correctly.
  *
  * @anchor IVVR_SEGY_FLOATISIEEE @B IVVR_SEGY_FLOATISIEEE @b @BR
  * Affects SoVRSegyFileReader. @BR
  * If TRUE (1), indicates that floats are written in IEEE floating point format.
  * Normally the SEGY reader is able to detect this,
  * but if necessary you can set this environment variable.
  *
  * @anchor IVVR_SEGY_SWAPBYTES @B IVVR_SEGY_SWAPBYTES @b @BR
  * Affects SoVRSegyFileReader. @BR
  * Set to 1 to force byte swapping, 0 to force no byte swapping.
  * Normally the SEGY reader is able to
  * detect if byte swapping is needed,
  * but if necessary you can set this environment variable.
  *
  * @anchor IVVR_SHADERS_PATH @B IVVR_SHADERS_PATH @b @BR
  * Specifies the full path to VolumeViz predefined shaders. @BR
  * Nodes SoVolumeShader, SoVolumeIsosurface, and SoVolumeRenderingQuality search predefined
  * shaders in the following directories in the following order: current directory, $IVVR_SHADERS_PATH, and
  * $OIVHOME/data/volumeviz/shaders. On Windows, the directory containing the VolumeViz DLL
  * is searched last.
  *
  * @anchor IVVR_TF_TEX_UNIT @B IVVR_TF_TEX_UNIT @b @BR
  * Affects SoTransferFunction @BR
  * Allows you to specify the OpenGL texture unit to be used for storing VolumeViz
  * transfer functions. The default is unit 0.
  *
  * @anchor IVVR_USE_TEX3D @B IVVR_USE_TEX3D @b @BR
  * Controls when VolumeViz will use OpenGL 3D texturing. @BR
  * All boards that report OpenGL version 1.2 or higher are required to
  * support 3D texturing and will render the correct image. However on some
  * boards (e.g. GeForce2) this support is not hardware accelerated and may
  * be very slow.  By default VolumeViz tries to detect this situation and
  * automatically disable use of 3D textures, but there are cases where it
  * is desirable to use 3D textures even if they are slow.  In these cases
  * set IVVR_USE_TEX3D to 1.  Valid values are:
  *
  * -  0 = Never    : Do not use 3D textures (even when available)
  * -  1 = Always   : Use 3D textures if supported in hardware or software
  * - -1 = WhenFast : Use 3D textures only if supported in hardware (DEFAULT)
  *
  * On some boards, e.g. ATI, WhenFast is the same as Always because we can't
  * reliably detect how 3D textures are implemented.
  *
  * @TOBEREVIEWED
  * @anchor LDM_USE_IN_MEM_COMPRESSION @B LDM_USE_IN_MEM_COMPRESSION @b @BR
  * Allow to desactivate in memory compression introduced in OIV 8.5 Setting
  * the variable to zero will force LDM to work with uncompressed tiles in memory.
  * Settingthe variable to 1 let LDM manage tiles depending on their state (read from
  * compressed file, detected as uniform etc.) 
  *
  * @anchor IVVR_FIRST_RESERVED_TEXTURE_UNIT @B IVVR_FIRST_RESERVED_TEXTURE_UNIT @b @BR
  * Specifies the range of reserved texture units in VolumeViz for various nodes :
  *
  * - SoVolumeClippingGroup : All texture units between IVVR_FIRST_RESERVED_TEXTURE_UNIT
  *   and IVVR_FIRST_RESERVED_TEXTURE_UNIT-2*numPasses are reserved.
  *
  * - SoVolumeShader : All texture units between IVVR_FIRST_RESERVED_TEXTURE_UNIT and
  *   IVVR_FIRST_RESERVED_TEXTURE_UNIT+SoVolumeShader::getNumReservedTextures()-1
  *   are reserved.
  *
  * If IVVR_FIRST_RESERVED_TEXTURE_UNIT is not set, its default value is
  * SoFragmentShader::getMaxTextureImageUnit()-SoVolumeShader::getNumReservedTextures().
  * Note the value returned by SoVolumeShader::getNumReservedTextures() may change between
  * versions and must not be assumed constant.  Also note the maximum number of texture
  * units depends on the graphics hardware.
  *
  * @anchor MESHVIZ_OCTREE_CACHE_CELLBBOX @B MESHVIZ_OCTREE_CACHE_CELLBBOX @b @BR
  * Affects MeshViz. @BR
  * Specifies if the cell boundingboxes must be cached when building the octree associated
  * to a mesh. This speeds up the search for cells in the octree when using
  * MoMeshPointProbe, MoMeshGridPlaneSlice and MoMeshStreamline nodes,
  * or pointprobes, gridplaneslice and streamline extractors for all kind of meshes
  * (MiPointProbeUnstructured, MiGridPlaneSliceExtractUnstructured, MiStreamlineExtractUnstructured)
  * except regular and rectilinear that do not use octrees. @BR
  * The default value is 0 (not cached).
  *
  * @anchor MESHVIZ_OCTREE_MAX_CELL_PER_TILE @B MESHVIZ_OCTREE_MAX_CELL_PER_TILE @b @BR
  * Affects MeshViz. @BR
  * Specifies the maximum number of cells that can be contained in a tile of the
  * octree built when using MoMeshPointProbe, MoMeshGridPlaneSlice and MoMeshStreamline nodes,
  * or pointprobes, gridplaneslice and streamline extractors for all kind of meshes
  * (MiPointProbeUnstructured, MiGridPlaneSliceExtractUnstructured, MiStreamlineExtractUnstructured)
  * except regular and rectilinear that do not use octrees. @BR
  * The default value is 40.
  *
  * @anchor MESHVIZ_OCTREE_MAX_DEPTH @B MESHVIZ_OCTREE_MAX_DEPTH @b @BR
  * Affects MeshViz. @BR
  * Specifies the maximum depth allowed to build the octree associated to a mesh
  * when using MoMeshPointProbe, MoMeshGridPlaneSlice and MoMeshStreamline nodes,
  * or pointprobes, gridplaneslice and streamline extractors for all kind of meshes
  * (MiPointProbeUnstructured, MiGridPlaneSliceExtractUnstructured, MiStreamlineExtractUnstructured)
  * except regular and rectilinear that do not use octrees. @BR
  * The default value is 6.
  *
  * @anchor MESHVIZ_POLYGON_OFFSET @B MESHVIZ_POLYGON_OFFSET @b @BR
  * Affects MoMeshRepresentation. @BR
  * Specifies if surface representations must be automaticallty offset with a SoPolygonOffset node,
  * to allow line representations on top without artifacts. @BR
  * However SoPolygonOffset can introduce other artifacts on surfaces when the two-sided lighting mode is active.
  * The default value is TRUE (1).
  *
  * @anchor MESHVIZ_TESSELLATION_MAX_DEPTH @B MESHVIZ_TESSELLATION_MAX_DEPTH @b @BR
  * Affects MeshViz. @BR
  * Specifies the maximum depth allowed while tessellating a non-linear cell using
  * the provided implementations of the MiTessellator interface for extractions from quadratic meshes.
  * This parameter makes the tessellation stop once the specified depth has been reached. This prevents
  * from spending too much time in this process.
  * However, the tolerance given by MiEdgeErrorMetric might be not achieved if the maximum depth is low. @BR
  * The default value is 10 which leads to a maximum of 2^10 = 1024 resulting edges per tessellated edge.
  *
  * @anchor OIV_3DDATA_CREASE_ANGLE @B OIV_3DDATA_CREASE_ANGLE @b @BR
  * Default value of the field PoMesh::creaseAngle. Default is
  * 0.0. Set the
  * value to 0.8 for compatibility with MeshViz 5.0 and earlier.
  *
  * @anchor OIV_3DDATA_CROSS_SECTION_METHOD @B OIV_3DDATA_CROSS_SECTION_METHOD @b @BR
  * Affects PoMeshCrossSection. @BR
  * Specifies the method used for computing a PoMeshCrossSection.
  *
  * - INTERSECTION - The cross section is computed like an isosurface.
  *
  * - ISOSURFACE - The cross section is computed by doing classic
  * intersections.
  *
  * Use PoMeshCrossSection::setCrossSectionMethod to specify the
  * cross section computation method programmatically.
  *
  * @anchor OIV_3DDATA_USE_TRIANGLE_STRIP_SET @B OIV_3DDATA_USE_TRIANGLE_STRIP_SET @b @BR
  * Affects PoMeshLevelSurf, PoMeshCrossSection. @BR
  * Specifies the Open Inventor primitive used to draw an isosurface.
  *
  * - TRUE (1) - a triangle strip set is used
  *
  * - FALSE (0) - an indexed face set is used
  *
  * PoMeshCrossSection uses this variable only when the cross section method is ISOSURFACE
  * (see @ref OIV_3DDATA_CROSS_SECTION_METHOD).
  *
  * @anchor OIV_ALPHA_TEST @B OIV_ALPHA_TEST @b @BR
  * Affects SoGLRenderAction. @BR
  * Enables or disables the OpenGL alpha test for rendering.
  * Default is 0 (alpha test is disabled).
  *
  * @anchor OIV_ALUT_NAME @B OIV_ALUT_NAME @b @BR
  * Affects SoDynamicLibManager. @BR
  * Allows you to use your own ALut dynamic library.
  * Do not add the suffix.
  * Do not add the "lib" prefix on UNIX systems.
  * Do not add the final "D" used in the debug name.
  * Default is "IvDLALut".
  *
  * @anchor OIV_AMBIENT_COLOR @B OIV_AMBIENT_COLOR  @b@BR
  * Affects SoEnvironment.@BR
  * Specifies the default color of ambient lighting.
  * The value is specified as
  * three floats (0.0 to 1.0) representing the RGB values of the color.
  * The value can be set programmatically using the
  * SoEnvironment::ambientColor field.
  *
  * @anchor OIV_AMBIENT_INTENSITY @B OIV_AMBIENT_INTENSITY  @b@BR
  * Affects SoEnvironment.@BR
  * Specifies the default intensity of ambient lighting.
  * The value can be set programmatically using the
  * SoEnvironment::ambientIntensity field.
  *
  * @anchor OIV_AUTO_CLIPPING @B OIV_AUTO_CLIPPING  @b@BR
  * Affects SoWinViewer, SoQtViewer, SoXtViewer.@BR
  * Specifies the default auto clipping flag (0=off, 1=on).
  * The auto clipping flag can be set programmatically using the setAutoClipping
  * method of the viewers classes above.
  *
  * @anchor OIV_AUTO_CLIP_TOLERANCE @B OIV_AUTO_CLIP_TOLERANCE  @b@BR
  * Affects SoWinViewer, SoQtViewer, SoXtViewer.@BR
  * Specifies the default auto clip tolerance (a float).
  * The tolerance can be set programmatically using the
  * setAutoClipTolerance method of the viewers classes above.
  *
  * @anchor OIV_BACKGROUND_COLOR @B OIV_BACKGROUND_COLOR @b @BR
  * Affects SoSceneManager, SoWinRenderArea, SoXtRenderArea,
  * SoQtRenderArea, SoMPEGRenderer,
  * SoXtMPRenderArea, SoWinMPRenderArea,
  * SoOffscreenRenderer, SoBigImageRenderer.@BR
  * Specifies the default background color. The value is specified as
  * three floats (0.0 to 1.0) representing the RGB values of the color.
  * The background color can be set programmatically using the setBackgroundColor
  * method of the classes above.
  *
  * @anchor OIV_BUFFER_REGION_ENABLE @B OIV_BUFFER_REGION_ENABLE @b @BR
  * Affects SoBufferRegion, SoGLRenderAction. @BR
  * If not specified, the OpenGL extension bufferRegion is enabled and
  * will be used if available on your graphics hardware.
  * Set to zero to disable use of buffer regions.
  *
  * @anchor OIV_CACHE_MODE @B OIV_CACHE_MODE @b @BR
  * If set to 1, Open Inventor 3.0 render caching behavior is used.
  * This may be necessary to produce correct results with some
  * graphics boards.
  *
  * @anchor OIV_CAMERA_TYPE @B OIV_CAMERA_TYPE @b @BR
  * Affects IvfDocument, IvfRenderArea, SoSceneViewer, SoQtViewer, SoWinViewer, SoXtViewer.@BR
  * Specifies what kind of camera the viewer should create if none
  * is provided. By default, a Perspective camera is created. To request
  * an Orthographic camera, specify "o", "O", or "0".
  *
  * @anchor OIV_CG_FRAG_PROFILE @B OIV_CG_FRAG_PROFILE @b @BR
  * Specifies the Cg profile to be used for fragment programs. @B arbfp1 @b by default.
  * See SoShaderObject for details.
  *
  * @anchor OIV_CG_VTX_PROFILE @B OIV_CG_VTX_PROFILE @b @BR
  * Specifies the Cg profile to be used for vertex programs. @B arbvp1 @b by default.
  * See SoShaderObject for details.
  *
  * @anchor OIV_CGM_HARDCOPY_BUFSIZE @B OIV_CGM_HARDCOPY_BUFSIZE @b @BR
  * Affects SoVectorizeCGMAction. @BR
  * Specifies the buffer size in bytes for storing CGM calls before writing them to the disk.
  * The default buffer size is 1048576 bytes (1 megabyte).
  * If set to 1, no buffering is done.
  *
  * @anchor OIV_CLIP_TEXT2 @B OIV_CLIP_TEXT2 @b @BR
  * When this variable is set, 2D text strings, which are rendered
  * using bitmaps, will be correctly clipped when the string start
  * point is outside the viewport (in previous releases the entire
  * string disappeared). @BR
  * NOTE: When this variable is set, auto render caching is suppressed
  * by SoText2 in all cases (by default it is not suppressed for
  * single line strings with default LEFT justification). This is
  * really only useful for applications rendering to multiple
  * screens, for example using the MultiPipe extension.
  *
  * @anchor OIV_COLORWHEEL_DBUF @B OIV_COLORWHEEL_DBUF @b [Win32 only] @BR
  * Some displays do not correctly handle the interaction between
  * the hardware cursor and OpenGL drawing in the front buffer.
  * By default the color wheel is single buffered and uses a
  * save/restore scheme when the user drags the "marker". If
  * this produces visual artifacts, try setting this environment
  * variable to force double-buffered rendering.
  *
  * @anchor OIV_COMPAT_24 @B OIV_COMPAT_24 @b [Win32 only] @BR
  * If this variable is set to any value, then the Open Inventor 2.4
  * pixel format selection code is used. Stereo is not possible.
  *
  * @anchor OIV_COMPAT_30 @B OIV_COMPAT_30 @b @BR
  * If set to 1, the Open Inventor 3.0 code for handling 2- and
  * 4-component texture images will be used. The 3.0 behavior could
  * reduce performance or produce unexpected results for images
  * that are actually opaque, so it is unlikely you will ever
  * need to set this variable.
  *
  * @anchor OIV_COMPAT_40 @B OIV_COMPAT_40 @b @BR
  * If set to 1, the Open Inventor 4.0 code for checking the OpenGL
  * extensions will be used. The 4.0 behavior can detect some extensions
  * even if they are not available on the current graphics hardware.
  *
  * @anchor OIV_COMPAT_CGM_HARDCOPY_400 @B OIV_COMPAT_CGM_HARDCOPY_400 @b @BR
  * Affects SoVectorizeCGMAction. @BR
  * If set to 1, CGM writing onto disk is not buffered (the buffering is only done
  * by stream data writing of the operating system). This value takes precedence
  * over OIV_CGM_HARDCOPY_BUFSIZE.
  *
  * @anchor OIV_COMPAT_HPGL_HARDCOPY_370 @B OIV_COMPAT_HPGL_HARDCOPY_370 @b @BR
  * Affects SoVectorizeHPGLAction. @BR
  * If set to 1, reproduces the (incorrect) HardCopy 3.7 line
  * pattern printing behavior. It is unlikely you will ever
  * need to set this variable.
  *
  * @anchor OIV_COMPAT_CONTEXT_80 @B OIV_COMPAT_CONTEXT_80 @b @BR
  * Affects the state of the compatibility mode for the contexts.@BR @BR
  * If set to 0 (default) the actual implementation of SoGLContext
  * will be used to manage the OpenGL contexts. @BR @BR
  * If set to 1 SoGLContext will call the OpenGL makeCurrent function
  * each time the bind() function is called. The unbind() function
  * won't do anything; this mode provides a way to have a valid context
  * outside any traversal. It's useful when third party APIs do direct OpenGL
  * calls. @BR @BR
  * If set to 2 the getCurrent() function will check the actual OpenGL state
  * instead of using the SoGLContext managment functions. This will prevent
  * issues related to third party code which could call OpenGL makeCurrent()
  * function instead of using SoGLContexts.
  *
  * @anchor OIV_COMPLEXITY @B OIV_COMPLEXITY  @b@BR
  * Affects SoComplexity.@BR
  * Specifies the default complexity (0.0 to 1.0).
  * The complexity can be set programmatically using the
  * SoComplexity::value field.
  *
  * @anchor OIV_COMPLEXITY_TYPE @B OIV_COMPLEXITY_TYPE  @b@BR
  * Affects SoComplexity.@BR
  * Specifies the default complexity type. Valid values
  * are OBJECT_SPACE, SCREEN_SPACE, BOUNDING_BOX.
  * The complexity type can be set programmatically using the
  * SoComplexity::type field.
  *
  * @anchor OIV_CONFIG_FILE @B OIV_CONFIG_FILE @b @BR
  * Specifies the full path of the configuration file.
  *
  * @anchor OIV_CREASE_ANGLE_FIX @B OIV_CREASE_ANGLE_FIX @b @BR
  * When set, forces FLAT shaded rendering when creaseAngle = 0.
  * Strictly speaking this is the correct behavior (see SoShapeHints),
  * however it is incompatible with the historical behavior of
  * Open Inventor and may change the appearance of geometry in
  * existing applications.
  * Applied only to SoIndexedTriangleStripSet and SoTriangleStripSet nodes.
  *
  * @anchor OIV_CSG_BUFFER_REGION @B OIV_CSG_BUFFER_REGION @b [Win32 only] [SolidViz only] @BR
  * Allows the SolidViz CSGGroup node rendering algorithm to use the
  * OpenGL Buffer Region extension to speed up save/restore of Z-Buffer
  * task. Classical save and restore of Z-Buffer (glDrawPixels/glReadPixels)
  * is used if this variable is not defined.
  * KTX_BUFFER_REGION: Uses the GL_KTX_buffer_region extension.
  * ARB_BUFFER_REGION: Uses the WGL_ARB_buffer_region extension.
  *
  * @anchor OIV_CURSOR_STYLE @B OIV_CURSOR_STYLE @b [Win32 only] @BR
  * Specifies the cursor style.
  *
  * - 0 Classic
  * - 1 XOR
  * - 2 Shadow
  *
  * The cursor can also be controlled programmatically. See SoWinViewer.
  *
  * @anchor OIV_DATABASE_CHECK @B OIV_DATABASE_CHECK @b @BR
  * If set, OpenInventor will perform advanced checks on database objects
  * during intialization and running steps.
  * This variable only applies to debug compilation mode (_DEBUG preprocessor option).
  * NOTE: This variable is all the most useful for users that develop
  * their own Openinventor nodes. User must be aware that even if helpful,
  * this variable leads to a larger memory usage.
  *
  * @anchor OIV_DEBUG_CONFIG @B OIV_DEBUG_CONFIG @b @BR
  * If set, requests that configuration debug output be generated.
  * NOTE: This configuration parameter must be set in the system environment,
  * not in a configuration file.
  *
  * @anchor OIV_DEBUG_PIXEL_FORMAT @B OIV_DEBUG_PIXEL_FORMAT @b [Win32 only] @BR
  * If this variable is set to 1, Open Inventor programs
  * will write a file (named pixel.txt) that indicates
  * which pixel format was chosen.
  *
  * @anchor OIV_DEFAULT_ACTION_USE_ALTERNATEREP @B OIV_DEFAULT_ACTION_USE_ALTERNATEREP @b @BR
  * If this variable is set to 1, then all action will ask for a potential alternal
  * representation to traversed node.
  * Default is FALSE.
  *
  * @anchor OIV_DECIMATION_GOAL_FPS @B OIV_DECIMATION_GOAL_FPS  @b@BR
  * Affects SoWinViewer, SoXtViewer, SoQtViewer.@BR
  * Specifies the default goal number of frames per second.
  * The value can be set programmatically using the setGoalFramesPerSecond
  * method of the classes above.
  *
  * @anchor OIV_DECIMATION_GOAL_NUM_OF_TRIANGLES @B OIV_DECIMATION_GOAL_NUM_OF_TRIANGLES  @b@BR
  * Affects SoWinViewer, SoXtViewer, SoQtViewer.@BR
  * Specifies the default goal number of triangles.
  * The value can be set programmatically using the setGoalNumberOfTriangles
  * method of the classes above.
  *
  * @anchor OIV_DECIMATION_PERCENTAGE @B OIV_DECIMATION_PERCENTAGE @b @BR
  * Affects SoWinViewer, SoXtViewer, SoQtViewer.@BR
  * Specifies the default decimation percentage.
  * The value can be set programmatically using the setFixedPercentage
  * method of the classes above.
  *
  * @anchor OIV_DECIMATION_STRATEGY @B OIV_DECIMATION_STRATEGY @b @BR
  * Affects SoWinViewer, SoXtViewer, SoQtViewer.@BR
  * Specifies the default decimation strategy.
  * Valid values are: NORMAL, FIXED_NUM_TRIANGLES, FRAMES_PER_SECOND, FIXED_PERCENTAGE.
  * The value can be set programmatically using the setDecimationStrategy
  * method of the classes above.
  *
  * @anchor OIV_DELAYED_SORTED_LAYERS_TEXTURE_UNIT @B OIV_DELAYED_SORTED_LAYERS_TEXTURE_UNIT @b @BR
  * If set, the DELAYED_SORTED_LAYERS_BLEND transparency type will use this
  * texture unit internally instead of SoFragmentShader::getMaxTextureImageUnit()-2.
  * OIV_SORTED_LAYERS_TEXTURE_UNIT is also used by DELAYED_SORTED_LAYERS_BLEND.
  *
  * @anchor OIV_DISABLE_DRAGGER_CTRL_KEY @B OIV_DISABLE_DRAGGER_CTRL_KEY @b @BR
  * Affects SoHandleBoxDragger, SoHandleBoxManip,
  * SoTrackBallDragger, SoTrackBallManip,
  * SoTransformerDragger, SoTransformerManip,
  * SoDragPointDragger, SoDragPointManip.@BR
  * If set to 1, when the CTRL key is pressed over the dragger,
  * nothing special happens. Otherwise, the CTRL key has its
  * usual behavior, which varies from dragger to dragger.
  *
  * @anchor OIV_DISABLED_GL_EXTENSION_LIST @B OIV_DISABLED_GL_EXTENSION_LIST @b @BR
  * This variable contains a comma separated list of OpenGL extension names to disable
  * explicitly in software.
  * This is useful when encountering a GPU driver bug, or to
  * check performance impact with or wihout a specific extension.
  * See SoGLExtension or www.opengl.org for a list of extension names.
  *
  * @anchor OIV_DRAW_OCTREE @B OIV_DRAW_OCTREE @b @BR
  * Affects SoOctreeOrdering. @BR
  * If this environment variable is set and your application uses an
  * SoOctreeOrdering node, an outline of the octree quadrants will be
  * drawn. This is a debugging aid to allow you to see how your scene
  * is distributed throughout the octree.
  *
  * @anchor OIV_ENABLE_PNG_BACKGROUND @B OIV_ENABLE_PNG_BACKGROUND  @b@BR
  * Affects SoPNGImageRW (and texture nodes that load PNG files).@BR
  * Enables the merge of the background into the displayed image.
  * The background replaces transparent parts of the image.
  *
  * @anchor OIV_ENVIRONMENT_ATTENUATION @B OIV_ENVIRONMENT_ATTENUATION  @b@BR
  * Affects SoEnvironment.@BR
  * Specifies the default squared, linear, and constant light attenuation
  * coefficients (in that order) with respect to distance of light from surface
  * (for Phong lighting).
  * The values are specified as three floats.
  * The background color can be set programmatically using the
  * SoEnvironment::attenuation field.

  * @anchor OIV_EXTRUSION_EPSILON @B OIV_EXTRUSION_EPSILON  @b@BR
  * Affects SoExtrusion and SoVRMLExtrusion.@BR
  * If your extrusion appears to twist unexpectedly,
  * try setting this value to a slightly smaller number. The default value is
  *.998.
  *
  * @anchor OIV_FACE_TYPE @B OIV_FACE_TYPE  @b@BR
  * Affects SoShapeHints.@BR
  * Specifies the default face type. Valid values
  * are UNKNOWN, CONVEX.
  * The face type can be set programmatically using the
  * SoShapeHints::faceType field.
  *
  * @anchor OIV_FILE_SEARCH_PATHS @B OIV_FILE_SEARCH_PATHS  @b@BR
  * Semi-colon separated path list used to initialize the directory list
  * in SoInput.  Most Open Inventor classes that take a file name (for
  * textures, shaders, etc) will search the directories in this list to
  * find the file.  Exception: SoDataSet, SoVolumeData and derived classes.
  *
  * @anchor OIV_FOG_COLOR @B OIV_FOG_COLOR  @b@BR
  * Affects SoEnvironment.@BR
  * Specifies the default fog color.
  * The value is specified as
  * three floats (0.0 to 1.0) representing the RGB values of the color.
  * The value can be set programmatically using the
  * SoEnvironment::fogColor field.
  *
  * @anchor OIV_FOG_TYPE @B OIV_FOG_TYPE  @b@BR
  * Affects SoEnvironment.@BR
  * Specifies the default fog type.
  * Valid values are: NONE, HAZE, FOG, SMOKE.
  * The value can be set programmatically using the
  * SoEnvironment::fogType field.
  *
  * @anchor OIV_FOG_VISIBILITY @B OIV_FOG_VISIBILITY  @b@BR
  * Affects SoEnvironment.@BR
  * Specifies the default distance at which fog totally obscures objects.
  * The value can be set programmatically using the
  * SoEnvironment::fogVisibility field.
  *
  * @anchor OIV_FONT_NAME @B OIV_FONT_NAME  @b@BR
  * Affects SoFont.@BR
  * Specifies the default font name.
  * The value can be set programmatically using the
  * SoFont::name field.
  *
  * @anchor OIV_FONT_PATH @B OIV_FONT_PATH @b@BR
  * Contains a colon-separated or semicolon-separated list of
  * directories to search for font definition files.
  * NOTE: This item cannot be set
  * via SoPreferences or a configuration file. It must be set
  * in the environment (e.g., using setenv). See SoFont for more information.
  *
  * @anchor OIV_FONT_SIZE @B OIV_FONT_SIZE  @b@BR
  * Affects SoFont.@BR
  * Specifies the default font size.
  * The value can be set programmatically using the
  * SoFont::size field.
  *
  * @anchor OIV_FONT_RENDERSTYLE @B OIV_FONT_RENDERSTYLE  @b@BR
  * Affects SoFont.@BR
  * Specifies the default font render style. Valid values
  * are POLYGON, TEXTURE, POLYGON_AND_OUTLINE.
  * The value can be set programmatically using the
  * SoFont::renderStyle field.
  *
  * @anchor OIV_FORCE_DUAL_TEX_SHADOW @B OIV_FORCE_DUAL_TEX_SHADOW @b @BR
  * Setting this variable to 1 tells the FXViz shadow algorithm to not
  * use the OpenGL Shadow extension. This is only useful if your
  * graphics board claims to support the extension but draws the
  * shadows incorrectly or very slowly (e.g., some GeForce2-based
  * boards).
  *
  * @anchor OIV_FORCE_GLU_NURBS @B OIV_FORCE_GLU_NURBS @b @BR
  * Affects SoNurbsSurface, SoIndexedNurbsSurface.@BR
  * If set to 1, then NURBS are tessellated and rendered using GLU.
  *
  * @anchor OIV_FORCE_PIXEL_FORMAT @B OIV_FORCE_PIXEL_FORMAT @b [Win32 only] @BR
  * If this environment variable is set to a positive integer,
  * Open Inventor will try to use it as the pixel format. You can
  * list the available pixel formats with the "oglinfo" utility
  * that is provided with the Open Inventor for Win32 SDK. To request
  * a pixel format programmatically, use the setPixelFormat method of
  * SoWinGLWidget.
  *
  * The following special values are provided for your convenience:
  *
  * - -1 Choose a pixel format without hardware acceleration (if any).
  * This is convenient for helping to determine if a problem is
  * due to hardware acceleration, i.e., if the problem lies in the
  * OpenGL driver or the board hardware.
  *
  * - -2 Choose the "minimal" pixel format. By default Open Inventor
  * will choose the pixel format with the most capabilities,
  * including stencil buffer, accumulation buffer, etc. On
  * low-end boards it may be possible to get better performance
  * using the pixel format with the least capabilities. Acceleration
  * is still selected.
  *
  * - -3 Choose the "minimal" pixel format without hardware acceleration.
  *
  * @anchor OIV_FORCE_TEX_COORD_SENDING @B OIV_FORCE_TEX_COORD_SENDING @b @BR
  * Affects shapes derived from SoVertexShape, and only affects
  * user-specified texture coordinates.
  * If set to 1 (TRUE), forces the sending of texture
  * coordinates to the OpenGL pipeline without having a texture
  * bound to the corresponding texture unit. This is useful when
  * working with programmable shaders. Default is 0 (FALSE).
  * The value can be set programmatically using the SoTextureCoordinate2::forceSending
  * field or the SoTextureCoordinate3::forceSending field.
  *
  * @anchor OIV_FORCE_USE_VBO @B OIV_FORCE_USE_VBO @b @BR
  * Affects the SoShapeHints::useVBO default value.
  * Since Open Inventor 8.1 the default value for SoShapeHints::useVBO is TRUE (1),
  * using this variable, you can force back it to FALSE (0).
  *
  * @anchor OIV_FREETYPE_NAME @B OIV_FREETYPE_NAME @b @BR
  * Affects SoDynamicLibManager. @BR
  * Allows you to use your own Freetype dynamic library.
  * Do not add the suffix.
  * Do not add the "lib" prefix on UNIX systems.
  * Do not add the final "D" used in the debug name.
  * Default is "IvDLFreetype".
  *
  * @anchor OIV_FULL_RENDER_WHEN_STILL @B OIV_FULL_RENDER_WHEN_STILL @b@BR
  * Affects SoWinViewer, SoQtViewer, SoXtViewer.@BR
  * Specifies if the viewer will be default render at full resolution
  * when it sits still for a certain period of time.  (0=no, 1=yes).
  * This flag can be set programmatically using the
  * enableFullRenderingWhenStill method of the viewers classes above.
  *
  * @anchor OIV_FULL_SCENE_ANTIALIASING @B OIV_FULL_SCENE_ANTIALIASING @b@BR
  * Affects SoFullSceneAntialiasing.@BR
  * Specifies whether full scene antialiasing (if already enabled) will be
  * applied to subsequent shapes (0=no, 1=yes).
  * The value can be set programmatically using the SoFullSceneAntialiasing::on field.
  * See SoFullSceneAntialiasing for information on enabling full scene antialiasing.
  *
  * @anchor OIV_FULL_SCENE_ANTIALIASING_FILTER @B OIV_FULL_SCENE_ANTIALIASING_FILTER @b@BR
  * Affects SoFullSceneAntialiasing.@BR
  * Specifies which kinds of primitives should be antialiased when full scene
  * antialiasing is enabled. Valid values are
  * ALL or any combination of LINES, POINTS, POLYGONS, and TEXT.
  * The value can be set programmatically using the SoFullSceneAntialiasing::filter field.
  * See SoFullSceneAntialiasing for complete details.
  *
  * @anchor OIV_GL_SMOOTHING @B OIV_GL_SMOOTHING @b@BR
  * Affects SoGLRenderAction.@BR
  * Specifies the default smoothing flag (0=no smooth, 1=smooth).
  * The smoothing flag can be set programmatically using
  * SoGLRenderAction::setSmoothing.
  *
  * @anchor OIV_SET_RAY_PRECISION @B OIV_SET_RAY_PRECISION @b@BR
  * Affects SoRayPickAction when defining a ray using the setRay method@BR
  * Specify (in radius) the value of fovy angle defined by the ray.
  * If not set, the default value is set to 0.0003F
  *
  * @anchor OIV_GLSL_DEBUG @B OIV_GLSL_DEBUG @b@BR
  * Affects SoShaderObject (and derived classes).@BR
  * Enables display of output generated by the GLSL compiler of the graphics display driver.
  * If not set to TRUE (1), no trace output is generated.
  *
  * @anchor OIV_HC_BLACK_AND_WHITE @B OIV_HC_BLACK_AND_WHITE @b @BR
  * Affects subclasses of SoVectorizeAction (HardCopy extension).
  * Force all non-white colors to full black.
  * This is useful because selecting "black & white" in the printer
  * setup dialog normally produces gray scale rendering and some
  * colors may be difficult to see.  This option is applied after
  * color translation (e.g. REVERSE_ONLY_BLACK_AND_WHITE). 
  *
  * @anchor OIV_HCGDI_APPCONTROL @B OIV_HCGDI_APPCONTROL @b @BR
  * Affects SoVectorizeGDIAction (HardCopy extension).
  * When this variable is non-zero, the application is responsible for calling StartDoc,
  * StartPage, EndPage and EndDoc to manage the printer.  There are two modes, depending
  * on the value of OIV_HCGDI_APPCONTROL:
  *    - 1 : This is the most flexible mode.  The application is responsible for
  *          setting the map mode, logical to device mapping, etc. (in addition
  *          to managing the printer). This mode is normally used in an MFC application.
  *    - 2 : This is the most convenient mode if you only need to manage the
  *          printer.  SoVectorizeGDIAction will set up the mapping as usual.
  *          This mode is only available in Open Inventor 7.2 and higher.
  *
  * @anchor OIV_HCGDI_EDGE_WIDTH @B OIV_HCGDI_EDGE_WIDTH @b @BR
  * Affects SoVectorizeGDIAction (HardCopy extension).
  * Default is to draw a minimum width line for polygon edges.
  * In most cases this is enough to prevent small triangles from disappearing.
  * If > 0, this value is a scale factor applied to the "nominalWidth"
  * (effectively same as SoDrawStyle::lineWidth). This value is fetched in
  * the constructor so it must be set before creating an SoVectorizeGDIAction.
  *
  * @anchor OIV_HCGDI_POLYGON_COMPAT @B OIV_HCGDI_POLYGON_COMPAT @b @BR
  * Affects SoVectorizeGDIAction (HardCopy extension).
  * Before Open Inventor 8.5.1.2 the action only used a "brush" (no pen) to render GDI polygons.
  * In this case GDI only draws the "interior" of the polygon, so very small polygons could 
  * disappear completely because GDI determined that no part of the interior was visible. 
  * Although it's unlikely to be needed, this variable allows returning to the pre-8.5.1.2 behavior.
  *
  * @anchor OIVHOME @B OIVHOME @b @BR
  * Specifies the path of the Open Inventor installation directory.
  * Open Inventor may search for the stroke font files as well as
  * pattern files in subdirectories of OIVHOME.
  *
  * @anchor OIVARCH @B OIVARCH @b @BR
  * Specifies the directory that contains all architecture dependent files. @BR
  * In a standard installation this directory is under the $OIVHOME directory
  * and has subdirectories such as "bin" and "lib".
  * For example: arch-Windows-x86_64-msvc9-Debug contains files for a 64-bit
  * Windows debug build using Visual Studio 2008 (VC++ 9).
  * Open Inventor uses this environment variable for:
  *  - Finding license files (in $OIVHOME/$OIVARCH/License)
  *  - Finding libraries to load dynamicly at runtime (in $OIVHOME/$OIVARCH/bin or lib)
  *  - Finding programs to launch dynamicly (in $OIVHOME/$OIVARCH/bin) (ScaleViz oiru for example)
  *
  * @anchor OIV_INTERACTIVE_DRAW_STYLE @B OIV_INTERACTIVE_DRAW_STYLE @b@BR
  * Affects SoWinViewer, SoQtViewer, SoXtViewer.@BR
  * Specifies the default interactive draw style.
  * Valid values are: VIEW_AS_IS, VIEW_HIDDEN_LINE, VIEW_NO_TEXTURE,
  *            VIEW_LOW_COMPLEXITY, VIEW_LINE, VIEW_POINT, VIEW_BBOX,
  *            VIEW_LOW_RES_LINE, VIEW_LOW_RES_POINT, VIEW_SAME_AS_STILL.
  * The interactive draw style can be set programmatically using the setDrawStyle method
  * of the viewers classes above.
  *
  * @anchor OIV_INTERSECT_EPSILON @B OIV_INTERSECT_EPSILON @b @BR
  * Specifies the epsilon value against which the area of a triangle
  * is checked to eliminate triangles with no area when picking.
  * It allows you to pick objects that have very small coordinate
  * values. Set the value to approximately 10 raised to three times
  * the exponent of the object coordinates. Example: For objects
  * with coordinates of approximately 10E-7, a value of 10E-21
  * would allow the objects to be picked.
  *
  * @anchor OIV_LD_LIBRARY_PATH @B OIV_LD_LIBRARY_PATH @b @BR
  * Affects SoDynamicLibManager. @BR
  * Specifies a single path in which to search for a dynamic
  * library to be loaded. Other paths may be searched as well.
  * See SoDynamicLibManager for details.
  *
  * @anchor OIV_LIBACIS_NAME @B OIV_LIBACIS_NAME @b @BR
  * Affects SoDynamicLibManager. @BR
  * Allows you to use your own libAcis dynamic library.
  * Do not add the suffix.
  * Do not add the final "D" used in the debug name.
  * Default is "IvDLAcis".
  *
  * @anchor OIV_LIBDXF_NAME @B OIV_LIBDXF_NAME @b @BR
  * Affects SoDynamicLibManager. @BR
  * Allows you to use your own libDxf dynamic library.
  * Do not add the suffix.
  * Do not add the final "D" used in the debug name.
  * Default is "IvDLDxf".
  *
  * @anchor OIV_LIBFLT_NAME @B OIV_LIBFLT_NAME @b @BR
  * Affects SoDynamicLibManager. @BR
  * Allows you to use your own libFlt dynamic library.
  * Do not add the suffix.
  * Do not add the "lib" prefix on UNIX systems.
  * Do not add the final "D" used in the debug name.
  * Default is "IvDLFlt".
  *
  * @anchor OIV_LIBJASPER_NAME @B OIV_LIBJASPER_NAME @b @BR
  * Affects SoDynamicLibManager. @BR
  * Allows you to use your own libJasper dynamic library.
  * Do not add the suffix.
  * Do not add the "lib" prefix on UNIX systems.
  * Do not add the final "D" used in the debug name.
  * Default is "IvDLJasper".
  *
  * @anchor OIV_LIBJPEG_NAME @B OIV_LIBJPEG_NAME @b @BR
  * Affects SoDynamicLibManager. @BR
  * Allows you to use your own libJpeg dynamic library.
  * Do not add the suffix.
  * Do not add the "lib" prefix on UNIX systems.
  * Do not add the final "D" used in the debug name.
  * Default is "IvDLJpeg".
  *
  * @anchor OIV_LIBPNG_NAME @B OIV_LIBPNG_NAME @b @BR
  * Affects SoDynamicLibManager. @BR
  * Allows you to use your own libPng dynamic library.
  * Do not add the suffix.
  * Do not add the "lib" prefix on UNIX systems.
  * Do not add the final "D" used in the debug name.
  * Default is "IvDLPng".
  *
  * @anchor OIV_LIBPROJ4_NAME @B OIV_LIBPROJ4_NAME @b @BR
  * Affects SoDynamicLibManager. @BR
  * Allows you to use your own libProj4 dynamic library.
  * Do not add the suffix.
  * Do not add the "lib" prefix on UNIX systems.
  * Do not add the final "D" used in the debug name.
  * Default is "IvDLProj4".
  *
  * @anchor OIV_LIBTIFF_NAME @B OIV_LIBTIFF_NAME @b @BR
  * Affects SoDynamicLibManager. @BR
  * Allows you to use your own libTiff dynamic library.
  * Do not add the suffix.
  * Do not add the "lib" prefix on UNIX systems.
  * Do not add the final "D" used in the debug name.
  * Default is "IvDLTiff".
  *
  * @anchor OIV_LINE_WIDTH @B OIV_LINE_WIDTH @b @BR
  * If defined, forces Open Inventor to use line width 1. no matter
  * what line width the program requests. (This was used to
  * improve performance on a system that had notoriously slow
  * wide lines.)
  *
  * @anchor OIV_LOWRESHIGHPERCENT @B OIV_LOWRESHIGHPERCENT @b @BR
  * Affects Remote Rendering.@BR
  * This variable specifies the rendered image size as a percentage of
  * the actual window size in the normal case. The default is 1.0 (full
  * size).
  *
  * @anchor OIV_LOWRESLOWPERCENT @B OIV_LOWRESLOWPERCENT @b @BR
  * Affects Remote Rendering.@BR
  * This variable specifies the rendered image size as a percentage of
  * the actual window size when the Open Inventor viewer is in "Move as
  * Low-Res" mode. The default is 0.7 (70 percent).
  *
  * @anchor OIV_LOWRESRENDER @B OIV_LOWRESRENDER @b @BR
  * Affects Remote Rendering.@BR
  * If this variable is defined and the target display (local machine)
  * supports OpenGL, then low resolution rendering is enabled. No change
  * to the application is required.
  *
  * @anchor OIV_MATERIALS_PATH @B OIV_MATERIALS_PATH @b [UNIX only] @BR
  * Affects SoMaterialEditor. @BR
  * Specifies the path where the material palette will look for materials.
  *
  * @anchor OIV_MAX_ANNO_RENDER2D_SIZE @B OIV_MAX_ANNO_RENDER2D_SIZE @b @BR
  * Affects SoAnnoText3.@BR
  * Specifies the maximum font size (in pixels) used in font size
  * computed when SoAnnoText3::renderPrintType field is equal to RENDER2D_PRINT_RASTER.
  * The default maximum value is 1000. If you notice
  * a performance issue when rendering and zooming a scene graph
  * containing many SoAnnoText3 nodes, setting this
  * value to a smaller number, such as 64, may improve performance.
  *
  * @anchor OIV_MAX_CACHES @B OIV_MAX_CACHES @b @BR
  * Specifies the maximum number of render caches for all
  * nodes that create render caches, including display
  * lists (e.g. SoSeparator, SoVRMLShape) and texture
  * objects (e.g. SoTexture2, SoVRMLImageTexture). To
  * disable caching entirely, set it to 0.
  * This can reduce memory requirements at the cost of
  * reduced performance.
  *
  * For multi-pipe rendering based on MPViewer, set
  * it to the number of pipes that will be used.
  *
  * For multi-GPU rendering using ScaleViz, OIV_MAX_CACHES is the maximum
  * number of render caches per rendering thread (not the total number of
  * render caches).
  * [Replaces IV_SEPARATOR_MAX_CACHES.]
  *
  * @anchor OIV_MAX_FONT_CACHES @B OIV_MAX_FONT_CACHES @b @BR
  * Specifies the maximum number of caches that can be used during text computation.
  * Default value is 20;
  * See SoFont for details.
  *
  * @anchor OIV_MAX_TEXTURED_FONT_RES @B OIV_MAX_TEXTURED_FONT_RES @b @BR
  * Specifies the maximum resolution used when generating textured glyph during
  * text computation. (SoFont::renderStyle field must be set to TEXTURE.)
  * The amount of memory used in textured text depends on this value.
  * Default value is 600.
  *
  * @anchor OIV_MIN_TEXTURED_FONT_RES @B OIV_MIN_TEXTURED_FONT_RES @b @BR
  * Specifies the minimum resolution used when generating textured glyph during
  * text computation. (SoFont::renderStyle field must be set to TEXTURE.)
  * The amount of memory used in textured text depends on this value.
  * Default value is 300.
  *
  * @anchor OIV_MIN_VERTEX_VA @B OIV_MIN_VERTEX_VA @b @BR
  * Shapes use Vertex Array (VA) if they contain at least OIV_MIN_VERTEX_VA vertices.
  * Default value is 0.
  *
  * @anchor OIV_MIN_VERTEX_VBO @B OIV_MIN_VERTEX_VBO @b @BR
  * Shape use Vertex Buffer Object (VBO) if they contain at least OIV_MIN_VERTEX_VBO vertices.
  * Default value is 0.
  *
  * @anchor OIV_MIN_VERTEX_VAVBO_NOCACHE @B OIV_MIN_VERTEX_VAVBO_NOCACHE @b @BR
  * Shapes using VBO or VA will deactivate caching if they contain at least OIV_MIN_VERTEX_VAVBO_NOCACHE vertices.
  * Default value is 10000.
  *
  * @anchor OIV_MOUSE_WHEEL_ENABLE @B OIV_MOUSE_WHEEL_ENABLE @b @BR
  * Affects SoWin, SoQt.@BR
  * Allows you to use the mouse wheel to zoom or
  * dolly the camera when using the Open Inventor viewers (examiner,
  * walk, etc.). The mouse wheel has the same kind of camera
  * movement as the right thumbwheel -- dolly or zoom -- depending
  * on the viewer type and camera type.
  * Default is TRUE (1).
  * The value can be set programmatically using the enableMouseWheelDolly
  * method of SoWinViewer or SoQtViewer.
  *
  * @anchor OIV_MP_CONFIG_FILE @B OIV_MP_CONFIG_FILE @b @BR
  * Specifies the pathname of the configuration file for
  * the multi-pipe viewer. Default is "./oivmp.cfg".
  *
  * @anchor OIV_MULTITHREAD @B OIV_MULTITHREAD @b @BR
  * Enables/disables multithread (MT) support.
  *
  * - 0 MT support disabled
  * - 1 MT support enabled
  *
  * If OIV_MULTITHREAD is not defined, then MT support is:
  *
  * - disabled if SoDB::init is called.
  * - enabled if SoDB::threadInit is called.
  *
  * @anchor OIV_MULTITEXTURING @B OIV_MULTITEXTURING @b @BR
  * Enables/disables multitexturing support.
  *
  * - 0 multitexturing support disabled
  * - 1 multitexturing support enabled
  *
  * If OIV_MULTITEXTURING is not defined, multitexturing support
  * is enabled (if your graphics board supports it). Setting this
  * variable to 0 is equivalent to maxTextureUnit equal 1. See
  * SoTextureUnit for details.

  * @anchor OIV_NO_FBO @B OIV_NO_FBO @b @BR
  * Set to 1 to disallow use of OpenGL Frame Buffer Object.
  * Default is 0.
  *
  * @anchor OIV_NO_FLEXNET @B OIV_NO_FLEXNET @b @BR
  * Set to 1 to disallow FLEXnet licensing checking.
  * Default is 0.
  *
  * @anchor OIV_NURBS_FIX_TRIM_CONNECTIONS @B OIV_NURBS_FIX_TRIM_CONNECTIONS @b @BR
  * In some cases, trimming curves are not properly connected in a trimming loop.
  * This may result in bad tesselations of NURBS surfaces when using the CONSTANT
  * tessellationType of the NurbsProperty node (the default mode).
  * When this mode is activated, the NURBS tesselation algorithm tries to reconnect trimming curves.
  * Set to 0 to disable this mode.
  * Default is 1.
  *
  * @anchor OIV_NURBS_FORCE_GLU_CONVEXISATION @B OIV_NURBS_FORCE_GLU_CONVEXISATION @b @BR
  * When set to 1, always use the GLU polygon tesselation instead of the internal one.
  * Before version 7.2, the default behavior was to use the internal tesselation.
  * Sometimes, the result produced by this internal tesselation was wrong when using the CONSTANT
  * tessellationType of the NurbsProperty node (the default mode).
  * Set to 0 to revert to the internal tesselation mode.
  * Default is 1.
  *
  * @anchor OIV_NURBS_CHECK_RATIONAL_TRIM_OUTSIDE_DOMAIN @B OIV_NURBS_CHECK_RATIONAL_TRIM_OUTSIDE_DOMAIN @b @BR
  * When set to 0, do not try to limit the values of homogeneous trimming curves coordinates to the boundaries of the NURBS domain.
  * Sometimes, trimming curve points can be defined outside the domain but their tesselated counterparts may lie inside the domain for "heavy" weights.
  * Notice that this test is always performed for non rational coordinates since it is invalid to define trimming curves lying outside the domain.
  * Default is 1: the test is performed.
  *
  * @anchor OIV_NO_IVTUNE @B OIV_NO_IVTUNE @b @BR
  * Affects IvTune activation. @BR
  * If set to 1, disallows interactive
  * activation of an IvTune window from an Open Inventor application.
  * You can also allow/disallow IvTune activation programmatically using the
  * SoDB::setIvTuneAllowed() method.
  * Default is 0.
  *
  * @anchor OIV_IVTUNE_SHORTCUT @B OIV_IVTUNE_SHORTCUT @b @BR
  * Controls the keyboard shortcut used
  * for activating IvTune. @BR
  * The shortcut is composed of [SHIFT] followed by a second key.
  * Use this environment variable to specify the value of the second key, chosen
  * from the SoKeyboardEvent::Key enum.
  * Default is 0xFFC9 [F12], which corresponds to a shortcut of [SHIFT] + [F12].
  *
  * @anchor OIV_NO_OVERLAYS @B OIV_NO_OVERLAYS @b @BR
  * Disables Open Inventor's normal attempt to automatically
  * use overlay planes on all platforms. This can be useful
  * to suppress the warning message on UNIX platforms (when
  * overlays are not available) or to avoid a problem with
  * the overlay planes not being correctly transparent.
  *
  * @anchor OIV_NORMGEN_COMPAT @B OIV_NORMGEN_COMPAT @b @BR
  * If set, Open Inventor will use the pre-version 3.1
  * algorithm for computing normals. This algorithm has
  * very bad performance when the geometry bounding box
  * is asymmetrical. It is not likely you will ever need
  * to set this variable.
  *
  * @anchor OIV_NORMGEN_TOLERANCE @B OIV_NORMGEN_TOLERANCE @b @BR
  * Sets the "tolerance factor" used to test for coincident vertices
  * when computing vertex normal vectors for a geometric primitive.
  * A larger value for OIV_NORMGEN_TOLERANCE results in fewer
  * vertices being considered coincident. This can significantly
  * reduce the time required to compute normal vectors for large
  * geometry, for example MeshViz meshes. The default value is 1000000.
  *
  * @anchor OIV_SEPARATE_SPECULAR_SUPPORT @B OIV_SEPARATE_SPECULAR_SUPPORT @b @BR
  * Enables the use of the GL_EXT_separate_specular extension in OpenInventor.
  * The default value is FALSE
  *
  * @anchor OIV_NO_SHADER_LAYERS_BLEND @B OIV_NO_SHADER_LAYERS_BLEND @b @BR
  * Disable the use of fragment shaders when using transparency type
  * SoTransparencyType::SORTED_LAYERS_BLEND.
  *
  * @anchor OIV_NO_TEX_TRIM_NURBS @B OIV_NO_TEX_TRIM_NURBS @b @BR
  * Affects SoNurbsSurface, SoIndexedNurbsSurface.@BR
  * @B Deprecated @b, use @ref OIV_FORCE_GLU_NURBS instead.
  *
  * @anchor OIV_NO_VBO @B OIV_NO_VBO @b @BR
  * Affects SoShapeHints.@BR
  * VBOs may be used to speed up rendering of SoIndexedFaceSets and
  * SoIndexedTriangleStripSets. If the rendering is not correct, try setting
  * this variable.
  *
  * @anchor OIV_NUM_RENDER_PASSES @B OIV_NUM_RENDER_PASSES @b@BR
  * Affects SoGLRenderAction.@BR
  * Specifies the default number of render passes. Must be an integer greater than 1.
  * The number of passes can be set programmatically using
  * SoGLRenderAction::numPasses.
  *
  * @anchor OIV_NUM_SORTED_LAYERS_PASSES @B OIV_NUM_SORTED_LAYERS_PASSES @b@BR
  * Affects SoGLRenderAction.@BR
  * Specifies the default number of render passes used when SORTED_LAYERS_BLEND
  * transparency is used. Must be an integer greater than 1.
  * The value can be set programmatically using
  * SoGLRenderAction::setSortedLayersNumPasses.
  *
  * @anchor OIV_OGLLIB_PATH @B OIV_OGLLIB_PATH @b [UNIX only] @BR
  * Specifies the path to the OpenGL library. It may be useful
  * if this dynamic library cannot be found automatically.
  * Open Inventor needs to open the dynamic OpenGL library
  * to evaluate which interesting extensions is supported.
  *
  * @anchor OIV_OLD_ERROR_HANDLER @B OIV_OLD_ERROR_HANDLER @b @BR
  * Due to a Windows programming limitation,
  * the error console (SoConsole) is not useable in multi-threaded applications.
  * This environment variable allows you to use the older (Open Inventor 3.1 and
  * earlier) error message handler instead.
  *
  * @anchor OIV_OPENAL_NAME @B OIV_OPENAL_NAME @b @BR
  * Affects SoDynamicLibManager. @BR
  * Allows you to use your own OpenAL dynamic library.
  * Do not add the suffix.
  * Do not add the "lib" prefix on UNIX systems.
  * Do not add the final "D" used in the debug name.
  * Default is "IvDLOpenAL32".
  *
  * @anchor OIV_PBUFFER_DEBUG @B OIV_PBUFFER_DEBUG @b @BR
  * Affects SoOffscreenRenderer, SoPBuffer. @BR
  * Set to 1 to enable debug trace output for Pbuffers.
  *
  * See also OIV_PBUFFER_ENABLE.
  *
  * @anchor OIV_PBUFFER_ENABLE @B OIV_PBUFFER_ENABLE @b @BR
  * Affects SoOffscreenRenderer, SoPBuffer.
  * Set to zero to disallow use of Pbuffers.
  *
  * The OpenGL Pbuffer extension allows accelerated rendering
  * to off-screen memory. The SoOffscreenRenderer class will
  * automatically use a Pbuffer (if possible) for rendering.
  * In case of problems using Pbuffers, this environment
  * variable may be used.
  *
  * Note: If Pbuffers are disallowed, OpenGL does rendering in
  * software. This gives low performance and OpenGL extensions will
  * often not be available. In general the image may not match the
  * on-screen image simply because a different renderer is being
  * used. However, the lack of OpenGL extensions can cause the
  * offscreen image to differ signficantly. Following are some of the
  * features that depend on OpenGL extensions: Open Inventor correct
  * transparency, VolumeViz 3D textures, FXViz shadowing and bump
  * mapping.
  *
  * @anchor OIV_PERFCOUNTER_ENABLE @B OIV_PERFCOUNTER_ENABLE @b@BR
  * Enable or not the SoPerfCounterManager performance counters manager.
  * By default it is disabled.
  *
  * @anchor OIV_PFD_SUPPORT_COMPOSITION @B OIV_PFD_SUPPORT_COMPOSITION @b@BR
  * Specifies if the composition with Aero (Windows Vista and 7) is on or off (0= force off, 1= force on).
  * By default OpenInventor will try to use composition.
  * Note that if you turn it on, PFD_SUPPORT_GDI is unset which will prevent using GDI on the
  * OpenGL render area. Also if you force the composition to off and the device doesn't provide any pixel
  * format with GDI support, OpenInventor will post an error.
  * Note also that it has no effect on SoQt viewers, see http://bugreports.qt.nokia.com/browse/QTBUG-6988.
  *
  * @anchor OIV_PFD_SUPPORT_GDI @B OIV_PFD_SUPPORT_GDI @b@BR
  * Specifies if the GDI support with Aero (Windows Vista and 7) is on or off (0= force off, 1= force on).
  * By default OpenInventor will try to use composition. (See OIV_PFD_SUPPORT_COMPOSITION)
  * GDI support and composition support are exclusive.
  * OIV_PFD_SUPPORT_GDI is preponderant on OIV_PFD_SUPPORT_COMPOSITION, meaning that if both are defined, GDI support is
  * choosen first.
  *
  * @anchor OIV_POLYGON_OFFSET @B OIV_POLYGON_OFFSET  @b@BR
  * Affects SoPolygonOffset.@BR
  * Specifies if the polygon offset computation is on by default (0=no, 1=yes)
  * The value can be set programmatically using the
  * SoPolygonOffset::on field.
  *
  * @anchor OIV_POLYGON_OFFSET_FACTOR @B OIV_POLYGON_OFFSET_FACTOR @b@BR
  * Affects SoPolygonOffset.@BR
  * Specifies the default polygon offset factor.
  * The value can be set programmatically using the
  * SoPolygonOffset::factor field.
  *
  * @anchor OIV_POLYGON_OFFSET_STYLES @B OIV_POLYGON_OFFSET_STYLES @b@BR
  * Affects SoPolygonOffset.@BR
  * Specifies the default polygon offset styles.
  * Valid values are FILLED, LINES, POINTS.
  * The value can be set programmatically using the
  * SoPolygonOffset::styles field.
  *
  * @anchor OIV_POLYGON_OFFSET_UNITS @B OIV_POLYGON_OFFSET_UNITS @b@BR
  * Affects SoPolygonOffset.@BR
  * Specifies the default polygon offset units.
  * The value can be set programmatically using the
  * SoPolygonOffset::units field.
  *
  * @anchor OIV_PRIORITIZE_CHILDREN_CACHING @B OIV_PRIORITIZE_CHILDREN_CACHING @b@BR
  * Specifies the default caching policy for children caching.
  * Valid value is 0 (FALSE) or 1 (TRUE). Default is TRUE.
  * The value can be set programmatically using the
  * SoDB::prioritizeChildrenCaching() method.
  *
  * @anchor OIV_PSFONT_PATH @B OIV_PSFONT_PATH @b deprecated @BR
  * Starting with Open Inventor 6.0, this environment variable is a synonym
  * for OIV_FONT_PATH. Please see OIV_FONT_PATH for details.
  *
  * @anchor OIV_QT_TIMER_THREAD @B OIV_QT_TIMER_THREAD @b @BR
  * Affects SoQt viewers.@BR
  * If set to 1, specifies that a separate thread should be used
  * to signal the delay sensor timeout.@BR
  *
  * When mouse events are continuously caught by the event \oivnetdoc delegate \else callback \endoivnetdoc,
  * the Qt viewers may not update the scene as often as
  * necessary. Because of the way that Qt's QTimer class works, the
  * timeout for processing the delay queue does not always occur, and
  * the scene is not updated. If the OIV_QT_TIMER_THREAD is set to 1,
  * a separate thread is used to signal the delay sensor timeout.
  * To avoid possible compatibility problems, the default is to use the
  * existing QTimer mechanism for processing the delay queue timeout.
  *
  * @anchor OIV_REMOTE_ENABLE @B OIV_REMOTE_ENABLE @b @BR
  * Applies to ScaleViz.@BR
  * - ON - Enable connection of client to get application's viewer frame
  *
  * - OFF (default) - Disable connection of client to get application's viewer frame
  *
  * @anchor OIV_REMOTE_PORT @B OIV_REMOTE_PORT @b @BR
  * Applies to ScaleViz.@BR
  * Specify the TCP port the application will use to listen for remote client
  * connection. This port must be free (not used by any other daemon or services).
  * Default is 0, meaning the value is dynamically allocated and printed to the console
  * or remote dialog GUI.
  *
  * @anchor OIV_REMOTE_TIMING @B OIV_REMOTE_TIMING @b @BR
  * Applies to ScaleViz.@BR
  * A value of 1 enables printing in the console of performance timing feedback about each step
  * of the remote frame compression mechanism for ScaleViz remote rendering.
  * Default is 0.
  *
  * @anchor OIV_REMOTERENDER @B OIV_REMOTERENDER @b @BR
  * - ON - Always use remote rendering
  *
  * - OFF - Never use remote rendering
  *
  * - AUTO (default) - Use if remote display does not have GLX
  *
  * @anchor OIV_REMOTERENDER_BUFFER @B OIV_REMOTERENDER_BUFFER @b @BR
  * - PBUFFER - Use an OpenGL Pbuffer for rendering (Default).
  * Allows accelerated off-screen rendering. If not available,
  * use a Pixmap.
  *
  * - PIXMAP - Use a Pixmap for rendering.
  * (Was the default value prior to version 3.1)
  *
  * - SCREEN - Use an on-screen window for rendering.
  * Generally provides best performance, but user must have
  * exclusive use of screen to avoid the window being overlapped
  * by other windows.
  *
  * @anchor OIV_REMOTERENDER_DEBUG @B OIV_REMOTERENDER_DEBUG @b @BR
  * Debug info is enabled when set to "1".
  *
  * @anchor OIV_REMOTERENDER_DISPLAY @B OIV_REMOTERENDER_DISPLAY @b @BR
  * Set this to the local X display string. The default is ":0.0".
  * Set to ":0.1" to use the second pipe and so on (if any).
  *
  * @anchor OIV_REPORT_ZERO_VECTORS @B OIV_REPORT_ZERO_VECTORS @b @BR
  * Applies only to the Open Inventor debug libraries. @BR
  * If set to 0, disables reporting of zero length vectors, specifically
  * direction vectors computed by certain interactive features,
  * e.g., draggers.
  *
  * @anchor OIV_REQUIRE_STENCIL @B OIV_REQUIRE_STENCIL \<int\>@b @BR
  * Provides a strong hint that an OpenGL stencil buffer is required
  * for correct rendering. The integer value is the requested stencil
  * buffer depth (default is 1). On Win32, a pixel format that has
  * a stencil buffer will be chosen even if it is not accelerated.
  *
  * @anchor OIV_SEEK_TIME @B OIV_SEEK_TIME @b@BR
  * Affects SoWinViewer, SoQtViewer, SoXtViewer.@BR
  * Specifies the default seek time (seconds).
  * The seek time can be set programmatically using the setSeekTime
  * method of the viewers classes above.
  *
  * @anchor OIV_SHADER_CHECK_INTERVAL @B OIV_SHADER_CHECK_INTERVAL @b @BR
  * Affects SoShaderObject. @BR
  * Specifies how frequently the shader source file is checked for a change (in seconds).
  * This allows you to edit a shader without needing to restart your
  * application after each shader modification.
  *
  * @anchor OIV_SHAPE_TYPE @B OIV_SHAPE_TYPE @b@BR
  * Affects SoShapeHints.@BR
  * Specifies the default shape type. Valid values
  * are UNKNOWN, SOLID.
  * The shape type can be set programmatically using the
  * SoShapeHints::shapeType field.
  *
  * @anchor OIV_SHARE_GEOM_MUTEX @B OIV_SHARE_GEOM_MUTEX @b @BR
  * By default all the geometry nodes share a single class mutex.
  * This reduces the number of mutexes needed and does not impose any
  * penalty once the geometry is render cached. If geometry cannot
  * be render cached, it may be better to use per-node mutexes by setting
  * this variable to "0" (zero).
  * Notes that in multi-thread mode default value is 0.
  *
  * @anchor OIV_SHARE_LISTS @B OIV_SHARE_LISTS @b @BR
  * Specifies what kind of OpenGL display list sharing is allowed.
  *
  * - 0 Disable display list sharing (same behavior as v2.6 and older)
  *
  * - 1 Conservative sharing (not available on Unix) @BR
  * Only add context to a share group containing contexts with the
  * same pixel format. This is the "official" limitation per the
  * Microsoft documentation, but is very limiting.
  *
  * - 2 Aggressive sharing (default) @BR
  * Add context to the first share group that OpenGL says we can
  * share with. This may allow us to share between contexts with
  * different pixel formats, which is valuable for single vs.
  * double buffered, stereo vs mono, etc.
  *
  * @anchor OIV_SORTED_LAYERS_TEXTURE_UNIT @B OIV_SORTED_LAYERS_TEXTURE_UNIT @b@BR
  * If set, the SORTED_LAYERS_BLEND transparency type will use this
  * texture unit internally instead of SoFragmentShader::getMaxTextureImageUnit()-1.
  *
  * @anchor OIV_STEREO_ACTIVE @B OIV_STEREO_ACTIVE @b@BR
  * Affects SoQtViewer, SoStereoViewer, SoWinMPRenderArea, SoWinViewer, SoXtMPRenderArea,
  * SoXtViewer.@BR
  * Specifies the default stereo viewing status. Valid values
  * are 0 or 1 (inactive or active).
  * The value can be set programmatically using the setStereoActive method
  * of the classes above.
  *
  * @anchor OIV_STEREO_BALANCE @B OIV_STEREO_BALANCE @b@BR
  * Affects SoQtViewer, SoStereoViewer, SoWinMPRenderArea, SoWinViewer, SoXtMPRenderArea,
  * SoXtViewer.@BR
  * Specifies the default stereo balance (the position of the zero parallax plane).
  * The value is specified as a float.
  * The value can be set programmatically using the setStereoBalance method
  * of the classes above.
  *
  * @anchor OIV_STEREO_BALANCE_NEAR_FRAC @B OIV_STEREO_BALANCE_NEAR_FRAC @b@BR
  * Affects SoQtViewer, SoStereoViewer, SoWinMPRenderArea, SoWinViewer, SoXtMPRenderArea,
  * SoXtViewer.@BR
  * Specifies whether the default stereo balance (the position of the zero parallax plane) is
  * defined as a fraction of the camera near distance, or not.
  * The value is specified as a boolean.
  * The value can be set programmatically using the setStereoBalance method
  * of the classes above.
  *
  * @anchor OIV_STEREO_ERROR_DIALOG @B OIV_STEREO_ERROR_DIALOG @b@BR
  * Affects SoQtGLWidget.@BR
  * If TRUE (1), an error dialog is shown when you try to enable raw stereo
  * on a system where raw stereo is not supported by the graphics board.
  * Default is TRUE.
  *
  * @anchor OIV_STEREO_GREENSHIFT @B OIV_STEREO_GREENSHIFT @b@BR
  * Affects SoInterlacedStereo. @BR
  * Enables the "green shift" operation. This is an image post-processing operation
  * required for stereo on a Sharp 3D LCD display. It is only meaningful when the
  * stereo format is vertical interlaced (fast or best).
  *
  * @anchor OIV_STEREO_OFFSET @B OIV_STEREO_OFFSET @b@BR
  * Affects SoQtViewer, SoStereoViewer, SoWinMPRenderArea, SoWinViewer, SoXtMPRenderArea,
  * SoXtViewer.@BR
  * Specifies the default stereo offset. The value is specified as a float.
  * The value can be set programmatically using the setStereoOffset method
  * of the classes above.
  *
  * @anchor OIV_STEREO_TESTPATTERN @B OIV_STEREO_TESTPATTERN @b@BR
  * Affects SoQtViewer, SoStereoViewer, SoWinMPRenderArea, SoWinViewer, SoXtMPRenderArea,
  * SoXtViewer.@BR
  * When stereo is enabled, displays a stereo text pattern on top of
  * the scene (it's probably best not to have anything else in
  * the scene). It displays a blue rectangle which should be visible
  * only to the left eye and a red rectangle which should be visible
  * only to the right eye. This allows you to confirm the display is
  * actually doing stereo and that the left/right eye images are
  * displayed in the correct order.
  *
  * @anchor OIV_STEREO_TYPE @B OIV_STEREO_TYPE @b@BR
  * Affects SoQtViewer, SoStereoViewer, SoWinMPRenderArea, SoWinViewer, SoXtMPRenderArea,
  * SoXtViewer.@BR
  * Specifies the default stereo viewer type. Valid values
  * are ANAGLYPH_RED_CYAN, ANAGLYPH_GREEN_MAGENTA, ANAGLYPH_BLUE_YELLOW,
  *            HALF_SCREEN_OVERUNDER_FILL, HALF_SCREEN_OVERUNDER,
  *            HALF_SCREEN_SIDEBYSIDE_FILL, HALF_SCREEN_SIDEBYSIDE,
  *            INTERLACED_HORIZONTAL_BEST, INTERLACED_VERTICAL_BEST,
  *            INTERLACED_HORIZONTAL_FAST, INTERLACED_VERTICAL_FAST, RAW.
  * The value can be set programmatically using the setStereoViewType method
  * of the classes above.
  *
  * @anchor OIV_STILL_DRAW_STYLE @B OIV_STILL_DRAW_STYLE @b@BR
  * Affects SoWinViewer, SoQtViewer, SoXtViewer.@BR
  * Specifies the default still draw style.
  * Valid values are: VIEW_AS_IS, VIEW_HIDDEN_LINE, VIEW_NO_TEXTURE,
  *            VIEW_LOW_COMPLEXITY, VIEW_LINE, VIEW_POINT, VIEW_BBOX,
  *            VIEW_LOW_RES_LINE, VIEW_LOW_RES_POINT.
  * The still draw style can be set programmatically using the setDrawStyle method
  * of the viewers classes above.
  *
  * @anchor OIV_STROKE_FONT_PATH @B OIV_STROKE_FONT_PATH @b @BR
  * Specifies the path of the directory containing the VSG stroke
  * font data files. See SoFont for information on the stroke
  * font files.
  *
  * @anchor OIV_STREAM_BUFFERS_NUMBER @B OIV_STREAM_BUFFERS_NUMBER @b @BR
  * Specifies the number of buffers used for the asynchronous file reading.
  *
  * @anchor OIV_STREAM_BUFFERS_SIZE @B OIV_STREAM_BUFFERS_SIZE @b @BR
  * Specifies the size of the buffers used for the asynchronous file reading.
  *
  * @anchor OIV_TEXTURE_BORDER_CLAMP_ENABLE @B OIV_TEXTURE_BORDER_CLAMP_ENABLE @b @BR
  * Affects SoShadowGroup. @BR
  *
  * Some shadowing problems (performance issues or no computation
  * of shadows) have been observed with some OpenGL drivers due
  * to the Texture Border Clamp OpenGL extension. Set this environment
  * variable to to 0 to disable use of this extension if necessary.
  *
  * @anchor OIV_TEXTURE_QUALITY @B OIV_TEXTURE_QUALITY @b@BR
  * Affects SoComplexity.@BR
  * Specifies the default texture quality (0.0 to 1.0).
  * The texture quality can be set programmatically using the
  * SoComplexity::textureQuality field.
  *
  * @anchor OIV_TEXTURED_TEXT_NO_MIPMAP @B OIV_TEXTURED_TEXT_NO_MIPMAP @b@BR
  * Affects text nodes when renderStyle is TEXTURED.@BR
  * Enables/Disables the use of mipmaps for textured text.
  * By default, mipmaps are generated considering the SoComplexity::textureQuality value.
  *
  * @anchor OIV_TRACKER_DIRECT_MODE @B OIV_TRACKER_DIRECT_MODE @b@BR
  * Affects SoDragger.@BR
  * Specifies the tracker direct mode.
  * Valid values are: NONE, MOVE, ROTATE, FREE, DEFAULT.
  * The tracker direct mode can be set programmatically using
  * SoDragger::setTrackerDirectMode.
  *
  * @anchor OIV_TRANSPARENCY_TYPE @B OIV_TRANSPARENCY_TYPE @b@BR
  * Affects SoGLRenderAction.@BR
  * Specifies the default transparency type.
  * Valid values are: SCREEN_DOOR, ADD, DELAYED_ADD, SORTED_OBJECT_ADD, BLEND,
  * DELAYED_BLEND, SORTED_OBJECT_BLEND, SORTED_TRIANGLES_ADD,
  * SORTED_TRIANGLES_BLEND, SORTED_OBJECT_TRIANGLES_ADD,
  * SORTED_OBJECT_TRIANGLES_BLEND, SORTED_LAYERS_BLEND.
  * The transparency type can be set programmatically using
  * GLRenderAction::transparencyType.
  *
  * @anchor OIV_TRANSPARENT_PIXEL @B OIV_TRANSPARENT_PIXEL @b [UNIX only] @BR
  * Specifies the color map index of the transparent pixel to be
  * used for clearing the overlay context. It overrides the value
  * built into Open Inventor or obtained from OpenGL.
  *
  * @anchor OIV_UPDATE_AREA_COMPAT @B OIV_UPDATE_AREA_COMPAT @b @BR
  * Affects SoGLRenderAction. @BR
  *
  * If not set (default), the update area is used for render
  * culling and for limiting the rectangular area of the viewport
  * region that will actually be rendered into.
  *
  * If set, Open Inventor will use the version 3.1.1 (and earlier)
  * behavior of the update area. The specified update area is used
  * for render culling, but not for limiting the rectangular area
  * of the viewport region that will be rendered into.
  *
  * @anchor OIV_USE_GLOBALFIELD_TIME @B OIV_USE_GLOBALFIELD_TIME @b @BR
  * Affects Open Inventor applications that use CAVELib.@BR
  * If set to 1, SoDB::getCurrentTime() will return the current time based
  * on the global "realTime" field which the CAVELib application can
  * set to Cave Time before each frame. Default is 0.
  *
  * @anchor OIV_USE_HEADLIGHT @B OIV_USE_HEADLIGHT @b@BR
  * Affects SoWinViewer, SoQtViewer, SoXtViewer.@BR
  * Specifies if the headlight is on by default (0=no, 1=yes)
  * The headlight state can be set programmatically using the setHeadlight method
  * of the classes above.
  *
  * @anchor OIV_USE_NPOT @B OIV_USE_NPOT @b@BR
  * Affects SoExtTexture2, SoTexture2, SoTextureCubeMap, SoVRMLTexture (and derived classes) @BR
  * By default, if your graphics board supports the OpenGL extension
  * ARB_texture_non_power_of_two, Open Inventor will pass non-power-of-two
  * textures directly to OpenGL.
  * To disable this behavior, set this configuration parameter to 0.
  * In this case the image will be scaled up or down to the next power of 2.
  * Default is 1.
  *
  * @anchor OIV_USE_OOB  @B OIV_USE_OOB @b@BR
  * Affects SoShape (and derived classes) @BR
  * By default, Open Inventor use Axis Aligned Bounding Box (AABB).
  * set this configuration parameter to 1, Object Oriented Bounding (OOB)
  * will be used whenever possible.
  * Using OOB provides better selection mechanism for culling, picking
  * and collision detection at the cost of higher CPU usage.
  * Default is 0.
  *
  * @anchor OIV_USER_LIBS @B OIV_USER_LIBS @b @BR
  * Defines a semi-colon separated list of shared libraries (UNIX) or DLLs (Windows)
  * that contain custom nodes to be loaded.
  * Items in list can be full paths, relative paths, library name with or without extension.
  * When using single library name, Open Inventor will search for them in various directories
  * as described in SoDynamicLibManager.
  *
  * @anchor OIV_VERTEX_ATTRIBS @B OIV_VERTEX_ATTRIBS @b @BR
  * Affects SoVertexShaderParameter and its derived classes.
  * If set to 0, vertex shader attributes are ignored.
  * Default is 1.
  *
  * @anchor OIV_VERTEX_ORDERING @B OIV_VERTEX_ORDERING @b@BR
  * Affects SoShapeHints.@BR
  * Specifies the default vertex ordering. Valid values
  * are UNKNOWN, CLOCKWISE, COUNTERCLOCKWISE.
  * The vertex ordering can be set programmatically using the
  * SoShapeHints::vertexOrdering field.
  *
  * @anchor OIV_VIEWER_ANIMATION @B OIV_VIEWER_ANIMATION @b@BR
  * Affects SoWinExaminerViewer, SoQtExaminerViewer, SoXtExaminerViewer.@BR
  * Specifies if animation is enabled by default (0=off, 1=on).
  * The animation flag can be set programmatically using the setAnimationEnabled
  * method of the viewers classes above.
  *
  * @anchor OIV_VIEWER_DECORATION @B OIV_VIEWER_DECORATION @b@BR
  * Affects SoWinFullViewer, SoQtFullViewer, SoXtFullViewer.@BR
  * Specifies if decorations are on or off by default (0=off, 1=on).
  * Decorations can be enabled/disabled programmatically using the
  * setDecoration method of the viewers classes above.
  *
  * @anchor OIV_VIEWER_POPUP_MENU @B OIV_VIEWER_POPUP_MENU @b@BR
  * Affects SoWinFullViewer, SoQtFullViewer, SoWxFullViewer, SoXtFullViewer.@BR
  * Specifies if the popup menu is enabled by default (0=off, 1=on).
  * The popup menu can be enabled/disabled programmatically using the
  * setPopupMenuEnabled method of the viewers classes above.
  *
  * @anchor OIV_VIEWER_SIZE @B OIV_VIEWER_SIZE @b@BR
  * Affects all SoXXXFullViewer (and derived) classes, including SoWinFullViewer,
  * SoQtFullViewer, SoXtFullViewer, SoXtMPFullViewer and SoWinMPFullViewer.@BR
  * Specifies the default size of the viewer window in pixels.
  * Default since Open Inventor 8.1 is 800x600 (previously was 400x400).
  *
  * @anchor OIV_VIEWER_SHOW_DIRECTVIZ_ENTRY @b@BR @TOBEREVIEWED
  * Affects SoWinFullViewer, SoQtFullViewer, SoWxFullViewer, SoXtFullViewer.@BR
  * Specifies if the "DirectViz" entry is available in the popup menu.
  * This entry is available by default (0=off, 1=on).
  * 
  * @anchor OIV_VIEWER_SHOW_RECORD_ENTRY @b@BR @TOBEREVIEWED
  * Affects SoWinFullViewer, SoQtFullViewer, SoWxFullViewer, SoXtFullViewer.@BR
  * Specifies if the "Record" entry is available in the popup menu.
  * This entry is available by default (0=off, 1=on).
  *
  * @anchor OIV_VIEWER_SHOW_FSAA_ENTRY @b@BR @TOBEREVIEWED
  * Affects SoWinFullViewer, SoQtFullViewer, SoWxFullViewer, SoXtFullViewer.@BR
  * Specifies if the "Full Scene AntiAliasing" entry is available in the popup menu.
  * This entry is available by default (0=off, 1=on).
  *
  * @anchor OIV_VIEWER_SHOW_STEREO_ENTRY @b@BR @TOBEREVIEWED
  * Affects SoWinFullViewer, SoQtFullViewer, SoWxFullViewer, SoXtFullViewer.@BR
  * Specifies if the "Stereo" entry is available in the popup menu.
  * This entry is available by default (0=off, 1=on).
  *
  * @anchor OIV_VRML_IMAGETEXTURE_MODEL_SUPPORT @B OIV_VRML_IMAGETEXTURE_MODEL_SUPPORT @b@BR
  * Specifies if SoVRMLImageTexture nodes should use the @I textureModel @i
  * hidden field. This field allows additional control over rendering,
  * similar to the standard Open Inventor texture nodes. Off by default (0=off, 1=on).
  *
  * @anchor OIV_WHEEL_DELTA @B OIV_WHEEL_DELTA @b @BR
  * Affects SoMouseWheelEvent.@BR
  * A mouse wheel has discrete, evenly spaced notches. When you rotate the
  * wheel, a wheel message is sent as each notch is encountered. Most
  * modern mouse wheels generate an event with a value of 120 per each
  * notch of the wheel. You can use this environment
  * variable to change this value.
  *
  * @anchor OIV_WINDING_TYPE @B OIV_WINDING_TYPE @b@BR
  * Affects SoShapeHints.@BR
  * Specifies the default winding type. Valid values
  * are NONE, ODD, NON_ZERO, POSITIVE, NEGATIVE, ABS_GEQ_TWO.
  * The winding type can be set programmatically using the
  * SoShapeHints::windingType field.
  *
  * @anchor OIV_ZERO_AREA_CHECK @B OIV_ZERO_AREA_CHECK @b @BR
  * Set this to a small positive float value. @BR
  * During decimation, a triangle with an area less than
  * the specified value will be discarded. If you notice
  * missing triangles in decimated output, try setting
  * the value to a smaller number. Default: 1E-5.
  *
  * @anchor OIV_ZLIB_NAME @B OIV_ZLIB_NAME @b @BR
  * Affects SoDynamicLibManager. @BR
  * Allows you to use your own zlib dynamic library.
  * Do not add the suffix.
  * Do not add the "lib" prefix on UNIX systems.
  * Do not add the final "D" used in the debug name.
  * Default is "IvDLZlib".
  *
  * @anchor OIV_SET_RAY_PRECISION @B OIV_SET_RAY_PRECISION @b@BR
  * Affects SoRayPickAction when defining a ray using the setRay method@BR
  * Specify (in radius) the value of fovy angle defined by the ray.
  * If not set, the default value is set to 0.0003F
  *
  * @anchor SO_DRAGGER_DIR @B SO_DRAGGER_DIR @b @BR
  * Specifies the path to the directory containing dragger
  * geometry files. By default, Open Inventor uses the dragger
  * geometry files from $OIVHOME/data/draggerDefaults. See SoDragger.
  *
  * @anchor SCALEVIZ_CLUSTERCOM @B SCALEVIZ_CLUSTERCOM @b @BR
  * Specifies which communication layer library to used by ScaleViz for Render Unit
  * communication (OIRU).
  * This value is a string that will specify:@BR @BR
  * libClustercom-\<string\>.so or ClusterCom-\<string\>.dll @BR @BR as the library to use
  * and @BR @BR
  * launch-\<string\>.sh or launch-\<string\>.bat @BR @BR as the launcher script to use to spawn the process for this
  * type of communication.
  * Default is "base" which is the default supported implementation for a given OS.
  * See ScaleViz text in User's Guide for more information.
  *
  * @anchor SCALEVIZ_CONFIG_FILE @B SCALEVIZ_CONFIG_FILE @b @BR
  * Specifies the path of the ScaleViz configuration file.
  *
  * @anchor SCALEVIZ_CONNECT_TIMEOUT @B SCALEVIZ_CONNECT_TIMEOUT @b @BR
  * Specifies the connection timeout in seconds used by application to connect
  * to ScaleViz Daemon/Service.
  * Default is 5 seconds.
  *
  * @anchor SCALEVIZ_DISABLE_GUI @B SCALEVIZ_DISABLE_GUI @b @BR
  * Applies to ScaleViz.@BR
  * Enables/Disables display of the ScaleViz GUI dialog provided with
  * the ScaleViz package. Default value is 0 (GUI is enabled by default).
  *
  * @anchor SCALEVIZ_GUI_SHORTCUT @B SCALEVIZ_GUI_SHORTCUT @b @BR
  * Applies to ScaleViz.@BR
  * Controls the keyboard shortcut used for displaying the ScaleViz GUI dialog.
  * The shortcut is composed of [SHIFT] followed by a second key.
  * Use this environment variable to specify the value of the second key, chosen
  * from the SoKeyboardEvent::Key enum.
  * Default is 0xFFC6 [F9], which corresponds to a shortcut of [SHIFT] + [F9].
  *
  * @anchor SCALEVIZ_OIRU_DISPLAY @B SCALEVIZ_OIRU_DISPLAY @b @BR
  * Applies to ScaleViz compositing (depth compositing, tile compositing).
  * - 1  Open Inventor Render Unit (OIRU) will display its rendered image on its own screen.
  *   Useful for debugging the configuration file or scene graph distribution.
  * - 0 (default) (no display of rendered image on OIRU's screen)
  *
  * @anchor SCALEVIZ_OIRU_PATH @B SCALEVIZ_OIRU_PATH @b @BR
  * Specifies the path to the Open Inventor Render Unit (OIRU).
  * The OIRU is a small executable that runs on the "slave" nodes
  * in a ScaleViz render cluster.
  * By default the OIRU is in %OIVHOME%/%OIVARCH%/bin/oiru.exe on Windows,
  * and $OIVHOME/$OIVARCH/bin/oiru on UNIX or Linux.
  *
  * @anchor SCALEVIZ_USER_LIBS @B SCALEVIZ_USER_LIBS @b @BR
  * Deprecated, replaced by OIV_USER_LIBS.
  * Is a semi-colon separated list of shared libraries (UNIX) or DLLs (Windows)
  * that contain custom nodes to be loaded.
  * Only the file names should be specified. Open Inventor will search
  * for them in various directories as described in SoDynamicLibManager.
  *
  * @anchor SCALEVIZD_RESOURCES_FILE @B SCALEVIZD_RESOURCES_FILE @b @BR
  * Specifies the path to the file describing the resources available in
  * the cluster.
  *
  * @anchor TGS_LICENSE_DEBUG @B TGS_LICENSE_DEBUG @b [Deprecated] @BR
  * Deprecated, please use VSG_LICENSE_DEBUG instead.
  *
  * @anchor TGS_LICENSE_FILE @B TGS_LICENSE_FILE @b [Deprecated] @BR
  * Deprecated, please use VSG_LICENSE_FILE instead.
  *
  * @anchor TVIZ_COMPAT_20 @B TVIZ_COMPAT_20 @b @BR
  * Affect SoTVizRender.@BR
  * If set, TerrainViz will use the version 2.0
  * algorithm for handling normals.
  *
  * @anchor TVIZ_VIEWER_DATA_PATH @B TVIZ_VIEWER_DATA_PATH @b @BR
  * Affects SoTVizViewer.@BR
  * Specifies the name of the directory where
  * the .iv files for the TerrainViz navigation tools are located.
  *
  * @anchor below @B Debug Environment Variables@b @BR
  * We recommend these flags only be used by expert Open Inventor
  * users or at the request of VSG Customer Support.
  *
  * @B IV_DEBUG_BUFLEN \<num> @b @BR Constructs an internal \<num> length
  * buffer to print into (See SoDebug.C)
  *
  * @B IV_DEBUG_CACHES @b @BR Prints interesting (!) stuff
  *
  * @B IV_DEBUG_CACHELIST @b @BR Ditto
  *
  * @B IV_DEBUG_SENSORS @b @BR Ditto (lots of!)
  *
  * @B IV_DEBUG_TRANSFORM_MANIP_FIELDS @b @BR Ditto
  *
  * @B IV_DEBUG_KIT_PARTS @b @BR Ditto
  *
  * @B IV_DEBUG_FROMNAME @b @BR Issues a message if the dynamic load
  * of a node class fails.
  *
  * @B IV_DEBUG_PICK_CULL @b @BR For relevant grouping nodes, prints
  * whether they were culled during picking.
  *
  * @B IV_DEBUG_RENDER_CULL @b @BR For relevant grouping nodes, prints
  * whether they were culled during rendering.
  *
  * @B IV_DEBUG_TEXCACHE @b @BR Prints information about texture caching.
  *
  * @B IV_DEBUG_WRITE_KIT_CHILDREN @b @BR Forces a nodekit to be
  * written out like an SoGroup node.
  *
  * @B OIV_DEBUG_SHADOW @b @BR Prints debug information about
  * SoShadowGroup.
  *
  * @B OIV_MP_DEBUG @b @BR Prints debug information about the
  * multi-pipe viewer.
  *
  * @B OIV_MUTEX_TIMEOUT @b [_WIN32 only] @BR Sets a timeout value
  * in milliseconds for the Open Inventor mutex classes, e.g.,
  * SbThreadMutex. If the timeout is exceeded without acquiring
  * the mutex or read/write lock, a message is printed. This can
  * be useful if you suspect the application is deadlocked in an
  * Open Inventor mutex. The default is no timeout in the release
  * build and five seconds in the debug build. NOTE: This item cannot be set
  * via SoPreferences or a configuration file. It must be set
  * in the environment (e.g., using set).
  *
  * @B OIV_SYNCHRONIZE @b [UNIX only] @BR If this variable is set
  * to "1", then Open Inventor will call
  * XSynchronize on each display connection that it uses. This
  * can be helpful if your application is getting an X error (hint:
  * set a breakpoint in the Xlib function _XError).
  *
  * @anchor VSG_LICENSE_DEBUG @B VSG_LICENSE_DEBUG @b @BR
  * Specifies the name of the file to which license debug
  * information will be written. If not set, license debug info is not generated.
  *
  * @anchor VSG_LICENSE_FILE @B VSG_LICENSE_FILE @b @BR
  * Specifies the full path of the file containing the VSG
  * license strings for Open Inventor and its extensions.
  * Open Inventor searches for a valid password in the
  * following locations: internal unlock string (see SoLockManager),
  * the system registry (Windows only, see Ladmin.htm),
  * VSG_LICENSE_FILE, $OIVHOME/license/password.dat, and password.dat
  * in the current directory.

 *
 * @SEE_ALSO
 *    SoBase,
 *    SoDB
 *
 *
 */

class INVENTORBASE_API SoPreferences {
 public:
  // Retrieving values

  /**
   * Returns the value of the specified environment variable in the
   * Open Inventor environment.
   * @BR
   * @BR
   * When the getValue method is called:
   *
   *   - It searches for the environment variable in memory and returns
   *     the associated value if found,
   *
   *   - If not found, it searches for the environment variable
   *     in the system environment.
   *
   *   - If found in the system environment, the environment variable
   *     and its value are stored in memory for faster access the next
   *     time it is queried.
   *
   *
   * The return value is the address of a character string containing
   * the associated value. This string may be empty if the name is
   * defined but does not have an associated value.
   *
   * The return value is NULL if the name was not found in the Open
   * Inventor environment or the system environment.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE static const char* getValue (const char* name);

  /**
   * Returns the value of the specified environment variable in the
   * Open Inventor environment.
   * @BR
   * @BR
   * When the getStringValue method is called:
   *
   *   - It searches for the environment variable in memory and returns
   *     the associated value if found,
   *
   *   - If not found, it searches for the environment variable
   *     in the system environment.
   *
   *   - If found in the system environment, the environment variable
   *     and its value are stored in memory for faster access the next
   *     time it is queried.
   *
   *
   * The return value is the address of a character string containing
   * the associated value. This string may be empty if the name is
   * defined but does not have an associated value.
   *
   * The return value is NULL if the name was not found in the Open
   * Inventor environment or the system environment.
   */
  static const SbString* getStringValue( const SbString& name );

  /**
   * Returns the value of the specified environment variable in the Open Inventor
   * environment, interpreted as a @B boolean@b. The search process is the same as for
   * #getValue.@BR
   * If the environment variable is not
   * defined in the Open Inventor environment, or if its value cannot be interpreted
   * as a @B boolean@b, the specified default value will be returned.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE static SbBool getBool( const char* name, SbBool defaultValue );

  /**
   * Returns the value of the specified environment variable in the Open Inventor
   * environment, interpreted as a @B boolean@b. The search process is the same as for
   * #getValue.@BR
   * If the environment variable is not
   * defined in the Open Inventor environment, or if its value cannot be interpreted
   * as a @B boolean@b, the specified default value will be returned.
   */
  static SbBool getBool( const SbString& name, SbBool defaultValue );

  /**
   *
   * Returns the value of the specified environment variable in the Open Inventor
   * environment, interpreted as an @B int@b. The search process is the same as for
   * #getValue.@BR
   * If the environment variable is not
   * defined in the Open Inventor environment, or if its value cannot be interpreted
   * as an @B int@b, the specified default value will be returned.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE static int getInt( const char* name, int defaultValue );

  /**
   *
   * Returns the value of the specified environment variable in the Open Inventor
   * environment, interpreted as an @B int@b. The search process is the same as for
   * #getValue.@BR
   * If the environment variable is not
   * defined in the Open Inventor environment, or if its value cannot be interpreted
   * as an @B int@b, the specified default value will be returned.
   */
  static int getInt( const SbString& name, int defaultValue);

  /**
   *
   * Returns the value of the specified environment variable in the Open Inventor
   * environment, interpreted as a @B long@b. The search process is the same as for
   * #getValue.@BR
   * If the environment variable is not
   * defined in the Open Inventor environment, or if its value cannot be interpreted
   * as a @B long@b, the specified default value will be returned.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE static long getLong( const char* name, long defaultValue );

  /**
   *
   * Returns the value of the specified environment variable in the Open Inventor
   * environment, interpreted as a @B long@b. The search process is the same as for
   * #getValue.@BR
   * If the environment variable is not
   * defined in the Open Inventor environment, or if its value cannot be interpreted
   * as a @B long@b, the specified default value will be returned.
   */
  static long getLong( const SbString& name, long defaultValue );

  /**
   *
   * Returns the value of the specified environment variable in the Open Inventor
   * environment, interpreted as a @B float@b. The search process is the same as for
   * #getValue.@BR
   * If the environment variable is not
   * defined in the Open Inventor environment, or if its value cannot be interpreted
   * as a @B float@b, the specified default value will be returned.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE static float getFloat( const char* name, float defaultValue );

  /**
   *
   * Returns the value of the specified environment variable in the Open Inventor
   * environment, interpreted as a @B float@b. The search process is the same as for
   * #getValue.@BR
   * If the environment variable is not
   * defined in the Open Inventor environment, or if its value cannot be interpreted
   * as a @B float@b, the specified default value will be returned.
   */
  static float getFloat( const SbString& name, float defaultValue );

  /**
   *
   * Returns the value of the specified environment variable in the Open Inventor
   * environment, interpreted as a @B double@b. The search process is the same as for
   * #getValue.@BR
   * If the environment variable is not
   * defined in the Open Inventor environment, or if its value cannot be interpreted
   * as a @B double@b, the specified default value will be returned.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE static double getDouble( const char* name, double defaultValue );

  /**
   *
   * Returns the value of the specified environment variable in the Open Inventor
   * environment, interpreted as a @B double@b. The search process is the same as for
   * #getValue.@BR
   * If the environment variable is not
   * defined in the Open Inventor environment, or if its value cannot be interpreted
   * as a @B double@b, the specified default value will be returned.
   */
  static double getDouble( const SbString& name, double defaultValue );

  /**
   *
   * Returns the value of the specified environment variable in the Open Inventor
   * environment. The search process is the same as for
   * #getValue.@BR
   * If the environment variable is not
   * defined in the Open Inventor environment, or if it is defined with no values
   * or as an empty string,
   * the specified default value will be returned.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE static const SbString& getString (const char* name, const SbString& defaultValue);

  /**
   *
   * Returns the value of the specified environment variable in the Open Inventor
   * environment. The search process is the same as for
   * #getValue.@BR
   * If the environment variable is not
   * defined in the Open Inventor environment, or if it is defined with no values
   * or as an empty string,
   * the specified default value will be returned.
   */
  static const SbString& getString( const SbString& name, const SbString& defaultValue );

  /**
   *
   * Returns the value of the specified environment variable in the Open Inventor
   * environment, interpreted as an @B SbVec3f@b. The search process is the same as for
   * #getValue.@BR
   * If the environment variable is not
   * defined in the Open Inventor environment, or if its value cannot be interpreted
   * as an @B SbVec3f@b, the specified default value will be returned.
   * @BR
   * To be correctly interpreted, the environment value must be a series of 3 floats
   * separated by spaces.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE static const SbVec3f& getVec3f( const char* name, const SbVec3f& defaultValue );

  /**
   *
   * Returns the value of the specified environment variable in the Open Inventor
   * environment, interpreted as an @B SbVec3f@b. The search process is the same as for
   * #getValue.@BR
   * If the environment variable is not
   * defined in the Open Inventor environment, or if its value cannot be interpreted
   * as an @B SbVec3f@b, the specified default value will be returned.
   * @BR
   * To be correctly interpreted, the environment value must be a series of 3 floats
   * separated by spaces.
   */
  static const SbVec3f& getVec3f( const SbString& name, const SbVec3f& defaultValue );

    /**
   *
   * Returns the value of the specified environment variable in the Open Inventor
   * environment, interpreted as an @B SbVec2s@b. The search process is the same as for
   * #getValue.@BR
   * If the environment variable is not
   * defined in the Open Inventor environment, or if its value cannot be interpreted
   * as an @B SbVec2s@b, the specified default value will be returned.
   * @BR
   * To be correctly interpreted, the environment value must be a series of 2 shorts
   * separated by spaces.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE static const SbVec2s& getVec2s( const char* name, const SbVec2s& defaultValue );

  /**
   *
   * Returns the value of the specified environment variable in the Open Inventor
   * environment, interpreted as an @B SbVec2s@b. The search process is the same as for
   * #getValue.@BR
   * If the environment variable is not
   * defined in the Open Inventor environment, or if its value cannot be interpreted
   * as an @B SbVec2s@b, the specified default value will be returned.
   * @BR
   * To be correctly interpreted, the environment value must be a series of 2 shorts
   * separated by spaces.
   */
  static const SbVec2s& getVec2s( const SbString& name, const SbVec2s& defaultValue );

  /**
   *
   * Returns the value of the specified environment variable in the Open Inventor
   * environment, interpreted as an @B SbColor@b. The search process is the same as for
   * #getValue.@BR
   * If the environment variable is not
   * defined in the Open Inventor environment, or if its value cannot be interpreted
   * as an @B SbColor@b, the specified default value will be returned.
   * @BR
   * To be correctly interpreted, the environment value must be a series of 3 floats
   * between 0.0 and 1.0, separated by spaces.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE static const SbColor& getColor( const char* name, const SbColor& defaultValue );

  /**
   *
   * Returns the value of the specified environment variable in the Open Inventor
   * environment, interpreted as an @B SbColor@b. The search process is the same as for
   * #getValue.@BR
   * If the environment variable is not
   * defined in the Open Inventor environment, or if its value cannot be interpreted
   * as an @B SbColor@b, the specified default value will be returned.
   * @BR
   * To be correctly interpreted, the environment value must be a series of 3 floats
   * between 0.0 and 1.0, separated by spaces.
   */
  static const SbColor& getColor( const SbString& name, const SbColor& defaultValue );


  // Setting values

  /**
   * Sets a variable in the Open Inventor environment. As this
   * variable is set in memory, it is local to the application process
   * and can only be retrieved using SoPreferences methods.
   *
   * If the value parameter is set to NULL (default), then the
   * variable is set with no value associated with it.
   *
   * If the first character of the string name is a '-', then the
   * variable is unset in the Open Inventor environment.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE static void setValue( const char* name, const char* value = NULL );

  /**
   * Sets a variable in the Open Inventor environment. As this
   * variable is set in memory, it is local to the application process
   * and can only be retrieved using SoPreferences methods.
   *
   * If the value parameter is set to NULL (default), then the
   * variable is set with no value associated with it.
   *
   * If the first character of the string name is a '-', then the
   * variable is unset in the Open Inventor environment.
   */
  static void setValue( const SbString& name, const SbString* value = NULL );

  /**
   * Sets a variable that has a @B boolean@b value in the Open Inventor
   * environment. See #setValue for details.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE static void setBool( const char* name, SbBool value );

  /**
   * Sets a variable that has a @B boolean@b value in the Open Inventor
   * environment. See #setValue for details.
   */
  static void setBool( const SbString& name, SbBool value );

  /**
   * Sets a variable that has an @B int@b value in the Open Inventor
   * environment. See #setValue for details.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE static void setInt( const char* name, int value );

  /**
   * Sets a variable that has an @B int@b value in the Open Inventor
   * environment. See #setValue for details.
   */
  static void setInt( const SbString& name, int value );

  /**
   * Sets a variable that has a @B long@b value in the Open Inventor
   * environment. See #setValue for details.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE static void setLong( const char* name, long value );

  /**
   * Sets a variable that has a @B long@b value in the Open Inventor
   * environment. See #setValue for details.
   */
  static void setLong( const SbString& name, long value );

  /**
   * Sets a variable that has a @B float@b value in the Open Inventor
   * environment. See #setValue for details.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE static void setFloat( const char* name, float value );

  /**
   * Sets a variable that has a @B float@b value in the Open Inventor
   * environment. See #setValue for details.
   */
  static void setFloat( const SbString& name, float value );

  /**
   * Sets a variable that has a @B double@b value in the Open Inventor
   * environment. See #setValue for details.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE static void setDouble( const char* name, double value );

  /**
   * Sets a variable that has a @B double@b value in the Open Inventor
   * environment. See #setValue for details.
   */
  static void setDouble( const SbString& name, double value );

#ifdef OIV_NET_DOC
  /**
  * Sets a variable that has a @B String@b value in the Open Inventor
  * environment. See #setValue for details.
  *
  * @UNICODE_WARNING
  */

#else

  /**
  * Sets a variable that has an @B SbString@b value in the Open Inventor
  * environment. See #setValue for details.
  *
  * @UNICODE_WARNING
  */

#endif //OIV_NET_DOC

    SoNONUNICODE static void setString (const char* name, const SbString& value);

#ifdef OIV_NET_DOC
  /**
  * Sets a variable that has a @B String@b value in the Open Inventor
  * environment. See #setValue for details.
  */

#else

  /**
  * Sets a variable that has an @B SbString@b value in the Open Inventor
  * environment. See #setValue for details.
  */

#endif //OIV_NET_DOC

    static void setString( const SbString& name, const SbString& value );

  /**
   * Sets a variable that has an @B SbVec3f@b value in the Open Inventor
   * environment. See #setValue for details.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE static void setVec3f( const char* name, const SbVec3f& value );

  /**
   * Sets a variable that has an @B SbVec3f@b value in the Open Inventor
   * environment. See #setValue for details.
   */
  static void setVec3f( const SbString& name, const SbVec3f& value );

    /**
   * Sets a variable that has an @B SbVec2s@b value in the Open Inventor
   * environment. See #setValue for details.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE static void setVec2s( const char* name, const SbVec2s& value );

  /**
   * Sets a variable that has an @B SbVec2s@b value in the Open Inventor
   * environment. See #setValue for details.
   */
  static void setVec2s( const SbString& name, const SbVec2s& value );

  /**
   * Sets a variable that has an @B SbColor@b value in the Open Inventor
   * environment. See #setValue for details.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE static void setColor( const char* name, const SbColor& value );


  /**
   * Sets a variable that has an @B SbColor@b value in the Open Inventor
   * environment. See #setValue for details.
   */
  static void setColor( const SbString& name, const SbColor& value );

  /**
   * Reads environment name-value pairs from the specified
   * configuration file and adds them to the current Open Inventor
   * environment. See the @ref Format "Configuration File Format" section for details.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE static void readFile (const char* filename);

  /**
   * Reads environment name-value pairs from the specified
   * configuration file and adds them to the current Open Inventor
   * environment. See the @ref Format "Configuration File Format" section for details.
   */
  static void readFile (const SbString& filename);

 private:
  static SbDict* m_dictionary;
  static SbThreadMutex* m_mutex;
  static void initialize ();
  static SbString s_unspecifiedValue;
  static bool s_verbose_env;

SoINTERNAL public:
  static void clean();

  class SoPreferencesImpl;
  friend class SoPreferencesImpl; //VC6 doesn't allow inner classes to access private members

};
#endif // _SB_ENVIRONMENT_VARS_H

