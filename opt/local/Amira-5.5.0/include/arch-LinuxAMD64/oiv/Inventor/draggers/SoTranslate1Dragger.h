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


#ifndef  _SO_TRANSLATE_1_DRAGGER_
#define  _SO_TRANSLATE_1_DRAGGER_

#include <Inventor/SbLinear.h>
#include <Inventor/draggers/SoDragger.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/sensors/SoSensor.h>

class SbDict;
class SbLineProjector;
class SoFieldSensor;

/**
 * Object you can translate along a line by dragging with the mouse.
 * 
 * @ingroup draggers
 * 
 * @DESCRIPTION
 *   SoTranslate1Dragger is a simple dragger that translates in one dimension when
 *   dragged with the mouse. It moves along the x axis of its local space, determined
 *   by its location in the scene graph. Transformation nodes placed before it will
 *   affect both the dragger and the direction of motion.
 *   
 *   This node has a #translation field which always reflects its position in
 *   local space. If you set the field, the dragger will move accordingly. You can
 *   also connect fields of other nodes or engines from this one to make them follow
 *   the dragger's motion.
 *   
 *   This dragger contains four parts, @B translator @b, @B translatorActive @b,
 *   @B feedback @b, and @B feedbackActive @b.
 *   
 *   Each of these is set by default from a resource described in the Dragger
 *   Resources section of the online reference page for this class. You can change
 *   the parts in any instance of this dragger using setPart().
 *   
 *   You can make your program use different default resources for the parts by
 *   copying the file @B $OIVHOME/data/draggerDefaults/translate1Dragger.iv @b into
 *   your own directory, editing the file, and then setting the environment variable
 *   @B SO_DRAGGER_DIR @b to be a path to that directory.
 * 
 * @FILE_FORMAT_DEFAULT
 *    Translate1Dragger {
 *    @TABLE_FILE_FORMAT
 *       @TR renderCaching        @TD AUTO
 *       @TR boundingBoxCaching   @TD AUTO
 *       @TR renderCulling        @TD AUTO
 *       @TR pickCulling          @TD AUTO
 *       @TR isActive             @TD FALSE
 *       @TR translation          @TD 0 0 0
 *       @TR callbackList         @TD NULL
 *       @TR translator           @TD \<translate1Translator resource\>
 *       @TR translatorActive     @TD \<translate1TranslatorActive resource\>
 *       @TR feedback             @TD \<translate1Feedback resource\>
 *       @TR feedbackActive       @TD \<translate1FeedbackActive resource\>
 *    @TABLE_END
 *    }
 * 
 * 
 * @DRAGGER_RESOURCES
 *    @TABLE_DRAGGER_RESOURCES
 *       @TR Resource:      @TD @B translate1Translator @b
 *       @TR Part:          @TD translator
 *       @TR Appearance:    @TD white arrow
 *       @TR Description:   @TD picking this initiates translation
 * 
 *       @TR Resource:      @TD @B translate1TranslatorActive @b
 *       @TR Part:          @TD translatorActive
 *       @TR Appearance:    @TD yellow arrow
 *       @TR Description:   @TD displayed during translation instead of the translator
 * 
 *       @TR Resource:      @TD @B translate1Feedback @b
 *       @TR Part:          @TD feedback
 *       @TR Appearance:    @TD empty Separator by default
 *       @TR Description:   @TD feedback displayed when not in motion
 * 
 *       @TR Resource:      @TD @B translate1FeedbackActive @b
 *       @TR Part:          @TD feedbackActive
 *       @TR Appearance:    @TD empty Separator by default
 *       @TR Description:   @TD feedback displayed while moving
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
 *    SoTranslate2Dragger
 * 
 * 
 */ 

class INVENTOR_API SoTranslate1Dragger : public SoDragger
{
  SO_KIT_HEADER(SoTranslate1Dragger);

  SO_KIT_CATALOG_ENTRY_HEADER(translatorSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(translator);
  SO_KIT_CATALOG_ENTRY_HEADER(translatorActive);
  SO_KIT_CATALOG_ENTRY_HEADER(feedbackSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(feedback);
  SO_KIT_CATALOG_ENTRY_HEADER(feedbackActive);

 public:
  
  /**
   * Constructor.
   */
  SoTranslate1Dragger();

  /**
   * Position of the dragger.
   * 
   */
  SoSFVec3f translation;

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

  virtual ~SoTranslate1Dragger();

 private:
  static const char geomBuffer[];
};    

#endif  /* _SO_TRANSLATE_1_DRAGGER_ */

