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



#ifndef  _SO_DIRECTIONAL_LIGHT_DRAGGER_
#define  _SO_DIRECTIONAL_LIGHT_DRAGGER_

#include <Inventor/SbLinear.h>
#include <Inventor/draggers/SoDragger.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFRotation.h>
#include <Inventor/sensors/SoSensor.h>

class SoFieldSensor;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoDirectionalLightDragger
//
//  This changes the direction of directional lights.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Directional icon you rotate and translate by dragging with the mouse.
 * 
 * @ingroup draggers
 * 
 * @DESCRIPTION
 *   SoDirectionalLightDragger is a composite dragger. It looks like a sun with a
 *   large arrow coming out of it. The arrow can be rotated about the sun by dragging
 *   with the mouse; its orientation is given by the #rotation field. You can
 *   also drag the sun (and the arrow with it) through 3-space. The location is
 *   stored in the #translation field.
 *   
 *   The dragger uses an SoRotateSphericalDragger for changing the rotation. Instead
 *   of using the default spherical geometry, this dragger uses an arrow shape.
 *   
 *   The sun is an SoDragPointDragger. Dragging it edits the #translation field;
 *   conversely, if you change the #translation field the sun will move to that
 *   new location, bringing the arrow with it. The sun looks and behaves just like
 *   the sun in an SoPointLightDragger, as does the @B material @b part. See the
 *   SoPointLightDragger reference page for details.
 *   
 *   @B Remember: @b This is @B not @b a light source! It just looks like one. If
 *   you want to move a light with this dragger, you can either:
 *   
 *     - Use an SoDirectionalLightManip, which is subclassed from SoLight. It creates
 *       an SoDirectionalLightDragger and uses it as the interface to change the
 *       @B direction @b of its light source (see the SoDirectionalLightManip reference
 *       page). The manipulator also edits the @B material @b part of this dragger to
 *       match the color of light the manipulator is producing. However, the directional
 *       light manipulator will ignore the #translation field, because a
 *       directional light has no location or translation field. So in this case the
 *       translation dragger merely allows you to move the physical arrow to wherever
 *       you'd like it to be.
 *   
 *     - Put an SoTransform under an SoTransformSeparator. Add the SoDirectionalLight
 *       as the next child. Use a field-to-field connection between the #rotation
 *       fields of this dragger and the transform node to synchronize the light with this
 *       dragger.
 *   
 *     - Use engines to connect the #rotation field of this dragger to the
 *       @B direction @b field of an SoDirectionalLight. Use the #rotation as
 *       input to an SoComposeMatrix engine. Then, use an SoTransformVec3f engine to
 *       apply that matrix to (0,0,-1), the default light direction.
 *   
 *   You can change the parts in any instance of this dragger using setPart().
 *   The default part geometries are defined as resources for this
 *   SoDirectionalLightDragger class. They are detailed in the Dragger Resources
 *   section of the online reference page for this class. You can make your program
 *   use different default resources for the parts by copying the file
 *   @B $OIVHOME/data/draggerDefaults/directionalLightDragger.iv @b into your own
 *   directory, editing the file, and then setting the environment variable
 *   @B SO_DRAGGER_DIR @b to be a path to that directory.
 * 
 * @FILE_FORMAT_DEFAULT
 *    DirectionalLightDragger {
 *    @TABLE_FILE_FORMAT
 *       @TR renderCaching                              @TD AUTO
 *       @TR boundingBoxCaching                         @TD AUTO
 *       @TR renderCulling                              @TD AUTO
 *       @TR pickCulling                                @TD AUTO
 *       @TR isActive                                   @TD FALSE
 *       @TR translation                                @TD 0 0 0
 *       @TR rotation                                   @TD 0 0 1 0
 *       @TR callbackList                               @TD NULL
 *       @TR material                                   @TD \<directionalLightOverallMaterial resource\>
 *       @TR translatorRotInv                           @TD NULL
 *       @TR translator                                 @TD DragPointDragger {
 *       @TR                                            @TD }
 *       @TR rotator                                    @TD RotateSphericalDragger {
 *       @TR                                            @TD }
 *       @TR rotator.rotator                            @TD \<directionalLightRotatorRotator resource\>
 *       @TR rotator.rotatorActive                      @TD \<directionalLightRotatorRotatorActive resource\>
 *       @TR rotator.feedback                           @TD \<directionalLightRotatorFeedback resource\>
 *       @TR rotator.feedbackActive                     @TD \<directionalLightRotatorFeedbackActive resource\>
 *       @TR translator.yzTranslator.translator         @TD \<directionalLightTranslatorPlaneTranslator resource\>
 *       @TR translator.xzTranslator.translator         @TD \<directionalLightTranslatorPlaneTranslator resource\>
 *       @TR translator.xyTranslator.translator         @TD \<directionalLightTranslatorPlaneTranslator resource\>
 *       @TR translator.yzTranslator.translatorActive   @TD \<directionalLightTranslatorPlaneTranslatorActive resource\>
 *       @TR translator.xzTranslator.translatorActive   @TD \<directionalLightTranslatorPlaneTranslatorActive resource\>
 *       @TR translator.xyTranslator.translatorActive   @TD \<directionalLightTranslatorPlaneTranslatorActive resource\>
 *       @TR translator.xTranslator.translator          @TD \<directionalLightTranslatorLineTranslator resource\>
 *       @TR translator.yTranslator.translator          @TD \<directionalLightTranslatorLineTranslator resource\>
 *       @TR translator.zTranslator.translator          @TD \<directionalLightTranslatorLineTranslator resource\>
 *       @TR translator.xTranslator.translatorActive    @TD \<directionalLightTranslatorLineTranslatorActive resource\>
 *       @TR translator.yTranslator.translatorActive    @TD \<directionalLightTranslatorLineTranslatorActive resource\>
 *       @TR translator.zTranslator.translatorActive    @TD \<directionalLightTranslatorLineTranslatorActive resource\>
 *    @TABLE_END
 *    }
 * 
 * 
 * @DRAGGER_RESOURCES
 *    @TABLE_DRAGGER_RESOURCES
 *       @TR Resource:      @TD @B directionalLightRotatorRotator @b
 *       @TR Part:          @TD rotator.rotator
 *       @TR Appearance:    @TD white arrow that goes through the sun
 *       @TR Description:   @TD picking this begins rotation of the arrow about the sun-shape
 * 
 *       @TR Resource:      @TD @B directionalLightRotatorRotatorActive @b
 *       @TR Part:          @TD rotator.rotatorActive
 *       @TR Appearance:    @TD yellow arrow that goes through the sun
 *       @TR Description:   @TD displayed while the arrow is being rotated
 * 
 *       @TR Resource:      @TD @B directionalLightRotatorFeedback @b
 *       @TR Part:          @TD rotator.feedback
 *       @TR Appearance:    @TD empty Separator
 *       @TR Description:   @TD this disables display of the axes that a rotateSpherical dragger uses by default
 * 
 *       @TR Resource:      @TD @B directionalLightRotatorFeedbackActive @b
 *       @TR Part:          @TD rotator.feedbackActive
 *       @TR Appearance:    @TD empty Separator
 *       @TR Description:   @TD this disables display of the axes that a rotateSpherical dragger uses by default
 * 
 *       @TR Resource:      @TD @B directionalLightOverallMaterial @b
 *       @TR Part:          @TD material
 *       @TR Appearance:    @TD white. half strength emissive, half strength diffuse
 *       @TR Description:   @TD sets material for the sun shape when stationary. Resource for the moving sun,
 *                           directionalLightTranslatorPlaneTranslatorActive, contains a yellow material for
 *                           highlighting.
 * 
 *       @TR Resource:      @TD @B directionalLightTranslatorPlaneTranslator @b
 *       @TR Parts:         @TD translator.yzTranslator.translator@BR
 *                               translator.xzTranslator.translator@BR
 *                               translator.xyTranslator.translator 
 *       @TR Appearance:    @TD sun shape with no material
 *       @TR Description:   @TD picking these parts initiates dragging by the yz, xz, and xy planar draggers
 *                           respectively.
 * 
 *       @TR Resource:      @TD @B directionalLightTranslatorPlaneTranslatorActive @b
 *       @TR Parts:         @TD translator.yzTranslator.translatorActive@BR
 *                               translator.xzTranslator.translatorActive@BR
 *                               translator.xyTranslator.translatorActive 
 *       @TR Appearance:    @TD yellow sun shape
 *       @TR Description:   @TD shown during planar dragging in the yz, xz, and xy planes respectively.
 * 
 *       @TR Resource:      @TD @B directionalLightTranslatorLineTranslator @b
 *       @TR Parts:         @TD translator.xTranslator.translator@BR
 *                               translator.yTranslator.translator@BR
 *                               translator.zTranslator.translator 
 *       @TR Appearance:    @TD white cylinder
 *       @TR Description:   @TD picking these parts initiates dragging in the x, y, and z linear draggers
 *                           respectively.
 * 
 *       @TR Resource:      @TD @B directionalLightTranslatorLineTranslatorActive @b
 *       @TR Parts:         @TD translator.xTranslator.translatorActive@BR
 *                               translator.yTranslator.translatorActive@BR
 *                               translator.zTranslator.translatorActive 
 *       @TR Appearance:    @TD yellow cylinder
 *       @TR Description:   @TD shown during linear dragging in the x, y, and z directions respectively.
 * 
 *    @TABLE_END
 * 
 * @CATALOG_PARTS
 *    All Parts
 *    @TABLE_CATALOG_PART
 *       @TR   callbackList      @TD   NodeKitListPart         @TD    --      @TD   yes     
 *       @TR   material          @TD   Material                @TD    --      @TD   yes     
 *       @TR   translatorRotInv  @TD   Rotation                @TD    --      @TD   yes     
 *       @TR   translator        @TD   DragPointDragger        @TD    --      @TD   yes     
 *       @TR   rotator           @TD   RotateSphericalDragger  @TD    --      @TD   yes     
 *    @TABLE_END
 * 
 *    Extra Information for List Parts from Above Table
 *    @TABLE_LIST_PART
 *       @TR   callbackList      @TD   Separator               @TD   Callback; EventCallback
 *    @TABLE_END
 * 
 * @SEE_ALSO
 *    SoInteractionKit,
 *    SoDragger,
 *    SoCenterballDragger,
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
 *    SoTranslate1Dragger,
 *    SoTranslate2Dragger
 * 
 * 
 */ 

