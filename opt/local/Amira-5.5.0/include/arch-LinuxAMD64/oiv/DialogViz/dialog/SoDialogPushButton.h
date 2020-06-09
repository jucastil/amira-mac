/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Oct 2002)
**=======================================================================*/
#ifndef  _SO_DIALOG_PUSH_BUTTON_
#define  _SO_DIALOG_PUSH_BUTTON_

#include <DialogViz/dialog/SoDialogComponent.h>

class SoDialogPushButtonAuditor;

/**
 * @VSGEXT Dialog push button node.
 * 
 * @ingroup Dialog
 * 
 * @DESCRIPTION
 *   This node defines a push button component for the dialog. This node is composed
 *   of a label on the left and a push button on the right. By default the text of 
 *   the label (#label) and the text of the button (#buttonLabel) are empty strings.
 *
 *   A 2D SoDialogPushButton component looks like:
 *      @IMAGE DialogPushButton.jpg
 *
 *   To add or remove an SoDialogPushButtonAuditor, use the addAuditor() and removeAuditor() methods.
 *   The push button auditor happens when the mouse left button is up, or the \<SPACE> key is released.
 *
 *   You can change the parts in any instance of this button using setPart().
 *   The default part geometries are defined as resources for this SoDialogPushButton class.
 *   They are detailed below in the Catalog Parts section of the online reference page
 *   for this class. You can make your program use different default resources for the
 *   parts by copying the file $OIVHOME/data/DialogViz/Skins/default/DialogPushButton.iv
 *   into your own directory, editing the file, and then setting the environment
 *   variable DIALOGVIZ_SKINS_DIR to be a path to that directory, or by using the
 *   setSkinDirectory() method in your application.
 *
 * @FILE_FORMAT_DEFAULT
 *   DialogPushButton {
 *   @TABLE_FILE_FORMAT
 *       @TR buttonLabel      @TD ""
 *       @TR // fields from SoDialogComponent
 *       @TR width            @TD 0
 *       @TR height           @TD 0
 *       @TR fixedWidth       @TD FALSE
 *       @TR fixedHeight      @TD FALSE
 *       @TR minWidth         @TD 0
 *       @TR maxWidth         @TD 0
 *       @TR minHeight        @TD 0
 *       @TR maxHeight        @TD 0
 *       @TR margin           @TD 0
 *       @TR edgeStyle        @TD NONE
 *       @TR labelVisibility  @TD TRUE
 *       @TR // fields from SoDialogViz
 *       @TR enable           @TD TRUE
 *       @TR label            @TD ""
 *       @TR labelAlignment   @TD RIGHT
 *       @TR auditorID      @TD ""
 *   @TABLE_END
 *   }
 *
 * @anchor SoDialogPushButton_CatalogParts @BR
 * @CATALOG_PARTS_INCLUDE sodialogpushbutton.cat.html
 *
 * @USAGE
 *
 *  @B Tab: @b Go to the next control in the current SoTopLevelDialog.
 *
 *  @B \<SHIFT\> + Tab: @b Go to the previous control in the current SoTopLevelDialog.
 *
 *  @B \<SPACE\>: @b If the window has focus, space bar activates the push button.
 * 
 * @SEE_ALSO
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
 *   SoDialogPushButtonLauncher,
 *   SoDialogSeparator,
 *   SoDialogIntegerSlider,
 *   SoDialogRealSlider 
 *
 */

class DIALOGVIZ_API SoDialogPushButton : public SoDialogComponent  
{
  SO_DG_HEADER(SoDialogPushButton);

 public:

  /**
   * Specifies the label of the button. Default is empty string.
   */
  SoSFString buttonLabel;

  /**
   * Constructor.
   */
  SoDialogPushButton();

  /**
   * Adds a dialogPushButtonAuditor to the current PushButton component.
   */
  void addAuditor(SoDialogPushButtonAuditor* auditor);

  /**
   * Removes the specified pushButtonAuditor from the auditor list.
   */
  void removeAuditor(SoDialogPushButtonAuditor* auditor);

  /*==============================================================================*/
 SoINTERNAL public:
  static  void    initClass();
  static  void    exitClass();
  virtual void    buildWidget(SoWidget parent, SbVec2i32 &rSize, SbVec2i32 & pos, SbBool isActive2d);
  virtual void    destroyWidget();
  virtual SoWidget  getLabelWidget();
  virtual void    updateFromSensor(SoSensor* sensor);
  virtual void    eventNotify(unsigned int event, uintptr_t param);

  void activateButton();
  void      updateLabelWidget();
  void      updateButtonWidget();
  void applyDlgCptAuditor();

 protected:
  SoWidget m_buttonWidget;
         
  virtual         ~SoDialogPushButton();

  // reflex function when fields change
  virtual void changeEdgeStyle();
  virtual void changeLabelVisibility();
  virtual void changeEnable();
  virtual void changeWidgetEnable(SbBool state);
  virtual void changeLabel();
  virtual void changeLabelAlignment();
  void changeButtonLabel();
  void changeButtonState(SbBool state);

 private:

  SbVec2i32 m_obSize; // original button size function of button text

  FIELD_SENSOR(buttonLabel);
  void      createLabelWidget();
  void      createButtonWidget();
  virtual SbVec2i32 getComponentInitSize();
  virtual void      getDefaultSize(SbVec2i32 &size, SbVec2i32 &min, SbVec2i32 &max);

///////////////////////////////////////////////////////////////////////////////////////
// 3D methods
SoINTERNAL public:
  static char* DialogPushButton; // Internal default skins.
  static void change3DSkin();
  static SbBool isSkinLoaded();
  static void setSkinLoaded(SbBool loaded);

  void set3DPressedGeometry(SoNode* node);
  void set3DReleasedGeometry(SoNode* node);

protected:
  SO_DG_CATALOG_ENTRY_HEADER(labelSep);
  SO_DG_CATALOG_ENTRY_HEADER(labelSwitch);
  SO_DG_CATALOG_ENTRY_HEADER(labelProp);
  SO_DG_CATALOG_ENTRY_HEADER(frameSep);
  SO_DG_CATALOG_ENTRY_HEADER(frameSwitch);
  SO_DG_CATALOG_ENTRY_HEADER(released);
  SO_DG_CATALOG_ENTRY_HEADER(pressed);
  SO_DG_CATALOG_ENTRY_HEADER(buttonLabelSep);
  SO_DG_CATALOG_ENTRY_HEADER(buttonLabelProp);

  SoText3 *pushButtonButtonLabel, *pushButtonLabel;
  SoTranslation *pushButtonLabelTranslation, *pushButtonFrameTranslation;
  SoTranslation *pushButtonButtonLabelTranslation;
  SoScale *pushButtonFrameScale;
  SoTransform *pushButtonFrameTransform;

private:
  SbBox3f m_buttonLabelCachedBBox;
  static SbBool m_isSkinLoaded;

  void create3DDialogPushButton();
  void update3DButton();
  void update3DLabel();

  void change3DButtonLabel();
  virtual void change3DLabelVisibility();
  virtual void change3DLabel();
  virtual void change3DLabelAlignment();
  void change3DButtonState(SbBool state);

  static void startCB3D( void *, SoDragger *inDragger );
  static void finishCB3D( void *, SoDragger *inDragger );
  void draggerStartCallback3D();
  void draggerFinishCallback3D();

///////////////////////////////////////////////////////////////////////////////////////
};

#endif // _SO_DIALOG_PUSH_BUTTON_
