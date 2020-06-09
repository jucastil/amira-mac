/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Dave Immel (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef _SO_OFFSCREEN_RENDERER_
#define _SO_OFFSCREEN_RENDERER_


#include <Inventor/SbColor.h>
#include <Inventor/SbViewportRegion.h>
#include <Inventor/SbLinear.h>
#include <Inventor/SbPList.h>
#include <Inventor/threads/SbThreadSpinlock.h>
#include <Inventor/components/SoGLGraphicConfigTemplate.h>
#include <Inventor/helpers/SbGlContextHelper.h>
#include <Inventor/sys/SoGLType.h>

#include <stdio.h>
  #undef Display

class SoBase;
class SoNode;
class SoPath;
class SoGLRenderAction;
class SoPBuffer;
class SoOffscreenTileObserver;
class SoGLContext;
class SoGLGraphicConfigTemplate;
class SbRasterImage;
class SoRasterImageFile;
class SoRasterImageRW;
class SoOffRenderItem;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoOffscreenRenderer
//
//  This file contains the definition of the SoOffscreenRenderer class.
//  This class is used for rendering a scene graph to an offscreen memory
//  buffer which can be used for printing or generating textures.
//
//  The implementation of this class uses the X Pixmap for rendering.
//
//////////////////////////////////////////////////////////////////////////////

#ifdef OIV_NET_DOC
/**
*
* Renders to an off-screen buffer for printing or generating textures.
*
* @ingroup General
*
* @DESCRIPTION
*   This class is used to render into an off-screen buffer to create a printable
*   image or to generate a texture image. It uses a Pbuffer (if possible)
*   or an off-screen bitmap for rendering.
*   Methods are provided to write the buffer to a file, as an RGB image, an
*   encapsulated PostScript description, or in one of several other image formats.
*
*   If the requested image size exceeds OpenGL rendering capabilities (the
*   maximum OpenGL viewport is typically 2048 by 2048),
*   the image will be created by rendering some number of "tiles".
*   Using tiles allows you to create large, high resolution images. For example,
*   a poster size image to be printed at 300 dpi would need to be (approximately)
*   10,000 pixels wide.
*
*   Some output file formats are much more efficient than
*   others at dealing with tiled output. If you anticipate generating very large
*   images, it may be helpful to chose an output format that can generate
*   tiled output efficiently. The formats in the "WRITE_SCANLINES" column in the
*   following table are more efficient at generating tiled output.
*
*  @TABLE_1B
*  @TR
*  @B Write Capability@BR
*  WRITE_FULL_IMAGE@b
*  @TD
*  @B Write Capability@BR
*  WRITE SCANLINES@b
*  @TR
*  BMP  @BR
*  JP2 (JPEG2000)  @BR
*  PGX  @BR
*  PNM  @BR
*  SUN  @BR
*  @TD
*  JPEG @BR
*  PNG  @BR
*  PS (PostScript)   @BR
*  SGIRGB  @BR
*  TIFF @BR
*  @TABLE_END
*
*   For the WRITE_FULL_IMAGE formats, the entire image must be written at
*   once, so a buffer large enough for the whole image is allocated,
*   and tiles are copied into it. Therefore
*   it must be possible to allocate enough memory
*   for a single tile (num_components *
*   tile_width * tile_height) plus
*   enough memory to assemble the complete image
*   (num_components * width * height).
*
*   For the WRITE_SCANLINES formats, the image can be written incrementally,
*   some number of scanlines at a time. Therefore it is only necessary to allocate
*   enough memory for a single tile, which at most will be the size of the maximum
*   OpenGL viewport (typically 2048x2048).
*
*   See the documentation for SoRasterImageRW and the individual image classes
*   (SoBMPImageRW, SoGIFImageRW, etc.) for further information.
*
*   Beginning with Open Inventor 3.1, this class will automatically try to use an
*   OpenGL @I Pbuffer @i for rendering. If a Pbuffer is available, rendering will be
*   accelerated by the 3D graphics hardware. If no Pbuffer is available, rendering
*   will use a software rendered off-screen buffer as before. Pbuffers are a
*   standard feature of OpenGL 1.2 and are often available as an extension on
*   older versions of OpenGL. However it is not guaranteed that Pbuffers will be
*   available or that a Pbuffer of the desired size can be created.
*
*   Rendering with a Pbuffer will generally produce the same image as would be
*   rendered on the screen, but this is not guaranteed. In general, software rendering
*   will produce the same image as on-screen if only OpenGL 1.1 features are used.
*   Newer OpenGL features and extensions will generally not be available using
*   software rendering.
*
*   Note that Pbuffers are a limited resource. If the application creates multiple
*   instances of SoOffscreenRenderer, it may be desirable to prevent some of them
*   (that are lower priority or render small scene graphs) from using a Pbuffer.
*   See the method setPbufferEnable().
*
*   The #setShareContext method allows you to
*   share an already existing OpenGL context with the offscreen renderer.
*   This avoids the necessity to re-generate textures and display lists
*   if they are already available in another OpenGL context (the viewer
*   context, for instance). This can dramatically reduce offscreen
*   rendering time, depending on your scene graph. A corresponding query method
*   (#GetShareContext) is also available.
*
*   Rendering a "snapshot" @BR
*   SoOffscreenRenderer is often used to save a snapshot of the image
*   in the viewer window. There are several common pitfalls. First, the
*   scene graph given to the renderer must include the camera node that
*   the viewer is using.  If the application allows the viewer to create
*   a camera automatically, the scene graph returned by the viewer's
*   GetSceneGraph() method does not include the camera. It's always safer
*   to get the SoSceneManager object then get the scene graph.  Second,
*   some rendering options are set on the viewer object, not in the
*   scene graph.  These options, which include background color and
*   transparency mode, must be explicitly queried from the viewer and
*   set on the renderer object.  Sample code to make a snapshot, given
*   a viewer object might look like this:
*   <PRE>
*      // Make image same size and shape as viewer image
*      SoOffscreenRenderer renderer =
*        new SoOffscreenRenderer( viewer.GetViewportRegion() );
*
*      // Transfer viewer settings to renderer
*      renderer.SetShareContext( viewer.GetShareContext() );
*      renderer.SetBackgroundColor( viewer.GetBackgroundColor() );
*      renderer.GetGLRenderAction().SetTransparencyType( viewer.GetTransparencyType() );
*
*      // Render scene (including camera and headlight)
*      renderer.Render( viewer.GetSceneManager().GetSceneGraph() );
*
*      // Write image to a file in PNG format
*      renderer.WriteToPNG( filename );
*   </PRE>
*   See: $OIVHOME/src/Inventor/examples/Mentor/CSharp/_09_1_Print
*   for a complete example.
*
*   NOTE: Tiled rendering does not currently work
*   correctly when a camera node's viewportMapping
*   field is set to one of the CROP_ options. It
*   does work correctly with the LEAVE_ALONE and
*   ADJUST_CAMERA (default) settings.
*
* @SEE_ALSO
*    SoRasterImageRW
*
*
*/
#else
/**
*
* Renders to an off-screen buffer for printing or generating textures.
*
* @ingroup General
*
* @DESCRIPTION
*   This class is used to render into an off-screen buffer to create a printable
*   image or to generate a texture image. It uses a Pbuffer (if possible)
*   or an off-screen bitmap for rendering.
*   Methods are provided to write the buffer to a file, as an RGB image, an
*   encapsulated PostScript description, or in one of several other image formats.
*
*   If the requested image size exceeds OpenGL rendering capabilities (the
*   maximum OpenGL viewport is typically 2048 by 2048),
*   the image will be created by rendering some number of "tiles".
*   Using tiles allows you to create large, high resolution images. For example,
*   a poster size image to be printed at 300 dpi would need to be (approximately)
*   10,000 pixels wide.
*
*   Some output file formats are much more efficient than
*   others at dealing with tiled output. If you anticipate generating very large
*   images, it may be helpful to chose an output format that can generate
*   tiled output efficiently. The formats in the "WRITE_SCANLINES" column in the
*   following table are more efficient at generating tiled output.
*
*  @TABLE_1B
*  @TR
*  @B Write Capability@BR
*  WRITE_FULL_IMAGE@b
*  @TD
*  @B Write Capability@BR
*  WRITE SCANLINES@b
*  @TR
*  BMP  @BR
*  JP2 (JPEG2000)  @BR
*  PGX  @BR
*  PNM  @BR
*  SUN  @BR
*  @TD
*  JPEG @BR
*  PNG  @BR
*  PS (PostScript)   @BR
*  SGIRGB  @BR
*  TIFF @BR
*  @TABLE_END
*
*   For the WRITE_FULL_IMAGE formats, the entire image must be written at
*   once, so a buffer large enough for the whole image is allocated,
*   and tiles are copied into it. Therefore
*   it must be possible to allocate enough memory
*   for a single tile (num_components *
*   tile_width * tile_height) plus
*   enough memory to assemble the complete image
*   (num_components * width * height).
*
*   For the WRITE_SCANLINES formats, the image can be written incrementally,
*   some number of scanlines at a time. Therefore it is only necessary to allocate
*   enough memory for a single tile, which at most will be the size of the maximum
*   OpenGL viewport (typically 2048x2048).
*
*   See the documentation for SoRasterImageRW and the individual image classes
*   (SoBMPImageRW, SoGIFImageRW, etc.) for further information.
*
*   PBuffers @BR
*   Beginning with Open Inventor 3.1, this class will automatically try to use an
*   OpenGL @I Pbuffer @i for rendering. If a Pbuffer is available, rendering will be
*   accelerated by the 3D graphics hardware. If no Pbuffer is available, rendering
*   will use a software rendered off-screen buffer as before. Pbuffers are a
*   standard feature of OpenGL 1.2 and are often available as an extension on
*   older versions of OpenGL. However it is not guaranteed that Pbuffers will be
*   available or that a Pbuffer of the desired size can be created.
*
*   Rendering with a Pbuffer will generally produce the same image as would be
*   rendered on the screen, but this is not guaranteed. In general, software rendering
*   will produce the same image as on-screen if only OpenGL 1.1 features are used.
*   Newer OpenGL features and extensions will generally not be available using
*   software rendering.
*
*   Note that Pbuffers are a limited resource. If the application creates multiple
*   instances of SoOffscreenRenderer, it may be desirable to prevent some of them
*   (that are lower priority or render small scene graphs) from using a Pbuffer.
*   See the method setPbufferEnable().
*
*   Rendering contexts @BR
*   The #setShareContext method allows you to
*   share an already existing OpenGL context with the offscreen renderer.
*   This avoids the necessity to re-generate textures and display lists
*   if they are already available in another OpenGL context (the viewer
*   context, for instance). This can dramatically reduce offscreen
*   rendering time, depending on your scene graph.
*
*   A corresponding query method (#getShareContext) is also available.
*
*   Here's how you might use these methods to share OpenGL contexts:
* <PRE>
*       pOffscreen->setShareContext(pViewer->getShareContext());
* </PRE>
*
*   Rendering a "snapshot" @BR
*   SoOffscreenRenderer is often used to save a snapshot of the image
*   in the viewer window. There are several common pitfalls. First, the
*   scene graph given to the renderer must include the camera node that
*   the viewer is using.  If the application allows the viewer to create
*   a camera automatically, the scene graph returned by the viewer's
*   getSceneGraph() method does not include the camera. It's always safer
*   to get the SoSceneManager object then get the scene graph.  Second,
*   some rendering options are set on the viewer object, not in the
*   scene graph.  These options, which include background color and
*   transparency mode, must be explicitly queried from the viewer and
*   set on the renderer object.  Sample code to make a snapshot, given
*   a viewer object "pViewer" might look like this:
*   <PRE>
*      // Make image same size and shape as viewer image
*      SoOffscreenRenderer renderer( pViewer->getViewportRegion() );
*
*      // Transfer viewer settings to renderer
*      renderer.setShareContext( pViewer->getShareContext() );
*      renderer.setBackgroundColor( pViewer->getBackgroundColor() );
*      renderer.getGLRenderAction()->setTransparencyType( pViewer->getTransparencyType() );
*
*      // Render scene (including camera and headlight)
*      renderer.render( pViewer->getSceneManager()->getSceneGraph() );
*
*      // Write image to a file in PNG format
*      FILE *fp = fopen( "test.png", "wb" );
*      renderer.writeToPNG( fp );
*      fclose( fp );
*   </PRE>
*   See: $OIVHOME/src/Inventor/examples/Mentor/Cxx/09.1.Print.cxx
*   for a complete example.
*
*   NOTE: Tiled rendering does not currently work
*   correctly when a camera node's viewportMapping
*   field is set to one of the CROP_ options. It
*   does work correctly with the LEAVE_ALONE and
*   ADJUST_CAMERA (default) settings.
*
* @SEE_ALSO
*    SoRasterImageRW
*/
#endif //OIV_NET_DOC


class INVENTOR_API SoOffscreenRenderer {

 public:
  /**
   * Constructor. An internal instance of an SoGLRenderAction will be
   * maintained with a viewport
   * region set to the one passed in by the constructor.
   */
  SoOffscreenRenderer(const SbViewportRegion &viewportRegion);
  /**
   * Constructor. The render action passed to the constructor
   * will be used in all subsequent offscreen renderings.
   */
  SoOffscreenRenderer(SoGLRenderAction *ra);

  /**
   * Destructor.
   */
  ~SoOffscreenRenderer();

  /** Components */
  enum Components {
    /** Luminance */
    LUMINANCE = 1,
    /** Luminance plus Alpha */
    LUMINANCE_TRANSPARENCY = 2,
    /** RGB (default) */
    RGB = 3,
    /** RGB plus Alpha */
    RGB_TRANSPARENCY = 4
  };

  /** TIFF Compression modes */
  enum TIFFCompressionMode {
    /** No compression */
    NO_COMPRESSION,
    /** Packbits compression (default) */
    PACKBITS_COMPRESSION
  };

  /** Buffer types */
  typedef enum {
   /** RGB buffer */
    RGB_BUFFER,
    /** JPEG buffer */
    JPEG_BUFFER/*,*/
    /*TIFF_BUFFER,*/
    /*PS_BUFFER,*/
    /*BMP_BUFFER,*/
  } BufferType;

  /** Possible return codes from a render abort callback */
  enum AbortCode {
    /**
     *  Continue rendering as usual.
     */
    CONTINUE,
    /**
     *  Stop rendering the rest of the big image.
     */
    ABORT
  };

  /** Callback functions for render abort should be of this type.
   * This typedef is defined within the class, since it needs to
   * refer to the AbortCode enumerated type.
   * [OIV-WRAPPER NAME{AbortCB}]
   */
  typedef AbortCode SoOffscreenAbortCB(void *userData, int numSubimage, int subimageCount);

  /**
   * Sets callback to call during rendering to test for abort condition. It will be
   * called for each subimage (tile) that is rendered. This allows the application to
   * terminate rendering prematurely if some condition occurs. The callback function
   * should return one of the AbortCode values to indicate whether rendering should
   * continue.
   *
   * Rendering a big image can take a long time (in the user's perception anyway).
   * This callback can also be used to display a "progress bar" or other indication
   * of how much work has been completed. @B numSubImage @b gives the total number
   * of subimages to be rendered. @B subImageCount @b gives the number of subimages
   * rendered so far.
   */
  void setAbortCallback(SoOffscreenAbortCB *func, void *userData)
    { m_abortCB = func; m_abortData = userData; }

  /**
   * Returns the number of pixels per inch (in the horizontal direction) of the
   * current X device screen.
   */
  static float getScreenPixelsPerInch();

  /**
   * Sets the components to be rendered. @BR
   * Default is RGB. For historical reasons the word TRANSPARENCY 
   * is used in the enum names, but RGB_TRANSPARENCY really means to render 
   * RGBA pixels. Alpha values will not be available if OpenGL does not provide
   * any pixel formats with an alpha buffer.  Some image file formats, for
   * example JPEG, do not support alpha values.  If you write to one of these
   * formats only the RGB components will be saved.  When using alpha values,
   * the framebuffer is initialized to the specified RGB values (see the
   * setBackgroundColor method) and an alpha value of zero.
   */
  void setComponents(Components components);

  /**
   * Returns the components to be rendered.
   */
  Components getComponents() const { return m_comps; }

  /**
   * Sets the maximum subimage (tile) size for rendering. The default value is
   * 1984 by 1984. This corresponds to the typical maximum image that OpenGL can
   * render, 2048 by 2048, minus a 32-pixel overlap on each edge.
   *
   * The maximum tile size that is set should not exceed the maximum image size that
   * OpenGL can render (implementation and/or hardware dependent) minus two times the
   * number of edge pixels (see below).
   */
  void    setMaxTileSize( SbVec2s size );
  /**
   * Synonym for #setMaxTileSize.
   */

  void    setMaxSubimage( SbVec2s size );

  /**
   * Gets the maximum subimage (tile) size for rendering.
   */
  SbVec2s getMaxTileSize() const {
    return SbVec2s((short)m_tileSize[0],(short)m_tileSize[1]); }
  /**
   * Synonym for #getMaxTileSize.
   */
  SbVec2s getMaxSubimage() const {
        return SbVec2s((short)m_tileSize[0],(short)m_tileSize[1]); }

  /**
   * Sets the number of pixels on the edge of each subimage that are not written
   * on the big image (overlapped pixels). The default value is two pixels. Some
   * overlap is usually required to avoid visual "artifacts" at the subimage
   * boundaries. One source of artifacts is that when OpenGL clips lines, it draws a
   * line between the points where the line exits and re-enters the visible region.
   * This additional segment is not part of the actual geometry. A two pixel overlap
   * will hide this undesired segment unless the line width is greater than two, in
   * which case you may need to specify a larger overlap.
   */
  void setNumEdgePixels( int nb );
  /**
   * Gets the number of pixels on the edge of each subimage that are not written
   * on the big image (overlapped pixels).
   */
  int  getNumEdgePixels() const { return m_numEdgePixels; }

  /**
   * Sets the viewport region used for rendering. This will NOT be applied
   * to the viewport region of any render action passed in.
   */
  void setViewportRegion(const SbViewportRegion &region);

  /**
   * Returns the viewport region used for rendering.
   */
  const SbViewportRegion &getViewportRegion() const;

  /**
   * Gets the maximum supported resolution of the viewport.
   */
  static SbVec2s getMaximumResolution();

  /**
   * Sets the background color for rendering.@BR
   * @BR
   * The default value can be set using the environment variable
   * OIV_BACKGROUND_COLOR. Specify three floats (R, G, B) in the range 0. to 1.,
   * separated by spaces.
   */
  void setBackgroundColor(const SbColor &c);
  /**
   * Returns the background color for rendering.
   */
  const SbColor &getBackgroundColor() const { return m_backgroundColor; }

  /**
   * Sets the render action to use for rendering.
   */
  void setGLRenderAction(SoGLRenderAction *ra);
  /**
   * Gets the render action to use for rendering. This will return any render
   * action passed in by the caller.
   */
  SoGLRenderAction *getGLRenderAction() const;

  /**
   * Renders the given scene, specified as a node, into an off-screen
   * buffer.
   *
   * Note: If tiled rendering will be
   * done, the application must call render(), but the actual
   * rendering is not
   * done until one of the writeToXXX() methods or getBuffer() is called.
   */
  SbBool render(SoNode *scene);
  /**
   * Renders the given scene, specified as a path, into an off-screen
   * buffer.
   *
   * Note: If tiled rendering will be
   * done, the application must call render(), but the actual
   * rendering is not
   * done until one of the writeToXXX() methods or getBuffer() is called.
   */
  SbBool render(SoPath *scene);


  /**
   * Sets a subregion of the viewport to be rendered.
   * Units are pixels. For regions greater thatn 32767,
   * use the setRegion_i32 method.
   * The origin is relative to the lower left corner.
   * Only this region will be rendered, returned by getBuffer,
   * or written to a file.
   */
  void setRegion(const SbVec2s& origin, const SbVec2s& size);

  /**
   * Sets a subregion of the viewport to be rendered.
   * Units are pixels.
   * The origin is relative to the lower left corner.
   * Only this region will be rendered, returned by getBuffer,
   * or written to a file.
   */
  void setRegion_i32(const SbVec2i32& origin, const SbVec2i32& size);

#ifdef OIV_NET_DOC
  /**
  * Returns a buffer containing the rendered image.
  *
  * If the specified buffer type is RGB_BUFFER, the buffer is an array of bytes.
  * Each pixel is stored sequentially by scanline, starting with the lower left
  * corner. The data stored for each pixel is determined by the Components set
  * before rendering. Pixels are stored in RGBA order and are packed without
  * any padding between pixels or scanlines.
  *
  * If the specified buffer type is JPEG_BUFFER and #writeToJPEG has been called
  * with a null file name, the buffer contains the result
  * of the requested JPEG encoding (see #writeToJPEG @B quality@b argument).
  * #GetBuffer returns null if writeToJPEG(JPEG_BUFFER) has not been called yet.
  * The returned buffer is available until the object is disposed or writeToJPEG(JPEG_BUFFER)
  * is called again.
  *
  * The buffer size is returned by the #GetBufferSize method.
  * [OIV-WRAPPER-RETURN-TYPE ARRAY{GetBufferSize()}]
  * [OIVJAVA-WRAPPER-RETURN-TYPE ARRAY{getBufferSize()}]
  */

#else
  /**
  * Returns a buffer containing the rendered image. @BR
  * This memory is "owned" by Open Inventor and should not be deleted by
  * the application. The memory is freed when the SoOffscreenRenderer
  * object is destroyed.
  *
  * If the specified buffer type is RGB_BUFFER, the buffer is an array of
  * bytes (unsigned char).
  * Each pixel is stored sequentially by scanline, starting with the lower left
  * corner. The data stored for each pixel is determined by the Components set
  * before rendering. Pixels are stored in RGBA order and are packed without
  * any padding between pixels or scanlines.
  *
  * If the specified buffer type is JPEG_BUFFER and #writeToJPEG has been called
  * with a NULL file descriptor, the buffer contains the result
  * of the requested JPEG encoding (see #writeToJPEG @B quality@b argument).
  * #getBuffer returns NULL if writeToJPEG(JPEG_BUFFER) has not been called yet.
  * The pointer returned is available until the destructor or writeToJPEG(JPEG_BUFFER)
  * is called again.
  *
  * The buffer size is returned by the #getBufferSize method.
  */

#endif //OIV_NET_DOC
  unsigned char *getBuffer(BufferType buffType = SoOffscreenRenderer::RGB_BUFFER);

  /**
   * Returns the buffer size in bytes. @BR
   * If the specified buffer type is JPEG_BUFFER,
   * getBufferSize returns 0 if #writeToJPEG (JPEG_BUFFER) has
   * not been called yet.
   */
  size_t getBufferSize(BufferType buffType = SoOffscreenRenderer::RGB_BUFFER);

  /**
   * Writes the buffer as an .rgb file to the given file pointer.
   * [OIVNET-WRAPPER-CUSTOM-CODE]
   * [OIVJAVA-WRAPPER-ARG WRAP_AS{SbString}]
   */
  SbBool writeToRGB(FILE *fp) const;

  /**
   * Writes the buffer as encapsulated PostScript to the given file pointer. The
   * size of the image in the buffer is adjusted so it is the same as the apparent
   * size of the viewport region on the current device.
   * [OIVNET-WRAPPER-CUSTOM-CODE]
   * [OIVJAVA-WRAPPER-ARG WRAP_AS{SbString}]
   */
  SbBool writeToPostScript(FILE *fp) const;

  /**
   * Writes the buffer as encapsulated PostScript to the given file pointer.
   * The print size is specified in inches.
   * [OIVNET-WRAPPER-CUSTOM-CODE]
   * [OIVJAVA-WRAPPER-ARG WRAP_AS{SbString}]
   */
  SbBool writeToPostScript(FILE *fp, const SbVec2f &printSize) const;

  /*************************************************************************************/
  // TIFF output
  /*************************************************************************************/
  // This software is based in part on the work of Sam Leffler / Silicon Graphics Inc.
  // Copyright (c) 1988-1996 Sam Leffler
  // Copyright (c) 1991-1996 Silicon Graphics, Inc.
  /**
   * Writes the buffer as a TIFF file to the given file pointer.
   *
   * [OIVNET-WRAPPER-CUSTOM-CODE]
   * [OIVJAVA-WRAPPER-ARG WRAP_AS{SbString}]
   */
  SbBool writeToTIFF(FILE *fp, TIFFCompressionMode TIFFcm = PACKBITS_COMPRESSION) const;

  /*************************************************************************************/
  // JPEG output
  /*************************************************************************************/
  // This software is based in part on the work of the Independent JPEG Group
  // Copyright (C) 1991-1998, Thomas G. Lane.
  /**
   * Writes the buffer as a JPEG file to the given file pointer. @BR
   * If the file pointer is NULL, the JPEG compression stream is written to a buffer.
   * Previous JPEG buffers are deleted and a new one is created.
   * The #getBuffer method returns a pointer to the buffer, and #getBufferSize
   * returns the buffer size.@BR
   * 1.0 is the best quality with the least compression,
   * 0.0 is the worst quality with the most compression.
   * A typical value for quality is 0.7.
   *
   * [OIVNET-WRAPPER-CUSTOM-CODE]
   * [OIVJAVA-WRAPPER-ARG WRAP_AS{SbString}]
   */
  SbBool writeToJPEG(FILE *fp, float quality = 1.0) const;

  /**
   * Writes the buffer as a PNG file to the given file pointer. @BR
   * The file must be opened in binary mode.
   * [OIVNET-WRAPPER-CUSTOM-CODE]
   * [OIVJAVA-WRAPPER-ARG WRAP_AS{SbString}]
   */
  SbBool writeToPNG(FILE *fp) const;

  /**
   * @WIN32 Writes the buffer as a "Windows RGB Encoded" .bmp file to the given file
   * pointer.
   * [OIVNET-WRAPPER-CUSTOM-CODE]
   * [OIVJAVA-WRAPPER-ARG WRAP_AS{SbString}]
   */
  SbBool writeToBMP(FILE *fp) const;


  /**
   * Writes the buffer using the image writer class passed as the second parameter.
   * This is a general
   * interface for writing the image buffer to a file. All the file format-specific
   * writeTo methods actually call this method.
   * See classes SoXXXImageRW (e.g., SoBMPImageRW, etc.).
   * [OIVNET-WRAPPER-CUSTOM-CODE]
   * [OIVJAVA-WRAPPER-ARG WRAP_AS{SbString}]
   */
  SbBool writeToRaster(FILE *fp, SoRasterImageRW* imageWriter);

  /**
   * Specifies a tile observer object which will be called after each tile is
   * rendered.
   */
  void setTileObserver(SoOffscreenTileObserver* tileObserver);


  /**
   * @WIN32 Returns the "device context" containing the rendered image. @BR This
   * value is only valid after the "render" method has been called (at least once) on
   * an instance of SoOffscreenRenderer. Standard Win32 API calls can be used to
   * retrieve the actual bitmap (DIBsection) from this device context, to copy the
   * bitmap into another device context, and so on. Not useful if tiled rendering
   * was required.
   */
  const HDC &getDC() const;

  /**
   * Sets the color depth to be used for offscreen rendering. Currently the only
   * values allowed are 8 and 24 (the default is 24). This feature is useful if you
   * want to do 256 color dithered rendering for printing. The change does not take
   * effect until the next render() or @B setupPixmap @b() call. Note:
   * @B WriteToBMP @b does not currently support 256 color bitmaps.
   */
  void setColorDepth(int nbits);

  /**
   * Gets the color depth to be used for offscreen rendering.
   */
  int getColorDepth() const { return m_nCurrentColorDepth; }

  /**
   * Specifies if a Pbuffer may be used for rendering.
   * Pbuffers are a limited resource. If an application is using multiple
   * offscreen renderers, it may better to use normal pixmap rendering for
   * some of them. Must be called before the first call to render().
   * Default is TRUE.
   */
  void setPbufferEnable( SbBool enable );

  /**
   * Returns TRUE if a Pbuffer may be used for rendering.
   */
  SbBool getPbufferEnable() const { return m_pbufferEnable; }


  /**
   *
   * Gets the current graphics configuration template.
   */
  SoGLGraphicConfigTemplate* getGraphicConfigTemplate();


  /**
   *
   * Sets a new graphics configuration template.
   */
  void setGraphicConfigTemplate(SoGLGraphicConfigTemplate* gTemplate);


  /**
   *
   * Sets the full-scene antialiasing preferences. @BR
   * minBits and maxBits are the minimum and maximum required number of samples used during antialiasing computation.
   * The required number of samples must be greater than or equal to minBits, and less
   * than or equal to maxBits. The maximum number of samples is always preferred.
   * If pref is FORBIDDEN, the min/max values are ignored.
   */
  void setFullSceneAntialiasing( SoGraphicConfigTemplate::Preference pref,
                                 int minFsaaBits = 0,
                                 int maxFsaaBits = INT_MAX );

  /**
   *
   * Returns the full-scene antialiasing preference and number of samples.
   * [OIVJAVA-WRAPPER PACK{AntialiasingInfo}]
   * [OIVJAVA-WRAPPER-RETURN-TYPE NAME{priority}]
   */
  SoGraphicConfigTemplate::Preference getFullSceneAntialiasing( int &minFsaaBits,
                                                                int &maxFsaaBits) const;

  /**
   *
   * Returns TRUE if FSAA is currently enabled. Also returns the current quality value.
   * [OIVJAVA-WRAPPER-ARG NO_WRAP]
   * [OIVJAVA-WRAPPER DUPLICATE{getFullSceneAntialiasingQuality}]
   * [OIVJAVA-WRAPPER-RETURN-TYPE APPLY_TO{getFullSceneAntialiasingQuality} SUCCESS_FLAG{throw new UnsupportedOperationException()}]
   */
  SbBool isFullSceneAntialiasing(float& quality);

  /**
   * Sets the OpenGL context to be shared by the SoOffscreenRenderer.
   * Its use is strongly recommended, because it can improve performance when
   * switching between on-screen and off-screen rendering. This is because it allows
   * the display lists and texture objects to be shared between the on-screen and
   * off-screen render context.
   * The shared context info is normally obtained by calling the viewer's
   * @B getShareContext@b method.
   *
   * NOTE: It has no effect when the hardware (or driver) does not allow sharing
   * with the off-screen context, for example if Pbuffers are not supported.
   *
   */
  void setShareContext(const SbGLShareContext shareCxt);


  /**
   *
   * Gets the OpenGL context shared by the SoOffscreenRenderer.
   */
  const SbGLShareContext getShareContext() const;



 SoEXTENDER public:

  /**
   * Do all the setup for rendering and make the offscreen context current
   * (useful if you want to make your own OpenGL calls)
   */
  SbBool setupPixmap();

  /**
   * Get the SoPBuffer used for rendering.  Can also be used to determine
   * if a Pbuffer is being used for rendering.  Returns NULL if no Pbuffer.
   */
  const SoPBuffer *getPBuffer() const { return m_pbuffer; }


 SoINTERNAL public:
  SbBool isLargeImage() {return m_largeImage;};
  SbBool isMultiTiled() {return m_multiTiled;};

  SoGLContext* m_glContext;

protected :
  unsigned char* m_pixelBuffer;
  int m_pixelBufferSize;
  unsigned char* m_jpegBuffer;
  size_t m_jpegBufferSize;
  Components m_comps;
  SbColor m_backgroundColor;
  // This indicates the dimensions of the maximum subimage used for rendering
  SbVec2i32 m_tileSize;


  SbVec2i32 m_previousSubTileBufferSize;

  // Number of pixels on the edge of each subimage that are not written on the big image
  int m_numEdgePixels;

  SoOffscreenTileObserver* m_tileObserver;

  // Variables for render abort:
  SoOffscreenAbortCB*    m_abortCB;       // Callback to test abort
  void *m_abortData;      // User data for abort callback

  SbViewportRegion m_vpRegion;

  SbVec2i32 m_regionOrigin;
  SbVec2i32 m_regionSize;
  SbBool  m_isRegion;

  // Share context
  SbGLShareContext m_glShareContext;

#ifdef _WIN32
  // These are used for rendering to the offscreen bitmap
  HDC      m_hDC;        // Memory device context
  HGLRC    m_context;    // Analog of GLXContext
  HBITMAP  m_hBitmap;    // Analog of GLXPixmap
  HBITMAP  m_hOldBitmap;
  HPALETTE m_hOldPalette;
  HGLRC    m_savedCtx;


  // Initialize an offscreen bitmap (DIBsection)
  // Note a lot of things have to be returned (eg. theOldBitmap)
  // so we can proper cleanup of the Win32 objects later.
  static SbBool initPixmap(SoOffscreenRenderer* offscreen,
                           HDC &theDC,
                           PIXELFORMATDESCRIPTOR &thePFD,
                           HGLRC &cx,
                           const SbVec2i32 &sz,
                           HBITMAP &theBitmap,
                           HBITMAP &theOldBitmap,
                           HPALETTE &theOldPalette);


#elif defined(__APPLE__)

  // These are used for rendering to the offscreen pixmap
  CGLContextObj  m_context;
  unsigned char* m_pixmap;
  CGLContextObj  m_savedCtx;
  
  // Initialize an offscreen pixmap
  static SbBool initPixmap(SoOffscreenRenderer* offscreen,
                           CGLContextObj& cx,
                           const SbVec2i32 &sz,
                           unsigned char* &thePixmap);
                           
#else
  /* UNIX */
  // These are used for rendering to the offscreen pixmap
  SbGlContextHelper::Display    m_display;
  SbGlContextHelper::VisualInfo m_visual;
  GLXContext  m_context;
  GLXPixmap   m_pixmap;
  Pixmap      m_pmap;
  GLXContext  m_savedCtx;


  // Initialize an offscreen pixmap
  static SbBool initPixmap(SoOffscreenRenderer* offscreen,
                           Display * &dpy, SbGlContextHelper::VisualInfo &vi,
                           GLXContext &cx, const SbVec2i32 &sz,
                           GLXPixmap &glxPmap, Pixmap &xpmap);


#endif

  SbGlContextHelper::Display  m_pBufferDisplay;


  SoPBuffer *m_pbuffer;
  SbBool     m_pbufferEnable; // are we allowed to use a Pbuffer

  int m_nRequestedColorDepth;
  int m_nCurrentColorDepth;

  // Query OpenGL
  static int    m_maxGlRenderSize;
  static SbBool m_maxGlRenderSizeFlag;
  static SbBool getMaxRenderSize();

  // Initialize a Pbuffer for rendering
  static SbBool initPbuffer( SoOffscreenRenderer* osr, SbGlContextHelper::Display &display,
                             const SbVec2i32 &sz, SoPBuffer* &pbuffer );

  // Read pixels back from the Pixmap
  void readPixels();

  // Compute array size in uncompressed format and set the GL image format
  void getAllocSizeAndFormat(int& allocSize, GLenum& format);

  // Set the graphics context
  SbBool bindContext();

  SbBool unbindContext();

  // Return the format used in the rendering
  GLenum getGLformat(void) const;

  // Returns TRUE if render action should abort based on callback
  SbBool checkAbort(int numSubimage, int subimageCount);

  // Function called by both render(SoNode) and render(SoPath) : the code was similar.
  // Render the given scene into a buffer
  SbBool renderNodeOrPath(SoBase *scene);

  SbBool doSubTile(SbVec2i32& pixelOffset, SbVec2i32& offset, SbVec2i32& renderSize, SbVec2i32& subTileBufferSize,
                   SbVec2i32& lastSubTileBufferSize, SbVec2i32& numSubTiles, SoRasterImageRW* imageWriter,
                   unsigned char*& tileBuffer, int totalNumTiles, unsigned char*& edgedSubTileBuffer,
                   SbRasterImage* rasterImage, SoRasterImageFile* imageFile, SbVec2i32& vpSize, GLenum format, FILE *fp);

  // Use multiple buffers
  SbBool m_multiTiled;

  SbBool m_largeImage;

  SoBase* m_scene;

  static void putHex(FILE *fp, unsigned char val, int &hexPos);
  int m_savedContextID;

  void commonConstructor(SoGLRenderAction* act, SbBool defaultRA = FALSE);
  SbBool m_shareContextSuccessful;
  SoGLGraphicConfigTemplate* m_currentGraphicConfigTemplate;
  SbBool m_currentGraphicConfigTemplateChanged;

  // Anti aliasing
  int m_minFsaaBits;
  int m_maxFsaaBits;
  SoGraphicConfigTemplate::Preference m_fsaaPref;
  SbBool m_isFsaaEnable;

private:
  // The list of offscreen renderers and their render actions
  static SoOffRenderItem* findOffRender(const SoOffscreenRenderer *rnd);
  static const SbViewportRegion& getCorrectVP(const SoOffscreenRenderer *rnd);

  static SbThreadSpinlock s_renderListMutex;
  static SbPList s_renderList;

};



/**
 *
 * @VSGEXT Class encapsulating offscreen tile properties
 *
 * @ingroup General
 *
 * This class is used to store information about each tile generated by the offscreen renderer.
 *
 *
 * @SEE_ALSO
 *    SoOffscreenRenderer,
 *    SoOffscreenTileObserver
 *
 *
 */

#include <Inventor/SoOffscreenRenderer.h>

class INVENTOR_API SoOffscreenTileProperty {

public:

  /**
   * Returns the origin of the tile.
   */
  const SbVec2i32& getOrigin() const;


  /**
   * Returns the size of the tile.
   */
  const SbVec2i32& getSize() const;

  /**
  * Returns a the tile buffer and sets the buffer size value given by reference.
  * [OIVJAVA-WRAPPER PACK{BufferInfo}]
  * [OIVJAVA-WRAPPER-RETURN-TYPE NAME{buffer}]
  */
  const unsigned char* getBuffer(int& bufferSize) const;


  /**
   * Returns the number of tiles renderered so far.
   */
  int getTileCount() const;



SoINTERNAL public:

  void setOrigin(SbVec2i32& origin);
  void setSize(SbVec2i32& size);
  void setBuffer(const unsigned char* buffer, int bufferSize);
  void setTileCount(int count);

private:
  SbVec2i32 m_origin;
  SbVec2i32 m_size;
  const unsigned char* m_buffer;
  int m_tileCount;
  int m_bufferSize;
};


/**
 *
 * @VSGEXT Abstract class for monitoring the rendering of tiles (sub-images).
 *
 * @ingroup General
 *
 * This abstract class is used for creating specific code that will be called by the class
 * SoOffscreenRenderer when it generates a tile.
 * SoOffscreenTileObserver will be given information about the current tile at each call by
 * SoOffscreenRenderer.
 * The application must define and instantiate a class derived from this class.
 *
 *
 * @SEE_ALSO
 *    SoOffscreenRenderer,
 *    SoOffscreenTileProperty
 *
 *
 */
class INVENTOR_API SoOffscreenTileObserver {

public:
  virtual ~SoOffscreenTileObserver() {}

  /**
   * Called as soon as a tile has been generated.
   * @B numTiles @b is the total number of tiles that will be rendered.
   * Must return an AbortCode value to indicate whether rendering should continue or not.
   */
  virtual SoOffscreenRenderer::AbortCode tileUpdated(SoOffscreenRenderer* offscreen,
                                                     SoOffscreenTileProperty* tileProperty,
                                                     int numTiles) = 0;
};




#endif // _SO_OFFSCREEN_RENDERER_

