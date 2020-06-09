/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : C. HUFSCHMITT (Jul 2001)
**=======================================================================*/

#ifndef _SO_MPEGNAVRENDERER_
#define _SO_MPEGNAVRENDERER_

#include <Inventor/MPEG/SoMPEGRenderer.h>
#include <Inventor/nodes/SoCamera.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/SbBasic.h>
#include <Inventor/SbPList.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/nodes/SoRotation.h>

/*----------------------------------------------------------------------------*/

/**
 * @VSGEXT Generates MPEG output that tracks camera motion.
 * 
 * @ingroup MPEG
 * 
 * @DESCRIPTION
 *   This class generates MPEG output that tracks (i.e. follows) camera motion -- 
 *   specifically changes in the position, orientation, nearDistance, and 
 *   farDistance fields. These are the fields that can be modified by mouse
 *   movements within a viewer.
 *
 *   After SoMPEGNavRenderer::record() is called, all camera movements are
 *   recorded until SoMPEGNavRenderer::stop() is called. At that time,
 *   frames corresponding to each camera movement are rendered and stored
 *   in the MPEG output.
 *
 *   See the parent class SoMPEGRenderer for methods to specify the file and
 *   recording parameters.
 *   
 * @SEE_ALSO
 *    SoMPEGRenderer, SoMPEGFrameRenderer
 * 
 * 
 */ 

class INVENTOR_API SoMPEGNavRenderer : public SoMPEGRenderer {

 public:

  /**
   * Constructor.
   * The method SoMPEGRenderer::setSceneGraph() is called with the given argument.
   * The specified scene graph must contain a camera in order to produce correct
   * results.
   */
  SoMPEGNavRenderer(SoNode *node);

  /**
   * Destructor.
   */
  virtual ~SoMPEGNavRenderer();

  /** 
   * Sets the scene graph used for generating frames in the MPEG output.
   */ 
  virtual void setSceneGraph(SoNode *node);

  /**
   * Starts recording camera movements. All camera movements are recorded
   * until stop() is called.
   */
  void record();

  /**
   * Stops recording camera movements. Each frame corresponding
   * to a camera movement is rendered and added to the MPEG output file.
   */
  void stop();

  /**
   * Specifies whether the camera movements are adjusted to the number of 
   * frames per second. Default is FALSE.
   *
   * - FALSE: Indicates that each camera movement corresponds to one 
   *          frame in the MPEG output.
   *          The amount of time between two camera movements is not taken
   *          into consideration.
   * 
   * - TRUE: The renderer takes into account the amount
   *         of time between two camera movements for generating frames.
   *         A new camera position could be associated with 0, 1, or 
   *         several frames in the MPEG output depending on how long
   *         the camera stayed in that position during the recording
   *         period.
   *         When the MPEG is played, the camera movements will 
   *         replay at the same speed as when they were originally
   *         recorded. 
   */
  void adjustNumFramesPerSecond(SbBool flag);

  /**
   * Returns whether the camera movements are adjusted to the number
   * of frames per second.
   */
  SbBool isAdjustedNumFramesPerSecond() const;

  /**
   * Specifies the camera to be used by the MPEG renderer.
   * Setting the camera is only needed if the first camera found in the scene 
   * isn't the one that should be used. 
   */
  void setCamera(SoCamera* camera);

  /** 
   * Returns the camera currently used by the MPEG renderer.
   */
  SoCamera *getCamera();

  /*----------------------------------------------------------------------------*/

 protected:
  SbPList *getHistory ();
  
  struct CamPosition {
    SbVec3f position;
    SbRotation orientation;
    float nearDistance;
    float farDistance;
    unsigned long time;
  };
  
  static void cameraChangedCB(void *render, SoSensor *s);
  
  void searchCameraAndHeadlight();
  
 private:

  SoCamera *m_Camera;
  SoDirectionalLight *m_Light;
  SoRotation *m_LightRotation;
  SoFieldSensor *m_Sensor;
  SbBool m_AdjustFrameRate;
  SbPList *m_CamHistory;
};/*----------------------------------------------------------------------------*/

#endif /* _SO_MPEGNAVRENDERER_ */
