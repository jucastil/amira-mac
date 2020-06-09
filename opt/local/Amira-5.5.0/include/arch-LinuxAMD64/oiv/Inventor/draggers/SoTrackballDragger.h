/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul Isaacs (MMM yyyy)
** Modified by : David Mott (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_TRACKBALL_DRAGGER_
#define  _SO_TRACKBALL_DRAGGER_

#include <Inventor/SbLinear.h>
#include <Inventor/SbTime.h>
#include <Inventor/sensors/SoSensor.h>
#include <Inventor/draggers/SoDragger.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFRotation.h>

class SbDict;
class SoGroup;
class SoRotation;
class SbSphereProjector;
class SbCylinderProjector;
class SbLineProjector;
class SoFieldSensor;
class SoTimerSensor;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoTrackballDragger
//
//  Trackball dragger - allows user to rotate objects.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Striped ball you can rotate or scale uniformly by dragging with the mouse.
 * 
 * @ingroup draggers
 * 
 * @DESCRIPTION
 *   SoTrackballDragger is a ball wrapped in three circular stripes. The stripes are
 *   oriented like wheels that spin around the x, y, and z axes. Drag the stripes to
 *   rotate the trackball around those axes. You do not have to hit the lines; pick
 *   anywhere within the stripe's outline. To rotate the trackball freely in 3
 *   dimensions, click the area between the stripes and then drag. An invisible but
 *   pickable sphere initiates this dragging. If the mouse is still moving when you
 *   release it, the trackball will continue to spin.
 *   
 *   Press the \<Control\> key to scale the trackball uniformly instead of rotating.
 *   
 *   Press the \<Shift\> key and the @B user axis @b appears; this is a draggable axis
 *   with an extra stripe around it. Moving the mouse along the surface of the sphere
 *   drags the 'pole' of the axis. Release the \<Shift\> key and the user axis remains;
 *   drag the new stripe for constrained rotation around the user axis. To make the
 *   user axis disappear, press \<Shift\> and drag the pole to where two of other
 *   stripes intersect. This aligns the user axis with a primary axis, at which point
 *   the user axis disappears.
 *   
 *   As you drag the trackball, it updates its #rotation field, or its
 *   #scaleFactor field if the \<Control\> key is down. As with all draggers, if
 *   you change the fields the dragger moves in response.
 *   
 *   Remember: This is @B not @b an SoTransform@B ! @b. If you want to move other
 *   objects with this dragger, you can either:
 *   
 *     - Use an SoTrackballManip, which is subclassed from SoTransform. The
 *       manipulator creates one of these draggers and uses it as the interface to edit
 *       the manipulator's fields. (see the SoTrackballManip reference page).
 *   
 *     - Use field-to-field connections to connect the fields of this dragger to those
 *       of any SoTransformation node.
 *   
 *   You can change the parts in any instance of this dragger using setPart().
 *   The default part geometries are defined as resources for this SoTrackballDragger
 *   class. They are detailed in the Dragger Resources section of the online
 *   reference page for this class. You can make your program use different default
 *   resources for the parts by copying the file
 *   @B $OIVHOME/data/draggerDefaults/trackballDragger.iv @b into your own
 *   directory, editing the file, and then setting the environment variable
 *   @B SO_DRAGGER_DIR @b to be a path to that directory.
 * 
 * @NOTES
 *    Unlike most multi-function draggers, SoTrackballDragger is not a compound
 *   dragger made up of other draggers that perform its smaller tasks. This is not
 *   because it was inappropriate, but because the trackball was written before
 *   implementation of the methods that take care of synchronizing multiple child
 *   draggers. The younger SoCenterballDragger is similar in form to the trackball,
 *   but the centerball @B is @b a compound dragger.
 * 
 * @FILE_FORMAT_DEFAULT
 *    TrackballDragger {
 *    @TABLE_FILE_FORMAT
 *       @TR renderCaching                    @TD AUTO
 *       @TR boundingBoxCaching               @TD AUTO
 *       @TR renderCulling                    @TD AUTO
 *       @TR pickCulling                      @TD AUTO
 *       @TR isActive                         @TD FALSE
 *       @TR rotation                         @TD 0 0 1 0
 *       @TR scaleFactor                      @TD 1 1 1
 *       @TR callbackList                     @TD NULL
 *       @TR surroundScale                    @TD NULL
 *       @TR antiSquish                       @TD AntiSquish {
 *       @TR                                  @TD &nbsp;sizing LONGEST_DIAGONAL 
 *       @TR                                  @TD }  
 *       @TR rotator                          @TD \<trackballRotator resource\>
 *       @TR rotatorActive                    @TD \<trackballRotatorActive resource\>
 *       @TR XRotator                         @TD \<trackballXRotator resource\>
 *       @TR XRotatorActive                   @TD \<trackballXRotatorActive resource\>
 *       @TR YRotator                         @TD \<trackballYRotator resource\>
 *       @TR YRotatorActive                   @TD \<trackballYRotatorActive resource\>
 *       @TR ZRotator                         @TD \<trackballZRotator resource\>
 *       @TR ZRotatorActive                   @TD \<trackballZRotatorActive resource\>
 *       @TR userAxis                         @TD \<trackballUserAxis resource\>
 *       @TR userAxisActive                   @TD \<trackballUserAxisActive resource\>
 *       @TR userRotator                      @TD \<trackballUserRotator resource\>
 *       @TR userRotatorActive                @TD \<trackballUserRotatorActive resource\>
 *    @TABLE_END
 *    }
 * 
 * 
 * @DRAGGER_RESOURCES
 *    @TABLE_DRAGGER_RESOURCES
 *       @TR Resource:      @TD @B trackballRotator @b
 *       @TR Part:          @TD rotator
 *       @TR Appearance:    @TD Invisible but pickable sphere
 *       @TR Description:   @TD Initiates unconstrained 3D rotation. Slightly smaller radius than the stripes,
 *                           so you must pick between the stripes to use it.
 * 
 *       @TR Resource:      @TD @B trackballRotatorActive @b
 *       @TR Part:          @TD rotatorActive
 *       @TR Appearance:    @TD Invisible sphere
 *       @TR Description:   @TD Displayed during unconstrained 3D rotation.
 * 
 *       @TR Resource:      @TD @B trackballXRotator @b
 *       @TR Part:          @TD XRotator
 *       @TR Appearance:    @TD White outline of a stripe aligned with the X axis.
 *       @TR Description:   @TD Pick this to initiate constrained rotation about the X axis.
 * 
 *       @TR Resource:      @TD @B trackballXRotatorActive @b
 *       @TR Part:          @TD XRotatorActive
 *       @TR Appearance:    @TD Yellow version of the regular XRotator
 *       @TR Description:   @TD Displayed during constrained rotation about the X axis.
 * 
 *       @TR Resource:      @TD @B trackballYRotator @b
 *       @TR Part:          @TD YRotator
 *       @TR Appearance:    @TD White outline of a stripe aligned with the Y axis.
 *       @TR Description:   @TD Pick this to initiate constrained rotation about the Y axis.
 * 
 *       @TR Resource:      @TD @B trackballYRotatorActive @b
 *       @TR Part:          @TD YRotatorActive
 *       @TR Appearance:    @TD Yellow version of the regular YRotator
 *       @TR Description:   @TD Displayed during constrained rotation about the Y axis.
 * 
 *       @TR Resource:      @TD @B trackballZRotator @b
 *       @TR Part:          @TD ZRotator
 *       @TR Appearance:    @TD White outline of a stripe aligned with the Z axis.
 *       @TR Description:   @TD Pick this to initiate constrained rotation about the Z axis.
 * 
 *       @TR Resource:      @TD @B trackballZRotatorActive @b
 *       @TR Part:          @TD ZRotatorActive
 *       @TR Appearance:    @TD Yellow version of the regular ZRotator
 *       @TR Description:   @TD Displayed during constrained rotation about the Z axis.
 * 
 *       @TR Resource:      @TD @B trackballUserAxis @b
 *       @TR Part:          @TD userAxis
 *       @TR Appearance:    @TD Thin purple line
 *       @TR Description:   @TD Displays the user axis. Dragging the @B userRotator @b rotates about this line.
 * 
 *       @TR Resource:      @TD @B trackballUserAxisActive @b
 *       @TR Part:          @TD userAxisActive
 *       @TR Appearance:    @TD Thin purple line
 *       @TR Description:   @TD Displays the user axis. Dragging the @B userRotator @b rotates about this line.
 * 
 *       @TR Resource:      @TD @B trackballUserRotator @b
 *       @TR Part:          @TD userRotator
 *       @TR Appearance:    @TD Transparent green stripe circling the user axis.
 *       @TR Description:   @TD Pick to initiate constrained rotation about the user axis.
 * 
 *       @TR Resource:      @TD @B trackballUserRotatorActive @b
 *       @TR Part:          @TD userRotatorActive
 *       @TR Appearance:    @TD Brighter green version of the regular userRotator
 *       @TR Description:   @TD Displayed during constrained rotation about the user axis.
 * 
 *    @TABLE_END
 * 
 * @CATALOG_PARTS
 *    All Parts
 *    @TABLE_CATALOG_PART
 *       @TR   callbackList       @TD   NodeKitListPart  @TD    --      @TD   yes     
 *       @TR   surroundScale      @TD   SurroundScale    @TD    --      @TD   yes     
 *       @TR   antiSquish         @TD   AntiSquish       @TD    --      @TD   no      
 *       @TR   rotator            @TD   Separator        @TD    --      @TD   yes     
 *       @TR   rotatorActive      @TD   Separator        @TD    --      @TD   yes     
 *       @TR   XRotator           @TD   Separator        @TD    --      @TD   yes     
 *       @TR   XRotatorActive     @TD   Separator        @TD    --      @TD   yes     
 *       @TR   YRotator           @TD   Separator        @TD    --      @TD   yes     
 *       @TR   YRotatorActive     @TD   Separator        @TD    --      @TD   yes     
 *       @TR   ZRotator           @TD   Separator        @TD    --      @TD   yes     
 *       @TR   ZRotatorActive     @TD   Separator        @TD    --      @TD   yes     
 *       @TR   userAxis           @TD   Separator        @TD    --      @TD   yes     
 *       @TR   userAxisActive     @TD   Separator        @TD    --      @TD   yes     
 *       @TR   userRotator        @TD   Separator        @TD    --      @TD   yes     
 *       @TR   userRotatorActive  @TD   Separator        @TD    --      @TD   yes     
 *    @TABLE_END
 * 
 *    Extra Information for List Parts from Above Table
 *    @TABLE_LIST_PART
 *       @TR   callbackList       @TD   Separator        @TD   Callback, EventCallback
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
 *    SoScaleUniformDragger,
 *    SoSpotLightDragger,
 *    SoTabBoxDragger,
 *    SoTabPlaneDragger,
 *    SoTransformBoxDragger,
 *    SoTransformerDragger,
 *    SoTranslate1Dragger,
 *    SoTranslate2Dragger
 * 
 * 
 */ 

class INVENTOR_API SoTrackballDragger : public SoDragger {

  SO_KIT_HEADER(SoTrackballDragger);

  // For making the dragger surround what lies above it.
  SO_KIT_CATALOG_ENTRY_HEADER(surroundScale);
  // For keeping the dragger even size in all 3 dimensions
  SO_KIT_CATALOG_ENTRY_HEADER(antiSquish);

  SO_KIT_CATALOG_ENTRY_HEADER(rotatorSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator);
  SO_KIT_CATALOG_ENTRY_HEADER(rotatorActive);
  SO_KIT_CATALOG_ENTRY_HEADER(XRotatorSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(XRotator);
  SO_KIT_CATALOG_ENTRY_HEADER(XRotatorActive);
  SO_KIT_CATALOG_ENTRY_HEADER(YRotatorSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(YRotator);
  SO_KIT_CATALOG_ENTRY_HEADER(YRotatorActive);
  SO_KIT_CATALOG_ENTRY_HEADER(ZRotatorSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(ZRotator);
  SO_KIT_CATALOG_ENTRY_HEADER(ZRotatorActive);

  // The userAxisRotation is not a public part.
  SO_KIT_CATALOG_ENTRY_HEADER(userAxisRotation);

  SO_KIT_CATALOG_ENTRY_HEADER(userAxisSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(userAxis);
  SO_KIT_CATALOG_ENTRY_HEADER(userAxisActive);
  SO_KIT_CATALOG_ENTRY_HEADER(userRotatorSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(userRotator);
  SO_KIT_CATALOG_ENTRY_HEADER(userRotatorActive);

 public:
  /**
   * Constructor.
   */
  SoTrackballDragger();

  /**
   * Orientation of the dragger.
   * 
   */
  SoSFRotation rotation;
  /**
   * Scale of the dragger.
   * 
   */
  SoSFVec3f scaleFactor;

  /**
   * Returns whether spin animation is enabled.
   */
  SbBool isAnimationEnabled() { return animationEnabled; }
  /**
   * Enables/disables spin animation. When spin animation is enabled, 
   * if the mouse is moving while you release it, the trackball will continue
   * to spin afterwards. By default, spin animation is enabled.
   */
  void setAnimationEnabled( SbBool newVal );

 SoINTERNAL public:
  static void         initClass();    // initialize the class
  static void exitClass();

 protected:

  // Callbacks for drag start, motion, and finish
  static void startCB(void *, SoDragger *);
  static void motionCB(void *, SoDragger *);
  static void finishCB(void *, SoDragger *);
    
  SoFieldSensor *rotFieldSensor;
  SoFieldSensor *scaleFieldSensor;
  static void fieldSensorCB( void *, SoSensor * );
  static void valueChangedCB( void *, SoDragger * );

  // Callback for pressing and releasing the meta keys
  static void metaKeyChangeCB(void *, SoDragger *);

  // These really do the work during startCB, motionCB, and finishCB
  void        dragStart();
  void        drag();
  void        dragFinish();

  void setAllPartsActive( SbBool onOrOff );

  // detach/attach any sensors, callbacks, and/or field connections.
  // Called by:            start/end of SoBaseKit::readInstance
  // and on new copy by:   start/end of SoBaseKit::copy.
  // Classes that redefine must call setUpConnections(TRUE,TRUE) 
  // at end of constructor.
  // Returns the state of the node when this was called.
  virtual SbBool setUpConnections( SbBool onOff, SbBool doItAlways = FALSE );

  virtual void setDefaultOnNonWritingFields();

  virtual ~SoTrackballDragger();

 private:

  enum State
  { INACTIVE, FREE_ROTATE, X_ROTATE, Y_ROTATE, Z_ROTATE,
    SCALE, USER_AXIS_ADJUST, USER_AXIS_ROTATE, SPINNING };
  State               currentState;     

  SbVec3f             constrainedAxis;// if so, about what axis?
  SbVec3f             userAxisVec;       // For storing the user definable
  // 'special' rotation axis.

  SbSphereProjector   *sphereProj;
  SbCylinderProjector *stripeProj;
  SbLineProjector     *lineProj;

  SbVec3f             startWorldHitPt; // used during interaction
  SbBool              ctlDown, shftDown; // keep track of meta keys
  SbVec3f             prevWorldHitPt; // used during interaction by 
  // spherical projector.
  SbMatrix            prevMotionMatrix; // used during interaction by
  // spherical projector.

  // functions which do all the work
  void        setHighlights();

  SbBool              rotateDrag();
  SbBool              scaleDrag();
  SbBool              userStripeDrag();
    
  // character strings from which the shared geometry is read
  static const char geomBuffer[];            

  // variables used for doing spinning animation
  SbBool animationEnabled;
  SbTime          prevTime;
  SbTime          spinTime;
  SbTime          scheduleRate;
  SoTimerSensor   *spinSensor;
  SbRotation      *rotBuffer;
  SbTime          *timeBuffer;
  int             firstIndex, lastIndex;
  SbVec3f         averageAxis;
  float           angleVelocity;
  SbBool          computeAverage;

  // routines used for doing spinning animation
  static  void spinSensorCB(void *, SoSensor *);
  void    spinAnimate();
  void    resetSpinStuff();

  // We record whether ball was spinning at drag start. If so, it will 
  // call ha->setHandled() in dragFinish().  This way, it won't be 
  // considered an item selection, which is usually the case when you click 
  // on an object without moving the mouse.
  SbBool  wasSpinningAtDragStart;

};

#endif /* _SO_TRACKBALL_DRAGGER_ */

