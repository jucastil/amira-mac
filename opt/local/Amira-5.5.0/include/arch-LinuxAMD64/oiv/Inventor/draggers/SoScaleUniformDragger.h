/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul Isaacs (MMM yyyy)
** Modified by : Howard Look (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_SCALE_UNIFORM_DRAGGER_
#define  _SO_SCALE_UNIFORM_DRAGGER_

#include <Inventor/SbLinear.h>
#include <Inventor/draggers/SoDragger.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/sensors/SoSensor.h>

class SbDict;
class SbLineProjector;
class SoFieldSensor;

/**
 * Object you can scale uniformly in 3D by dragging with the mouse.
 * 
 * @ingroup draggers
 * 
 * @DESCRIPTION
 *   SoScaleUniformDragger is a simple dragger that scales uniformly in all 3
 *   dimensions when dragged with the mouse. The local space is determined by its
 *   location in the scene graph. Transformation nodes placed before it will affect
 *   both the dragger and the plane of motion.This node has a #scaleFactor
 *   field which always reflects its size in local space. If you set the field, the
 *   dragger will change accordingly. You can also connect fields of other nodes or
 *   engines from this one to make them follow the dragger's motion.This dragger
 *   contains four parts, @B scaler @b, @B scalerActive @b, @B feedback @b, and
 *   @B feedbackActive @b.Each of these is set by default from a resource described
 *   in the Dragger Resources section of the online reference page for this class.
 *   You can change the parts in any instance of this dragger using @B setPart @b().
 *   You can make your program use different default resources for the parts by
 *   copying the file $OIVHOME/data/draggerDefaults/scaleUniformDragger.iv into your
 *   own directory, editing the file, and then setting the environment variable
 *   SO_DRAGGER_DIR to be a path to that directory.
 * 
 * @FILE_FORMAT_DEFAULT
 *    ScaleUniformDragger {
 *    @TABLE_FILE_FORMAT
 *       @TR renderCaching        @TD AUTO
 *       @TR boundingBoxCaching   @TD AUTO
 *       @TR renderCulling        @TD AUTO
 *       @TR pickCulling          @TD AUTO
 *       @TR isActive             @TD FALSE
 *       @TR scaleFactor          @TD 1 1 1
 *    @TABLE_END
 *    }
 * 
 * 
 * @DRAGGER_RESOURCES
 *    @TABLE_DRAGGER_RESOURCES
 *       @TR Resource:      @TD @B scaleUniformScaler @b
 *       @TR Part:          @TD scaler
 *       @TR Appearance:    @TD 8 small white cubes at the corners of a larger 2x2x2 cube.
 *       @TR Description:   @TD picking this initiates the scaling
 * 
 *       @TR Resource:      @TD @B scaleUniformScalerActive @b
 *       @TR Part:          @TD scalerActive
 *       @TR Appearance:    @TD yellow version of scaler, but with extra yellow box connecting corners
 *       @TR Description:   @TD displayed instead of scaler while in motion
 * 
 *       @TR Resource:      @TD @B scaleUniformFeedback @b
 *       @TR Part:          @TD feedback
 *       @TR Appearance:    @TD thin purple 3-D crosshair
 *       @TR Description:   @TD shows center of scale when still
 * 
 *       @TR Resource:      @TD @B scaleUniformFeedbackActive @b
 *       @TR Part:          @TD feedbackActive
 *       @TR Appearance:    @TD thin, slightly brighter purple 3-D crosshair
 *       @TR Description:   @TD shows center of scale while in motion
 * 
 *    @TABLE_END
 * 
 * @CATALOG_PARTS
 *    All Parts
 *    @TABLE_CATALOG_PART
 *       @TR   callbackList    @TD   NodeKitListPart  @TD    --      @TD   yes     
 *       @TR   scaler          @TD   Separator        @TD    --      @TD   yes     
 *       @TR   scalerActive    @TD   Separator        @TD    --      @TD   yes     
 *       @TR   feedback        @TD   Separator        @TD    --      @TD   yes     
 *       @TR   feedbackActive  @TD   Separator        @TD    --      @TD   yes     
 *    @TABLE_END
 * 
 *    Extra Information for List Parts from Above Table
 *    @TABLE_LIST_PART
 *       @TR   callbackList    @TD   Separator        @TD   Callback, EventCallback
 *    @TABLE_END
 * 
 * @SEE_ALSO
 *    SoInteractionKit,
 *    SoDragger,
 *    SoCenterballDragger,
 *    SoDirectionalLightDragger,
 *    SoDragPointDragger,
 *    SoHandleBoxDragger,
 *    SoJackDragger,
 *    SoPointLightDragger,
 *    SoRotateCylindricalDragger,
 *    SoRotateDiscDragger,
 *    SoRotateSphericalDragger,
 *    SoScale1Dragger,
 *    SoScale2Dragger,
 *    SoScale2UniformDragger,
 *    SoSpotLightDragger,
 *    SoTabBoxDragger,
 *    SoTabPlaneDragger,
 *    SoTrackballDragger,
 *    SoTransformBoxDragger,
 *    SoTransformerDragger,
 *    SoTranslate1Dragger,
 *    SoTranslate2Dragger
 * 
 * 
 */ 

class INVENTOR_API SoScaleUniformDragger : public SoDragger
{
  SO_KIT_HEADER(SoScaleUniformDragger);

  SO_KIT_CATALOG_ENTRY_HEADER(scalerSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(scaler);
  SO_KIT_CATALOG_ENTRY_HEADER(scalerActive);
  SO_KIT_CATALOG_ENTRY_HEADER(feedbackSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(feedback);
  SO_KIT_CATALOG_ENTRY_HEADER(feedbackActive);

 public:
  
  /**
   * Constructor.
   */
  SoScaleUniformDragger();

  SoSFVec3f scaleFactor;

 SoINTERNAL public:
  static void initClass();  // initialize the class
  static void exitClass();

 protected:

  SbLineProjector *lineProj; // projector for linear scaling

  static void startCB( void *, SoDragger * );
  static void motionCB( void *, SoDragger * );
  static void finishCB( void *, SoDragger * );

  SoFieldSensor *fieldSensor;
  static void fieldSensorCB( void *, SoSensor * );
  static void valueChangedCB( void *, SoDragger * );

  void dragStart();
  void drag();
  void dragFinish();

  // detach/attach any sensors, callbacks, and/or field connections.
  // Called by:            start/end of SoBaseKit::readInstance
  // and on new copy by:   start/end of SoBaseKit::copy.
  // Classes that redefine must call setUpConnections(TRUE,TRUE) 
  // at end of constructor.
  // Returns the state of the node when this was called.
  virtual SbBool setUpConnections( SbBool onOff, SbBool doItAlways = FALSE );

  virtual ~SoScaleUniformDragger();

 private:
  static const char geomBuffer[];
};

#endif  /* _SO_SCALE_UNIFORM_DRAGGER_ */




