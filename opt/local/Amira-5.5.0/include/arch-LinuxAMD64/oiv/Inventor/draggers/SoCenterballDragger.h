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


#ifndef  _SO_CENTERBALL_DRAGGER_
#define  _SO_CENTERBALL_DRAGGER_

#include <Inventor/SbLinear.h>
#include <Inventor/sensors/SoSensor.h>
#include <Inventor/draggers/SoDragger.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFRotation.h>

class SoFieldSensor;
class SoInput;
class SoGetBoundingBoxAction;
class SoGetMatrixAction;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoCenterballDragger
//
//  CenterballDragger - allows user to rotate objects.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Striped ball you rotate and re-center by dragging with the mouse.
 * 
 * @ingroup draggers
 * 
 * @DESCRIPTION
 *   SoCenterballDragger is a composite dragger. Its shape is a sphere defined by
 *   three intersecting circles. Where the circles intersect (at the ends of the x, y
 *   and z axes) there are sets of small green crosshairs. Dragging a pair of
 *   crosshairs translates the entire centerball within the plane of the crosshairs.
 *   The interface of the sphere and circles is just like SoTrackballDragger.
 *   Dragging a circle rotates about a constrained axis and dragging the areas
 *   between them rotates the sphere freely about the center. An invisible but
 *   pickable sphere initiates the free-rotation dragging.
 *   
 *   When you drag the crosshairs, the #center field is updated; there is no
 *   @B translation @b field. Dragging other parts of the centerball updates the
 *   #rotation field. As with all draggers, if you change the fields the
 *   dragger moves in response.
 *   
 *   The draggers used for the crosshair parts are SoTranslate2Draggers, so pressing
 *   the \<Shift\> key allows you to constrain motion to slide along either the local
 *   @B x axis @b or @B y axis @b of that crosshair. The direction is determined
 *   by your initial mouse gesture after pressing the key. Releasing the key removes
 *   the constraint.
 *   
 *   @B Remember: @b This is @B not @b an SoTransform! If you want to move other
 *   objects with this dragger, you can either:
 *   
 *     - Use an SoCenterballManip, which is subclassed from SoTransform. The
 *       manipulator creates one of these draggers and uses it as the interface to edit
 *       the manipulator's fields. (See the SoCenterballManip reference page.)
 *   
 *     - Use field-to-field connections to connect the fields of this dragger to those
 *       of any SoTransformation node.
 *   
 *   You can change the parts in any instance of this dragger using setPart().
 *   The default part geometries are defined as resources for this
 *   SoCenterballDragger class. They are detailed in the Dragger Resources section of
 *   the online reference page for this class. You can make your program use
 *   different default resources for the parts by copying the file
 *   @B $OIVHOME/data/draggerDefaults/centerballDragger.iv @b into your own
 *   directory, editing the file, and then setting the environment variable
 *   @B SO_DRAGGER_DIR @b to be a path to that directory.
 * 
 * @FILE_FORMAT_DEFAULT
 *    CenterballDragger {
 *    @TABLE_FILE_FORMAT
 *       @TR renderCaching                     @TD AUTO
 *       @TR boundingBoxCaching                @TD AUTO
 *       @TR renderCulling                     @TD AUTO
 *       @TR pickCulling                       @TD AUTO
 *       @TR isActive                          @TD FALSE
 *       @TR rotation                          @TD 0 0 1 0
 *       @TR center                            @TD 0 0 0
 *       @TR callbackList                      @TD NULL
 *       @TR translateToCenter                 @TD MatrixTransform {
 *       @TR                                   @TD matrix 
 *       @TR                                   @TD 1 0 0 0
 *       @TR                                   @TD 0 1 0 0
 *       @TR                                   @TD 0 0 1 0
 *       @TR                                   @TD 0 0 0 1
 *       @TR                                   @TD } 
 *       @TR surroundScale                     @TD NULL
 *       @TR antiSquish                        @TD AntiSquish {
 *       @TR                                   @TD   sizing LONGEST_DIAGONAL 
 *       @TR                                   @TD } 
 *       @TR lightModel                        @TD LightModel {
 *       @TR                                   @TD   model PHONG 
 *       @TR                                   @TD } 
 *       @TR XAxis                             @TD \<centerballXAxis resource>
 *       @TR YAxis                             @TD \<centerballYAxis resource>
 *       @TR ZAxis                             @TD \<centerballZAxis resource>
 *       @TR rotator                           @TD RotateSphericalDragger {
 *       @TR                                   @TD }
 *       @TR YRotator                          @TD RotateCylindricalDragger {
 *       @TR                                   @TD }
 *       @TR ZCenterChanger                    @TD Translate2Dragger {
 *       @TR                                   @TD }
 *       @TR ZRotator                          @TD RotateCylindricalDragger {
 *       @TR                                   @TD }
 *       @TR YCenterChanger                    @TD Translate2Dragger {
 *       @TR                                   @TD }
 *       @TR XCenterChanger                    @TD Translate2Dragger {
 *       @TR                                   @TD }
 *       @TR XRotator                          @TD RotateCylindricalDragger {
 *       @TR                                   @TD }
 *       @TR rotator.rotator                   @TD \<centerballRotator resource>
 *       @TR rotator.rotatorActive             @TD \<centerballRotatorActive resource>
 *       @TR XRotator.rotator                  @TD \<centerballStripe resource>
 *       @TR YRotator.rotator                  @TD \<centerballStripe resource>
 *       @TR ZRotator.rotator                  @TD \<centerballStripe resource>
 *       @TR XRotator.rotatorActive            @TD \<centerballStripeActive resource>
 *       @TR YRotator.rotatorActive            @TD \<centerballStripeActive resource>
 *       @TR ZRotator.rotatorActive            @TD \<centerballStripeActive resource>
 *       @TR XCenterChanger.translator         @TD \<centerballCenterChanger resource>
 *       @TR YCenterChanger.translator         @TD \<centerballCenterChanger resource>
 *       @TR ZCenterChanger.translator         @TD \<centerballCenterChanger resource>
 *       @TR XCenterChanger.translatorActive   @TD \<centerballCenterChangerActive resource>
 *       @TR YCenterChanger.translatorActive   @TD \<centerballCenterChangerActive resource>
 *       @TR ZCenterChanger.translatorActive   @TD \<centerballCenterChangerActive resource>
 *       @TR XCenterChanger.xAxisFeedback      @TD \<centerballCenterXAxisFeedback resource>
 *       @TR YCenterChanger.xAxisFeedback      @TD \<centerballCenterXAxisFeedback resource>
 *       @TR ZCenterChanger.xAxisFeedback      @TD \<centerballCenterXAxisFeedback resource>
 *       @TR XCenterChanger.yAxisFeedback      @TD \<centerballCenterYAxisFeedback resource>
 *       @TR YCenterChanger.yAxisFeedback      @TD \<centerballCenterYAxisFeedback resource>
 *       @TR ZCenterChanger.yAxisFeedback      @TD \<centerballCenterYAxisFeedback resource>
 *    @TABLE_END
 *    }
 * 
 * 
 * @DRAGGER_RESOURCES
 *    @TABLE_DRAGGER_RESOURCES
 *       @TR Resource:      @TD @B centerballRotator @b
 *       @TR Part:          @TD rotator.rotator
 *       @TR Appearance:    @TD Invisible but pickable sphere
 *       @TR Description:   @TD When picked, initiates free rotation about the center point. Slightly smaller
 *                           radius than the stripes, so you must pick between the stripes to use it.
 * 
 *       @TR Resource:      @TD @B centerballRotatorActive @b
 *       @TR Part:          @TD rotator.rotatorActive
 *       @TR Appearance:    @TD Invisible sphere
 *       @TR Description:   @TD Displayed during unconstrained 3D rotation instead of centerballRotator.
 * 
 *       @TR Resource:      @TD @B centerballStripe @b
 *       @TR Parts:         @TD XRotator.rotator@BR
 *                               YRotator.rotator@BR
 *                               ZRotator.rotator 
 *       @TR Appearance:    @TD White circle aligned with rotation axis.
 *       @TR Description:   @TD When picked, initiates constrained rotation. Each rotator rotates locally about
 *                           its Y axis. The centerball contains private transform parts that orient the
 *                           draggers along three different axes.
 * 
 *       @TR Resource:      @TD @B centerballStripeActive @b
 *       @TR Parts:         @TD XRotator.rotatorActive@BR
 *                               YRotator.rotatorActive@BR
 *                               ZRotator.rotatorActive 
 *       @TR Appearance:    @TD White circle aligned with the rotation axis.
 *       @TR Description:   @TD Displayed during constrained rotation instead of the rotator part. The
 *                           centerball orients the draggers along three different axes.
 * 
 *       @TR Resource:      @TD @B centerballCenterChanger @b
 *       @TR Parts:         @TD XCenterChanger.translator@BR
 *                               YCenterChanger.translator@BR
 *                               ZCenterChanger.translator 
 *       @TR Appearance:    @TD Two sets of small green crosshairs, one located at each intersection of
