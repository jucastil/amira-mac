/*
Copyright 1999-2013 Visualization Sciences Group, SAS
Copyright 1995-2013, ZIB Berlin
ALL RIGHTS RESERVED.

amira(R) is a registered trademark of ZIB.

amira(R) is being jointly developed by Zuse Institute Berlin and
Visualization Sciences Group, SAS.
Avizo® is a registered trademark of Visualization Sciences Group, SAS
HardCopy, MeshViz, VolumeViz, TerrainViz are marks of Visualization
Sciences Group, SAS 
Visualization Sciences Group, SAS is a source licensee of OpenGL®, Open Inventor® 
from Silicon Graphics, Inc. OpenGL® and Open Inventor® are 
registered trademark of Silicon Graphics, Inc. All other products and 
company names are trademarks or registered trademarks of 
their respective companies. 

FEI Visualization Sciences Group accepts no liability to any 
party for loss or damage caused by errors or omissions or by 
statements of any kind in this publication, whether such errors 
result from accident, negligence or any other cause. FEI Visualization
Sciences Group assumes  no liability for incidental or consequential
damages arising from the use of information in this publication.
FEI Visualization Sciences Group provides no 
warranties regarding the information contained in this 
publication, whether expressed, implied, or statutory, including 
implied warranties of merchantability or fitness for a 
particular purpose. 

FEI Visualization Sciences Group also does not assume any liability
for links from this publication to publications from other companies,
organizations or individuals. FEI Visualization Sciences Group does not
imply endorsement of any specific  company, organization or individual
through offering links to this content.
All information provided within this publication 
is subject to change at any time and is provided for 
informational purposes only by FEI Visualization Sciences Group.
Copyright 1994-2012 by Visualization Sciences Group, SAS Merignac, France.

*/

/// @addtogroup hxcore hxcore
/// @{
#ifndef _HX_GL_FUNCS
#define _HX_GL_FUNCS

#include <hxcore/hxgl.h>

#include <hxcore/HxAmiraWinDLLApi.h>
#include <hxcore/HxDSO.h>


#ifdef HX_OS_WIN
    #include <windows.h>
    DECLARE_HANDLE(HPBUFFERARB);
#endif

////////////////////////////////////////
// ARB_texture_rectangle
////////////////////////////////////////
#define GL_TEXTURE_RECTANGLE_ARB            0x84F5
#define GL_TEXTURE_BINDING_RECTANGLE_ARB    0x84F6
#define GL_PROXY_TEXTURE_RECTANGLE_ARB      0x84F7
#define GL_MAX_RECTANGLE_TEXTURE_SIZE_ARB   0x84F8


////////////////////////////////////////
// WGL_NV_render_texture_rectangle
////////////////////////////////////////
	
#define WGL_BIND_TO_TEXTURE_RECTANGLE_RGB_NV           0x20A0
#define WGL_BIND_TO_TEXTURE_RECTANGLE_RGBA_NV          0x20A1
#define WGL_TEXTURE_RECTANGLE_NV                       0x20A2

	
////////////////////////////////////////
// GL_NV_float_buffer
// WGL_NV_float_buffer
////////////////////////////////////////
#define GL_FLOAT_R_NV                                      0x8880
#define GL_FLOAT_RG_NV                                     0x8881
#define GL_FLOAT_RGB_NV                                    0x8882
#define GL_FLOAT_RGBA_NV                                   0x8883
#define GL_FLOAT_R16_NV                                    0x8884
#define GL_FLOAT_R32_NV                                    0x8885
#define GL_FLOAT_RG16_NV                                   0x8886
#define GL_FLOAT_RG32_NV                                   0x8887
#define GL_FLOAT_RGB16_NV                                  0x8888
#define GL_FLOAT_RGB32_NV                                  0x8889
#define GL_FLOAT_RGBA16_NV                                 0x888A
#define GL_FLOAT_RGBA32_NV                                 0x888B

#define GL_TEXTURE_FLOAT_COMPONENTS_NV                     0x888C

#define GL_FLOAT_CLEAR_COLOR_VALUE_NV                      0x888D
#define GL_FLOAT_RGBA_MODE_NV                              0x888E

#define WGL_FLOAT_COMPONENTS_NV                         0x20B0
#define WGL_BIND_TO_TEXTURE_RECTANGLE_FLOAT_R_NV        0x20B1
#define WGL_BIND_TO_TEXTURE_RECTANGLE_FLOAT_RG_NV       0x20B2
#define WGL_BIND_TO_TEXTURE_RECTANGLE_FLOAT_RGB_NV      0x20B3
#define WGL_BIND_TO_TEXTURE_RECTANGLE_FLOAT_RGBA_NV     0x20B4

#define WGL_TEXTURE_FLOAT_R_NV                          0x20B5
#define WGL_TEXTURE_FLOAT_RG_NV                         0x20B6
#define WGL_TEXTURE_FLOAT_RGB_NV                        0x20B7
#define WGL_TEXTURE_FLOAT_RGBA_NV                       0x20B8


////////////////////////////////////////
// ARB_draw_buffers
////////////////////////////////////////
#define MAX_DRAW_BUFFERS_ARB                    0x8824
#define DRAW_BUFFER0_ARB                        0x8825
#define DRAW_BUFFER1_ARB                        0x8826
#define DRAW_BUFFER2_ARB                        0x8827
#define DRAW_BUFFER3_ARB                        0x8828
#define DRAW_BUFFER4_ARB                        0x8829
#define DRAW_BUFFER5_ARB                        0x882A
#define DRAW_BUFFER6_ARB                        0x882B
#define DRAW_BUFFER7_ARB                        0x882C
#define DRAW_BUFFER8_ARB                        0x882D
#define DRAW_BUFFER9_ARB                        0x882E
#define DRAW_BUFFER10_ARB                       0x882F
#define DRAW_BUFFER11_ARB                       0x8830
#define DRAW_BUFFER12_ARB                       0x8831
#define DRAW_BUFFER13_ARB                       0x8832
#define DRAW_BUFFER14_ARB                       0x8833
#define DRAW_BUFFER15_ARB                       0x8834

////////////////////////////////////////
// ARB_point_sprites.
////////////////////////////////////////
#define GL_POINT_SPRITE_ARB  0x8861
#define GL_COORD_REPLACE_ARB 0x8862


////////////////////////////////////////
// NV_float_buffer
////////////////////////////////////////
#define WGL_FLOAT_COMPONENTS_NV                         0x20B0
#define WGL_BIND_TO_TEXTURE_RECTANGLE_FLOAT_R_NV        0x20B1
#define WGL_BIND_TO_TEXTURE_RECTANGLE_FLOAT_RG_NV       0x20B2
#define WGL_BIND_TO_TEXTURE_RECTANGLE_FLOAT_RGB_NV      0x20B3
#define WGL_BIND_TO_TEXTURE_RECTANGLE_FLOAT_RGBA_NV     0x20B4



////////////////////////////////////////
// NV shader
////////////////////////////////////////

