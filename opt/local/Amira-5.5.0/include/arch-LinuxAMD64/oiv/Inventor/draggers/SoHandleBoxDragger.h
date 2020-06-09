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


#ifndef  _SO_HANDLEBOX_DRAGGER_
#define  _SO_HANDLEBOX_DRAGGER_

#include <Inventor/draggers/SoDragger.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/sensors/SoSensor.h>

class SbDict;
class SoDrawStyle;
class SbPlaneProjector;
class SbLineProjector;
class SoFieldSensor;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoHandleBoxDragger
//
//  HandleBox dragger - allows user to transform objects.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Box you can scale, stretch and translate by dragging with the mouse.
 * 
 * @ingroup draggers
 * 
 * @DESCRIPTION
 *   SoHandleBoxDragger is a dragger shaped like a wireframe box with small @B corner
 *   cubes @b mounted on each corner. Click and drag any of these cubes to scale the
 *   box uniformly. Six other @B center cubes @b are centered on the sides of the
 *   box; white lines connect them to the center of the dragger. Drag one of the
 *   center cubes along its line to stretch the box in that direction. Dragging a
 *   face of the box translates the dragger within that plane.
 *   
 *   While you drag a face of the box, purple @B feedback arrows @b display the
 *   possible directions of motion. Press the \<Shift\> key to @B constrain @b the
 *   motion to one of the two major directions in the plane. The constraint direction
 *   is chosen based on the next user gesture. Press the \<Control\> key and the
 *   dragger will translate @B perpendicular @b to that plane. The
 *   #translation field is modified as the face is dragged.
 *   
 *   By default, dragging any of the small cubes scales about the center of the
 *   object. Pressing the \<Control\> key changes this: A corner cube will scale about
 *   its opposite corner. A center cube will scale about the center of its opposite
 *   face. Dragging one of the small cubes will usually result in changes to both the
 *   #scaleFactor and #translation fields. This is because any scale
 *   about a point other than the origin has a translation element.
 *   
 *   As with all draggers, if you change the fields the dragger will move to match the
 *   new settings.
 *   
 *   @B Remember: @b This is @B not @b an SoTransform@B ! @b. If you want to move
 *   other objects with this dragger, you can either:
 *   
 *     - Use an SoHandleBoxManip, which is subclassed from SoTransform. It creates one
 *       of these draggers and uses it as the interface to change its fields. (see the
 *       SoHandleBoxManip reference page).
 *   
 *     - Use field-to-field connections to connect the fields of this dragger to those
 *       of any SoTransformation node.
 *   
 *   You can change the parts in any instance of this dragger using setPart().
 *   The default part geometries are defined as resources for this SoHandleBoxDragger
 *   class. They are detailed in the Dragger Resources section of the online
 *   reference page for this class. You can make your program use different default
 *   resources for the parts by copying the file
 *   @B $OIVHOME/data/draggerDefaults/handleBoxDragger.iv @b into your own
 *   directory, editing the file, and then setting the environment variable
 *   @B SO_DRAGGER_DIR @b to be a path to that directory.
 * 
 * @NOTES
 *    Unlike most multi-function draggers, SoHandleBoxDragger is not a compound
 *   dragger made up of other draggers that perform its smaller tasks. This is not
 *   because it was inappropriate, but because was written before implementation of
 *   the methods that synchronize multiple child draggers. The younger
 *   SoTransformBoxDragger has similarities to the handle box dragger, but the
 *   transform box dragger @B is @b a compound dragger.
 * 
 * @FILE_FORMAT_DEFAULT
 *    HandleBoxDragger {
 *    @TABLE_FILE_FORMAT
 *       @TR renderCaching        @TD AUTO
 *       @TR boundingBoxCaching   @TD AUTO
 *       @TR renderCulling        @TD AUTO
 *       @TR pickCulling          @TD AUTO
 *       @TR isActive             @TD FALSE
 *       @TR translation          @TD 0 0 0
 *       @TR scaleFactor          @TD 1 1 1
 *       @TR callbackList         @TD NULL
 *       @TR surroundScale        @TD NULL
 *       @TR translator1          @TD \<handleBoxTranslator1 resource\>
 *       @TR translator1Active    @TD \<handleBoxTranslator1Active resource\>
 *       @TR translator2          @TD \<handleBoxTranslator2 resource\>
 *       @TR translator2Active    @TD \<handleBoxTranslator2Active resource\>
 *       @TR translator3          @TD \<handleBoxTranslator3 resource\>
 *       @TR translator3Active    @TD \<handleBoxTranslator3Active resource\>
 *       @TR translator4          @TD \<handleBoxTranslator4 resource\>
 *       @TR translator4Active    @TD \<handleBoxTranslator4Active resource\>
 *       @TR translator5          @TD \<handleBoxTranslator5 resource\>
 *       @TR translator5Active    @TD \<handleBoxTranslator5Active resource\>
 *       @TR translator6          @TD \<handleBoxTranslator6 resource\>
 *       @TR translator6Active    @TD \<handleBoxTranslator6Active resource\>
 *       @TR extruder1            @TD \<handleBoxExtruder1 resource\>
 *       @TR extruder1Active      @TD \<handleBoxExtruder1Active resource\>
 *       @TR extruder2            @TD \<handleBoxExtruder2 resource\>
 *       @TR extruder2Active      @TD \<handleBoxExtruder2Active resource\>
 *       @TR extruder3            @TD \<handleBoxExtruder3 resource\>
 *       @TR extruder3Active      @TD \<handleBoxExtruder3Active resource\>
 *       @TR extruder4            @TD \<handleBoxExtruder4 resource\>
 *       @TR extruder4Active      @TD \<handleBoxExtruder4Active resource\>
 *       @TR extruder5            @TD \<handleBoxExtruder5 resource\>
 *       @TR extruder5Active      @TD \<handleBoxExtruder5Active resource\>
 *       @TR extruder6            @TD \<handleBoxExtruder6 resource\>
 *       @TR extruder6Active      @TD \<handleBoxExtruder6Active resource\>
 *       @TR uniform1             @TD \<handleBoxUniform1 resource\>
 *       @TR uniform1Active       @TD \<handleBoxUniform1Active resource\>
 *       @TR uniform2             @TD \<handleBoxUniform2 resource\>
 *       @TR uniform2Active       @TD \<handleBoxUniform2Active resource\>
 *       @TR uniform3             @TD \<handleBoxUniform3 resource\>
 *       @TR uniform3Active       @TD \<handleBoxUniform3Active resource\>
 *       @TR uniform4             @TD \<handleBoxUniform4 resource\>
 *       @TR uniform4Active       @TD \<handleBoxUniform4Active resource\>
 *       @TR uniform5             @TD \<handleBoxUniform5 resource\>
 *       @TR uniform5Active       @TD \<handleBoxUniform5Active resource\>
 *       @TR uniform6             @TD \<handleBoxUniform6 resource\>
 *       @TR uniform6Active       @TD \<handleBoxUniform6Active resource\>
 *       @TR uniform7             @TD \<handleBoxUniform7 resource\>
 *       @TR uniform7Active       @TD \<handleBoxUniform7Active resource\>
 *       @TR uniform8             @TD \<handleBoxUniform8 resource\>
 *       @TR uniform8Active       @TD \<handleBoxUniform8Active resource\>
 *       @TR arrow1               @TD \<handleBoxArrow1 resource\>
 *       @TR arrow2               @TD \<handleBoxArrow2 resource\>
 *       @TR arrow3               @TD \<handleBoxArrow3 resource\>
 *       @TR arrow4               @TD \<handleBoxArrow4 resource\>
 *       @TR arrow5               @TD \<handleBoxArrow5 resource\>
 *       @TR arrow6               @TD \<handleBoxArrow6 resource\>
 *    @TABLE_END
 *    }
 * 
 * 
 * @DRAGGER_RESOURCES
 *    @TABLE_DRAGGER_RESOURCES
 *       @TR Resource:      @TD @B handleBoxTranslator1 @b
 *       @TR Part:          @TD translator1
 *       @TR Appearance:    @TD White Line-Style Square
 *       @TR Description:   @TD Top face of handleBox. Picking this initiates translation in x-z plane.
 * 
 *       @TR Resource:      @TD @B handleBoxTranslator2 @b
 *       @TR Part:          @TD translator2
 *       @TR Appearance:    @TD White Line-Style Square
 *       @TR Description:   @TD Bottom face of handleBox. Picking this initiates translation in x-z plane.
 * 
 *       @TR Resource:      @TD @B handleBoxTranslator3 @b
 *       @TR Part:          @TD translator3
 *       @TR Appearance:    @TD White Line-Style Square
 *       @TR Description:   @TD Left face of handleBox. Picking this initiates translation in y-z plane.
 * 
 *       @TR Resource:      @TD @B handleBoxTranslator4 @b
 *       @TR Part:          @TD translator4
 *       @TR Appearance:    @TD White Line-Style Square
 *       @TR Description:   @TD Right face of handleBox. Picking this initiates translation in y-z plane.
 * 
 *       @TR Resource:      @TD @B handleBoxTranslator5 @b
 *       @TR Part:          @TD translator5
 *       @TR Appearance:    @TD White Line-Style Square
 *       @TR Description:   @TD Front face of handleBox. Picking this initiates translation in x-y plane.
 * 
 *       @TR Resource:      @TD @B handleBoxTranslator6 @b
 *       @TR Part:          @TD translator6
 *       @TR Appearance:    @TD White Line-Style Square
 *       @TR Description:   @TD Back face of handleBox. Picking this initiates translation in x-y plane.
 * 
 *       @TR Resource:      @TD @B handleBoxTranslator1Active @b
 *       @TR Part:          @TD translator1Active
 *       @TR Appearance:    @TD Yellow version of handleBoxTranslator1
 *       @TR Description:   @TD Replaces handleBoxTranslator1 during dragging.
 * 
 *       @TR Resource:      @TD @B handleBoxTranslator2Active @b
 *       @TR Part:          @TD translator2Active
 *       @TR Appearance:    @TD Yellow version of handleBoxTranslator2
 *       @TR Description:   @TD Replaces handleBoxTranslator2 during dragging.
 * 
 *       @TR Resource:      @TD @B handleBoxTranslator3Active @b
 *       @TR Part:          @TD translator3Active
 *       @TR Appearance:    @TD Yellow version of handleBoxTranslator3
 *       @TR Description:   @TD Replaces handleBoxTranslator3 during dragging.
 * 
 *       @TR Resource:      @TD @B handleBoxTranslator4Active @b
 *       @TR Part:          @TD translator4Active
 *       @TR Appearance:    @TD Yellow version of handleBoxTranslator4
 *       @TR Description:   @TD Replaces handleBoxTranslator4 during dragging.
 * 
 *       @TR Resource:      @TD @B handleBoxTranslator5Active @b
 *       @TR Part:          @TD translator5Active
 *       @TR Appearance:    @TD Yellow version of handleBoxTranslator5
 *       @TR Description:   @TD Replaces handleBoxTranslator5 during dragging.
 * 
 *       @TR Resource:      @TD @B handleBoxTranslator6Active @b
 *       @TR Part:          @TD translator6Active
 *       @TR Appearance:    @TD Yellow version of handleBoxTranslator6
 *       @TR Description:   @TD Replaces handleBoxTranslator6 during dragging.
 * 
 *       @TR Resource:      @TD @B handleBoxExtruder1 @b
 *       @TR Part:          @TD extruder1
 *       @TR Appearance:    @TD Small white cube at (0,1.25,0) with line to origin
 *       @TR Description:   @TD Selecting this part initiates 1-D scaling along Y axis.
 * 
 *       @TR Resource:      @TD @B handleBoxExtruder2 @b
 *       @TR Part:          @TD extruder2
 *       @TR Appearance:    @TD Small white cube at (0,-1.25,0) with line to origin
 *       @TR Description:   @TD Selecting this part initiates 1-D scaling along Y axis.
 * 
 *       @TR Resource:      @TD @B handleBoxExtruder3 @b
 *       @TR Part:          @TD extruder3
 *       @TR Appearance:    @TD Small white cube at (-1.25,0,0) with line to origin
 *       @TR Description:   @TD Selecting this part initiates 1-D scaling along X axis.
 * 
 *       @TR Resource:      @TD @B handleBoxExtruder4 @b
 *       @TR Part:          @TD extruder4
 *       @TR Appearance:    @TD Small white cube at (1.25,0,0) with line to origin
 *       @TR Description:   @TD Selecting this part initiates 1-D scaling along X axis.
 * 
 *       @TR Resource:      @TD @B handleBoxExtruder5 @b
 *       @TR Part:          @TD extruder5
 *       @TR Appearance:    @TD Small white cube at (0,0,1.25) with line to origin
 *       @TR Description:   @TD Selecting this part initiates 1-D scaling along Z axis.
 * 
 *       @TR Resource:      @TD @B handleBoxExtruder6 @b
 *       @TR Part:          @TD extruder6
 *       @TR Appearance:    @TD Small white cube at (0,0,-1.25) with line to origin
 *       @TR Description:   @TD Selecting this part initiates 1-D scaling along Z axis.
 * 
 *       @TR Resource:      @TD @B handleBoxExtruder1Active @b
 *       @TR Part:          @TD extruder1Active
 *       @TR Appearance:    @TD Yellow version of handleBoxExtruder1
 *       @TR Description:   @TD Replaces handleBoxExtruder1 during dragging.
 * 
 *       @TR Resource:      @TD @B handleBoxExtruder2Active @b
 *       @TR Part:          @TD extruder2Active
 *       @TR Appearance:    @TD Yellow version of handleBoxExtruder1
 *       @TR Description:   @TD Replaces handleBoxExtruder1 during dragging.
 * 
 *       @TR Resource:      @TD @B handleBoxExtruder3Active @b
 *       @TR Part:          @TD extruder3Active
 *       @TR Appearance:    @TD Yellow version of handleBoxExtruder3
 *       @TR Description:   @TD Replaces handleBoxExtruder3 during dragging.
 * 
 *       @TR Resource:      @TD @B handleBoxExtruder4Active @b
 *       @TR Part:          @TD extruder4Active
 *       @TR Appearance:    @TD Yellow version of handleBoxExtruder4
 *       @TR Description:   @TD Replaces handleBoxExtruder4 during dragging.
 * 
 *       @TR Resource:      @TD @B handleBoxExtruder5Active @b
 *       @TR Part:          @TD extruder5Active
 *       @TR Appearance:    @TD Yellow version of handleBoxExtruder5
 *       @TR Description:   @TD Replaces handleBoxExtruder5 during dragging.
 * 
 *       @TR Resource:      @TD @B handleBoxExtruder6Active @b
 *       @TR Part:          @TD extruder6Active
 *       @TR Appearance:    @TD Yellow version of handleBoxExtruder6
 *       @TR Description:   @TD Replaces handleBoxExtruder6 during dragging.
 * 
 *       @TR Resource:      @TD @B handleBoxUniform1 @b
 *       @TR Part:          @TD uniform1
 *       @TR Appearance:    @TD Small white cube in (+x+y+z) corner of handleBox
 *       @TR Description:   @TD Picking this initiates uniform scaling.
 * 
 *       @TR Resource:      @TD @B handleBoxUniform2 @b
 *       @TR Part:          @TD uniform2
 *       @TR Appearance:    @TD Small white cube in (+x+y-z) corner of handleBox
 *       @TR Description:   @TD Picking this initiates uniform scaling.
 * 
 *       @TR Resource:      @TD @B handleBoxUniform3 @b
 *       @TR Part:          @TD uniform3
 *       @TR Appearance:    @TD Small white cube in (+x-y+z) corner of handleBox
 *       @TR Description:   @TD Picking this initiates uniform scaling.
 * 
 *       @TR Resource:      @TD @B handleBoxUniform4 @b
 *       @TR Part:          @TD uniform4
 *       @TR Appearance:    @TD Small white cube in (+x-y-z) corner of handleBox
 *       @TR Description:   @TD Picking this initiates uniform scaling.
 * 
 *       @TR Resource:      @TD @B handleBoxUniform5 @b
 *       @TR Part:          @TD uniform5
 *       @TR Appearance:    @TD Small white cube in (-x+y+z) corner of handleBox
 *       @TR Description:   @TD Picking this initiates uniform scaling.
 * 
 *       @TR Resource:      @TD @B handleBoxUniform6 @b
 *       @TR Part:          @TD uniform6
 *       @TR Appearance:    @TD Small white cube in (-x+y-z) corner of handleBox
 *       @TR Description:   @TD Picking this initiates uniform scaling.
 * 
 *       @TR Resource:      @TD @B handleBoxUniform7 @b
 *       @TR Part:          @TD uniform7
 *       @TR Appearance:    @TD Small white cube in (-x-y+z) corner of handleBox
 *       @TR Description:   @TD Picking this initiates uniform scaling.
 * 
 *       @TR Resource:      @TD @B handleBoxUniform8 @b
 *       @TR Part:          @TD uniform8
 *       @TR Appearance:    @TD Small white cube in (-x-y-z) corner of handleBox
 *       @TR Description:   @TD Picking this initiates uniform scaling.
 * 
 *       @TR Resource:      @TD @B handleBoxUniform1Active @b
 *       @TR Part:          @TD uniform1Active
 *       @TR Appearance:    @TD Yellow version of handleBoxUniform1Active
 *       @TR Description:   @TD Replaces handleBoxUniform1Active during dragging.
 * 
 *       @TR Resource:      @TD @B handleBoxUniform2Active @b
 *       @TR Part:          @TD uniform2Active
 *       @TR Appearance:    @TD Yellow version of handleBoxUniform1Active
 *       @TR Description:   @TD Replaces handleBoxUniform1Active during dragging.
 * 
 *       @TR Resource:      @TD @B handleBoxUniform3Active @b
 *       @TR Part:          @TD uniform3Active
 *       @TR Appearance:    @TD Yellow version of handleBoxUniform1Active
 *       @TR Description:   @TD Replaces handleBoxUniform1Active during dragging.
 * 
 *       @TR Resource:      @TD @B handleBoxUniform4Active @b
 *       @TR Part:          @TD uniform4Active
 *       @TR Appearance:    @TD Yellow version of handleBoxUniform1Active
 *       @TR Description:   @TD Replaces handleBoxUniform1Active during dragging.
 * 
 *       @TR Resource:      @TD @B handleBoxUniform5Active @b
 *       @TR Part:          @TD uniform5Active
 *       @TR Appearance:    @TD Yellow version of handleBoxUniform1Active
 *       @TR Description:   @TD Replaces handleBoxUniform1Active during dragging.
 * 
 *       @TR Resource:      @TD @B handleBoxUniform6Active @b
 *       @TR Part:          @TD uniform6Active
 *       @TR Appearance:    @TD Yellow version of handleBoxUniform1Active
 *       @TR Description:   @TD Replaces handleBoxUniform1Active during dragging.
 * 
 *       @TR Resource:      @TD @B handleBoxUniform7Active @b
 *       @TR Part:          @TD uniform7Active
 *       @TR Appearance:    @TD Yellow version of handleBoxUniform1Active
 *       @TR Description:   @TD Replaces handleBoxUniform1Active during dragging.
 * 
 *       @TR Resource:      @TD @B handleBoxUniform8Active @b
 *       @TR Part:          @TD uniform8Active
 *       @TR Appearance:    @TD Yellow version of handleBoxUniform1Active
 *       @TR Description:   @TD Replaces handleBoxUniform1Active during dragging.
 * 
 *       @TR Resource:      @TD @B handleBoxArrow1 @b
 *       @TR Part:          @TD arrow1
 *       @TR Appearance:    @TD Purple Arrow, pointing up
 *       @TR Description:   @TD Displayed when translating if Y direction is permitted.
 * 
 *       @TR Resource:      @TD @B handleBoxArrow2 @b
 *       @TR Part:          @TD arrow2
 *       @TR Appearance:    @TD Purple Arrow, pointing down
 *       @TR Description:   @TD Displayed when translating if Y direction is permitted.
 * 
 *       @TR Resource:      @TD @B handleBoxArrow3 @b
 *       @TR Part:          @TD arrow3
 *       @TR Appearance:    @TD Purple Arrow, pointing left
 *       @TR Description:   @TD Displayed when translating if X direction is permitted.
 * 
 *       @TR Resource:      @TD @B handleBoxArrow4 @b
 *       @TR Part:          @TD arrow4
 *       @TR Appearance:    @TD Purple Arrow, pointing right
 *       @TR Description:   @TD Displayed when translating if X direction is permitted.
 * 
 *       @TR Resource:      @TD @B handleBoxArrow5 @b
 *       @TR Part:          @TD arrow5
 *       @TR Appearance:    @TD Purple Arrow, pointing forward
 *       @TR Description:   @TD Displayed when translating if Z direction is permitted.
 * 
 *       @TR Resource:      @TD @B handleBoxArrow6 @b
 *       @TR Part:          @TD arrow6
 *       @TR Appearance:    @TD Purple Arrow, pointing backward
 *       @TR Description:   @TD Displayed when translating if Z direction is permitted.
 * 
 *    @TABLE_END
 * 
 * @CATALOG_PARTS
 *    All Parts
 *    @TABLE_CATALOG_PART
 *       @TR   callbackList       @TD   NodeKitListPart  @TD    --      @TD   yes     
 *       @TR   surroundScale      @TD   SurroundScale    @TD    --      @TD   yes     
 *       @TR   translator1        @TD   Separator        @TD    --      @TD   yes     
 *       @TR   translator1Active  @TD   Separator        @TD    --      @TD   yes     
 *       @TR   translator2        @TD   Separator        @TD    --      @TD   yes     
 *       @TR   translator2Active  @TD   Separator        @TD    --      @TD   yes     
 *       @TR   translator3        @TD   Separator        @TD    --      @TD   yes     
 *       @TR   translator3Active  @TD   Separator        @TD    --      @TD   yes     
 *       @TR   translator4        @TD   Separator        @TD    --      @TD   yes     
 *       @TR   translator4Active  @TD   Separator        @TD    --      @TD   yes     
 *       @TR   translator5        @TD   Separator        @TD    --      @TD   yes     
 *       @TR   translator5Active  @TD   Separator        @TD    --      @TD   yes     
 *       @TR   translator6        @TD   Separator        @TD    --      @TD   yes     
 *       @TR   translator6Active  @TD   Separator        @TD    --      @TD   yes     
 *       @TR   extruder1          @TD   Separator        @TD    --      @TD   yes     
 *       @TR   extruder1Active    @TD   Separator        @TD    --      @TD   yes     
 *       @TR   extruder2          @TD   Separator        @TD    --      @TD   yes     
 *       @TR   extruder2Active    @TD   Separator        @TD    --      @TD   yes     
 *       @TR   extruder3          @TD   Separator        @TD    --      @TD   yes     
 *       @TR   extruder3Active    @TD   Separator        @TD    --      @TD   yes     
 *       @TR   extruder4          @TD   Separator        @TD    --      @TD   yes     
 *       @TR   extruder4Active    @TD   Separator        @TD    --      @TD   yes     
 *       @TR   extruder5          @TD   Separator        @TD    --      @TD   yes     
 *       @TR   extruder5Active    @TD   Separator        @TD    --      @TD   yes     
 *       @TR   extruder6          @TD   Separator        @TD    --      @TD   yes     
 *       @TR   extruder6Active    @TD   Separator        @TD    --      @TD   yes     
 *       @TR   uniform1           @TD   Separator        @TD    --      @TD   yes     
 *       @TR   uniform1Active     @TD   Separator        @TD    --      @TD   yes     
 *       @TR   uniform2           @TD   Separator        @TD    --      @TD   yes     
 *       @TR   uniform2Active     @TD   Separator        @TD    --      @TD   yes     
 *       @TR   uniform3           @TD   Separator        @TD    --      @TD   yes     
 *       @TR   uniform3Active     @TD   Separator        @TD    --      @TD   yes     
 *       @TR   uniform4           @TD   Separator        @TD    --      @TD   yes     
 *       @TR   uniform4Active     @TD   Separator        @TD    --      @TD   yes     
 *       @TR   uniform5           @TD   Separator        @TD    --      @TD   yes     
 *       @TR   uniform5Active     @TD   Separator        @TD    --      @TD   yes     
 *       @TR   uniform6           @TD   Separator        @TD    --      @TD   yes     
 *       @TR   uniform6Active     @TD   Separator        @TD    --      @TD   yes     
 *       @TR   uniform7           @TD   Separator        @TD    --      @TD   yes     
 *       @TR   uniform7Active     @TD   Separator        @TD    --      @TD   yes     
 *       @TR   uniform8           @TD   Separator        @TD    --      @TD   yes     
 *       @TR   uniform8Active     @TD   Separator        @TD    --      @TD   yes     
 *       @TR   arrow1             @TD   Separator        @TD    --      @TD   yes     
 *       @TR   arrow2             @TD   Separator        @TD    --      @TD   yes     
 *       @TR   arrow3             @TD   Separator        @TD    --      @TD   yes     
 *       @TR   arrow4             @TD   Separator        @TD    --      @TD   yes     
 *       @TR   arrow5             @TD   Separator        @TD    --      @TD   yes     
 *       @TR   arrow6             @TD   Separator        @TD    --      @TD   yes     
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