axis and ball.
 *       @TR Description:   @TD When picked, initiates 2D translation of ball through space. Edits the
 *                           #center field, which becomes center for subsequent rotations. Each
 *                           translator works locally in its X-Y plane. The centerball containsprivate
 *                           transform parts that place the draggers along three different axes.
 * 
 *       @TR Resource:      @TD @B centerballCenterChangerActive @b
 *       @TR Parts:         @TD XCenterChanger.translatorActive@BR
 *                               YCenterChanger.translatorActive@BR
 *                               ZCenterChanger.translatorActive 
 *       @TR Appearance:    @TD Yellow version of centerballCenterChanger.
 *       @TR Description:   @TD Displayed during 2D translation instead of regular translator part. The
 *                           centerball places the draggers along three different axes.
 * 
 *       @TR Resource:      @TD @B centerballCenterXAxisFeedback @b
 *       @TR Parts:         @TD XCenterChanger.xAxisFeedback@BR
 *                               YCenterChanger.xAxisFeedback@BR
 *                               ZCenterChanger.xAxisFeedback 
 *       @TR Appearance:    @TD Double-headed purple arrows, one located at each intersection of axis and
ball. Located atop X axis of crosshair.
 *       @TR Description:   @TD Only shown if dragger is moving and the axis is a permitted direction of motion.
 *                           When pressing &lt;shift&gt;, motion is constrained, and this is displayed only
 *                           if the primary motion is in the X direction of the child dragger's local space.
 *                           The centerball places the draggers along three different axes; so not all of
 *                           these parts aligns with the X axis in centerball space.
 * 
 *       @TR Resource:      @TD @B centerballCenterYAxisFeedback @b
 *       @TR Parts:         @TD XCenterChanger.yAxisFeedback@BR
 *                               YCenterChanger.yAxisFeedback@BR
 *                               ZCenterChanger.yAxisFeedback 
 *       @TR Appearance:    @TD Double-headed purple arrows, one located at each intersection of axis and
