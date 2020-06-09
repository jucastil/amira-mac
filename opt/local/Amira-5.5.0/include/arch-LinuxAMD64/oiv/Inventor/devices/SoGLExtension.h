/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Rodolphe ALBOU (Oct 2001)
**=======================================================================*/

#ifndef _SO_GL_EXTENSION_H_
#define _SO_GL_EXTENSION_H_

#include <Inventor/SbBasic.h>
#include <Inventor/SbString.h>
#include <Inventor/STL/list>
#include <Inventor/threads/SbThreadSpinlock.h>

class SoGLWindow;
class SbPList;

#if defined (_WIN32)
// Prototype declarations for Win32 specific context handling
typedef int (WINAPI * PFNWGLCHOOSEPIXELFORMATPROC) (HDC hdc, const PIXELFORMATDESCRIPTOR* ppfd);  
typedef int (WINAPI * PFNWGLDESCRIBEPIXELFORMATPROC) (HDC hdc, int iPixelFormat, UINT nBytes, LPPIXELFORMATDESCRIPTOR ppfd);
typedef int (WINAPI * PFNWGLSETPIXELFORMATPROC) (HDC hDC, int pf, const PIXELFORMATDESCRIPTOR* pfd);
typedef int (WINAPI * PFNWGLSWAPBUFFERSPROC) (HDC hdc);

#define wglChoosePixelFormat    SoGLExtension::m_wglChoosePixelFormat
#define wglSetPixelFormat       SoGLExtension::m_wglSetPixelFormat
#define wglDescribePixelFormat  SoGLExtension::m_wglDescribePixelFormat
#define wglSwapBuffers          SoGLExtension::m_wglSwapBuffers

#endif // _WIN32

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

/**
 * @VSGEXT Contains useful methods to query and use OpenGL extensions.
 *
 * @ingroup GLDevice
 *
 * @DESCRIPTION
 *   SoGLExtension is based on GLEW (the OpenGL Extension Wrangler library).
 *   The OpenGL Extension Wrangler Library (GLEW) is a cross-platform,
 *   open-source extension loading library. GLEW provides efficient run-time
 *   mechanisms for determining which OpenGL extensions are supported on the
 *   current platform.  Once an extension is known to be present, the function 
 *   linked to that extension can be called directly.
 *
 * @NOTES
 *   The SoGLExtension header file must be included before any OpenGL header files.
 *
 * @EXAMPLE
 *   Here is an example of checking if a GL extension is present:
 *
 *   <PRE>
 *
 *   if ( SoGLExtension::isAvailable("GL_ARB_vertex_program") )
 *     glGenProgramsARB(...); // It is safe to use the ARB_vertex_program extension here.
 *   
 *   </PRE>
 *
 */