class INVENTOR_API SoHandleBoxDragger : public SoDragger {

  SO_KIT_HEADER(SoHandleBoxDragger);

  SO_KIT_CATALOG_ENTRY_HEADER(drawStyle);

  // For making the dragger surround what lies above it.
  SO_KIT_CATALOG_ENTRY_HEADER(surroundScale);

  SO_KIT_CATALOG_ENTRY_HEADER(translator1Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(translator1);
  SO_KIT_CATALOG_ENTRY_HEADER(translator1Active);
  SO_KIT_CATALOG_ENTRY_HEADER(translator2Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(translator2);
  SO_KIT_CATALOG_ENTRY_HEADER(translator2Active);
  SO_KIT_CATALOG_ENTRY_HEADER(translator3Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(translator3);
  SO_KIT_CATALOG_ENTRY_HEADER(translator3Active);
  SO_KIT_CATALOG_ENTRY_HEADER(translator4Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(translator4);
  SO_KIT_CATALOG_ENTRY_HEADER(translator4Active);
  SO_KIT_CATALOG_ENTRY_HEADER(translator5Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(translator5);
  SO_KIT_CATALOG_ENTRY_HEADER(translator5Active);
  SO_KIT_CATALOG_ENTRY_HEADER(translator6Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(translator6);
  SO_KIT_CATALOG_ENTRY_HEADER(translator6Active);


  SO_KIT_CATALOG_ENTRY_HEADER(extruder1Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(extruder1);
  SO_KIT_CATALOG_ENTRY_HEADER(extruder1Active);
  SO_KIT_CATALOG_ENTRY_HEADER(extruder2Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(extruder2);
  SO_KIT_CATALOG_ENTRY_HEADER(extruder2Active);
  SO_KIT_CATALOG_ENTRY_HEADER(extruder3Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(extruder3);
  SO_KIT_CATALOG_ENTRY_HEADER(extruder3Active);
  SO_KIT_CATALOG_ENTRY_HEADER(extruder4Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(extruder4);
  SO_KIT_CATALOG_ENTRY_HEADER(extruder4Active);
  SO_KIT_CATALOG_ENTRY_HEADER(extruder5Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(extruder5);
  SO_KIT_CATALOG_ENTRY_HEADER(extruder5Active);
  SO_KIT_CATALOG_ENTRY_HEADER(extruder6Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(extruder6);
  SO_KIT_CATALOG_ENTRY_HEADER(extruder6Active);

  SO_KIT_CATALOG_ENTRY_HEADER(uniform1Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(uniform1);
  SO_KIT_CATALOG_ENTRY_HEADER(uniform1Active);
  SO_KIT_CATALOG_ENTRY_HEADER(uniform2Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(uniform2);
  SO_KIT_CATALOG_ENTRY_HEADER(uniform2Active);
  SO_KIT_CATALOG_ENTRY_HEADER(uniform3Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(uniform3);
  SO_KIT_CATALOG_ENTRY_HEADER(uniform3Active);
  SO_KIT_CATALOG_ENTRY_HEADER(uniform4Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(uniform4);
  SO_KIT_CATALOG_ENTRY_HEADER(uniform4Active);
  SO_KIT_CATALOG_ENTRY_HEADER(uniform5Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(uniform5);
  SO_KIT_CATALOG_ENTRY_HEADER(uniform5Active);
  SO_KIT_CATALOG_ENTRY_HEADER(uniform6Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(uniform6);
  SO_KIT_CATALOG_ENTRY_HEADER(uniform6Active);
  SO_KIT_CATALOG_ENTRY_HEADER(uniform7Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(uniform7);
  SO_KIT_CATALOG_ENTRY_HEADER(uniform7Active);
  SO_KIT_CATALOG_ENTRY_HEADER(uniform8Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(uniform8);
  SO_KIT_CATALOG_ENTRY_HEADER(uniform8Active);

  SO_KIT_CATALOG_ENTRY_HEADER(arrowTranslation);

  SO_KIT_CATALOG_ENTRY_HEADER(arrow1Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(arrow1);
  SO_KIT_CATALOG_ENTRY_HEADER(arrow2Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(arrow2);
  SO_KIT_CATALOG_ENTRY_HEADER(arrow3Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(arrow3);
  SO_KIT_CATALOG_ENTRY_HEADER(arrow4Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(arrow4);
  SO_KIT_CATALOG_ENTRY_HEADER(arrow5Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(arrow5);
  SO_KIT_CATALOG_ENTRY_HEADER(arrow6Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(arrow6);

 public:
  /**
   * Constructor.
   */
  SoHandleBoxDragger();
    
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
  static void         initClass();    // initialize the class
  static void         exitClass();

 protected:

  // Callbacks for drag start, motion, and finish
  static void startCB( void *, SoDragger * );
  static void motionCB( void *, SoDragger * );
  static void finishCB( void *, SoDragger * );
    
  SoFieldSensor *translFieldSensor;
  SoFieldSensor *scaleFieldSensor;
  static void   fieldSensorCB( void *, SoSensor * );
  static void valueChangedCB( void *, SoDragger * );

  // Callbacks for pressing and releasing the meta keys
  static void metaKeyChangeCB( void *, SoDragger *);

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

  virtual ~SoHandleBoxDragger();

 private:

  enum WhichAxis 
  { POSX, POSY, POSZ, NEGX, NEGY, NEGZ };
  void   highlightAxisForScale( WhichAxis axis );

  enum State
  { INACTIVE, 
    SCALE_GEOM_ONLY,
    RIT_X_SCALE,  TOP_Y_SCALE,  FNT_Z_SCALE, 
    LFT_X_SCALE,  BOT_Y_SCALE,  BAK_Z_SCALE, 

    PX_PY_PZ_3D_SCALE, PX_PY_NZ_3D_SCALE, PX_NY_PZ_3D_SCALE, 
    PX_NY_NZ_3D_SCALE, NX_PY_PZ_3D_SCALE, NX_PY_NZ_3D_SCALE, 
    NX_NY_PZ_3D_SCALE, NX_NY_NZ_3D_SCALE, 

    RIT_TRANSLATE,  TOP_TRANSLATE,  FNT_TRANSLATE,
    LFT_TRANSLATE,  BOT_TRANSLATE,  BAK_TRANSLATE };

  State               currentState;     
  int                 translateDir;   // Used for 1-D translation,
  // this variable records the current
  // axis being used.

  SbPlaneProjector    *motionPlaneProj;
  SbLineProjector     *motionLineProj;

  State           restartState;     // used by meta callback. 
  SbVec3f         worldRestartPt; // used during interaction

  SbBool          altDown, ctlDown, shftDown;  // used to keep track of
  // which meta keys were down.

  // functions which do all the work
  void        setHighlights();
  void        setFeedbackArrows();

  SbBool              translateInit();
  SbBool              faceScaleInit();
  SbBool              uniformScaleInit();
  SbBool              scaleGeomSizeOnlyInit();

  SbBool              translateDrag();
  SbBool              scaleDrag();
  SbBool              scaleGeomSizeOnlyDrag();

  // character strings from which the shared geometry is read
  static const char geomBuffer[];            
};

#endif /* _SO_HANDLEBOX_DRAGGER_ */