ball. Located atop Y axis of crosshair.
 *       @TR Description:   @TD Only shown if dragger is moving and the axis is a permitted direction of motion.
 *                           When pressing &lt;shift&gt;, motion is constrained, and this is displayed only
 *                           if the primary motion is in the Y direction of the child dragger's local space.
 *                           The centerball places the draggers along three different axes; so not all of
 *                           these parts aligns with the Y axis in centerball space.
 * 
 *       @TR Resource:      @TD @B centerballXAxis @b
 *       @TR Part:          @TD XAxis
 *       @TR Appearance:    @TD Thin yellow line connecting left and right crosshairs.
 *       @TR Description:   @TD Feedback shown alone during rotation about X axis; displayed with
 *                           centerballYAxis and centerballZAxis while center is dragged.
 * 
 *       @TR Resource:      @TD @B centerballYAxis @b
 *       @TR Part:          @TD YAxis
 *       @TR Appearance:    @TD Thin yellow line connecting lower and upper crosshairs.
 *       @TR Description:   @TD Feedback shown alone during rotation about Y axis; displayed with
 *                           centerballXAxis and centerballZAxis while center is dragged.
 * 
 *       @TR Resource:      @TD @B centerballZAxis @b
 *       @TR Part:          @TD ZAxis
 *       @TR Appearance:    @TD Thin yellow line connecting near and far crosshairs.
 *       @TR Description:   @TD Feedback shown alone during rotation about Z axis; displayed with
 *                           centerballXAxis and centerballYAxis while center is dragged.
 * 
 *    @TABLE_END
 * 
 * @CATALOG_PARTS
 *    All Parts
 *    @TABLE_CATALOG_PART
 *       @TR   callbackList       @TD   NodeKitListPart           @TD    --      @TD   yes     
 *       @TR   translateToCenter  @TD   MatrixTransform           @TD    --      @TD   yes     
 *       @TR   surroundScale      @TD   SurroundScale             @TD    --      @TD   yes     
 *       @TR   antiSquish         @TD   AntiSquish                @TD    --      @TD   no      
 *       @TR   lightModel         @TD   LightModel                @TD    --      @TD   yes     
 *       @TR   XAxis              @TD   Separator                 @TD    --      @TD   yes     
 *       @TR   YAxis              @TD   Separator                 @TD    --      @TD   yes     
 *       @TR   ZAxis              @TD   Separator                 @TD    --      @TD   yes     
 *       @TR   rotator            @TD   RotateSphericalDragger    @TD    --      @TD   yes     
 *       @TR   YRotator           @TD   RotateCylindricalDragger  @TD    --      @TD   yes     
 *       @TR   ZCenterChanger     @TD   Translate2Dragger         @TD    --      @TD   yes     
 *       @TR   ZRotator           @TD   RotateCylindricalDragger  @TD    --      @TD   yes     
 *       @TR   YCenterChanger     @TD   Translate2Dragger         @TD    --      @TD   yes     
 *       @TR   XCenterChanger     @TD   Translate2Dragger         @TD    --      @TD   yes     
 *       @TR   XRotator           @TD   RotateCylindricalDragger  @TD    --      @TD   yes     
 *    @TABLE_END
 * 
 *    Extra Information for List Parts from Above Table
 *    @TABLE_LIST_PART
 *       @TR   callbackList       @TD   Separator                 @TD   Callback, EventCallback
 *    @TABLE_END
 * 
 * @SEE_ALSO
 *    SoInteractionKit,
 *    SoDragger,
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
 *    SoTrackballDragger,
 *    SoTransformBoxDragger,
 *    SoTranslate1Dragger,
 *    SoTranslate2Dragger
 * 
 * 
 */ 

