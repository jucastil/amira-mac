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


#ifndef  _SO_DRAGPOINT_DRAGGER_
#define  _SO_DRAGPOINT_DRAGGER_

#include <Inventor/SbLinear.h>
#include <Inventor/SbBox.h>
#include <Inventor/draggers/SoDragger.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/sensors/SoSensor.h>


class SoFieldSensor;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoDragPointDragger
//
//  DragPoint dragger - allows user to move a single coordinate in
//  three dimensions.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Object you can translate in 3D by dragging with the mouse.
 * 
 * @ingroup draggers
 * 
 * @DESCRIPTION
 *   SoDragPointDragger is a compound dragger that translates in all three dimensions
 *   when dragged with the mouse.
 *   
 *   It is made up of six smaller draggers, which it displays two at a time. Each pair
 *   has one @B plane @b dragger and one @B line @b dragger. The line dragger is
 *   oriented perpendicular to the plane, so together the @B plane/line pair @b lets
 *   you move through all of 3-space.
 *   
 *   DragPoint has a total of three such pairs, oriented along the x, y, and z axes of
 *   its local space. You can cycle through the three pairs by hitting the \<Control\>
 *   key with the cursor over the dragger. (You need not press the mouse button.)
 *   An application can cycle through the pairs by calling the showNextDraggerSet
 *   method or display a specific pair by calling the showDraggerSet method.
 *   The dragger starts with the Y axis (y-line/xz-plane) pair displayed.
 *   
 *   The line draggers are SoTranslate1Draggers and the plane draggers are
 *   SoTranslate2Draggers. So you can use the \<Shift\> key to constrain the motion of
 *   a plane dragger along one of the two axes within the plane, as described in the
 *   SoTranslate2Draggers reference page.
 *   
 *   DragPoint adds extra feedback parts to provide a more intuitive idea of where you
 *   are placed in three-space. There are three @B feedback planes @b and three
 *   @B feedback axes @b; each corresponds to one of the plane or line draggers, but
 *   spans a much greater distance. When you drag along a line, that line's larger
 *   feedback axis is displayed, and remains anchored in space while the dragger
 *   slides along it. This helps establish the motion of the dragger relative to the
 *   rest of the scene. Similarly, when you drag within a plane, the larger (but
 *   transparent) feedback plane establishes a ground plane for you to move upon. The
 *   location of the dragger within the plane is pinpointed by two intersecting axes
 *   that always cross below the cursor and extend to the edges of the plane. When
 *   you move dragPoint to the edge of the feedback plane (or line), the feedback
 *   will jump to a new location in that direction, so that the dragger never leaves
 *   the feedback behind.
 *   
 *   The primary directions of motion are given by the local space of the dragger.
 *   Transforms earlier in the scene will affect the dragger, its children, and the
 *   orientation of its directions of motion.
 *   
 *   This node has a #translation field which always reflects its position in
 *   local space. Setting the field moves the dragger to that point. You can also
 *   connect fields of other nodes or engines from this one to make them follow the
 *   dragger's motion.
 *   
 *   Although the child draggers each have their own resources defining default part
 *   geometries, the dragPoint dragger overrides these with a new set of resources.
 *   It also defines resources for the feedback parts that it adds. These are
 *   detailed in the Dragger Resources section of the online reference page for this
 *   class. You can change the parts in any instance of this dragger using
 *   setPart().
 *   
 *   You can make your program use different default resources for the parts by
 *   copying the file @B $OIVHOME/data/draggerDefaults/dragPointDragger.iv @b into
 *   your own directory, editing the file, and then setting the environment variable
 *   @B SO_DRAGGER_DIR @b to be a path to that directory.
 * 
 * @FILE_FORMAT_DEFAULT
 *    DragPointDragger {
 *    @TABLE_FILE_FORMAT
 *       @TR renderCaching                   @TD AUTO
 *       @TR boundingBoxCaching              @TD AUTO
 *       @TR renderCulling                   @TD AUTO
 *       @TR pickCulling                     @TD AUTO
 *       @TR isActive                        @TD FALSE
 *       @TR translation                     @TD 0 0 0
 *       @TR callbackList                    @TD NULL
 *       @TR xTranslator                     @TD Translate1Dragger {
 *       @TR      }                          @TD 
 *       @TR xyTranslator                    @TD Translate2Dragger {
 *       @TR      }                          @TD 
 *       @TR xzTranslator                    @TD Translate2Dragger {
 *       @TR      }                          @TD 
 *       @TR zTranslator                     @TD Translate1Dragger {
 *       @TR      }                          @TD 
 *       @TR yzTranslator                    @TD Translate2Dragger {
 *       @TR      }                          @TD 
 *       @TR yTranslator                     @TD Translate1Dragger {
 *       @TR      }                          @TD 
 *       @TR xFeedback                       @TD \<dragPointXFeedback resource\>
 *       @TR yFeedback                       @TD \<dragPointYFeedback resource\>
 *       @TR zFeedback                       @TD \<dragPointZFeedback resource\>
 *       @TR yzFeedback                      @TD \<dragPointYZFeedback resource\>
 *       @TR xzFeedback                      @TD \<dragPointXZFeedback resource\>
 *       @TR xyFeedback                      @TD \<dragPointXYFeedback resource\>
 *       @TR xTranslator.translator          @TD \<dragPointXTranslatorTranslator resource\>
 *       @TR xTranslator.translatorActive    @TD \<dragPointXTranslatorTranslatorActive resource\>
 *       @TR yTranslator.translator          @TD \<dragPointYTranslatorTranslator resource\>
 *       @TR yTranslator.translatorActive    @TD \<dragPointYTranslatorTranslatorActive resource\>
 *       @TR zTranslator.translator          @TD \<dragPointZTranslatorTranslator resource\>
 *       @TR zTranslator.translatorActive    @TD \<dragPointZTranslatorTranslatorActive resource\>
 *       @TR yzTranslator.translator         @TD \<dragPointYZTranslatorTranslator resource\>
 *       @TR yzTranslator.translatorActive   @TD \<dragPointYZTranslatorTranslatorActive resource\>
 *       @TR xzTranslator.translator         @TD \<dragPointXZTranslatorTranslator resource\>
 *       @TR xzTranslator.translatorActive   @TD \<dragPointXZTranslatorTranslatorActive resource\>
 *       @TR xyTranslator.translator         @TD \<dragPointXYTranslatorTranslator resource\>
 *       @TR xyTranslator.translatorActive   @TD \<dragPointXYTranslatorTranslatorActive resource\>
 *    @TABLE_END
 *    }
 * 
 * 
 * @DRAGGER_RESOURCES
 *    @TABLE_DRAGGER_RESOURCES
 *       @TR Resource:      @TD @B dragPointXTranslatorTranslator @b
 *       @TR Part:          @TD xTranslator.translator
 *       @TR Appearance:    @TD white cylinder with axis aligned in X direction
 *       @TR Description:   @TD picking this initiates linear motion in X direction
 * 
 *       @TR Resource:      @TD @B dragPointXTranslatorTranslatorActive @b
 *       @TR Part:          @TD xTranslator.translatorActive
 *       @TR Appearance:    @TD yellow cylinder with axis aligned in X direction
 *       @TR Description:   @TD shown when moving in X direction
 * 
 *       @TR Resource:      @TD @B dragPointYTranslatorTranslator @b
 *       @TR Part:          @TD yTranslator.translator
 *       @TR Appearance:    @TD white cylinder with axis aligned in Y direction
 *       @TR Description:   @TD picking this initiates linear motion in Y direction
 * 
 *       @TR Resource:      @TD @B dragPointYTranslatorTranslatorActive @b
 *       @TR Part:          @TD yTranslator.translatorActive
 *       @TR Appearance:    @TD yellow cylinder with axis aligned in Y direction
 *       @TR Description:   @TD shown when moving in Y direction
 * 
 *       @TR Resource:      @TD @B dragPointZTranslatorTranslator @b
 *       @TR Part:          @TD zTranslator.translator
 *       @TR Appearance:    @TD white cylinder with axis aligned in Z direction
 *       @TR Description:   @TD picking this initiates linear motion in Z direction
 * 
 *       @TR Resource:      @TD @B dragPointZTranslatorTranslatorActive @b
 *       @TR Part:          @TD zTranslator.translatorActive
 *       @TR Appearance:    @TD yellow cylinder with axis aligned in Z direction
 *       @TR Description:   @TD shown when moving in Z direction
 * 
 *       @TR Resource:      @TD @B dragPointYZTranslatorTranslator @b
 *       @TR Part:          @TD yzTranslator.translator
 *       @TR Appearance:    @TD white flattened cube within the yz plane of motion
 *       @TR Description:   @TD picking this initiates planar motion in yz plane
 * 
 *       @TR Resource:      @TD @B dragPointYZTranslatorTranslatorActive @b
 *       @TR Part:          @TD yzTranslator.translatorActive
 *       @TR Appearance:    @TD yellow flattened cube within the yz plane of motion
 *       @TR Description:   @TD shown when moving in yz plane
 * 
 *       @TR Resource:      @TD @B dragPointXZTranslatorTranslator @b
 *       @TR Part:          @TD xzTranslator.translator
 *       @TR Appearance:    @TD white flattened cube within the xz plane of motion
 *       @TR Description:   @TD picking this initiates planar motion in xz plane
 * 
 *       @TR Resource:      @TD @B dragPointXZTranslatorTranslatorActive @b
 *       @TR Part:          @TD xzTranslator.translatorActive
 *       @TR Appearance:    @TD yellow flattened cube within the xz plane of motion
 *       @TR Description:   @TD shown when moving in xz plane
 * 
 *       @TR Resource:      @TD @B dragPointXYTranslatorTranslator @b
 *       @TR Part:          @TD xyTranslator.translator
 *       @TR Appearance:    @TD white flattened cube within the xy plane of motion
 *       @TR Description:   @TD picking this initiates planar motion in xy plane
 * 
 *       @TR Resource:      @TD @B dragPointXYTranslatorTranslatorActive @b
 *       @TR Part:          @TD xyTranslator.translatorActive
 *       @TR Appearance:    @TD yellow flattened cube within the xy plane of motion
 *       @TR Description:   @TD shown when moving in xy plane
 * 
 *       @TR Resource:      @TD @B dragPointXFeedback @b
 *       @TR Part:          @TD xFeedback
 *       @TR Appearance:    @TD douple-headed purple arrow
 *       @TR Description:   @TD feedback for motion in x direction
 * 
 *       @TR Resource:      @TD @B dragPointYFeedback @b
 *       @TR Part:          @TD yFeedback
 *       @TR Appearance:    @TD douple-headed purple arrow
 *       @TR Description:   @TD feedback for motion in y direction
 * 
 *       @TR Resource:      @TD @B dragPointZFeedback @b
 *       @TR Part:          @TD zFeedback
 *       @TR Appearance:    @TD douple-headed purple arrow
 *       @TR Description:   @TD feedback for motion in z direction
 * 
 *       @TR Resource:      @TD @B dragPointYZFeedback @b
 *       @TR Part:          @TD yzFeedback
 *       @TR Appearance:    @TD semi-transparent green square in yz plane
 *       @TR Description:   @TD feedback for motion in yz plane
 * 
 *       @TR Resource:      @TD @B dragPointXZFeedback @b
 *       @TR Part:          @TD xzFeedback
 *       @TR Appearance:    @TD semi-transparent green square in yz plane
 *       @TR Description:   @TD feedback for motion in xz plane
 * 
 *       @TR Resource:      @TD @B dragPointXYFeedback @b
 *       @TR Part:          @TD xyFeedback
 *       @TR Appearance:    @TD semi-transparent green square in yz plane
 *       @TR Description:   @TD feedback for motion in xy plane
 * 
 *    @TABLE_END
 * 
 * @CATALOG_PARTS
 *    All Parts
 *    @TABLE_CATALOG_PART
 *       @TR   callbackList  @TD   NodeKitListPart    @TD    --      @TD   yes     
 *       @TR   xTranslator   @TD   Translate1Dragger  @TD    --      @TD   yes     
 *       @TR   xyTranslator  @TD   Translate2Dragger  @TD    --      @TD   yes     
 *       @TR   xzTranslator  @TD   Translate2Dragger  @TD    --      @TD   yes     
 *       @TR   zTranslator   @TD   Translate1Dragger  @TD    --      @TD   yes     
 *       @TR   yzTranslator  @TD   Translate2Dragger  @TD    --      @TD   yes     
 *       @TR   yTranslator   @TD   Translate1Dragger  @TD    --      @TD   yes     
 *       @TR   xFeedback     @TD   Separator          @TD    --      @TD   yes     
 *       @TR   yFeedback     @TD   Separator          @TD    --      @TD   yes     
 *       @TR   zFeedback     @TD   Separator          @TD    --      @TD   yes     
 *       @TR   yzFeedback    @TD   Separator          @TD    --      @TD   yes     
 *       @TR   xzFeedback    @TD   Separator          @TD    --      @TD   yes     
 *       @TR   xyFeedback    @TD   Separator          @TD    --      @TD   yes     
 *    @TABLE_END
 * 
 *    Extra Information for List Parts from Above Table
 *    @TABLE_LIST_PART
 *       @TR   callbackList  @TD   Separator          @TD   Callback, EventCallback
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

