/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Oct 2002)
**=======================================================================*/
#ifndef  _SO_DIALOG_COMPONENT_
#define  _SO_DIALOG_COMPONENT_

#include <DialogViz/dialog/SoTopComponent.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFInt32.h>

class SoTransform ;
class SoTranslation;
class SoScale;

/**
 * @VSGEXT Abstract base class for all basic dialog components.
 * 
 * @ingroup Dialog
 * 
 * @DESCRIPTION
 *   This class specifies the general appearance of the component.
 *
 *   @TABLE_1B
 *   @TR @TABLE_0B
 *   @TR #edgeStyle field change
 *   @TD NONE
 *   @TD SHADOW_IN
 *   @TD SHADOW_OUT
 *   @TR
 *   @TD @IMAGE DialogComponent_edgeStyle_NONE.jpg
 *   @TD @IMAGE DialogComponent_edgeStyle_SHADOW_IN.jpg
 *   @TD @IMAGE DialogComponent_edgeStyle_SHADOW_OUT.jpg
 *   @TABLE_END
 *   @TABLE_END
 *
 * @SEE_ALSO
 *   SoDialogCheckBox,
 *   SoDialogCheckBoxLauncher,
 *   SoDialogComboBox,
 *   SoDialogRadioButtons,
 *   SoDialogCustom,
 *   SoDialogEditText,
 *   SoDialogLabel,
 *   SoColumnDialog,
 *   SoRowDialog,
 *   SoTabDialog,
 *   SoDialogPushButton,
 *   SoDialogPushButtonLauncher,
 *   SoDialogSeparator,
 *   SoDialogIntegerSlider,
 *   SoDialogRealSlider 
 *
 */

class DIALOGVIZ_API SoDialogComponent : public SoTopComponent  
{
  SO_DG_HEADER(SoDialogComponent);

 public:

  /**
   * Preferred width of the element. Default is zero.
   * The default value zero indicates that the width of the component will be 
   * computed automatically according to its contents.
   */
  SoSFInt32 width;

  /**
   * Preferred height of the element. Default is zero.
   * The default value zero indicates that the height of the component will be 
   * computed automatically according to its contents.
   */
  SoSFInt32 height;

  /**
   * When set to FALSE, this allows the component to be resized in the width direction.
   * Default is TRUE.
   */
  SoSFBool  fixedWidth;

  /**
   * When set to FALSE, this allows the component to be resized in the height direction.
   * Default is TRUE.
   */
  SoSFBool  fixedHeight;

  /**
   * Sets minimum component width. Default is zero.
   * The default value zero indicates no minimum value is specified.
   */
  SoSFInt32 minWidth;

  /**
   * Sets maximum component width. Default is zero.
   * The default value zero indicates no maximum value is specified.
   */
  SoSFInt32 maxWidth;

  /**
   * Sets minimum component height. Default is zero.
   * The default value zero indicates no minimum value is specified.
   */
  SoSFInt32 minHeight;

  /**
   * Sets maximum component height. Default is zero.
   * The default value zero indicates no maximum value is specified.
   */
  SoSFInt32 maxHeight;

  enum EdgeStyle {
    /** The component does not have any border (default). */
    NONE,
    /** The component edge appears depressed (goes in). */
    SHADOW_IN,
    /** The component edge appears raised (sticks out). */
    SHADOW_OUT
  };
  
  /**
   * Controls the appearance of the edges of the component. Default value is NONE.
   */
  SoSFEnum edgeStyle;

  /**
   * Specifies if the label of the component defined in SoDialogViz is visible or not.
   * Default is TRUE.
   */
  SoSFBool labelVisibility;


/*==============================================================================*/
SoINTERNAL public:

