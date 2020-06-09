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


#ifndef  _SO_TRANSFORMER_DRAGGER_
#define  _SO_TRANSFORMER_DRAGGER_

#include <Inventor/SoLists.h>
#include <Inventor/draggers/SoDragger.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFRotation.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/sensors/SoSensor.h>

class SbDict;
class SbPlaneProjector;
class SbLineProjector;
class SbSphereSectionProjector;
class SbCylinderPlaneProjector;
class SoFieldSensor;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoTransformerDragger
//
//  SoTransformerDragger - allows user to transform objects.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Box-like object you scale, rotate, and translate by dragging with the mouse.
 * 
 * @ingroup draggers
 * 
 * @DESCRIPTION
 *   SoTransformerDragger is a dragger shaped like a box. It has small cubes at the
 *   corners and small balls sticking out of the middle of each face. Click and drag
 *   any face of the box for 2D translation in the plane of that face. Drag any
 *   corner-cube to scale the box uniformly. Pick any of the mid-face balls to rotate
 *   the whole dragger about its center.
 *   
 *   The SoTransformerDragger uses locate highlighting, so you can tell which part you
 *   are about to select before pressing the mouse button. By default, the locate
 *   highlight color is gold.
 *   
 *   Click-drag any @B face @b to translate the dragger within the plane of that
 *   face. The face you selected will highlight in yellow. While you drag, yellow
 *   @B feedback arrows @b display the two directions of motion. Press the \<Shift\>
 *   key and the arrows turn orange; you may now pick between these two directions to
 *   @B constrain @b the motion. The direction you move the cursor in will determine
 *   which direction is chosen. Press the \<Control\> key and the dragger will
 *   translate @B perpendicular @b to that plane. The #translation field is
 *   modified as the face is dragged.
 *   
 *   Click a @B corner @b to scale the dragger. The corner you selected will turn
 *   yellow and radial lines will indicate that you may move toward and away from the
 *   center of the box. Drag radially and you will perform uniform scale. Press the
 *   \<Control\> key to scale about the opposite corner instead of the center of the
 *   box.
 *   
 *   To stretch the dragger non-uniformly, press \<Shift\> when you drag the corner
 *   cube. Now you will see three orange arrows indicating that your gesture will
 *   determine which direction to choose. Move the cursor and the selected arrow will
 *   turn yellow while the others disappear. Now the dragger will stretch only in the
 *   direction you selected. Pressing \<Control\> at the same time as \<Shift\> allows
 *   you to stretch the dragger while keeping the opposite side pinned in place. When
 *   you drag a corner, this modifies the #scaleFactor and possibly the
 *   #translation field of the dragger.
 *   
 *   Click one of the @B spherical knobs @b to rotate the dragger. When you first
 *   click, you'll see two orange lines and two purple circles. The purple circles
 *   indicate the two ways you can rotate. The orange lines are, once again, the two
 *   choices for your mouse gesture. Each line begins you moving around one of the
 *   two circles. Once you move the cursor far enough, the selected line turns yellow
 *   and you begin rotating the dragger about the selected circle. The other circle
 *   and line will disappear.
 *   
 *   To perform unconstrained ("free") rotation, just press \<Shift\> while you drag the
 *   spherical knob. There will be no choices; instead all three purple circles will
 *   be displayed, forming a ball that you can roll around. Regardless of how you
 *   rotate, dragging the spherical knobs will modify the #rotation field of
 *   the dragger. Depending on how it is centered and what transforms precede it in
 *   the scene graph, rotation is likely to affect the #translation and
 *   #scaleFactor fields as well.
 *   
 *   Pressing the \<Control\> key will change the center of rotation in both the
 *   constrained and unconstrained (\<Shift\>) case. By default, rotation occurs about
 *   the center of the bounding box. With \<Control\> depressed, rotation occurs about
 *   the middle of the opposite side of the bounding box. The purple feedback will
 *   change to illustrate this; the feedback circles increase in size and purple
 *   crosshairs sprout at the new rotational center.
 *   
 *   Ordinarily, the knobs of the dragger are unsquished upon readin from file and
 *   when the mouse button is released at the end of a drag. If you want this to
 *   happen more often, then you should call the method unsquishKnobs().
 *   
 *   As with all draggers, if you change the fields the dragger will move to match the
 *   new settings.
 *   
 *   Remember: This is @B not @b an SoTransform@B ! @b. If you want to move other
 *   objects with this dragger, you can either:
 *   
 *     - Use an SoTransformerManip, which is subclassed from SoTransform. It creates
 *       one of these draggers and uses it as the interface to change its fields. (see
 *       the SoTransformerManip reference page).
 *   
 *     - Use field-to-field connections to connect the fields of this dragger to those
 *       of any SoTransformation node.
 *   
 *   You can change the parts in any instance of this dragger using setPart().
 *   The default part geometries are defined as resources for this
 *   SoTransformerDragger class. They are detailed in the Dragger Resources section
 *   of the online reference page for this class. You can make your program use
 *   different default resources for the parts by copying the file
 *   @B $OIVHOME/data/draggerDefaults/transformerDragger.iv @b into your own
 *   directory, editing the file, and then setting the environment variable
 *   @B SO_DRAGGER_DIR @b to be a path to that directory.
 * 
 * @FILE_FORMAT_DEFAULT
 *    TransformerDragger {
 *    @TABLE_FILE_FORMAT
 *       @TR renderCaching           @TD AUTO
 *       @TR boundingBoxCaching      @TD AUTO
 *       @TR renderCulling           @TD AUTO
 *       @TR pickCulling             @TD AUTO
 *       @TR isActive                @TD FALSE
 *       @TR translation             @TD 0 0 0
 *       @TR scaleFactor             @TD 1 1 1
 *       @TR rotation                @TD 0 0 1 0
 *       @TR minDiscRotDot           @TD 0.025
 *       @TR callbackList            @TD NULL
 *       @TR surroundScale           @TD NULL
 *       @TR translator1             @TD \<transformerTranslator1 resource\>
 *       @TR translator1Active       @TD \<transformerTranslator1Active resource\>
 *       @TR translator2             @TD \<transformerTranslator2 resource\>
 *       @TR translator2Active       @TD \<transformerTranslator2Active resource\>
 *       @TR translator3             @TD \<transformerTranslator3 resource\>
 *       @TR translator3Active       @TD \<transformerTranslator3Active resource\>
 *       @TR translator4             @TD \<transformerTranslator4 resource\>
 *       @TR translator4Active       @TD \<transformerTranslator4Active resource\>
 *       @TR translator5             @TD \<transformerTranslator5 resource\>
 *       @TR translator5Active       @TD \<transformerTranslator5Active resource\>
 *       @TR translator6             @TD \<transformerTranslator6 resource\>
 *       @TR translator6Active       @TD \<transformerTranslator6Active resource\>
 *       @TR rotator1                @TD \<transformerRotator1 resource\>
 *       @TR rotator1Active          @TD \<transformerRotator1Active resource\>
 *       @TR rotator2                @TD \<transformerRotator2 resource\>
 *       @TR rotator2Active          @TD \<transformerRotator2Active resource\>
 *       @TR rotator3                @TD \<transformerRotator3 resource\>
 *       @TR rotator3Active          @TD \<transformerRotator3Active resource\>
 *       @TR rotator4                @TD \<transformerRotator4 resource\>
 *       @TR rotator4Active          @TD \<transformerRotator4Active resource\>
 *       @TR rotator5                @TD \<transformerRotator5 resource\>
 *       @TR rotator5Active          @TD \<transformerRotator5Active resource\>
 *       @TR rotator6                @TD \<transformerRotator6 resource\>
 *       @TR rotator6Active          @TD \<transformerRotator6Active resource\>
 *       @TR scale1                  @TD \<transformerScale1 resource\>
 *       @TR scale1Active            @TD \<transformerScale1Active resource\>
 *       @TR scale2                  @TD \<transformerScale2 resource\>
 *       @TR scale2Active            @TD \<transformerScale2Active resource\>
 *       @TR scale3                  @TD \<transformerScale3 resource\>
 *       @TR scale3Active            @TD \<transformerScale3Active resource\>
 *       @TR scale4                  @TD \<transformerScale4 resource\>
 *       @TR scale4Active            @TD \<transformerScale4Active resource\>
 *       @TR scale5                  @TD \<transformerScale5 resource\>
 *       @TR scale5Active            @TD \<transformerScale5Active resource\>
 *       @TR scale6                  @TD \<transformerScale6 resource\>
 *       @TR scale6Active            @TD \<transformerScale6Active resource\>
 *       @TR scale7                  @TD \<transformerScale7 resource\>
 *       @TR scale7Active            @TD \<transformerScale7Active resource\>
 *       @TR scale8                  @TD \<transformerScale8 resource\>
 *       @TR scale8Active            @TD \<transformerScale8Active resource\>
 *       @TR xAxisFeedbackActive     @TD \<transformerXAxisFeedbackActive resource\>
 *       @TR xAxisFeedbackSelect     @TD \<transformerXAxisFeedbackSelect resource\>
 *       @TR xCrosshairFeedback      @TD \<transformerXCrosshairFeedback resource\>
 *       @TR yAxisFeedbackActive     @TD \<transformerYAxisFeedbackActive resource\>
 *       @TR yAxisFeedbackSelect     @TD \<transformerYAxisFeedbackSelect resource\>
 *       @TR yCrosshairFeedback      @TD \<transformerYCrosshairFeedback resource\>
 *       @TR zAxisFeedbackActive     @TD \<transformerZAxisFeedbackActive resource\>
 *       @TR zAxisFeedbackSelect     @TD \<transformerZAxisFeedbackSelect resource\>
 *       @TR zCrosshairFeedback      @TD \<transformerZCrosshairFeedback resource\>
 *       @TR translateBoxFeedback    @TD \<transformerTranslateBoxFeedback resource\>
 *       @TR scaleBoxFeedback        @TD \<transformerScaleBoxFeedback resource\>
 *       @TR posXWallFeedback        @TD \<transformerPosXWallFeedback resource\>
 *       @TR posXRoundWallFeedback   @TD \<transformerPosXRoundWallFeedback resource\>
 *       @TR posYWallFeedback        @TD \<transformerPosYWallFeedback resource>
 *       @TR posYRoundWallFeedback   @TD \<transformerPosYRoundWallFeedback resource\>
 *       @TR posZWallFeedback        @TD \<transformerPosZWallFeedback resource\>
 *       @TR posZRoundWallFeedback   @TD \<transformerPosZRoundWallFeedback resource\>
 *       @TR negXWallFeedback        @TD \<transformerNegXWallFeedback resource\>
 *       @TR negXRoundWallFeedback   @TD \<transformerNegXRoundWallFeedback resource\>
 *       @TR negYWallFeedback        @TD \<transformerNegYWallFeedback resource\>
 *       @TR negYRoundWallFeedback   @TD \<transformerNegYRoundWallFeedback resource\>
 *       @TR negZWallFeedback        @TD \<transformerNegZWallFeedback resource\>
 *       @TR negZRoundWallFeedback   @TD \<transformerNegZRoundWallFeedback resource\>
 *       @TR radialFeedback          @TD \<transformerRadialFeedback resource\>
 *       @TR xCircleFeedback         @TD \<transformerXCircleFeedback resource\>
 *       @TR yCircleFeedback         @TD \<transformerYCircleFeedback resource\>
 *       @TR zCircleFeedback         @TD \<transformerZCircleFeedback resource\>
 *       @TR none                    @TD \<transformerLocateMaterial resource\>
 *    @TABLE_END
 *    }
 * 
 * 
 * @DRAGGER_RESOURCES
 *    @TABLE_DRAGGER_RESOURCES
 *       @TR Resource:      @TD @B transformerLocateMaterial @b
 *       @TR Part:          @TD none
 *       @TR Appearance:    @TD Gold diffuse and emissive color
 *       @TR Description:   @TD Locate highlight color used for all parts.
 * 
 *       @TR Resource:      @TD @B transformerOverallStyle @b
 *       @TR Part:          @TD overallStyle
 *       @TR Appearance:    @TD White Low-Complexity lines
 *       @TR Description:   @TD If nothing else specified, this is style of the part.
 * 
 *       @TR Resource:      @TD @B transformerTranslator1 @b
 *       @TR Part:          @TD translator1
 *       @TR Appearance:    @TD White Line-Style Square
 *       @TR Description:   @TD Top face of transformer. Picking this initiates translation in x-z plane.
 * 
 *       @TR Resource:      @TD @B transformerTranslator2 @b
 *       @TR Part:          @TD translator2
 *       @TR Appearance:    @TD White Line-Style Square
 *       @TR Description:   @TD Bottom face of transformer. Picking this initiates translation in x-z plane.
 * 
 *       @TR Resource:      @TD @B transformerTranslator3 @b
 *       @TR Part:          @TD translator3
 *       @TR Appearance:    @TD White Line-Style Square
 *       @TR Description:   @TD Left face of transformer. Picking this initiates translation in y-z plane.
 * 
 *       @TR Resource:      @TD @B transformerTranslator4 @b
 *       @TR Part:          @TD translator4
 *       @TR Appearance:    @TD White Line-Style Square
 *       @TR Description:   @TD Right face of transformer. Picking this initiates translation in y-z plane.
 * 
 *       @TR Resource:      @TD @B transformerTranslator5 @b
 *       @TR Part:          @TD translator5
 *       @TR Appearance:    @TD White Line-Style Square
 *       @TR Description:   @TD Front face of transformer. Picking this initiates translation in x-y plane.
 * 
 *       @TR Resource:      @TD @B transformerTranslator6 @b
 *       @TR Part:          @TD translator6
 *       @TR Appearance:    @TD White Line-Style Square
 *       @TR Description:   @TD Back face of transformer. Picking this initiates translation in x-y plane.
 * 
 *       @TR Resource:      @TD @B transformerTranslator1Active @b
 *       @TR Part:          @TD translator1Active
 *       @TR Appearance:    @TD Yellow version of transformerTranslator1
 *       @TR Description:   @TD Replaces transformerTranslator1 during dragging.
 * 
 *       @TR Resource:      @TD @B transformerTranslator2Active @b
 *       @TR Part:          @TD translator2Active
 *       @TR Appearance:    @TD Yellow version of transformerTranslator2
 *       @TR Description:   @TD Replaces transformerTranslator2 during dragging.
 * 
 *       @TR Resource:      @TD @B transformerTranslator3Active @b
 *       @TR Part:          @TD translator3Active
 *       @TR Appearance:    @TD Yellow version of transformerTranslator3
 *       @TR Description:   @TD Replaces transformerTranslator3 during dragging.
 * 
 *       @TR Resource:      @TD @B transformerTranslator4Active @b
 *       @TR Part:          @TD translator4Active
 *       @TR Appearance:    @TD Yellow version of transformerTranslator4
 *       @TR Description:   @TD Replaces transformerTranslator4 during dragging.
 * 
 *       @TR Resource:      @TD @B transformerTranslator5Active @b
 *       @TR Part:          @TD translator5Active
 *       @TR Appearance:    @TD Yellow version of transformerTranslator5
 *       @TR Description:   @TD Replaces transformerTranslator5 during dragging.
 * 
 *       @TR Resource:      @TD @B transformerTranslator6Active @b
 *       @TR Part:          @TD translator6Active
 *       @TR Appearance:    @TD Yellow version of transformerTranslator6
 *       @TR Description:   @TD Replaces transformerTranslator6 during dragging.
 * 
 *       @TR Resource:      @TD @B transformerRotator1 @b
 *       @TR Part:          @TD rotator1
 *       @TR Appearance:    @TD Green Sphere at end of a stick
 *       @TR Description:   @TD Top knob of transformer. Picking this initiates rotation.
 * 
 *       @TR Resource:      @TD @B transformerRotator2 @b
 *       @TR Part:          @TD rotator2
 *       @TR Appearance:    @TD Green Sphere at end of a stick
 *       @TR Description:   @TD Bottom knob of transformer. Picking this initiates rotation.
 * 
 *       @TR Resource:      @TD @B transformerRotator3 @b
 *       @TR Part:          @TD rotator3
 *       @TR Appearance:    @TD Green Sphere at end of a stick
 *       @TR Description:   @TD Left knob of transformer. Picking this initiates rotation.
 * 
 *       @TR Resource:      @TD @B transformerRotator4 @b
 *       @TR Part:          @TD rotator4
 *       @TR Appearance:    @TD Green Sphere at end of a stick
 *       @TR Description:   @TD Right knob of transformer. Picking this initiates rotation.
 * 
 *       @TR Resource:      @TD @B transformerRotator5 @b
 *       @TR Part:          @TD rotator5
 *       @TR Appearance:    @TD Green Sphere at end of a stick
 *       @TR Description:   @TD Front knob of transformer. Picking this initiates rotation.
 * 
 *       @TR Resource:      @TD @B transformerRotator6 @b
 *       @TR Part:          @TD rotator6
 *       @TR Appearance:    @TD Green Sphere at end of a stick
 *       @TR Description:   @TD Back knob of transformer. Picking this initiates rotation.
 * 
 *       @TR Resource:      @TD @B transformerRotator1Active @b
 *       @TR Part:          @TD rotator1Active
 *       @TR Appearance:    @TD Yellow version of transformerRotator1
 *       @TR Description:   @TD Replaces transformerRotator1 during dragging.
 * 
 *       @TR Resource:      @TD @B transformerRotator2Active @b
 *       @TR Part:          @TD rotator2Active
 *       @TR Appearance:    @TD Yellow version of transformerRotator2
 *       @TR Description:   @TD Replaces transformerRotator2 during dragging.
 * 
 *       @TR Resource:      @TD @B transformerRotator3Active @b
 *       @TR Part:          @TD rotator3Active
 *       @TR Appearance:    @TD Yellow version of transformerRotator3
 *       @TR Description:   @TD Replaces transformerRotator3 during dragging.
 * 
 *       @TR Resource:      @TD @B transformerRotator4Active @b
 *       @TR Part:          @TD rotator4Active
 *       @TR Appearance:    @TD Yellow version of transformerRotator4
 *       @TR Description:   @TD Replaces transformerRotator4 during dragging.
 * 
 *       @TR Resource:      @TD @B transformerRotator5Active @b
 *       @TR Part:          @TD rotator5Active
 *       @TR Appearance:    @TD Yellow version of transformerRotator5
 *       @TR Description:   @TD Replaces transformerRotator5 during dragging.
 * 
 *       @TR Resource:      @TD @B transformerRotator6Active @b
 *       @TR Part:          @TD rotator6Active
 *       @TR Appearance:    @TD Yellow version of transformerRotator6
 *       @TR Description:   @TD Replaces transformerRotator6 during dragging.
 * 
 *       @TR Resource:      @TD @B transformerScale1 @b
 *       @TR Part:          @TD scale1
 *       @TR Appearance:    @TD Small white cube in (+x+y+z) corner of transformer
 *       @TR Description:   @TD Picking this initiates scaling.
 * 
 *       @TR Resource:      @TD @B transformerScale2 @b
 *       @TR Part:          @TD scale2
 *       @TR Appearance:    @TD Small white cube in (+x+y-z) corner of transformer
 *       @TR Description:   @TD Picking this initiates scaling.
 * 
 *       @TR Resource:      @TD @B transformerScale3 @b
 *       @TR Part:          @TD scale3
 *       @TR Appearance:    @TD Small white cube in (+x-y+z) corner of transformer
 *       @TR Description:   @TD Picking this initiates scaling.
 * 
 *       @TR Resource:      @TD @B transformerScale4 @b
 *       @TR Part:          @TD scale4
 *       @TR Appearance:    @TD Small white cube in (+x-y-z) corner of transformer
 *       @TR Description:   @TD Picking this initiates scaling.
 * 
 *       @TR Resource:      @TD @B transformerScale5 @b
 *       @TR Part:          @TD scale5
 *       @TR Appearance:    @TD Small white cube in (-x+y+z) corner of transformer
 *       @TR Description:   @TD Picking this initiates scaling.
 * 
 *       @TR Resource:      @TD @B transformerScale6 @b
 *       @TR Part:          @TD scale6
 *       @TR Appearance:    @TD Small white cube in (-x+y-z) corner of transformer
 *       @TR Description:   @TD Picking this initiates scaling.
 * 
 *       @TR Resource:      @TD @B transformerScale7 @b
 *       @TR Part:          @TD scale7
 *       @TR Appearance:    @TD Small white cube in (-x-y+z) corner of transformer
 *       @TR Description:   @TD Picking this initiates scaling.
 * 
 *       @TR Resource:      @TD @B transformerScale8 @b
 *       @TR Part:          @TD scale8
 *       @TR Appearance:    @TD Small white cube in (-x-y-z) corner of transformer
 *       @TR Description:   @TD Picking this initiates scaling.
 * 
 *       @TR Resource:      @TD @B transformerScale1Active @b
 *       @TR Part:          @TD scale1Active
 *       @TR Appearance:    @TD Yellow version of transformerScale1Active
 *       @TR Description:   @TD Replaces transformerScale1Active during dragging.
 * 
 *       @TR Resource:      @TD @B transformerScale2Active @b
 *       @TR Part:          @TD scale2Active
 *       @TR Appearance:    @TD Yellow version of transformerScale2Active
 *       @TR Description:   @TD Replaces transformerScale2Active during dragging.
 * 
 *       @TR Resource:      @TD @B transformerScale3Active @b
 *       @TR Part:          @TD scale3Active
 *       @TR Appearance:    @TD Yellow version of transformerScale3Active
 *       @TR Description:   @TD Replaces transformerScale3Active during dragging.
 * 
 *       @TR Resource:      @TD @B transformerScale4Active @b
 *       @TR Part:          @TD scale4Active
 *       @TR Appearance:    @TD Yellow version of transformerScale4Active
 *       @TR Description:   @TD Replaces transformerScale4Active during dragging.
 * 
 *       @TR Resource:      @TD @B transformerScale5Active @b
 *       @TR Part:          @TD scale5Active
 *       @TR Appearance:    @TD Yellow version of transformerScale5Active
 *       @TR Description:   @TD Replaces transformerScale5Active during dragging.
 * 
 *       @TR Resource:      @TD @B transformerScale6Active @b
 *       @TR Part:          @TD scale6Active
 *       @TR Appearance:    @TD Yellow version of transformerScale6Active
 *       @TR Description:   @TD Replaces transformerScale6Active during dragging.
 * 
 *       @TR Resource:      @TD @B transformerScale7Active @b
 *       @TR Part:          @TD scale7Active
 *       @TR Appearance:    @TD Yellow version of transformerScale7Active
 *       @TR Description:   @TD Replaces transformerScale7Active during dragging.
 * 
 *       @TR Resource:      @TD @B transformerScale8Active @b
 *       @TR Part:          @TD scale8Active
 *       @TR Appearance:    @TD Yellow version of transformerScale8Active
 *       @TR Description:   @TD Replaces transformerScale8Active during dragging.
 * 
 *       @TR Resource:      @TD @B transformerXAxisFeedbackActive @b
 *       @TR Part:          @TD xAxisFeedbackActive
 *       @TR Appearance:    @TD Yellow arrow along X axis
 *       @TR Description:   @TD Displayed when translating if X direction is permitted.
 * 
 *       @TR Resource:      @TD @B transformerXAxisFeedbackSelect @b
 *       @TR Part:          @TD xAxisFeedbackSelect
 *       @TR Appearance:    @TD Orange arrow along X axis
 *       @TR Description:   @TD Displayed when awaiting gesture to pick between X axis and another direction(s).
 * 
 *       @TR Resource:      @TD @B transformerYAxisFeedbackActive @b
 *       @TR Part:          @TD yAxisFeedbackActive
 *       @TR Appearance:    @TD Yellow arrow along Y axis
 *       @TR Description:   @TD Displayed when translating if Y direction is permitted.
 * 
 *       @TR Resource:      @TD @B transformerYAxisFeedbackSelect @b
 *       @TR Part:          @TD yAxisFeedbackSelect
 *       @TR Appearance:    @TD Orange arrow along Y axis
 *       @TR Description:   @TD Displayed when awaiting gesture to pick between Y axis and another direction(s).
 * 
 *       @TR Resource:      @TD @B transformerZAxisFeedbackActive @b
 *       @TR Part:          @TD zAxisFeedbackActive
 *       @TR Appearance:    @TD Yellow arrow along Z axis
 *       @TR Description:   @TD Displayed when translating if Z direction is permitted.
 * 
 *       @TR Resource:      @TD @B transformerZAxisFeedbackSelect @b
 *       @TR Part:          @TD zAxisFeedbackSelect
 *       @TR Appearance:    @TD Orange arrow along Z axis
 *       @TR Description:   @TD Displayed when awaiting gesture to pick between Z axis and another direction(s).
 * 
 *       @TR Resource:      @TD @B transformerXCrosshairFeedback @b
 *       @TR Part:          @TD xCrosshairFeedback
 *       @TR Appearance:    @TD Yellow crossHair in y-z plane
 *       @TR Description:   @TD Displayed when translating perpendicular to y-z plane.
 * 
 *       @TR Resource:      @TD @B transformerYCrosshairFeedback @b
 *       @TR Part:          @TD yCrosshairFeedback
 *       @TR Appearance:    @TD Yellow crossHair in x-z plane
 *       @TR Description:   @TD Displayed when translating perpendicular to x-z plane.
 * 
 *       @TR Resource:      @TD @B transformerZCrosshairFeedback @b
 *       @TR Part:          @TD zCrosshairFeedback
 *       @TR Appearance:    @TD Yellow crossHair in x-y plane
 *       @TR Description:   @TD Displayed when translating perpendicular to x-y plane.
 * 
 *       @TR Resource:      @TD @B transformerXCircleFeedback @b
 *       @TR Part:          @TD xCircleFeedback
 *       @TR Appearance:    @TD Purple Unit Circle about X axis
 *       @TR Description:   @TD Displayed when rotating about X axis
 * 
 *       @TR Resource:      @TD @B transformerYCircleFeedback @b
 *       @TR Part:          @TD yCircleFeedback
 *       @TR Appearance:    @TD Purple Unit Circle about Y axis
 *       @TR Description:   @TD Displayed when rotating about Y axis
 * 
 *       @TR Resource:      @TD @B transformerZCircleFeedback @b
 *       @TR Part:          @TD zCircleFeedback
 *       @TR Appearance:    @TD Purple Unit Circle about Z axis
 *       @TR Description:   @TD Displayed when rotating about Z axis
 * 
 *       @TR Resource:      @TD @B transformerRadialFeedback @b
 *       @TR Part:          @TD radialFeedback
 *       @TR Appearance:    @TD Purple Rays emanating from center through corners
 *       @TR Description:   @TD Displayed when scaling uniformly about center.
 * 
 *       @TR Resource:      @TD @B transformerTranslateBoxFeedback @b
 *       @TR Part:          @TD translateBoxFeedback
 *       @TR Appearance:    @TD Purple Box with one bright yellow side
 *       @TR Description:   @TD Displayed when translating. Automatically oriented so yellow side matches
 *                           selected face.
 * 
 *       @TR Resource:      @TD @B transformerPosXWallFeedback @b
 *       @TR Part:          @TD posXWallFeedback
 *       @TR Appearance:    @TD Purple Plane along Right side of transformer
 *       @TR Description:   @TD Displayed when &lt;Control&gt; scaling and keeping right side fixed.
 * 
 *       @TR Resource:      @TD @B transformerPosYWallFeedback @b
 *       @TR Part:          @TD posYWallFeedback
 *       @TR Appearance:    @TD Purple Plane along Top side of transformer
 *       @TR Description:   @TD Displayed when &lt;Control&gt; scaling and keeping top side fixed.
 * 
 *       @TR Resource:      @TD @B transformerPosZWallFeedback @b
 *       @TR Part:          @TD posZWallFeedback
 *       @TR Appearance:    @TD Purple Plane along Front side of transformer
 *       @TR Description:   @TD Displayed when &lt;Control&gt; scaling and keeping front side fixed.
 * 
 *       @TR Resource:      @TD @B transformerNegXWallFeedback @b
 *       @TR Part:          @TD negXWallFeedback
 *       @TR Appearance:    @TD Purple Plane along Left side of transformer
 *       @TR Description:   @TD Displayed when &lt;Control&gt; scaling and keeping left side fixed.
 * 
 *       @TR Resource:      @TD @B transformerNegYWallFeedback @b
 *       @TR Part:          @TD negYWallFeedback
 *       @TR Appearance:    @TD Purple Plane along Bottom side of transformer
 *       @TR Description:   @TD Displayed when &lt;Control&gt; scaling and keeping bottom side fixed.
 * 
 *       @TR Resource:      @TD @B transformerNegZWallFeedback @b
 *       @TR Part:          @TD negZWallFeedback
 *       @TR Appearance:    @TD Purple Plane along Back side of transformer
 *       @TR Description:   @TD Displayed when &lt;Control&gt; scaling and keeping back side fixed.
 * 
 *    @TABLE_END
 * 
 * @CATALOG_PARTS
 *    All Parts
 *    @TABLE_CATALOG_PART
 *       @TR   callbackList           @TD   NodeKitListPart  @TD    --      @TD   yes     
 *       @TR   surroundScale          @TD   SurroundScale    @TD    --      @TD   yes     
 *       @TR   translator1            @TD   Separator        @TD    --      @TD   yes     
 *       @TR   translator1Active      @TD   Separator        @TD    --      @TD   yes     
 *       @TR   translator2            @TD   Separator        @TD    --      @TD   yes     
 *       @TR   translator2Active      @TD   Separator        @TD    --      @TD   yes     
 *       @TR   translator3            @TD   Separator        @TD    --      @TD   yes     
 *       @TR   translator3Active      @TD   Separator        @TD    --      @TD   yes     
 *       @TR   translator4            @TD   Separator        @TD    --      @TD   yes     
 *       @TR   translator4Active      @TD   Separator        @TD    --      @TD   yes     
 *       @TR   translator5            @TD   Separator        @TD    --      @TD   yes     
 *       @TR   translator5Active      @TD   Separator        @TD    --      @TD   yes     
 *       @TR   translator6            @TD   Separator        @TD    --      @TD   yes     
 *       @TR   translator6Active      @TD   Separator        @TD    --      @TD   yes     
 *       @TR   rotator1               @TD   Separator        @TD    --      @TD   yes     
 *       @TR   rotator1Active         @TD   Separator        @TD    --      @TD   yes     
 *       @TR   rotator2               @TD   Separator        @TD    --      @TD   yes     
 *       @TR   rotator2Active         @TD   Separator        @TD    --      @TD   yes     
 *       @TR   rotator3               @TD   Separator        @TD    --      @TD   yes     
 *       @TR   rotator3Active         @TD   Separator        @TD    --      @TD   yes     
 *       @TR   rotator4               @TD   Separator        @TD    --      @TD   yes     
 *       @TR   rotator4Active         @TD   Separator        @TD    --      @TD   yes     
 *       @TR   rotator5               @TD   Separator        @TD    --      @TD   yes     
 *       @TR   rotator5Active         @TD   Separator        @TD    --      @TD   yes     
 *       @TR   rotator6               @TD   Separator        @TD    --      @TD   yes     
 *       @TR   rotator6Active         @TD   Separator        @TD    --      @TD   yes     
 *       @TR   scale1                 @TD   Separator        @TD    --      @TD   yes     
 *       @TR   scale1Active           @TD   Separator        @TD    --      @TD   yes     
 *       @TR   scale2                 @TD   Separator        @TD    --      @TD   yes     
 *       @TR   scale2Active           @TD   Separator        @TD    --      @TD   yes     
 *       @TR   scale3                 @TD   Separator        @TD    --      @TD   yes     
 *       @TR   scale3Active           @TD   Separator        @TD    --      @TD   yes     
 *       @TR   scale4                 @TD   Separator        @TD    --      @TD   yes     
 *       @TR   scale4Active           @TD   Separator        @TD    --      @TD   yes     
 *       @TR   scale5                 @TD   Separator        @TD    --      @TD   yes     
 *       @TR   scale5Active           @TD   Separator        @TD    --      @TD   yes     
 *       @TR   scale6                 @TD   Separator        @TD    --      @TD   yes     
 *       @TR   scale6Active           @TD   Separator        @TD    --      @TD   yes     
 *       @TR   scale7                 @TD   Separator        @TD    --      @TD   yes     
 *       @TR   scale7Active           @TD   Separator        @TD    --      @TD   yes     
 *       @TR   scale8                 @TD   Separator        @TD    --      @TD   yes     
 *       @TR   scale8Active           @TD   Separator        @TD    --      @TD   yes     
 *       @TR   xAxisFeedbackActive    @TD      Separator     @TD    --      @TD   yes     
 *       @TR   xAxisFeedbackSelect    @TD      Separator     @TD    --      @TD   yes     
 *       @TR   xCrosshairFeedback     @TD      Separator     @TD    --      @TD   yes     
 *       @TR   yAxisFeedbackActive    @TD      Separator     @TD    --      @TD   yes     
 *       @TR   yAxisFeedbackSelect    @TD      Separator     @TD    --      @TD   yes     
 *       @TR   yCrosshairFeedback     @TD      Separator     @TD    --      @TD   yes     
 *       @TR   zAxisFeedbackActive    @TD      Separator     @TD    --      @TD   yes     
 *       @TR   zAxisFeedbackSelect    @TD      Separator     @TD    --      @TD   yes     
 *       @TR   zCrosshairFeedback     @TD      Separator     @TD    --      @TD   yes     
 *       @TR   translateBoxFeedback   @TD      Separator     @TD    --      @TD   yes     
 *       @TR   scaleBoxFeedback       @TD   Separator        @TD    --      @TD   yes     
 *       @TR   posXWallFeedback       @TD   Separator        @TD    --      @TD   yes     
 *       @TR   posXRoundWallFeedback  @TD      Separator     @TD    --      @TD   yes     
 *       @TR   posYWallFeedback       @TD   Separator        @TD    --      @TD   yes     
 *       @TR   posYRoundWallFeedback  @TD      Separator     @TD    --      @TD   yes     
 *       @TR   posZWallFeedback       @TD   Separator        @TD    --      @TD   yes     
 *       @TR   posZRoundWallFeedback  @TD      Separator     @TD    --      @TD   yes     
 *       @TR   negXWallFeedback       @TD   Separator        @TD    --      @TD   yes     
 *       @TR   negXRoundWallFeedback  @TD      Separator     @TD    --      @TD   yes     
 *       @TR   negYWallFeedback       @TD   Separator        @TD    --      @TD   yes     
 *       @TR   negYRoundWallFeedback  @TD      Separator     @TD    --      @TD   yes     
 *       @TR   negZWallFeedback       @TD   Separator        @TD    --      @TD   yes     
 *       @TR   negZRoundWallFeedback  @TD      Separator     @TD    --      @TD   yes     
 *       @TR   radialFeedback         @TD   Separator        @TD    --      @TD   yes     
 *       @TR   xCircleFeedback        @TD   Separator        @TD    --      @TD   yes     
 *       @TR   yCircleFeedback        @TD   Separator        @TD    --      @TD   yes     
 *       @TR   zCircleFeedback        @TD   Separator        @TD    --      @TD   yes     
 *    @TABLE_END
 * 
 *    Extra Information for List Parts from Above Table
 *    @TABLE_LIST_PART
 *       @TR   callbackList           @TD   Separator        @TD   Callback, EventCallback
 *    @TABLE_END
 * 
 * @SEE_ALSO
 *    SoDragger,
 *    SoInteractionKit,
 *    SoLocateHighlight,
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
 *    SoTranslate1Dragger,
 *    SoTranslate2Dragger
 * 
 * 
 */ 