class INVENTOR_API SoDragPointDragger : public SoDragger
{
  SO_KIT_HEADER(SoDragPointDragger);

  SO_KIT_CATALOG_ENTRY_HEADER(noRotSep);
  SO_KIT_CATALOG_ENTRY_HEADER(xTranslatorSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(xTranslator);
  SO_KIT_CATALOG_ENTRY_HEADER(xyTranslatorSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(xyTranslator);

  SO_KIT_CATALOG_ENTRY_HEADER(rotXSep);
  SO_KIT_CATALOG_ENTRY_HEADER(rotX);
  SO_KIT_CATALOG_ENTRY_HEADER(xzTranslatorSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(xzTranslator);

  SO_KIT_CATALOG_ENTRY_HEADER(rotYSep);
  SO_KIT_CATALOG_ENTRY_HEADER(rotY);
  SO_KIT_CATALOG_ENTRY_HEADER(zTranslatorSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(zTranslator);
  SO_KIT_CATALOG_ENTRY_HEADER(yzTranslatorSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(yzTranslator);

  SO_KIT_CATALOG_ENTRY_HEADER(rotZSep);
  SO_KIT_CATALOG_ENTRY_HEADER(rotZ);
  SO_KIT_CATALOG_ENTRY_HEADER(yTranslatorSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(yTranslator);

  SO_KIT_CATALOG_ENTRY_HEADER(xFeedbackSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(xFeedbackSep);
  SO_KIT_CATALOG_ENTRY_HEADER(xFeedbackTranslation);
  SO_KIT_CATALOG_ENTRY_HEADER(xFeedback);

  SO_KIT_CATALOG_ENTRY_HEADER(yFeedbackSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(yFeedbackSep);
  SO_KIT_CATALOG_ENTRY_HEADER(yFeedbackTranslation);
  SO_KIT_CATALOG_ENTRY_HEADER(yFeedback);

  SO_KIT_CATALOG_ENTRY_HEADER(zFeedbackSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(zFeedbackSep);
  SO_KIT_CATALOG_ENTRY_HEADER(zFeedbackTranslation);
  SO_KIT_CATALOG_ENTRY_HEADER(zFeedback);

  SO_KIT_CATALOG_ENTRY_HEADER(planeFeedbackSep);
  SO_KIT_CATALOG_ENTRY_HEADER(planeFeedbackTranslation);
  SO_KIT_CATALOG_ENTRY_HEADER(planeFeedbackSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(yzFeedback);
  SO_KIT_CATALOG_ENTRY_HEADER(xzFeedback);
  SO_KIT_CATALOG_ENTRY_HEADER(xyFeedback);

 public:
  /**
   * Constructor.
   */
  SoDragPointDragger();

  /**
   * Position of the dragger.
   * 
   */
  SoSFVec3f translation;

 public:
  /**
   * Sets the point at which the feedback axes will jump to a new position.
   * For example, if set to .1 (the default), the feedback axes will jump when the
   * dragger gets within 10\% of the end of the axis.
   */
  void    setJumpLimit(float limit)   { jumpLimit = limit; }
  /**
   * Gets the point at which the feedback axes will jump to a new position.
   */
  float   getJumpLimit() const        { return jumpLimit; }

  /**
   * The dragPoint dragger contains three pairs of draggers, each containing a plane
   * dragger and a line dragger (see the Description above). The dragger starts with
   * the (y-line/xz-plane) pair displayed. Calling this method will cycle next
   * through the (z-line/xy-plane), then the (x-line/yz-plane).
   */
  void showNextDraggerSet();

  /** Dragger set */
  enum DraggerSet {
    /*
     * X axis dragger set (x-line/yz-plane)
     */
    X_AXIS,
    /*
     * Y axis dragger set (y-line/xz-plane)
     */
    Y_AXIS,
    /*
     * Z axis dragger set (z-line/xy-plane)
     */
    Z_AXIS
  };

  /**
   * The dragPoint dragger contains three pairs of draggers, each containing a plane
   * dragger and a line dragger (see the Description above). By default the Y axis
   * (y-line/xz-plane) pair is displayed. Calling this method selects a specific pair.
   */
  void showDraggerSet( DraggerSet set );

 SoINTERNAL public:
  static void         initClass();    // initialize the class
  static void         exitClass();

 protected:

  static void startCB( void *, SoDragger * );
  static void motionCB( void *, SoDragger * );
  static void finishCB( void *, SoDragger * );

  SoFieldSensor *fieldSensor;
  static void fieldSensorCB( void *, SoSensor * );
  static void valueChangedCB( void *, SoDragger * );

  static void metaKeyChangeCB( void *, SoDragger *);

  void        dragStart();
  void        drag();
  void        dragFinish();
    
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

  virtual ~SoDragPointDragger();

 private:
    
  SoDragger *currentDragger;
  SbVec3f    startLocalHitPt;

  SbBool          shftDown;  // used to keep track of if meta key is down.

  // The box defining the area where the feedback appears.
  // This box stays still in world space whil the dragger is moved.
  // But when the dragger gets too close to the edge, it jumps over
  // to define a new box.
  // Limit box in local space preserves size of box even when world
  // space coordinates are very large (small box dimensions could be
  // lost because of limited floating point precision).
  SbBox3f     limitBox;
  SbBox3f     localLimitBox;
    
  // when to jump
  float       jumpLimit;

  // sets the feedback geometry based on the level of
  // constraints
  void        setFeedbackGeometry();

  // checks the limit box and extends it if necessary
  void        checkBoxLimits();

  // Sets the offsetWorkLimit box and updates the feedback geometry 
  void  updateLimitBoxAndFeedback();

  static const char geomBuffer[];

  SoGetBoundingBoxAction* bba;

  //  Cached values to make updating feedback more efficient
  SoNode *oldXAxisNode;
  SoNode *oldYAxisNode;
  SoNode *oldZAxisNode;

};

#endif  /* _SO_DRAGPOINT_DRAGGER_ */

