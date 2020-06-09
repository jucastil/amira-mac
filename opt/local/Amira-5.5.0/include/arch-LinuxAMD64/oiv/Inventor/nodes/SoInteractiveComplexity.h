/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef SO_INTERACTIVE_COMPLEXITY_H
#define SO_INTERACTIVE_COMPLEXITY_H

#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFFloat.h>

#include <Inventor/STL/map>
#include <Inventor/sensors/SoAlarmSensor.h>

/**
 * Field interactive complexity node.
 *
 * @ingroup PropertyNodes
 *
 * @DESCRIPTION
 * This node allows the application to define different parameter values
 * for certain fields of specific node classes, depending on whether a user interaction,
 * for example moving the camera, is occurring.  This means that while the
 * camera is moving these fields will use a specified "interaction" parameter
 * value, but when interactive manipulation is stopped these fields will
 * automatically change to a specified "still" parameter value.  Optionally,
 * for scalar fields, the transition from interaction value to still value
 * can be automatically animated using a specified increment.
 *
 * Note: The values specified in SoInteractiveComplexity override the values in
 * the fields of the specified nodes during rendering. But calling getValue() on 
 * the fields still returns the value set directly into the field (or the default
 * value if none was set).
 *
 * This is a powerful technique for maintaining an interactive framerate
 * when interacting with GPU intensive datasets or rendering effects, while
 * still getting a final image with very high quality and giving the user
 * a "progressive refinement" effect while transitioning from interaction
 * back to "still".
 *
 * These settings are applied to all instances of the node class containing the
 * specified field and are declared with a specially formatted string set in the
 * #fieldSettings field.  For scalar fields like SoSFInt, the string looks like this: @BR
 * "ClassName FieldName InteractionValue StillValue [IncrementPerSecond]"
 *
 *   If @I IncrementPerSecond @i is omitted, @I StillValue @i is applied as soon as
 *   interaction stops.  Else the transition from
 *   @I InteractionValue @i to @I StillValue @i is automatically animated.
 *   Because incrementing is actually done at each redraw, and redraw happens many times
 *   per second, IncrementPerSecond is allowed to be greater than StillValue.
 *   In the following code, the field named @I numSlices @i belonging to the class
 *   SoVolumeRender will be set to 500 during an interaction. When the interaction
 *   stops, @I numSlices @i will be increased by 2000 every second until it reaches 1000.
 *   Effectively this means that the StillValue (1000) will be reached
 *   in (1000-500)/2000 = 0.25 seconds.
 *   \oivnetdoc
 *     \code
 *     SoInteractiveComplexity icplx = new SoInteractiveComplexity();
 *     icplx.fieldSettings.Set1Value(0, "SoVolumeRender numSlices 500 1000 2000");
 *     root.AddChild(icplx);
 *     root.AddChild(volumeRender);
 *     \endcode
 *   \else
 *     \code
 *     SoInteractiveComplexity* icplx = new SoInteractiveComplexity;
 *     icplx->fieldSettings.set1Value(0, "SoVolumeRender numSlices 500 1000 2000");
 *     root->addChild(icplx);
 *     root->addChild(volumeRender);
 *     \endcode
 *   \endoivnetdoc
 *
 *  A time delay before changing the value, or starting the animation, can be
 *  set using the #refinementDelay field.
 *
 *  The field #interactiveMode allows to force the use of the InteractionValue or the StillValue.
 *
 *  Only a limited number of fields are supported by this node:
 *  - SoComplexity
 *    - textureQuality
 *    - value
 *  - SoOrthoSlice
 *    - largeSliceSupport
 *  - SoShadowGroup
 *    - isActive
 *    - quality
 *  - SoVolumeGroup
 *    - multiVolumes
 *  - SoVolumeRender
 *    - interpolation
 *    - lowScreenResolutionScale
 *    - numSlices
 *    - projectedTileSubdivision
 *  - SoVolumeRenderingQuality
 *    - boundaryOpacity
 *    - colorInterpolation
 *    - edgeColoring
 *    - edgeDetect2D
 *    - gradientQuality
 *    - lighting
 *    - segmentedInterpolation
 *  - SoVolumeSkin
 *    - largeSliceSupport
 *
 * @FILE_FORMAT_DEFAULT
 *    InteractiveComplexity {
 *    @TABLE_FILE_FORMAT
 *       @TR fieldSettings             @TD []
 *       @TR refinementDelay           @TD 0.5
 *       @TR interactiveMode           @TD AUTO
 *    @TABLE_END
 *    }
 *
 * @SEE_ALSO
 *    SoComplexity
 */
class INVENTOR_API SoInteractiveComplexity : public SoNode
{
  SO_NODE_HEADER(SoInteractiveComplexity);

public:
  SoInteractiveComplexity();

  /** Interactive mode */
  enum InteractiveMode {
    /** Automatically detect when a user interaction is occurring (default) */
    AUTO,
    /** Behave like a user interaction is occurring (always use InteractionValue) */
    FORCE_INTERACTION,
    /** Behave like there isn't any interaction (always use StillValue) */
    FORCE_STILL,
    /** Behave like there isn't any SoInteractiveComplexity node */
    DISABLED
  };

