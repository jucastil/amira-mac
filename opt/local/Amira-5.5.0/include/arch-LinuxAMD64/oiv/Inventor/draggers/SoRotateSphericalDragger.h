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


#ifndef  _SO_ROTATE_SPHERICAL_DRAGGER_
#define  _SO_ROTATE_SPHERICAL_DRAGGER_

#include <Inventor/SbLinear.h>
#include <Inventor/draggers/SoDragger.h>
#include <Inventor/fields/SoSFRotation.h>
#include <Inventor/sensors/SoSensor.h>


class SbDict;
class SbSphereProjector;
class SoFieldSensor;

/**
 * Object you can rotate about a spherical surface by dragging with the mouse.
 * 
 * @ingroup draggers
 * 
 * @DESCRIPTION
 *   SoRotateSphericalDragger is a simple dragger that rotates freely in all
 *   directions. The feel of the rotation is as if you were rolling a ball. The
 *   center of rotation is the origin of the local space, determined by the dragger's
 *   location in the scene graph. Transformation nodes placed before it will affect
 *   both the dragger and the direction of motion.
 *   
 *   This node has a #rotation field which always reflects its orientation in
 *   local space. If you set the field, the dragger will rotate accordingly. You can
 *   also connect fields of other nodes or engines from this one to make them follow
 *   the dragger's orientation.
 *   
 *   This dragger contains four parts, @B rotator @b, @B rotatorActive @b,
 *   @B feedback @b, and @B feedbackActive @b.
 *   
 *   Each of these is set by default from a resource described in the Dragger
 *   Resources section of the online reference page for this class. You can change
 *   the parts in any instance of this dragger using setPart().
 *   
 *   You can make your program use different default resources for the parts by
 *   copying the file @B $OIVHOME/data/draggerDefaults/rotateSphericalDragger.iv @b
 *   into your own directory, editing the file, and then setting the environment
 *   variable @B SO_DRAGGER_DIR @b to be a path to that directory.
 * 
 * @FILE_FORMAT_DEFAULT
 *    RotateSphericalDragger {
 *    @TABLE_FILE_FORMAT
 *       @TR renderCaching        @TD AUTO
 *       @TR boundingBoxCaching   @TD AUTO
 *       @TR renderCulling        @TD AUTO
 *       @TR pickCulling          @TD AUTO
 *       @TR isActive             @TD FALSE
 *       @TR rotation             @TD 0 0 1 0
 *       @TR callbackList         @TD NULL
 *       @TR rotator              @TD \<rotateSphericalRotator resource\>
 *       @TR rotatorActive        @TD \<rotateSphericalRotatorActive resource\>
 *       @TR feedback             @TD \<rotateSphericalFeedback resource\>
 *       @TR feedbackActive       @TD \<rotateSphericalFeedbackActive resource\>
 *    @TABLE_END
 *    }
 * 
 * 
 * @DRAGGER_RESOURCES
 *    @TABLE_DRAGGER_RESOURCES
 *       @TR Resource:      @TD @B rotateSphericalRotator @b
 *       @TR Part:          @TD rotator
 *       @TR Appearance:    @TD white sphere made of three intersecting circles. Each circle is in a different
plane of local space
 *       @TR Description:   @TD picking this initiates rotation
 * 
 *       @TR Resource:      @TD @B rotateSphericalRotatorActive @b
 *       @TR Part:          @TD rotatorActive
 *       @TR Appearance:    @TD yellow version of rotator
 *       @TR Description:   @TD displayed while in motion instead of the rotator
 * 
 *       @TR Resource:      @TD @B rotateSphericalFeedback @b
 *       @TR Part:          @TD feedback
 *       @TR Appearance:    @TD thin purple 3-D crosshairs at origin
 *       @TR Description:   @TD shows center of rotation when not moving
 * 
 *       @TR Resource:      @TD @B rotateSphericalFeedbackActive @b
 *       @TR Part:          @TD feedbackActive
 *       @TR Appearance:    @TD thin, slightly brighter purple 3-D crosshairs at origin
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
 *    SoRotateDiscDragger,
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

class INVENTOR_API SoRotateSphericalDragger : public SoDragger
{
  SO_KIT_HEADER(SoRotateSphericalDragger);

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
  SoRotateSphericalDragger();

  /**
   * Orientation of the dragger.
   * 
   */
  SoSFRotation rotation;

  /**
   * Sets a different sphere projector. See the SbSphereProjector reference
   * pages to find out how each kind affects the feel of your dragger's motion. The
   * default uses an SbSpherePlaneProjector.
   * 
   * Passing in NULL will cause the default type of projector to be used. Any
   * projector you pass in will be deleted by this dragger when this dragger is
   * deleted. Note that the center and radius of the sphere are determined by the
   * dragger, based on the origin of the local space and the distance between the
   * initial mouse click and that origin.
   */
  void                        setProjector(SbSphereProjector *p);
  /**
   * Gets the sphere projector.
   */
  const SbSphereProjector *   getProjector() const     { return sphereProj; }

 SoINTERNAL public:
  static void         initClass();    // initialize the class
  static void         exitClass();

 protected:

  SbMatrix        prevMotionMatrix; // used during interaction
  SbVec3f         prevWorldHitPt; // used during interaction
  SbSphereProjector   *sphereProj;    // Sphere projector to use.
  SbBool              userProj;       // using a user defined projector?

  // Redefines this to also copy the projector.
  // The projector needs to be copied since the user can set it.
  virtual void        copyContents(const SoFieldContainer *fromFC,
                                   SbBool copyConnections);

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

  virtual ~SoRotateSphericalDragger();

 private:
  // Default geometry
  static const char geomBuffer[];

};    


#endif  /* _SO_ROTATE_SPHERICAL_DRAGGER_ */



