/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas Daguise (Jan 2002)
**=======================================================================*/
#ifndef  _SO_DIALOG_SLIDER_
#define  _SO_DIALOG_SLIDER_

#include <DialogViz/dialog/SoDialogComponent.h>
#include <Inventor/fields/SoMFColor.h>

class SoDialogCustomSlider;
class SbLineProjector;
class SoEventCallback;
class SoKeyboardEvent;

/**
 * @VSGEXT Abstract class for the slider nodes.
 * 
 * @ingroup Dialog
 * 
 * @DESCRIPTION
 *   This node defines the properties for slider components.
 *   From left to right, it consists of:
 *     - a label,
 *     - a check box representing the #continuousTrigger field,
 *     - the slider,
 *     - an edit zone which displays the current value.
 *
 * @SEE_ALSO
 *   SoDialogIntegerSlider,
 *   SoDialogRealSlider
 *
 */

class DIALOGVIZ_API SoDialogSlider : public SoDialogComponent  
{
  SO_DG_HEADER(SoDialogSlider);

 public:

  /**
   * Specifies whether the edit zone value is visible or not. Default is TRUE.
   */
  SoSFBool valueVisible;

  /**
   * Specify the string format of the slider value edit zone. This string is C formated..
   */
  SoSFString format;

  /**
   * If this field is set to FALSE, the associated interface is called when
   * the mouse button is released. If set to TRUE, the associated interface is called
   * each time the slider cursor is moved. Default is FALSE.
   */
  SoSFBool continuousTrigger;
  
  /** 
   * Specifies whether the toggle button that manages continuous triggering 
   * is visible or not. Default is TRUE.
   */
  SoSFBool toggleVisible;

  /**
   * Allows user to enter a value outside the min/max range. If such a value is entered,
   * the min/max range is automatically extended. Default is FALSE.
   */
  SoSFBool fixedLimits;

  /**
   * Contains an array of colors. These colors are rendered in the slider from left to right
   * according to the @B shadedColors @b field. If no colors are specified, the default
   * color of the slider is gray. Default array is empty.
   */
  SoMFColor colors;

  /**
   * Indicates is the set of colors defined in the field @B colors @b is rendered in shaded 
   * mode or not. Default is TRUE.
   */
  SoSFBool shadedColors;

  /**
   * Constructor.
   */
  SoDialogSlider();


  /*==============================================================================*/
 SoINTERNAL public:
  virtual void   buildWidget(SoWidget parent, SbVec2i32 &rSize, SbVec2i32 &pos, SbBool isActive2d);
  virtual void   destroyWidget();
  virtual void   eventNotify(unsigned int event, uintptr_t param);
  virtual SoWidget getLabelWidget();
  static  void   initClass();
  static  void   exitClass();
  virtual void   setValueFromEdit(SbBool ) {};
  virtual void   setValueFromSlider(float ) {};
  virtual void   changeSliderValue() {};
  virtual void   updateFromSensor(SoSensor* sensor);
  float   getValue();
  static  void   finishCallback(void *slider, float newValue);
  static  void   valueChangeCallback(void* slider, float newValue);
  virtual void   setValue() {};
  SbBool getActive2d() { return m_isActive2d; };

// methods called by callbacks
  void changeValueFromSlider(float newValue);
  void changeValueAfterFinish(float newValue);
  void changeSliderFromEdit();
  void changeSliderFromSlider(float num);

  // pos and size changes
  void updateEditWidget();
  void updateSliderWidget();
  void updateLabelWidget();
  void updateToggleWidget();

 protected:
  SoWidget m_sliderWidget;
  SoWidget m_toggleWidget;
  SoWidget m_editWidget;
  int    m_sliderWidth;
  int    m_editWidth;
  float  m_sliderValue;
  SoDialogCustomSlider* m_dialogCustomSlider;

  virtual        ~SoDialogSlider();

  virtual void changeEditValue() {};
  SbString getValueFromEdit();
  virtual int computeEditZoneWidth() {return 0;};

  void updateWidget();

 private:
  /* === FIELDS DECLARATION === */
  FIELD_SENSOR(valueVisible);
  FIELD_SENSOR(continuousTrigger);
  FIELD_SENSOR(toggleVisible);
  FIELD_SENSOR(fixedLimits);
  FIELD_SENSOR(colors);
  FIELD_SENSOR(shadedColors);
  FIELD_SENSOR(format);

