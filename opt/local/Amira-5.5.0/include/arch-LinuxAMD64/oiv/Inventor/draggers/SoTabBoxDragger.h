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


#ifndef  _SO_TAB_BOX_DRAGGER_
#define  _SO_TAB_BOX_DRAGGER_

#include <Inventor/SbLinear.h>
#include <Inventor/draggers/SoDragger.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/sensors/SoSensor.h>

class SoFieldSensor;

/**
 * Cubic object you can translate and scale by dragging with the mouse.
 * 
 * @ingroup draggers
 * 
 * @DESCRIPTION
 *   SoTabBoxDragger is a composite dragger shaped like a box. Inside it are six
 *   SoTabPlaneDraggers which the dragger positions and orients to form a cube. The
 *   operations available in an SoTabPlaneDragger (translation, 1D scaling and 2D
 *   scaling) are available on each face of the cube. Since they each move in their
 *   local space, the dragger may be easily translated or scaled in any direction.
 *   
 *   As a composite dragger, this class makes sure that when one plane is dragged, the
 *   entire box moves together.
 *   
 *   Each SoTabPlaneDragger tries to keep the small tabs a constant size in screen 
 *   space. Every time a drag begins or ends, the size is automatically recalculated
 *   based on the viewing and modeling matrix. But note that the tab size is not
 *   automatically recalculated when the camera moves.  One solution for this is to 
 *   add a viewer finish callback (see for example SoXt::addFinishCallback) and call
 *   the SoTabBoxDragger's adjustScaleTabSize() method in the callback function.
 *
 *   If the dragger becomes too small in one dimension to contain all three tabs
 *   (two corner tabs plus the edge tab), the middle (edge) tab will not be drawn.
 *   If the dragger becomes very small (or flat) in one dimension, it may not be
 *   possible for the user to resize using the tabs.  One solution for this is to
 *   provide a "reset dragger" button in the application.
 *   
 *   When dragging the translator part, press the \<Shift\> key and you can constrain
 *   motion to either the local @B x axis @b or the @B y axis @b. The direction is
 *   determined by your initial mouse gesture after pressing the key. Releasing the
 *   key removes the constraint.
 *   
 *   As each sub-dragger is moved, the SoTabBoxDragger updates its #scaleFactor
 *   and #translation fields. As with all draggers, if you change a field the
 *   dragger will move to match the new settings.
 *   
 *   @B Remember: @b This is @B not @b an SoTransform!. If you want to move other
 *   objects with this dragger, you can either:
 *   
 *     - Use an SoTabBoxManip, which is subclassed from SoTransform. It creates one of
 *       these draggers and uses it as the interface to change its fields. (see the
 *       SoTabBoxManip reference page).
 *   
 *     - Use field-to-field connections to connect the fields of this dragger to those
 *       of any SoTransformation node.
 *   
 *   You can change the parts in any instance of this dragger using setPart().
 *   The default part geometries are defined as resources for this SoTabBoxDragger
 *   class. They are detailed below in the Dragger Resources section of the online
 *   reference page for this class. You can make your program use different default
 *   resources for the parts by copying the file
 *   @B $OIVHOME/data/draggerDefaults/tabBoxDragger.iv @b into your own directory,
 *   editing the file, and then setting the environment variable
 *   @B SO_DRAGGER_DIR @b to be a path to that directory.
 * 
 * @FILE_FORMAT_DEFAULT
 *    TabBoxDragger {
 *    @TABLE_FILE_FORMAT
 *       @TR renderCaching                @TD AUTO
 *       @TR boundingBoxCaching           @TD AUTO
 *       @TR renderCulling                @TD AUTO
 *       @TR pickCulling                  @TD AUTO
 *       @TR isActive                     @TD FALSE
 *       @TR translation                  @TD 0 0 0
 *       @TR scaleFactor                  @TD 1 1 1
 *       @TR callbackList                 @TD NULL
 *       @TR surroundScale                @TD NULL
 *       @TR tabPlane1                    @TD TabPlaneDragger {
 *       @TR      }                       @TD 
 *       @TR tabPlane2                    @TD TabPlaneDragger {
 *       @TR      }                       @TD 
 *       @TR tabPlane3                    @TD TabPlaneDragger {
 *       @TR      }                       @TD 
 *       @TR tabPlane4                    @TD TabPlaneDragger {
 *       @TR      }                       @TD 
 *       @TR tabPlane5                    @TD TabPlaneDragger {
 *       @TR      }                       @TD 
 *       @TR tabPlane6                    @TD TabPlaneDragger {
 *       @TR      }                       @TD 
 *       @TR boxGeom                      @TD \<tabBoxBoxGeom resource\>
 *       @TR tabPlane1.translator         @TD \<tabBoxTranslator resource\>
 *       @TR tabPlane2.translator         @TD \<tabBoxTranslator resource\>
 *       @TR tabPlane3.translator         @TD \<tabBoxTranslator resource\>
 *       @TR tabPlane4.translator         @TD \<tabBoxTranslator resource\>
 *       @TR tabPlane5.translator         @TD \<tabBoxTranslator resource\>
 *       @TR tabPlane6.translator         @TD \<tabBoxTranslator resource\>
 *       @TR tabPlane1.scaleTabMaterial   @TD \<tabBoxScaleTabMaterial resource\>
 *       @TR tabPlane2.scaleTabMaterial   @TD \<tabBoxScaleTabMaterial resource\>
 *       @TR tabPlane3.scaleTabMaterial   @TD \<tabBoxScaleTabMaterial resource\>
 *       @TR tabPlane4.scaleTabMaterial   @TD \<tabBoxScaleTabMaterial resource\>
 *       @TR tabPlane5.scaleTabMaterial   @TD \<tabBoxScaleTabMaterial resource\>
 *       @TR tabPlane6.scaleTabMaterial   @TD \<tabBoxScaleTabMaterial resource\>
 *       @TR tabPlane1.scaleTabHints      @TD \<tabBoxScaleTabHints resource\>
 *       @TR tabPlane2.scaleTabHints      @TD \<tabBoxScaleTabHints resource\>
 *       @TR tabPlane3.scaleTabHints      @TD \<tabBoxScaleTabHints resource\>
 *       @TR tabPlane4.scaleTabHints      @TD \<tabBoxScaleTabHints resource\>
 *       @TR tabPlane5.scaleTabHints      @TD \<tabBoxScaleTabHints resource\>
 *       @TR tabPlane6.scaleTabHints      @TD \<tabBoxScaleTabHints resource\>
 *    @TABLE_END
 *    }
 * 
 * 
 * @DRAGGER_RESOURCES
 *    @TABLE_DRAGGER_RESOURCES
 *       @TR Resource:      @TD @B tabBoxTranslator @b
 *       @TR Parts:         @TD tabPlane1.translator@BR
 *                               tabPlane2.translator@BR
 *                               tabPlane3.translator@BR
 *                               tabPlane4.translator@BR
 *                               tabPlane5.translator@BR
 *                               tabPlane6.translator 
 *       @TR Appearance:    @TD Outline of a Square. The region within is pickable
 *       @TR Description:   @TD Begins translation within the plane. The tabBox places and orients each tabPlane
 *                           so that these squares form a box.
 * 
 *       @TR Resource:      @TD @B tabBoxScaleTabMaterial @b
 *       @TR Parts:         @TD tabPlane1.scaleTabMaterial@BR
 *                               tabPlane2.scaleTabMaterial@BR
 *                               tabPlane3.scaleTabMaterial@BR
 *                               tabPlane4.scaleTabMaterial@BR
 *                               tabPlane5.scaleTabMaterial@BR
 *                               tabPlane6.scaleTabMaterial 
 *       @TR Appearance:    @TD Green - half diffuse, half emissive.
 *       @TR Description:   @TD Used as material for scaling tabs.
 * 
 *       @TR Resource:      @TD @B tabBoxScaleTabHints @b
 *       @TR Parts:         @TD tabPlane1.scaleTabHints@BR
 *                               tabPlane2.scaleTabHints@BR
 *                               tabPlane3.scaleTabHints@BR
 *                               tabPlane4.scaleTabHints@BR
 *                               tabPlane5.scaleTabHints@BR
 *                               tabPlane6.scaleTabHints 
 *       @TR Appearance:    @TD shapeHints node:COUNTERCLOCKWISE/SOLID/CONVEX
 *       @TR Description:   @TD Property for the tab nodes.
 * 
 *       @TR Resource:      @TD @B tabBoxBoxGeom @b
 *       @TR Part:          @TD boxGeom
 *       @TR Appearance:    @TD Unpickable gray outline of a box.
 *       @TR Description:   @TD Just feedback.
 * 
 *    @TABLE_END
 * 
 * @CATALOG_PARTS
 *    All Parts
 *    @TABLE_CATALOG_PART
 *       @TR   callbackList   @TD   NodeKitListPart  @TD    --      @TD   yes     
 *       @TR   surroundScale  @TD   SurroundScale    @TD    --      @TD   yes     
 *       @TR   tabPlane1      @TD   TabPlaneDragger  @TD    --      @TD   yes     
 *       @TR   tabPlane2      @TD   TabPlaneDragger  @TD    --      @TD   yes     
 *       @TR   tabPlane3      @TD   TabPlaneDragger  @TD    --      @TD   yes     
 *       @TR   tabPlane4      @TD   TabPlaneDragger  @TD    --      @TD   yes     
 *       @TR   tabPlane5      @TD   TabPlaneDragger  @TD    --      @TD   yes     
 *       @TR   tabPlane6      @TD   TabPlaneDragger  @TD    --      @TD   yes     
 *       @TR   boxGeom        @TD   Separator        @TD    --      @TD   yes     
 *    @TABLE_END
 * 
 *    Extra Information for List Parts from Above Table
 *    @TABLE_LIST_PART
 *       @TR   callbackList   @TD   Separator        @TD   Callback, EventCallback
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
 *    SoTabPlaneDragger,
 *    SoTrackballDragger,
 *    SoTransformBoxDragger,
 *    SoTransformerDragger,
 *    SoTranslate1Dragger,
 *    SoTranslate2Dragger
 * 
 * 
 */ 