#define GL_FRAGMENT_PROGRAM_NV            0x8870
#define GL_VERTEX_PROGRAM_NV              0x8620
#define GL_INVERSE_TRANSPOSE_NV           0x862D
#define GL_IDENTITY_NV                    0x862A
#define GL_MODELVIEW_PROJECTION_NV        0x8629
#define GL_PROGRAM_ERROR_POSITION_NV      0x864B
#define GL_PROGRAM_ERROR_STRING_NV        0x8874

////////////////////////////////////////
// ATI shader
////////////////////////////////////////

#define GL_FRAGMENT_SHADER_ATI            0x8920
#define GL_REG_0_ATI                      0x8921
#define GL_REG_1_ATI                      0x8922
#define GL_REG_2_ATI                      0x8923
#define GL_SWIZZLE_STR_ATI                0x8976
#define GL_SWIZZLE_STQ_ATI                0x8977
#define GL_MOV_ATI                        0x8961
#define GL_MUL_ATI                        0x8964
#define GL_ADD_ATI                        0x8963
#define GL_CON_0_ATI                      0x8941

////////////////////////////////////////
// ARB_multitexture
////////////////////////////////////////

#define GL_ACTIVE_TEXTURE                 0x84E0
#define GL_CLIENT_ACTIVE_TEXTURE          0x84E1
#define GL_MAX_TEXTURE_UNITS              0x84E2
#define GL_TEXTURE0                       0x84C0
#define GL_TEXTURE1                       0x84C1
#define GL_TEXTURE2                       0x84C2
#define GL_TEXTURE3                       0x84C3
#define GL_TEXTURE4                       0x84C4
#define GL_TEXTURE5                       0x84C5
#define GL_TEXTURE6                       0x84C6
#define GL_TEXTURE7                       0x84C7
#define GL_TEXTURE8                       0x84C8
#define GL_TEXTURE9                       0x84C9
#define GL_TEXTURE10                      0x84CA
#define GL_TEXTURE11                      0x84CB
#define GL_TEXTURE12                      0x84CC
#define GL_TEXTURE13                      0x84CD
#define GL_TEXTURE14                      0x84CE
#define GL_TEXTURE15                      0x84CF
#define GL_TEXTURE16                      0x84D0
#define GL_TEXTURE17                      0x84D1
#define GL_TEXTURE18                      0x84D2
#define GL_TEXTURE19                      0x84D3
#define GL_TEXTURE20                      0x84D4
#define GL_TEXTURE21                      0x84D5
#define GL_TEXTURE22                      0x84D6
#define GL_TEXTURE23                      0x84D7
#define GL_TEXTURE24                      0x84D8
#define GL_TEXTURE25                      0x84D9
#define GL_TEXTURE26                      0x84DA
#define GL_TEXTURE27                      0x84DB
#define GL_TEXTURE28                      0x84DC
#define GL_TEXTURE29                      0x84DD
#define GL_TEXTURE30                      0x84DE
#define GL_TEXTURE31                      0x84DF

////////////////////////////////////////
// ARB shader
////////////////////////////////////////

#define GL_PROGRAM_FORMAT_ASCII_ARB       0x8875
#define GL_PROGRAM_ERROR_POSITION_ARB     0x864B
#define GL_PROGRAM_ERROR_STRING_ARB       0x8874

////////////////////////////////////////
// ARB_vertex_program
////////////////////////////////////////

#define GL_VERTEX_PROGRAM_ARB                              0x8620
#define GL_VERTEX_PROGRAM_POINT_SIZE_ARB                   0x8642
#define GL_VERTEX_PROGRAM_TWO_SIDE_ARB                     0x8643
#define GL_COLOR_SUM_ARB                                   0x8458
#define GL_VERTEX_ATTRIB_ARRAY_ENABLED_ARB                 0x8622
#define GL_VERTEX_ATTRIB_ARRAY_SIZE_ARB                    0x8623
#define GL_VERTEX_ATTRIB_ARRAY_STRIDE_ARB                  0x8624
#define GL_VERTEX_ATTRIB_ARRAY_TYPE_ARB                    0x8625
#define GL_VERTEX_ATTRIB_ARRAY_NORMALIZED_ARB              0x886A
#define GL_CURRENT_VERTEX_ATTRIB_ARB                       0x8626
#define GL_VERTEX_ATTRIB_ARRAY_POINTER_ARB                 0x8645
#define GL_PROGRAM_LENGTH_ARB                              0x8627
#define GL_PROGRAM_FORMAT_ARB                              0x8876
#define GL_PROGRAM_BINDING_ARB                             0x8677
#define GL_PROGRAM_INSTRUCTIONS_ARB                        0x88A0
#define GL_MAX_PROGRAM_INSTRUCTIONS_ARB                    0x88A1
#define GL_PROGRAM_NATIVE_INSTRUCTIONS_ARB                 0x88A2
#define GL_MAX_PROGRAM_NATIVE_INSTRUCTIONS_ARB             0x88A3
#define GL_PROGRAM_TEMPORARIES_ARB                         0x88A4
#define GL_MAX_PROGRAM_TEMPORARIES_ARB                     0x88A5
#define GL_PROGRAM_NATIVE_TEMPORARIES_ARB                  0x88A6
#define GL_MAX_PROGRAM_NATIVE_TEMPORARIES_ARB              0x88A7
#define GL_PROGRAM_PARAMETERS_ARB                          0x88A8
#define GL_MAX_PROGRAM_PARAMETERS_ARB                      0x88A9
#define GL_PROGRAM_NATIVE_PARAMETERS_ARB                   0x88AA
#define GL_MAX_PROGRAM_NATIVE_PARAMETERS_ARB               0x88AB
#define GL_PROGRAM_ATTRIBS_ARB                             0x88AC
#define GL_MAX_PROGRAM_ATTRIBS_ARB                         0x88AD
#define GL_PROGRAM_NATIVE_ATTRIBS_ARB                      0x88AE
#define GL_MAX_PROGRAM_NATIVE_ATTRIBS_ARB                  0x88AF
#define GL_PROGRAM_ADDRESS_REGISTERS_ARB                   0x88B0
#define GL_MAX_PROGRAM_ADDRESS_REGISTERS_ARB               0x88B1
#define GL_PROGRAM_NATIVE_ADDRESS_REGISTERS_ARB            0x88B2
#define GL_MAX_PROGRAM_NATIVE_ADDRESS_REGISTERS_ARB        0x88B3
#define GL_MAX_PROGRAM_LOCAL_PARAMETERS_ARB                0x88B4
#define GL_MAX_PROGRAM_ENV_PARAMETERS_ARB                  0x88B5
#define GL_PROGRAM_UNDER_NATIVE_LIMITS_ARB                 0x88B6
#define GL_PROGRAM_STRING_ARB                              0x8628
#define GL_CURRENT_MATRIX_ARB                              0x8641
#define GL_TRANSPOSE_CURRENT_MATRIX_ARB                    0x88B7
#define GL_CURRENT_MATRIX_STACK_DEPTH_ARB                  0x8640
#define GL_MAX_VERTEX_ATTRIBS_ARB                          0x8869
#define GL_MAX_PROGRAM_MATRICES_ARB                        0x862F
#define GL_MAX_PROGRAM_MATRIX_STACK_DEPTH_ARB              0x862E
#define GL_MATRIX0_ARB                                     0x88C0
#define GL_MATRIX1_ARB                                     0x88C1
#define GL_MATRIX2_ARB                                     0x88C2
#define GL_MATRIX3_ARB                                     0x88C3
#define GL_MATRIX4_ARB                                     0x88C4
#define GL_MATRIX5_ARB                                     0x88C5
#define GL_MATRIX6_ARB                                     0x88C6
#define GL_MATRIX7_ARB                                     0x88C7
#define GL_MATRIX8_ARB                                     0x88C8
#define GL_MATRIX9_ARB                                     0x88C9
#define GL_MATRIX10_ARB                                    0x88CA
#define GL_MATRIX11_ARB                                    0x88CB
#define GL_MATRIX12_ARB                                    0x88CC
#define GL_MATRIX13_ARB                                    0x88CD
#define GL_MATRIX14_ARB                                    0x88CE
#define GL_MATRIX15_ARB                                    0x88CF
#define GL_MATRIX16_ARB                                    0x88D0
#define GL_MATRIX17_ARB                                    0x88D1
#define GL_MATRIX18_ARB                                    0x88D2
#define GL_MATRIX19_ARB                                    0x88D3
#define GL_MATRIX20_ARB                                    0x88D4
#define GL_MATRIX21_ARB                                    0x88D5
#define GL_MATRIX22_ARB                                    0x88D6
#define GL_MATRIX23_ARB                                    0x88D7
#define GL_MATRIX24_ARB                                    0x88D8
#define GL_MATRIX25_ARB                                    0x88D9
#define GL_MATRIX26_ARB                                    0x88DA
#define GL_MATRIX27_ARB                                    0x88DB
#define GL_MATRIX28_ARB                                    0x88DC
#define GL_MATRIX29_ARB                                    0x88DD
#define GL_MATRIX30_ARB                                    0x88DE
#define GL_MATRIX31_ARB                                    0x88DF