class INVENTOR_API SoCenterballDragger : public SoDragger {

  SO_KIT_HEADER(SoCenterballDragger);

  // For making the dragger surround what lies above it.
  SO_KIT_CATALOG_ENTRY_HEADER(surroundScale);
  // For keeping the dragger even size in all 3 directions
  SO_KIT_CATALOG_ENTRY_HEADER(antiSquish);

  // Translates whole dragger to location of center.
  SO_KIT_CATALOG_ENTRY_HEADER(translateToCenter);

  SO_KIT_CATALOG_ENTRY_HEADER(lightModel);

  SO_KIT_CATALOG_ENTRY_HEADER(rotator);

  SO_KIT_CATALOG_ENTRY_HEADER(YRotator);
  SO_KIT_CATALOG_ENTRY_HEADER(ZCenterChanger);
  SO_KIT_CATALOG_ENTRY_HEADER(ZAxisSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(ZAxis);

  SO_KIT_CATALOG_ENTRY_HEADER(rotX90);

  SO_KIT_CATALOG_ENTRY_HEADER(ZRotator);
  SO_KIT_CATALOG_ENTRY_HEADER(YCenterChanger);
  SO_KIT_CATALOG_ENTRY_HEADER(YAxisSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(YAxis);

  SO_KIT_CATALOG_ENTRY_HEADER(rotY90);

  SO_KIT_CATALOG_ENTRY_HEADER(XRotator);

  SO_KIT_CATALOG_ENTRY_HEADER(rot2X90);

  SO_KIT_CATALOG_ENTRY_HEADER(XCenterChanger);
  SO_KIT_CATALOG_ENTRY_HEADER(XAxisSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(XAxis);

 public:
  /**
   * Constructor.
   */
  SoCenterballDragger();

  /**
   * Orientation of the centerball dragger.
   * 
   */
  SoSFRotation rotation;
  /**
   * Center of rotation and scale of the centerball dragger.
   * 
   */
  SoSFVec3f    center;

 SoEXTENDER public:
  // Saves the matrix that moves the center relative to the motionMatrix
  // after it calls the default SoDragger method.
  virtual void saveStartParameters();

 SoINTERNAL public:
  static void         initClass();    // initialize the class
  static void         exitClass();

 protected:
    
  SoFieldSensor *rotFieldSensor;
  SoFieldSensor *centerFieldSensor;
  static void fieldSensorCB( void *, SoSensor *);
  static void valueChangedCB( void *, SoDragger *);

  void transferCenterDraggerMotion(SoDragger *childDragger);

  // Differs from SoDragger as follows: If it has a surroundScale node with 
  // 'ignoreInBbox' set to TRUE, this means surroundScale is calculating its 
  // bbox for sizing. So we also need to ignore the 'translateToCenter' 
  // matrix. Take care of this by disabling notification of 
  // 'translateToCenter', changing it to identity, running action, 
  // and then putting everything back.
  virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void        getMatrix(SoGetMatrixAction *action);

  static void kidStartCB(  void *, SoDragger * );
  static void kidFinishCB( void *, SoDragger * );

  void setSwitches( SoDragger *activeChild );

  // detach/attach any sensors, callbacks, and/or field connections.
  // Also set geometry of childDraggers to be our default instead of their
  // regular default, using our resources.
  // Called by:            start/end of SoBaseKit::readInstance
  // and on new copy by:   start/end of SoBaseKit::copy.
  // Classes that redefine must call setUpConnections(TRUE,TRUE) 
  // at end of constructor.
  // Returns the state of the node when this was called.
  virtual SbBool setUpConnections( SbBool onOff, SbBool doItAlways = FALSE );

  virtual void setDefaultOnNonWritingFields();

  ~SoCenterballDragger();

 private:
  // Used by centerball to save initial matrix of the 'translateToCenter'
  // part when the child begins to move.
  SbMatrix startCenterMatrix;

  // character string from which the shared geometry is read
  static const char geomBuffer[];
};

#endif /* _SO_CENTERBALL_DRAGGER_ */