class INVENTOR_API SoTabBoxDragger : public SoDragger
{
  SO_KIT_HEADER(SoTabBoxDragger);

  // For making the dragger surround what lies above it.
  SO_KIT_CATALOG_ENTRY_HEADER(surroundScale);

  SO_KIT_CATALOG_ENTRY_HEADER(tabPlane1Sep);
  SO_KIT_CATALOG_ENTRY_HEADER(tabPlane1Xf);
  SO_KIT_CATALOG_ENTRY_HEADER(tabPlane1);
  SO_KIT_CATALOG_ENTRY_HEADER(tabPlane2Sep);
  SO_KIT_CATALOG_ENTRY_HEADER(tabPlane2Xf);
  SO_KIT_CATALOG_ENTRY_HEADER(tabPlane2);
  SO_KIT_CATALOG_ENTRY_HEADER(tabPlane3Sep);
  SO_KIT_CATALOG_ENTRY_HEADER(tabPlane3Xf);
  SO_KIT_CATALOG_ENTRY_HEADER(tabPlane3);
  SO_KIT_CATALOG_ENTRY_HEADER(tabPlane4Sep);
  SO_KIT_CATALOG_ENTRY_HEADER(tabPlane4Xf);
  SO_KIT_CATALOG_ENTRY_HEADER(tabPlane4);
  SO_KIT_CATALOG_ENTRY_HEADER(tabPlane5Sep);
  SO_KIT_CATALOG_ENTRY_HEADER(tabPlane5Xf);
  SO_KIT_CATALOG_ENTRY_HEADER(tabPlane5);
  SO_KIT_CATALOG_ENTRY_HEADER(tabPlane6Sep);
  SO_KIT_CATALOG_ENTRY_HEADER(tabPlane6Xf);
  SO_KIT_CATALOG_ENTRY_HEADER(tabPlane6);