///////////////////////////////////////
// Multitexture
//////////////////////////////////////
#define GL_COMBINE                        0x8570
#define GL_COMBINE_RGB                    0x8571
#define GL_COMBINE_ALPHA                  0x8572
#define GL_SOURCE0_RGB                    0x8580
#define GL_SOURCE1_RGB                    0x8581
#define GL_SOURCE2_RGB                    0x8582
#define GL_SOURCE0_ALPHA                  0x8588
#define GL_SOURCE1_ALPHA                  0x8589
#define GL_SOURCE2_ALPHA                  0x858A
#define GL_OPERAND0_RGB                   0x8590
#define GL_OPERAND1_RGB                   0x8591
#define GL_OPERAND2_RGB                   0x8592
#define GL_OPERAND0_ALPHA                 0x8598
#define GL_OPERAND1_ALPHA                 0x8599
#define GL_OPERAND2_ALPHA                 0x859A
#define GL_PREVIOUS                       0x8578
#define GL_DOT3_RGB                       0x86AE
#define GL_DOT3_RGBA                      0x86AF
#ifndef GL_SRC0_RGB
#  define GL_SRC0_RGB                     GL_SOURCE0_RGB
#endif
#ifndef GL_SRC1_RGB
#  define GL_SRC1_RGB                     GL_SOURCE1_RGB
#endif
#ifndef GL_SRC2_RGB
#  define GL_SRC2_RGB                     GL_SOURCE2_RGB
#endif
#ifndef GL_SRC0_ALPHA
#  define GL_SRC0_ALPHA                   GL_SOURCE0_ALPHA
#endif
#ifndef GL_SRC1_ALPHA
#  define GL_SRC1_ALPHA                   GL_SOURCE1_ALPHA
#endif
#ifndef GL_SRC2_ALPHA
#  define GL_SRC2_ALPHA                   GL_SOURCE2_ALPHA
#endif


////////////////////////////////////////
// ARB_fragment_program
////////////////////////////////////////

#define GL_FRAGMENT_PROGRAM_ARB                            0x8804
#define GL_PROGRAM_ALU_INSTRUCTIONS_ARB                    0x8805
#define GL_PROGRAM_TEX_INSTRUCTIONS_ARB                    0x8806
#define GL_PROGRAM_TEX_INDIRECTIONS_ARB                    0x8807
#define GL_PROGRAM_NATIVE_ALU_INSTRUCTIONS_ARB             0x8808
#define GL_PROGRAM_NATIVE_TEX_INSTRUCTIONS_ARB             0x8809
#define GL_PROGRAM_NATIVE_TEX_INDIRECTIONS_ARB             0x880A
#define GL_MAX_PROGRAM_ALU_INSTRUCTIONS_ARB                0x880B
#define GL_MAX_PROGRAM_TEX_INSTRUCTIONS_ARB                0x880C
#define GL_MAX_PROGRAM_TEX_INDIRECTIONS_ARB                0x880D
#define GL_MAX_PROGRAM_NATIVE_ALU_INSTRUCTIONS_ARB         0x880E
#define GL_MAX_PROGRAM_NATIVE_TEX_INSTRUCTIONS_ARB         0x880F
#define GL_MAX_PROGRAM_NATIVE_TEX_INDIRECTIONS_ARB         0x8810

////////////////////////////////////////
// ARB_vertex_shader
////////////////////////////////////////

#define GL_VERTEX_SHADER_ARB                        0x8B31
#define GL_MAX_VERTEX_UNIFORM_COMPONENTS_ARB        0x8B4A
#define GL_MAX_VARYING_FLOATS_ARB                   0x8B4B
#define GL_MAX_VERTEX_ATTRIBS_ARB                   0x8869
#define GL_MAX_TEXTURE_IMAGE_UNITS_ARB              0x8872
#define GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS_ARB       0x8B4C
#define GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS_ARB     0x8B4D
#define GL_MAX_TEXTURE_COORDS_ARB                   0x8871
#define GL_VERTEX_PROGRAM_POINT_SIZE_ARB            0x8642
#define GL_VERTEX_PROGRAM_TWO_SIDE_ARB              0x8643
#define GL_OBJECT_ACTIVE_ATTRIBUTES_ARB             0x8B89
#define GL_OBJECT_ACTIVE_ATTRIBUTE_MAX_LENGTH_ARB   0x8B8A
#define GL_VERTEX_ATTRIB_ARRAY_ENABLED_ARB          0x8622
#define GL_VERTEX_ATTRIB_ARRAY_SIZE_ARB             0x8623
#define GL_VERTEX_ATTRIB_ARRAY_STRIDE_ARB           0x8624
#define GL_VERTEX_ATTRIB_ARRAY_TYPE_ARB             0x8625
#define GL_VERTEX_ATTRIB_ARRAY_NORMALIZED_ARB       0x886A
#define GL_CURRENT_VERTEX_ATTRIB_ARB                0x8626
#define GL_VERTEX_ATTRIB_ARRAY_POINTER_ARB          0x8645

