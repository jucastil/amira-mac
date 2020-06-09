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


#ifndef  _SO_SCALE_2_DRAGGER_
#define  _SO_SCALE_2_DRAGGER_

#include <Inventor/SbLinear.h>
#include <Inventor/draggers/SoDragger.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/sensors/SoSensor.h>

class SbDict;
class SbPlaneProjector;
class SoFieldSensor;

/**
 * Object you can scale in two dimensions by dragging with the mouse.
 * 
 * @ingroup draggers
 * 
 * @DESCRIPTION
 *   SoScale2Dragger is a simple dragger that scales freely and independently in two
 *   dimensions when dragged with the mouse. It moves within the x-y plane of its
 *   local space, as determined by its location in the scene graph. Transformation
 *   nodes placed before it will affect both the dragger and the plane of motion.
 *   
 *   This node has a #scaleFactor field which always reflects its size in local
 *   space. If you set the field, the dragger will change accordingly. You can also
 *   connect fields of other nodes or engines from this one to make them follow the
 *   dragger's motion.
 *   
 *   This dragger contains four parts, @B scaler @b, @B scalerActive @b,
 *   @B feedback @b, and @B feedbackActive @b.
 *   
 *   Each of these is set by default from a resource described in the Dragger
 *   Resources section of the online reference page for this class. You can change
 *   the parts in any instance of this dragger using setPart().
 *   
 *   You can make your program use different default resources for the parts by
 *   copying the file @B $OIVHOME/data/draggerDefaults/scale2Dragger.iv @b into
 *   your own directory, editing the file, and then setting the environment variable
 *   @B SO_DRAGGER_DIR @b to be a path to that directory.
 * 
 * @FILE_FORMAT_DEFAULT
 *    Scale2Dragger {
 *    @TABLE_FILE_FORMAT
 *       @TR renderCaching        @TD AUTO
 *       @TR boundingBoxCaching   @TD AUTO
 *       @TR renderCulling        @TD AUTO
 *       @TR pickCulling          @TD AUTO
 *       @TR isActive             @TD FALSE
 *       @TR scaleFactor          @TD 1 1 1
 *       @TR callbackList         @TD NULL
 *       @TR scaler               @TD \<scale2Scaler resource\>
 *       @TR scalerActive         @TD \<scale2ScalerActive resource\>
 *       @TR feedback             @TD \<scale2Feedback resource\>
 *       @TR feedbackActive       @TD \<scale2FeedbackActive resource\>
 *    @TABLE_END
 *    }
 * 
 * 
 * @DRAGGER_RESOURCES
 *    @TABLE_DRAGGER_RESOURCES
 *       @TR Resource:      @TD @B scale2Scaler @b
 *       @TR Part:          @TD scaler
 *       @TR Appearance:    @TD white photo-corners at corners of 2-by-2 square in plane of motion
 *       @TR Description:   @TD picking this initiates the scaling
 * 
 *       @TR Resource:      @TD @B scale2ScalerActive @b
 *       @TR Part:          @TD scalerActive
 *       @TR Appearance:    @TD yellow version of scaler, but with an extra yellow box
 *       @TR Description:   @TD displayed instead of scaler while in motion
 * 
 *       @TR Resource:      @TD @B scale2Feedback @b
 *       @TR Part:          @TD feedback
 *       @TR Appearance:    @TD thin purple 3-D crosshair
 *       @TR Description:   @TD shows center of scale when still
 * 
 *       @TR Resource:      @TD @B scale2FeedbackActive @b
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
 *    SoScale2UniformDragger,
 *    SoScaleUniformDragger,
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

class INVENTOR_API SoScale2Dragger : public SoDragger
{
  SO_KIT_HEADER(SoScale2Dragger);

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
  SoScale2Dragger();

  /**
   * Scale factor affecting the dragger.
   * 
   */
  SoSFVec3f scaleFactor;

 SoINTERNAL public:
  static void initClass();  // initialize the class
  static void exitClass();

 protected:

  SbPlaneProjector *planeProj; // projector for planar scaling

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

  virtual ~SoScale2Dragger();

 private:
  static const char geomBuffer[];
};    

#endif  /* _SO_SCALE_2_DRAGGER_ */