  SO_KIT_CATALOG_ENTRY_HEADER(boxGeom);

 public:
  /**
   * Constructor.
   */
  SoTabBoxDragger();

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

  /**
  * If set to TRUE, handles will be resized at each camera motion
  * 
  * @FIELD_SINCE_OIV 7.0
  */
  SoSFBool resizeHandles;

  /**
   * Cause the scale tab sizes to be re-adjusted on all 6 SoTabPlaneDraggers so that
   * they remain a near constant screen space size. This happens automatically upon
   * dragger finish. Call this to adjust the scale tab sizes at other times, for
   * instance after the camera has changed in a viewer finish \oivnetdoc delegate \else callback \endoivnetdoc.
   */
  void    adjustScaleTabSize();

 SoINTERNAL public:
  static void initClass();  // initialize the class
  static void exitClass();

  int getCurrentState();

protected:

  SoFieldSensor *translFieldSensor;
  SoFieldSensor *scaleFieldSensor;
  SoFieldSensor *resizeHandlesFieldSensor;

  static void resizeHandlesSensorCB( void *, SoSensor * );
  static void fieldSensorCB( void *, SoSensor * );
  static void valueChangedCB( void *, SoDragger * );

  static void invalidateSurroundScaleCB(  void *, SoDragger * );
  static void adjustScaleTabSizeCB(  void *, SoDragger * );

  virtual void handleEvent( SoHandleEventAction *action );

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

  virtual ~SoTabBoxDragger();

 private:
  static const char geomBuffer[];
};    

#endif  /* _SO_TAB_BOX_DRAGGER_ */

