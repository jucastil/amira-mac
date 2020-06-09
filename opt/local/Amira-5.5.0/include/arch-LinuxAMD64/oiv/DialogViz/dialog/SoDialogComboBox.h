/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Oct 2002)
**=======================================================================*/
#ifndef  _SO_DIALOG_COMBO_BOX_
#define  _SO_DIALOG_COMBO_BOX_

#include <DialogViz/dialog/SoDialogChoice.h>

/**
 * @VSGEXT Dialog ComboBox node.
 * 
 * @ingroup Dialog
 * 
 * @DESCRIPTION
 *   This node defines a ComboBox component for the dialog.
 *
 *   @IMAGE DialogComboBox.jpg
 *   @IMAGE DialogComboBoxOpenList.jpg
 *
 *   This component does not support \\n (newline) characters in its fields.
 *
 *   You can change the parts in any instance of this combo box using setPart().
 *   The default part geometries are defined as resources for this SoDialogComboBox class.
 *   They are detailed below in the Catalog Parts section of the online reference page
 *   for this class. You can make your program use different default resources for the
 *   parts by copying the file $OIVHOME/data/DialogViz/Skins/default/DialogComboBox.iv
 *   into your own directory, editing the file, and then setting the environment
 *   variable DIALOGVIZ_SKINS_DIR to be a path to that directory, or by using the
 *   setSkinDirectory() method in your application.
 *
 * @FILE_FORMAT_DEFAULT
 *   DialogComboBox {
 *   @TABLE_FILE_FORMAT
 *       @TR // fields from SoDialogChoice
 *       @TR items            @TD []
 *       @TR selectedItem     @TD 0
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
 * @CATALOG_PARTS_INCLUDE sodialogcombobox.cat.html
 *
 * @SEE_ALSO
 *   SoDialogCheckBox,
 *   SoDialogCheckBoxLauncher,
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

class DIALOGVIZ_API SoDialogComboBox : public SoDialogChoice  
{
  SO_DG_HEADER(SoDialogComboBox);
  

 public:

  /**
   * Constructor
   */
  SoDialogComboBox();

/*==============================================================================*/
SoINTERNAL public:
  SoWidget *m_itemWidget;
  virtual void   buildWidget(SoWidget parent, SbVec2i32 &rSize, SbVec2i32 & pos, SbBool isActive2d);
  virtual void   destroyWidget();
  void   eventNotify(unsigned int event, uintptr_t lParam);
  static  void   initClass();
  static  void   exitClass();
  SoWidget m_comboBoxWidget;

  void updateComboBoxWidget();
  void updateLabelWidget();

protected:
  virtual        ~SoDialogComboBox();

 private:
  SbVec2i32 m_olSize, m_ocSize;
  void createComboBoxWidget();
  void createLabelWidget();
  virtual SbVec2i32 getComponentInitSize();
  virtual void getDefaultSize(SbVec2i32 &size, SbVec2i32 &min, SbVec2i32 &max);

  // reflex function when fields change
  virtual void changeItems();
  virtual void changeSelectedItem();
  virtual void changeLabel();
  virtual void changeLabelVisibility();
  virtual void changeLabelAlignment();
  virtual void changeEnable();
  virtual void changeWidgetEnable(SbBool state);
  virtual void changeEdgeStyle();

///////////////////////////////////////////////////////////////////////////////////////
// 3D methods
SoINTERNAL public:
  static char* DialogComboBox;  // Internal default skins.
  static void change3DSkin();
  static SbBool isSkinLoaded();
  static void setSkinLoaded(SbBool loaded);

protected:
  SO_DG_CATALOG_ENTRY_HEADER( labelSep       );
  SO_DG_CATALOG_ENTRY_HEADER( labelSwitch    );
  SO_DG_CATALOG_ENTRY_HEADER( labelProp      );
  SO_DG_CATALOG_ENTRY_HEADER( frameSep       );
  SO_DG_CATALOG_ENTRY_HEADER( frame          );
  SO_DG_CATALOG_ENTRY_HEADER( textSep        );
  SO_DG_CATALOG_ENTRY_HEADER( textProp       );
  SO_DG_CATALOG_ENTRY_HEADER( buttonSep      );
  SO_DG_CATALOG_ENTRY_HEADER( buttonSwitch   );
  SO_DG_CATALOG_ENTRY_HEADER( buttonReleased );
  SO_DG_CATALOG_ENTRY_HEADER( buttonPressed  );
  SO_DG_CATALOG_ENTRY_HEADER( itemsSwitch    );
  SO_DG_CATALOG_ENTRY_HEADER( itemStrucSep   );
  SO_DG_CATALOG_ENTRY_HEADER( itemSep        );
  SO_DG_CATALOG_ENTRY_HEADER( itemFrame      );
  SO_DG_CATALOG_ENTRY_HEADER( itemTextSep    );
  SO_DG_CATALOG_ENTRY_HEADER( itemTextProp   );

  SoScale *comboBoxFrameScale;
  SoText3 *comboBoxText, *comboBoxItemText;
  SoTransform *comboBoxFrameTransform, *comboBoxButtonTransform, *comboBoxItemTransform;
  SoTranslation *comboBoxFrameTranslation, *comboBoxTextTranslation, \
                *comboBoxItemsTranslation, *comboBoxButtonTranslation, \
                *comboBoxItemTranslation, *comboBoxItemTextTranslation;

private:

  SoNodeList m_item3DTextList;
  SoNodeList m_item3DItemList;
  SoNodeList m_item3DTextScList;
  SoNodeList m_item3DTextScInvList;
  SbBox3f m_textCachedBBox;

  void create3DDialogComboBox();
  void update3DComboBox();
  void update3DLabel();

  virtual void change3DLabel();
  virtual void change3DLabelAlignment();
  virtual void change3DLabelVisibility();
  virtual void change3DSelectedItem();
          void change3DItems();
  virtual void set3DInactive();

  static void startCB3D( void *, SoDragger *inDragger );
  void draggerStartCallback3D();

  SbBool m_isOpenedDropDown;

  static SbBool m_isSkinLoaded;

///////////////////////////////////////////////////////////////////////////////////////

};

#endif // _SO_DIALOG_COMBO_BOX_
