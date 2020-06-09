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


#ifndef  _SO_TRANSFORM_BOX_DRAGGER_
#define  _SO_TRANSFORM_BOX_DRAGGER_

#include <Inventor/SbLinear.h>
#include <Inventor/draggers/SoDragger.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFRotation.h>
#include <Inventor/sensors/SoSensor.h>

class SbDict;
class SoFieldSensor;

/**
 * Box-like object you scale, rotate, and translate by dragging with the mouse.
 * 
 * @ingroup draggers
 * 
 * @DESCRIPTION
 *   SoTransformBoxDragger is a composite dragger shaped like a box with small cubes
 *   at the corners. Click and drag any of these cubes to scale the box uniformly.
 *   Drag any edge of the box to rotate the whole dragger about its center, along an
 *   axis parallel to that edge. Pick any face of the box for 2D translation in the
 *   plane of that face.
 *   
 *   Although the box looks just about like a wireframe cube, it is composed of many
 *   different simple draggers arranged in a composite assembly. When one part is
 *   dragged, the transformBox makes sure they all move together. Each of the parts
 *   of the box is a different dragger with the default geometry changed. The faces
 *   of the box are SoTranslate2Draggers, the edges are SoRotateCylindricalDraggers,
 *   and the cubes are an SoScaleUniformDragger. Drag them and the dragger will
 *   update its #translation, #rotation and #scaleFactor fields to
 *   reflect the changes. As with all draggers, if you change the fields the dragger
 *   will move to match the new settings.
 *   
 *   Remember: This is @B not @b an SoTransform@B ! @b. If you want to move other
 *   objects with this dragger, you can either:
 *   
 *     - Use an SoTransformBoxManip, which is subclassed from SoTransform. It creates
 *       one of these draggers and uses it as the interface to change its fields. (see
 *       the SoTransformBoxManip reference page).
 *   
 *     - Use field-to-field connections to connect the fields of this dragger to those
 *       of any SoTransformation node.
 *   
 *   You can change the parts in any instance of this dragger using setPart().
 *   The default part geometries are defined as resources for this
 *   SoTransformBoxDragger class. They are detailed in the Dragger Resources section
 *   of the online reference page for this class. You can make your program use
 *   different default resources for the parts by copying the file
 *   @B $OIVHOME/data/draggerDefaults/transformBoxDragger.iv @b into your own
 *   directory, editing the file, and then setting the environment variable
 *   @B SO_DRAGGER_DIR @b to be a path to that directory.
 * 
 * @FILE_FORMAT_DEFAULT
 *    TransformBoxDragger {
 *    @TABLE_FILE_FORMAT
 *       @TR renderCaching                     @TD AUTO
 *       @TR boundingBoxCaching                @TD AUTO
 *       @TR renderCulling                     @TD AUTO
 *       @TR pickCulling                       @TD AUTO
 *       @TR isActive                          @TD FALSE
 *       @TR rotation                          @TD 0 0 1 0
 *       @TR translation                       @TD 0 0 0
 *       @TR scaleFactor                       @TD 1 1 1
 *       @TR callbackList                      @TD NULL
 *       @TR surroundScale                     @TD NULL
 *       @TR antiSquish                        @TD AntiSquish {
 *       @TR                                   @TD   sizing BIGGEST_DIMENSION
 *       @TR                                   @TD }
 *       @TR scaler                            @TD ScaleUniformDragger {
 *       @TR                                   @TD 
 *       @TR rotator1                          @TD RotateCylindricalDragger {
 *       @TR                                   @TD 
 *       @TR rotator2                          @TD RotateCylindricalDragger {
 *       @TR                                   @TD 
 *       @TR rotator3                          @TD RotateCylindricalDragger {
 *       @TR                                   @TD 
 *       @TR translator1                       @TD Translate2Dragger {
 *       @TR                                   @TD }
 *       @TR translator2                       @TD Translate2Dragger {
 *       @TR                                   @TD }
 *       @TR translator3                       @TD Translate2Dragger {
 *       @TR                                   @TD }
 *       @TR translator4                       @TD Translate2Dragger {
 *       @TR                                   @TD }
 *       @TR translator5                       @TD Translate2Dragger {
 *       @TR                                   @TD }
 *       @TR translator6                       @TD Translate2Dragger {
 *       @TR                                   @TD }
 *       @TR scaler.scaler                     @TD \<transformBoxScalerScaler resource\>
 *       @TR scaler.scalerActive               @TD \<transformBoxScalerScalerActive resource\>
 *       @TR scaler.feedback                   @TD \<transformBoxScalerFeedback resource\>
 *       @TR scaler.feedbackActive             @TD \<transformBoxScalerFeedbackActive resource\>
 *       @TR rotator1.rotator                  @TD \<transformBoxRotatorRotator resource\>
 *       @TR rotator2.rotator                  @TD \<transformBoxRotatorRotator resource\>
 *       @TR rotator3.rotator                  @TD \<transformBoxRotatorRotator resource\>
 *       @TR rotator1.rotatorActive            @TD \<transformBoxRotatorRotatorActive resource\>
 *       @TR rotator2.rotatorActive            @TD \<transformBoxRotatorRotatorActive resource\>
 *       @TR rotator3.rotatorActive            @TD \<transformBoxRotatorRotatorActive resource\>
 *       @TR rotator1.feedback                 @TD \<transformBoxRotatorFeedback resource\>
 *       @TR rotator2.feedback                 @TD \<transformBoxRotatorFeedback resource\>
 *       @TR rotator3.feedback                 @TD \<transformBoxRotatorFeedback resource\>
 *       @TR rotator1.feedbackActive           @TD \<transformBoxRotatorFeedbackActive resource\>
 *       @TR rotator2.feedbackActive           @TD \<transformBoxRotatorFeedbackActive resource\>
 *       @TR rotator3.feedbackActive           @TD \<transformBoxRotatorFeedbackActive resource\>
 *       @TR translator1.translator            @TD \<transformBoxTranslatorTranslator resource\>
 *       @TR translator2.translator            @TD \<transformBoxTranslatorTranslator resource\>
 *       @TR translator3.translator            @TD \<transformBoxTranslatorTranslator resource\>
 *       @TR translator4.translator            @TD \<transformBoxTranslatorTranslator resource\>
 *       @TR translator5.translator            @TD \<transformBoxTranslatorTranslator resource\>
 *       @TR translator6.translator            @TD \<transformBoxTranslatorTranslator resource\>
 *       @TR translator1.translatorActive      @TD \<transformBoxTranslatorTranslatorActive resource\>
 *       @TR translator2.translatorActive      @TD \<transformBoxTranslatorTranslatorActive resource\>
 *       @TR translator3.translatorActive      @TD \<transformBoxTranslatorTranslatorActive resource\>
 *       @TR translator4.translatorActive      @TD \<transformBoxTranslatorTranslatorActive resource\>
 *       @TR translator5.translatorActive      @TD \<transformBoxTranslatorTranslatorActive resource\>
 *       @TR translator6.translatorActive      @TD \<transformBoxTranslatorTranslatorActive resource\>
 *       @TR translator1.xAxisFeedback         @TD \<transformBoxTranslatorXAxisFeedback resource\>
 *       @TR translator2.xAxisFeedback         @TD \<transformBoxTranslatorXAxisFeedback resource\>
 *       @TR translator3.xAxisFeedback         @TD \<transformBoxTranslatorXAxisFeedback resource\>
 *       @TR translator4.xAxisFeedback         @TD \<transformBoxTranslatorXAxisFeedback resource\>
 *       @TR translator5.xAxisFeedback         @TD \<transformBoxTranslatorXAxisFeedback resource\>
 *       @TR translator6.xAxisFeedback         @TD \<transformBoxTranslatorXAxisFeedback resource\>
 *       @TR translator1.yAxisFeedback         @TD \<transformBoxTranslatorYAxisFeedback resource\>
 *       @TR translator2.yAxisFeedback         @TD \<transformBoxTranslatorYAxisFeedback resource\>
 *       @TR translator3.yAxisFeedback         @TD \<transformBoxTranslatorYAxisFeedback resource\>
 *       @TR translator4.yAxisFeedback         @TD \<transformBoxTranslatorYAxisFeedback resource\>
 *       @TR translator5.yAxisFeedback         @TD \<transformBoxTranslatorYAxisFeedback resource\>
 *       @TR translator6.yAxisFeedback         @TD \<transformBoxTranslatorYAxisFeedback resource\>
 *    @TABLE_END
 *    }
 * 
 * 
 * @DRAGGER_RESOURCES
 *    @TABLE_DRAGGER_RESOURCES
 *       @TR Resource:      @TD @B transformBoxScalerScaler @b
 *       @TR Part:          @TD scaler.scaler
 *       @TR Appearance:    @TD Eight small white cubes at the corners of the box
 *       @TR Description:   @TD Picking this initiates uniform 3D scaling of the dragger.
 * 
 *       @TR Resource:      @TD @B transformBoxScalerScalerActive @b
 *       @TR Part:          @TD scaler.scalerActive
 *       @TR Appearance:    @TD Yellow version of the regular scaler part
 *       @TR Description:   @TD Displayed while the dragger is being scaled.
 * 
 *       @TR Resource:      @TD @B transformBoxScalerFeedback @b
 *       @TR Part:          @TD scaler.feedback
 *       @TR Appearance:    @TD Empty separator
 *       @TR Description:   @TD Removes any feedback geometry created in the constructor of the
 *                           SoScaleUniformDragger.
 * 
 *       @TR Resource:      @TD @B transformBoxScalerFeedbackActive @b
 *       @TR Part:          @TD scaler.feedbackActive
 *       @TR Appearance:    @TD Empty separator
 *       @TR Description:   @TD Removes any feedbackActive geometry created in the constructor of the
 *                           SoScaleUniformDragger.
 * 
 *       @TR Resource:      @TD @B transformBoxRotatorRotator @b
 *       @TR Parts:         @TD rotator1.rotator@BR
 *                               rotator2.rotator@BR
 *                               rotator3.rotator 
 *       @TR Appearance:    @TD Four white lines along the edges of the box
 *       @TR Description:   @TD Picking this begins rotational dragging. In each of the three rotateCylindrical
 *                           draggers, the lines of the rotator part are oriented parallel to the axis of
 *                           rotation.
 * 
 *       @TR Resource:      @TD @B transformBoxRotatorRotatorActive @b
 *       @TR Parts:         @TD rotator1.rotatorActive@BR
 *                               rotator2.rotatorActive@BR
 *                               rotator3.rotatorActive 
 *       @TR Appearance:    @TD Four yellow lines along the edges of the box
 *       @TR Description:   @TD Displayed while the dragger is being rotated
 * 
 *       @TR Resource:      @TD @B transformBoxRotatorFeedback @b
 *       @TR Parts:         @TD rotator1.feedback@BR
 *                               rotator2.feedback@BR
 *                               rotator3.feedback 
 *       @TR Appearance:    @TD Empty separator
 *       @TR Description:   @TD Removes any feedback geometry created in the constructor of the
 *                           SoRotateCylindricalDragger.
 * 
 *       @TR Resource:      @TD @B transformBoxRotatorFeedbackActive @b
 *       @TR Parts:         @TD rotator1.feedbackActive@BR
 *                               rotator2.feedbackActive@BR
 *                               rotator3.feedbackActive 
 *       @TR Appearance:    @TD Thin purple line through center of box
 *       @TR Description:   @TD Displayed to show axis of rotation during rotational dragging.
 * 
 *       @TR Resource:      @TD @B transformBoxTranslatorTranslator @b
 *       @TR Parts:         @TD translator1.translator@BR
 *                               translator2.translator@BR
 *                               translator3.translator@BR
 *                               translator4.translator@BR
 *                               translator5.translator@BR
 *                               translator6.translator 
 *       @TR Appearance:    @TD Invisible but pickable square surface
 *       @TR Description:   @TD Picking these begins 2-D translational dragging within the plane of one of the
 *                           sides of the box. The invisible squares of the six translate2Draggers are
 *                           arranged to form the sides of the box.The squares are easy to discern, although
 *                           rendered as invisible; they are bounded by the lines of the rotational dragger
 *                           parts.
 * 
 *       @TR Resource:      @TD @B transformBoxTranslatorTranslatorActive @b
 *       @TR Parts:         @TD translator1.translatorActive@BR
 *                               translator2.translatorActive@BR
 *                               translator3.translatorActive@BR
 *                               translator4.translatorActive@BR
 *                               translator5.translatorActive@BR
 *                               translator6.translatorActive 
 *       @TR Appearance:    @TD Invisible square surface
 *       @TR Description:   @TD Shown during 2-D translational dragging.
 * 
 *       @TR Resource:      @TD @B transformBoxTranslatorXAxisFeedback @b
 *       @TR Parts:         @TD translator1.xAxisFeedback@BR
 *                               translator2.xAxisFeedback@BR
 *                               translator3.xAxisFeedback@BR
 *                               translator4.xAxisFeedback@BR
 *                               translator5.xAxisFeedback@BR
 *                               translator6.xAxisFeedback 
 *       @TR Appearance:    @TD Short thin purple line
 *       @TR Description:   @TD Only shown if dragger is moving and the axis is a permissable direction of
 *                           motion. When pressing &lt;shift&gt;, motion is constrained, and this is
 *                           displayed only if the primary motion is in the X direction.
 * 
 *       @TR Resource:      @TD @B transformBoxTranslatorYAxisFeedback @b
 *       @TR Parts:         @TD translator1.yAxisFeedback@BR
 *                               translator2.yAxisFeedback@BR
 *                               translator3.yAxisFeedback@BR
 *                               translator4.yAxisFeedback@BR
 *                               translator5.yAxisFeedback@BR
 *                               translator6.yAxisFeedback 
 *       @TR Appearance:    @TD Short thin purple line
 *       @TR Description:   @TD Only shown if dragger is moving and the axis is a permissable direction of
 *                           motion. When pressing &lt;shift&gt;, motion is constrained, and this is
 *                           displayed only if the primary motion is in the Y direction.
 * 
 *    @TABLE_END
 * 
 * @CATALOG_PARTS
 *    All Parts
 *    @TABLE_CATALOG_PART
 *       @TR   callbackList   @TD   NodeKitListPart           @TD    --      @TD   yes     
 *       @TR   surroundScale  @TD   SurroundScale             @TD    --      @TD   yes     
 *       @TR   antiSquish     @TD   AntiSquish                @TD    --      @TD   no      
 *       @TR   scaler         @TD   ScaleUniformDragger       @TD    --      @TD   yes     
 *       @TR   rotator1       @TD   RotateCylindricalDragger  @TD    --      @TD   yes     
 *       @TR   rotator2       @TD   RotateCylindricalDragger  @TD    --      @TD   yes     
 *       @TR   rotator3       @TD   RotateCylindricalDragger  @TD    --      @TD   yes     
 *       @TR   translator1    @TD   Translate2Dragger         @TD    --      @TD   yes     
 *       @TR   translator2    @TD   Translate2Dragger         @TD    --      @TD   yes     
 *       @TR   translator3    @TD   Translate2Dragger         @TD    --      @TD   yes     
 *       @TR   translator4    @TD   Translate2Dragger         @TD    --      @TD   yes     
 *       @TR   translator5    @TD   Translate2Dragger         @TD    --      @TD   yes     
 *       @TR   translator6    @TD   Translate2Dragger         @TD    --      @TD   yes     
 *    @TABLE_END
 * 
 *    Extra Information for List Parts from Above Table
 *    @TABLE_LIST_PART
 *       @TR   callbackList   @TD   Separator                 @TD   Callback, EventCallback
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
 *    SoTrackballDragger,
 *    SoTransformerDragger,
 *    SoTranslate1Dragger,
 *    SoTranslate2Dragger
 * 
 * 
 */ 

