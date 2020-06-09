/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David Beilloin (Dec 2010)
**=======================================================================*/
#if !defined _SO_UNIFORM_GRID_PROJECTION_CLIPPING_H_
#define _SO_UNIFORM_GRID_PROJECTION_CLIPPING_H_

#include <VolumeViz/nodes/SoUniformGridClipping.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/SbViewportRegion.h>

class SoCamera;
class SoOrthographicCamera;

/** 
 * @VREXT Clips a volume with the depth map projection of a shape.
 *
 * @ingroup VolumeVizNodes
 *
 * @DESCRIPTION
 * This class is an helper class derived from SoUniformGridClipping.
 * It defines its clipping texture by the depth map of the given #sceneGraph 
 * in the given #axis orientation.
 *
 * Notes:
 *   Rendering the #sceneGraph on top of the clipped volume might result in z-fighting 
 *   artefacts due to depth precision. In order to correct this issue it is necessary to use
 *   a SoPolygonOffset node before the geometry to render.
 *
 * See SoUniformGridClipping node for detailed behavior and limitations.
 *
 * @NODE_SINCE_OIV 8.6
 *
 * @FILE_FORMAT_DEFAULT
 *    UniformGridProjectionClipping {
 *    @TABLE_FILE_FORMAT
 *       @TR axis                     @TD Y
 *       @TR thickness                @TD 0
 *       @TR clipBelow                @TD FALSE
 *       @TR clipAbove                @TD TRUE
 *       @TR sceneGraph               @TD NULL
 *    @TABLE_END
 *    }
 *
 * @SEE_ALSO
 *  SoUniformGridClipping,
 *  SoVolumeClippingGroup,
 *  SoPolygonOffset
 *
 */
class VOLUMEVIZ_API SoUniformGridProjectionClipping : public SoUniformGridClipping
{

  SO_NODE_HEADER(SoUniformGridProjectionClipping);

public:
  /** Constructor */
  SoUniformGridProjectionClipping();

  /**
   * Scene graph containing shapes to project on the orthogonal plane defined by 
   * #axis field to generate the SoUniformGridClipping height map texture.
   */
  SoSFNode sceneGraph;

SoINTERNAL public:
  /** @copydoc SoUniformGridClipping::initClass */
  static void initClass();

  /** @copydoc SoUniformGridClipping::exitClass */
  static void exitClass();

  /** @copydoc SoUniformGridClipping::notify */
  virtual void notify(SoNotList *list);

  /** @copydoc SoUniformGridClipping::isCulled */
  virtual SbBool isCulled(const SbBox3f &box);

protected:

  /** Destructor */
  virtual ~SoUniformGridProjectionClipping();
  
  virtual void getMinMax(float &min, float &max);

private:
  // used to setup an orthographic camera correctly for RTT property
  void adjustCameraClippingPlanes(SoCamera* camera, const SbViewportRegion& viewport, SoNode* sceneRoot, SoNode* cameraSceneGraph=NULL);

  // generate the scenegraph responsible for clipping
  void generateClippingSceneGraph();
  void updateClippingSceneGraph();

  // internal node used to do the correct clipping representation
  SoOrthographicCamera* m_camOrtho;
  SoSeparator* m_separatorSG;
  SoSeparator* m_RTTMain;
};

#endif // _SO_UNIFORM_GRID_PROJECTION_CLIPPING_H_
