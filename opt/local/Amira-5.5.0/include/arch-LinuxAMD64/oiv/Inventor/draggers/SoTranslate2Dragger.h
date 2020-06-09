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


#ifndef  _SO_TRANSLATE_2_DRAGGER_
#define  _SO_TRANSLATE_2_DRAGGER_

#include <Inventor/SbLinear.h>
#include <Inventor/draggers/SoDragger.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/sensors/SoSensor.h>

class SbDict;
class SbPlaneProjector;
class SoFieldSensor;

/**
 * Object you can translate within a plane by dragging with the mouse.
 * 
 * @ingroup draggers
 * 
 * @DESCRIPTION
 *   SoTranslate2Dragger is a simple dragger that translates in two dimensions when
 *   dragged with the mouse. It moves within the x-y plane of its local space,
 *   determined by its location in the scene graph. Transformation nodes placed
 *   before it will affect both the dragger and the direction of motion.
 *   
 *   Pressing the \<Shift\> key allows you to constrain motion to either the x axis or
 *   the y axis. The direction is determined by your initial mouse gesture after
 *   pressing the key. Releasing the key removes the constraint.
 *   
 *   This node has a #translation field which always reflects its position in
 *   local space. If you set the field, the dragger will move accordingly. You can
 *   also connect fields of other nodes or engines from this one to make them follow
 *   the dragger's motion.
 *   
 *   This dragger contains six parts, @B translator @b, @B translatorActive @b,
 *   @B feedback @b, @B feedbackActive @b, @B xAxisFeedback @b, and
 *   @B yAxisFeedback @b. The last two parts are only displayed during motion, and
 *   only when their direction of motion is enabled. (Pressing the \<Shift\> key and
 *   then dragging disables one of the two directions.)
 *   
 *   Each of these is set by default from a resource described in the Dragger
 *   Resources section of the online reference page for this class. You can change
 *   the parts in any instance of this dragger using setPart().
 *   
 *   You can make your program use different default resources for the parts by
 *   copying the file @B $OIVHOME/data/draggerDefaults/translate2Dragger.iv @b into
 *   your own directory, editing the file, and then setting the environment variable
 *   @B SO_DRAGGER_DIR @b to be a path to that directory.
 * 
 * @FILE_FORMAT_DEFAULT
 *    Translate2Dragger {
 *    @TABLE_FILE_FORMAT
 *       @TR renderCaching        @TD AUTO
 *       @TR boundingBoxCaching   @TD AUTO
 *       @TR renderCulling        @TD AUTO
 *       @TR pickCulling          @TD AUTO
 *       @TR isActive             @TD FALSE
 *       @TR translation          @TD 0 0 0
 *       @TR callbackList         @TD NULL
 *       @TR translator           @TD \<translate2Translator resource\>
 *       @TR translatorActive     @TD \<translate2TranslatorActive resource\>
 *       @TR feedback             @TD \<translate2Feedback resource\>
 *       @TR feedbackActive       @TD \<translate2FeedbackActive resource\>
 *       @TR xAxisFeedback        @TD \<translate2XAxisFeedback resource\>
 *       @TR yAxisFeedback        @TD \<translate2YAxisFeedback resource\>
 *    @TABLE_END
 *    }
 * 
 * 
 * @DRAGGER_RESOURCES
 *    @TABLE_DRAGGER_RESOURCES
 *       @TR Resource:      @TD @B translate2Translator @b
 *       @TR Part:          @TD translator
 *       @TR Appearance:    @TD pair of white crossing arrows
 *       @TR Description:   @TD picking this initiates translation
 * 
 *       @TR Resource:      @TD @B translate2TranslatorActive @b
 *       @TR Part:          @TD translatorActive
 *       @TR Appearance:    @TD pair of yellow crossing arrows
 *       @TR Description:   @TD displayed during translation instead of the translator
 * 
 *       @TR Resource:      @TD @B translate2Feedback @b
 *       @TR Part:          @TD feedback
 *       @TR Appearance:    @TD empty Separator by default
 *       @TR Description:   @TD feedback displayed when not moving
 * 
 *       @TR Resource:      @TD @B translate2FeedbackActive @b
 *       @TR Part:          @TD feedbackActive
 *       @TR Appearance:    @TD empty Separator by default
 *       @TR Description:   @TD feedback displayed when moving
 * 
 *       @TR Resource:      @TD @B translate2XAxisFeedback @b
 *       @TR Part:          @TD xAxisFeedback
 *       @TR Appearance:    @TD thin purple line
 *       @TR Description:   @TD Only shown if dragger is moving and the axis is a permissable direction of
 *                           motion. When pressing &lt;shift&gt;, motion is constrained, and this is
 *                           displayed only if the primary motion is in the x direction.
 * 
 *       @TR Resource:      @TD @B translate2YAxisFeedback @b
 *       @TR Part:          @TD yAxisFeedback
 *       @TR Appearance:    @TD thin purple line
 *       @TR Description:   @TD Only shown if dragger is moving and the axis is a permissable direction of
 *                           motion. When pressing &lt;shift&gt;, motion is constrained, and this is
 *                           displayed only if the primary motion is in the y direction.
 * 
 *    @TABLE_END
 * 
 * @CATALOG_PARTS
 *    All Parts
 *    @TABLE_CATALOG_PART
 *       @TR   callbackList      @TD   NodeKitListPart  @TD    --      @TD   yes     
 *       @TR   translator        @TD   Separator        @TD    --      @TD   yes     
 *       @TR   translatorActive  @TD   Separator        @TD    --      @TD   yes     
 *       @TR   feedback          @TD   Separator        @TD    --      @TD   yes     
 *       @TR   feedbackActive    @TD   Separator        @TD    --      @TD   yes     
 *       @TR   xAxisFeedback     @TD   Separator        @TD    --      @TD   yes     
 *       @TR   yAxisFeedback     @TD   Separator        @TD    --      @TD   yes     
 *    @TABLE_END
 * 
 *    Extra Information for List Parts from Above Table
 *    @TABLE_LIST_PART
 *       @TR   callbackList      @TD   Separator        @TD   Callback, EventCallback
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
 *    SoTransformBoxDragger,
 *    SoTransformerDragger,
 *    SoTranslate1Dragger
 * 
 * 
 */ 