////////////////////////////////////////
// ARB_fragment_shader
////////////////////////////////////////

#define GL_FRAGMENT_SHADER_ARB                      0x8B30
#define GL_MAX_FRAGMENT_UNIFORM_COMPONENTS_ARB      0x8B49

////////////////////////////////////////
// SGI color table
////////////////////////////////////////

#ifndef GL_COLOR_TABLE_SGI
#  define GL_COLOR_TABLE_SGI                        0x80D0
#endif
#ifndef GL_TEXTURE_COLOR_TABLE_SGI
#  define GL_TEXTURE_COLOR_TABLE_SGI                0x80BC
#endif
#ifndef GL_COLOR_INDEX8_EXT
#  define GL_COLOR_INDEX8_EXT                       0x80E5
#endif

////////////////////////////////////////
// ARB_texture_border_clamp
////////////////////////////////////////

#define GL_CLAMP_TO_BORDER_ARB                      0x812D

////////////////////////////////////////
// OpenGL 1.2
////////////////////////////////////////

#define GL_CLAMP_TO_EDGE                            0x812F

////////////////////////////////////////
// GL_EXT_blend_minmax
////////////////////////////////////////

#define GL_FUNC_ADD_EXT                             0x8006
#define GL_MAX_EXT                                  0x8008

////////////////////////////////////////
// GL_EXT_texture3D
////////////////////////////////////////

#ifndef GL_TEXTURE_BINDING_3D_EXT
#  define GL_TEXTURE_BINDING_3D_EXT               0x806A
#endif
#ifndef GL_TEXTURE_BINDING_3D
#  define GL_TEXTURE_BINDING_3D                   GL_TEXTURE_BINDING_3D_EXT
#endif
#ifndef GL_PACK_SKIP_IMAGES_EXT
#  define GL_PACK_SKIP_IMAGES_EXT                 0x806B
#endif
#ifndef GL_PACK_SKIP_IMAGES
#  define GL_PACK_SKIP_IMAGES                     GL_PACK_SKIP_IMAGES_EXT
#endif
#ifndef GL_PACK_IMAGE_HEIGHT_EXT
#  define GL_PACK_IMAGE_HEIGHT_EXT                0x806C
#endif
#ifndef GL_PACK_IMAGE_HEIGHT
#  define GL_PACK_IMAGE_HEIGHT                    GL_PACK_IMAGE_HEIGHT_EXT
#endif
#ifndef GL_UNPACK_SKIP_IMAGES_EXT
#  define GL_UNPACK_SKIP_IMAGES_EXT               0x806D
#endif
#ifndef GL_UNPACK_SKIP_IMAGES
#  define GL_UNPACK_SKIP_IMAGES                   GL_UNPACK_SKIP_IMAGES_EXT
#endif
#ifndef GL_UNPACK_IMAGE_HEIGHT_EXT
#  define GL_UNPACK_IMAGE_HEIGHT_EXT              0x806E
#endif
#ifndef GL_UNPACK_IMAGE_HEIGHT
#  define GL_UNPACK_IMAGE_HEIGHT                  GL_UNPACK_IMAGE_HEIGHT_EXT
#endif
#ifndef GL_TEXTURE_3D_EXT
#  define GL_TEXTURE_3D_EXT                       0x806F
#endif
#ifndef GL_TEXTURE_3D
#  define GL_TEXTURE_3D                           GL_TEXTURE_3D_EXT
#endif
#ifndef GL_PROXY_TEXTURE_3D_EXT
#  define GL_PROXY_TEXTURE_3D_EXT                 0x8070
#endif
#ifndef GL_PROXY_TEXTURE_3D
#  define GL_PROXY_TEXTURE_3D                     GL_PROXY_TEXTURE_3D_EXT
#endif
#ifndef GL_TEXTURE_DEPTH_EXT
#  define GL_TEXTURE_DEPTH_EXT                    0x8071
#endif
#ifndef GL_TEXTURE_DEPTH
#  define GL_TEXTURE_DEPTH                        GL_TEXTURE_DEPTH_EXT
#endif
#ifndef GL_TEXTURE_WRAP_R_EXT
#  define GL_TEXTURE_WRAP_R_EXT                   0x8072
#endif
#ifndef GL_TEXTURE_WRAP_R
#  define GL_TEXTURE_WRAP_R                       GL_TEXTURE_WRAP_R_EXT
#endif
#ifndef GL_MAX_3D_TEXTURE_SIZE_EXT
#  define GL_MAX_3D_TEXTURE_SIZE_EXT              0x8073
#endif
#ifndef GL_MAX_3D_TEXTURE_SIZE
#  define GL_MAX_3D_TEXTURE_SIZE                  GL_MAX_3D_TEXTURE_SIZE_EXT
#endif

////////////////////////////////////////
// windows pbuffer
////////////////////////////////////////

#define WGL_DRAW_TO_PBUFFER_ARB         0x202D
#define WGL_DRAW_TO_PBUFFER_ARB         0x202D
#define WGL_MAX_PBUFFER_PIXELS_ARB      0x202E
#define WGL_MAX_PBUFFER_WIDTH_ARB       0x202F
#define WGL_MAX_PBUFFER_HEIGHT_ARB      0x2030
#define WGL_PBUFFER_LARGEST_ARB         0x2033
#define WGL_PBUFFER_WIDTH_ARB           0x2034
#define WGL_PBUFFER_HEIGHT_ARB          0x2035
#define WGL_PBUFFER_LOST_ARB            0x2036

////////////////////////////////////////
// WGL_ARB_pixel_format
////////////////////////////////////////

#define WGL_NUMBER_PIXEL_FORMATS_ARB    0x2000
#define WGL_DRAW_TO_WINDOW_ARB          0x2001
#define WGL_DRAW_TO_BITMAP_ARB          0x2002
#define WGL_ACCELERATION_ARB            0x2003
#define WGL_NEED_PALETTE_ARB            0x2004
#define WGL_NEED_SYSTEM_PALETTE_ARB     0x2005
#define WGL_SWAP_LAYER_BUFFERS_ARB      0x2006
#define WGL_SWAP_METHOD_ARB             0x2007
#define WGL_NUMBER_OVERLAYS_ARB         0x2008
#define WGL_NUMBER_UNDERLAYS_ARB        0x2009
#define WGL_TRANSPARENT_ARB             0x200A
#define WGL_TRANSPARENT_RED_VALUE_ARB   0x2037
#define WGL_TRANSPARENT_GREEN_VALUE_ARB 0x2038
#define WGL_TRANSPARENT_BLUE_VALUE_ARB  0x2039
#define WGL_TRANSPARENT_ALPHA_VALUE_ARB 0x203A
#define WGL_TRANSPARENT_INDEX_VALUE_ARB 0x203B
#define WGL_SHARE_DEPTH_ARB             0x200C
#define WGL_SHARE_STENCIL_ARB           0x200D
#define WGL_SHARE_ACCUM_ARB             0x200E
#define WGL_SUPPORT_GDI_ARB             0x200F
#define WGL_SUPPORT_OPENGL_ARB          0x2010
#define WGL_DOUBLE_BUFFER_ARB           0x2011
#define WGL_STEREO_ARB                  0x2012
#define WGL_PIXEL_TYPE_ARB              0x2013
#define WGL_COLOR_BITS_ARB              0x2014
#define WGL_RED_BITS_ARB                0x2015
#define WGL_RED_SHIFT_ARB               0x2016
#define WGL_GREEN_BITS_ARB              0x2017
#define WGL_GREEN_SHIFT_ARB             0x2018
#define WGL_BLUE_BITS_ARB               0x2019
#define WGL_BLUE_SHIFT_ARB              0x201A
#define WGL_ALPHA_BITS_ARB              0x201B
#define WGL_ALPHA_SHIFT_ARB             0x201C
#define WGL_ACCUM_BITS_ARB              0x201D
#define WGL_ACCUM_RED_BITS_ARB          0x201E
#define WGL_ACCUM_GREEN_BITS_ARB        0x201F
#define WGL_ACCUM_BLUE_BITS_ARB         0x2020
#define WGL_ACCUM_ALPHA_BITS_ARB        0x2021
#define WGL_DEPTH_BITS_ARB              0x2022
#define WGL_STENCIL_BITS_ARB            0x2023
#define WGL_AUX_BUFFERS_ARB             0x2024

