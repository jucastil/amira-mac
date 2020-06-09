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


#ifndef  _SO_TAB_PLANE_DRAGGER_
#define  _SO_TAB_PLANE_DRAGGER_

#include <Inventor/SbLinear.h>
#include <Inventor/sensors/SoSensor.h>
#include <Inventor/projectors/SbLineProjector.h>
#include <Inventor/projectors/SbPlaneProjector.h>
#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/draggers/SoDragger.h>

class SoNode;
class SoCoordinate3;
class SoGLRenderAction;
class SoRayPickAction;
class SoFieldSensor;
class SoSwitch;

/**
 * Object you can translate or scale within a plane by dragging with the mouse.
 * 
 * @ingroup draggers
 * 
 * @DESCRIPTION
 *   SoTabPlaneDragger is a dragger which allows the user to interactively translate
 *   and scale in a plane. It looks like a square white outline with smaller green
 *   squares (or @B tabs @b) set in the corners and along the center of each edge.
 *   Dragging a @B corner tab @b scales the dragger in 2D by scaling about the
 *   opposite corner. Dragging an @B edge tab @b performs 1D scaling about the
 *   opposite edge. Uniform scaling can be enforced by setting the #scaleUniform
 *   field to TRUE. The rest of the dragger is invisible but pickable; selecting it
 *   initiates translation within the plane.
 *   
 *   The dragger tries to keep the small tabs a constant size in screen space.
 *   Before version 7.0, this adjustment was only done when a drag operation
 *   started and ended, or when the #adjustScaleTabSize method was called.
 *   Now as long as the #resizeHandles field is set to TRUE (the default), the tab
 *   size is automatically recalculated whenever the view matrix changes
 *   (normally because the camera position or orientation changed).  
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
 *   When the translator part drags, the dragger updates its #translation field.
 *   The various scaling parts cause changes to both the #scaleFactor and
 *   #translation field, since scaling about a point other than the center adds
 *   translation to the center of the dragger. If you set the field, the dragger will
 *   move accordingly. You can also connect fields of other nodes or engines from
 *   this one to make them follow the dragger's motion.
 *   
 *   You can not change the shape used to draw the tabs. This part is kept privately
 *   and may not be changed; the coordinates for the tabs are edited during
 *   adjustScaleTabSize().
 *   
 *   The SoTabPlaneDragger class does contain three other parts you can change:
 *   @B tabPlaneTranslator @b, @B tabPlaneScaleTabMaterial @b and
 *   @B tabPlaneScaleTabHints @b.
 *   
 *   Each of these is set by default from a resource described in the Dragger
 *   Resources section of the online reference page for this class. You can change
 *   the parts in any instance of this dragger using setPart().
 *   
 *   You can make your program use different default resources for the parts by
 *   copying the file @B $OIVHOME/data/draggerDefaults/tabPlaneDragger.iv @b into
 *   your own directory, editing the file, and then setting the environment variable
 *   @B SO_DRAGGER_DIR @b to be a path to that directory.
 * 
 * @FILE_FORMAT_DEFAULT
 *    TabPlaneDragger {
 *    @TABLE_FILE_FORMAT
 *       @TR renderCaching        @TD AUTO
 *       @TR boundingBoxCaching   @TD AUTO
 *       @TR renderCulling        @TD AUTO
 *       @TR pickCulling          @TD AUTO
 *       @TR isActive             @TD FALSE
 *       @TR resizeHandles        @TD FALSE
 *       @TR translation          @TD 0 0 0
 *       @TR scaleFactor          @TD 1 1 1
 *       @TR scaleUniform         @TD FALSE
 *       @TR twoSidedLighting      @TD FALSE
 *       @TR lineWidth            @TD 1
 *       @TR callbackList         @TD NULL
 *       @TR translator           @TD \<tabPlaneTranslator resource\>
 *       @TR scaleTabMaterial     @TD \<tabPlaneScaleTabMaterial resource\>
 *       @TR scaleTabHints        @TD \<tabPlaneScaleTabHints resource\>
 *    @TABLE_END
 *    }
 * 
 * 
 * @DRAGGER_RESOURCES
 *    @TABLE_DRAGGER_RESOURCES
 *       @TR Resource:      @TD @B tabPlaneTranslator @b
 *       @TR Part:          @TD translator
 *       @TR Appearance:    @TD Outline of a Square. The region within it is pickable
 *       @TR Description:   @TD Begins translation within the plane
 * 
 *       @TR Resource:      @TD @B tabPlaneScaleTabMaterial @b
 *       @TR Part:          @TD scaleTabMaterial
 *       @TR Appearance:    @TD Green - half diffuse, half emissive.
 *       @TR Description:   @TD Used as material for scaling tabs.
 * 
 *       @TR Resource:      @TD @B tabPlaneScaleTabHints @b
 *       @TR Part:          @TD scaleTabHints
 *       @TR Appearance:    @TD shapeHints node:COUNTERCLOCKWISE/SOLID/CONVEX
 *       @TR Description:   @TD Property for the tab nodes.
 * 
 *    @TABLE_END
 * 
 * @CATALOG_PARTS
 *    All Parts
 *    @TABLE_CATALOG_PART
 *       @TR   callbackList         @TD   NodeKitListPart   @TD     --      @TD   yes     
 *       @TR   translator           @TD   Separator         @TD     --      @TD   yes     
 *       @TR   scaleTabMaterial     @TD   Material          @TD     --      @TD   yes     
 *       @TR   scaleTabHints        @TD   ShapeHints        @TD     --      @TD   yes     
 *       @TR   translatorDrawStyle  @TD   DrawStyle         @TD     --      @TD   no
 *       @TR   translatorMaterial   @TD   Material          @TD     --      @TD   no
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
 *    SoTrackballDragger,
 *    SoTransformBoxDragger,
 *    SoTransformerDragger,
 *    SoTranslate1Dragger,
 *    SoTranslate2Dragger
 * 
 * 
 */ 