  /**
   * Each string in this field specifies the interactionValue and stillValue
   * for a specific field of a specific node class.  The format is:
   * <table>
   *  <tr>
   *   <td>For scalar fields 
   *       (SoSFInt32, SoSFFloat...)</td>
   *   <td>ClassName FieldName InteractionValue StillValue [IncrementPerSecond]</td>
   *  </tr>
   *  <tr>
   *   <td>For SoSFBool fields 
   *       (NumberOfSeconds = delay before switching state)</td>
   *   <td>ClassName FieldName InteractionValue [StillValue] [NumberOfSeconds]</td>
   *  </tr>
   *  <tr>
   *   <td>For SoSFEnum fields</td>
   *   <td>ClassName FieldName InteractionValue StillValue</td>
   *  </tr>
   * </table>
   *
   * The following example defines values for a SoSFInt32, a SoSFBool and a SoSFEnum:
   * \oivnetdoc
   *   \code
   *   SoInteractiveComplexity icplx = new SoInteractiveComplexity();
   *   icplx.fieldSettings.Set1Value(0, "SoVolumeRender numSlices 500 1000 1");
   *   // Will switch to TRUE 2 seconds after stopping interaction
   *   icplx.fieldSettings.set1Value(1, "SoShadowGroup isActive FALSE 2");
   *   icplx.fieldSettings.set1Value(2, "SoVolumeRenderingQuality gradientQuality LOW HIGH");
   *   \endcode
   * \else
   *   \code
   *   icplx->fieldSettings.set1Value(0, "SoVolumeRender numSlices 500 1000 1");
   *   // Will switch to TRUE 2 seconds after stopping interaction
   *   icplx->fieldSettings.set1Value(1, "SoShadowGroup isActive FALSE 2");
   *   icplx->fieldSettings.set1Value(2, "SoVolumeRenderingQuality gradientQuality LOW HIGH");
   *   \endcode
   * \endoivnetdoc
   *
   *
   */
  SoMFString fieldSettings;

  /**
   * Time in seconds after interaction stops before field values start to be increased. Default is 0.5.
   */
  SoSFFloat refinementDelay;

  /**
  * Interactive mode.
  * Use enum #InteractiveMode. Default is AUTO.
  *
  * @FIELD_SINCE_OIV 8.6
  */
  SoSFEnum interactiveMode;

SoEXTENDER public:
  virtual void doAction(SoAction *action);
  virtual void GLRender(SoGLRenderAction *action);

SoINTERNAL public:
  /**
   * Handle field change
   */
  virtual void notify(SoNotList *list);

  static void initClass();
  static void exitClass();

  /** Return the current value of the field*/
  double getScalarFieldValue(SoState* state, const SoSField* field);
  SbBool getBooleanFieldValue(SoState* state, const SoSFBool* field);
  int getEnumFieldValue(SoState* state, const SoSFEnum* field);

  /** True if the field has values for interactive mode */
  bool isBounded(const SoField* field) const;

protected:
  struct ScalarBounds
  {
    double startBound;
    double endBound;
    double increment;
    // used to return the previous val during delayed pass
    double currentVal;
    bool immediate;
  };
  typedef std::map<SbString, ScalarBounds> ScalarBoundsMap;

  virtual ~SoInteractiveComplexity();

  /** True if field is a scalar field */
  static SbBool isScalarField(const SoField* field);

  /** recreate the parameter map */
  void updateFieldList();
  void addParameters(const SbString& paramString);

  /** Handle paramString for scalar field and add parameters to the parameter map */
  void handleScalarParam(const SbString& paramString, const std::vector<SbString>& token);
  void handleBoolParam(const SbString& paramString, const std::vector<SbString>& token);
  void handleEnumParam(const SbString& paramString, const std::vector<SbString>& token,
                       const SoField* field);

  /** Display en error if numParam != expected */
  bool checkParamNumber(size_t numParam, size_t expected, const SbString& fieldName) const;

  /** Get the name of the class containing field and the name of the field */
  void getClassAndFieldName(const SoField* field, SbString& className, SbString& fieldName) const;

  /** Get the name of the class containing field and the name of the field */
  double getScalarFieldValue(SoState* state, const SoSField* field,
                             const SbString& classAndFieldName, bool updateValue = false);

  /** Compute current value of all field types */
  void updateAllFieldsValue(SoState* state);

  /** Called by the redrawSensor. Just shedule a redraw for this node. 
   * data must be this node. */
  static void sensorCB(void *data, SoSensor *sensor);

  /** All bounds are converted to a scalar bound */
  ScalarBoundsMap m_scalarBounds;

  /** Sensor use to schedule a display at the end of refinementDelay */
  SoAlarmSensor m_redrawSensor;
};

#endif //SO_INTERACTIVE_COMPLEXITY_H
