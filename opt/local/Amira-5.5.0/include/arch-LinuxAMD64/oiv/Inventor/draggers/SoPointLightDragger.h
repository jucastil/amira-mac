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


#ifndef  _SO_POINT_LIGHT_DRAGGER_
#define  _SO_POINT_LIGHT_DRAGGER_

#include <Inventor/SbLinear.h>
#include <Inventor/draggers/SoDragger.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/sensors/SoSensor.h>

class SoFieldSensor;

/**
 * Sun-shaped icon you can translate in 3D by dragging with the mouse.
 * 
 * @ingroup draggers
 * 
 * @DESCRIPTION
 *   SoPointLightDragger is a dragger that looks like a point light source, can be
 *   translated in three directions, and has a #translation field that always
 *   reflects its position in local space. The point light dragger also has a special
 *   material part which can be used to make it take on the color of a light
 *   source.
 *   
 *   @B Remember: @b This is @B not @b a light source! It just looks like one. If
 *   you want to move a light with this dragger, you can either:
 *   
 *     - Use an SoPointLightManip, which is subclassed from SoLight. It creates one of
 *       these draggers and uses it as the interface to change the @B location @b of its
 *       light source (see the SoPointLightManip reference page). The manipulator also
 *       edits the @B material @b part of this dragger to match the color of light the
 *       manipulator is producing.
 *   
 *     - Use a field-to-field connection to connect the @B location @b of a light
 *       source from this dragger's #translation field.
 *   
 *   This dragger contains an SoDragPointDragger, which you drag through 3-space using
 *   an integrated set of linear and planar draggers. (For detailed information on
 *   how to use SoDragPointDragger, see its reference page.) The point light dragger
 *   sets the planar translation parts of this dragPoint dragger with a new default
 *   that looks like a shining sun emanating rays of light (okay, so use your
 *   imagination).
 *   
 *   By changing the @B material @b part you can change the color of the sun shape,
 *   because the default part contains no SoMaterial nodes. This fact enables the
 *   SoPointLightManip (not the dragger, the manipulator) to color its dragger to
 *   match the color of the light it is emanating. Recall that a point light
 *   @B manip @b is derived from SoLight and creates a point light @B dragger @b to
 *   provide an interface and geometrical presence on screen. The manipulator also
 *   has a @B color @b field; when the light color changes, it changes the
 *   @B material @b part of its dragger so that they match.
 *   
 *   You can change the parts in any instance of this dragger using
 *   setPart().
 *   
 *   The default part geometries are defined as resources for this SoPointLightDragger
 *   class. They are detailed in the Dragger Resources section of the online
 *   reference page for this class. You can make your program use different default
 *   resources for the parts by copying the file
 *   @B $OIVHOME/data/draggerDefaults/pointLightDragger.iv @b into your own
 *   directory, editing the file, and then setting the environment variable
 *   @B SO_DRAGGER_DIR @b to be a path to that directory.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PointLightDragger {
 *    @TABLE_FILE_FORMAT
 *       @TR renderCaching                              @TD AUTO
 *       @TR boundingBoxCaching                         @TD AUTO
 *       @TR renderCulling                              @TD AUTO
 *       @TR pickCulling                                @TD AUTO
 *       @TR isActive                                   @TD FALSE
 *       @TR translation                                @TD 0 0 0
 *       @TR callbackList                               @TD NULL
 *       @TR material                                   @TD \<pointLightOverallMaterial resource\>
 *       @TR translator                                 @TD DragPointDragger {
 *       @TR      }                                     @TD 
 *       @TR translator.yzTranslator.translator         @TD \<pointLightTranslatorPlaneTranslator resource\>
 *       @TR translator.xzTranslator.translator         @TD \<pointLightTranslatorPlaneTranslator resource\>
 *       @TR translator.xyTranslator.translator         @TD \<pointLightTranslatorPlaneTranslator resource\>
 *       @TR translator.yzTranslator.translatorActive   @TD \<pointLightTranslatorPlaneTranslatorActive resource\>
 *       @TR translator.xzTranslator.translatorActive   @TD \<pointLightTranslatorPlaneTranslatorActive resource\>
 *       @TR translator.xyTranslator.translatorActive   @TD \<pointLightTranslatorPlaneTranslatorActive resource\>
 *       @TR translator.xTranslator.translator          @TD \<pointLightTranslatorLineTranslator resource\>
 *       @TR translator.yTranslator.translator          @TD \<pointLightTranslatorLineTranslator resource\>
 *       @TR translator.zTranslator.translator          @TD \<pointLightTranslatorLineTranslator resource\>
 *       @TR translator.xTranslator.translatorActive    @TD \<pointLightTranslatorLineTranslatorActive resource\>
 *       @TR translator.yTranslator.translatorActive    @TD \<pointLightTranslatorLineTranslatorActive resource\>
 *       @TR translator.zTranslator.translatorActive    @TD \<pointLightTranslatorLineTranslatorActive resource\>
 *    @TABLE_END
 *    }
 * 
 * 
 * @DRAGGER_RESOURCES
 *    @TABLE_DRAGGER_RESOURCES
 *       @TR Resource:      @TD @B pointLightOverallMaterial @b
 *       @TR Part:          @TD material
 *       @TR Appearance:    @TD white. half strength emissive, half strength diffuse
 *       @TR Description:   @TD sets material for the sun shape when stationary. Resource for the moving sun,
 *                           pointLightTranslatorPlaneTranslatorActive, contains a yellow material for
 *                           highlighting.
 * 
 *       @TR Resource:      @TD @B pointLightTranslatorPlaneTranslator @b
 *       @TR Parts:         @TD translator.yzTranslator.translator@BR
 *                               translator.xzTranslator.translator@BR
 *                               translator.xyTranslator.translator 
 *       @TR Appearance:    @TD sun shape with no material
 *       @TR Description:   @TD picking these parts initiates dragging by the yz, xz, and xy planar draggers
 *                           respectively.
 * 
 *       @TR Resource:      @TD @B pointLightTranslatorPlaneTranslatorActive @b
 *       @TR Parts:         @TD translator.yzTranslator.translatorActive@BR
 *                               translator.xzTranslator.translatorActive@BR
 *                               translator.xyTranslator.translatorActive 
 *       @TR Appearance:    @TD yellow sun shape
 *       @TR Description:   @TD shown during planar dragging in the yz, xz, and xy planes respectively.
 * 
 *       @TR Resource:      @TD @B pointLightTranslatorLineTranslator @b
 *       @TR Parts:         @TD translator.xTranslator.translator@BR
 *                               translator.yTranslator.translator@BR
 *                               translator.zTranslator.translator 
 *       @TR Appearance:    @TD white cylinder
 *       @TR Description:   @TD picking these parts initiates dragging in the x, y, and z linear draggers
 *                           respectively.
 * 
 *       @TR Resource:      @TD @B pointLightTranslatorLineTranslatorActive @b
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
 *       @TR   callbackList  @TD   NodeKitListPart   @TD    --      @TD   yes     
 *       @TR   material      @TD   Material          @TD    --      @TD   yes     
 *       @TR   translator    @TD   DragPointDragger  @TD    --      @TD   yes     
 *    @TABLE_END
 * 
 *    Extra Information for List Parts from Above Table
 *    @TABLE_LIST_PART
 *       @TR   callbackList  @TD   Separator         @TD   Callback, EventCallback
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

class INVENTOR_API SoPointLightDragger : public SoDragger
{
  SO_KIT_HEADER(SoPointLightDragger);

  // This gives the dragger an overall material.  It is edited by lightManips
  // to make its dragger match the color of the light.  Any materials within 
  // other parts will override this one. 
  SO_KIT_CATALOG_ENTRY_HEADER(material);

  SO_KIT_CATALOG_ENTRY_HEADER(translator);

 public:
  /**
   * Constructor.
   */
  SoPointLightDragger();

  /**
   * Position of the dragger.
   * 
   */
  SoSFVec3f    translation;

 SoINTERNAL public:
  static void initClass();  // initialize the class
  static void exitClass();
 protected:

  SoFieldSensor *fieldSensor;
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

  virtual ~SoPointLightDragger();

 private:
  static const char geomBuffer[];
};    

#endif  /* _SO_POINT_LIGHT_DRAGGER_ */