#define WGL_NO_ACCELERATION_ARB         0x2025
#define WGL_GENERIC_ACCELERATION_ARB    0x2026
#define WGL_FULL_ACCELERATION_ARB       0x2027

#define WGL_SWAP_EXCHANGE_ARB           0x2028
#define WGL_SWAP_COPY_ARB               0x2029
#define WGL_SWAP_UNDEFINED_ARB          0x202A

#define WGL_TYPE_RGBA_ARB               0x202B
#define WGL_TYPE_COLORINDEX_ARB         0x202C

////////////////////////////////////////
// WGL_ARB_render_texture 
////////////////////////////////////////

#define WGL_BIND_TO_TEXTURE_RGB_ARB         0x2070
#define WGL_BIND_TO_TEXTURE_RGBA_ARB        0x2071
#define WGL_TEXTURE_FORMAT_ARB              0x2072
#define WGL_TEXTURE_TARGET_ARB              0x2073
#define WGL_MIPMAP_TEXTURE_ARB              0x2074

#define WGL_TEXTURE_RGB_ARB                 0x2075
#define WGL_TEXTURE_RGBA_ARB                0x2076
#define WGL_NO_TEXTURE_ARB                  0x2077
#define WGL_TEXTURE_CUBE_MAP_ARB            0x2078
#define WGL_TEXTURE_1D_ARB                  0x2079
#define WGL_TEXTURE_2D_ARB                  0x207A
#define WGL_NO_TEXTURE_ARB                  0x2077
#define WGL_MIPMAP_LEVEL_ARB                0x207B
#define WGL_CUBE_MAP_FACE_ARB               0x207C


#define WGL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB     0x207D
#define WGL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB     0x207E
#define WGL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB     0x207F
#define WGL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB     0x2080
#define WGL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB     0x2081 
#define WGL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB     0x2082


#define WGL_FRONT_LEFT_ARB                  0x2083
#define WGL_FRONT_RIGHT_ARB                 0x2084
#define WGL_BACK_LEFT_ARB                   0x2085
#define WGL_BACK_RIGHT_ARB                  0x2086
#define WGL_AUX0_ARB                        0x2087 
#define WGL_AUX1_ARB                        0x2088 
#define WGL_AUX2_ARB                        0x2089 
#define WGL_AUX3_ARB                        0x208A 
#define WGL_AUX4_ARB                        0x208B 
#define WGL_AUX5_ARB                        0x208C 
#define WGL_AUX6_ARB                        0x208D
#define WGL_AUX7_ARB                        0x208E 
#define WGL_AUX8_ARB                        0x208F 
#define WGL_AUX9_ARB                        0x2090

////////////////////////////////////////
// ARB_shader_objects
////////////////////////////////////////

#define GL_PROGRAM_OBJECT_ARB                       0x8B40
#define GL_OBJECT_TYPE_ARB                          0x8B4E
#define GL_OBJECT_SUBTYPE_ARB                       0x8B4F
#define GL_OBJECT_DELETE_STATUS_ARB                 0x8B80
#define GL_OBJECT_COMPILE_STATUS_ARB                0x8B81
#define GL_OBJECT_LINK_STATUS_ARB                   0x8B82
#define GL_OBJECT_VALIDATE_STATUS_ARB               0x8B83
#define GL_OBJECT_INFO_LOG_LENGTH_ARB               0x8B84
#define GL_OBJECT_ATTACHED_OBJECTS_ARB              0x8B85
#define GL_OBJECT_ACTIVE_UNIFORMS_ARB               0x8B86
#define GL_OBJECT_ACTIVE_UNIFORM_MAX_LENGTH_ARB     0x8B87
#define GL_OBJECT_SHADER_SOURCE_LENGTH_ARB          0x8B88
#define GL_SHADER_OBJECT_ARB                        0x8B48
#define GL_FLOAT_VEC2_ARB                           0x8B50
#define GL_FLOAT_VEC3_ARB                           0x8B51
#define GL_FLOAT_VEC4_ARB                           0x8B52
#define GL_INT_VEC2_ARB                             0x8B53
#define GL_INT_VEC3_ARB                             0x8B54
#define GL_INT_VEC4_ARB                             0x8B55
#define GL_BOOL_ARB                                 0x8B56
#define GL_BOOL_VEC2_ARB                            0x8B57
#define GL_BOOL_VEC3_ARB                            0x8B58
#define GL_BOOL_VEC4_ARB                            0x8B59
#define GL_FLOAT_MAT2_ARB                           0x8B5A
#define GL_FLOAT_MAT3_ARB                           0x8B5B
#define GL_FLOAT_MAT4_ARB                           0x8B5C

typedef char GLcharARB;
#ifndef HX_OS_MACX
typedef GLuint GLhandleARB;
#endif

#if !(defined(AMIRA64) && (defined(__sgi) || defined(__sun))) && !defined(__hpux)
/* This is taken from mcgl/GL/glew.h */
#if !defined(_W64)
#  if !defined(__midl) && (defined(_X86_) || defined(_M_IX86)) && _MSC_VER >= 1300
#    define _W64 __w64
#  else
#    define _W64
#  endif
#endif
#if !defined(_PTRDIFF_T_DEFINED) && !defined(_PTRDIFF_T_)
#  ifdef _WIN64
typedef __int64 ptrdiff_t;
#  else
typedef _W64 int ptrdiff_t;
#  endif
#  define _PTRDIFF_T_DEFINED
#  define _PTRDIFF_T_
#endif
#endif

#ifndef HX_OS_MACX
typedef ptrdiff_t GLsizeiptr;
typedef ptrdiff_t GLintptr;
#endif

////////////////////////////////////////
// WGL_ATI_pixel_format_float
////////////////////////////////////////