/**
 * The following list categorizes the extensions that can be queried with
 * isAvailable():
 *
 * - GL_VERSION_1_1
 * - GL_VERSION_1_2
 * - GL_VERSION_1_3
 * - GL_VERSION_1_4
 * - GL_VERSION_1_5
 * - GL_VERSION_2_0
 * - GL_VERSION_2_1
 * - GL_VERSION_3_0
 * - GL_VERSION_3_1
 * - GL_VERSION_3_2
 * - GL_VERSION_3_3
 * - GL_VERSION_4_0
 * - GL_VERSION_4_1
 *
 * 3DFX
 * - GL_3DFX_multisample
 * - GL_3DFX_tbuffer
 * - GL_3DFX_texture_compression_FXT1
 *
 * AMD
 * - GL_AMD_draw_buffers_blend
 * - GL_AMD_performance_monitor
 * - GL_AMD_texture_texture4
 * - GL_AMD_vertex_shader_tessellator
 * - GL_AMD_seamless_cubemap_per_texture
 * - GL_AMD_shader_stencil_export
 * - GL_AMD_conservative_depth 
 * - GL_AMD_debug_output
 * - GL_AMD_name_gen_delete
 * - GL_AMD_transform_feedback3_lines_triangles 
 * - GL_AMD_depth_clamp_separate 
 *
 * APPLE
 * - GL_APPLE_aux_depth_stencil
 * - GL_APPLE_client_storage
 * - GL_APPLE_element_array
 * - GL_APPLE_fence
 * - GL_APPLE_float_pixels
 * - GL_APPLE_flush_buffer_range
 * - GL_APPLE_object_purgeable
 * - GL_APPLE_pixel_buffer
 * - GL_APPLE_rgb_422
 * - GL_APPLE_row_bytes
 * - GL_APPLE_specular_vector
 * - GL_APPLE_texture_range
 * - GL_APPLE_transform_hint
 * - GL_APPLE_vertex_array_object
 * - GL_APPLE_vertex_array_range
 * - GL_APPLE_vertex_program_evaluators
 * - GL_APPLE_ycbcr_422
 *
 * ARB
 * - GL_ARB_color_buffer_float
 * - GL_ARB_compatibility
 * - GL_ARB_copy_buffer
 * - GL_ARB_depth_buffer_float
 * - GL_ARB_depth_clamp
 * - GL_ARB_depth_texture
 * - GL_ARB_draw_buffers
 * - GL_ARB_draw_buffers_blend
 * - GL_ARB_draw_elements_base_vertex
 * - GL_ARB_draw_instanced
 * - GL_ARB_fragment_coord_conventions
 * - GL_ARB_fragment_program
 * - GL_ARB_fragment_program_shadow
 * - GL_ARB_fragment_shader
 * - GL_ARB_framebuffer_object
 * - GL_ARB_framebuffer_sRGB
 * - GL_ARB_geometry_shader4
 * - GL_ARB_half_float_pixel
 * - GL_ARB_half_float_vertex
 * - GL_ARB_imaging
 * - GL_ARB_instanced_arrays
 * - GL_ARB_map_buffer_range
 * - GL_ARB_matrix_palette
 * - GL_ARB_multisample
 * - GL_ARB_multitexture
 * - GL_ARB_occlusion_query
 * - GL_ARB_pixel_buffer_object
 * - GL_ARB_point_parameters
 * - GL_ARB_point_sprite
 * - GL_ARB_provoking_vertex
 * - GL_ARB_sample_shading
 * - GL_ARB_seamless_cube_map
 * - GL_ARB_shader_objects
 * - GL_ARB_shader_texture_lod
 * - GL_ARB_shading_language_100
 * - GL_ARB_shadow
 * - GL_ARB_shadow_ambient
 * - GL_ARB_sync
 * - GL_ARB_texture_border_clamp
 * - GL_ARB_texture_buffer_object
 * - GL_ARB_texture_compression
 * - GL_ARB_texture_compression_rgtc
 * - GL_ARB_texture_cube_map
 * - GL_ARB_texture_cube_map_array
 * - GL_ARB_texture_env_add
 * - GL_ARB_texture_env_combine
 * - GL_ARB_texture_env_crossbar
 * - GL_ARB_texture_env_dot3
 * - GL_ARB_texture_float
 * - GL_ARB_texture_gather
 * - GL_ARB_texture_mirrored_repeat
 * - GL_ARB_texture_multisample
 * - GL_ARB_texture_non_power_of_two
 * - GL_ARB_texture_query_lod
 * - GL_ARB_texture_rectangle
 * - GL_ARB_texture_rg
 * - GL_ARB_transpose_matrix
 * - GL_ARB_uniform_buffer_object
 * - GL_ARB_vertex_array_bgra
 * - GL_ARB_vertex_array_object
 * - GL_ARB_vertex_blend
 * - GL_ARB_vertex_buffer_object
 * - GL_ARB_vertex_program
 * - GL_ARB_vertex_shader
 * - GL_ARB_window_pos
 * - GL_ARB_blend_func_extended
 * - GL_ARB_draw_indirect
 * - GL_ARB_explicit_attrib_location
 * - GL_ARB_gpu_shader5
 * - GL_ARB_gpu_shader_fp64
 * - GL_ARB_occlusion_query2
 * - GL_ARB_sampler_objects
 * - GL_ARB_shader_bit_encoding
 * - GL_ARB_shader_subroutine
 * - GL_ARB_shading_language_include
 * - GL_ARB_tessellation_shader
 * - GL_ARB_texture_buffer_object_rgb32
 * - GL_ARB_texture_compression_bptc
 * - GL_ARB_texture_rgb10_a2ui
 * - GL_ARB_texture_swizzle
 * - GL_ARB_timer_query
 * - GL_ARB_transform_feedback2
 * - GL_ARB_transform_feedback3
 * - GL_ARB_vertex_type_2_10_10_10_rev 
 * - GL_ARB_ES2_compatibility
 * - GL_ARB_cl_event
 * - GL_ARB_debug_output
 * - GL_ARB_get_program_binary
 * - GL_ARB_robustness
 * - GL_ARB_separate_shader_objects
 * - GL_ARB_shader_precision
 * - GL_ARB_shader_stencil_export
 * - GL_ARB_vertex_attrib_64bit
 * - GL_ARB_viewport_array  
 *
 * ATI
 * - GL_ATIX_point_sprites
 * - GL_ATIX_texture_env_combine3
 * - GL_ATIX_texture_env_route
 * - GL_ATIX_vertex_shader_output_point_size
 * - GL_ATI_draw_buffers
 * - GL_ATI_element_array
 * - GL_ATI_envmap_bumpmap
 * - GL_ATI_fragment_shader
 * - GL_ATI_map_object_buffer
 * - GL_ATI_meminfo
 * - GL_ATI_pn_triangles
 * - GL_ATI_separate_stencil
 * - GL_ATI_shader_texture_lod
 * - GL_ATI_text_fragment_shader
 * - GL_ATI_texture_compression_3dc
 * - GL_ATI_texture_env_combine3
 * - GL_ATI_texture_float
 * - GL_ATI_texture_mirror_once
 * - GL_ATI_vertex_array_object
 * - GL_ATI_vertex_attrib_array_object
 * - GL_ATI_vertex_streams
 *
 * EXT
 * - GL_EXT_422_pixels
 * - GL_EXT_Cg_shader
 * - GL_EXT_abgr
 * - GL_EXT_bgra
 * - GL_EXT_bindable_uniform
 * - GL_EXT_blend_color
 * - GL_EXT_blend_equation_separate
 * - GL_EXT_blend_func_separate
 * - GL_EXT_blend_logic_op
 * - GL_EXT_blend_minmax
 * - GL_EXT_blend_subtract
 * - GL_EXT_clip_volume_hint
 * - GL_EXT_cmyka
 * - GL_EXT_color_subtable
 * - GL_EXT_compiled_vertex_array
 * - GL_EXT_convolution
 * - GL_EXT_coordinate_frame
 * - GL_EXT_copy_texture
 * - GL_EXT_cull_vertex
 * - GL_EXT_depth_bounds_test
 * - GL_EXT_direct_state_access
 * - GL_EXT_draw_buffers2
 * - GL_EXT_draw_instanced
 * - GL_EXT_draw_range_elements
 * - GL_EXT_fog_coord
 * - GL_EXT_fragment_lighting
 * - GL_EXT_framebuffer_blit
 * - GL_EXT_framebuffer_multisample
 * - GL_EXT_framebuffer_object
 * - GL_EXT_framebuffer_sRGB
 * - GL_EXT_geometry_shader4
 * - GL_EXT_gpu_program_parameters
 * - GL_EXT_gpu_shader4
 * - GL_EXT_histogram
 * - GL_EXT_index_array_formats
 * - GL_EXT_index_func
 * - GL_EXT_index_material
 * - GL_EXT_index_texture
 * - GL_EXT_light_texture
 * - GL_EXT_misc_attribute
 * - GL_EXT_multi_draw_arrays
 * - GL_EXT_multisample
 * - GL_EXT_packed_depth_stencil
 * - GL_EXT_packed_float
 * - GL_EXT_packed_pixels
 * - GL_EXT_paletted_texture
 * - GL_EXT_pixel_buffer_object
 * - GL_EXT_pixel_transform
 * - GL_EXT_pixel_transform_color_table
 * - GL_EXT_point_parameters
 * - GL_EXT_polygon_offset
 * - GL_EXT_provoking_vertex
 * - GL_EXT_rescale_normal
 * - GL_EXT_separate_shader_objects
 * - GL_EXT_scene_marker
 * - GL_EXT_secondary_color
 * - GL_EXT_separate_specular_color
 * - GL_EXT_shadow_funcs
 * - GL_EXT_shared_texture_palette
 * - GL_EXT_stencil_clear_tag
 * - GL_EXT_stencil_two_side
 * - GL_EXT_stencil_wrap
 * - GL_EXT_subtexture
 * - GL_EXT_texture
 * - GL_EXT_texture3D
 * - GL_EXT_texture_array
 * - GL_EXT_texture_buffer_object
 * - GL_EXT_texture_compression_dxt1
 * - GL_EXT_texture_compression_latc
 * - GL_EXT_texture_compression_rgtc
 * - GL_EXT_texture_compression_s3tc
 * - GL_EXT_texture_cube_map
 * - GL_EXT_texture_edge_clamp
 * - GL_EXT_texture_env
 * - GL_EXT_texture_env_add
 * - GL_EXT_texture_env_combine
 * - GL_EXT_texture_env_dot3
 * - GL_EXT_texture_filter_anisotropic
 * - GL_EXT_texture_integer
 * - GL_EXT_texture_lod_bias
 * - GL_EXT_texture_mirror_clamp
 * - GL_EXT_texture_object
 * - GL_EXT_texture_perturb_normal
 * - GL_EXT_texture_rectangle
 * - GL_EXT_texture_snorm
 * - GL_EXT_texture_sRGB
 * - GL_EXT_texture_shared_exponent
 * - GL_EXT_texture_swizzle
 * - GL_EXT_timer_query
 * - GL_EXT_transform_feedback
 * - GL_EXT_vertex_array
 * - GL_EXT_vertex_array_bgra
 * - GL_EXT_vertex_shader
 * - GL_EXT_vertex_weighting
 * - GL_EXT_shader_image_load_store
 * - GL_EXT_vertex_attrib_64bit
 * - GL_EXT_texture_sRGB_decode  
 *
 * GRemedy
 * - GL_GREMEDY_frame_terminator
 * - GL_GREMEDY_string_marker
 *
 * HP
 * - GL_HP_convolution_border_modes
 * - GL_HP_image_transform
 * - GL_HP_occlusion_test
 * - GL_HP_texture_lighting
 *
 * IBM
 * - GL_IBM_cull_vertex
 * - GL_IBM_multimode_draw_arrays
 * - GL_IBM_rasterpos_clip
 * - GL_IBM_static_data
 * - GL_IBM_texture_mirrored_repeat
 * - GL_IBM_vertex_array_lists
 *
 * INGR
 * - GL_INGR_color_clamp
 * - GL_INGR_interlace_read
 *
 * Intel
 * - GL_INTEL_parallel_arrays
 * - GL_INTEL_texture_scissor
 *
 * KTX
 * - GL_KTX_buffer_region
 *
 * MESA
 * - GL_MESAX_texture_stack
 * - GL_MESA_pack_invert
 * - GL_MESA_resize_buffers
 * - GL_MESA_window_pos
 * - GL_MESA_ycbcr_texture
 *
 * NVidia
 * - GL_NV_blend_square
 * - GL_NV_conditional_render
 * - GL_NV_copy_depth_to_color
 * - GL_NV_copy_image
 * - GL_NV_depth_buffer_float
 * - GL_NV_depth_clamp
 * - GL_NV_depth_range_unclamped
 * - GL_NV_evaluators
 * - GL_NV_explicit_multisample
 * - GL_NV_fence
 * - GL_NV_float_buffer
 * - GL_NV_fog_distance
 * - GL_NV_fragment_program
 * - GL_NV_fragment_program2
 * - GL_NV_fragment_program4
 * - GL_NV_fragment_program_option
 * - GL_NV_framebuffer_multisample_coverage
 * - GL_NV_geometry_program4
 * - GL_NV_geometry_shader4
 * - GL_NV_gpu_program4
 * - GL_NV_half_float
 * - GL_NV_light_max_exponent
 * - GL_NV_multisample_filter_hint
 * - GL_NV_occlusion_query
 * - GL_NV_packed_depth_stencil
 * - GL_NV_parameter_buffer_object
 * - GL_NV_parameter_buffer_object2
 * - GL_NV_pixel_data_range
 * - GL_NV_point_sprite
 * - GL_NV_present_video
 * - GL_NV_primitive_restart
 * - GL_NV_register_combiners
 * - GL_NV_register_combiners2
 * - GL_NV_shader_buffer_load
 * - GL_NV_texgen_emboss
 * - GL_NV_texgen_reflection
 * - GL_NV_texture_barrier
 * - GL_NV_texture_compression_vtc
 * - GL_NV_texture_env_combine4
 * - GL_NV_texture_expand_normal
 * - GL_NV_texture_rectangle
 * - GL_NV_texture_shader
 * - GL_NV_texture_shader2
 * - GL_NV_texture_shader3
 * - GL_NV_transform_feedback
 * - GL_NV_transform_feedback2
 * - GL_NV_vertex_array_range
 * - GL_NV_vertex_array_range2
 * - GL_NV_vertex_buffer_unified_memory
 * - GL_NV_vertex_program
 * - GL_NV_vertex_program1_1
 * - GL_NV_vertex_program2
 * - GL_NV_vertex_program2_option
 * - GL_NV_vertex_program3
 * - GL_NV_vertex_program4
 * - GL_NV_gpu_program5
 * - GL_NV_gpu_program_fp64
 * - GL_NV_gpu_shader5
 * - GL_NV_tessellation_program5
 * - GL_NV_vertex_attrib_integer_64bit
 * - GL_NV_multisample_coverage
 * - GL_NV_vdpau_interop
 * - GL_NVX_gpu_memory_info  
 *
 * OES
 * - GL_OES_byte_coordinates
 * - GL_OES_compressed_paletted_texture
 * - GL_OES_read_format
 * - GL_OES_single_precision
 *
 * OML
 * - GL_OML_interlace
 * - GL_OML_resample
 * - GL_OML_subsample
 *
 * PGI
 * - GL_PGI_misc_hints 
 * - GL_PGI_vertex_hints
 *
 * Rend
 * - GL_REND_screen_coordinates
 *
 * S3
 * - GL_S3_s3tc
 *
 * SGI
 * - GL_SGIS_color_range
 * - GL_SGIS_detail_texture
 * - GL_SGIS_fog_function
 * - GL_SGIS_generate_mipmap
 * - GL_SGIS_multisample
 * - GL_SGIS_pixel_texture
 * - GL_SGIS_point_line_texgen
 * - GL_SGIS_sharpen_texture
 * - GL_SGIS_texture4D
 * - GL_SGIS_texture_border_clamp
 * - GL_SGIS_texture_edge_clamp
 * - GL_SGIS_texture_filter4
 * - GL_SGIS_texture_lod
 * - GL_SGIS_texture_select
 * - GL_SGIX_async
 * - GL_SGIX_async_histogram
 * - GL_SGIX_async_pixel
 * - GL_SGIX_blend_alpha_minmax
 * - GL_SGIX_clipmap
 * - GL_SGIX_convolution_accuracy
 * - GL_SGIX_depth_texture
 * - GL_SGIX_flush_raster
 * - GL_SGIX_fog_offset
 * - GL_SGIX_fog_texture
 * - GL_SGIX_fragment_specular_lighting
 * - GL_SGIX_framezoom
 * - GL_SGIX_interlace
 * - GL_SGIX_ir_instrument1
 * - GL_SGIX_list_priority
 * - GL_SGIX_pixel_texture
 * - GL_SGIX_pixel_texture_bits
 * - GL_SGIX_reference_plane
 * - GL_SGIX_resample
 * - GL_SGIX_shadow
 * - GL_SGIX_shadow_ambient
 * - GL_SGIX_sprite
 * - GL_SGIX_tag_sample_buffer
 * - GL_SGIX_texture_add_env
 * - GL_SGIX_texture_coordinate_clamp
 * - GL_SGIX_texture_lod_bias
 * - GL_SGIX_texture_multi_buffer
 * - GL_SGIX_texture_range
 * - GL_SGIX_texture_scale_bias
 * - GL_SGIX_vertex_preclip
 * - GL_SGIX_vertex_preclip_hint
 * - GL_SGIX_ycrcb
 * - GL_SGI_color_matrix
 * - GL_SGI_color_table
 * - GL_SGI_texture_color_table
 *
 * Sun
 * - GL_SUNX_constant_data
 * - GL_SUN_convolution_border_modes
 * - GL_SUN_global_alpha
 * - GL_SUN_mesh_array
 * - GL_SUN_read_video_pixels
 * - GL_SUN_slice_accum
 * - GL_SUN_triangle_list
 * - GL_SUN_vertex
 *
 * Win
 * - GL_WIN_phong_shading
 * - GL_WIN_specular_fog
 * - GL_WIN_swap_hint
 *
 * WGL
 * - WGL_3DFX_multisample
 * - WGL_3DL_stereo_control
 * - WGL_AMD_gpu_association
 * - WGL_ARB_buffer_region
 * - WGL_ARB_create_context
 * - WGL_ARB_create_context_profile
 * - WGL_ARB_extensions_string
 * - WGL_ARB_framebuffer_sRGB
 * - WGL_ARB_make_current_read
 * - WGL_ARB_multisample
 * - WGL_ARB_pbuffer
 * - WGL_ARB_pixel_format
 * - WGL_ARB_pixel_format_float
 * - WGL_ARB_render_texture
 * - WGL_ATI_pixel_format_float
 * - WGL_ATI_render_texture_rectangle
 * - WGL_EXT_depth_float
 * - WGL_EXT_display_color_table
 * - WGL_EXT_extensions_string
 * - WGL_EXT_framebuffer_sRGB
 * - WGL_EXT_make_current_read
 * - WGL_EXT_multisample
 * - WGL_EXT_pbuffer
 * - WGL_EXT_pixel_format
 * - WGL_EXT_pixel_format_packed_float
 * - WGL_EXT_swap_control
 * - WGL_I3D_digital_video_control
 * - WGL_I3D_gamma
 * - WGL_I3D_genlock
 * - WGL_I3D_image_buffer
 * - WGL_I3D_swap_frame_lock
 * - WGL_I3D_swap_frame_usage
 * - WGL_NV_copy_image
 * - WGL_NV_float_buffer
 * - WGL_NV_gpu_affinity
 * - WGL_NV_present_video
 * - WGL_NV_render_depth_texture
 * - WGL_NV_render_texture_rectangle
 * - WGL_NV_swap_group
 * - WGL_NV_vertex_array_range
 * - WGL_NV_video_output
 * - WGL_OML_sync_control
 * - WGL_NV_multisample_coverage 
 * - WGL_ARB_create_context_robustness
 * - WGL_EXT_create_context_es2_profile 
 *
 * GLX
 * - GLX_VERSION_1_2
 * - GLX_VERSION_1_3
 * - GLX_VERSION_1_4
 * - GLX_3DFX_multisample
 * - GLX_ARB_create_context
 * - GLX_ARB_create_context_profile
 * - GLX_ARB_fbconfig_float
 * - GLX_ARB_framebuffer_sRGB
 * - GLX_ARB_get_proc_address
 * - GLX_ARB_multisample
 * - GLX_ARB_vertex_buffer_object 
 * - GLX_ATI_pixel_format_float
 * - GLX_ATI_render_texture
 * - GLX_EXT_fbconfig_packed_float
 * - GLX_EXT_framebuffer_sRGB
 * - GLX_EXT_import_context
 * - GLX_EXT_scene_marker
 * - GLX_EXT_texture_from_pixmap
 * - GLX_EXT_visual_info
 * - GLX_EXT_visual_rating
 * - GLX_EXT_swap_control 
 * - GLX_INTEL_swap_event 
 * - GLX_MESA_agp_offset
 * - GLX_MESA_copy_sub_buffer
 * - GLX_MESA_pixmap_colormap
 * - GLX_MESA_release_buffers
 * - GLX_MESA_set_3dfx_mode
 * - GLX_NV_copy_image
 * - GLX_NV_float_buffer
 * - GLX_NV_present_video
 * - GLX_NV_swap_group
 * - GLX_NV_vertex_array_range
 * - GLX_NV_video_output
 * - GLX_OML_swap_method
 * - GLX_OML_sync_control
 * - GLX_SGIS_blended_overlay
 * - GLX_SGIS_color_range
 * - GLX_SGIS_multisample
 * - GLX_SGIS_shared_multisample
 * - GLX_SGIX_fbconfig
 * - GLX_SGIX_hyperpipe
 * - GLX_SGIX_pbuffer
 * - GLX_SGIX_swap_barrier
 * - GLX_SGIX_swap_group
 * - GLX_SGIX_video_resize
 * - GLX_SGIX_visual_select_group
 * - GLX_SGI_cushion
 * - GLX_SGI_make_current_read
 * - GLX_SGI_swap_control
 * - GLX_SGI_video_sync
 * - GLX_SUN_get_transparent_index
 * - GLX_SUN_video_resize
 * - GLX_AMD_gpu_association
 * - GLX_NV_multisample_coverage 
 * - GLX_ARB_create_context_robustness
 * - GLX_EXT_create_context_es2_profile  
 *
 */

