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


#ifndef  _SO_ROTATE_DISC_DRAGGER_
#define  _SO_ROTATE_DISC_DRAGGER_

#include <Inventor/SbLinear.h>
#include <Inventor/draggers/SoDragger.h>
#include <Inventor/fields/SoSFRotation.h>
#include <Inventor/sensors/SoSensor.h>

class SbDict;
class SoSwitch;
class SoTransform;
class SbPlaneProjector;
class SoFieldSensor;

/**
 * Object you can rotate like a knob by dragging with the mouse.
 * 
 * @ingroup draggers
 * 
 * @DESCRIPTION
 *   SoRotateDiscDragger is a simple dragger that rotates about the z axis of its
 *   local space. The feel of the rotation is as if you were spinning a record on a
 *   turntable or rotating the volume knob of a radio. The local space is determined
 *   by its location in the scene graph. Transformation nodes placed before it will
 *   affect both the dragger and the direction of motion.
 *   
 *   This node has a #rotation field which always reflects its orientation in
 *   local space. If you set the field, the dragger will rotate accordingly. You can
 *   also connect fields of other nodes or engines from this one to make them follow
 *   the dragger's rotation.
 *   
 *   This dragger contains four parts, @B rotator @b, @B rotatorActive @b,
 *   @B feedback @b, and @B feedbackActive @b.
 *   
 *   Each of these is set by default from a resource described in the Dragger
 *   Resources section of the online reference page for this class. You can change
 *   the parts in any instance of this dragger using setPart().
 *   
 *   You can make your program use different default resources for the parts by
 *   copying the file @B $OIVHOME/data/draggerDefaults/rotateDiscDragger.iv @b into
 *   your own directory, editing the file, and then setting the environment variable
 *   @B SO_DRAGGER_DIR @b to be a path to that directory.
 * 
 * @FILE_FORMAT_DEFAULT
 *    RotateDiscDragger {
 *    @TABLE_FILE_FORMAT
 *       @TR renderCaching        @TD AUTO
 *       @TR boundingBoxCaching   @TD AUTO
 *       @TR renderCulling        @TD AUTO
 *       @TR pickCulling          @TD AUTO
 *       @TR isActive             @TD FALSE
 *       @TR rotation             @TD 0 0 1 0
 *       @TR callbackList         @TD NULL
 *       @TR rotator              @TD \<rotateDiscRotator resource\>
 *       @TR rotatorActive        @TD \<rotateDiscRotatorActive resource\>
 *       @TR feedback             @TD \<rotateDiscFeedback resource\>
 *       @TR feedbackActive       @TD \<rotateDiscFeedbackActive resource\>
 *    @TABLE_END
 *    }
 * 
 * 
 * @DRAGGER_RESOURCES
 *    @TABLE_DRAGGER_RESOURCES
 *       @TR Resource:      @TD @B rotateDiscRotator @b
 *       @TR Part:          @TD rotator
 *       @TR Appearance:    @TD white cylinder (with axis along z-direction) made of lines
 *       @TR Description:   @TD picking this initiates rotation
 * 
 *       @TR Resource:      @TD @B rotateDiscRotatorActive @b
 *       @TR Part:          @TD rotatorActive
 *       @TR Appearance:    @TD yellow version of rotator, with added yellow cube
 *       @TR Description:   @TD displayed while in motion instead of the rotator
 * 
 *       @TR Resource:      @TD @B rotateDiscFeedback @b
 *       @TR Part:          @TD feedback
 *       @TR Appearance:    @TD thin purple line along local z-axis
 *       @TR Description:   @TD shows center of rotation when not moving
 * 
 *       @TR Resource:      @TD @B rotateDiscFeedbackActive @b
 *       @TR Part:          @TD feedbackActive
 *       @TR Appearance:    @TD thin, slightly brighter purple line along local z-axis
 *       @TR Description:   @TD shows center of rotation when moving
 * 
 *    @TABLE_END
 * 
 * @CATALOG_PARTS
 *    All Parts
 *    @TABLE_CATALOG_PART
 *       @TR   callbackList    @TD   NodeKitListPart  @TD    --      @TD   yes     
 *       @TR   rotator         @TD   Separator        @TD    --      @TD   yes     
 *       @TR   rotatorActive   @TD   Separator        @TD    --      @TD   yes     
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
 *    SoRotateSphericalDragger,
 *    SoScale1Dragger,
 *    SoScale2Dragger,
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

class INVENTOR_API SoRotateDiscDragger : public SoDragger
{
  SO_KIT_HEADER(SoRotateDiscDragger);

  SO_KIT_CATALOG_ENTRY_HEADER(rotatorSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator);
  SO_KIT_CATALOG_ENTRY_HEADER(rotatorActive);
  SO_KIT_CATALOG_ENTRY_HEADER(feedbackSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(feedback);
  SO_KIT_CATALOG_ENTRY_HEADER(feedbackActive);

 public:
  /**
   * Constructor.
   */
  SoRotateDiscDragger();

  /**
   * Orientation of the dragger.
   * 
   */
  SoSFRotation rotation;

 SoINTERNAL public:
  static void         initClass();    // initialize the class
  static void         exitClass();

 protected:

  SbPlaneProjector    *planeProj;     // projector to use

  static void startCB( void *, SoDragger * );
  static void motionCB( void *, SoDragger * );
  static void doneCB( void *, SoDragger * );

  SoFieldSensor *fieldSensor;
  static void fieldSensorCB( void *, SoSensor * );
  static void valueChangedCB( void *, SoDragger * );

  void        dragStart();
  void        drag();
  void        dragFinish();

  // detach/attach any sensors, callbacks, and/or field connections.
  // Called by:            start/end of SoBaseKit::readInstance
  // and on new copy by:   start/end of SoBaseKit::copy.
  // Classes that redefine must call setUpConnections(TRUE,TRUE) 
  // at end of constructor.
  // Returns the state of the node when this was called.
  virtual SbBool setUpConnections( SbBool onOff, SbBool doItAlways = FALSE );

  virtual ~SoRotateDiscDragger();

 private:
  // Default geometry
  static const char geomBuffer[];
};    



#endif  /* _SO_ROTATE_DISC_DRAGGER_ */



