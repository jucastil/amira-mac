/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Oct 2002)
**=======================================================================*/
#ifndef  _SO_DIALOG_CHECK_BOX_
#define  _SO_DIALOG_CHECK_BOX_

#include <DialogViz/dialog/SoDialogComponent.h>

class SoDialogCheckBoxAuditor;
class SoText3;
class SoSeparator;
class SoSwitch;

/**
 * @VSGEXT Dialog CheckBox node.
 * 
 * @ingroup Dialog
 * 
 * @DESCRIPTION
 *   This node defines a check box component for the dialog.
 *   @IMAGE DialogCheckBox.jpg
 *
 *   The #state field is the state of the check box (TRUE/FALSE).
 *   The #onString field represents the string displayed when the check state is TRUE,
 *   the #offString field represents the string displayed when the state is FALSE.
 *
 *   @TABLE_1B
 *   @TR @TABLE_0B
 *   @TR #state field change
 *   @TD TRUE
 *   @TD FALSE
 *   @TR
 *   @TD @IMAGE DialogCheckBox_state_TRUE.jpg
 *   @TD @IMAGE DialogCheckBox_state_FALSE.jpg
 *   @TABLE_END
 *   @TABLE_END
 * 
 *   You can change the parts in any instance of this check button using setPart().
 *   The default part geometries are defined as resources for this SoDialogCheckBox class.
 *   They are detailed below in the Catalog Parts section of the online reference page
 *   for this class. You can make your program use different default resources for the
 *   parts by copying the file $OIVHOME/data/DialogViz/Skins/default/DialogCheckBox.iv
 *   into your own directory, editing the file, and then setting the environment
 *   variable DIALOGVIZ_SKINS_DIR to be a path to that directory, or by using the
 *   setSkinDirectory() method in your application.
 *
 * @FILE_FORMAT_DEFAULT
 *   DialogCheckBox {
 *   @TABLE_FILE_FORMAT
 *       @TR state            @TD FALSE
 *       @TR onString         @TD "On"
 *       @TR offString        @TD "Off"
 *       @TR // fields from SoDialogComponent
 *       @TR width            @TD 0
 *       @TR height           @TD 0
 *       @TR fixedWidth       @TD FALSE
 *       @TR fixedHeight      @TD FALSE
 *       @TR minWidth         @TD 0
 *       @TR maxWidth         @TD 0
 *       @TR minHeight        @TD 0
 *       @TR maxHeight        @TD 0
 *       @TR edgeStyle        @TD NONE
 *       @TR labelVisibility  @TD TRUE
 *       @TR // fields from SoDialogViz
 *       @TR enable           @TD TRUE
 *       @TR label            @TD ""
 *       @TR labelAlignment   @TD RIGHT
 *       @TR auditorID        @TD ""
 *   @TABLE_END
 *   }
 * 
 * @anchor SoDialogCheckBox_CatalogParts @BR
 * @CATALOG_PARTS_INCLUDE sodialogcheckbox.cat.html
 *
 * @SEE_ALSO
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
 *   SoDialogIntegerSlider,
 *   SoDialogRealSlider 
 *
 */

class DIALOGVIZ_API SoDialogCheckBox : public SoDialogComponent  
{
  SO_DG_HEADER(SoDialogCheckBox);

 public:

  /**
   * State of the check button. Default is FALSE.
   */
  SoSFBool state;

  /**
   * String used for state TRUE. Default is "On".
   */
  SoSFString  onString;

  /**
   * String used for state FALSE. Default is "Off".
   */
  SoSFString  offString;

  /**
   * Constructor.
   */
  SoDialogCheckBox();

  /**
   * Adds a dialogCheckBoxAuditor to current CheckBox component.
   */
  void addAuditor(SoDialogCheckBoxAuditor* auditor);

  /**
   * Removes the specified checkBoxAuditor from the auditor list.
   */
  void removeAuditor(SoDialogCheckBoxAuditor* auditor);

  /*==============================================================================*/

 SoINTERNAL public:
  static  void    initClass();
  static  void    exitClass();
  virtual void    buildWidget(SoWidget parent, SbVec2i32 &rSize, SbVec2i32 & pos, SbBool isActive2d);
  virtual void    destroyWidget();
  virtual void    eventNotify(unsigned int event, uintptr_t param);
  virtual SoWidget  getLabelWidget();
  virtual void    updateFromSensor(SoSensor* sensor);

  void updateLabelWidget();
  void updateCheckBoxWidget();

  void applyDlgCptAuditor();

 protected:
  SoWidget  m_checkBoxWidget;
          
  virtual ~SoDialogCheckBox();

  /* === FIELDS DECLARATION === */
  FIELD_SENSOR(state);
  FIELD_SENSOR(onString);
  FIELD_SENSOR(offString);

  // local change methods
  void changeOnOffString();

 private:

  SbVec2i32 m_oonSize, m_ooffSize, m_olSize;


  /* === SIZE COMPUTING METHODS === */
  virtual SbVec2i32 getComponentInitSize();
  virtual void getDefaultSize(SbVec2i32 &size, SbVec2i32 &min, SbVec2i32 &max);

  /* === CREATION METHODS === */
  void createLabelWidget();
  void createCheckBoxWidget();

  // local change methods
  void changeState();

  // inherited change methods from SoDialogComponent
  virtual void changeLabelVisibility();
  virtual void changeEdgeStyle();

  // inherited change methods from SoDialogViz
  virtual void changeEnable();
  virtual void changeWidgetEnable(SbBool state);
  virtual void changeLabel();
  virtual void changeLabelAlignment();

///////////////////////////////////////////////////////////////////////////////////////
// 3D methods
SoINTERNAL public:
  static char* DialogCheckBox; // Internal default skins.
  static void change3DSkin();
  static SbBool isSkinLoaded();
  static void setSkinLoaded(SbBool loaded);

protected:
  SO_DG_CATALOG_ENTRY_HEADER(frameSep);
  SO_DG_CATALOG_ENTRY_HEADER(frame);
  SO_DG_CATALOG_ENTRY_HEADER(stateSep);
  SO_DG_CATALOG_ENTRY_HEADER(stateSwitch);
  SO_DG_CATALOG_ENTRY_HEADER(stateOn);
  SO_DG_CATALOG_ENTRY_HEADER(stateOff);
  SO_DG_CATALOG_ENTRY_HEADER(labelSep);
  SO_DG_CATALOG_ENTRY_HEADER(labelSwitch);
  SO_DG_CATALOG_ENTRY_HEADER(labelProp);
  SO_DG_CATALOG_ENTRY_HEADER(onOffStringSep);
  SO_DG_CATALOG_ENTRY_HEADER(onOffStringProp);

  SoText3 *checkBoxString, *checkBoxLabel;
  SoTranslation *checkBoxLabelTranslation, *checkBoxButtonTranslation;
  SoTranslation *checkBoxStringTranslation, *checkBoxFrameTranslation;
  SoScale *checkBoxFrameScale;
  SoTransform *checkBoxFrameTransform;

  virtual void change3DState();
  void change3DOnOffString();

private:
  SbBox3f m_checkStringCachedBBox;

  void create3DDialogCheckBox();
  void update3DCheckBox();
  void update3DLabel();

  virtual void change3DLabelVisibility();
  void change3DLabel();
  virtual void change3DLabelAlignment();

  static void finishCB3D( void *, SoDragger *inDragger );
  virtual void draggerFinishCallback3D();

  static SbBool m_isSkinLoaded;

///////////////////////////////////////////////////////////////////////////////////////

};

#endif // _SO_DIALOG_CHECK_BOX_