class INVENTOR_API SoTranslate2Dragger : public SoDragger
{
  SO_KIT_HEADER(SoTranslate2Dragger);

  SO_KIT_CATALOG_ENTRY_HEADER(translatorSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(translator);
  SO_KIT_CATALOG_ENTRY_HEADER(translatorActive);
  SO_KIT_CATALOG_ENTRY_HEADER(feedbackSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(feedback);
  SO_KIT_CATALOG_ENTRY_HEADER(feedbackActive);
  SO_KIT_CATALOG_ENTRY_HEADER(axisFeedbackSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(xAxisFeedback);
  SO_KIT_CATALOG_ENTRY_HEADER(yAxisFeedback);

 public:
  /**
   * Constructor.
   */
  SoTranslate2Dragger();

  /**
   * Position of the dragger.
   * 
   */
  SoSFVec3f translation;

 SoINTERNAL public:
  static void initClass();  // initialize the class
  static void exitClass();

 protected:

  SbVec3f         worldRestartPt; // used if SHIFT key goes down to 
  // initiate a new gesture.
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

  // Callback for pressing and releasing the meta keys
  static void metaKeyChangeCB( void *, SoDragger *);

  // detach/attach any sensors, callbacks, and/or field connections.
  // Called by:            start/end of SoBaseKit::readInstance
  // and on new copy by:   start/end of SoBaseKit::copy.
  // Classes that redefine must call setUpConnections(TRUE,TRUE) 
  // at end of constructor.
  // Returns the state of the node when this was called.
  virtual SbBool setUpConnections( SbBool onOff, SbBool doItAlways = FALSE );

  virtual ~SoTranslate2Dragger();

 private:
  int     translateDir;   // Used for 1-D translation,
  SbBool  shftDown;  // used to keep track of shift modifier key

  static const char geomBuffer[];
};    

#endif  /* _SO_TRANSLATE_2_DRAGGER_ */