#define WGL_TYPE_RGBA_FLOAT_ATI             0x21A0
#define GL_RGBA_FLOAT_MODE_ATI              0x8820
#define GL_COLOR_CLEAR_UNCLAMPED_VALUE_ATI  0x8835

#define GL_ARRAY_BUFFER 0x8892
#define GL_STREAM_DRAW                    0x88E0
#define GL_STREAM_READ                    0x88E1
#define GL_STREAM_COPY                    0x88E2
#define GL_STATIC_DRAW                    0x88E4
#define GL_STATIC_READ                    0x88E5
#define GL_STATIC_COPY                    0x88E6
#define GL_DYNAMIC_DRAW                   0x88E8
#define GL_DYNAMIC_READ                   0x88E9
#define GL_DYNAMIC_COPY                   0x88EA

////////////////////////////////////////
// ARB_imaging
////////////////////////////////////////
#define GL_HISTOGRAM 0x8024

/* This class has been replaced by mcgl, see mcgl/mcgl.h !

   This is a wrapper class to provide a standardized interface to some GL
   functions. In some implementations they are extensions (EXT), in others
   not. With theGLFuncs->getgl... () you get a pointer to the function.
   If an implementation does not provide the functionality, get... returns 0.
*/
class HXCORE_API HxGLFuncs 
{
public: 

    // We're a singleton, use this function to get us.
    static HxGLFuncs * getTheGLFuncs ();

    /* Returns the Pointer to the requested GL-Function.
       If the function is not available returns 0.
       Note that getting a pointer doesn't mean
       calling this pointer will do anything helpful.
       You still have to check if the
       renderer also provides the requested
       extension. */
    static void * get (const char* name);

    // checks and clears OpenGLs error code stack
    static int errorCheck( unsigned int inLine=0, const char * inFile=0,
        const char * inCommand=0, unsigned int inFirstErr=0, bool inNotify=0 );

    ////////////////////////////////////////
    // historical stuff
    ////////////////////////////////////////

    // 
    void * getglBindTexture ();
    //
    void * getglTexImage3D ();
    //
    void * getglTexSubImage3D ();
    //
    void * getglBlendEquation ();

    // SGI (or HP) color table
    void * getglColorTableSGI();

    // SGI (or HP) color table
    void * getglColorTableHP();

    // palleted texture
    void * getglColorTableEXT();

