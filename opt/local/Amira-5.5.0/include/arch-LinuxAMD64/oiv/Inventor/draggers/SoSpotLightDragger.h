/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : SGI (MMM YYYY)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/
////////////////////////////////////////////////////////////////////////
//
// Description:
//  This is the include file for the SoSpotLightDragger. 
//  This is a composite dragger which allows independent rotation,
//  translation, and beam spread editting of a spot light.
//
//  It is composed of an SoRotateSphericalDragger (for rotation), 
//  an SoDragPointDragger (for translation), and it creates its own projector
//  handles mouse events for doing it's own dragging of the beam angle.
//
//  The beam is editted by behaving like an SoRotateDiscDragger, but the 
//  plane of the disc is re-defined every time a drag is initiated.
//  The plane always passes through the z axis and the selected point.
//  When the rotation angle is determined, however, the beam is not rotated,
//  but scaled so it looks like an opening or closing umbrella. This is done
//  by scaling evenly in x and y, and a different amount in z, so the distance
//  between the selected point and the origin remains constant.
//
// NOTE TO DEVELOPERS:
//     For info about the structure of SoSpotLightDragger:
//     [1] compile: /usr/share/src/Inventor/samples/ivNodeKitStructure
//     [2] type:    ivNodeKitStructure SoSpotLightDragger.
//     [3] The program prints a diagram of the scene graph and a table with 
//         information about each part.
//
//
//  The following parts in this dragger are created at construction time.
//  'ResourceName' corresponds to the name of the default geometry for the
//  part. The dragger's constructor gets the scene graph for 'ResourceName'
//  by querying the global dictionary ( SoDB::getByName("ResourceName"); ).  
//
//  Resource Name:                      Part Name:
//
//  spotLightOverallMaterial          - material
//
//  spotLightTranslatorLineTranslator - 
//                                    - translator.xTranslator.translator
//                                    - translator.yTranslator.translator
//                                    - translator.zTranslator.translator
//  spotLightTranslatorLineTranslatorActive  - 
//                                    - translator.xTranslator.translatorActive
//                                    - translator.yTranslator.translatorActive
//                                    - translator.zTranslator.translatorActive
//
//  spotLightTranslatorPlaneTranslator- 
//                                    - translator.yzTranslator.translator
//                                    - translator.xzTranslator.translator
//                                    - translator.xyTranslator.translator
//  spotLightTranslatorPlaneTranslatorActive  - 
//                                    - translator.yzTranslator.translatorActive
//                                    - translator.xzTranslator.translatorActive
//                                    - translator.xyTranslator.translatorActive
//
//  spotLightRotatorRotator           - rotator.rotator      
//  spotLightRotatorRotatorActive     - rotator.rotatorActive
//  spotLightRotatorFeedback          - rotator.feedback      
//  spotLightRotatorFeedbackActive    - rotator.feedbackActive
//
//  spotLightBeam                     - beam
//  spotLightBeamActive               - beamActive
//
//  NOTE: This is a translation node that 
//        moves the beam origin relative
//        to the rest of the dragger.
//  spotLightBeamPlacement            - beamPlacement
//
////////////////////////////////////////////////////////////////////////

 
#ifndef  _SO_SPOT_LIGHT_DRAGGER_
#define  _SO_SPOT_LIGHT_DRAGGER_

#include <Inventor/SbLinear.h>
#include <Inventor/draggers/SoDragger.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFRotation.h>
#include <Inventor/sensors/SoSensor.h>

class SoFieldSensor;
class SbPlaneProjector;

