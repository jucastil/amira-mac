/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David Beilloin (Dec 2010)
**=======================================================================*/
#ifndef _SO_OFFSCREEN_VOLUME_RENDER_H_
#define _SO_OFFSCREEN_VOLUME_RENDER_H_

#include <Inventor/fields/SoSFNode.h>
#include <Inventor/fields/SoSFVec3i32.h>
#include <Inventor/nodes/SoGroup.h>
#include <Inventor/nodes/SoOrthographicCamera.h>
#include <Inventor/SbViewportRegion.h>
#include <VolumeViz/nodes/SoVolumeData.h>

class SoBufferObject;
class SoCamera;
class SoGLTexture;
class SoFrameBufferObject;
class SoGLQuery;

/**
* @VREXT Extract data from a SoVolumeRender
*
* @ingroup VolumeVizNodes
*
* @IMPORTANT_NOTE THIS NODE REQUIRES A SPECIFIC / SEPARATE LICENSE. @BR
*
* @DESCRIPTION
* The SoOffscreenVolumeRender node extracts data by rendering one or more volumes (via SoVolumeRender)
* into a buffer that can then be used for different computation tasks.
*
* Volumes of interest are specified by a subscenegraph in #volumerenderSceneGraph.
*
* The region to be extracted is the bounding box of the scene graph specified in
* the #bboxSceneGraph field. 
*
* To implement an extraction, the application must derive a new class from SoOffscreenVolumeRender
* and implement :
* - the #boxComputed() method.  This method is called with parameters that give
* access to information about the processed box.
* - the #getNextSubBox() method. This method must return subBox size smaller than getMaxBoxSize.
* We recommend to request subbox even smaller in order to get more parallelism between extraction 
* processing (done on GPU) and application processing and reduce peak GPU memory resources used.
*
* The resolution of the extraction is controlled by #boxSize field.
* As extraction is done using GPU techniques, there is a size limit on the boxSize
* that can be extract in one call. This limit can be retreived through getMaxBoxSize call.
* 
*
* @B Limitations: @b 
* It is not possible to extract a volume displayed as an isosurface
* (via SoVolumeDataDrawStyle or SoVolumeIsosurface).
*
* @FILE_FORMAT_DEFAULT
*    SoOffscreenVolumeRender {
*    @TABLE_FILE_FORMAT
*      @TR volumerenderSceneGraph @TD NULL
*      @TR bboxSceneGraph   @TD NULL
*      @TR boxSize          @TD (64, 64, 64)
*      @TR trigger          @TD FALSE
*      @TR opacityThreshold @TD 0
*      @TR components       @TD ALPHA
*    @TABLE_END
*    }
*
* @SEE_ALSO
* SoDataSet, SoVolumeData, SoVolumeRender
*/
class VOLUMEVIZ_API SoOffscreenVolumeRender : public SoNode
{
  SO_NODE_ABSTRACT_HEADER(SoOffscreenVolumeRender);

public:
  /** Default constructor */
  SoOffscreenVolumeRender();

  /** Head of the scene graph that contains one or multiple VolumeRender node to render in 3D off-screen cube */
  SoSFNode volumerenderSceneGraph;

  /** Head of the scene graph that defines the 3D off-screen scene cube to consider in world coordinates */
  SoSFNode bboxSceneGraph;

  /** Resolution of the output data in the off-screen box */
  SoSFVec3i32 boxSize;

  /** Setting this field to TRUE will start the off-screen rendering process.
  * This field is set to FALSE when computation is finished. Default is FALSE.
  */
  SoSFBool trigger;

  /** During extraction, voxels with an opacity less than the specified value will be ignored
  * Default is 0. Valid range is [0-1].
  */
  SoSFFloat opacityThreshold;

  /** */
  enum Components
  {
    /** */
    ALPHA,
    /** */
    RGBA
  };

  /**
  * Components to get back from the offscreen render.
  * Use enum #Components. Default is ALPHA.
  */
  SoSFEnum components;

  /** 
   * Returns the maximum boxSize that can be extract in one boxComputed
   * for the current state.
   */
  SbVec3i32 getMaxBoxSize(SoState*state=NULL);

SoEXTENDER_Documented protected:
  /**
   * Called by extraction process to get iteratively the subbox inside boxSize to extract.
   * @param box to extract in ijk space. It must be contained in boxSize
   * @return FALSE when no more subbox should be extract
   */
  virtual SbBool getNextSubBox(SbBox3i32& box) = 0;

  /** Method called each time a subBox has been computed.
   * If FALSE is returned then the whole process is aborted.
   * @param action is the current applied action
   * @param data contains extracted values for the current box
   * @param box is the current box in ijk space
   * @return FALSE if the processing must be stopped
   */
  virtual SbBool boxComputed(SoGLRenderAction* action,
    SoBufferObject* data,
    const SbBox3i32& box
    ) = 0;

SoEXTENDER public:

  /** reimplement GLRender behavior to launch computation when trigger touch */
  virtual void GLRender(SoGLRenderAction *action);

SoINTERNAL public:
  // Internal:
  static void         initClass();
  static void         exitClass();

  SbBox3f getBoundingBox(SoAction* action);

  void setSliceNumber(SoState* state, int slice);
  void beginOffscreenRendering(SoState* state);
  void endOffscreenRendering(SoState* state);
  virtual void notify(SoNotList *list);

protected:
  /** Destructor */
  virtual ~SoOffscreenVolumeRender();

  /** internal use only */
  virtual int isValid() const
  { return 0; }

private:
  void adjustCameraClippingPlanes(SoCamera* camera, const SbViewportRegion& viewport, SoNode* sceneRoot, SoNode* cameraSceneGraph);
  void clear3dTexture(SoState* state, GLenum internalFormat, const SbVec3i32& tileSize);

  SbBox3f ijkToXyzBox(const SbBox3i32& ijkBox);


  SoOrthographicCamera* m_camera;

  SoGLTexture* m_texture;
  SoFrameBufferObject* m_fbo;
  SoGLQuery* m_occlusionQuery;
  bool m_emptyBox;
  SbXfBox3f m_xfExtractionBbox;
};

#endif //_SO_OFFSCREEN_VOLUME_RENDER_H_