  static void initClass();
  static void exitClass();
  virtual void buildWidget(SoWidget parent, SbVec2i32 & rSize, SbVec2i32 & pos, SbBool isActive2d);
  virtual void destroyWidget();
  virtual SoWidget getLabelWidget();
  virtual void eventNotify(unsigned int event, uintptr_t param);
  virtual void updateFromSensor(SoSensor* sensor);
  virtual void setLabelSize(SbVec2i32& size);
  virtual void setComponentSize(SbVec2i32 &size);
  virtual SbVec2i32 getComponentInitSize();
  virtual SbVec2i32 getLabelInitSize();
  virtual void setFocus() {};
  virtual void changeWidgetEnable(SbBool state);
  virtual void resetSize();
  void    getSize(SbVec2i32 &size, SbVec2i32 &min, SbVec2i32 &max);
  SoWidget  getWidget();
  void get2DComponentSize(SbVec2i32& size, SbVec2i32 &pos);
  void get3DComponentSize(SbVec2i32& size, SbVec2i32 &pos);
  void* getLayout();

protected:

  SoWidget    m_labelWidget;
  SoWidget    m_componentWidget;
  SoWidget    m_componentWidgetXt;
  void *    m_layout;
  void *    m_spacer;
  SbVec2i32 m_componentSize;
  SbVec2i32 m_labelSize;
  SbVec2i32 m_componentInitSize;  // keep component init size to speed up computing.
  SbVec2i32 m_labelInitSize;  // keep component init size to speed up computing.
  SbVec2i32 m_olSize;

  SoDialogComponent();
  virtual      ~SoDialogComponent();
  virtual void getDefaultSize(SbVec2i32 &size, SbVec2i32 &min, SbVec2i32 &max);
          void getDefaultState(SbVec2i32 &size, SbVec2i32 &min, SbVec2i32 &max);

  virtual void changeLabelVisibility() {};
  virtual void changeLabelAlignment();
  virtual void changeEdgeStyle();
  virtual void updateComponentWidget();
  virtual void changeEnable();
  virtual void changeWidth();
  virtual void changeHeight();
  virtual void changeMinMaxSize();

private:

  SbVec2i32 m_pos;
  SbVec2i32 m_initSize;
  SbVec2i32 m_initMinSize;
  SbVec2i32 m_initMaxSize;
  SbBool m_isFirstBuild;

  FIELD_SENSOR(edgeStyle);
  FIELD_SENSOR(labelVisibility);
  FIELD_SENSOR(margin);
  FIELD_SENSOR(width);
  FIELD_SENSOR(height);
  FIELD_SENSOR(minWidth);
  FIELD_SENSOR(minHeight);
  FIELD_SENSOR(maxWidth);
  FIELD_SENSOR(maxHeight);

  void createComponentWidget(SoWidget parent);
  void setSize(int32_t sw, int32_t sh, int32_t smw, int32_t smh, int32_t smmw, int32_t smmh);
  void setDefaultState();

///////////////////////////////////////////////////////////////////////////////////////
// 3D methods
SoINTERNAL public:
  static char* DialogComponent;  // Internal default skins.
  static void change3DSkin();
  static SbBool isSkinLoaded();
  static void setSkinLoaded(SbBool loaded);

  SO_DG_CATALOG_ENTRY_HEADER(mainCptSeparator);
  SO_DG_CATALOG_ENTRY_HEADER(edgeStyleSwitch);
  SO_DG_CATALOG_ENTRY_HEADER(edgeStyleNone);
  SO_DG_CATALOG_ENTRY_HEADER(edgeStyleShadowIn);
  SO_DG_CATALOG_ENTRY_HEADER(edgeStyleShadowOut);

  SoTranslation *componentTranslation;  // need this translation to be reported to children
  SoTransform  *componentTransform;

 protected:

  SoScale* componentScale;
  float m_mComponentCachedDepth;

  virtual void change3DLabelVisibility() {};
  virtual void change3DEdgeStyle();

 private:

  void update3DDialogComponent();
  void create3DDialogComponent();

  static SbBool m_isSkinLoaded;

SoEXTENDER public:
  virtual void getBoundingBox(SoGetBoundingBoxAction* action);

///////////////////////////////////////////////////////////////////////////////////////
};

#endif // _SO_DIALOG_COMPONENT_