class INVENTOR_API SoTransformerDragger : public SoDragger {

  SO_KIT_HEADER(SoTransformerDragger);

  SO_KIT_CATALOG_ENTRY_HEADER(overallStyle);

  // For making the dragger surround what lies above it.
  SO_KIT_CATALOG_ENTRY_HEADER(surroundScale);

  SO_KIT_CATALOG_ENTRY_HEADER(translatorSep);
  SO_KIT_CATALOG_ENTRY_HEADER(translator1Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(translator1LocateGroup);
  SO_KIT_CATALOG_ENTRY_HEADER(translator1);
  SO_KIT_CATALOG_ENTRY_HEADER(translator1Active);
  SO_KIT_CATALOG_ENTRY_HEADER(translator2Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(translator2LocateGroup);
  SO_KIT_CATALOG_ENTRY_HEADER(translator2);
  SO_KIT_CATALOG_ENTRY_HEADER(translator2Active);
  SO_KIT_CATALOG_ENTRY_HEADER(translator3Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(translator3LocateGroup);
  SO_KIT_CATALOG_ENTRY_HEADER(translator3);
  SO_KIT_CATALOG_ENTRY_HEADER(translator3Active);
  SO_KIT_CATALOG_ENTRY_HEADER(translator4Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(translator4LocateGroup);
  SO_KIT_CATALOG_ENTRY_HEADER(translator4);
  SO_KIT_CATALOG_ENTRY_HEADER(translator4Active);
  SO_KIT_CATALOG_ENTRY_HEADER(translator5Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(translator5LocateGroup);
  SO_KIT_CATALOG_ENTRY_HEADER(translator5);
  SO_KIT_CATALOG_ENTRY_HEADER(translator5Active);
  SO_KIT_CATALOG_ENTRY_HEADER(translator6Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(translator6LocateGroup);
  SO_KIT_CATALOG_ENTRY_HEADER(translator6);
  SO_KIT_CATALOG_ENTRY_HEADER(translator6Active);


  SO_KIT_CATALOG_ENTRY_HEADER(rotatorSep);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator1Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator1LocateGroup);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator1);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator1Active);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator2Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator2LocateGroup);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator2);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator2Active);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator3Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator3LocateGroup);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator3);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator3Active);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator4Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator4LocateGroup);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator4);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator4Active);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator5Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator5LocateGroup);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator5);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator5Active);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator6Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator6LocateGroup);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator6);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator6Active);

  SO_KIT_CATALOG_ENTRY_HEADER(scaleSep);
  SO_KIT_CATALOG_ENTRY_HEADER(scale1Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(scale1LocateGroup);
  SO_KIT_CATALOG_ENTRY_HEADER(scale1);
  SO_KIT_CATALOG_ENTRY_HEADER(scale1Active);
  SO_KIT_CATALOG_ENTRY_HEADER(scale2Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(scale2LocateGroup);
  SO_KIT_CATALOG_ENTRY_HEADER(scale2);
  SO_KIT_CATALOG_ENTRY_HEADER(scale2Active);
  SO_KIT_CATALOG_ENTRY_HEADER(scale3Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(scale3LocateGroup);
  SO_KIT_CATALOG_ENTRY_HEADER(scale3);
  SO_KIT_CATALOG_ENTRY_HEADER(scale3Active);
  SO_KIT_CATALOG_ENTRY_HEADER(scale4Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(scale4LocateGroup);
  SO_KIT_CATALOG_ENTRY_HEADER(scale4);
  SO_KIT_CATALOG_ENTRY_HEADER(scale4Active);
  SO_KIT_CATALOG_ENTRY_HEADER(scale5Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(scale5LocateGroup);
  SO_KIT_CATALOG_ENTRY_HEADER(scale5);
  SO_KIT_CATALOG_ENTRY_HEADER(scale5Active);
  SO_KIT_CATALOG_ENTRY_HEADER(scale6Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(scale6LocateGroup);
  SO_KIT_CATALOG_ENTRY_HEADER(scale6);
  SO_KIT_CATALOG_ENTRY_HEADER(scale6Active);
  SO_KIT_CATALOG_ENTRY_HEADER(scale7Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(scale7LocateGroup);
  SO_KIT_CATALOG_ENTRY_HEADER(scale7);
  SO_KIT_CATALOG_ENTRY_HEADER(scale7Active);
  SO_KIT_CATALOG_ENTRY_HEADER(scale8Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(scale8LocateGroup);
  SO_KIT_CATALOG_ENTRY_HEADER(scale8);
  SO_KIT_CATALOG_ENTRY_HEADER(scale8Active);

  SO_KIT_CATALOG_ENTRY_HEADER(axisFeedbackSep);
  SO_KIT_CATALOG_ENTRY_HEADER(axisFeedbackLocation);
  SO_KIT_CATALOG_ENTRY_HEADER(xAxisFeedbackSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(xAxisFeedbackActive);
  SO_KIT_CATALOG_ENTRY_HEADER(xAxisFeedbackSelect);
  SO_KIT_CATALOG_ENTRY_HEADER(xCrosshairFeedback);
  SO_KIT_CATALOG_ENTRY_HEADER(yAxisFeedbackSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(yAxisFeedbackActive);
  SO_KIT_CATALOG_ENTRY_HEADER(yAxisFeedbackSelect);
  SO_KIT_CATALOG_ENTRY_HEADER(yCrosshairFeedback);
  SO_KIT_CATALOG_ENTRY_HEADER(zAxisFeedbackSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(zAxisFeedbackActive);
  SO_KIT_CATALOG_ENTRY_HEADER(zAxisFeedbackSelect);
  SO_KIT_CATALOG_ENTRY_HEADER(zCrosshairFeedback);

  SO_KIT_CATALOG_ENTRY_HEADER(translateBoxFeedbackSep);
  SO_KIT_CATALOG_ENTRY_HEADER(translateBoxFeedbackSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(translateBoxFeedbackRotation);
  SO_KIT_CATALOG_ENTRY_HEADER(translateBoxFeedback);

  SO_KIT_CATALOG_ENTRY_HEADER(scaleBoxFeedbackSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(scaleBoxFeedback);

  SO_KIT_CATALOG_ENTRY_HEADER(posXWallFeedbackSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(posXWallFeedback);
  SO_KIT_CATALOG_ENTRY_HEADER(posXRoundWallFeedback);
  SO_KIT_CATALOG_ENTRY_HEADER(posYWallFeedbackSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(posYWallFeedback);
  SO_KIT_CATALOG_ENTRY_HEADER(posYRoundWallFeedback);
  SO_KIT_CATALOG_ENTRY_HEADER(posZWallFeedbackSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(posZWallFeedback);
  SO_KIT_CATALOG_ENTRY_HEADER(posZRoundWallFeedback);
  SO_KIT_CATALOG_ENTRY_HEADER(negXWallFeedbackSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(negXWallFeedback);
  SO_KIT_CATALOG_ENTRY_HEADER(negXRoundWallFeedback);
  SO_KIT_CATALOG_ENTRY_HEADER(negYWallFeedbackSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(negYWallFeedback);
  SO_KIT_CATALOG_ENTRY_HEADER(negYRoundWallFeedback);
  SO_KIT_CATALOG_ENTRY_HEADER(negZWallFeedbackSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(negZWallFeedback);
  SO_KIT_CATALOG_ENTRY_HEADER(negZRoundWallFeedback);

  SO_KIT_CATALOG_ENTRY_HEADER(radialFeedbackSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(radialFeedback);

  SO_KIT_CATALOG_ENTRY_HEADER(circleFeedbackSep);
  SO_KIT_CATALOG_ENTRY_HEADER(circleFeedbackTransformSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(circleFeedbackAntiSquish);
  SO_KIT_CATALOG_ENTRY_HEADER(circleFeedbackTransform);
  SO_KIT_CATALOG_ENTRY_HEADER(xCircleFeedbackSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(xCircleFeedback);
  SO_KIT_CATALOG_ENTRY_HEADER(yCircleFeedbackSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(yCircleFeedback);
  SO_KIT_CATALOG_ENTRY_HEADER(zCircleFeedbackSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(zCircleFeedback);


 public:
  /**
   * Constructor.
   */
  SoTransformerDragger();

  /**
   * Orientation of the dragger.
   * 
   */
  SoSFRotation    rotation;
  /**
   * Position of the dragger.
   * 
   */
  SoSFVec3f       translation;
  /**
   * Scale of the dragger.
   * 
   */
  SoSFVec3f       scaleFactor;
  /**
   * Specifies the minimum dot product between @B eyeDir @b and @B rotPlane @b
   * normal before switching from record-player-type rotation to rolling-pin-type
   * rotation. This transition is made so that rotations don't get screwy when the
   * circle is edge-on. Lies in range [0-1]. Best to leave this alone.
   * 
   */
  SoSFFloat       minDiscRotDot;

  /**
   * Tells the dragger to unsquish its rotation and scale knobs during the next
   * traversal. Ordinarily, the knobs are only unsquished upon readin from file and
   * when the mouse button is released at the end of a drag. If you want this to
   * happen more often, then you should call this method.
   */
  void unsquishKnobs();

  /**
   * Returns whether or not locate highlighting is used.
   */
  SbBool isLocateHighlighting() { return locateHighlightOn; }
  /**
   * Sets whether or not locate highlighting is used. Default is TRUE.
   */
  void setLocateHighlighting( SbBool onOff );

  /**
   * Sets the colinear threshold.
   * When picking a direction for constraining based on gesture, this parameter
   * determines how many pixels must separate two axes before they are regarded as
   * distinct. If they are deemed "the same" then the shorter of the two will be
   * discarded.  Default is 4.
   */
  static void setColinearThreshold(int newVal);
  /**
   * Returns the colinear threshold. This parameter determines the number of
   * pixels that must separate two axes before they are regarded as distinct.
   */
  static int getColinearThreshold();

 SoEXTENDER public:

  // These convert points and directions from the space of the unit
  // box to world space. Can be useful during callbacks.
  SbVec3f getBoxPointInWorldSpace( const SbVec3f &pointOnUnitBox );
  SbVec3f getBoxDirInWorldSpace( const SbVec3f &dirOnUnitBox );
  SbVec3f getWorldPointInBoxSpace( const SbVec3f &pointInWorldSpace );
  SbVec2f getWorldPointInPixelSpace( const SbVec3f &thePoint );

  // Callbacks would like to know this sometimes.
  // It's the location in bbox space of the point about which the 
  // transformer is rotating or scaling.  It's different depending on 
  // which part is picked (determined by getCurrentState()) and
  // which modifier keys are down.
  SbVec3f getInteractiveCenterInBoxSpace() 
    { return interactiveCenterInBoxSpace; }

 SoINTERNAL public:
  static void         initClass();    // initialize the class
  static void exitClass();

  enum State
  { INACTIVE, 
    RIT_X_ROTATE,  TOP_Y_ROTATE,  FNT_Z_ROTATE, 
    LFT_X_ROTATE,  BOT_Y_ROTATE,  BAK_Z_ROTATE, 

    PX_PY_PZ_3D_SCALE, PX_PY_NZ_3D_SCALE, PX_NY_PZ_3D_SCALE, 
    PX_NY_NZ_3D_SCALE, NX_PY_PZ_3D_SCALE, NX_PY_NZ_3D_SCALE, 
    NX_NY_PZ_3D_SCALE, NX_NY_NZ_3D_SCALE, 

    RIT_TRANSLATE,  TOP_TRANSLATE,  FNT_TRANSLATE,
    LFT_TRANSLATE,  BOT_TRANSLATE,  BAK_TRANSLATE };

  State getCurrentState() { return currentState; }

 protected:

  // Callbacks for drag start, motion, and finish
  static void startCB( void *, SoDragger * );
  static void motionCB( void *, SoDragger * );
  static void finishCB( void *, SoDragger * );
    
  SoFieldSensor *translFieldSensor;
  SoFieldSensor *scaleFieldSensor;
  SoFieldSensor *rotateFieldSensor;
  static void   fieldSensorCB( void *, SoSensor * );
  static void valueChangedCB( void *, SoDragger * );

  // Callbacks for pressing and releasing the meta keys
  static void metaKeyChangeCB( void *, SoDragger *);

  // These really do the work during startCB, motionCB, and finishCB
  void        dragStart();
  void        drag();
  void        dragFinish();

  // Sets switch values for all parts in the scale, rotate, and translate
  // assemblies.
  void setAllPartSwitches( int     scaleAssemblyWhich,
                           int    rotateAssemblyWhich,
                           int translateAssemblyWhich );

  // detach/attach any sensors, callbacks, and/or field connections.
  // Called by:            start/end of SoBaseKit::readInstance
  // and on new copy by:   start/end of SoBaseKit::copy.
  // Classes that redefine must call setUpConnections(TRUE,TRUE) 
  // at end of constructor.
  // Returns the state of the node when this was called.
  virtual SbBool setUpConnections( SbBool onOff, SbBool doItAlways = FALSE );

  virtual void setDefaultOnNonWritingFields();

  virtual ~SoTransformerDragger();

  // Finds all SoAntiSquish nodes in subgraph and puts them in list.
  void updateAntiSquishList();
  // Tells all nodes in the antiSquishList to recalculate next time through.
  SoNodeList antiSquishList;

  int    getMouseGestureDirection(SbBool xAllowed, SbBool yAllowed, 
                                  SbBool zAllowed);

  static int getIgnoreAxis(SbVec2f axis[3][2], SbBool xAllowed, 
                           SbBool yAllowed, SbBool zAllowed );

  static void makeMinorAxisPerpendicularIfColinear( SbVec2f origin, 
                                                    SbVec2f axisEnds[3][2], int indexA, int indexB );

  static SbBool isColinear(SbVec2f a1[2], SbVec2f a2[2], int pixels);

 private:

  State               currentState;     
  int                 currentDir;   // Used for 1-D operations,
  // this variable records the current
  // axis being used.
  // when doing 1-D rot, can rotate as disc (like spinning a turntable) or 
  // cylinder (like rolling a rolling pin). This flag says which.
  SbBool              rotatingAsDisc;

  SbPlaneProjector           *planeProj;
  SbLineProjector            *lineProj;
  SbSphereSectionProjector   *sphereProj;
  SbCylinderPlaneProjector   *cylProj;

  State           restartState;   // used by meta callback. 
  SbVec3f         worldRestartPt; // used during interaction

  SbMatrix prevMotionMatrix; // used during rotate interaction
  SbVec3f  prevWorldHitPt;   // used during rotate and translate interaction
  SbVec3f  interactiveCenterInBoxSpace; // used during rotations.

  // used to reset prevWorldHitPt after initializing the cylinder projector.
  // Need to store during rotateInit() since SoDragger provides no method 
  // to retrieve.
  SbVec2f  startNormalizedLocaterPosition; 

  SbBool          altDown, ctlDown, shftDown;  // used to keep track of
  // which meta keys were down.
  SbBool constraining; // Depends on state of shftDown and which part picked.

  // functions which do all the work
  void        setHighlights();
  void        setFeedback();
  void        setFeedbackForTranslate();
  void        setFeedbackForScale();
  void        setFeedbackForRotate();

  State               getStateFromPick();
  SbBool              translateInit();
  SbBool              rotateInit();
  SbBool              scaleInit();

  SbBool              translateDrag();
  SbBool              scaleDrag();

  SbBool              rotateDrag();
  SbBool              rotateConstrainedDrag();
  SbBool              rotateConstrainedDiscDrag();
  SbBool              rotateConstrainedCylindricalDrag();

  void initSphereProjector();
  void initDiscProjector();
  void initCylinderProjector();

  SbBool getShouldRotateAsDisc();
  int getConstrainedRotationAxis();

  // character strings from which the shared geometry is read
  static const char geomBuffer[];            

  void setAllDefaultParts();

  SbBool locateHighlightOn;

  static int colinearThreshold;

  // These subroutines construct the catalog. They normally would just
  // sit in the constructor, but the compiler doesn't like such huge
  // methods so we broke it up into small chunks.
  void makeCatalog();
  void makeTranslaterCatalogParts();
  void makeRotaterCatalogParts();
  void makeScalerCatalogParts();
  void makeAxisFeedbackCatalogParts();
  void makeBoxFeedbackCatalogParts();
  void makeWallFeedbackCatalogParts();
  void makeRadialFeedbackCatalogParts();
  void makeCircleFeedbackCatalogParts();

};

#endif /* _SO_TRANSFORMER_DRAGGER_ */

