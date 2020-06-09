/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _SO_IMAGE_BACKGROUND_H_
#define _SO_IMAGE_BACKGROUND_H_

#include <Inventor/fields/SoSFFilePathString.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFImage.h>
#include <Inventor/SbString.h>

#include <Inventor/nodes/SoBackground.h>
#include <Inventor/caches/SoGLTexCacheList.h>
#include <Inventor/threads/SbThreadStorage.h>

class SoFieldSensor;
class SbThreadRWMutex;
class SbRasterImage;

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

/**
 * Image background node
 *
 * @ingroup BackgroundNodes
 *
 * @DESCRIPTION
 *  Draws a background image.
 *
 *  This node provides a convenient way of rendering an image
 *  in the background of the scene. The position options like
 *  LOWER_LEFT can be used, for example, to place a logo in
 *  the corner of the window. The STRETCH and TILE options
 *  cause the image to fill the window and automatically adjust
 *  if the window size changes.
 *
 *  Note that the SoImage node can also be used to place an
 *  image in the scene, but the position of the image is
 *  specified in 3D coordinates. This node positions images
 *  relative to the physical drawing window.
 *
 *  Generally background nodes should be placed at the
 *  beginning of the scene graph so that geometry is drawn on
 *  top of the background. Background nodes have no size, are
 *  not pickable, and do not modify the OpenGL depth buffer.
 *
 *  Another convenient feature is that this node renders
 *  correctly on a tiled display that represents a single large
 *  virtual window, for example using the MultiPipe extension
 *  (see SoXtMPExaminerViewer). The image will be stretched or
 *  tiled across the entire virtual window.
 *
 * @FILE_FORMAT_DEFAULT
 *    ImageBackground {
 *    @TABLE_FILE_FORMAT
 *       @TR filename                 @TD ""
 *       @TR image                    @TD 0 0 0 0
 *       @TR style                    @TD TILE
 *    @TABLE_END
 *    }
 *
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction @BR
 *        Renders background, does not affect state.
 *
 * @SEE_ALSO
 *    SoBackground,
 *    SoGradientBackground
 *
 *
 */

class INVENTOR_API SoImageBackground : public SoBackground {

  SO_NODE_HEADER(SoImageBackground);

public:

  /** Image background style */
  enum Style {
    /**
     *  No image is rendered.
     */
    NONE       ,
    /**
     *  Image rendered actual size, centered in window.
     */
    CENTER     ,
    /**
     *  Image rendered actual size in lower left corner.
     */
    LOWER_LEFT ,
    /**
     *  Image rendered actual size in upper left corner.
     */
    UPPER_LEFT ,
    /**
     *  Image rendered actual size in upper right corner.
     */
    UPPER_RIGHT,
    /**
     *  Image rendered actual size in lower right corner.
     */
    LOWER_RIGHT,
    /**
     *  Image stretched to fill window.
     */
    STRETCH    ,
    /**
     *  Image tiled to fill window starting from lower left corner.
     */
    TILE
  };

   // Fields:
   //
  /**
   * Names file from which to read texture image. The standard image file formats are
   * supported. See SoRasterImageRW for the list. If the
   * filename is not an absolute path name, the list of directories maintained by
   * SoInput is searched. If the texture is not found in any of those directories,
   * then the file is searched for relative to the directory from which the
   * node was read. For example, if a node with a filename of
   * "../tofu.rgb" is read from /usr/people/bob/models/food.iv, then
   * /usr/people/bob/tofu.rgb will be read (assuming tofu.rgb isn't found in the
   * directories maintained by SoInput).
   */
  SoSFFilePathString       filename;

  /**
   * Contains an in-memory representation of the texture map. It is either the
   * contents of the file read from #filename, an image read directly from an
   * Open Inventor file, or an image set programmatically using the methods provided
   * by SoSFImage.
   */
  SoSFImage        image;

  /**
   * Specifies how the image will be mapped onto the window.
   * Use enum #Style. Default is TILE.
   */
  SoSFEnum         style;

  /**
   * Creates a background image node with default settings.
   */
  SoImageBackground();

SoINTERNAL public:
  // Initializes this class for use in scene graphs. This
  // should be called after database initialization and before
  // any instance of this node is constructed.
  static void    initClass();
  static void    exitClass();

SoEXTENDER public:
  // Implement render action
  // We will inherit all other action methods from SoNode.
  // We don't need a doAction because this node has no effect
  // on traversal state (or at least it shouldn't :-).
  virtual void   GLRender(SoGLRenderAction *action);

protected:
  // Destructor. Protected to keep people from trying to delete
  // nodes, rather than using the reference count mechanism.
  virtual ~SoImageBackground();

  // Reads stuff into instance. Returns FALSE on error.
  virtual SbBool readInstance(SoInput *in, unsigned short flags);

  int  getReadStatus() const { return readStatus; }
  void setReadStatus(int s) { readStatus = s; }

private:
  // These keep the image and filename fields in sync.
  SoFieldSensor *imageSensor;
  static void	 imageChangedCB(void *, SoSensor *);
  SoFieldSensor *filenameSensor;
  static void	 filenameChangedCB(void *, SoSensor *);

  // Display list info for this texture
  SbThreadStorage< SoGLTexCacheList* > m_texList;
  SbThreadRWMutex* m_mutex;

  int readStatus;

  SbRasterImage* m_rasterImage;

  int m_numRenderCaches;
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif //SoImageBackground