class INVENTOR_API SoDirectionalLightDragger : public SoDragger {

  SO_KIT_HEADER(SoDirectionalLightDragger);

  // This gives the dragger an overall material.  It is edited by lightManips
  // to make its dragger match the color of the light.  Any materials within 
  // other parts will override this one. 
  SO_KIT_CATALOG_ENTRY_HEADER(material);

  // The translator is kept under a separator along with a
  // rotation that is maintained as the inverse to the rotation of the
  // light. This means that using the rotator does not rotate the
  // coordinate system that we translate the base of the dragger in.
  SO_KIT_CATALOG_ENTRY_HEADER(translatorSep);
  SO_KIT_CATALOG_ENTRY_HEADER(translatorRotInv);
  SO_KIT_CATALOG_ENTRY_HEADER(translator);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator);

 public:
  /**
   * Constructor.
   */
  SoDirectionalLightDragger();

  /**
   * Orientation of the rotating part (an arrow by default).
   * 
   */
  SoSFRotation rotation;
  /**
   * Position of the origin of the directional light dragger.
   * 
   */
  SoSFVec3f    translation;

 SoINTERNAL public:
  static void         initClass();    // initialize the class
  static void         exitClass();

 protected:

  SoFieldSensor *translFieldSensor;
  SoFieldSensor *rotFieldSensor;
  static void   fieldSensorCB( void *, SoSensor * );
  static void valueChangedCB( void *, SoDragger * );

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

  ~SoDirectionalLightDragger();

 private:
  static const char geomBuffer[];
};

#endif /* _SO_DIRECTIONAL_LIGHT_DRAGGER_ */

