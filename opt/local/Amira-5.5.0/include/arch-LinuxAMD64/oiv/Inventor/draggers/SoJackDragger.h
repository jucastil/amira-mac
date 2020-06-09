/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul Isaacs (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_JACK_DRAGGER_
#define  _SO_JACK_DRAGGER_

#include <Inventor/SbLinear.h>
#include <Inventor/draggers/SoDragger.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFRotation.h>
#include <Inventor/sensors/SoSensor.h>

class SbDict;
class SoFieldSensor;

/**
 * Jack-shaped object you rotate, translate, or scale by dragging with the mouse.
 * 
 * @ingroup draggers
 * 
 * @DESCRIPTION
 *   SoJackDragger is a composite dragger in the shape of a jack from the children's
 *   game jacks. Three lines along the x, y, and z axes form the central star shape,
 *   which you can drag with the mouse to rotate the jack. Dragging any of the small
 *   cubes mounted at the end of the axes will scale the jack uniformly in all 3
 *   dimensions. At the core of the jack is an SoDragPointDragger for translating the
 *   jack.
 *   
 *   Each of these shapes is a different dragger with the default geometry changed.
 *   All of them are parts of the jack dragger, which keeps them moving together. The
 *   star is an SoRotateSphericalDragger, and dragging it updates the #rotation
 *   field of the jack dragger. The small cubes are an SoScaleUniformDragger, tied to
 *   the #scaleFactor field. The position of the SoDragPointDragger is given by
 *   the #translation field. As with all draggers, if you change the fields the
 *   dragger will move to match the new settings.
 *   
 *   @B Remember: @b This is @B not @b an SoTransform@B ! @b. If you want to move
 *   other objects with this dragger, you can either:
 *   
 *     - Use an SoJackManip, which is subclassed from SoTransform. It creates one of
 *       these draggers and uses it as the interface to change its fields. (see the
 *       SoJackManip reference page).
 *   
 *     - Use field-to-field connections to connect the fields of this dragger to those
 *       of any SoTransformation node.
 *   
 *   You can change the parts in any instance of this dragger using setPart().
 *   The default part geometries are defined as resources for this SoJackDragger
 *   class. They are detailed in the Dragger Resources section of the online
 *   reference page for this class. You can make your program use different default
 *   resources for the parts by copying the file
 *   @B $OIVHOME/data/draggerDefaults/jackDragger.iv @b into your own directory,
 *   editing the file, and then setting the environment variable
 *   @B SO_DRAGGER_DIR @b to be a path to that directory.
 * 
 * @FILE_FORMAT_DEFAULT
 *    JackDragger {
 *    @TABLE_FILE_FORMAT
 *       @TR renderCaching                              @TD AUTO
 *       @TR boundingBoxCaching                         @TD AUTO
 *       @TR renderCulling                              @TD AUTO
 *       @TR pickCulling                                @TD AUTO
 *       @TR isActive                                   @TD FALSE
 *       @TR rotation                                   @TD 0 0 1 0
 *       @TR translation                                @TD 0 0 0
 *       @TR scaleFactor                                @TD 1 1 1
 *       @TR callbackList                               @TD NULL
 *       @TR surroundScale                              @TD NULL
 *       @TR antiSquish                                 @TD AntiSquish {
 *       @TR                                            @TD   sizing BIGGEST_DIMENSION
 *       @TR                                            @TD }
 *       @TR scaler                                     @TD ScaleUniformDragger { }
 *       @TR rotator                                    @TD RotateSphericalDragger { }
 *       @TR translator                                 @TD DragPointDragger { }
 *       @TR rotator.rotator                            @TD \<jackRotatorRotator resource>
 *       @TR rotator.rotatorActive                      @TD \<jackRotatorRotatorActive resource>
 *       @TR rotator.feedback                           @TD \<jackRotatorFeedback resource>
 *       @TR rotator.feedbackActive                     @TD \<jackRotatorFeedbackActive resource>
 *       @TR scaler.scaler                              @TD \<jackScalerScaler resource>
 *       @TR scaler.scalerActive                        @TD \<jackScalerScalerActive resource>
 *       @TR scaler.feedback                            @TD \<jackScalerFeedback resource>
 *       @TR scaler.feedbackActive                      @TD \<jackScalerFeedbackActive resource>
 *       @TR translator.xTranslator.translator          @TD \<jackTranslatorLineTranslator resource>
 *       @TR translator.yTranslator.translator          @TD \<jackTranslatorLineTranslator resource>
 *       @TR translator.zTranslator.translator          @TD \<jackTranslatorLineTranslator resource>
 *       @TR translator.xTranslator.translatorActive    @TD \<jackTranslatorLineTranslatorActive resource>
 *       @TR translator.yTranslator.translatorActive    @TD \<jackTranslatorLineTranslatorActive resource>
 *       @TR translator.zTranslator.translatorActive    @TD \<jackTranslatorLineTranslatorActive resource>
 *       @TR translator.yzTranslator.translator         @TD \<jackTranslatorPlaneTranslator resource>
 *       @TR translator.xzTranslator.translator         @TD \<jackTranslatorPlaneTranslator resource>
 *       @TR translator.xyTranslator.translator         @TD \<jackTranslatorPlaneTranslator resource>
 *       @TR translator.yzTranslator.translatorActive   @TD \<jackTranslatorPlaneTranslatorActive resource>
 *       @TR translator.xzTranslator.translatorActive   @TD \<jackTranslatorPlaneTranslatorActive resource>
 *       @TR translator.xyTranslator.translatorActive   @TD \<jackTranslatorPlaneTranslatorActive resource>
 *       @TR xFeedback                                  @TD \<jackTranslatorXFeedback resource>
 *       @TR yFeedback                                  @TD \<jackTranslatorYFeedback resource>
 *       @TR zFeedback                                  @TD \<jackTranslatorZFeedback resource>
 *       @TR yzFeedback                                 @TD \<jackTranslatorYZFeedback resource>
 *       @TR xzFeedback                                 @TD \<jackTranslatorXZFeedback resource>
 *       @TR xyFeedback                                 @TD \<jackTranslatorXYFeedback resource>
 *    @TABLE_END
 *    }
 * 
 * 
 * @DRAGGER_RESOURCES
 *    @TABLE_DRAGGER_RESOURCES
 *       @TR Resource:      @TD @B jackRotatorRotator @b
 *       @TR Part:          @TD rotator.rotator
 *       @TR Appearance:    @TD The 'star' of the jack. Set of 3 white axes (lines)
 *       @TR Description:   @TD Picking star begins rotational dragging of the jackDragger.
 * 
 *       @TR Resource:      @TD @B jackRotatorRotatorActive @b
 *       @TR Part:          @TD rotator.rotatorActive
 *       @TR Appearance:    @TD Yellow version of the rotator.rotator part.
 *       @TR Description:   @TD Displayed while the jackDragger is being rotated
 * 
 *       @TR Resource:      @TD @B jackRotatorFeedback @b
 *       @TR Part:          @TD rotator.feedback
 *       @TR Appearance:    @TD Empty separator
 *       @TR Description:   @TD Removes any feedback geometry created in the constructor of the
 *                           SoRotateSphericalDragger.
 * 
 *       @TR Resource:      @TD @B jackRotatorFeedbackActive @b
 *       @TR Part:          @TD rotator.feedbackActive
 *       @TR Appearance:    @TD Empty separator
 *       @TR Description:   @TD Removes any feedbackActive geometry created in the constructor of the
 *                           SoRotateSphericalDragger.
 * 
 *       @TR Resource:      @TD @B jackScalerScaler @b
 *       @TR Part:          @TD scaler.scaler
 *       @TR Appearance:    @TD Six small white cubes, the tips of the rotator star
 *       @TR Description:   @TD Picking this initiates uniform 3D scaling of the dragger.
 * 
 *       @TR Resource:      @TD @B jackScalerScalerActive @b
 *       @TR Part:          @TD scaler.scalerActive
 *       @TR Appearance:    @TD Yellow version of the scaler.scaler resource.
 *       @TR Description:   @TD Displayed while the dragger is being scaled.
 * 
 *       @TR Resource:      @TD @B jackScalerFeedback @b
 *       @TR Part:          @TD scaler.feedback
 *       @TR Appearance:    @TD Empty separator
 *       @TR Description:   @TD Removes any feedback geometry created in the constructor of the
 *                           SoScaleUniformDragger.
 * 
 *       @TR Resource:      @TD @B jackScalerFeedbackActive @b
 *       @TR Part:          @TD scaler.feedbackActive
 *       @TR Appearance:    @TD Empty separator
 *       @TR Description:   @TD Removes any feedbackActive geometry created in the constructor of the
 *                           SoScaleUniformDragger.
 * 
 *       @TR Resource:      @TD @B jackTranslatorLineTranslator @b
 *       @TR Parts:         @TD translator.xTranslator.translator@BR
 *                               translator.yTranslator.translator@BR
 *                               translator.zTranslator.translator 
 *       @TR Appearance:    @TD Skinny white cylinder aligned with axes of motion
 *       @TR Description:   @TD Picking these parts initiates dragging in the x, y, and z linear draggers
 *                           respectively.
 * 
 *       @TR Resource:      @TD @B jackTranslatorLineTranslatorActive @b
 *       @TR Parts:         @TD translator.xTranslator.translatorActive@BR
 *                               translator.yTranslator.translatorActive@BR
 *                               translator.zTranslator.translatorActive 
 *       @TR Appearance:    @TD Skinny yellow cylinder aligned with axes of motion
 *       @TR Description:   @TD Shown during linear dragging in the x, y, and z directions respectively.
 * 
 *       @TR Resource:      @TD @B jackTranslatorPlaneTranslator @b
 *       @TR Parts:         @TD translator.yzTranslator.translator@BR
 *                               translator.xzTranslator.translator@BR
 *                               translator.xyTranslator.translator 
 *       @TR Appearance:    @TD White flattened cube, drawn in wireframe
 *       @TR Description:   @TD Picking these parts initiates dragging by the yz, xz, and xy planar draggers
 *                           respectively.
 * 
 *       @TR Resource:      @TD @B jackTranslatorPlaneTranslatorActive @b
 *       @TR Parts:         @TD translator.yzTranslator.translatorActive@BR
 *                               translator.xzTranslator.translatorActive@BR
 *                               translator.xyTranslator.translatorActive 
 *       @TR Appearance:    @TD Yellow flattened cube, drawn in wireframe
 *       @TR Description:   @TD Shown during planar dragging in the yz, xz, and xy planes respectively.
 * 
 *       @TR Resource:      @TD @B jackTranslatorXFeedback @b
 *       @TR Part:          @TD xFeedback
 *       @TR Appearance:    @TD Double-headed purple arrow
 *       @TR Description:   @TD Feedback for motion in x direction
 * 
 *       @TR Resource:      @TD @B jackTranslatorYFeedback @b
 *       @TR Part:          @TD yFeedback
 *       @TR Appearance:    @TD Double-headed purple arrow
 *       @TR Description:   @TD Feedback for motion in y direction
 * 
 *       @TR Resource:      @TD @B jackTranslatorZFeedback @b
 *       @TR Part:          @TD zFeedback
 *       @TR Appearance:    @TD Double-headed purple arrow
 *       @TR Description:   @TD Feedback for motion in z direction
 * 
 *       @TR Resource:      @TD @B jackTranslatorYZFeedback @b
 *       @TR Part:          @TD yzFeedback
 *       @TR Appearance:    @TD Semi-transparent green square in yz plane
 *       @TR Description:   @TD Feedback for motion in yz plane
 * 
 *       @TR Resource:      @TD @B jackTranslatorXZFeedback @b
 *       @TR Part:          @TD xzFeedback
 *       @TR Appearance:    @TD Semi-transparent green square in yz plane
 *       @TR Description:   @TD Feedback for motion in xz plane
 * 
 *       @TR Resource:      @TD @B jackTranslatorXYFeedback @b
 *       @TR Part:          @TD xyFeedback
 *       @TR Appearance:    @TD Semi-transparent green square in yz plane
 *       @TR Description:   @TD Feedback for motion in xy plane
 * 
 *    @TABLE_END
 * 
 * @CATALOG_PARTS
 *    All Parts
 *    @TABLE_CATALOG_PART
 *       @TR   callbackList   @TD   NodeKitListPart         @TD    --      @TD   yes     
 *       @TR   surroundScale  @TD   SurroundScale           @TD    --      @TD   yes     
 *       @TR   antiSquish     @TD   AntiSquish              @TD    --      @TD   no      
 *       @TR   scaler         @TD   ScaleUniformDragger     @TD    --      @TD   yes     
 *       @TR   rotator        @TD   RotateSphericalDragger  @TD    --      @TD   yes     
 *       @TR   translator     @TD   DragPointDragger        @TD    --      @TD   yes     
 *    @TABLE_END
 * 
 *    Extra Information for List Parts from Above Table
 *    @TABLE_LIST_PART
 *       @TR   callbackList   @TD   Separator               @TD   Callback, EventCallback
 *    @TABLE_END
 * 
 * @SEE_ALSO
 *    SoInteractionKit,
 *    SoDragger,
 *    SoCenterballDragger,
 *    SoDirectionalLightDragger,
 *    SoDragPointDragger,
 *    SoHandleBoxDragger,
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
 *    SoTransformerDragger,
 *    SoTranslate1Dragger,
 *    SoTranslate2Dragger
 * 
 * 
 */ 

class INVENTOR_API SoJackDragger : public SoDragger
{
  SO_KIT_HEADER(SoJackDragger);

  // For making the dragger surround what lies above it.
  SO_KIT_CATALOG_ENTRY_HEADER(surroundScale);
  // For keeping the dragger even size in all 3 dimensions
  SO_KIT_CATALOG_ENTRY_HEADER(antiSquish);

  SO_KIT_CATALOG_ENTRY_HEADER(scaler);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator);
  SO_KIT_CATALOG_ENTRY_HEADER(translator);

 public:
  
  /**
   * Constructor.
   */
  SoJackDragger();

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


  virtual ~SoJackDragger();

 private:
  static const char geomBuffer[];
};    

#endif  /* _SO_JACK_DRAGGER_ */