class INVENTOR_API SoTabPlaneDragger : public SoDragger
{
  // Define typeId and name stuff
  SO_KIT_HEADER(SoTabPlaneDragger);

  SO_KIT_CATALOG_ENTRY_HEADER(planeSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(translator);
  SO_KIT_CATALOG_ENTRY_HEADER(scaleTabs);
  SO_KIT_CATALOG_ENTRY_HEADER(scaleTabMaterial);
  SO_KIT_CATALOG_ENTRY_HEADER(scaleTabHints);
  SO_KIT_CATALOG_ENTRY_HEADER(scaleTabMaterialBinding);
  SO_KIT_CATALOG_ENTRY_HEADER(scaleTabNormalBinding);
  SO_KIT_CATALOG_ENTRY_HEADER(scaleTabNormal);
  SO_KIT_CATALOG_ENTRY_HEADER(edgeScaleCoords);
  SO_KIT_CATALOG_ENTRY_HEADER(edgeScaleTab0);
  SO_KIT_CATALOG_ENTRY_HEADER(edgeScaleTab1);
  SO_KIT_CATALOG_ENTRY_HEADER(edgeScaleTab2);
  SO_KIT_CATALOG_ENTRY_HEADER(edgeScaleTab3);
  SO_KIT_CATALOG_ENTRY_HEADER(cornerScaleCoords);
  SO_KIT_CATALOG_ENTRY_HEADER(cornerScaleTab0);
  SO_KIT_CATALOG_ENTRY_HEADER(cornerScaleTab1);
  SO_KIT_CATALOG_ENTRY_HEADER(cornerScaleTab2);
  SO_KIT_CATALOG_ENTRY_HEADER(cornerScaleTab3);
  SO_KIT_CATALOG_ENTRY_HEADER(translatorMaterial);
  SO_KIT_CATALOG_ENTRY_HEADER(translatorDrawStyle);
  SO_KIT_CATALOG_ENTRY_HEADER(translatorCoordinates);

public:
  /**
  * Constructor.
  */
  SoTabPlaneDragger();

  /**
  * Position of the dragger.  Default is (0,0,0).
  */
  SoSFVec3f    translation;
 
  /**
  * Scale factor affecting the dragger.  Default is (1,1,1).
  * 
  */
  SoSFVec3f    scaleFactor;

  /**
  * If set to TRUE, handles will be resized automatically when the
  * view matrix (camera) changes.  Default is TRUE.
  * 
  * @FIELD_SINCE_OIV 7.0
  */
  SoSFBool resizeHandles;

  /**
  * If set to TRUE, scaling will always be uniform.  Default is FALSE.
  * 
  * @FIELD_SINCE_OIV 7.1
  */
  SoSFBool scaleUniform;

  /**
  * If set to TRUE, OpenGL two sided lighting will be enabled.  Default is FALSE.
  * 
  * @FIELD_SINCE_OIV 7.1
  */
  SoSFBool twoSidedLighting;

  /**
  * Specifies the line width for the outline box.  Default is 1.0
  * 
  * @FIELD_SINCE_OIV 7.1
  */
  SoSFFloat lineWidth;

  /**
   * Causes the scale tab sizes to be adjusted so that they remain a near constant
   * screen space size. This happens automatically upon dragger finish. Call this to
   * manually adjust the scale tab sizes at other times, for instance after the camera has
   * changed in a viewer finish \oivnetdoc delegate \else callback \endoivnetdoc.
   * Note that (since version 7.0) handles are automatically resized when the camera
   * changes, as long as the #resizeHandles field is set to TRUE.
   */
  void    adjustScaleTabSize();

  /** show or hide edges */
  void showEdgeScales( const SbBool show );

  /** show or hide corners */
  void showCornerScales( const SbBool show );

 SoINTERNAL public:
  /** register class in database */
  static void initClass();
  /** unregister class from database */
  static void exitClass();

  int getCurrentState();

protected:

  /** edges switch (controlled by showEdgeScales() methods) */
  SoSwitch* m_edgeSwitch;

  /** corner switch (controlled by showCornerScales() methods) */
  SoSwitch* m_cornerSwitch;

  //sensor to detect twoSidedLighting changes
  SoFieldSensor *lightingSensor;

  //sensor to detect twoSidedLighting changes
  SoFieldSensor *lineWidthSensor;

  static void lightingSensorCB( void *, SoSensor * );

  static void lineWidthSensorCB( void *, SoSensor * );

  static void startCB( void *, SoDragger *);
  static void motionCB( void *, SoDragger *);
  static void finishCB( void *, SoDragger *);
  static void metaKeyChangeCB( void *, SoDragger *);

  SbLineProjector     *lineProj;
  SbPlaneProjector    *planeProj;

  SoFieldSensor *translFieldSensor;
  SoFieldSensor *scaleFieldSensor;
  static void   fieldSensorCB( void *, SoSensor * );
  static void valueChangedCB( void *, SoDragger * );

  virtual void GLRender( SoGLRenderAction *action );
  virtual void rayPick(SoRayPickAction *action);

  void        dragStart();
  void        drag();
  void        dragFinish();

  void        translateStart();
  void        translateDrag();
    
  void        edgeScaleStart();
  void        edgeScaleDrag();
    
  void        cornerScaleStart();
  void        cornerScaleDrag();
    
  void        scaleUniformStart();
  void        scaleUniformDrag();

  SbVec3f           worldRestartPt;
  int               currentScalePatch;

  enum State {
    INACTIVE, TRANSLATING, EDGE_SCALING, CORNER_SCALING, UNIFORM_SCALING
  };
  SbBool              shftDown;

  State               currentState;
  State               restartState;
  int                 translateDir;

  SbVec3f             scaleCenter;

  SbBool              needScaleTabAdjustment;
  void                reallyAdjustScaleTabSize(SoAction *action);

  void getXYScreenLengths( SbVec2f &lengths, const SbMatrix &localToScreen, 
                           const SbVec2s &winSize);

  // detach/attach any sensors, callbacks, and/or field connections.
  // Called by:            start/end of SoBaseKit::readInstance
  // and on new copy by:   start/end of SoBaseKit::copy.
  // Classes that redefine must call setUpConnections(TRUE,TRUE) 
  // at end of constructor.
  // Returns the state of the node when this was called.
  virtual SbBool setUpConnections( SbBool onOff, SbBool doItAlways = FALSE );

  virtual void setDefaultOnNonWritingFields();

  virtual ~SoTabPlaneDragger();

 private:
  static const char geomBuffer[];
  static bool s_resizeOnInactiveOnly;

};    

#endif  /* _SO_TAB_PLANE_DRAGGER_ */

