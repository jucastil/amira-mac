/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : R. ALBOU (Feb 1998)
**=======================================================================*/

                                                             /* include files */
#ifndef _SO_IMAGE_
#define _SO_IMAGE_

#include <Inventor/nodes/SoShape.h>

#include <Inventor/fields/SoSFFilePathString.h>
#include <Inventor/fields/SoSFImage.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoTexture.h>
#include <Inventor/image/SbRasterImage.h>

#include <Inventor/sys/SoGLType.h>

/*----------------------------------------------------------------------------*/

class SoGetPrimitiveCountAction;
class SoGLRenderAction;
class SoSensor;
class SoFieldSensor;

/**
 * @VSGEXT Displays an image that always faces the camera.
 * 
 * @ingroup ShapeNodes
 * 
 * @DESCRIPTION
 *   The SoImage node allows you to display an image without using the texture
 *   facilities. The image is a 2D image attached to a 3D justification point. The
 *   justification point is at (0,0,0) after applying the current transformation. The
 *   image is always parallel to the screen. The image is @I not @i resized when the
 *   render window is resized. 
 *   
 *   The image can be read from the file specified by the #filename field. Once
 *   the image has been read, the #image field contains the image data.
 *   However, this field is marked so the image is not written out when the image
 *   node is written to a file. To turn off the image, set the #filename field
 *   to an empty string ("").
 *   
 *   Images can also be specified in memory by setting the #image field to
 *   contain the image data. Doing so resets the file name to the empty string.
 *   
 *   This node can be useful for placing a logo in the scene, or for attaching an icon
 *   or marker to a 3D point. 
 *   
 *   By default (or when the width and height fields are both set to negative values),
 *   the actual size of the image is used. If the width and/or height are specified,
 *   the image is scaled to the specified size in pixels.
 *   
 *   Note that SoImage automatically enables OpenGL blending for 2 or 4 component
 *   images, but it does not set the blending function. However, if you have enabled
 *   non-screendoor transparency, or if any of the textures in your scene graph have
 *   2 or 4 components, the blending function @I will @i be set.
 *
 *   Note that the position of the image on the screen depends on the current
 *   camera settings, so generally this node should not be render cached.
 *   SoImage nodes prohibit auto-caching, so that no SoSeparator (or other render
 *   caching node) above an SoImage in the scene graph will automatically create a
 *   render cache.  This can significantly affect performance and applications should
 *   try to keep nodes that @I can @i be render cached (especially geometry nodes)
 *   under a different SoSeparator.
 *
 *   Shape Antialiasing type is SoShape::POINTS.
 *
 * @FILE_FORMAT_DEFAULT
 *    Image {
 *    @TABLE_FILE_FORMAT
 *       @TR filename        @TD " "
 *       @TR image           @TD 0 0 0
 *       @TR horAlignment    @TD LEFT
 *       @TR vertAlignment   @TD BOTTOM
 *       @TR width           @TD -1
 *       @TR height          @TD -1
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction @BR
 *        Draws the image parallel to the screen.
 * 
 *    SoRayPickAction @BR
 *        Picks the image based on the current transformation and view.
 * 
 *    SoGetPrimitiveCountAction @BR
 *        Increments the number of images by 1.
 * 
 * 
 * @SEE_ALSO
 *    SoFullSceneAntialiasing,
 *    SoMarkerSet,
 *    SoTexture2
 * 
 * 
 */ 

class INVENTOR_API SoImage : public SoShape {

  SO_NODE_HEADER(SoImage);

 public:

   /** Horizontal alignment */
  enum HorAlignment {
    /**
     *  The image is left justified. 
     */
    LEFT,
    /**
     *  The image is center justified. 
     */
    CENTER,
    /**
     *  The image is right justified. 
     */
    RIGHT
  };
  
  /** Vertical alignment */
  enum VertAlignment {
    /**
     *  The image is bottom justified. 
     */
    BOTTOM,
    /**
     *  The image is middle justified. 
     */
    HALF,
    /**
     *  The image is top justified. 
     */
    TOP
  };

  /** File type */
  enum FileType {
    /**
     *  The file type is unknown. 
     */
    UNKNOWN = SoTexture::UNKNOWN,
    /**
     *  The file type is RGB. 
     */
    RGB = SoTexture::RGB,
    /**
     *  The file type is SGI. 
     */
    SGI = SoTexture::SGI,
    /**
     *  The file type is TIFF. 
     */
    TIFF = SoTexture::TIFF,
    /**
     *  The file type is GIF. 
     */
    GIF = SoTexture::GIF,
    /**
     *  The file type is JPEG. 
     */
    JPEG = SoTexture::JPEG,
    /**
     *  The file type is BMP. 
     */
    BMP = SoTexture::BMP,
    /**
     *  The file type is PNG. 
     */
    PNG = SoTexture::PNG,
    /**
     *  The file type is JPEG2000. 
     */
    JPEG2000 = SoTexture::JPEG2000,
    /**
       *  The file type is PGX. 
       */
    PGX = SoTexture::PGX,
    /**
       *  The file type is PNM. 
       */
    PNM = SoTexture::PNM,
    /**
       *  The file type is SUN Raster. 
       */
    RAS = SoTexture::RAS,
    /**
       *  The file type is DDS (DirectDraw Surface).
       */
    DDS = SoTexture::DDS,
    /** 
       *  The file type is HDRi (High Dynamic Range). 
       */
    HDRI = SoTexture::HDRI,
    /** NUM_FILETYPES */
    NUM_FILETYPES
  };


