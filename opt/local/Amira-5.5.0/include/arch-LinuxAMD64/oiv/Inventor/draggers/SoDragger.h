/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul Isaacs (MMM yyyy)
** Modified by : David Mott (MMM yyyy)
** Modified by : Howard Look (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_DRAGGER_
#define  _SO_DRAGGER_

#include <Inventor/SbBox.h>
#include <Inventor/SbViewportRegion.h>
#include <Inventor/SbLinear.h>
#include <Inventor/nodekits/SoInteractionKit.h>
#include <Inventor/misc/SoCallbackList.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/nodes/SoMatrixTransform.h>
#include <Inventor/nodes/SoScale.h>


class SoPickedPoint;
class SoAction;
class SoHandleEventAction;
class SoGetBoundingBoxAction;
class SoGetMatrixAction;
class SoSearchAction;
class SoEvent;
class SoPath;
class SoTempPath;
class SbPList;

class SoDragger;  // forward reference

// The following typedef is used in defining the callback function lists.
/**
 * [OIV-WRAPPER NAME{DraggerCallback}]
 */
typedef void SoDraggerCB(void *userData, SoDragger *dragger );

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoDragger
//
//  Base class for draggers which are operated by a start (mouse down)
//  followed by dragging, followed by end (mouse up).
//
//////////////////////////////////////////////////////////////////////////////

#ifdef OIV_NET_DOC
/**
* Base class for nodekits that move in response to click-drag-release mouse
* events.
*
* @ingroup draggers
*
* @DESCRIPTION
*   SoDragger is the base class for all nodekits you move by using the mouse to
*   click-drag-and-release. More specifically, they are operated by a start (mouse
*   button 1 pressed over dragger to pick it), followed by dragging (mouse motion
*   events are interpreted by the dragger and result in some form of motion and/or
*   change to a field), followed by finish (mouse up).
*
*   Each dragger has a different paradigm for interpreting mouse motion and changing
*   its fields as a result. Draggers map 2D mouse motion into motion of a point on
*   3D lines, planes, spheres, or cylinders. (See the SbProjector reference pages.)
*   Then they react to this motion of a point through 3-space by scaling,
*   translating, or rotating. For example, SoTranslate2Dragger maps mouse motion
*   onto a 3D plane, then translates to follow the cursor as it moves within that
*   plane.
*
*   Beginning with version 3.0, draggers also respond to tracked input device
*   events (see SoControllerButtonEvent and SoTrackerEvent) in order to support
*   immersive VR devices like a wand. Interaction is started by pressing wand
*   button 1 when the tracker "ray" intersects the dragger's geometry.
*   Analogous to 2D, in which the interaction is driven by tracking the ray
*   from the 2D mouse cursor, in 3D the interaction is driven by tracking the
*   ray emanating from the tracking device.
*
*   Beginning with version 5.0,
*   draggers can also take position and orientation changes directly from the
*   tracker's position and orientation. Specifically the difference between the
*   tracker's current values and the values at the start of the interaction is
*   applied as an incremental change to the dragger. In general this is a more
*   natural way to manipulate objects in an immersive environment. You can use
*   the #setTrackerDirectMode method to enable this behavior.
*   - If mode is NONE,
*   the dragger will not use tracker values directly (but it will still respond
*   to tracker events in the version 3.0 way).
*   - If mode is DEFAULT, the dragger's natural default direct behavior will
*   be used (either NONE, MOVE, ROTATE, or FREE depending on the dragger class).
*   - If mode is
*   MOVE or ROTATE, the dragger will use the tracker's position or orientation
*   directly.
*   - If mode is FREE, the dragger will use the tracker's position and
*   orientation directly.
*
*   Every dragger has @B fields @b that describe its current state. Scaling draggers
*   have a @B scaleFactor @b field, rotational draggers have a @B rotation @b
*   field, etc. All draggers have the #isActive field, defined in this class.
*   It is true while the dragger is being dragged, false otherwise.
*
*   Draggers that have only one part to pick and one motion field are called
*   @B simple draggers@b. Examples are the SoRotateDiscDragger, SoScale1Dragger,
*   and SoTranslate2Dragger.
*
*   Draggers that create assemblies out of other draggers and then orchestrate the
*   motion of the whole assembly are call @B composite draggers@b.
*   SoTransformBoxDragger is a composite dragger made entirely of simple draggers.
*   SoDirectionalLightDragger contains both a simple dragger
*   (SoRotateSphericalDragger) and a composite dragger (SoDragPointDragger) When
*   using a composite dragger, the fields of the composite dragger are the ones you
*   should work with. Draggers lower down in the assemblage usually have zeroed out
*   values. For example, when you drag the face of a transformBox, an
*   SoTranslate2Dragger, the transformBox "steals" the translation from the child
*   dragger and transfers it up to the top of the composite dragger, where it
*   effects all pieces of the assemblage.
*
*   Draggers always keep their fields up to date, including while they are being
*   dragged. So you can use field-to-field connections and engines to connect
*   dragger values to other parts of your scene graph. Hence draggers can be easily
*   utilized as input devices for mouse-driven 3D interface elements. You can also
*   register value-changed callbacks, which are called whenever any of the fields is
*   changed.
*
*   Also, if you set the field of a dragger through some method other than dragging,
*   (by calling setValue(), for example), the dragger's internal
*   SoFieldSensor will sense this and the dragger will move to satisfy that new
*   value.
*
*   This makes it easy to constrain draggers to keep their fields within certain
*   limits: if the limit is exceeded, just set it back to the exceeded maximum or
*   minimum. You can do this even as the dragger is in use, by constraining the
*   field value within a value-changed delegate that you add with
*   addValueChangedCallback(). In this case, be sure to temporarily disable
*   the other value-changed callbacks using enableValueChangedCallbacks().
*   Doing this will prevent infinite-looping; changing the value followed by calling
*   the callbacks which change the value ad infinitum.
*
*   When you drag a dragger, the dragger only moves itself. Draggers do not change
*   the state or affect objects that follow in the scene graph. For example a
*   dragger does not ever behave like an SoTransform and change the current
*   transformation matrix. Draggers are not transforms, even if they have field
*   names like translation, rotation, scaleFactor. Many draggers, such as
*   SoTrackballDragger, have a corresponding SoTransformManip, in this case
*   SoTrackballManip. The manipulator is a subclass of SoTransform, and affects
*   other objects in the scene; it uses a trackball @B dragger @b to provide its
*   user interface. In this way, draggers are employed extensively by manipulators.
*   Dragger's delegates allow its employer to be notified of start,
*   motion, finish, and value changes. In all cases, a reference to the dragger which
*	invokes	the delegate is passed as argument. (See the various reference pages for
*	more details on specific draggers and manipulators).
*   All draggers are nodekits. However, draggers do not list their parts in the Parts
*   section of the reference page. Instead, there is a section called Dragger
*   Resources, more suited to describe the parts made available to the programmer.
*   Because of space limitations, the Dragger Resources section only appears in the
*   online versions of the reference pages. Each dragger has some parts you can pick
*   on, and other parts that replace them when they are @B active @b or moving.
*   These active parts are often just the same geometry in another color. Draggers
*   also have pieces for displaying feedback. Each of these pieces has a default
*   scene graph, as well as a special function within the dragger. Each part also
*   has a resource name. All this information is contained in the DRAGGER RESOURCES
*   section.
*
*   Since draggers are nodekits, you can set the parts in any instance of a dragger
*   using setPart().
*
*   But draggers also give each part a @B resource name@b. When a dragger builds a
*   part, it looks in the global dictionary for the node with that
*   @B resourceName@b. By putting a new entry in the dictionary, you can override
*   that default. The default part geometries are defined as resources for each
*   class, and each class has a file you can change to alter the defaults. The files
*   are listed in each dragger's reference page. You can make your program use
*   different default resources for the parts by copying the listed file from the
*   directory @B $OIVHOME/data/draggerDefaults @b into your own directory, editing
*   the file, and then setting the environment variable @B SO_DRAGGER_DIR @b to be
*   a path to that directory.
*   
*   The SoInteractionKit method SetPartAsPath() provides support for creating "stand-in"
*   objects for parts in the interaction kit. The "stand-in", or "surrogate" part,
*   is a path to an object that lies somewhere else in the scene graph.
*   This could be used, for example, with an SoTranslate1Dragger to allow the
*   user to click on some geometry and directly drag it (without displaying any
*   separate dragger geometry).  This technique is used, for example, in SoOrthoSliceDragger.
*
* @FILE_FORMAT_DEFAULT
*    Dragger {
*    @TABLE_FILE_FORMAT
*       @TR renderCaching        @TD AUTO
*       @TR boundingBoxCaching   @TD AUTO
*       @TR renderCulling        @TD AUTO
*       @TR pickCulling          @TD AUTO
*       @TR isActive             @TD false
*       @TR callbackList         @TD NULL
*    @TABLE_END
*    }
*
* @CATALOG_PARTS
*    All Parts
*    @TABLE_CATALOG_PART
*       @TR   callbackList  @TD   NodeKitListPart  @TD    --      @TD   yes
*    @TABLE_END
*
*    Extra Information for List Parts from Above Table
*    @TABLE_LIST_PART
*       @TR   callbackList  @TD   Separator        @TD   Callback, EventCallback
*    @TABLE_END
*
* @SEE_ALSO
*    SoInteractionKit,
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
*    SoTranslate1Dragger,
*    SoTranslate2Dragger
*
*
*/
#else
/**
* Base class for nodekits that move in response to click-drag-release mouse
* events.
*
* @ingroup draggers
*
* @DESCRIPTION
*   SoDragger is the base class for all nodekits you move by using the mouse to
*   click-drag-and-release. More specifically, they are operated by a start (mouse
*   button 1 pressed over dragger to pick it), followed by dragging (mouse motion
*   events are interpreted by the dragger and result in some form of motion and/or
*   change to a field), followed by finish (mouse up).
*
*   Each dragger has a different paradigm for interpreting mouse motion and changing
*   its fields as a result. Draggers map 2D mouse motion into motion of a point on
*   3D lines, planes, spheres, or cylinders. (See the SbProjector reference pages.)
*   Then they react to this motion of a point through 3-space by scaling,
*   translating, or rotating. For example, SoTranslate2Dragger maps mouse motion
*   onto a 3D plane, then translates to follow the cursor as it moves within that
*   plane.
*
*   Beginning with version 3.0, draggers also respond to tracked input device
*   events (see SoControllerButtonEvent and SoTrackerEvent) in order to support
*   immersive VR devices like a wand. Interaction is started by pressing wand
*   button 1 when the tracker "ray" intersects the dragger's geometry.
*   Analogous to 2D, in which the interaction is driven by tracking the ray
*   from the 2D mouse cursor, in 3D the interaction is driven by tracking the
*   ray emanating from the tracking device.
*
*   Beginning with version 5.0,
*   draggers can also take position and orientation changes directly from the
*   tracker's position and orientation. Specifically the difference between the
*   tracker's current values and the values at the start of the interaction is
*   applied as an incremental change to the dragger. In general this is a more
*   natural way to manipulate objects in an immersive environment. You can use
*   the #setTrackerDirectMode method to enable this behavior.
*   - If mode is NONE,
*   the dragger will not use tracker values directly (but it will still respond
*   to tracker events in the version 3.0 way).
*   - If mode is DEFAULT, the dragger's natural default direct behavior will
*   be used (either NONE, MOVE, ROTATE, or FREE depending on the dragger class).
*   - If mode is
*   MOVE or ROTATE, the dragger will use the tracker's position or orientation
*   directly.
*   - If mode is FREE, the dragger will use the tracker's position and
*   orientation directly.
*
*   Every dragger has @B fields @b that describe its current state. Scaling draggers
*   have a @B scaleFactor @b field, rotational draggers have a @B rotation @b
*   field, etc. All draggers have the #isActive field, defined in this class.
*   It is TRUE while the dragger is being dragged, FALSE otherwise.
*
*   Draggers that have only one part to pick and one motion field are called
*   @B simple draggers@b. Examples are the SoRotateDiscDragger, SoScale1Dragger,
*   and SoTranslate2Dragger.
*
*   Draggers that create assemblies out of other draggers and then orchestrate the
*   motion of the whole assembly are call @B composite draggers@b.
*   SoTransformBoxDragger is a composite dragger made entirely of simple draggers.
*   SoDirectionalLightDragger contains both a simple dragger
*   (SoRotateSphericalDragger) and a composite dragger (SoDragPointDragger) When
*   using a composite dragger, the fields of the composite dragger are the ones you
*   should work with. Draggers lower down in the assemblage usually have zeroed out
*   values. For example, when you drag the face of a transformBox, an
*   SoTranslate2Dragger, the transformBox "steals" the translation from the child
*   dragger and transfers it up to the top of the composite dragger, where it
*   effects all pieces of the assemblage.
*
*   Draggers always keep their fields up to date, including while they are being
*   dragged. So you can use field-to-field connections and engines to connect
*   dragger values to other parts of your scene graph. Hence draggers can be easily
*   utilized as input devices for mouse-driven 3D interface elements. You can also
*   register value-changed callbacks, which are called whenever any of the fields is
*   changed.
*
*   Also, if you set the field of a dragger through some method other than dragging,
*   (by calling setValue(), for example), the dragger's internal
*   SoFieldSensor will sense this and the dragger will move to satisfy that new
*   value.
*
*   This makes it easy to constrain draggers to keep their fields within certain
*   limits: if the limit is exceeded, just set it back to the exceeded maximum or
*   minimum. You can do this even as the dragger is in use, by constraining the
*   field value within a value-changed callback that you add with
*   addValueChangedCallback(). In this case, be sure to temporarily disable
*   the other value-changed callbacks using enableValueChangedCallbacks().
*   Doing this will prevent infinite-looping; changing the value followed by calling
*   the callbacks which change the value ad infinitum.
*
*   When you drag a dragger, the dragger only moves itself. Draggers do not change
*   the state or affect objects that follow in the scene graph. For example a
*   dragger does not ever behave like an SoTransform and change the current
*   transformation matrix. Draggers are not transforms, even if they have field
*   names like translation, rotation, scaleFactor. Many draggers, such as
*   SoTrackballDragger, have a corresponding SoTransformManip, in this case
*   SoTrackballManip. The manipulator is a subclass of SoTransform, and affects
*   other objects in the scene; it uses a trackball @B dragger @b to provide its
*   user interface. In this way, draggers are employed extensively by manipulators.
*   Callback functions on the dragger allow its employer to be notified of start,
*   motion, finish, and value changes. In all cases, the callback function is passed
*   a pointer to the dragger which initiated the callback. (See the various
*   reference pages for more details on specific draggers and manipulators).
*
*   All draggers are nodekits. However, draggers do not list their parts in the Parts
*   section of the reference page. Instead, there is a section called Dragger
*   Resources, more suited to describe the parts made available to the programmer.
*   Because of space limitations, the Dragger Resources section only appears in the
*   online versions of the reference pages. Each dragger has some parts you can pick
*   on, and other parts that replace them when they are @B active @b or moving.
*   These active parts are often just the same geometry in another color. Draggers
*   also have pieces for displaying feedback. Each of these pieces has a default
*   scene graph, as well as a special function within the dragger. Each part also
*   has a resource name. All this information is contained in the DRAGGER RESOURCES
*   section.
*
*   Since draggers are nodekits, you can set the parts in any instance of a dragger
*   using setPart().
*
*   But draggers also give each part a @B resource name@b. When a dragger builds a
*   part, it looks in the global dictionary for the node with that
*   @B resourceName@b. By putting a new entry in the dictionary, you can override
*   that default. The default part geometries are defined as resources for each
*   class, and each class has a file you can change to alter the defaults. The files
*   are listed in each dragger's reference page. You can make your program use
*   different default resources for the parts by copying the listed file from the
*   directory @B $OIVHOME/data/draggerDefaults @b into your own directory, editing
*   the file, and then setting the environment variable @B SO_DRAGGER_DIR @b to be
*   a path to that directory.
*   
*   The SoInteractionKit method setPartAsPath() provides support for creating "stand-in"
*   objects for parts in the interaction kit. The "stand-in", or "surrogate" part,
*   is a path to an object that lies somewhere else in the scene graph.
*   This could be used, for example, with an SoTranslate1Dragger to allow the
*   user to click on some geometry and directly drag it (without displaying any
*   separate dragger geometry).  This technique is used, for example, in SoOrthoSliceDragger.
*
* @FILE_FORMAT_DEFAULT
*    Dragger {
*    @TABLE_FILE_FORMAT
*       @TR renderCaching        @TD AUTO
*       @TR boundingBoxCaching   @TD AUTO
*       @TR renderCulling        @TD AUTO
*       @TR pickCulling          @TD AUTO
*       @TR isActive             @TD FALSE
*       @TR callbackList         @TD NULL
*    @TABLE_END
*    }
*
* @CATALOG_PARTS
*    All Parts
*    @TABLE_CATALOG_PART
*       @TR   callbackList  @TD   NodeKitListPart  @TD    --      @TD   yes
*    @TABLE_END
*
*    Extra Information for List Parts from Above Table
*    @TABLE_LIST_PART
*       @TR   callbackList  @TD   Separator        @TD   Callback, EventCallback
*    @TABLE_END
*
* @SEE_ALSO
*    SoInteractionKit,
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
*    SoEllipsoidDragger,
*    SoTrackballDragger,
*    SoTransformBoxDragger,
*    SoTransformerDragger,
*    SoTranslate1Dragger,
*    SoTranslate2Dragger
*
*
*/
#endif //OIV_NET_DOC


class INVENTOR_API SoDragger : public SoInteractionKit {

  SO_KIT_HEADER(SoDragger);

  SO_KIT_CATALOG_ENTRY_HEADER(motionMatrix);

 public:

  /**
   * TRUE when mouse is down and dragging, else FALSE.
   */
  SoSFBool  isActive;

  /**
  * If set to FALSE, motion, start and finish callbacks are disabled.
  * Default is TRUE.
  * Note that valueChanged callbacks are enabled and disabled using
  * the #enableValueChangedCallbacks method.
  *
  * @FIELD_SINCE_OIV 7.1
  */
  SoSFBool  enableCallbacks;

  // Dragger Callbacks
  // In all cases, the callback data will be a pointer to the dragger
  // that caused the callback. Each type of callback maintains a list of
  // callbacks, so many callback functions may be registered, if desired.

  /**
   * Adds start callback.
   * Start callbacks are made after the mouse button 1 goes down and the dragger
   * determines that it has been picked. If it is going to begin dragging, it grabs
   * events and invokes the startCallbacks (if they are enabled - see the
   * #enableCallbacks field).
   * [OIV-WRAPPER EVENT_NAME{StartDragging}]
   */
  void    addStartCallback(SoDraggerCB *f, void *userData = NULL);

  /**
   * Removes start callback.
   * [OIV-WRAPPER EVENT_NAME{StartDragging}]
   */
  void removeStartCallback(SoDraggerCB *f, void *userData = NULL);

  /**
   * Adds motion callback.
   * Motion callbacks are called after each movement of the mouse during dragging
   * (if they are enabled - see the #enableCallbacks field).
   * [OIV-WRAPPER EVENT_NAME{MouseMove}]
   */
  void    addMotionCallback(SoDraggerCB *f, void *userData = NULL);

  /**
   * Removes motion callback.
   * [OIV-WRAPPER EVENT_NAME{MouseMove}]
   */
  void removeMotionCallback(SoDraggerCB *f, void *userData = NULL);

  /**
   * Adds finish callback.
   * Finish callbacks are made after dragging ends and the dragger has stopped
   * grabbing events (if they are enabled - see the #enableCallbacks field).
   * [OIV-WRAPPER EVENT_NAME{FinishDragging}]
   */
  void    addFinishCallback(SoDraggerCB *f, void *userData = NULL);

  /**
   * Removes finish callback.
   * [OIV-WRAPPER EVENT_NAME{FinishDragging}]
   */
  void removeFinishCallback(SoDraggerCB *f, void *userData = NULL);

  /**
   * Adds value-changed callback.
   * Value-changed callbacks are made after a dragger changes any of its fields. This
   * does not include changes to the #isActive field. See also
   * enableValueChangedCallbacks().
   * [OIV-WRAPPER EVENT_NAME{ValueChanged}]
   */
  void    addValueChangedCallback(SoDraggerCB *f, void *userData = NULL);

  /**
   * Removes value-changed callback.
   * [OIV-WRAPPER EVENT_NAME{ValueChanged}]
   */
  void removeValueChangedCallback(SoDraggerCB *f, void *userData = NULL);

  /**
   * Sets the number of pixels of movement required to initiate a constraint
   * gesture. Default is 8.
   */
  void    setMinGesture(int pixels)       { minGesture = (float)pixels; }

  /**
   *  Float version of #setMinGesture. It can be used when a desktop is magnified
   *  on a wall of screens using ScaleViz with a tracker
   *  device calibrated for this wall.
   */
  void    setMinGesture(float pixels)       { minGesture = pixels; }

  /**
   * Gets the number of pixels of movement required to initiate a constraint
   * gesture.
   */
  int     getMinGesture() const           { return (int)minGesture; }

  /**
   *  Float version of #getMinGesture. It can be used when a desktop is magnified
   *  on a wall of screens using ScaleViz with a tracker
   *  device calibrated for this wall.
   */
  float   getMinGestureFloat() const           { return minGesture; }

  /**
   * Sets the smallest scale that any dragger will write. If the user attempts to go below
   * this amount, the dragger will set it to this minimum. Default is .001.
   */
  static void  setMinScale(float newMinScale);

  /**
   * Gets the smallest scale that any dragger will write.
   */
  static float getMinScale();

  /**
   * You can temporarily disable a dragger's valueChangedCallbacks. The method
   * returns a value that tells you if callbacks were already enabled. Use this
   * method if you write a valueChanged \oivnetdoc delegate \else callback \endoivnetdoc of your own and you change one of
   * the dragger's fields within the \oivnetdoc delegate \else callback \endoivnetdoc. (For example, when writing a \oivnetdoc delegate \else callback \endoivnetdoc
   * to constrain your dragger). Disable first, then change the field, then re-enable
   * the callbacks (if they were enabled to start with). All this prevents you from
   * entering an infinite loop of changing values, calling callbacks which change
   * values, etc.
   * [OIVNET-WRAPPER NAME{EnableValueChangedEvent}]
   */
  SbBool enableValueChangedCallbacks( SbBool newVal );

  /** Tracker direct mode */
  enum TrackerDirectMode {
    /**
     * Dragger will not use tracker values directly (default).
     */
    NONE,
    /**
     * Dragger will use tracker position values directly.
     */
    MOVE,
    /**
     * Dragger will use tracker orientation values directly.
     */
    ROTATE,
    /**
     * Dragger will use tracker position and orientation directly.
     */
    FREE,
    /**
     * Dragger will use its natural default direct behavior
     * (which will be NONE, MOVE, ROTATE, or FREE depending on the dragger class).
     */
    DEFAULT
  };

  /**
   * Sets the tracker direct mode for this dragger (see description above).
   * Mode can also be set by preference keyword OIV_TRACKER_DIRECT_MODE.
   * The default is NONE.
   */
  void setTrackerDirectMode( TrackerDirectMode mode = DEFAULT );

  /**
   * Get the current tracker direct mode for this dragger.
   */
  TrackerDirectMode getTrackerDirectMode() const;

  /**
   * Set the initial tracker direct mode for draggers not yet created.
   * Use this immediately after initializing Open Inventor to set
   * the tracker direct mode (typically to DEFAULT) for all draggers.
   */
  static void setInitialTrackerDirectMode( TrackerDirectMode mode = DEFAULT );

  /**
   * Get the initial tracker direct mode.
   */
  static TrackerDirectMode getInitialTrackerDirectMode();

  /** @TOBEREVIEWED Set the motion matrix.  Triggers value changed callbacks, but only
   * if (newMatrix != the current motionMatrix)
   */
  void            setMotionMatrix( const SbMatrix &newMatrix );

  /**
   * Get the motion matrix.  @BR
   * The motion matrix places the dragger relative to its parent space.
   *
   * Generally, it is better to look
   * in a dragger's fields to find out about its state. For example,
   * looking at the 'translation' field of an SoTranslate1Dragger is
   * easier than extracting the translation from its motion matrix.
   * However for some complex draggers, e.g. SoCenterballDragger, it
   * is not possible to reconstruct the internal matrix from the
   * external fields. This method is useful in that case.
   */
  const SbMatrix &getMotionMatrix();

 SoEXTENDER public:

  // In addition to the public callback functions, these callback
  // functions can also be used by subclasses to find out when things
  // have happened.

  // otherEvent callbacks are called in response to events other than
  // the standard button1Down, mouseMotion, and button1Up events.
  // They are only called if the dragger has grabbed (which occurs
  // only when button1 goes down and picks the dragger).
  void addOtherEventCallback(SoDraggerCB *f, void *userData = NULL);
  void removeOtherEventCallback(SoDraggerCB *f, void *userData = NULL);
  void clearOtherEventCallbacks();

  // Compound draggers should call this for each child dragger
  // so that user callbacks (valueChanged, start, motion, finish, other event)
  // registered with the parent dragger will be invoked based on the child
  // dragger.  Also, this will add the 'transferMotion' callback as a
  // valueChanged callback on the child. Child dragger enableCallbacks field
  // will be automatically connected from parent dragger enableCallbacks field, 
  // so that when parent dragger enableCallbacks field is set, value is the same 
  // for child draggers
  void registerChildDragger(SoDragger *child);
  void unregisterChildDragger(SoDragger *child);

  // These two routines tie the child to the parent, but WITHOUT the
  // transferMotion callback. It is good
  // for child draggers that need to move independently of their parents,
  // but which should still call the parents (valueChanged, start, motion,
  // end, and otherEvent) callbacks when they are dragged.
  void registerChildDraggerMovingIndependently(SoDragger *child);
  void unregisterChildDraggerMovingIndependently(SoDragger *child);

  // Get the matrix which converts from one dragger space to another.
  SbMatrix getLocalToWorldMatrix( SoAction* action = NULL );
  SbMatrix getWorldToLocalMatrix( SoAction* action = NULL );

  // Returns the starting point in local coordinates.
  SbVec3f     getLocalStartingPoint();
  // Returns the starting point in world coordinates.
  SbVec3f     getWorldStartingPoint();

  // Get the matrix which converts from the space of one part into
  // local space. Good to use if transforms occur between 'motionMatrix'
  // and the space you want to work in.
  // Note: This routine will try not to create parts that don't exist.
  //       Instead it finds the existing part that precedes it in traversal.
  //       But this only works if the partName is in this nodekit's catalog.
  //       If the part is nested within another kit below this one or
  //       sitting inside a list part, the part will be created when it
  //       doesn't exist.
  void getPartToLocalMatrix( const SbName &partName,
                             SbMatrix &partToLocalMatrix,
                             SbMatrix &localToPartMatrix);

  // Transforms a given matrix from one space into another space
  void  transformMatrixLocalToWorld( const SbMatrix &fromMatrix,
                                     SbMatrix &toMatrix);
  void  transformMatrixWorldToLocal( const SbMatrix &fromMatrix,
                                     SbMatrix &toMatrix);
  void  transformMatrixToLocalSpace( const SbMatrix &fromMatrix,
                                     SbMatrix &toMatrix, const SbName &fromSpacePartName);

  // Invokes the valueChangedCallbacks.
  // These are invoked whenever setMotionMatrix() changes the motion matrix.
  // If a subclass wishes to invoke the valueChanged callbacks for some
  // other reason, they may call valueChanged(). Example: SoSpotLightDragger
  // changes its angle field without altering the motionMatrix. So it
  // calls valueChanged() to invoke callbacks.
  void valueChanged();

  // Used to calculate motion relative to the dragger's position at the
  // beginning of the dragging.
  const SbMatrix &getStartMotionMatrix() { return startMotionMatrix; }

  // By default, saves the motionMatrix as the startMotionMatrix.
  // Subclasses may want to save additional info. For example, the
  // centerballDragger also saves the matrix that moves the center relative
  // to the motionMatrix.
  virtual void saveStartParameters();

  // Information that's good to have during a valueChanged callback
  const SoPath              *getPickPath()       const;
  const SoEvent             *getEvent() const;

  // Creates a new path leading to this dragger, if the last path given by
  // setTempPathToThis()  is still valid.  Will return NULL if not possible.
  // You must ref() and unref() this new path if you
  // don't want it (and all the nodes along it) to stay around forever.
  SoPath                    *createPathToThis();

  // Surrogate Pick Information. This is relevant if the we are dragging
  // based on the pick of a surrogate part. This happens when you call
  // SoInteractionKit::setPartAsPath() and thus specify a 'stand-in' path
  // to pick when initiating a drag.
  // Owner:
  //       Path to the InteractionKit that owns the surrogate part.
  const SoPath *getSurrogatePartPickedOwner() const
    { return pathToSurrogatePickOwner;}
  // Name:
  //       Name of the surrogate part within the owners list.
  const SbName &getSurrogatePartPickedName() const
    { return surrogateNameInPickOwner; }
  // SurrogatePath:
  //        The owner's surrogate path for this name. This path may
  //        differ from the actual pickPath, but it is guaranteed to
  //        be contained within the pickPath.
  const SoPath *getSurrogatePartPickedPath() const
    { return surrogatePathInPickOwner;}

  // Set the point where the drag begins.
  // The pickedPoint version would usually be the result of a pick.
  void setStartingPoint( const SoPickedPoint *newPoint );
  // The SbVec3f version would usually be a point saved from the end of
  // another gesture. For example, when a modifier key goes down, we might
  // save the current position and use it to begin another connected gesture.
  void setStartingPoint( const SbVec3f &newPoint );

  // Information about the window an event occurred in.
  // Upon construction, the values are defaults.
  // When drag begins, new values are taken from the handleEventAction
  // and used for the duration of the drag.
  // When drag ends, new values are taken from the final handleEventAction.
  //
  // DEPRECATED SINCE OIV 9.3
  // Dragger must not store information related to viewer settings.
  // In a multi-viewers configuration, draggers internal computation can be
  // corrupted by using one of these values set from another viewer
  // This has been solved by directly getting viewvolume and viewport from
  // the state, or from the current action.
  /** @DEPRECATED_BEGIN */
   /**
    * @deprecated No more used.
    * Dragger must not store information related to viewer settings.
    * In a multi-viewers configuration, draggers internal computation can be
    * corrupted by using one of these values set from another viewer
    * This has been solved by directly getting viewvolume and viewport from
    * the state, or from the current action.
    * @DEPRECATED_SINCE_OIV 9.3
    */
  SoDEPRECATED const SbViewVolume      &getViewVolume() { return viewVolume; }
  SoDEPRECATED void  setViewVolume(const SbViewVolume &vol) { viewVolume = vol; }
  SoDEPRECATED const SbViewportRegion  &getViewportRegion() { return vpRegion; }
  SoDEPRECATED void  setViewportRegion(const  SbViewportRegion &reg) { vpRegion = reg; }
  /** @DEPRECATED_END */

  // Get the most recent handleEventAction.
  SoHandleEventAction *getHandleEventAction() const { return handleEventAction; }
  void setHandleEventAction( SoHandleEventAction *newAction );

  // A path leading to 'this.' It is used to calculate the
  // motionMatrix. It is set when a dragger first grabs event, through the
  // handleEvent action, or by setCameraInfo() if NULL at the time.
  void                setTempPathToThis(const SoPath *somethingClose);

  // Called when the dragger gains or loses status as "grabber" of events.
  virtual void grabEventsSetup();
  virtual void grabEventsCleanup();

  // Changes only that part of the matrix for which this dragger has fields.
  // For instance, when called by an SoTranslate1Dragger, any rotations and
  // scales in the matrix will remain unchanged. But the translation will
  // be replaced with value in the 'translation' field.
  //   First, factor mtx to get values for the following:
  //      trans, rot, scale, scaleOrient.
  //      If there's a center field, send it to the factor method.
  //   Replace any of these four values if fields are found named
  //     'translation' 'scaleFactor' 'rotation' and/or 'scaleOrientation'
  //     Note that this could be all or none of the 4 listed.
  //     Values for which no fields are found remain unchanged.
  //   Build a new matrix using the new values. Some may be the originals
  //     and some may have been replaced.
  void workFieldsIntoTransform( SbMatrix &mtx );

  // Same as above, but values are given explicitly as pointers.
  // If the pointers are NULL, the values in the matrix are not changed.
  static void workValuesIntoTransform( SbMatrix &mtx,
                                       const SbVec3f *translationPtr,
                                       const SbRotation *rotationPtr,
                                       const SbVec3f *scaleFactorPtr,
                                       const SbRotation *scaleOrientationPtr,
                                       const SbVec3f *centerPtr);

  // Faster versions of getTransform() and factor() that take advantage of
  // the case where there is no scaleOrientation. Reverts to slow method
  // if it needs to.
  // This method will not work if the matrix given contains any scales
  // less than zero, and it does not check for that case.
  static void getTransformFast( SbMatrix &mtx, SbVec3f &translation,
                                SbRotation &rotation, SbVec3f &scaleFactor,
                                SbRotation &scaleOrientation,
                                const SbVec3f &center);
  static void getTransformFast( SbMatrix &mtx, SbVec3f &translation,
                                SbRotation &rotation, SbVec3f &scaleFactor,
                                SbRotation &scaleOrientation);

  // Appends the given motion to the end of 'mtx'.
  // 'conversion' transforms from the space the motion is defined in
  // to the space 'mtx'.
  static SbMatrix appendTranslation( const SbMatrix &mtx,
                                     const SbVec3f &translation,
                                     const SbMatrix *conversion = NULL );
  static SbMatrix appendScale( const SbMatrix &mtx,
                               const SbVec3f &scale, const SbVec3f &scaleCenter,
                               const SbMatrix *conversion = NULL );
  static SbMatrix appendRotation( const SbMatrix &mtx,
                                  const SbRotation &rot, const SbVec3f &rotCenter,
                                  const SbMatrix *conversion = NULL );

  // Is the current tracker direct mode MOVE, ROTATE or FREE ?
  SbBool isTrackerDirectMode() const;

 SoINTERNAL public:
  void GLRender(SoGLRenderAction *action);

  static void initClass();
  static void exitClass();
  SB_THREAD_TLS_HEADER();

  // Initialize ALL Inventor dragger classes
  static void initClasses();
  static void exitClasses();

  // These control behavior of the rotational parts. If FRONT, no matter
  // where you hit the dragger relative to its center, it will behave as if
  // you are dragging from the front. If BACK, the rear. If USE_PICK,
  // then it depends on the relationship between the picked point and the
  // center of the dragger.
  enum ProjectorFrontSetting {
    FRONT, BACK, USE_PICK
  };
  void setFrontOnProjector( ProjectorFrontSetting newVal )
    { projectorFrontSetting = newVal; }
  ProjectorFrontSetting getFrontOnProjector() const
    { return projectorFrontSetting;}

  inline void setInteracting(bool flag) { m_draggerInteracting = flag; }

 protected:

  // Constructor
  SoDragger();

  // Sensor attached to enableCallbacks field
  SoFieldSensor* m_enableSensor;

  //Field sensor callback
  static void enableCB( void *, SoSensor * );

  // Get the last known position of the locator (mouse).
  // 2D locater positions have (0,0) at lower-left, and are
  // relative to the viewport.
  // Normalized positions go from 0.0 to 1.0.
  // Regular positions go from 0 to (vpSize - 1)
  SbVec2f     getNormalizedLocaterPosition();
  const SbVec2f&     getLocaterPosition();

  // Get the 3D tracker device's ray in world coords (new in v3.0)
  SbLine  getTrackerRay();

  // Get the position of the locater when dragging started.
  const SbVec2f&     getStartLocaterPosition() const     { return startLocater; }

  // The start locater position is automatically set when button 1
  // goes down over the dragger. Subclasses may wish to reset it, such
  // as when a constraint key goes down during dragging.
  void        setStartLocaterPosition(const SbVec2f& p)   { startLocater = p; }

  // Has the locater moved far enough from where it started to
  // choose a constraint gesture.
  SbBool      isAdequateConstraintMotion();

  // Given a pickPath and a surrogatePath, decides whether it should
  // grab based on the surrogate. First, the pickPath must
  // contain the surrogatePath, indicating that the surrogate was picked.
  // Second, we consider the part of the pickPath below the point where
  // the surrogatePath ends.
  // If this bottom section contains other draggers, then we will pass it up.
  // This is because the other draggers will want to grab when they find out
  // they've been picked.
  virtual SbBool shouldGrabBasedOnSurrogate( const SoPath *pickPath,
                                             const SoPath *surrogatePath );

  //
  // The dragger looks in this action to get information about the camera
  // and the viewport.  Usually the action used is just the handleEventAction.
  void setCameraInfo( SoAction *action );

  // This is called during traversal by a HandleEventAction. It
  // calls ha->setHandled() if the event is handled.
  virtual void               handleEvent(SoHandleEventAction *ha);

  // This should be called by every child dragger of a compound dragger
  // as a result of compoundDragger->registerChildDragger( childDragger );
  // Called on the compoundDragger when childDragger's value changes.
  // Gets the motionMatrix from a the child dragger. Appends that change
  // to the parent dragger's savedStartMatrix, and sets the result as the
  // parent's motionMatrix.
  // Then, it zeros out the motionMatrix of the child dragger.
  void transferMotion(SoDragger *child);

  // Set/get whether the dragger should be ignored during bounding
  // box calculations.
  void    setIgnoreInBbox( SbBool newVal ) { ignoreInBbox = newVal; }
  SbBool  isIgnoreInBbox() { return ignoreInBbox; }

  // Implements getBoundingBox action. Differs from separator as follows:
  // If the 'ignoreInBbox' flag is set to TRUE, then it will return without
  // traversing children.
  virtual void        getBoundingBox(SoGetBoundingBoxAction *action);

  // Stubs used by compound draggers to get user callbacks from
  // the child dragger
  static void childTransferMotionAndValueChangedCB(void *, SoDragger *);
  static void childValueChangedCB(void *, SoDragger *);
  static void childStartCB(void *, SoDragger *);
  static void childMotionCB(void *, SoDragger *);
  static void childFinishCB(void *, SoDragger *);
  static void childOtherEventCB(void *, SoDragger *);

  // Called by the above child callbacks. Establishes which child dragger
  // is currently active. Set at beginning of child callback, returned to
  // original value at end. Returns current value at time method is called.
  void       setActiveChildDragger( SoDragger *newChildDragger );
  SoDragger *getActiveChildDragger() const { return activeChildDragger; }

  // Called by the SoBaseKit::write() method.
  //
  // Draggers don't want to write out fields if they have default vals.
  //
  // sets isActive to default if default and not connected.
  //
  // Looks for fields named:
  //    'rotation'    with value SbRotation::identity()
  //    'translation' with value (0,0,0)
  //    'center'      with value (0,0,0)
  //    'scaleFactor' with value (1,1,1)
  // and sets them to default if they are not connected from a field.
  // (most draggers are missing at least some of these, but thats okay)
  //
  // Then calls the method for SoInteractionKit.
  //
  // NOTE: Parts which are set to default may still wind up writing to file
  //       if, for example, they lie on a path.
  virtual void setDefaultOnNonWritingFields();

  // In tracker direct mode, apply motion of tracked input device
  // directly to dragger's motion matrix.  (new for v5.0)
  virtual SbBool applyTrackerMotion();

  virtual ~SoDragger();

  // Class static thread local storage
  struct MTstruct {
    SoGetMatrixAction *m_matrixAction;
    SoSearchAction    *m_searchAction;
  };

  // Support for tracker direct mode (for immersive environments)
  //
  // Allows direct mode to be set for all draggers
  static TrackerDirectMode m_initialDirectMode;
  // Current direct mode for this dragger instance
  TrackerDirectMode        m_directMode;
  // Default direct mode for this class of dragger
  TrackerDirectMode        m_defaultDirectMode;
  // Saved start position of tracked input device
  SbVec3f                  m_trackerStartPos;
  // Saved start orientation of tracked input device
  SbRotation               m_trackerStartRot;

  SbViewVolume        viewVolume;         // view volume for xsection tests
  SbViewportRegion    vpRegion;           // view volume for xsection tests

 private:

  // lists of callback functions
  SoCallbackList      *startCallbacks;
  SoCallbackList      *motionCallbacks;
  SoCallbackList      *finishCallbacks;
  SoCallbackList      *valueChangedCallbacks;

  SoCallbackList      *otherEventCallbacks;

  SbBool    valueChangedCallbacksEnabled;
  SoDragger *activeChildDragger;

  SoHandleEventAction *handleEventAction; // current event action

  // A record of the world space point which initiated the dragging.
  // This might be set from a pickedPoint of a handleEventAction,
  // or explicitly from a given point when a meta-key callback
  // changes gestures mid-stream and wants to select its own transitional
  // starting point.
  SbVec3f             startingWorldPoint;

  // Used by parent draggers to save initial matrix when motion begins.
  SbMatrix startMotionMatrix;

  // Where the locater was when dragging was initiated
  SbVec2f     startLocater;


  // sets pick path and tempPathToThis
  void                setPickPath(SoPath *newPickPath);
  SoPath              *pickPath;          // pick path to the dragger

  // sets surrogate part picks.
  void setNoPickedSurrogate();
  void setPickedSurrogate( SoPath *pathToOwner, SbName &nameUsedByOwner,
                           SoPath *pathUsedByOwner );

  SbName surrogateNameInPickOwner;
  SoPath *pathToSurrogatePickOwner;
  SoPath *surrogatePathInPickOwner;

  // A tempPath leading to 'this.' It is used to calculate the
  // motionMatrix. It is set when a dragger first grabs event, through the
  // handleEvent action, or by setCameraInfo() if NULL at the time.
  // A tempPath does not increase any ref counts, so keeping this path
  // will not prevent this node from being deleted. However, we must be
  // very careful before using it, since some nodes my get deleted out from
  // under us. The variable tempPathNumKidsHack helps us fix up paths
  // that have changed since the path was set.
  SoTempPath          *tempPathToThis;
  SbPList             *tempPathNumKidsHack;
  // Determines if this path can actually be used. Since a temp path
  // does not ref the nodes, some nodes my get deleted out from
  // under us. This routine makes sure that everythings all right.
  SbBool              isTempPathToThisOk();
  // Creates a temp path copy of the full path.
  SoTempPath      *createTempPathFromFullPath( const SoFullPath *fp ) const;

  // Minimum number of pixels to move before choosing a constraint
  // based on the gesture.
  float         minGesture;

  // The smallest scale that any dragger will write. If the user attempts
  // to go below this amount, the dragger will set it to this minimum.
  // Default is .0001
  static float       minScale;

  // We keep these matrices and their inverses around
  // to use when converting between spaces. The four
  // pairs are cached; the pair becomes invalud when its
  // valid flag is set to FALSE.

  // Called to make sure these matrixes are up to date.
  void validateMatrices( SoAction* );

  // These matrices are ones that are commonly queried by
  // subclasses. So, we cache them.
  // Two things determine the localToWorld matrix. The pathToThis and
  // the motionMatrix. If either value is invalid, we need to recalculate.
  // But depending on which one it is, we either need to run a matrix
  // action on the pick path or just on the motionMatrix.
  SbBool   cachedPathToThisValid;
  SbBool   cachedMotionMatrixValid;
  SbMatrix cachedMotionMatrix;
  // PostMotion is the matrix space just AFTER the motion matrix.
  SbMatrix postMotionToWorldMatrix;
  SbMatrix worldToPostMotionMatrix;
  // PreMotion is the matrix space just BEFORE the motion matrix.
  SbMatrix preMotionToWorldMatrix;
  SbMatrix worldToPreMotionMatrix;

  // Used so that draggers don't try to include themselves
  // as part of their own sizing boxes. By default this is FALSE.
  SbBool ignoreInBbox;

  // Keeps track of whether the mouse has been moved since the mouse
  // went down.
  SbBool mouseMovedYet;
  bool m_draggerInteracting;

  ProjectorFrontSetting projectorFrontSetting;
};

#endif /* _SO_DRAGGER_ */