class INVENTORGL_API SoGLExtension {

public:
  /**
   *  Returns true if the extension is available.
   */
  static SbBool isAvailable( const char* extension );

  /**
   *  Returns true if the extension is available.
   */
  static SbBool isAvailable( const SbString& extension );

  /**
   *  Disable a specific extension in software.
   *  The given extension will be disabled for any subsequent calls
   *  to isAvailable and for any existing contexts.
   *
   *  A list of extensions can be disabled using the environment 
   *  variable OIV_DISABLED_GL_EXTENSION_LIST ( see SoPreferences ).
   */
  static void disableExtension(const SbString& extension);

SoEXTENDER public:
  /**
   * Methods to quickly figure out if an OpenGL extension is
   * available at run-time.
   * This is the slow routine-- convert from a string to an integer.
   * The integer should be saved to do quick lookups:
   */
  static int          getExtID(const char *str);

  /** This routine is pretty quick. */
  static SbBool       extSupported(int contextID, int ext);

SoINTERNAL public:
  /**
   *  Inits SoGLExtension. @BR
   *  This is normally done automatically as part of initializing Open Inventor.
   */
  static SbBool initClass();

  /**
   *  Exits SoGLExtension.
   */
  static void exitClass();

  /**
   * Returns true if the class has been initialized.
   */
  static SbBool isInitialized();

#if defined(_WIN32)
  static PFNWGLCHOOSEPIXELFORMATPROC    m_wglChoosePixelFormat;
  static PFNWGLSETPIXELFORMATPROC       m_wglSetPixelFormat;
  static PFNWGLDESCRIBEPIXELFORMATPROC  m_wglDescribePixelFormat;
  static PFNWGLSWAPBUFFERSPROC          m_wglSwapBuffers;
#endif // _WIN32

  /**
   * Return TRUE if 32-bits floating point textures are expected 
   * to be fast (ie: not software when enabling linear interpolation or 
   * blending)
   */
  static SbBool hasFullFloat32TextureSupport();

private:
  /** Create and activate a fake context*/
  static SoGLWindow* createAndEnableFakeContext();

  static std::list<char*> s_disabledList;
  static SbBool           s_initialized;

  /**Protect extension list */
  static SbThreadSpinlock s_extensionListMutex;
  static SbPList* s_extensionList;

};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif // _SO_GL_EXTENSION_H_
