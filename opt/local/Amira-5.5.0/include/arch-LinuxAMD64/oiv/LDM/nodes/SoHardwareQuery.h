/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_HARDWARE_QUERY_
#define  _SO_HARDWARE_QUERY_

#ifdef _WIN32
#pragma warning(disable:4251)
#pragma warning(disable:4244)
#endif

#include <Inventor/nodes/SoNode.h>

class LDM_API SoHardwareQuery : public SoNode {
  SO_NODE_ABSTRACT_HEADER( SoHardwareQuery );

 public:
  ////////////////////////////////////////////////////////////////////////////////
  // Hardware Query section
   SoHardwareQuery();

  enum HW_Feature {
  /**
   *  The system supports OpenGL 3D texture mapping.
   * On some boards, this query may return TRUE even
   * if your board does not support accelerated
   * 3D textures. In this case performance may
   * be slow, and you may prefer to use
   * 2D textures instead. Note: The inability
   * to determine if 3D textures are accelerated 
   * is a limitation of OpenGL, not Open Inventor.
   */
    HW_3DTEXMAP,
  /**
   *  The system supports the OpenGL paletted
   *  texture extension and/or the texture color table
   *  extension. 
   */
    HW_TEXCOLORMAP,
  /**
   *  The system supports the OpenGL texture
   *  compression extension.
   */
    HW_TEXCOMPRESSION
  };
  enum HW_SupportStatus {
    NO,
    YES,
    UNKNOWN
  };

  /**
   * Returns information about hardware support for various volume rendering
   * features. This query is only valid after SoVolumeRendering::init has been
   * called. Otherwise the return value will be UNKNOWN.
   */
  static HW_SupportStatus isSupported( HW_Feature feature );

  SoINTERNAL public:
    static void initClass();
    static void exitClass();

    static void registerInit();

  // ------------------------------------------------------------
  // OpenGL Extensions
  static void    checkOGLExtensions();
  static SbBool _OGLExtensionsChecked;
  static void   (*_GlTexImage3D)();
  static void   (*_GlTexSubImage3D)();
  static void   (*_GlColorTable)();
  static void   (*_GlBlendEquation)();
  static int    _hasSharedPalette;
  static int    _palettedTexType;
  static int    _GlTexInternalFormat;
  static int    _GlTexFormat;
  static int    _GlLutTarget;
  static int    _GlLutInternalFormat;
  static int    _hasCompressedTexture;
  static int    _GlTexRGBAInternalFormat;
  static int    _hasFragmentProgram;
  static int    _hasTextureExtension;
};
#endif // _SO_HARDWARE_QUERY_