/**
 * Spotlight shaped dragger that allows you to change position, direction, and
 * width of the beam.
 * 
 * @ingroup draggers
 * 
 * @DESCRIPTION
 *   SoSpotLightDragger is a composite dragger. It is shaped like a beam of light
 *   emanating from a sun-like ball. An arrow runs along the axis of the beam and
 *   extends past the end of the beam.
 *   
 *   When you click and drag the beam, it opens and closes with an umbrella-like
 *   motion. The angle between the center and edge of the beam is stored in the
 *   #angle field of this dragger; setting the #angle field causes the
 *   beam to widen or narrow in response. The spotlight dragger does not use a
 *   standard dragger class to execute this motion. More details are given later in
 *   this section.
 *   
 *   Dragging the arrow rotates it around the sun, and the beam moves with it. The
 *   arrow is an SoRotateSphericalDragger that controls the #rotation field.
 *   See the reference page for SoDirectionalLightDragger, which works the same way,
 *   for details.
 *   
 *   The sun-shape can be dragged to translate all three pieces together through
 *   3-space. Its movement controls the #translation field and works exactly as
 *   described in the reference pages for SoDirectionalLightDragger and
 *   SoPointLightDragger (which goes into more detail).
 *   
 *   @B Remember: @b This is @B not @b a light source! It just looks like one. If
 *   you want to move a light with this dragger, you can do the following:
 *   
 *     - Use an SoSpotLightManip, which is subclassed from SoLight. It creates an
 *       SoSpotLightDragger and uses it as the interface to change the @B location @b,
 *       @B direction @b, and @B cutOffAngle @b of its light source (see the
 *       SoSpotLightManip reference page). The manip also edits the @B material @b part
 *       of this dragger to match the color of light the manip is producing.
 *   
 *     - Connect the #angle field of this dragger to the @B cutOffAngle @b
 *       field of an SoSpotLight with a field-to-field connection.
 *   
 *   See the SoPointLightDragger and SoDirectionalLightDragger reference pages for
 *   other ways to control light parameters with the #rotation and
 *   #translation fields.
 *   
 *   This class creates its own projector and handles mouse events to do its own
 *   dragging of the beam angle. When the mouse picks a point on the beam, that point
 *   is dragged in a circle just like in an SoRotateDiscDragger, but the plane of the
 *   disc is re-defined every time a drag is initiated. Imagine placing the metal tip
 *   of a compass at the apex of the cone and the pencil tip at the picked point. If
 *   you swing an arc through the central axis of the cone, you will be drawing the
 *   arc used to drag the beam open and closed.
 *   
 *   The beam is opened and closed not by rotating, but by scaling. The dragger scales
 *   the beam-cone so that the height and radius change to move the picked point
 *   along the circle. Then the #angle field is calculated from the height and
 *   radius.
 *   
 *   You can change the geometry of parts in any instance of this dragger using
 *   setPart(). The default part geometries are defined as resources for this
 *   SoSpotLightDragger class. They are detailed below in the DRAGGER RESOURCE
 *   section. You can make your program use different default resources for the parts
 *   by copying the file @B $OIVHOME/data/draggerDefaults/spotLightDragger.iv @b
 *   into your own directory, editing the file, and then setting the environment
 *   variable @B SO_DRAGGER_DIR @b to be a path to that directory.
 * 
 * @FILE_FORMAT_DEFAULT
 *    SpotLightDragger {
 *    @TABLE_FILE_FORMAT
 *       @TR renderCaching                                   @TD AUTO
 *       @TR boundingBoxCaching                              @TD AUTO
 *       @TR renderCulling                                   @TD AUTO
 *       @TR pickCulling                                     @TD AUTO
 *       @TR isActive                                        @TD FALSE
 *       @TR rotation                                        @TD 0 0 1 0
 *       @TR translation                                     @TD 0 0 0
 *       @TR angle                                           @TD 1
 *       @TR callbackList                                    @TD NULL
 *       @TR material                                        @TD \<spotLightOverallMaterial resource\>
 *       @TR translator                                      @TD DragPointDragger { }
 *       @TR rotator                                         @TD RotateSphericalDragger { }
 *       @TR beamPlacement                                   @TD \<spotLightBeamPlacement resource\>
 *       @TR beamScale                                       @TD Scale {
 *       @TR                                                 @TD &nbsp;scaleFactor 0.841471 0.841471 0.540302 
 *       @TR                                                 @TD }   
 *       @TR beam                                            @TD \<spotLightBeam resource\>
 *       @TR beamActive                                      @TD \<spotLightBeamActive resource\>
 *       @TR rotator.rotator                                 @TD \<spotLightRotatorRotator resource\>
 *       @TR rotator.rotatorActive                           @TD \<spotLightRotatorRotatorActive resource\>
 *       @TR rotator.feedback                                @TD \<spotLightRotatorFeedback resource\>
 *       @TR rotator.feedbackActive                          @TD \<spotLightRotatorFeedbackActive resource\>
 *       @TR translator.yzTranslator.translator              @TD \<spotLightTranslatorPlaneTranslator resource\>
 *       @TR translator.xzTranslator.translator              @TD \<spotLightTranslatorPlaneTranslator resource\>
 *       @TR translator.xyTranslator.translator              @TD \<spotLightTranslatorPlaneTranslator resource\>
 *       @TR translator.yzTranslator.translatorActive        @TD \<spotLightTranslatorPlaneTranslatorActive resource\>
 *       @TR translator.xzTranslator.translatorActive        @TD \<spotLightTranslatorPlaneTranslatorActive resource\>
 *       @TR translator.xyTranslator.translatorActive        @TD \<spotLightTranslatorPlaneTranslatorActive resource\>
 *       @TR translator.xTranslator.translator               @TD \<spotLightTranslatorLineTranslator resource\>
 *       @TR translator.yTranslator.translator               @TD \<spotLightTranslatorLineTranslator resource\>
 *       @TR translator.zTranslator.translator               @TD \<spotLightTranslatorLineTranslator resource\>
 *       @TR translator.xTranslator.translatorActive         @TD \<spotLightTranslatorLineTranslatorActive resource\>
 *       @TR translator.yTranslator.translatorActive         @TD \<spotLightTranslatorLineTranslatorActive resource\>
 *       @TR translator.zTranslator.translatorActive         @TD \<spotLightTranslatorLineTranslatorActive resource\>
 *    @TABLE_END
 *    }
 * 
 * 
 * @DRAGGER_RESOURCES
 *    @TABLE_DRAGGER_RESOURCES
 *       @TR Resource:      @TD @B spotLightBeam @b
 *       @TR Part:          @TD beam
 *       @TR Appearance:    @TD wireframe cone with no SoMaterial node
 *       @TR Description:   @TD picking this initiates dragging of the beam angle. The beam inherits colors from
 *                           the @B material @b part, just like the stationary version of the sun shape.
 * 
 *       @TR Resource:      @TD @B spotLightBeamActive @b
 *       @TR Part:          @TD beamActive
 *       @TR Appearance:    @TD yellow wireframe cone
 *       @TR Description:   @TD displayed during dragging of the beam angle.
 * 
 *       @TR Resource:      @TD @B spotLightBeamPlacement @b
 *       @TR Part:          @TD beamPlacement
 *       @TR Appearance:    @TD translation of (0,0,-1)
 *       @TR Description:   @TD This translation node moves the beam parts relative to the rest of the dragger.
 *                           In this case, moving by (0,0,-1) slides the cone outward along rotator part
 *                           toward its arrowhead. The distance chosen places the apex of the cone on the
 *                           surface of the sun shape.
 * 
 *       @TR Resource:      @TD @B spotLightRotatorRotator @b
 *       @TR Part:          @TD rotator.rotator
 *       @TR Appearance:    @TD white arrow that goes through the sun
 *       @TR Description:   @TD picking this begins rotation of the arrow about the sun-shape
 * 
 *       @TR Resource:      @TD @B spotLightRotatorRotatorActive @b
 *       @TR Part:          @TD rotator.rotatorActive
 *       @TR Appearance:    @TD yellow arrow that goes through the sun
 *       @TR Description:   @TD displayed while the arrow is being rotated
 * 
 *       @TR Resource:      @TD @B spotLightRotatorFeedback @b
 *       @TR Part:          @TD rotator.feedback
 *       @TR Appearance:    @TD empty Separator
 *       @TR Description:   @TD this disables display of the axes that a rotateSpherical dragger uses by default
 * 
 *       @TR Resource:      @TD @B spotLightRotatorFeedbackActive @b
 *       @TR Part:          @TD rotator.feedbackActive
 *       @TR Appearance:    @TD empty Separator
 *       @TR Description:   @TD this disables display of the axes that a rotateSpherical dragger uses by default
 * 
 *       @TR Resource:      @TD @B spotLightOverallMaterial @b
 *       @TR Part:          @TD material
 *       @TR Appearance:    @TD white. half strength emissive, half strength diffuse
 *       @TR Description:   @TD sets material for the sun shape when stationary. Resource for the moving sun,
 *                           spotLightTranslatorPlaneTranslatorActive, contains a yellow material for
 *                           highlighting.
 * 
 *       @TR Resource:      @TD @B spotLightTranslatorPlaneTranslator @b
 *       @TR Parts:         @TD translator.yzTranslator.translator@BR
 *                               translator.xzTranslator.translator@BR
 *                               translator.xyTranslator.translator 
 *       @TR Appearance:    @TD sun shape with no material
 *       @TR Description:   @TD picking these parts initiates dragging by the yz, xz, and xy planar draggers
 *                           respectively.
 * 
 *       @TR Resource:      @TD @B spotLightTranslatorPlaneTranslatorActive @b
 *       @TR Parts:         @TD translator.yzTranslator.translatorActive@BR
 *                               translator.xzTranslator.translatorActive@BR
 *                               translator.xyTranslator.translatorActive 
 *       @TR Appearance:    @TD yellow sun shape
 *       @TR Description:   @TD shown during planar dragging in the yz, xz, and xy planes respectively.
 * 
 *       @TR Resource:      @TD @B spotLightTranslatorLineTranslator @b
 *       @TR Parts:         @TD translator.xTranslator.translator@BR
 *                               translator.yTranslator.translator@BR
 *                               translator.zTranslator.translator 
 *       @TR Appearance:    @TD white cylinder
 *       @TR Description:   @TD picking these parts initiates dragging in the x, y, and z linear draggers
 *                           respectively.
 * 
 *       @TR Resource:      @TD @B spotLightTranslatorLineTranslatorActive @b
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
 *       @TR   callbackList   @TD   NodeKitListPart         @TD    --      @TD   yes     
 *       @TR   material       @TD   Material                @TD    --      @TD   yes     
 *       @TR   translator     @TD   DragPointDragger        @TD    --      @TD   yes     
 *       @TR   rotator        @TD   RotateSphericalDragger  @TD    --      @TD   yes     
 *       @TR   beamPlacement  @TD   Translation             @TD    --      @TD   yes     
 *       @TR   beamScale      @TD   Scale                   @TD    --      @TD   yes     
 *       @TR   beam           @TD   Separator               @TD    --      @TD   yes     
 *       @TR   beamActive     @TD   Separator               @TD    --      @TD   yes     
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
 *    SoJackDragger,
 *    SoPointLightDragger,
 *    SoRotateCylindricalDragger,
 *    SoRotateDiscDragger,
 *    SoRotateSphericalDragger,
 *    SoScale1Dragger,
 *    SoScale2Dragger,
 *    SoScale2UniformDragger,
 *    SoScaleUniformDragger,
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

class INVENTOR_API SoSpotLightDragger : public SoDragger
{
  SO_KIT_HEADER(SoSpotLightDragger);

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
  // Beneath a separator, the beamPlacement part places the beam's local
  // space relative to the other parts.
  // The beamSwitch is flipped when the beam is dragged. 
  SO_KIT_CATALOG_ENTRY_HEADER(beamSep);
  SO_KIT_CATALOG_ENTRY_HEADER(beamPlacement);
  SO_KIT_CATALOG_ENTRY_HEADER(beamScale);
  SO_KIT_CATALOG_ENTRY_HEADER(beamSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(beam);
  SO_KIT_CATALOG_ENTRY_HEADER(beamActive);

 public:
  /**
   * Constructor.
   */
  SoSpotLightDragger();

  /**
   * Orientation of the rotating part (an arrow by default).
   * 
   */
  SoSFRotation rotation;
  /**
   * Position of the dragger.
   * 
   */
  SoSFVec3f    translation;
  /**
   * Angle between center and edge of beam.
   * 
   */
  SoSFFloat    angle;

 SoINTERNAL public:
  static void initClass(); // Initialize the class. 
  static void exitClass();

 protected:

  SbPlaneProjector    *planeProj;  // used during interaciton with beam

  static void startCB( void *, SoDragger * );
  static void motionCB( void *, SoDragger * );
  static void doneCB( void *, SoDragger * );

  void        dragStart();
  void        drag();
  void        dragFinish();

  SoFieldSensor *rotFieldSensor;
  SoFieldSensor *translFieldSensor;
  SoFieldSensor *angleFieldSensor;
  static void   fieldSensorCB( void *, SoSensor * );
  static void   valueChangedCB( void *, SoDragger * );

  // Returns scaleFactor for beamScale part to display beamAngle.
  void setBeamScaleFromAngle(float beamAngle);

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

  virtual ~SoSpotLightDragger();

 private:
  static const char geomBuffer[];
};    

#endif  /* _SO_SPOT_LIGHT_DRAGGER_ */