  /* === COMPUTING METHODS === */
  virtual SbVec2i32 getComponentInitSize();
  virtual void    getDefaultSize(SbVec2i32 &size, SbVec2i32 &min, SbVec2i32 &max);

  /* === CREATION METHODS === */
  void createEditWidget();
  void createLabelWidget();
  void createSliderWidget();
  void createToggleWidget();

  /* === UPDATE METHODS === */

  // local change methods
  virtual void changeValueVisible();
  virtual void changeToggleVisible();
  virtual void changeContinuousTrigger();
  virtual void changeFormat();

  // inherited change methods from SoDialogComponent
  virtual void changeEdgeStyle();
  virtual void changeLabelVisibility();

  // inherited change methods from SoDialogViz
  virtual void changeEnable();
  virtual void changeWidgetEnable(SbBool state);
  virtual void changeLabel();
  virtual void changeLabelAlignment();

///////////////////////////////////////////////////////////////////////////////////////
// 3D methods
SoINTERNAL public:
  static char* DialogSlider; // Internal default skins.
  static void change3DSkin();
  static SbBool isSkinLoaded();
  static void setSkinLoaded(SbBool loaded);

  SbBool ip_isEditing;

  void change3DSliderValue();
  void change3DCursor();

  static void processKeyEvents(void *inDragger, SoEventCallback *cb);

protected:

  SO_DG_CATALOG_ENTRY_HEADER( labelSep      );
  SO_DG_CATALOG_ENTRY_HEADER( labelSwitch   );
  SO_DG_CATALOG_ENTRY_HEADER( labelProp     );
  SO_DG_CATALOG_ENTRY_HEADER( checkSep      );
  SO_DG_CATALOG_ENTRY_HEADER( checkSwtch    );
  SO_DG_CATALOG_ENTRY_HEADER( checkStateOff );
  SO_DG_CATALOG_ENTRY_HEADER( checkStateOn  );
  SO_DG_CATALOG_ENTRY_HEADER( sliderSep     );
  SO_DG_CATALOG_ENTRY_HEADER( frameSep      );
  SO_DG_CATALOG_ENTRY_HEADER( frame         );
  SO_DG_CATALOG_ENTRY_HEADER( cursorSep     );
  SO_DG_CATALOG_ENTRY_HEADER( cursor        );
  SO_DG_CATALOG_ENTRY_HEADER( edtSwtch      );
  SO_DG_CATALOG_ENTRY_HEADER( edtFrmSep     );
  SO_DG_CATALOG_ENTRY_HEADER( edtFrmSwtch   );
  SO_DG_CATALOG_ENTRY_HEADER( valueFrame    );
  SO_DG_CATALOG_ENTRY_HEADER( editValueFrame);
  SO_DG_CATALOG_ENTRY_HEADER( editTextSep   );
  SO_DG_CATALOG_ENTRY_HEADER( editTextProp  );

  SoScale *sliderFrameScale, *sliderEditFrameScale;
  SoText3 *sliderLabel, *sliderEditText;
  SoTransform *sliderFrameTransform, *sliderEditFrameTransform;
  SoTranslation *sliderLabelTranslation, *sliderToggleTranslation;
  SoTranslation *sliderFrameTranslation, *sliderEditFrameTranslation;
  SoTranslation *sliderEditTextTranslation, *sliderCursorTranslation, *sliderCursorPosTranslation;

  SbString get3DValueFromEdit();
  virtual void change3DEditValue();
  virtual void change3DEnable();

private:
  SbBox3f m_editTextCachedBBox;
  static SbBool m_isSkinLoaded;

  SbLineProjector* m_lineProj;
  SbVec3f m_initialPos;
  int m_slider3DWidth;

  void create3DDialogSlider();
  void update3DSlider();
  void update3DLabel();

  virtual void set3DInactive();
  virtual void change3DLabelVisibility();
  virtual void change3DLabel();
  virtual void change3DLabelAlignment();
  void change3DContinuousTrigger();
  void change3DValueVisible();
  void change3DToggleVisible();

  static void startCB3D( void *, SoDragger *inDragger );
  static void motionCB3D( void *, SoDragger *inDragger );
  static void finishCB3D( void *, SoDragger *inDragger );
  void draggerStartCallback3D();
  void draggerMotionCallback3D();
  void draggerFinishCallback3D();

  virtual void computeNewSliderEditValue(SoKeyboardEvent* ) {};

SoEXTENDER public:
  virtual void finish3DEditing() {};
///////////////////////////////////////////////////////////////////////////////////////

};

#endif // _SO_DIALOG_SLIDER_