    static void glBlendEquation( GLenum mode );
    static void glBlendColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);

    static void glDrawBuffersARB(GLsizei n, const GLenum *bufs);
    static void glDrawBuffersATI(GLsizei n, const GLenum *bufs);

    static void glBindBuffer(GLenum target, GLuint buffer);
    static void glDeleteBuffers(GLsizei n, const GLuint *buffers);
    static void glGenBuffers(GLsizei n,  GLuint *buffers);
    static void glBufferData(GLenum target, GLsizeiptr size, const void *data, GLenum usage);
    static void glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void *data);
    static void *glMapBuffer(GLenum target, GLenum access);
    static GLboolean glUnmapBuffer(GLenum target);

    ////////////////////////////////////////
    // ARB imaging
    ////////////////////////////////////////
    static void glHistogram(GLenum target, GLsizei width, GLenum internalformat, GLboolean sink);
    static void glGetHistogram(GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid* values);

    ////////////////////////////////////////
    // NV shaders
    ////////////////////////////////////////

    static void      glGenProgramsNV(GLsizei n, GLuint *ids);
    static GLboolean glIsProgramNV(GLuint id);
    static void      glBindProgramNV(GLenum target, GLuint id);
    static void      glTrackMatrixNV(GLenum target, GLuint address, GLenum matrix, GLenum transform);
    static void      glProgramNamedParameter4fvNV(GLuint id, GLsizei len, const GLubyte *name, const GLfloat v[]);
    static GLuint    glGenFragmentShadersATI( GLuint range );
    static GLvoid    glBindFragmentShaderATI( GLuint id );
    static GLvoid    glBeginFragmentShaderATI( );
    static GLvoid    glSampleMapATI( GLuint dst, GLuint interp, GLenum swizzle );
    static GLvoid    glColorFragmentOp1ATI( GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod);
    static GLvoid    glAlphaFragmentOp1ATI( GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod );
    static GLvoid    glEndFragmentShaderATI( );
    static void      glLoadProgramNV(GLenum target, GLuint id, GLsizei len, const GLubyte *program);

    ////////////////////////////////////////
    // ARB_vertex_program
    ////////////////////////////////////////

    static GLvoid glVertexAttrib1sARB(GLuint index, GLshort x);
    static GLvoid glVertexAttrib1fARB(GLuint index, GLfloat x);
    static GLvoid glVertexAttrib1dARB(GLuint index, GLdouble x);
    static GLvoid glVertexAttrib2sARB(GLuint index, GLshort x, GLshort y);
    static GLvoid glVertexAttrib2fARB(GLuint index, GLfloat x, GLfloat y);
    static GLvoid glVertexAttrib2dARB(GLuint index, GLdouble x, GLdouble y);
    static GLvoid glVertexAttrib3sARB(GLuint index, GLshort x, GLshort y, GLshort z);
    static GLvoid glVertexAttrib3fARB(GLuint index, GLfloat x, GLfloat y, GLfloat z);
    static GLvoid glVertexAttrib3dARB(GLuint index, GLdouble x, GLdouble y, GLdouble z);
    static GLvoid glVertexAttrib4sARB(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
    static GLvoid glVertexAttrib4fARB(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    static GLvoid glVertexAttrib4dARB(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
    static GLvoid glVertexAttrib4NubARB(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
    static GLvoid glVertexAttrib1svARB(GLuint index, const GLshort *v);
    static GLvoid glVertexAttrib1fvARB(GLuint index, const GLfloat *v);
    static GLvoid glVertexAttrib1dvARB(GLuint index, const GLdouble *v);
    static GLvoid glVertexAttrib2svARB(GLuint index, const GLshort *v);
    static GLvoid glVertexAttrib2fvARB(GLuint index, const GLfloat *v);
    static GLvoid glVertexAttrib2dvARB(GLuint index, const GLdouble *v);
    static GLvoid glVertexAttrib3svARB(GLuint index, const GLshort *v);
    static GLvoid glVertexAttrib3fvARB(GLuint index, const GLfloat *v);
    static GLvoid glVertexAttrib3dvARB(GLuint index, const GLdouble *v);
    static GLvoid glVertexAttrib4bvARB(GLuint index, const GLbyte *v);
    static GLvoid glVertexAttrib4svARB(GLuint index, const GLshort *v);
    static GLvoid glVertexAttrib4ivARB(GLuint index, const GLint *v);
    static GLvoid glVertexAttrib4ubvARB(GLuint index, const GLubyte *v);
    static GLvoid glVertexAttrib4usvARB(GLuint index, const GLushort *v);
    static GLvoid glVertexAttrib4uivARB(GLuint index, const GLuint *v);
    static GLvoid glVertexAttrib4fvARB(GLuint index, const GLfloat *v);
    static GLvoid glVertexAttrib4dvARB(GLuint index, const GLdouble *v);
    static GLvoid glVertexAttrib4NbvARB(GLuint index, const GLbyte *v);
    static GLvoid glVertexAttrib4NsvARB(GLuint index, const GLshort *v);
    static GLvoid glVertexAttrib4NivARB(GLuint index, const GLint *v);
    static GLvoid glVertexAttrib4NubvARB(GLuint index, const GLubyte *v);
    static GLvoid glVertexAttrib4NusvARB(GLuint index, const GLushort *v);
    static GLvoid glVertexAttrib4NuivARB(GLuint index, const GLuint *v);
    static GLvoid glVertexAttribPointerARB(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer);
    static GLvoid glEnableVertexAttribArrayARB(GLuint index);
    static GLvoid glDisableVertexAttribArrayARB(GLuint index);
    static GLvoid glProgramStringARB(GLenum target, GLenum format, GLsizei len, const GLvoid *string); 
    static GLvoid glBindProgramARB(GLenum target, GLuint program);
    static GLvoid glDeleteProgramsARB(GLsizei n, const GLuint *programs);
    static GLvoid glGenProgramsARB(GLsizei n, GLuint *programs);
    static GLvoid glProgramEnvParameter4dARB(GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
    static GLvoid glProgramEnvParameter4dvARB(GLenum target, GLuint index, const GLdouble *params);
    static GLvoid glProgramEnvParameter4fARB(GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    static GLvoid glProgramEnvParameter4fvARB(GLenum target, GLuint index, const GLfloat *params);
    static GLvoid glProgramLocalParameter4dARB(GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
    static GLvoid glProgramLocalParameter4dvARB(GLenum target, GLuint index, const GLdouble *params);
    static GLvoid glProgramLocalParameter4fARB(GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    static GLvoid glProgramLocalParameter4fvARB(GLenum target, GLuint index, const GLfloat *params);
    static GLvoid glGetProgramEnvParameterdvARB(GLenum target, GLuint index, GLdouble *params);
    static GLvoid glGetProgramEnvParameterfvARB(GLenum target, GLuint index, GLfloat *params);
    static GLvoid glGetProgramLocalParameterdvARB(GLenum target, GLuint index, GLdouble *params);
    static GLvoid glGetProgramLocalParameterfvARB(GLenum target, GLuint index, GLfloat *params);
    static GLvoid glGetProgramivARB(GLenum target, GLenum pname, GLint *params);
    static GLvoid glGetProgramStringARB(GLenum target, GLenum pname, GLvoid *string);
    static GLvoid glGetVertexAttribdvARB(GLuint index, GLenum pname, GLdouble *params);
    static GLvoid glGetVertexAttribfvARB(GLuint index, GLenum pname, GLfloat *params);
    static GLvoid glGetVertexAttribivARB(GLuint index, GLenum pname, GLint *params);
    static GLvoid glGetVertexAttribPointervARB(GLuint index, GLenum pname, GLvoid **pointer);
    static GLboolean glIsProgramARB(GLuint program);

    ////////////////////////////////////////
    // EXT_texture3D
    ////////////////////////////////////////

    static GLvoid glTexImage3D          (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid *pixels );
    static GLvoid glTexSubImage3D       (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid * pixels ); 
    static GLvoid glCopyTexSubImage3D   (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);

    ////////////////////////////////////////
    // ARB_multitexture
    ////////////////////////////////////////

    static GLvoid glActiveTexture    (GLenum texture);
    static GLvoid glClientActiveTexture (GLenum texture);
    static GLvoid glMultiTexCoord1d  (GLenum texture, GLdouble s);
    static GLvoid glMultiTexCoord1dv (GLenum texture, const GLdouble *v);
    static GLvoid glMultiTexCoord1f  (GLenum texture, GLfloat s);
    static GLvoid glMultiTexCoord1fv (GLenum texture, const GLfloat *v);
    static GLvoid glMultiTexCoord1i  (GLenum texture, GLint s);
    static GLvoid glMultiTexCoord1iv (GLenum texture, const GLint *v);
    static GLvoid glMultiTexCoord1s  (GLenum texture, GLshort s);
    static GLvoid glMultiTexCoord1sv (GLenum texture, const GLshort *v);
    static GLvoid glMultiTexCoord2d  (GLenum texture, GLdouble s, GLdouble t);
    static GLvoid glMultiTexCoord2dv (GLenum texture, const GLdouble *v);
    static GLvoid glMultiTexCoord2f  (GLenum texture, GLfloat s, GLfloat t);
    static GLvoid glMultiTexCoord2fv (GLenum texture, const GLfloat *v);
    static GLvoid glMultiTexCoord2i  (GLenum texture, GLint s, GLint t);
    static GLvoid glMultiTexCoord2iv (GLenum texture, const GLint *v);
    static GLvoid glMultiTexCoord2s  (GLenum texture, GLshort s, GLshort t);
    static GLvoid glMultiTexCoord2sv (GLenum texture, const GLshort *v);
    static GLvoid glMultiTexCoord3d  (GLenum texture, GLdouble s, GLdouble t, GLdouble r);
    static GLvoid glMultiTexCoord3dv (GLenum texture, const GLdouble *v);
    static GLvoid glMultiTexCoord3f  (GLenum texture, GLfloat s, GLfloat t, GLfloat r);
    static GLvoid glMultiTexCoord3fv (GLenum texture, const GLfloat *v);
    static GLvoid glMultiTexCoord3i  (GLenum texture, GLint s, GLint t, GLint r);
    static GLvoid glMultiTexCoord3iv (GLenum texture, const GLint *v);
    static GLvoid glMultiTexCoord3s  (GLenum texture, GLshort s, GLshort t, GLshort r);
    static GLvoid glMultiTexCoord3sv (GLenum texture, const GLshort *v);
    static GLvoid glMultiTexCoord4d  (GLenum texture, GLdouble s, GLdouble t, GLdouble r, GLdouble q);
    static GLvoid glMultiTexCoord4dv (GLenum texture, const GLdouble *v);
    static GLvoid glMultiTexCoord4f  (GLenum texture, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
    static GLvoid glMultiTexCoord4fv (GLenum texture, const GLfloat *v);
    static GLvoid glMultiTexCoord4i  (GLenum texture, GLint s, GLint t, GLint r, GLint q);
    static GLvoid glMultiTexCoord4iv (GLenum texture, const GLint *v);
    static GLvoid glMultiTexCoord4s  (GLenum texture, GLshort s, GLshort t, GLshort r, GLshort q);
    static GLvoid glMultiTexCoord4sv (GLenum texture, const GLshort *v);

    ////////////////////////////////////////
    // ARB_vertex_shader
    ////////////////////////////////////////

    static GLvoid glBindAttribLocationARB(GLhandleARB programObj, GLuint index, const GLcharARB *name);
    static GLint glGetAttribLocationARB(GLhandleARB programObj, const GLcharARB *name);

#ifdef HX_OS_WIN

	////////////////////////////////////////
	// WGL_extensions_string
	////////////////////////////////////////
	static const GLcharARB* wglGetExtensionsStringARB(HDC hdc);

    ////////////////////////////////////////
    // windows pbuffers
    ////////////////////////////////////////

    static HPBUFFERARB  wglCreatePbufferARB (HDC hDC, int iPixelFormat, int iWidth, int iHeight, const int *piAttribList);
    static HDC  wglGetPbufferDCARB (HPBUFFERARB hPbuffer);
    static int  wglReleasePbufferDCARB (HPBUFFERARB hPbuffer, HDC hDC);
    static BOOL wglDestroyPbufferARB (HPBUFFERARB hPbuffer);
    static BOOL wglQueryPbufferARB (HPBUFFERARB hPbuffer, int iAttribute, int *piValue);
    
    ////////////////////////////////////////
    // WGL_ARB_render_texture 
    ////////////////////////////////////////

    static BOOL wglBindTexImageARB (HPBUFFERARB hPbuffer, int iBuffer);
    static BOOL wglReleaseTexImageARB (HPBUFFERARB hPbuffer, int iBuffer) ;
    static BOOL wglSetPbufferAttribARB (HPBUFFERARB hPbuffer, const int *piAttribList) ;

    ////////////////////////////////////////
    // WGL_ARB_pixel_format
    ////////////////////////////////////////

    static BOOL wglGetPixelFormatAttribivARB (HDC hdc,int iPixelFormat, int iLayerPlane, UINT nAttributes, const int *piAttributes, int *piValues);
    static BOOL wglGetPixelFormatAttribfvARB (HDC hdc,int iPixelFormat, int iLayerPlane, UINT nAttributes, const int *piAttributes, FLOAT *pfValues);
    static BOOL wglChoosePixelFormatARB (HDC hdc,const int *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats);

#endif

    ////////////////////////////////////////
    // ARB_shader_objects
    ////////////////////////////////////////

    static GLvoid        glDeleteObjectARB(GLhandleARB obj);
    static GLhandleARB   glGetHandleARB(GLenum pname);
    static GLvoid        glDetachObjectARB(GLhandleARB containerObj, GLhandleARB attachedObj);
    static GLhandleARB   glCreateShaderObjectARB(GLenum shaderType);
    static GLvoid        glShaderSourceARB(GLhandleARB shaderObj, GLsizei count, GLcharARB **string, GLint *length);
    static GLvoid        glCompileShaderARB(GLhandleARB shaderObj);
    static GLhandleARB   glCreateProgramObjectARB();
    static GLvoid        glAttachObjectARB(GLhandleARB containerObj, GLhandleARB obj);
    static GLvoid        glLinkProgramARB(GLhandleARB programObj);
    static GLvoid        glUseProgramObjectARB(GLhandleARB programObj);
    static GLvoid        glValidateProgramARB(GLhandleARB programObj);
    static GLvoid        glUniform1fARB(GLint location, GLfloat v0);
    static GLvoid        glUniform2fARB(GLint location, GLfloat v0, GLfloat v1);
    static GLvoid        glUniform3fARB(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
    static GLvoid        glUniform4fARB(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
    static GLvoid        glUniform1iARB(GLint location, GLint v0);
    static GLvoid        glUniform2iARB(GLint location, GLint v0, GLint v1);
    static GLvoid        glUniform3iARB(GLint location, GLint v0, GLint v1, GLint v2);
    static GLvoid        glUniform4iARB(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
    static GLvoid        glUniform1fvARB(GLint location, GLsizei count, GLfloat *value);
    static GLvoid        glUniform2fvARB(GLint location, GLsizei count, GLfloat *value);
    static GLvoid        glUniform3fvARB(GLint location, GLsizei count, GLfloat *value);
    static GLvoid        glUniform4fvARB(GLint location, GLsizei count, GLfloat *value);
    static GLvoid        glUniform1ivARB(GLint location, GLsizei count, GLint *value);
    static GLvoid        glUniform2ivARB(GLint location, GLsizei count, GLint *value);
    static GLvoid        glUniform3ivARB(GLint location, GLsizei count, GLint *value);
    static GLvoid        glUniform4ivARB(GLint location, GLsizei count, GLint *value);
    static GLvoid        glUniformMatrix2fvARB(GLint location, GLsizei count, GLboolean transpose, GLfloat *value);
    static GLvoid        glUniformMatrix3fvARB(GLint location, GLsizei count, GLboolean transpose, GLfloat *value);
    static GLvoid        glUniformMatrix4fvARB(GLint location, GLsizei count, GLboolean transpose, GLfloat *value);
    static GLvoid        glGetObjectParameterfvARB(GLhandleARB obj, GLenum pname, GLfloat *params);
    static GLvoid        glGetObjectParameterivARB(GLhandleARB obj, GLenum pname, GLint *params);
    static GLvoid        glGetInfoLogARB(GLhandleARB obj, GLsizei maxLength, GLsizei *length, GLcharARB *infoLog);
    static GLvoid        glGetAttachedObjectsARB(GLhandleARB containerObj, GLsizei maxCount, GLsizei *count, GLhandleARB *obj);
    static GLint         glGetUniformLocationARB(GLhandleARB programObj, GLcharARB *name);
    static GLvoid        glGetActiveUniformARB(GLhandleARB programObj, GLuint index, GLsizei maxLength, GLsizei *length, GLint *size, GLenum *type, GLcharARB *name);
    static GLvoid        glGetUniformfvARB(GLhandleARB programObj, GLint location, GLfloat *params);
    static GLvoid        glGetUniformivARB(GLhandleARB programObj, GLint location, GLint *params);
    static GLvoid        glGetShaderSourceARB(GLhandleARB obj, GLsizei maxLength, GLsizei *length, GLcharARB *source);

    ////////////////////////////////////////
    //
    ////////////////////////////////////////

private:
    /// singelton --> private.
    HxGLFuncs ();
    /// the one object that exists.
    static HxGLFuncs* _theGLFuncs;
    /// the DSO loader stuff.
    static HxDSO libGL;
};

#define theGLFuncs (HxGLFuncs::getTheGLFuncs ())

#if 0
// These macros have been replaced by mcgl MCGL_CK, MCGL_CK_N, MCGL_CK_C !

// macro that checks for OpenGL errors
static unsigned int mcgle_____;

// this macro returns a nonzero value on error
#define MCCK_GL(CMD) (  (CMD), \
                        mcgle_____=::glGetError(), \
                        mcgle_____ ? HxGLFuncs::errorCheck( __LINE__, __FILE__, #CMD, mcgle_____, 0) : 0 )

// this macro returns a nonzero value and displays a message box on error
#define MCCK_GL_N(CMD) (  (CMD), \
                        mcgle_____=::glGetError(), \
                        mcgle_____ ? HxGLFuncs::errorCheck( __LINE__, __FILE__, #CMD, mcgle_____, 1) : 0 )

// this macro throws an nonzero integer on error
#define MCCK_GL_C(CMD) (  (CMD), \
                        mcgle_____=::glGetError(), \
                        mcgle_____ ? throw HxGLFuncs::errorCheck( __LINE__, __FILE__, #CMD, mcgle_____, 0) : 0 )
#endif

#endif

/// @}
