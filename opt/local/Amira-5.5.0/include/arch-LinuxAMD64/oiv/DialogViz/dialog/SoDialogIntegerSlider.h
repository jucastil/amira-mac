/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Oct 2002)
**=======================================================================*/
#ifndef  _SO_DIALOG_INTEGER_SLIDER_
#define  _SO_DIALOG_INTEGER_SLIDER_

#include <DialogViz/dialog/SoDialogSlider.h>

class SoDialogIntegerSliderAuditor;

/**
 * @VSGEXT Dialog integer slider node.
 * 
 * @ingroup Dialog
 * 
 * @DESCRIPTION
 *   This node defines a slider component for the dialog. Values of the slider are 
 *   integer values only.
 *
 *   @IMAGE DialogIntegerSlider.jpg
 *
 *   The #min field specifies the minimum possible value for the slider.
 *   The #max field specifies the maximum possible value for the slider.
 *   The #value field is the current value specifying the slider cursor position.
 *
 *   You can change the parts in any instance of this slider component using setPart().
 *   The default part geometries are defined as resources for this SoDialogSlider class.
 *   They are detailed below in the Catalog Parts section of the online reference page
 *   for this class. You can make your program use different default resources for the
 *   parts by copying the file $OIVHOME/data/DialogViz/Skins/default/DialogSlider.iv
 *   into your own directory, editing the file, and then setting the environment
 *   variable DIALOGVIZ_SKINS_DIR to be a path to that directory, or by using the
 *   setSkinDirectory() method in your application.
 *
 * @FILE_FORMAT_DEFAULT
 *   DialogIntegerSlider {
 *   @TABLE_FILE_FORMAT
 *       @TR min                @TD 0
 *       @TR max                @TD 1
 *       @TR value              @TD 0
 *       @TR format             @TD "%d"
 *       @TR // fields from SoDialogSlider
 *       @TR valueVisible       @TD TRUE
 *       @TR continuousTrigger  @TD FALSE
 *       @TR toggleVisible      @TD TRUE
 *       @TR fixedLimits        @TD FALSE
 *       @TR colors             @TD []
 *       @TR shadedColors       @TD TRUE
 *       @TR // fields from SoDialogComponent
 *       @TR width              @TD 0
 *       @TR height             @TD 0
 *       @TR fixedWidth         @TD FALSE
 *       @TR fixedHeight        @TD FALSE
 *       @TR minWidth           @TD 0
 *       @TR maxWidth           @TD 0
 *       @TR minHeight          @TD 0
 *       @TR maxHeight          @TD 0
 *       @TR margin             @TD 0
 *       @TR edgeStyle          @TD NONE
 *       @TR labelVisibility    @TD TRUE
 *       @TR // fields from SoDialogViz
 *       @TR enable             @TD TRUE
 *       @TR label              @TD ""
 *       @TR labelAlignment     @TD RIGHT
 *       @TR auditorID        @TD ""
 *   @TABLE_END
 *   }
 *
 * @CATALOG_PARTS_INCLUDE sodialogintegerslider.cat.html
 *
 * @SEE_ALSO
 *   SoDialogSlider,
 *   SoDialogCheckBox,
 *   SoDialogCheckBoxLauncher,
 *   SoDialogComboBox,
 *   SoDialogRadioButtons,
 *   SoDialogCustom,
 *   SoDialogEditText,
 *   SoColumnDialog,
 *   SoRowDialog,
 *   SoTabDialog,
 *   SoDialogLabel,
 *   SoDialogPushButton,
 *   SoDialogPushButtonLauncher,
 *   SoDialogSeparator,
 *   SoDialogRealSlider
 *
 */

class DIALOGVIZ_API SoDialogIntegerSlider : public SoDialogSlider  
{
  SO_DG_HEADER(SoDialogIntegerSlider);

 public:

  /**
   * Minimum value. Default is 0.
   */
  SoSFInt32 min;

  /**
   * Maximum value. Default is 1.
   */
  SoSFInt32 max;

  /**
   * Current value. Default is 0.
   */
  SoSFInt32 value;

  /**
   * Constructor.
   */
  SoDialogIntegerSlider();

  /**
   * Adds a dialogIntegerSliderAuditor to the current integerSlider component.
   */
  void addAuditor(SoDialogIntegerSliderAuditor* auditor);

  /**
   * Removes the specified integerSliderAuditor from the auditor list.
   */
  void removeAuditor(SoDialogIntegerSliderAuditor* auditor);


  /*==============================================================================*/
 SoINTERNAL public:
  static  void initClass();
  static  void exitClass();
  virtual void changeSliderValue();
  virtual void setValueFromEdit(SbBool is2dRender);
  virtual void updateFromSensor(SoSensor* sensor);
  virtual void applyDlgCptAuditor();
  virtual void   buildWidget(SoWidget parent, SbVec2i32 &rSize, SbVec2i32 &pos, SbBool isActive2d);

 protected:
  virtual      ~SoDialogIntegerSlider();
  virtual void changeEditValue();
  virtual void setValueFromSlider(float newValue);
  virtual void setValue();

 private:
  
  FIELD_SENSOR(min);
  FIELD_SENSOR(max);
  FIELD_SENSOR(value);

  virtual int computeEditZoneWidth();


///////////////////////////////////////////////////////////////////////////////////////
// 3D methods
SoINTERNAL public:

private:

  virtual void change3DEditValue();
  virtual void computeNewSliderEditValue(SoKeyboardEvent* kev);

SoEXTENDER public:
  virtual void finish3DEditing();

///////////////////////////////////////////////////////////////////////////////////////


};

#endif // _SO_DIALOG_INTEGER_SLIDER_