  // Fields
  /**
   * Names file from which to read image. The standard image file formats 
   * are supported. See SoRasterImageRW for the list. If the filename is not an
   * absolute path name, the list of directories maintained by SoInput is searched.
   * If the texture is not found in any of those directories, then the file is
   * searched for relative to the directory from which the SoImage node was read. For
   * example, if an SoImage node with a filename of "../tofu.rgb" is read from
   * /usr/people/bob/models/food.iv, then /usr/people/bob/tofu.rgb will be read
   * (assuming tofu.rgb isn't found in the directories maintained by SoInput).
   * 
   */
  SoSFFilePathString filename;

  /**
   * Contains an in-memory representation of the image. It is either the contents of
   * the file read from filename, an image read directly from an Open Inventor file,
   * or an image set programmatically using the methods provided by SoSFImage.
   * 
   */
  SoSFImage image;
  /**
   * Horizontal alignment. 
   * For example, if the image is RIGHT BOTTOM
   * justified, the bottom right-hand corner of the image is placed at the
   * justification point. Use enum #HorAlignment. Default is LEFT.
   * 
   */
  SoSFEnum horAlignment;
  /**
   * Vertical alignment. For example, if the image is RIGHT BOTTOM
   * justified, the bottom right-hand corner of the image is placed at the
   * justification point. Use enum #VertAlignment. Default is BOTTOM.
   * 
   */
  SoSFEnum vertAlignment;

  /**
   * Width of image in pixels (optional). By default (or when the width
   * and height fields are both set to negative values), the actual size of the image
   * is used. If the width and/or height are specified, the image is scaled to the
   * specified size in pixels.
   * 
   */
  SoSFInt32 width;

  /**
   * Height of image in pixels (optional). By default (or when the width
   * and height fields are both set to negative values), the actual size of the image
   * is used. If the width and/or height are specified, the image is scaled to the
   * specified size in pixels.
   * 
   */
  SoSFInt32 height;

  /**
   * Constructor.
   */
  SoImage();

  /*----------------------------------------------------------------------------*/

 SoEXTENDER public:
  virtual void GLRender(SoGLRenderAction *action);
  virtual void rayPick(SoRayPickAction *action);
  virtual void getPrimitiveCount(SoGetPrimitiveCountAction *action);

  virtual void computeBBox(SoAction *action, SbBox3f &box, SbVec3f &center);

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

 protected:
  virtual void generatePrimitives(SoAction *action);

  // Returns TRUE if the shape should be rendered. Subclasses can
  // call this in their rendering methods to determine whether to
  // continue.
  virtual SbBool shouldGLRender(SoGLRenderAction *action,
                                SbBool isPointsOrLines = FALSE);

  // Reads stuff into instance. Returns FALSE on error.
  virtual SbBool readInstance(SoInput *in, unsigned short flags);

  int  getReadStatus()             { return m_readStatus; }
  void setReadStatus(SbBool flag)  { m_readStatus = flag; }

  // Destructor
  virtual ~SoImage();

 private:
  SbBool m_readStatus;
  
  // These keep the image and filename fields in sync.
  SoFieldSensor *m_imageSensor;
  SoFieldSensor *m_filenameSensor;
  
  static void imageChangedCB(void *, SoSensor *);
  static void filenameChangedCB(void *, SoSensor *);

  // Compute the limits of the image
  void computeImageLimits(SoAction *action, SbBox3f &box);

  // Compute the limits of the image
  void computeImageLimitsPoints(SoAction *action,SbVec3f &p0,
                                SbVec3f &p1, SbVec3f &p2, SbVec3f &p3);
 
  // Draw the image with GL
  void drawImage(SoState *state, int widthPixels, int heightPixels);
 
  // Return the left bottom point of the image in pixels
  SbVec3f getLeftBottomPoint(SbVec3f &origPixels, 
                             int widthPixels, int heightPixels);
 
  // Return the requested size of the image.
  int getWidth();
  int getHeight();
 
  FileType m_filetype; 
 
};
/*----------------------------------------------------------------------------*/

#endif /* _SO_IMAGE_ */