class INVENTOR_API SoTransformBoxDragger : public SoDragger
{
  SO_KIT_HEADER(SoTransformBoxDragger);

  // For making the dragger surround what lies above it.
  SO_KIT_CATALOG_ENTRY_HEADER(surroundScale);
  // For keeping the dragger even size in all 3 dimensions
  SO_KIT_CATALOG_ENTRY_HEADER(antiSquish);

  SO_KIT_CATALOG_ENTRY_HEADER(scaler);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator1Sep);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator1Rot);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator1);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator2Sep);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator2Rot);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator2);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator3Sep);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator3Rot);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator3);
  SO_KIT_CATALOG_ENTRY_HEADER(translator1Sep);
  SO_KIT_CATALOG_ENTRY_HEADER(translator1Rot);
  SO_KIT_CATALOG_ENTRY_HEADER(translator1);
  SO_KIT_CATALOG_ENTRY_HEADER(translator2Sep);
  SO_KIT_CATALOG_ENTRY_HEADER(translator2Rot);
  SO_KIT_CATALOG_ENTRY_HEADER(translator2);
  SO_KIT_CATALOG_ENTRY_HEADER(translator3Sep);
  SO_KIT_CATALOG_ENTRY_HEADER(translator3Rot);
  SO_KIT_CATALOG_ENTRY_HEADER(translator3);
  SO_KIT_CATALOG_ENTRY_HEADER(translator4Sep);
  SO_KIT_CATALOG_ENTRY_HEADER(translator4Rot);
  SO_KIT_CATALOG_ENTRY_HEADER(translator4);
  SO_KIT_CATALOG_ENTRY_HEADER(translator5Sep);
  SO_KIT_CATALOG_ENTRY_HEADER(translator5Rot);
  SO_KIT_CATALOG_ENTRY_HEADER(translator5);
  SO_KIT_CATALOG_ENTRY_HEADER(translator6Sep);
  SO_KIT_CATALOG_ENTRY_HEADER(translator6Rot);
  SO_KIT_CATALOG_ENTRY_HEADER(translator6);

 public:
  /**
   * Constructor.
   */
  SoTransformBoxDragger();

  /**
   * Orientation of the dragger.
   * 
   */
  SoSFRotation rotation;
  /**
   * Position of the dragger.
   * 
   */
  SoSFVec3f    translation;
  /**
   * Scale of the dragger.
   * 
   */
  SoSFVec3f    scaleFactor;

 SoINTERNAL public:
  static void initClass();  // initialize the class
  static void exitClass();

 protected:

  SoFieldSensor *rotFieldSensor;
  SoFieldSensor *translFieldSensor;
  SoFieldSensor *scaleFieldSensor;
  static void   fieldSensorCB( void *, SoSensor * );
  static void valueChangedCB( void *, SoDragger * );

  static void invalidateSurroundScaleCB(  void *, SoDragger * );

  // detach/attach callbacks to child draggers.
  // Also set geometry of childDraggers to be our default instead of their
  // regular default, using our resources.
  // Called by:            start/end of SoBaseKit::readInstance
  // and on new copy by:   start/end of SoBaseKit::copy.
  // Classes that redefine must call setUpConnections(TRUE,TRUE) 
  // at end of constructor.
  // Returns the state of the node when this was called.
  virtual SbBool setUpConnections( SbBool onOff, SbBool doItAlways = FALSE );

  virtual void setDefaultOnNonWritingFields();

  virtual ~SoTransformBoxDragger();

 private:
  static const char geomBuffer[];
};    

#endif  /* _SO_TRANSFORM_BOX_DRAGGER_ */

